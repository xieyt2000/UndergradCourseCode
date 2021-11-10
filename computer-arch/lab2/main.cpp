#include <iostream>
#include <cmath>
#include "cache.h"
#include "solver.h"

using namespace std;

/*
	��ַ��Χ��[0, 1600)������[0, 800)��δ֪��ַu���ܵķ�Χ��
*/

int main() {
    bool right = true;
    int count = 0;
    double correct = 0;

    // ��u��ÿ��������в���
    for (int i = 0; i < 800; ++i) {

        // ����δ֪��ַ������ʼ��cache��
        int u = i;
        BaseCache *bc = new BaseCache(u, 32);

        // ���ù������̣�ͳ�Ʒ��ʴ���
        Solver user;
        int x = user.getAns(bc, 800, 32);
        count += bc->getCount();

        // �����ȡ��ֵ������Ϊ����ʧ��
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
