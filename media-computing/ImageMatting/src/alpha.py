import cv2
import numpy as np
from scipy import sparse
from scipy.sparse import linalg

WIN_LEN = 3
WIN_AREA = WIN_LEN ** 2
EPSILON = 1e-5


def get_laplace(image, scribe_mask):
    h, w, c = image.shape
    index_mat = np.arange(h * w).reshape((h, w))
    scribe_mask = cv2.erode(scribe_mask.astype(np.float64), np.ones((WIN_LEN, WIN_LEN)), iterations=1)

    lap_map = {}

    for h_i in range(1, h - 1):
        for w_i in range(1, w - 1):
            if scribe_mask[h_i, w_i]:
                continue

            win_idx = index_mat[h_i - 1:h_i + 2, w_i - 1:w_i + 2].flatten()
            row = np.tile(win_idx, WIN_AREA)
            col = np.repeat(win_idx, WIN_AREA)

            wined_img = image[h_i - 1:h_i + 2, w_i - 1:w_i + 2].reshape(WIN_AREA, c)
            wined_mean = wined_img.mean(axis=0).reshape(c, 1)
            wined_norm = wined_img - wined_mean.T
            wined_mean_sqr = np.dot(wined_mean, wined_mean.T)
            wined_sqr = np.dot(wined_img.T, wined_img) / WIN_AREA
            wined_var = np.linalg.inv(wined_sqr - wined_mean_sqr + EPSILON * np.eye(c))
            wined_lap = (np.dot(np.dot(wined_norm, wined_var), wined_norm.T) + 1) / WIN_AREA
            lap = wined_lap.flatten()
            for r, co, l in zip(row, col, lap):
                key = (r, co)
                lap_map[key] = lap_map.get(key, 0) + l

    laps = np.fromiter(lap_map.values(), np.float64)
    rows = np.fromiter((k[0] for k in lap_map.keys()), np.int64)
    cols = np.fromiter((k[1] for k in lap_map.keys()), np.int64)
    laps = sparse.coo_matrix((laps, (rows, cols)), shape=(h * w, h * w))
    laps_sum = np.array(laps.sum(axis=1)).squeeze()
    diag = sparse.diags(laps_sum)
    laps = diag - laps
    return laps


def get_alpha(image, scribe_weight, scribe_mask):
    h, w, c = image.shape
    laps = get_laplace(image, scribe_mask.astype(np.float64))
    prior_conf = 1000 * scribe_mask.flatten()
    confidence = sparse.diags(prior_conf, shape=(h * w, h * w))
    A = laps + confidence
    b = confidence * scribe_weight.flatten()
    alpha = linalg.spsolve(A, b).reshape((h, w)).clip(0, 1)
    return alpha
