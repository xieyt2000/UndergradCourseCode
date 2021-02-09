#include "Table.h"
#include <sstream>
#include <map>
#include <cctype>
#include <vector>
#include <algorithm>
#include <stdexcept>
#include <iostream>
#include <cstdlib>
#include <stack>

string toUpper(const string & _src)
{
	string tmp("");
	for (const char a : _src)
	{
		tmp += static_cast<char>(toupper(a));
	}
	return tmp;
}

Table::Table(string _cmd)
{
	//加本行是为了消掉VS的一个warning，在保证主键存在的前提下没有实际意义
	primaryIndex = 0;

	std::istringstream sIN(_cmd);
	string cmdLine;

	//以逗号为分隔逐一解析参数列表
	while (std::getline(sIN, cmdLine, ','))
	{
		dropSpace(cmdLine);

		std::istringstream tmpIN(cmdLine);
		string tmp, tmp2;
		Column::TYPE tmpType;

		tmpIN >> tmp;

		bool skip = false;
		if (toUpper(tmp) == "PRIMARY")	//读到"PRIMARY"
		{
			std::getline(tmpIN, tmp2, '(');
			dropSpace(tmp2);

			if (toUpper(tmp2) == "KEY")	//检查下一个词是否是"KEY"
			{	//若是，读后面括号里的值，将主键设置为它，这条命令执行完毕
				std::getline(tmpIN, tmp, ')');
				primaryIndex = int(std::find(colName.begin(), colName.end(), tmp) - colName.begin());
			}
			else
			{	//若不是，说明这是一个名为primary的列
				tmpType = toType(tmp2);

				colName.push_back(tmp);
				create(tmpIN, tmp, tmp2, tmpType);
			}
			continue;
		}

		tmpIN >> tmp2;
		tmpType = toType(tmp2);

		colName.push_back(tmp);
		create(tmpIN, tmp, tmp2, tmpType);
	}
}

void Table::insert(const string & _attrName, const string & _value)
{
	std::istringstream attrIN(_attrName), valIN(_value);
	std::map<string, string> m;
	string attrTmp, valTmp;

	//为了实现参数顺序、数量的任意性，在这里多用一个map建立参数名和值的联系，并逐列插入值或NULL
	//以逗号分隔解析参数列表，并除去空格，建立映射
	while (std::getline(attrIN, attrTmp, ','))
	{
		std::getline(valIN, valTmp, ',');
		dropSpace(valTmp);
		dropSpace(attrTmp);

		m[attrTmp] = valTmp;
	}

	//对每一列都要插入
	for (auto & a : colName)
	{
		if (m.count(a))
			//这样插入的是值
			col[a].insert(m[a]);
		else
			//这样插入的是_NULL
			col[a].insert();
	}
}

void Table::drop(string _clause)
{
	auto whereResult = doClasue(_clause);

	//函数doClause返回的是vector<bool>，为了使先删除的不影响后删除的，让下标逆向循环
	//size_t是无符号类型，为使它不死循环，把0独立出来
	for (size_t i = whereResult.size() - 1; i > 0; i--)
	{
		if (!whereResult[i]) continue;

		for (auto & a : col)
			a.second.drop(i);
	}
	if (whereResult[0])
	{
		for (auto & a : col)
			a.second.drop(0);
	}
}

void Table::update(const string & _attrName, const string & _val, string _clause)
{
	auto whereResult = doClasue(_clause);

	for (size_t i = 0; i < whereResult.size(); i++)
	{
		if (!whereResult[i]) continue;

		col[_attrName].update(i, _val);
	}
}

void Table::showCol() const
{
	std::cout << "Field\tType\tNull\tKey\tDefault\tExtra" << std::endl;
	for (int i = 0; i < col.size(); i++)
	{
		//是为了书写方便
		const string & a = colName[i];

		std::cout << a << '\t'	//列名称
			<< col.at(a).getType() << col.at(a).getWidth() << '\t'	//数据类型和宽度
			<< col.at(a).getNN() << '\t'	//非空属性
			<< (i == primaryIndex ? "PRI" : "") << '\t'	//主键属性
			<< "NULL" << '\t'	//Default，当前未实现
			<< ""	//Extra，当前未实现
			<< std::endl;
	}
}

