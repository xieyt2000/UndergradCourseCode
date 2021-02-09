#ifndef _DATABASE_H_
#define _DATABASE_H_

#include "Table.h"
#include <string>
#include <sstream>
#include <map>
#include <vector>

class Database
{
public:
	Database(const string & _name = _NULL) : name(_name)
	{}

	~Database()
	{}

	//����ֻ����һ���ӿڣ�����һ���������DB�������ִ��
	void work(const string & cmdLine);

private:
	string name;
	std::vector<string> tabName;
	std::map<string, Table> tab;
	
	//��ʾ���ݱ�
	void showTab();

	//��ӱ�
	void create(const string & _name, const string & _attr);

	//ɾ����
	void drop(const string & _tabName);
};


#endif // !_DATABASE_H_
