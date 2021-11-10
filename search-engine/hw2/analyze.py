import sys
import pickle
import matplotlib.pyplot as plt
import numpy as np

FROM_PKL = True


def redirect():
    sys.stdout = open("output.txt", 'w')
    sys.stdin = open("data/wiki.graph")


def plot_out(out_degree: list):
    print("plot out degrees")
    plt.hist(out_degree, 100)
    plt.show()


def plot_in(node2idx, link):
    print("print in degrees")
    in_degree = [0] * len(node2idx)
    for lk in link:
        in_degree[node2idx[lk[1]]] += 1
    with open("in-degree.pkl", 'wb') as file:
        pickle.dump(in_degree, file)
    plt.hist(in_degree, 100)
    plt.show()


def plot_pr(pr):
    print("plot pr")
    plt.hist(pr, 100)
    plt.show()


def plot_in_pr(pr):
    with open("in-degree.pkl", 'rb') as file:
        in_degree = pickle.load(file)
    print("plot rel of pr and in")
    plt.scatter(in_degree, pr)
    plt.show()


def init_plot():
    plt.yscale('log')


def word(node_list, pr):
    print("print words")
    pr = np.array(pr)
    sorted_index = pr.argsort()
    result_index = np.concatenate([sorted_index[:2], sorted_index[-3:]])
    for idx in result_index:
        print(node_list[idx], pr[idx])


def main():
    if FROM_PKL:
        with open("graph.pkl", 'rb') as file:
            node2idx, node_list, out_degree, link = pickle.load(file)
        with open("pr.pkl", 'rb') as file:
            pr = pickle.load(file)
    init_plot()
    with open("in-degree.pkl", 'rb') as file:
        in_degree = pickle.load(file)
    print(len(in_degree))
    print(sorted(in_degree)[-5:])
    print([node_list[i] for i in np.array(in_degree).argsort()[-5:]])
    # plot_out(out_degree)
    # plot_in(node2idx, link)
    # plot_pr(pr)
    # plot_in_pr(pr)
    # word(node_list, pr)


if __name__ == '__main__':
    main()
