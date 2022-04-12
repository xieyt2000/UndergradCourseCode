import os

import jittor
from PIL import Image
import numpy as np
from scipy import ndimage
from keys import *


def read_image(input_path, *, sidelength=256, channels=1):
    image = Image.open(input_path).resize((sidelength, sidelength))
    if channels == 1:
        image = image.convert('L')
    elif channels == 3:
        image = image.convert('RGB')
    else:
        raise ValueError()
    image_arr = jittor.array(np.array(image))
    if channels == 1:
        image_arr = image_arr.unsqueeze(-1)
    image_arr /= 255
    image_arr = 2 * image_arr - 1
    return image_arr


def get_mgrid(sidelength=256, dimension=2):
    arrs = [jittor.linspace(-1, 1, sidelength) for _ in range(dimension)]
    mgrid = jittor.stack(jittor.meshgrid(*arrs), dim=-1)
    mgrid = mgrid.view(-1, dimension)
    return mgrid


def get_fit_data(input_path, sidelength, channels):
    image_arr = read_image(input_path, sidelength=sidelength, channels=channels)
    mgrid = get_mgrid(sidelength)
    image_arr = image_arr.reshape(-1, channels)
    return mgrid, image_arr


def get_poisson_data(input_path, sidelength, channels):
    coords, image_arr = get_fit_data(input_path, sidelength, channels)
    laplace = []
    for _ in range(channels):
        laplace.append(ndimage.laplace(image_arr.numpy() * 1e4)[..., None])
    laplace = np.concatenate(laplace, axis=-1)
    laplace = laplace.reshape(-1, channels)
    return {
        LAP_KEY: jittor.array(laplace),
        IMAGE_KEY: image_arr
    }


def get_grad(image, channels):
    img = image.numpy().astype(np.float64)
    grad = []
    for i in range(channels):
        xgrad = ndimage.sobel(img[:, :, i], axis=0)[..., None]
        ygrad = ndimage.sobel(img[:, :, i], axis=1)[..., None]
        grad += [xgrad, ygrad]
    grad = np.concatenate(grad, axis=-1)
    grad = grad.reshape(-1, 2 * channels)
    return jittor.array(grad)


def get_compos_data(image_path, ot_image_path, sidelength, channels):
    coord, img = get_fit_data(image_path, sidelength, channels)
    _, ot_img = get_fit_data(ot_image_path, sidelength, channels)
    grad, ot_grad = get_grad(read_image(image_path, sidelength=sidelength, channels=channels), channels), get_grad(
        read_image(ot_image_path, sidelength=sidelength, channels=channels), channels)
    grad = 0.5 * grad + 0.5 * ot_grad
    return {
        GRAD_KEY: grad,
        IMAGE_KEY: img,
        OTHER_IMAGE_KEY: ot_img
    }


def get_inpaint_data(image_path, sidelength, channels, points):
    coord, img_arr = get_fit_data(image_path, sidelength, channels)
    mask = np.random.choice(np.arange(len(coord)), points, replace=False)
    selected_coord = coord[mask]
    selected_img = img_arr[mask]
    return {
        SELECTED_COORD_KEY: selected_coord,
        COORD_KEY: coord,
        IMAGE_KEY: img_arr,
        SELECT_IMG_KEY: selected_img,
        MASK_KEY: mask
    }


def form_image(img_arr, sidelength=256, channels=1, ref_img=None):
    res_img = img_arr.reshape(sidelength, sidelength, channels).detach()
    if ref_img is not None:  # normalize to ref
        res_img = (res_img - res_img.min()) / (res_img.max() - res_img.min()) * (
                ref_img.max() - ref_img.min()) + ref_img.min()
    # revert normalize
    res_img = res_img * 0.5 + 0.5
    res_img = (res_img.safe_clip(0, 1) * 255).numpy().astype(np.uint8)
    if channels == 1:
        res_img = res_img.squeeze()
        return Image.fromarray(res_img, 'L')
    elif channels == 3:
        return Image.fromarray(res_img, 'RGB')
    else:
        raise ValueError()


def output_result(output_dir, output, coords, sidelength=256, channels=1, ref_image=None):
    image = form_image(output[OUT_KEY], sidelength, channels, ref_image)
    image.save(os.path.join(output_dir, "output.jpg"))


def output_masked_image(output_dir, selected_img, ori_img, mask, sidelength, channels):
    masked_image = jittor.ones_like(ori_img)
    masked_image[mask] = selected_img
    masked_image = form_image(masked_image, sidelength, channels)
    masked_image.save(os.path.join(output_dir, "masked.jpg"))
