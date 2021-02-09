#ifndef _OURSQL_H_
#define _OURSQL_H_
#include "Database.h"

class ourSQL
{
public:
	ourSQL() : activeDB(string()) {}
	~ourSQL() {}

	//对外只留一个接口，调用后由这个对象接管I/O
	void work();
private:
	std::map<std::string, Database> db;
	std::vector<string> dbName;
	string activeDB;

	void showDB();
};

#endif // !_OURSQL_H_

