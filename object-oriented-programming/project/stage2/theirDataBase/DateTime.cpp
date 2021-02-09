#include "DateTime.h"
#include<iostream>
#include<exception>
using std::cout;
using std::endl;
using std::stoi;
using std::to_string;
int getDaysbyMonthandYear(int m, int y)
{
	int DaysPerMonth[20] = { 0,31,-1,31,30,31,30,31,31,30,31,30,31 }; //if ==-1 then decided by year
	if (DaysPerMonth[m] != -1) return DaysPerMonth[m];
	else
	{
		if (y % 4 == 0)
		{
			if (y % 100 == 0)
			{
				if (y % 400 == 0) return 29;
				else return 28;
			}
			else return 29;
		}
		else return 28;
	}
}


//constructor
Date::Date(string date) :datestr(date)
{
	try
	{
		year = stoi(date.substr(0, 4));
		month = stoi(date.substr(5, 2));
		day = stoi(date.substr(8, 2));
		if (year < 0 || month < 1 || month>12 || day<1 || day>getDaysbyMonthandYear(month, year))
		{
			throw "...";
		}
	}
	catch (...)
	{
		datestr = "2000-01-01";
		cout << "Input falied. Use default as 2000-01-01" << endl;
	}
}
Time::Time(string time) :timestr(time)
{
	try
	{
		int pos = time.find(':');
		hour = stoi(time.substr(0, pos));
		pos++;
		minute = stoi(time.substr(pos, 2));
		pos += 3;
		second = stoi(time.substr(pos, 2));
		if (hour < 0 || minute < 0 || minute>60 || second < 0 || second>60)
		{
			throw "TLE!";
		}
	}
	catch (const char * str)
	{
		timestr = "00:00:00";
		cout << str;
		cout << "Input falied. Use default as 00:00:00" << endl;
	}
	catch (...)
	{
		timestr = "00:00:00";
		cout << "Input falied. Use default as 00:00:00" << endl;
	}
}
DateTime::DateTime(string datePart, string timePart) :date(Date(datePart)), time(Time(timePart))
{
	datestr = date.datestr;
	timestr = time.timestr;
}


//cmp operator
bool Date::operator==(const Date & cmp)
{
	return ((day == cmp.day)
		&& (month == cmp.month)
		&& (year == cmp.year)
		);
}
bool Date::operator<(const Date & cmp)
{
	if (year < cmp.year) return true;
	else
	{
		if (year == cmp.year)
		{
			if (month < cmp.month) return true;
			else
			{
				if (month == cmp.month)
				{
					if (day < cmp.day) return true;
					else return false;
				}
				else return false;
			}
		}
		else return false;
	}
}
bool Date::operator>(const Date & cmp)
{
	if (year > cmp.year) return true;
	else
	{
		if (year == cmp.year)
		{
			if (month > cmp.month) return true;
			else
			{
				if (month == cmp.month)
				{
					if (day > cmp.day) return true;
					else return false;
				}
				else return false;
			}
		}
		else return false;
	}
}

bool Time::operator==(const Time & cmp)
{
	return ((second == cmp.second)
		&& (minute == cmp.minute)
		&& (hour == cmp.hour)
		);
}
bool Time::operator<(const Time & cmp)
{
	if (hour < cmp.hour) return true;
	else
	{
		if (hour == cmp.hour)
		{
			if (minute < cmp.minute) return true;
			else
			{
				if (minute == cmp.minute)
				{
					if (second < cmp.second) return true;
					else return false;
				}
				else return false;
			}
		}
		else return false;
	}
}
bool Time::operator>(const Time & cmp)
{
	if (hour > cmp.hour) return true;
	else
	{
		if (hour == cmp.hour)
		{
			if (minute > cmp.minute) return true;
			else
			{
				if (minute == cmp.minute)
				{
					if (second > cmp.second) return true;
					else return false;
				}
				else return false;
			}
		}
		else return false;
	}
}

bool DateTime::operator==(const DateTime & cmp)
{
	return (date == cmp.date && time == cmp.time);
}
bool DateTime::operator<(const DateTime & cmp)
{
	if (date < cmp.date) return true;
	else
	{
		if (date == cmp.date)
		{
			return (time < cmp.time);
		}
		else return false;
	}
}
bool DateTime::operator>(const DateTime & cmp)
{
	if (date > cmp.date) return true;
	else
	{
		if (date == cmp.date)
		{
			return (time > cmp.time);
		}
		else return false;
	}
}


//string generator
void Date::genDatestr()
{
	datestr.clear();
	string y = to_string(year);
	while (y.size() < 4)
	{
		y.insert(0, "0");
	}
	datestr = y;
	datestr += '-';
	string m = to_string(month);
	if (month < 10) m.insert(0, "0");
	datestr += m;
	datestr += '-';
	string d = to_string(day);
	if (day < 10) d.insert(0, "0");
	datestr += d;
}

void Time::genTimestr()
{
	timestr.clear();
	string h = to_string(hour);
	timestr = h;
	timestr += ':';
	string m = to_string(minute);
	if (minute < 10) m.insert(0, "0");
	timestr += m;
	timestr += ':';
	string s = to_string(second);
	if (second < 10) s.insert(0, "0");
	timestr += s;
}

//add function
void Date::addDate(int adDays)
{
	while (true)
	{
		if (adDays <= getDaysbyMonthandYear(month, year) - day)
		{
			day += adDays;
			break;
		}
		else
		{
			adDays -= getDaysbyMonthandYear(month, year) - day + 1;
			day = 1;
			month++;
			if (month > 12)
			{
				year++;
				month = 1;
			}
		}
	}
	genDatestr();
}

void Time::addTime(const Time & adTime)
{
	second += adTime.second;
	int tmpMin = second / 60;
	second = second % 60;
	minute += tmpMin + adTime.minute;
	int tmpHor = minute / 60;
	minute = minute % 60;
	hour += tmpHor + adTime.hour;
	genTimestr();
}

void DateTime::addDate(int adDays)
{
	date.addDate(adDays);
	datestr = date.datestr;
}
void DateTime::addTime(const Time & adTime)
{
	time.addTime(adTime);
	if (time.hour >= 24)
	{
		date.addDate(time.hour / 24);
		time.hour = time.hour % 24;
		time.genTimestr();
	}
	datestr = date.datestr;
	timestr = time.timestr;
}


//print function
void Date::printDate()
{
	cout << datestr;
}
void Time::printTime()
{
	cout << timestr;
}
void DateTime::printDateTime()
{
	date.printDate(); cout << '|'; time.printTime();
}
ostream & operator<<(ostream & out, const Date & src)
{
	out << src.datestr;
	return out;
}
ostream & operator<<(ostream & out, const Time & src)
{
	out << src.timestr;
	return out;
}
ostream & operator<<(ostream & out, const DateTime & src)
{
	out << src.datestr << '|' << src.timestr;
	return out;
}