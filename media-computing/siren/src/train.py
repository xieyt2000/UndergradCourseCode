import os
import jittor
import model
import numpy as np
from tqdm import tqdm


def train(network: model.Siren, optim: jittor.optim.Optimizer, loss_fn, epochs, coords, gt, save_path):
    network.train()
    min_loss = np.inf
    for epoch in tqdm(range(epochs)):
        output = network(coords)
        loss = loss_fn(output, gt)
        optim.step(loss)
        loss = loss.item()
        if loss < min_loss:
            min_loss = loss
            jittor.save(network.state_dict(), save_path)
        if epoch % 10 == 0:
            tqdm.write(f"epoch: {epoch}, loss: {loss}, min_loss: {min_loss}")
