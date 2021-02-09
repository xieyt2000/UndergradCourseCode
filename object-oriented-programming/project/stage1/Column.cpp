#include "Column.h"

void dropSpace(string & _str)
{	
	while (!_str.empty() && isspace(_str.front())) _str.erase(_str.begin());
	while (!_str.empty() && isspace(_str.back())) _str.pop_back();
}

template <Column::TYPE T>
bool cmp(const string & l, const string & r)
{
	return true;
}

template <>
bool cmp<Column::TYPE::INT>(const string & l, const string & r)
{
	return std::stoi(l) < std::stoi(r);
}
template <>
bool cmp<Column::TYPE::DOUBLE>(const string & l, const string & r)
{
	return std::stod(l) < std::stod(r);
}
template <>
bool cmp<Column::TYPE::CHAR>(const string & l, const string & r)
{
	return l < r;
}
