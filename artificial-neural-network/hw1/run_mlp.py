import argparse

from torch.utils.tensorboard import SummaryWriter
from datetime import datetime

from network import Network
from utils import LOG_INFO
from layers import Relu, Sigmoid, Linear, Gelu
from loss import EuclideanLoss, SoftmaxCrossEntropyLoss, HingeLoss
from solve_net import train_net, test_net
from load_data import load_mnist_2d


train_data, test_data, train_label, test_label = load_mnist_2d('data')

# losses and activations
LOSSES = {"Euclidean": EuclideanLoss,
          "Softmax": SoftmaxCrossEntropyLoss, "Hinge": HingeLoss}
ACTIVATIONS = {"Relu": Relu, "Sigmoid": Sigmoid, "Gelu": Gelu}


# argument parser
def parser_args():
    parser = argparse.ArgumentParser()
    parser.add_argument("--layers", type=int, choices=[1, 2], default=1)
    parser.add_argument("--loss", choices=LOSSES.keys(), default="Euclidean",)
    parser.add_argument("--activation", choices=ACTIVATIONS.keys(), default="Relu")
    return parser.parse_args()


# Your model defintion here
# You should explore different model architecture
args = parser_args()
model = Network()
activation = ACTIVATIONS[args.activation]
loss = LOSSES[args.loss]("loss")
if args.layers == 1:
    model.add(Linear('fc1', 784, 256, 0.01))
    model.add(activation('act1'))
    model.add(Linear('fc2', 256, 10, 0.01))
elif args.layers == 2:
    model.add(Linear('fc1', 784, 500, 0.01))
    model.add(activation('act1'))
    model.add(Linear('fc2', 500, 256, 0.01))
    model.add(activation('act2'))
    model.add(Linear('fc3', 256, 10, 0.01))
else:
    raise Exception("layers error")


# Training configuration
# You should adjust these hyperparameters
# NOTE: one iteration means model forward-backwards one batch of samples.
#       one epoch means model has gone through all the training samples.
#       'disp_freq' denotes number of iterations in one epoch to display information.

config = {
    'learning_rate': 0.01,
    'weight_decay': 0.0,
    'momentum': 0.9,
    'batch_size': 100,
    'max_epoch': 100,
    'disp_freq': 50,
    'test_epoch': 1
}

start_time = datetime.now()
writer = SummaryWriter(comment=f'-{args.layers}_{args.loss}_{args.activation}')

# step for tensorboard
train_step, test_step = 0, 0

for epoch in range(config['max_epoch']):
    LOG_INFO('Training @ %d epoch...' % (epoch))
    losses, accuracies = train_net(model, loss, config, train_data, train_label, config['batch_size'], config['disp_freq'])
    for loss_val, accuracy in zip(losses, accuracies):
        writer.add_scalar("Loss/train", loss_val, train_step)
        writer.add_scalar("Accuracy/train", accuracy, train_step)
        train_step += 1

    if epoch % config['test_epoch'] == 0:
        LOG_INFO('Testing @ %d epoch...' % (epoch))
        loss_val, accuracy = test_net(model, loss, test_data, test_label, config['batch_size'])
        writer.add_scalar("Loss/test", loss_val, test_step)
        writer.add_scalar("Accuracy/test", accuracy, test_step)
        test_step += 1

end_time = datetime.now()
writer.add_text("time", f"{(end_time-start_time).microseconds} ms")
writer.flush()
writer.close()
