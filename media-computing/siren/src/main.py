import argparse
import os

import dataio
import model
import jittor

import compute
from train import train
from keys import *


def parse():
    parser = argparse.ArgumentParser()
    parser.add_argument('--task', default='fit')
    parser.add_argument('--input_path', default='../data/camera.jpg')
    parser.add_argument('--output_dir', default='../data/fit')
    parser.add_argument('--channels', type=int, default=1)
    parser.add_argument('--sidelength', type=int, default=256)
    parser.add_argument('--epochs', type=int, default=1000)
    parser.add_argument('--lr', type=float, default=1e-4)
    parser.add_argument('--ot_image_path', default='../data/bear.jpg')
    parser.add_argument('--points', type=int, default=5000)
    return parser.parse_args()


def main():
    jittor.flags.use_cuda = 1
    args = parse()
    task = args.task
    input_path, output_dir = args.input_path, args.output_dir
    sidelength, channels = args.sidelength, args.channels
    lr, epochs = args.lr, args.epochs
    if not os.path.exists(output_dir):
        os.mkdir(output_dir)

    network = model.Siren(channels)
    optim = jittor.optim.Adam(network.parameters(), lr=lr)
    network_path = os.path.join(output_dir, "network.pkl")
    coords, image_arr = dataio.get_fit_data(input_path, sidelength, channels)
    if task == 'fit':
        gt = image_arr.clone()
        loss_fn = compute.mse
    elif task == 'poisson':
        gt = dataio.get_poisson_data(input_path, sidelength, channels)
        loss_fn = compute.laplace_mse
    elif task == 'composition':
        gt = dataio.get_compos_data(input_path, args.ot_image_path, sidelength, channels)
        loss_fn = compute.two_grad_mse
    elif task == 'inpaint':
        data = dataio.get_inpaint_data(input_path, sidelength, channels, args.points)
        coords = data[SELECTED_COORD_KEY]
        loss_fn = compute.mse
        gt = data[SELECT_IMG_KEY]
        dataio.output_masked_image(output_dir, data[SELECT_IMG_KEY], data[IMAGE_KEY], data[MASK_KEY], sidelength,
                                   channels)
    else:
        raise ValueError()
    print("Training")
    train(network, optim, loss_fn, epochs, coords, gt, network_path)
    network.load_state_dict(jittor.load(network_path))
    best_output = network(coords)
    if task == 'inpaint':
        best_output = network(data[COORD_KEY])
    dataio.output_result(output_dir, best_output, coords, sidelength, channels, image_arr)


if __name__ == '__main__':
    main()
