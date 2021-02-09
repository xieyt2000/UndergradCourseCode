#ifndef _COLUMN_H_
#define _COLUMN_H_

#include <string>
#include <vector>
#include <stdexcept>
#include <sstream>
#include <iomanip>
#include <iostream>
using std::string;

//���ڱ�ǿ�ֵ���ַ���������Ϊ���㹻�����Եĸ��˰���
static const string _NULL("tHiS_iS_a_NuLl_VaLuE");

class Column
{
public:

	//�����������͵ı�ǣ�Null����ֻ��Ϊ��Ĭ�Ϲ��캯���ķ���
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

	//���룬��ȱʡֵʵ��NULL
	void insert(const string & _val = _NULL)
	{
		if (notNull && _val == _NULL)
			throw std::runtime_error("Cannot write null value into NOT NULL column.");

		val.push_back(_val);
		//���������CHAR����Ⲣ��ȥ����ʱ���е�����
		if (type == TYPE::CHAR)
		{
			if (val.back().front() == '"' || val.back().front() == '\'') val.back().erase(val.back().begin());
			if (val.back().back() == '"' || val.back().back() == '\'') val.back().pop_back();
		}
	}

	//ȡֵ������NULL������������������ʽ��
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

	//���ͣ������
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

	//���ͣ��ڱ�Ĺ�������
	TYPE Type() const { return type; }

	//���
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

	//�ǿ�����
	string getNN() const
	{
		return string(notNull ? "NO" : "YES");
	}

	//����ֵ
	void update(const size_t & _index, const string & _val)
	{
		val.at(_index) = _val;
		//���������CHAR����Ⲣ��ȥ����
		if (type == TYPE::CHAR)
		{
			if (val.at(_index).front() == '"' || val.at(_index).front() == '\'') val.at(_index).erase(val.at(_index).begin());
			if (val.at(_index).back() == '"' || val.at(_index).back() == '\'') val.at(_index).pop_back();
		}
	}

	//ɾ��
	void drop(const size_t & _index)
	{
		val.erase(val.begin() + _index);
	}
	
	//������
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

//��ȥ�ַ���ǰ��Ŀհ��ַ�
void dropSpace(string & _str);
#endif // !_COLUMN_H_