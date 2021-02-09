#include<iostream>

using namespace std;
int DayPerMonth[20] = { 0,31,28,31,30,31,30,31,31,30,31,30,31 };
struct time {
	int year;
	int month;
	int day;
	int hour;
	int minute;
};
struct occupied {
	time start;
	time end;
};
int Minus(time a, time b) {//b-a
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
	time begin = { 2019,1,1,0,0 };
	int N;
	cin >> N;
	time out;
	cin >> out.year >> out.month >> out.day >> out.hour >> out.minute;
	
	for (int i = 1;i <= N;i++) {
		cin >> durs[i].start.year >> durs[i].start.month >> durs[i].start.day >> durs[i].start.hour >> durs[i].start.minute;
		cin >> durs[i].end.year >> durs[i].end.month >> durs[i].end.day >> durs[i].end.hour >> durs[i].end.minute;
	}
	int max = Minus(begin, durs[1].start);
	for (int i = 1;i < N;i++) {
		int tempt = Minus(durs[i].start, durs[i].end);
		if (tempt > max) max = tempt;
	}
	int tempt = Minus(durs[N].end, out);
	if (tempt > max) max = tempt;
	cout << max << endl;
	return 0;
}
