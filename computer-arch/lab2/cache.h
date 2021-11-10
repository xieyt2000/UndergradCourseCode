#pragma once
#include <iostream>
#include <cstdlib>

using namespace std;

class BaseCache {
	// ����32��Cache Line������ֱ��ӳ��ķ�ʽ��֯����ַ % 32 ����ӳ���Cache Line����
	// u: δ֪��ַ
	int u;

	// tag���洢�������ַ��valid���Ƿ���Ч��time����ʱ
	int line;
	int tag[32];
	bool valid[32];
	int time[32];

	// count�������ܷ��ʴ���
	int count;

	void state_rand();

public:
	BaseCache(int _u, int _line);

	int getCount();

	// flush(x)������ַx��cache�������������У��ӳٸߣ������ӳٵ͡�
	// access(x)����д��ַx��������У��ӳٵͣ������ӳٸߡ�
	// flushu��accessu���Ե�ַu��flush��access������Ҫ����������ֵͬһ���flush��access��
	// flushAny��������cache��������cache�д�����Ч���ݣ��ӳٸߣ������ӳٵ͡�
	// �ӳٸߣ�����1�� �ӳٵͣ�����0

	int flush(int x);

	int access(int x);

	int accessu();

	int flushu();

	int flushAny();
};
