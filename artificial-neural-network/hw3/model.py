import numpy as np
import torch
from torch import nn
import torch.nn.functional as F

from rnn_cell import RNNCell, GRUCell, LSTMCell

class RNN(nn.Module):
    def __init__(self,
            num_embed_units,  # pretrained wordvec size
            num_units,        # RNN units size
            num_layers,       # number of RNN layers
            num_vocabs,       # vocabulary size
            wordvec,          # pretrained wordvec matrix
            dataloader,       # dataloader
            cell_type,  # argument of cell type
            embedding_type    # argument of embedding type
            ):

        super().__init__()

        # load pretrained wordvec
        self.wordvec = wordvec
        # the dataloader
        self.dataloader = dataloader

        # TODO START
        # fill the parameter for multi-layer RNN
        if embedding_type == 'pretrained':
            self.embedding = nn.Embedding.from_pretrained(wordvec)
        else:
            self.embedding = nn.Embedding(num_vocabs, num_embed_units)
        CELL_MAP = {'rnn': RNNCell, 'gru': GRUCell, 'lstm': LSTMCell}
        cell = CELL_MAP[cell_type]
        self.cells = nn.Sequential(
            cell(num_embed_units, num_units),
            *[cell(num_units, num_units) for _ in range(num_layers - 1)]
        )
        # TODO END

        # intialize other layers
        self.linear = nn.Linear(num_units, num_vocabs)

    def forward(self, batched_data, device):
        # Padded Sentences
        sent = torch.tensor(batched_data["sent"], dtype=torch.long, device=device) # shape: (batch_size, length)
        # An example:
        #   [
        #   [2, 4, 5, 6, 3, 0],   # first sentence: <go> how are you <eos> <pad>
        #   [2, 7, 3, 0, 0, 0],   # second sentence:  <go> hello <eos> <pad> <pad> <pad>
        #   [2, 7, 8, 1, 1, 3]    # third sentence: <go> hello i <unk> <unk> <eos>
        #   ]
        # You can use self.dataloader.convert_ids_to_sentence(sent[0]) to translate the first sentence to string in this batch.

        # Sentence Lengths
        length = torch.tensor(batched_data["sent_length"], dtype=torch.long, device=device) # shape: (batch)
        # An example (corresponding to the above 3 sentences):
        #   [5, 3, 6]

        batch_size, seqlen = sent.shape

        # TODO START
        # implement embedding layer
        embedding = self.embedding(sent) # shape: (batch_size, length, num_embed_units)
        # TODO END

        now_state = []
        for cell in self.cells:
            now_state.append(cell.init(batch_size, device))

        loss = 0
        logits_per_step = []
        for i in range(seqlen - 1):
            hidden = embedding[:, i]
            for j, cell in enumerate(self.cells):
                hidden, now_state[j] = cell(hidden, now_state[j]) # shape: (batch_size, num_units)
            logits = self.linear(hidden) # shape: (batch_size, num_vocabs)
            logits_per_step.append(logits)

        # TODO START
        # calculate loss
        vocab_logits = torch.stack(logits_per_step, dim=1)  # shape: (batch_size, seqlen-1, num_vocabs)
        vocab_logits = F.log_softmax(vocab_logits, -1)
        sent_no_go = sent[:, 1:].unsqueeze(-1)  # remove go and add one dimension for gather
        sent_logits = vocab_logits.gather(2, sent_no_go).squeeze()  # shape: (batch_size, seqlen-1)
        length_no_go = length - 1
        for i in range(seqlen - 1):  # set pad and end to 0
            sent_logits[:, i] *= (i < length_no_go)
        loss_batch = -torch.sum(sent_logits, dim=1) / length_no_go
        loss = torch.mean(loss_batch)
        # TODO END

        return loss, torch.stack(logits_per_step, dim=1)

    def inference(self, batch_size, device, decode_strategy, temperature, max_probability):
        # First Tokens is <go>
        now_token = torch.tensor([self.dataloader.go_id] * batch_size, dtype=torch.long, device=device)
        flag = torch.tensor([1] * batch_size, dtype=torch.float, device=device)

        now_state = []
        for cell in self.cells:
            now_state.append(cell.init(batch_size, device))

        generated_tokens = []
        for _ in range(50): # max sentecne length

            # TODO START
            embedding = self.embedding(now_token)  # shape: (batch_size, num_embed_units)
            # TODO END

            hidden = embedding
            for j, cell in enumerate(self.cells):
                hidden, now_state[j] = cell(hidden, now_state[j])
            logits = self.linear(hidden) # shape: (batch_size, num_vocabs)

            if decode_strategy == "random":
                prob = (logits / temperature).softmax(dim=-1) # shape: (batch_size, num_vocabs)
                now_token = torch.multinomial(prob, 1)[:, 0] # shape: (batch_size)
            elif decode_strategy == "top-p":
                # TODO START
                # Reference: https://gist.github.com/thomwolf/1a5a29f6962089e871b94cbd09daf317
                # implement top-p samplings
                prob = (logits / temperature).softmax(dim=-1)
                sorted_prob, sorted_index = prob.sort(descending=True)
                cumulative_prob = sorted_prob.cumsum(dim=-1)
                sorted_index_remove = cumulative_prob >= max_probability

                # sorted_index_remove >>= 1
                sorted_index_remove = sorted_index_remove.roll(shifts=1, dims=-1)
                sorted_index_remove[..., 0] = False

                index_remove = torch.zeros(size=prob.shape, dtype=torch.bool)
                index_remove = index_remove.scatter(dim=-1, index=sorted_index, src=sorted_index_remove)
                prob[index_remove] = 0
                prob /= prob.sum(-1, keepdim=True)
                now_token = torch.multinomial(prob, 1)[:, 0]  # shape: (batch_size)
                # TODO END
            else:
                raise NotImplementedError("unknown decode strategy")

            generated_tokens.append(now_token)
            flag = flag * (now_token != self.dataloader.eos_id)

            if flag.sum().tolist() == 0: # all sequences has generated the <eos> token
                break

        return torch.stack(generated_tokens, dim=1).detach().cpu().numpy()
