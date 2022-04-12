import argparse
import os

import cv2
import numpy as np

from alpha import get_alpha
from fb import get_fb


def parse():
    parser = argparse.ArgumentParser()
    parser.add_argument('--image_path', default='../data/input/teddy_ear.bmp')
    parser.add_argument('--scribe_path', default='../data/input/teddy_ear_m.bmp')
    parser.add_argument('--output_dir', default='../data/output/teddy_ear')
    return parser.parse_args()


def get_scribe(ori_img, scr_img, scr_gray):
    scribe = (ori_img - scr_img).sum(axis=-1)
    scribe_mask = (scribe != 0)
    scribe_weight = scribe_mask * scr_gray
    return scribe_mask, scribe_weight


def output_format(img_arr):
    return (img_arr * 255).astype(np.uint8)


def main():
    args = parse()
    output_dir = args.output_dir
    image_path, scribe_path = args.image_path, args.scribe_path
    if not os.path.exists(output_dir):
        os.makedirs(output_dir)

    image = cv2.imread(image_path).astype(np.float64) / 255
    scribed_img = cv2.imread(scribe_path).astype(np.float64) / 255
    scribed_gray = cv2.imread(scribe_path, cv2.IMREAD_GRAYSCALE).astype(np.float64) / 255
    scribe_mask, scribe_weight = get_scribe(image, scribed_img, scribed_gray)
    print('solve alpha')
    alpha = get_alpha(image, scribe_weight, scribe_mask.astype(np.float64))
    cv2.imwrite(os.path.join(output_dir, "alpha.jpg"), output_format(alpha))
    print('solve fb')
    f, b = get_fb(image, alpha)
    for c in range(image.shape[2]):
        f[:, :, c] *= alpha
        b[:, :, c] *= 1 - alpha
    f = f.clip(0, 1)
    b = b.clip(0, 1)
    cv2.imwrite(os.path.join(output_dir, "foreground.png"), output_format(f))
    cv2.imwrite(os.path.join(output_dir, "background.png"), output_format(b))


if __name__ == '__main__':
    main()
