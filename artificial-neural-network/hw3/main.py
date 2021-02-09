import numpy as np
import time
import random
import argparse
import torch
from torch import optim
import torch.nn.functional as F
import os
import csv

from torch.utils.tensorboard import SummaryWriter

random.seed(1229)

import cotk

from model import RNN

parser = argparse.ArgumentParser()

parser.add_argument('--name', type=str, default="run",
    help='Experiment name. Default: run')
parser.add_argument('--num_epochs', type=int, default=50,
    help='Number of training epoch. Default: 50')
parser.add_argument('--batch_size', type=int, default=32,
    help='The number of batch_size. Default: 32')
parser.add_argument('--learning_rate', type=float, default=1e-3,
    help='Learning rate during optimization. Default: 1e-3')
parser.add_argument('--test', type=str, default=None,
    help='Evaluate the model with the specified name. Default: None')
parser.add_argument('--embed_units', type=int, default=300,
    help='Size of word embedding. Default: 300')
parser.add_argument('--units', type=int, default=64,
    help='Size of RNN. Default: 64')
parser.add_argument('--layers', type=int, default=1,
    help='Number of layers of RNN. Default: 1')
parser.add_argument('--data_dir', type=str, default='./data',
    help='Data directory. Default: ../data')
parser.add_argument('--wordvec_dir', type=str, default='./wordvec',
    help='Wordvector directory. Default: ../wordvec')
parser.add_argument('--train_dir', type=str, default='./train',
    help='Training directory for saving model. Default: ./train')
parser.add_argument('--decode_strategy', type=str, choices=["random", "top-p"], default="random",
    help='The strategy for decoding. Can be "random" or "top-p". Default: random')
parser.add_argument('--temperature', type=float, default=1,
    help='The temperature for decoding. Default: 1')
parser.add_argument('--max_probability', type=float, default=0.8,
    help='The p for top-p decoding. Default: 0.8')
parser.add_argument('--cell_type', type=str, default='rnn', choices=['rnn', 'lstm', 'gru'])
parser.add_argument('--embedding', type=str, choices=['pretrained', 'untrained'], default='pretrained')
args = parser.parse_args()

class TensorboardStat:
    status: str  # train, val, test...
    writer: SummaryWriter

    def __init__(self, writer, status):
        self.step = 0
        self.writer = writer
        self.status = status

    def add(self, loss):
        self.writer.add_scalar(f'Loss/{self.status}', loss, self.step)
        self.step += 1


def csv_write_row(filename, row):
    with open(filename, 'a') as file:
        csv_writer = csv.writer(file)
        csv_writer.writerow(row)

def fast_evaluate(model, dataloader, datakey, device):
    model.eval()
    with torch.no_grad():
        # use cotk metric to get Perplexity
        metric = cotk.metric.PerplexityMetric(dataloader, reference_allvocabs_key="sent_allvocabs", reference_len_key="sent_length")
        for batched_data in dataloader.get_batches(datakey, batch_size=args.batch_size, shuffle=False):
            _, logits = model(batched_data, device)
            batched_data["gen_log_prob"] = F.log_softmax(logits, dim=-1)
            metric.forward(batched_data)
            # Perplexity metric need a dict, for example:
            # batched_data = {
            #    "gen_log_prob": a tensor with shape [batch_size, sent_length, vocab_size]
            #    "sent_allvocabs": a tensor indicating the sentence with shape [batch, sent_length]
            #    "sent_length": a tensor indicating the sentence length with shape [batch]
            # }

    model.train() # return to training mode

    perplexity = metric.close()['perplexity']
    loss = np.log(perplexity)
    return loss, perplexity

def evaluate(model, dataloader, datakey, device):
    model.eval()
    with torch.no_grad():
        metric = cotk.metric.MetricChain()
        # use cotk metric to get Bleu metrics and generated sentences
        metric.add_metric(cotk.metric.FwBwBleuCorpusMetric(dataloader, dataloader.get_all_batch(datakey)['sent']))
        metric.add_metric(cotk.metric.LanguageGenerationRecorder(dataloader))
        for i in range(0, 5000, args.batch_size):
            gen_sent = model.inference(min(args.batch_size, 5000 - i), device, args.decode_strategy, args.temperature, args.max_probability)
            data = {"gen": gen_sent}
            metric.forward(data)
            # FwBwBleuCorpusMetric and LanguageGenerationRecorder need a dict, for example:
            # batched_data = {
            #    "gen": a tensor indicating the generated sentence with shape [batch_size, sent_length]
            # }

    model.train() # return to training mode

    return metric.close()

