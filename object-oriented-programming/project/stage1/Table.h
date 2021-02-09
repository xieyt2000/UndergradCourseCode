#ifndef _TABLE_H_
#define _TABLE_H_

#include "Column.h"
#include <string>
#include <map>
#include <vector>

//���ַ���תΪ��д�ĺ�����ʵ�ֹؼ��ֵĴ�Сд������
string toUpper(const string & _src);

class Table
{
public:
	//���캯����ͨ��_cmd��������б�
	Table(string _cmd);

	Table() :primaryIndex(-1) {}

	~Table()
	{}

	//���뺯��
	void insert(const string & _attrName, const string & _value);

	//ɾ������
	void drop(string _clause = _NULL);

	//���ĺ���
	void update(const string & _attrName, const string & _val, string _clause = _NULL);

	//��ʾ�к���
	void showCol() const;

	//��ʾ���ݺ���
	void select(const string & _attrName, string _clause = _NULL);

private:
	std::vector<string> colName;
	std::map<string, Column> col;
	int primaryIndex;

	//string��Column::TYPE��ת��������������ʱʹ��
	Column::TYPE toType(const string & _str);

	//�����ͼ�����ʽ�ĺ���
	std::vector<bool> doClasue(string clause);
	std::vector<bool> doClauseNoOR(string clause, const size_t & size);
	std::vector<bool> doClauseSIMPLE(const string & clause, const size_t & size);
	void simpleClause(const string & clause, const size_t & pos, string & l, string & r);

	//Ϊ��ʹ�����������ĺ���
	void create(std::istream & tmpIN, const string & tmpName, string & tmp2, const Column::TYPE & tmpType);
};

#endif // !_TABLE_H_