void Table::select(const string & _attrName, string _clause)
{
	//对于空表格，不应输出表头，故特判
	if (col[colName[primaryIndex]].getSize() == 0) return;

	//这是为了实现排序
	//这样实现排序效率不高，但直接排序内容更加困难
	//（由于每个Column都要依照主键顺序排列）
	std::map<string, size_t> m;
	std::vector<string> v;

	auto whereResult = doClasue(_clause);
	for (size_t i = 0; i < whereResult.size(); i++)
	{
		if (!whereResult[i]) continue;

		m[col[colName[primaryIndex]].getVal(i)] = i;
		v.push_back(col[colName[primaryIndex]].getVal(i));
	}

	//全部显示和部分显示实现略有不同，通过这个bool区分
	bool doAll = _attrName == "*";

	if (doAll)
	{
		switch (col[colName[primaryIndex]].Type())
		{
		case Column::TYPE::CHAR:
			std::sort(v.begin(), v.end(), cmp<Column::TYPE::CHAR>);
		case Column::TYPE::INT:
			std::sort(v.begin(), v.end(), cmp<Column::TYPE::INT>);
		case Column::TYPE::DOUBLE:
			std::sort(v.begin(), v.end(), cmp<Column::TYPE::DOUBLE>);
		default:
			break;
		}
	}
	else
	{
		switch (col[_attrName].Type())
		{
		case Column::TYPE::CHAR:
			std::sort(v.begin(), v.end(), cmp<Column::TYPE::CHAR>);
		case Column::TYPE::INT:
			std::sort(v.begin(), v.end(), cmp<Column::TYPE::INT>);
		case Column::TYPE::DOUBLE:
			std::sort(v.begin(), v.end(), cmp<Column::TYPE::DOUBLE>);
		default:
			break;
		}
	}

	if (doAll)
	{
		for (size_t i = 0; i < colName.size() - 1; i++)
			std::cout << colName[i] << '\t';
		std::cout << colName[colName.size() - 1] << std::endl;

		for (auto a : v)
		{
			for (size_t i = 0; i < colName.size() - 1; i++)
				std::cout << col[colName[i]].getVal(m[a]) << '\t';
			std::cout << col[colName[colName.size() - 1]].getVal(m[a]) << std::endl;
		}
	}
	else
	{
		std::cout << _attrName << std::endl;

		for (auto a : v)
			std::cout << col[_attrName].getVal(m[a]) << std::endl;
	}
}

Column::TYPE Table::toType(const string & _str)
{
	if (toUpper(_str) == "INT")
		return Column::TYPE::INT;
	else if (toUpper(_str) == "DOUBLE")
		return Column::TYPE::DOUBLE;
	else if (toUpper(_str) == "CHAR")
		return Column::TYPE::CHAR;
	else
		throw std::runtime_error("Type error");
}

//第一步：按OR拆分条件子句
std::vector<bool> Table::doClasue(string clause)
{
	size_t size = col[colName[primaryIndex]].getSize();
	std::vector<bool> result(size), tmp(size);

	//特判：如果条件为空，则每一行数据都在选取之列
	if (clause == _NULL)
	{
		std::fill(result.begin(), result.end(), true);
		return result;
	}

	std::fill(result.begin(), result.end(), false);
	
	//这里不适用toUpper函数，故如此实现对大小写不敏感
	while (clause.find(" or ") != string::npos)
		clause.replace(clause.find(" or "), 4, " OR ");
	
	for (auto i = clause.find("OR"); i != std::string::npos; i = clause.find("OR"))
	{
		//拆分后每个小子句进入第二步
		tmp = doClauseNoOR(clause.substr(0, i - 1), size);
		
		for (int i = 0; i < size; i++)
			result[i] = tmp[i] || result[i];
		
		//把处理过的小子句删去
		clause.erase(0, i + 3);
	}

	//没有OR或处理最后一个小子句
	tmp = doClauseNoOR(clause, size);
	for (int i = 0; i < size; i++)
		result[i] = tmp[i] || result[i];

	return result;
}

//第二步：按AND拆分上一步传来的子句
std::vector<bool> Table::doClauseNoOR(string clause, const size_t & size)
{
	std::vector<bool> re(size), tmp(size);
	std::fill(re.begin(), re.end(), true);

	//同1
	if (clause.find(" and ") != string::npos)
		clause.replace(clause.find(" and "), 5, " AND ");
	
	for (auto i = clause.find("AND"); i != std::string::npos; i = clause.find("AND"))
	{
		//每个小子句进入第三步
		tmp = doClauseSIMPLE(clause.substr(0, i - 1), size);

		for (int i = 0; i < size; i++)
			re[i] = tmp[i] && re[i];
		clause.erase(0, i + 4);
	}

	//没有AND或处理最后一个小子句
	tmp = doClauseSIMPLE(clause, size);
	for (int i = 0; i < size; i++)
		re[i] = tmp[i] && re[i];

	return re;
}

