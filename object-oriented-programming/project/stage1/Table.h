#ifndef _TABLE_H_
#define _TABLE_H_

#include "Column.h"
#include <string>
#include <map>
#include <vector>

//将字符串转为大写的函数，实现关键字的大小写不敏感
string toUpper(const string & _src);

class Table
{
public:
	//构造函数，通过_cmd传入参数列表
	Table(string _cmd);

	Table() :primaryIndex(-1) {}

	~Table()
	{}

	//插入函数
	void insert(const string & _attrName, const string & _value);

	//删除函数
	void drop(string _clause = _NULL);

	//更改函数
	void update(const string & _attrName, const string & _val, string _clause = _NULL);

	//显示列函数
	void showCol() const;

	//显示内容函数
	void select(const string & _attrName, string _clause = _NULL);

private:
	std::vector<string> colName;
	std::map<string, Column> col;
	int primaryIndex;

	//string到Column::TYPE的转换函数，构造列时使用
	Column::TYPE toType(const string & _str);

	//解析和计算表达式的函数
	std::vector<bool> doClasue(string clause);
	std::vector<bool> doClauseNoOR(string clause, const size_t & size);
	std::vector<bool> doClauseSIMPLE(const string & clause, const size_t & size);
	void simpleClause(const string & clause, const size_t & pos, string & l, string & r);

	//为了使代码更简洁加入的函数
	void create(std::istream & tmpIN, const string & tmpName, string & tmp2, const Column::TYPE & tmpType);
};

#endif // !_TABLE_H_
