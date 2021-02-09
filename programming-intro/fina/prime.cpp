#include<iostream>
#include<cstring>
#include<cmath>
#include<algorithm>
using namespace std;
int DayPerMonth[20] = { 0,31,28,31,30,31,30,31,31,30,31,30,31 };
struct Time {
	int year;
	int month;
	int day;
	int hour;
	int minute;
};
struct occupied {
	Time start;
	Time end;
};
int Minus(Time a, Time b) {//b-a
	int Day = b.day - a.day;
	for (int i = a.month;i < b.month;i++) {
		Day += DayPerMonth[i];
	}
	int Hour = b.hour - a.hour;
	Hour += 24 * Day;
	int min = b.minute - a.minute;
	min += Hour * 60;
	return min;
}
occupied durs[20000];
int main() {
	Time begin = { 2019,1,1,0,0 };
	int N;
	cin >> N;
	Time out;
	cin >> out.year >> out.month >> out.day >> out.hour >> out.minute;

	for (int i = 1;i <= N;i++) {
		cin >> durs[i].start.year >> durs[i].start.month >> durs[i].start.day >> durs[i].start.hour >> durs[i].start.minute;
		cin >> durs[i].end.year >> durs[i].end.month >> durs[i].end.day >> durs[i].end.hour >> durs[i].end.minute;
	}
	durs[0].end = begin;
	durs[N + 1].start = out;
	int max = 0;
	for (int i = 0;i < N+1;i++) {
		int tempt = Minus(durs[i].end, durs[i+1].start);
		if (tempt > max) max = tempt;
	}
	cout << max << endl;
	return 0;
}
