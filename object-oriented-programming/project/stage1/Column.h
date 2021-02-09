#ifndef _COLUMN_H_
#define _COLUMN_H_

#include <string>
#include <vector>
#include <stdexcept>
#include <sstream>
#include <iomanip>
#include <iostream>
using std::string;

//用于标记空值的字符串，内容为有足够特殊性的个人爱好
static const string _NULL("tHiS_iS_a_NuLl_VaLuE");

class Column
{
public:

	//本列数据类型的标记，Null类型只是为了默认构造函数的方便
	enum TYPE
	{
		Null = 0,
		INT = 1,
		DOUBLE = 2,
		CHAR = 3,
	};

	Column() : name(_NULL), type(TYPE::Null), notNull(false), width(0)
	{}

	Column(const string & _name, TYPE _type, bool _notNull = false) : name(_name), type(_type), notNull(_notNull)
	{
		switch (type)
		{
		case Column::INT:
			width = 11;
			break;
		case Column::DOUBLE:
			width = 0;
			break;
		case Column::CHAR:
			width = 1;
			break;
		default:
			width = 0;
			break;
		}
	}

	~Column()
	{}

	//插入，用缺省值实现NULL
	void insert(const string & _val = _NULL)
	{
		if (notNull && _val == _NULL)
			throw std::runtime_error("Cannot write null value into NOT NULL column.");

		val.push_back(_val);
		//如果类型是CHAR，检测并除去输入时带有的引号
		if (type == TYPE::CHAR)
		{
			if (val.back().front() == '"' || val.back().front() == '\'') val.back().erase(val.back().begin());
			if (val.back().back() == '"' || val.back().back() == '\'') val.back().pop_back();
		}
	}

	//取值，特判NULL，按照数据类型做格式化
	string getVal(const size_t & _index)
	{
		if (val.at(_index) == _NULL) return string("NULL");

		switch (type)
		{
		case Column::INT:
			return (val.at(_index));
			break;
		case Column::DOUBLE:
		{
			std::stringstream ss;
			ss << std::fixed << std::setprecision(4) << std::stod(val.at(_index));
			return ss.str();
			break;
		}
		case Column::CHAR:
		{
			return val.at(_index);
			break;
		}
		default:
		case Column::Null:
			return val.at(_index);
			break;
		}
	}

	//类型，输出用
	string getType() const
	{
		switch (type)
		{
		case Column::INT:
			return string("int");
			break;
		case Column::DOUBLE:
			return string("double");
			break;
		case Column::CHAR:
			return string("char");
			break;
		case Column::Null:
		default:
			return _NULL;
			break;
		}
	}

	//类型，在别的功能中用
	TYPE Type() const { return type; }

	//宽度
	string getWidth() const
	{
		if (width != 0)
		{
			return "(" + std::to_string(width) + ")";
		}
		else
		{
			return string();
		}
	}

	//非空属性
	string getNN() const
	{
		return string(notNull ? "NO" : "YES");
	}

	//更新值
	void update(const size_t & _index, const string & _val)
	{
		val.at(_index) = _val;
		//如果类型是CHAR，检测并除去引号
		if (type == TYPE::CHAR)
		{
			if (val.at(_index).front() == '"' || val.at(_index).front() == '\'') val.at(_index).erase(val.at(_index).begin());
			if (val.at(_index).back() == '"' || val.at(_index).back() == '\'') val.at(_index).pop_back();
		}
	}

	//删除
	void drop(const size_t & _index)
	{
		val.erase(val.begin() + _index);
	}
	
	//内容数
	size_t getSize() const
	{
		return val.size();
	}

private:
	string name;
	TYPE type;
	bool notNull;
	std::vector<string> val;
	unsigned width;
};

template <Column::TYPE T>
bool cmp(const string & l, const string & r);

template <>
bool cmp<Column::TYPE::INT>(const string & l, const string & r);

template <>
bool cmp<Column::TYPE::DOUBLE>(const string & l, const string & r);

template <>
bool cmp<Column::TYPE::CHAR>(const string & l, const string & r);

//除去字符串前后的空白字符
void dropSpace(string & _str);
#endif // !_COLUMN_H_