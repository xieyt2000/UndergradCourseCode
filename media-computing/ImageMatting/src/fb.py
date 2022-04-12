import numpy as np
from scipy import sparse
from scipy.sparse import linalg

ALPHA_BOT_THRESH = 0.02
ALPHA_TOP_THRESH = 1 - ALPHA_BOT_THRESH


def mask_grad(mask):
    hor_left = np.ravel_multi_index(np.nonzero(mask[:, :-1] | mask[:, 1:]), mask.shape)
    hor_right = hor_left + 1
    ver_top = np.ravel_multi_index(np.nonzero(mask[:-1, :] | mask[1:, :]), mask.shape)
    ver_bot = ver_top + mask.shape[1]
    dia_main1 = np.ravel_multi_index(np.nonzero(mask[:-1, :-1] | mask[1:, 1:]), mask.shape)
    dia_main2 = dia_main1 + mask.shape[1] + 1
    dia_ant1 = np.ravel_multi_index(np.nonzero(mask[:-1, 1:] | mask[1:, :-1]), mask.shape) + 1
    dia_ant2 = dia_ant1 + mask.shape[1] - 1

    idx1 = np.concatenate([hor_left, ver_top, dia_main1, dia_ant1])
    idx2 = np.concatenate([hor_right, ver_bot, dia_main2, dia_ant2])
    indices = np.stack((idx1, idx2), axis=-1)

    return sparse.coo_matrix((np.tile([-1, 1], len(indices)),
                              (np.arange(indices.size) // 2, indices.flatten())),
                             shape=(len(indices), mask.size))


def get_conditions(alpha_1d):
    return (alpha_1d < ALPHA_BOT_THRESH) * 100. + 0.03 * (1 - alpha_1d) * (
            alpha_1d < 0.3) + 0.01 * (alpha_1d > 1.0 - 0.02)


def get_fb(image, alpha):
    alpha_1d = alpha.flatten()
    h, w, c = image.shape
    image_arr = image.reshape(h * w, c)

    cond_b = get_conditions(alpha_1d)
    cond_b_sp = sparse.diags(cond_b)
    img_b = (cond_b * (alpha_1d < ALPHA_TOP_THRESH)).reshape((-1, 1)) * image_arr
    cond_f = get_conditions(1 - alpha_1d)
    cond_f_sp = sparse.diags(cond_f)
    img_f = (cond_f * (alpha_1d > ALPHA_BOT_THRESH)).reshape((-1, 1)) * image_arr
    comp_cond = sparse.hstack((sparse.diags(alpha_1d), sparse.diags(1 - alpha_1d)))
    none_zero_cond = sparse.vstack((
        comp_cond,
        sparse.hstack((cond_f_sp, sparse.coo_matrix(cond_f_sp.shape))),
        sparse.hstack((sparse.coo_matrix(cond_b_sp.shape), cond_b_sp))
    ))
    img_con = np.concatenate((image_arr, img_f, img_b))
    b = none_zero_cond.T * img_con

    alpha_mask = np.logical_and(alpha > ALPHA_BOT_THRESH, alpha < ALPHA_TOP_THRESH)
    grad = mask_grad(alpha_mask)
    grad_weight = np.sqrt(np.abs(grad * alpha_1d))
    grad_non_neg = grad.maximum(0)
    grad_f_weight = grad_weight + 0.003 * grad_non_neg * (1 - alpha_1d)
    grad_b_weight = grad_weight + 0.003 * grad_non_neg * alpha_1d

    smooth_cond = sparse.vstack((
        sparse.hstack((
            sparse.diags(grad_f_weight) * grad, sparse.coo_matrix(grad.shape)
        )),
        sparse.hstack((
            sparse.coo_matrix(grad.shape), sparse.diags(grad_b_weight) * grad
        ))
    ))
    cond = sparse.vstack((none_zero_cond, smooth_cond))
    A = cond.T * cond

    fb = linalg.spsolve(A, b)
    f = fb[:h * w, :].reshape(image.shape)
    b = fb[h * w:].reshape(image.shape)
    return f, b
