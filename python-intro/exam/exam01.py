# python3
import sys

card_val_cmp = ['3', '4', '5', '6', '7', '8', '9', '10', 'J', 'Q', 'K', 'A', '2']
car_color_cmp = ['S', 'H', 'C', 'D']


class Card:
    def __init__(self, color, value):
        self.color = color
        self.value = value

    def __lt__(self, other):
        if card_val_cmp.index(self.value) < card_val_cmp.index(other.value):
            return True
        elif card_val_cmp.index(self.value) > card_val_cmp.index(other.value):
            return False
        elif car_color_cmp.index(self.color) < car_color_cmp.index(other.color):
            return True
        else:
            return False


def card_cpm(self, other):
    if card_val_cmp.index(self.value) < card_val_cmp.index(other.value):
        return 1
    elif car_color_cmp.index(self.color) < card_val_cmp.index(other.color):
        return 1
    else:
        return -1


def output(arr_card):
    out = []
    for i in arr_card:
        out.append(i.color + i.value)
    n = len(out)
    for i in out[:n - 1]:
        print(i, end=',')
    print(out[n - 1])


def sort(ori, out_flag=True):
    n = len(ori)
    for i in range(n - 1):
        for j in ori[i + 1:]:
            if ori[i].value == j.value and ori[i].color == j.color:
                print('Error4')
                sys.exit(0)
    n = len(ori)
    arr = ori
    for i in range(n):
        for j in range(0, n - i - 1):

            if arr[j + 1] < arr[j]:
                arr[j], arr[j + 1] = arr[j + 1], arr[j]
    if out_flag:
        output(arr)
    return arr


def cmp(ori_card, cmp_card):
    for i in ori_card:
        for j in cmp_card:
            if i.value == j.value and i.color == j.color:
                print('Error4')
                sys.exit(0)
    ori_type = check(ori_card)
    cmp_type = check(cmp_card)
    if ori_type == 0 or cmp_type == 0:
        print('=')
        return
    if ori_type != cmp_type:
        if ori_type == 4:
            print('>')
            return
        elif cmp_type == 4:
            print('<')
            return
        else:
            print('=')
            return
    else:
        if ori_type == 1:
            if ori_card[0].value < cmp_card[0].value:
                print('<')
                return
            elif ori_card[0].value > cmp_card[0].value:
                print('>')
                return
            else:
                print('=')
                return
        if ori_type == 2:
            if len(ori_card) != len(cmp_card):
                print('=')
                return
            else:
                ori_card = sort(ori_card)
                cmp_card = sort(cmp_card)
                if ori_card[0].value < cmp_card[0].value:
                    print('<')
                    return
                elif ori_card[0].value > cmp_card[0].value:
                    print('>')
                    return
                else:
                    print('=')
                    return
        if ori_type == 4:
            if ori_card[0].value < cmp_card[0].value:
                print('<')
                return
            elif ori_card[0].value > cmp_card[0].value:
                print('>')
                return
            else:
                print('=')
                return
        if ori_type == 3:
            counter = {}
            for i in ori_card:
                if i.value in counter.keys():
                    ori_card[0] = i.value
                else:
                    counter[i.value] = 1
            counter = {}
            for i in cmp_card:
                if i.value in counter.keys():
                    cmp_card[0] = i.value
                else:
                    counter[i.value] = 1
            if ori_card[0].value < cmp_card[0].value:
                print('<')
                return
            elif ori_card[0].value > cmp_card[0].value:
                print('>')
                return
            else:
                print('=')
                return


def check(ori):
    n = len(ori)
    for i in range(n - 1):
        for j in ori[i + 1:]:
            if ori[i].value == j.value and ori[i].color == j.color:
                print('Error4')
                sys.exit(0)
    # single
    if len(ori) == 1:
        return 1

    if len(ori) == 4:
        # boom
        isboom = True
        for i in ori[1:]:
            if i.value != ori[0].value:
                isboom = False
        if isboom:
            return 4
        # 3-1
        counter = {}
        for i in ori:
            if i.value in counter.keys():
                counter[i.value] += 1
            else:
                counter[i.value] = 1
        if len(counter) == 2:
            for val in counter.values():
                if val == 1:
                    return 3
    # sequence
    ori = sort(ori, out_flag=False)
    n = len(ori)
    is_sequence = True
    for i in ori:
        if i.value == '2':
            return 0
    for i in range(n - 1):
        if card_val_cmp.index(ori[i].value) != card_val_cmp.index(ori[i + 1].value) - 1:
            is_sequence = False
    if is_sequence:
        return 1
    # none
    return 0


# def valid_card(ori):
def main():
    try:
        type = sys.argv[1]
    except:
        print('Error1')
        return
    if type != '-sort' and type != '-check' and type != '-cmp':
        print('Error1')
        return
    try:
        ori_card = []
        cards_str = sys.argv[2].split(',')
    except:
        print('Error2')
        return
    for i in cards_str:
        if i[0] not in car_color_cmp or i[1:] not in card_val_cmp:
            print('Error3')
            return
        ori_card.append(Card(i[0], i[1:]))
    if type == '-sort':
        if len(sys.argv) > 3:
            print('Error2')
            return
        sort(ori_card)
    elif type == '-check':
        if len(sys.argv) > 3:
            print('Error2')
            return
        out = check(ori_card)
        print(out)
    elif type == '-cmp':
        if len(sys.argv) > 4:
            print('Error2')
            return
        try:
            cmp_str = sys.argv[3].split(',')
            cmp_card = []
            for i in cmp_str:
                if i[0] not in car_color_cmp or i[1:] not in card_val_cmp:
                    print('Error3')
                    return
                cmp_card.append(Card(i[0], i[1:]))
        except:
            print('Error2')
            return
        cmp(ori_card, cmp_card)
    else:
        print("Error1")
        return


main()
