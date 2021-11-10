import sys
import pickle

NUM_INPUT = 40000
ALPHA = 0.15
TN = 30


def readline():
    string = input()
    head, nodes = string.split(':')
    head = int(head)
    if nodes:
        nodes = [int(node) for node in nodes.split(',')]
    else:
        nodes = []
    return head, nodes


def build_graph():
    node2idx, nodes_list = {}, []
    out_degree, link = [], []
    idx = 0

    def check_new_node(node_id, init_out):
        nonlocal idx
        if node_id not in node2idx:
            node2idx[node_id] = idx
            idx += 1
            nodes_list.append(node_id)
            out_degree.append(init_out)
            return True
        return False

    for i in range(NUM_INPUT):
        head, nodes = readline()
        if not check_new_node(head, len(nodes)):
            head_idx = node2idx[head]
            out_degree[head_idx] += len(nodes)
        for node in nodes:
            check_new_node(node, 0)
            link.append((head, node))
    return node2idx, nodes_list, out_degree, link


def page_rank(node2idx, out_degrees, links):
    num_nodes = len(out_degrees)
    pr = [1 / num_nodes] * num_nodes
    for iteration in range(TN):
        new_pr = [ALPHA / num_nodes] * num_nodes
        zero_out_pr = 0
        for idx, out_degree in enumerate(out_degrees):
            if out_degree == 0:
                zero_out_pr += pr[idx]
        for src, dst in links:
            src_idx, dst_idx = node2idx[src], node2idx[dst]
            new_pr[dst_idx] += (1 - ALPHA) * pr[src_idx] / out_degrees[src_idx]
        for i in range(num_nodes):
            pr[i] = new_pr[i] + (1 - ALPHA) * zero_out_pr / num_nodes
    return pr


def output(pr, node_list):
    node_pr = [(node_list[idx], pri) for idx, pri in enumerate(pr)]
    node_pr.sort()
    for pair in node_pr:
        print(f"{pair[0]} {pair[1]:.8f}")


def main():
    node2idx, node_list, out_degree, link = build_graph()
    # with open("graph.pkl", 'wb') as file:
    #     pickle.dump((node2idx, node_list, out_degree, link), file)
    pr = page_rank(node2idx, out_degree, link)
    # with open("pr.pkl", 'wb') as file:
    #     pickle.dump(pr, file)
    output(pr, node_list)


if __name__ == '__main__':
    main()
