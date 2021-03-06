﻿// encodings=UTF-8
#include "Table.h"
#include <algorithm>

Table::Table(string name, vector<Attribute> a, string primary)
	:name(name), attrs(a), primary(primary)
{}

Table::Table(Table && t) {}

Table::~Table() {}

bool Table::insert(vector<string> attrNames, vector<ValueBase *> vals)
{
	Record t(attrs.size());
	bool succ = true;
	for (size_t i = 0; i < attrNames.size(); i++)
	{
		for (size_t j = 0; j < attrs.size(); j++)
		{
			if (attrNames[i] == attrs[j].name)
			{
// 检查是否指定了重复的属性
				for (size_t k = 0; k < attrNames.size(); k++)
					if (i != k && attrNames[i] == attrNames[k])
						succ = false;
				if (vals[i] == nullptr)
				{
					t[j] = nullptr;
					break;
				}
				switch (attrs[j].type)
				{
				case ATTR_INT:
				{
					t[j] = convert<int>(vals[i]);
					if (vals[i] && !t[j]) succ = false;
					break;
				}
				case ATTR_DOUBLE:
				{
					t[j] = convert<double>(vals[i]);
					if (vals[i] && !t[j]) succ = false;
					break;
				}
				case ATTR_CHAR:
				{
					t[j] = convert<string>(vals[i]);
					if (vals[i] && !t[j]) succ = false;
					break;
				}
				case ATTR_DATE:
				{
					t[j] = convert<Date>(vals[i]);
					if (vals[i] && !t[j]) succ = false;
					break;
				}
				case ATTR_TIME:
				{
					t[j] = convert<Time>(vals[i]);
					if (vals[i] && !t[j]) succ = false;
					break;
				}
				case ATTR_DATETIME:
				{
					t[j] = convert<DateTime>(vals[i]);
					if (vals[i] && !t[j]) succ = false;
					break;
				}
				default:
					break;
				}

				break;
			}
		}
		if (!succ) break;
	}
	int primaryIndex = 0;
	for (size_t i = 0; i < attrs.size(); i++)
	{
		if (primary == attrs[i].name)
		{
			primaryIndex = i;
			// 检查主键唯一性
			for (auto & j : data)
			{
				if (*j[i] == *t[i])
				{
					succ = false;
					break;
				}
			}
			break;
		}
	}
	for (size_t i = 0; i < attrs.size(); i++)
	{
// notNull 检查(主键强制非空)
		if (t[i] == nullptr && (attrs[i].notNull || primaryIndex == i))
		{
			succ = false;
			break;
		}
		if (!succ) break;
	}
	// 根据要求，记录要按照主键排序
	// （插入排序）
	if (succ)
	{
		auto iter = data.begin();
		for (; iter != data.end() && *(*iter)[primaryIndex] < *t[primaryIndex]; iter++);
		data.insert(iter, std::move(t));
	}
	return succ;
}

