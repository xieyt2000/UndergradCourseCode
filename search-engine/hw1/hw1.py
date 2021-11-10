import csv


def cal_stat(site, name, labels):
    labels = list(map(int, labels))
    ap = sum([sum(labels[:i]) / i for i in range(1, 11)]) / len(labels)
    p10 = sum(labels) / len(labels)
    s10 = int(1 in labels)
    if s10:
        rr = 1 / (labels.index(1) + 1)
    else:
        rr = 0
    return [site, name, labels, ap, p10, rr, s10]


def main():
    with open("data.txt") as file:
        lines = file.read().splitlines()
    res = []
    for i in range(0, len(lines), 3):
        name = lines[i]
        res.append(cal_stat("baidu", name, lines[i + 1]))
        res.append(cal_stat("bing", name, lines[i + 2]))
    with open("result.csv", "w", encoding='utf_8_sig') as file:
        writer = csv.writer(file)
        writer.writerow(["site", 'name', 'labels', 'AP', "P@10", "RR", "success@10"])
        writer.writerows(res)


def bonus():
    res = [cal_stat('baidu', 'paper', [1, 0, 0, 1, 1, 0, 0, 0, 0, 0]),
           cal_stat('bing', 'paper', [1, 1, 1, 1, 1, 1, 1, 0, 0, 0])]
    with open("bonus_result.csv", "w", encoding='utf_8_sig') as file:
        writer = csv.writer(file)
        writer.writerow(["site", 'name', 'labels', 'AP', "P@10", "RR", "success@10"])
        writer.writerows(res)


# main()
bonus()
