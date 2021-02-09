#include "Value.h"
#include <string>
using std::string;

ValueBase::~ValueBase() {}

long double stolld(string str)
{
	long double ret = 0;
	int exp = 0;
	for (int i = str.length() - 1; i >= 0; i--)
	{
		if (str[i] == '.') exp = i;
		else ret = ret * 0.1 + (str[i] - '0');
	}
	exp--;
	while (exp--) ret *= 10;
	return ret;
}

ValueBase * stringToValue(string tmp)
{
	ValueBase * vb;

	if (tmp == "null" || tmp == "NULL")
		return nullptr;

	if (tmp[0] == '\'')
	{
		vb = new Value<string>(tmp.substr(1, tmp.find_last_of('\'') - 1));
	}
	else if (tmp[0] == '\"')
	{
		vb = new Value<string>(tmp.substr(1, tmp.find_last_of('\"') - 1));
	}
	else if (tmp.find('.') != string::npos)
	{
		vb = new Value<double>(stolld(tmp));
		//vb = new Value<double>(0);
	}
	else if (tmp.find('|') != string::npos)
	{ //yyyy-mm-dd|hh:mm:ss
		string date = tmp.substr(0, 10);
		string time = tmp.substr(11, 8);
		DateTime datetime(date, time);
		vb = new Value<DateTime>(datetime);
	}
	else if (tmp.find(':') != string::npos)
	{
		Time time(tmp);
		vb = new Value<Time>(time);
	}
	else if (tmp.find('-') != string::npos)
	{
		Date date(tmp);
		vb = new Value<Date>(date);
	}
	else
	{
		int ttt = atoi(tmp.c_str());
		vb = new Value<int>(ttt);
	}
	return vb;
}

template<class T> Value<T> * convert(ValueBase * b)
{
	auto i = dynamic_cast<Value<T> *> (b);
	if (b == nullptr) return nullptr;
	return i->copy();
}
template<> Value<double> * convert(ValueBase * b)
{
	auto d = dynamic_cast<Value<double> *>(b);
	if (d != nullptr) return d->copy();
	auto i = dynamic_cast<Value<int> *>(b);
	if (i != nullptr) return new Value<double>(i->operator int());
	return nullptr;
}
template<> Value<int> * convert(ValueBase * b)
{
	auto d = dynamic_cast<Value<int> *>(b);
	if (d != nullptr) return d->copy();
	auto i = dynamic_cast<Value<double> *>(b);
	if (i != nullptr) return new Value<int>(i->operator double());
	return nullptr;
}
template Value<string> * convert<string>(ValueBase * b);
//
template<> Value<Date> * convert(ValueBase * b)
{
	auto i = dynamic_cast<Value<Date> *> (b);
	if (b == nullptr) return nullptr;
	return i->copy();
}
template<> Value<Time> * convert(ValueBase * b)
{
	auto i = dynamic_cast<Value<Time> *> (b);
	if (b == nullptr) return nullptr;
	return i->copy();
}
template<> Value<DateTime> * convert(ValueBase * b)
{
	auto i = dynamic_cast<Value<DateTime> *> (b);
	if (b == nullptr) return nullptr;
	return i->copy();
}

template <typename T>
T string_to_val(const string & str) { return T(str); }
template <> int string_to_val(const string & str) { return atoi(str.c_str()); }
template <> double string_to_val(const string & str) { return stolld(str.c_str()); }
template <> Date string_to_val(const string & str) { return Date(str); }
template <> Time string_to_val(const string & str) { return Time(str); }
template <> DateTime string_to_val(const string & str)
{
	string date = str.substr(0, 10);
	string time = str.substr(11, 8);
	return DateTime(date, time);
}