bool Table::del(WhereClause c)
{
// 逆序选择元素
	for (int i = data.size() - 1; i >= 0; i--)
	{
		if (c.test(data[i], attrs))
		{
			data.erase(data.begin() + i);
		}
	}
	return true;
}
bool Table::checkType(AttributeType att, ValueBase * v)
{
	if (att == ATTR_CHAR && !dynamic_cast<Value<string> *> (v))
		return false;
	if (att == ATTR_DOUBLE && !dynamic_cast<Value<double> *> (v))
		return false;
	if (att == ATTR_INT && !dynamic_cast<Value<int> *> (v))
		return false;
	/*  
		I added some cases, may cause bugs. LXZ 
	*/
	if (att == ATTR_DATE && !dynamic_cast<Value<Date> *> (v))
		return false;
	if (att == ATTR_TIME && !dynamic_cast<Value<Time> *> (v))
		return false;
	if (att == ATTR_DATETIME && !dynamic_cast<Value<DateTime> *> (v))
		return false;

	return true;
}
AttributeType Table::askType(const string & _attrName) const
{
	for (auto & attr : attrs)
	{
		if (attr.name == _attrName)
			return attr.type;
	}
	return ATTR_INT;
}
//#define DEBUG
#ifdef DEBUG
#include <iostream>
#endif
bool Table::update(vector<string> attrNames, vector<ValueBase *> vals, WhereClause c)
{
// 类型匹配，非空检查
	for (size_t j = 0; j < attrNames.size(); j++)
	{
		for (size_t k = 0; k < attrs.size(); k++)
		{
			if (attrNames[j] == attrs[k].name)
			{
// 类型转换
				if (attrs[k].type == ATTR_DOUBLE)
				{
					auto nv = convert<double>(vals[j]);
					delete vals[j];
					vals[j] = nv;
				}
				if (!checkType(attrs[k].type, vals[j]))
				{
					errMsg = "Incompatible type.";
#ifdef DEBUG
					vals[j]->print(std::cout);
#endif
					return false;
				}
				if (attrs[k].notNull && vals[j] == nullptr)
				{
					errMsg = "Null where it should be not null.";
					return false;
				}
				break;
			}
		}
	}
	// 主键查重
	vector<int> updateList; // 待修改的行号记录在这里
	// primaryCount: 主键的新值在更新完成后出现了多少次；
	// primaryIndex: 主键在attrs中的下标索引是多少
	int primaryCount = 0, primaryIndex = 0;
	// primaryValue: 主键的新值是多少（如果主键未被修改，则为nullptr）
	ValueBase * primaryValue = nullptr;
	for (size_t i = 0; i < attrs.size(); i++)
	{
		if (attrs[i].name == primary)
		{
			primaryIndex = i;
			break;
		}
	}
	for (size_t i = 0; i < vals.size(); i++)
	{
		if (attrNames[i] == primary)
			primaryValue = vals[i];
	}
	// 合法，则可以进行修改
	for (size_t i = 0; i < data.size(); i++)
	{
		if (!c.test(data[i], attrs))
		{
			if (primaryValue)
				primaryCount += *data[i][primaryIndex] == *primaryValue;
		}
		else
		{
			updateList.push_back(i);
			primaryCount++; // 对于赋值型更新，每修改一个，重复次数多一次
		}
		if (primaryValue && primaryCount > 1) break;
	}
	if (primaryValue && primaryCount > 1)
	{
		errMsg = "Duplicated primary value.";
		return false;
	}
	for (auto i : updateList)
	{
		for (size_t j = 0; j < attrNames.size(); j++)
		{
			for (size_t k = 0; k < attrs.size(); k++)
			{
				if (attrNames[j] == attrs[k].name)
				{
					delete data[i][k];
					data[i][k] = vals[j]->copy();
					break;
				}
			}
		}
		if (primaryValue == nullptr) continue;
		Record r = data[i];
		using std::cout;
		using std::endl;
		// cout << "[debug]" << i << " " ;
		// cout << *data[i+1][primaryIndex] << " " << *r[primaryIndex] << " " << (*data[i+1][primaryIndex] < *r[primaryIndex]);
		// cout << endl;
		size_t j;	// I changed this j from int to size_t, if things go wrong, this may be the cause. LXZ
		for (j = i; j > 0 && *data[j - 1][primaryIndex] > * r[primaryIndex]; j--)
			data[j] = std::move(data[j - 1]);
		data[j] = r;
		r = data[i];
		for (j = i; j + 1 < data.size() && *data[j + 1][primaryIndex] < *r[primaryIndex]; j++)
			data[j] = std::move(data[j + 1]);
		data[j] = r;
	}
	return true;
}

PrintableTable * Table::select(vector<string> attrFilter, WhereClause c)
{
	vector<Attribute> newTableAttrs;
	for (auto i : attrs)
	{
		bool flag = false;
		for (auto j : attrFilter)
		{
			if (j == "*" || j == i.name)
			{
				flag = true;
				break;
			}
		}
		if (flag)
			newTableAttrs.push_back(i);
	}
	// 这里主键名称为空，不符合约定，因此
	PrintableTable * table = new PrintableTable(newTableAttrs);
	int n = attrs.size(), m = newTableAttrs.size();
	for (auto r : data)
	{
		if (!c.test(r, attrs)) continue;
		auto nr = new ValueBase * [m];
		for (int i = 0, j = 0; i < n; i++)
		{
			if (j > m) break;	//	will crash with current program. added this. LXZ
			if (j == m || attrs[i].name == newTableAttrs[j].name)	
			{
				nr[j] = r[i] ? r[i]->copy() : r[i];
				j++;
			}
		}
		table->insert(nr);
	}
	return table;
}

ostream & Table::show(ostream & out) const
{
	out << "Field\tType\tNull\tKey\tDefault\tExtra" << std::endl;
	// 括号内的数字是显示宽度(int)/长度(char)/数字位数(double)
	// P.S. 我刚知道CHAR是定长度字符串？而且默认长度是1？？
	for (auto i : attrs)
	{
		out << i.name << "\t";

		switch (i.type)
		{
		case ATTR_INT:
			out << "int(11)";
			break;
		case ATTR_CHAR:			
			out << "char(1)";
			break;
		case ATTR_DOUBLE:
			out << "double";
			break;
		case ATTR_DATE:
			out << "date";
			break;
		case ATTR_DATETIME:
			out << "datetime";
			break;
		case ATTR_TIME:
			out << "time";
			break;
		default:
			break;
		}
		out << "\t";
		out << (i.notNull ? "NO" : "YES") << "\t" << (primary == i.name ? "PRI" : "") << "\t";
		out << "NULL\t" << std::endl;
	}

	return out;
}

// 以下代码仅供单元测试使用
/*
#include <iostream>
using std::cout;
using std::endl;
void Table::test_print() {
	int n = attrs.size();
	for (int i = 0; i < n; i++) cout << attrs[i].name << "\t";
	cout << endl;
	for (auto & j: data) {
		for (int i = 0; i < n; i++) {
			if (j[i]) cout << (*j[i]);
			cout << "\t";
		}
		cout << endl;
	}
}*/