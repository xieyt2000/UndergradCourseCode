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

	//对外只留存一个接口，传入一整行命令，由DB负责解析执行
	void work(const string & cmdLine);

private:
	string name;
	std::vector<string> tabName;
	std::map<string, Table> tab;
	
	//显示数据表
	void showTab();

	//添加表
	void create(const string & _name, const string & _attr);

	//删除表
	void drop(const string & _tabName);
};


#endif // !_DATABASE_H_
