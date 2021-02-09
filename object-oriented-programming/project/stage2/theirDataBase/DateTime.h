#pragma once
#include<string>
#include<iostream>
using std::ostream;
using std::string;
class Date
{
private:
	int year = 2000;
	int month = 1;
	int day = 1;
	string datestr = "2000-01-01";//written form
	friend class DateTime;
	friend ostream& operator<<(ostream& out, const Date& src);
public:
	bool operator ==(const Date& cmp);
	bool operator <(const Date& cmp);
	bool operator >(const Date& cmp);
	Date(string date);//year-month-day
	void addDate(int adDays);
	void genDatestr();
	void printDate();
};
class Time
{
private:
	int hour = 0;
	int minute = 0;
	int second = 0;
	string timestr = "00:00:00";//written form
	friend class DateTime;
	friend ostream& operator<<(ostream& out, const Time& src);
public:
	bool operator ==(const Time& cmp);
	bool operator <(const Time& cmp);
	bool operator >(const Time& cmp);
	Time(string time);//hour:minute:second
	void addTime(const Time& adTime);
	void genTimestr();
	void printTime();
};
class DateTime
{
private:
	Date date;
	Time time;
	friend ostream& operator<<(ostream& out, const DateTime& src);
	string datestr;
	string timestr;
public:
	bool operator ==(const DateTime& cmp);
	bool operator <(const DateTime& cmp);
	bool operator >(const DateTime& cmp);
	DateTime(string datePart, string timePart);//yyyy-mm-dd hh:mm:ss
	void addDate(int adDays);
	void addTime(const Time& adTime);
	void printDateTime();
	//string getDatestr() { return date.datestr; }
	//string getTimestr() { return time.timestr; }
};