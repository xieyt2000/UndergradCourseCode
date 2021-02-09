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
	//�ӱ�����Ϊ������VS��һ��warning���ڱ�֤�������ڵ�ǰ����û��ʵ������
	primaryIndex = 0;

	std::istringstream sIN(_cmd);
	string cmdLine;

	//�Զ���Ϊ�ָ���һ���������б�
	while (std::getline(sIN, cmdLine, ','))
	{
		dropSpace(cmdLine);

		std::istringstream tmpIN(cmdLine);
		string tmp, tmp2;
		Column::TYPE tmpType;

		tmpIN >> tmp;

		bool skip = false;
		if (toUpper(tmp) == "PRIMARY")	//����"PRIMARY"
		{
			std::getline(tmpIN, tmp2, '(');
			dropSpace(tmp2);

			if (toUpper(tmp2) == "KEY")	//�����һ�����Ƿ���"KEY"
			{	//���ǣ��������������ֵ������������Ϊ������������ִ�����
				std::getline(tmpIN, tmp, ')');
				primaryIndex = int(std::find(colName.begin(), colName.end(), tmp) - colName.begin());
			}
			else
			{	//�����ǣ�˵������һ����Ϊprimary����
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

	//Ϊ��ʵ�ֲ���˳�������������ԣ����������һ��map������������ֵ����ϵ�������в���ֵ��NULL
	//�Զ��ŷָ����������б�����ȥ�ո񣬽���ӳ��
	while (std::getline(attrIN, attrTmp, ','))
	{
		std::getline(valIN, valTmp, ',');
		dropSpace(valTmp);
		dropSpace(attrTmp);

		m[attrTmp] = valTmp;
	}

	//��ÿһ�ж�Ҫ����
	for (auto & a : colName)
	{
		if (m.count(a))
			//�����������ֵ
			col[a].insert(m[a]);
		else
			//�����������_NULL
			col[a].insert();
	}
}

void Table::drop(string _clause)
{
	auto whereResult = doClasue(_clause);

	//����doClause���ص���vector<bool>��Ϊ��ʹ��ɾ���Ĳ�Ӱ���ɾ���ģ����±�����ѭ��
	//size_t���޷������ͣ�Ϊʹ������ѭ������0��������
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
		//��Ϊ����д����
		const string & a = colName[i];

		std::cout << a << '\t'	//������
			<< col.at(a).getType() << col.at(a).getWidth() << '\t'	//�������ͺͿ��
			<< col.at(a).getNN() << '\t'	//�ǿ�����
			<< (i == primaryIndex ? "PRI" : "") << '\t'	//��������
			<< "NULL" << '\t'	//Default����ǰδʵ��
			<< ""	//Extra����ǰδʵ��
			<< std::endl;
	}
}

void Table::select(const string & _attrName, string _clause)
{
	//���ڿձ�񣬲�Ӧ�����ͷ��������
	if (col[colName[primaryIndex]].getSize() == 0) return;

	//����Ϊ��ʵ������
	//����ʵ������Ч�ʲ��ߣ���ֱ���������ݸ�������
	//������ÿ��Column��Ҫ��������˳�����У�
	std::map<string, size_t> m;
	std::vector<string> v;

	auto whereResult = doClasue(_clause);
	for (size_t i = 0; i < whereResult.size(); i++)
	{
		if (!whereResult[i]) continue;

		m[col[colName[primaryIndex]].getVal(i)] = i;
		v.push_back(col[colName[primaryIndex]].getVal(i));
	}

	//ȫ����ʾ�Ͳ�����ʾʵ�����в�ͬ��ͨ�����bool����
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

//��һ������OR��������Ӿ�
std::vector<bool> Table::doClasue(string clause)
{
	size_t size = col[colName[primaryIndex]].getSize();
	std::vector<bool> result(size), tmp(size);

	//���У��������Ϊ�գ���ÿһ�����ݶ���ѡȡ֮��
	if (clause == _NULL)
	{
		std::fill(result.begin(), result.end(), true);
		return result;
	}

	std::fill(result.begin(), result.end(), false);
	
	//���ﲻ����toUpper�����������ʵ�ֶԴ�Сд������
	while (clause.find(" or ") != string::npos)
		clause.replace(clause.find(" or "), 4, " OR ");
	
	for (auto i = clause.find("OR"); i != std::string::npos; i = clause.find("OR"))
	{
		//��ֺ�ÿ��С�Ӿ����ڶ���
		tmp = doClauseNoOR(clause.substr(0, i - 1), size);
		
		for (int i = 0; i < size; i++)
			result[i] = tmp[i] || result[i];
		
		//�Ѵ������С�Ӿ�ɾȥ
		clause.erase(0, i + 3);
	}

	//û��OR�������һ��С�Ӿ�
	tmp = doClauseNoOR(clause, size);
	for (int i = 0; i < size; i++)
		result[i] = tmp[i] || result[i];

	return result;
}

//�ڶ�������AND�����һ���������Ӿ�
std::vector<bool> Table::doClauseNoOR(string clause, const size_t & size)
{
	std::vector<bool> re(size), tmp(size);
	std::fill(re.begin(), re.end(), true);

	//ͬ1
	if (clause.find(" and ") != string::npos)
		clause.replace(clause.find(" and "), 5, " AND ");
	
	for (auto i = clause.find("AND"); i != std::string::npos; i = clause.find("AND"))
	{
		//ÿ��С�Ӿ���������
		tmp = doClauseSIMPLE(clause.substr(0, i - 1), size);

		for (int i = 0; i < size; i++)
			re[i] = tmp[i] && re[i];
		clause.erase(0, i + 4);
	}

	//û��AND�������һ��С�Ӿ�
	tmp = doClauseSIMPLE(clause, size);
	for (int i = 0; i < size; i++)
		re[i] = tmp[i] && re[i];

	return re;
}

//������������û���߼���������Ӿ�
std::vector<bool> Table::doClauseSIMPLE(const string & clause, const size_t & size)
{
	std::vector<bool> r(size);
	string attrName, attrVal;
	size_t pos;

	//���ﴦ��úܲ��ã���������ʵ�ֹ���
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

//���Ƚϱ��ʽ
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