//第三步：计算没有逻辑运算符的子句
std::vector<bool> Table::doClauseSIMPLE(const string & clause, const size_t & size)
{
	std::vector<bool> r(size);
	string attrName, attrVal;
	size_t pos;

	//这里处理得很不好，但至少能实现功能
	if ((pos = clause.find('<')) != std::string::npos)
	{
		simpleClause(clause, pos, attrName, attrVal);
		if (col[attrName].Type() == Column::CHAR)
		{
			for (int i = 0; i < size; i++)
			{
				if (col[attrName].getVal(i) == "NULL")
				{
					r[i] = false;
					continue;
				}
				r[i] = col[attrName].getVal(i) < attrVal;
			}
		}
		else if (col[attrName].Type() == Column::INT)
		{
			for (int i = 0; i < size; i++)
			{
				if (col[attrName].getVal(i) == "NULL")
				{
					r[i] = false;
					continue;
				}
				r[i] = std::stoi(col[attrName].getVal(i)) < std::stoi(attrVal);
			}
		}
		else if (col[attrName].Type() == Column::DOUBLE)
		{
			for (int i = 0; i < size; i++)
			{
				if (col[attrName].getVal(i) == "NULL")
				{
					r[i] = false;
					continue;
				}
				r[i] = std::stod(col[attrName].getVal(i)) < std::stod(attrVal);
			}
		}
		else
			throw std::runtime_error("");

	}
	else if ((pos = clause.find('>')) != std::string::npos)
	{
		simpleClause(clause, pos, attrName, attrVal);
		if (col[attrName].Type() == Column::CHAR)
		{
			for (int i = 0; i < size; i++)
			{
				if (col[attrName].getVal(i) == "NULL")
				{
					r[i] = false;
					continue;
				}
				r[i] = col[attrName].getVal(i) > attrVal;
			}
		}
		else if (col[attrName].Type() == Column::INT)
		{
			for (int i = 0; i < size; i++)
			{
				if (col[attrName].getVal(i) == "NULL")
				{
					r[i] = false;
					continue;
				}
				r[i] = std::stoi(col[attrName].getVal(i)) > std::stoi(attrVal);
			}
		}
		else if (col[attrName].Type() == Column::DOUBLE)
		{
			for (int i = 0; i < size; i++)
			{
				if (col[attrName].getVal(i) == "NULL")
				{
					r[i] = false;
					continue;
				}
				r[i] = std::stod(col[attrName].getVal(i)) > std::stod(attrVal);
			}
		}
		else
			throw std::runtime_error("");

	}
	else if ((pos = clause.find('=')) != std::string::npos)
	{
		simpleClause(clause, pos, attrName, attrVal);
		if (col[attrName].Type() == Column::CHAR)
		{
			for (int i = 0; i < size; i++)
			{
				if (col[attrName].getVal(i) == "NULL")
				{
					r[i] = false;
					continue;
				}
				r[i] = col[attrName].getVal(i) == attrVal;
			}
		}
		else if (col[attrName].Type() == Column::INT)
		{
			for (int i = 0; i < size; i++)
			{
				if (col[attrName].getVal(i) == "NULL")
				{
					r[i] = false;
					continue;
				}
				r[i] = std::stoi(col[attrName].getVal(i)) == std::stoi(attrVal);
			}
		}
		else if (col[attrName].Type() == Column::DOUBLE)
		{
			for (int i = 0; i < size; i++)
			{
				if (col[attrName].getVal(i) == "NULL")
				{
					r[i] = false;
					continue;
				}
				r[i] = abs(std::stod(col[attrName].getVal(i)) - std::stod(attrVal)) < 0.1;
			}
		}

		else
			throw std::runtime_error("");
	}
	else
		throw std::runtime_error("Clause error");

	return r;
}

//拆解比较表达式
void Table::simpleClause(const string & clause, const size_t & pos, string & l, string & r)
{
	l = clause.substr(0, pos);
	dropSpace(l);
	r = clause.substr(pos + 1);
	dropSpace(r);

	if (r.front() == '"' || r.front() == '\'') r.erase(r.begin());
	if (r.back() == '"' || r.back() == '\'') r.pop_back();

	return;
}

void Table::create(std::istream & tmpIN, const string & tmpName, string & tmp2, const Column::TYPE & tmpType)
{
	if (std::getline(tmpIN, tmp2))
	{
		dropSpace(tmp2);
		col.emplace(std::make_pair(tmpName, Column(tmpName, tmpType, toUpper(tmp2) == "NOT NULL")));
	}
	else
		col.emplace(std::make_pair(tmpName, Column(tmpName, tmpType)));
}
