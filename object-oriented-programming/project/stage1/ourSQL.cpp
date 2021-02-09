#include "ourSQL.h"
#include <sstream>
#include <iostream>
#include <string>
#include <map>
#include <utility>
#include <algorithm>

//所有对DataBase的操作都在这一级完成，其余的传入activeDB，交由其判断执行
void ourSQL::work()
{
	std::string buffer, cmd1, cmd2, tmpName;
	
	//以分号为分隔读取命令，并除去前后空白字符
	while (std::getline(std::cin, buffer, ';'))
	{
		dropSpace(buffer);
		//如果读到的是空行，则跳过
		if (buffer.empty()) continue;

		//用stringstream解析命令
		std::istringstream cmdIN(buffer);
		cmdIN >> cmd1;

		if (toUpper(cmd1) == "CREATE")
		{
			cmdIN >> cmd2;
			if (toUpper(cmd2) != "DATABASE")
			{
				if (activeDB.empty())
					throw std::runtime_error("Cmd. error");
				else
				{
					db[activeDB].work(buffer);
					continue;
				}
			}

			cmdIN >> tmpName;
			db.emplace(std::make_pair(tmpName, Database(tmpName)));
			dbName.push_back(tmpName);
		}
		else if (toUpper(cmd1) == "DROP")
		{
			cmdIN >> cmd2;
			if (toUpper(cmd2) != "DATABASE")
			{
				if (activeDB.empty())
					throw std::runtime_error("Cmd. error");
				else
				{
					db[activeDB].work(buffer);
					continue;
				}
			}

			cmdIN >> tmpName;
			if (!db.count(tmpName))
				throw std::runtime_error("No such database");

			if (activeDB == tmpName)
				activeDB.clear();
			db.erase(tmpName);
			dbName.erase(std::find(dbName.begin(), dbName.end(), tmpName));
		}
		else if (toUpper(cmd1) == "SHOW")
		{
			cmdIN >> cmd2;
			if (toUpper(cmd2) != "DATABASES")
			{
				if (activeDB.empty())
					throw std::runtime_error("Cmd. error");
				else
				{
					db[activeDB].work(buffer);
					continue;
				}
			}

			showDB();
		}
		else if (toUpper(cmd1) == "USE")
		{
			cmdIN >> tmpName;
			if (db.count(tmpName))
				activeDB = tmpName;
			else
				throw std::runtime_error("No such database");
		}
		else
		{
			if (activeDB.empty())
				throw std::runtime_error("Cmd. error");
			else
				db[activeDB].work(buffer);
		}
	}
}

void ourSQL::showDB()
{
	std::cout << "Database" << std::endl;
	std::sort(dbName.begin(), dbName.end());
	for (auto & a : dbName)
		std::cout << a << std::endl;
}