def show_example(model, dataloader, num_samples, device):
    model.eval()
    with torch.no_grad():
        metric = cotk.metric.LanguageGenerationRecorder(dataloader)
        # use cotk metric to get generated sentences
        gen_sent = model.inference(num_samples, device, args.decode_strategy, args.temperature, args.max_probability)
        data = {"gen": gen_sent}
        metric.forward(data)
        # LanguageGenerationRecorder need a dict, for example:
        # batched_data = {
        #    "gen": a tensor indicating the generated sentence with shape [batch_size, sent_length]
        # }
    model.train() # return to training mode

    return metric.close()["gen"]


if __name__ == '__main__':
    print(args)
    args.name = f'{args.cell_type}-{args.embedding}-{args.layers}'
    device = torch.device("cuda" if torch.cuda.is_available() else "cpu")
    if not os.path.exists(args.train_dir):
        os.mkdir(args.train_dir)
    dataloader = cotk.dataloader.LanguageGeneration(args.data_dir, tokenizer="space", convert_to_lower_letter=False, min_frequent_vocab_times=0)
    wordvec = cotk.wordvector.GeneralWordVector(args.wordvec_dir)

    if not args.test:
        print("Created model with fresh parameters.")
        model = RNN(
            args.embed_units,
            args.units,
            args.layers,
            dataloader.frequent_vocab_size,
            torch.tensor(wordvec.load_matrix(args.embed_units, dataloader.frequent_vocab_list), dtype=torch.float, device=device),
            dataloader,
            cell_type=args.cell_type,
            embedding_type=args.embedding)
        model.to(device)

        optimizer = optim.Adam(model.parameters(), lr=args.learning_rate, weight_decay=0)
        best_val_ppl = float("inf")
        best_epoch = -1

        # tensorboard writer
        writer = SummaryWriter(f'log/{args.name}')
        train_stat = TensorboardStat(writer, 'train')
        val_stat = TensorboardStat(writer, 'val')

        for epoch in range(1, args.num_epochs + 1):
            start_time = time.time()

            losses = []
            for batch, batched_data in enumerate(dataloader.get_batches("train", batch_size=args.batch_size, shuffle=True)):
                optimizer.zero_grad()
                loss, _ = model(batched_data, device)
                loss.backward()
                optimizer.step()
                losses.append(loss.tolist())

                if (batch + 1) % 100 == 0:
                    print("Epoch %d Batch %d, train loss %f" % (epoch, batch, np.mean(losses[-100:])))

            train_loss = np.mean(losses)
            train_stat.add(train_loss)

            val_loss, val_ppl = fast_evaluate(model, dataloader, "dev", device)
            val_stat.add(val_loss)

            if val_ppl < best_val_ppl:
                best_val_ppl = val_ppl
                best_epoch = epoch

                with open(os.path.join(args.train_dir, 'checkpoint_%s.pth.tar' % args.name), 'wb') as fout:
                    torch.save(model, fout)

            samples = show_example(model, dataloader, 5, device)

            epoch_time = time.time() - start_time
            print("Epoch " + str(epoch) + " of " + str(args.num_epochs) + " took " + str(epoch_time) + "s")
            print("  training loss:                 " + str(train_loss))
            print("  validation loss:               " + str(val_loss))
            print("  validation perplexity:         " + str(val_ppl))
            print("  best epoch:                    " + str(best_epoch))
            print("  best validation perplexity:    " + str(best_val_ppl))

            for example_id, sent in enumerate(samples):
                print("Example %d: " % example_id + " ".join(sent))
        csv_write_row('train.csv', [args.cell_type, args.embedding, args.layers, best_epoch, best_val_ppl])

    else:
        model_path = os.path.join(args.train_dir, 'checkpoint_%s.pth.tar' % args.test)
        if os.path.exists(model_path):
            print("Loading model from %s" % model_path)
            model = torch.load(model_path)
        else:
            raise RuntimeError("No such checkpoint")

        _, ppl = fast_evaluate(model, dataloader, "test", device)
        result = evaluate(model, dataloader, "test", device)
        with open(f'output/{args.test}-{args.decode_strategy}-{args.temperature}-{args.max_probability}.txt', 'w') as fout:
            for sent in result["gen"]:
                fout.write(" ".join(sent) + "\n")
        csv_write_row('test.csv', [args.test, args.decode_strategy,
                                   args.temperature, args.max_probability, ppl,
                                   result["fw-bleu"], result["bw-bleu"], result["fw-bw-bleu"]])
        print("        test_set, perplexity %.2f, forward BLEU %.3f, backward BLEU %.3f, harmonic BLEU %.3f" % (ppl, result["fw-bleu"], result["bw-bleu"], result["fw-bw-bleu"]))
        print("        test_set, write inference results to output.txt")
