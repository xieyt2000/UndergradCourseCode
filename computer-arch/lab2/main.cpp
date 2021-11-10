#include <iostream>
#include <cmath>
#include "cache.h"
#include "solver.h"

using namespace std;

/*
	地址范围：[0, 1600)。其中[0, 800)是未知地址u可能的范围。
*/

int main() {
    bool right = true;
    int count = 0;
    double correct = 0;

    // 对u的每种情况进行测试
    for (int i = 0; i < 800; ++i) {

        // 设置未知地址，并初始化cache。
        int u = i;
        BaseCache *bc = new BaseCache(u, 32);

        // 调用攻击过程，统计访问次数
        Solver user;
        int x = user.getAns(bc, 800, 32);
        count += bc->getCount();

        // 如果获取的值错误，视为攻击失败
        if (x != u) {
            right = false;
        } else {
            correct++;
        }
        delete bc;
    }

    if (right) {
        cout << "right, operation count :" << count << endl;
        if (count <= 100000) cout << "score : 7" << endl;
        else if (count <= 150000) cout << "score : 6.5" << endl;
        else if (count <= 300000) cout << "score : 6" << endl;
        else if (count <= 500000) cout << "score : 5.5" << endl;
        else if (count <= 750000) cout << "score : 5" << endl;
        else if (count <= 1000000) cout << "score : 4" << endl;
        else cout << "score : 3" << endl;
    } else {
        cout << "wrong" << endl;
        cout << "score : " << round((correct * 6 / 800)) / 2 << endl;
    }

    return 0;
}
