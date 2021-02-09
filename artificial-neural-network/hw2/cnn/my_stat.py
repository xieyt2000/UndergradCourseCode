from torch.utils.tensorboard.writer import SummaryWriter


class Stat:
    status: str  # train, val, test...
    writer: SummaryWriter

    def __init__(self, writer, status):
        self.step = 0
        self.writer = writer
        self.status = status

    def add(self, loss, accuracy):
        self.writer.add_scalar(f'Loss/{self.status}', loss, self.step)
        self.writer.add_scalar(f'Accuracy/{self.status}', accuracy, self.step)
        self.step += 1
