#include "Database.h"
#include <iostream>
#include <string>
#include <sstream>
#include <cctype>
#include <utility>
#include <algorithm>

//解析和执行命令
void Database::work(const string & cmdLine)
{
	string cmd1, cmd2, tmpName, whr, tmpClause;

	std::istringstream cmdIN(cmdLine);
	cmdIN >> cmd1;
	if (toUpper(cmd1) == "CREATE")
	{
		cmdIN >> cmd2;
		if (toUpper(cmd2) != "TABLE") throw std::runtime_error("Cmd. error");

		std::getline(cmdIN, tmpName, '(');
		dropSpace(tmpName);

		std::getline(cmdIN, tmpClause);
		dropSpace(tmpClause);
		if (tmpClause.back() == ')') tmpClause.pop_back();

		create(tmpName, tmpClause);
	}
	else if (toUpper(cmd1) == "SHOW")
	{
		cmdIN >> cmd2;
		//DB一级SHOW开头的命令有两个
		if (toUpper(cmd2) == "COLUMNS")
		{
			cmdIN >> whr;
			if (toUpper(whr) != "FROM") throw std::runtime_error("Cmd. error");

			cmdIN >> tmpName;
			tab[tmpName].showCol();
		}
		else if (toUpper(cmd2) == "TABLES")
		{
			showTab();
		}
		else
			throw std::runtime_error("Cmd. error");
	}
	else if (toUpper(cmd1) == "INSERT")
	{
		cmdIN >> cmd2;
		if (toUpper(cmd2) != "INTO") throw std::runtime_error("Cmd. error");

		std::getline(cmdIN, tmpName, '(');
		dropSpace(tmpName);

		string tmpAttr;
		std::getline(cmdIN, tmpAttr, ')');
		dropSpace(tmpAttr);

		cmdIN >> cmd2;
		if (toUpper(cmd2) != "VALUES") throw std::runtime_error("Cmd. error");
		
		//抛掉可能存在的不需要的字符和'('
		std::getline(cmdIN, tmpClause, '(');	
		
		std::getline(cmdIN, tmpClause, ')');
		dropSpace(tmpClause);

		tab[tmpName].insert(tmpAttr, tmpClause);
	}
	else if (toUpper(cmd1) == "DELETE")
	{
		cmdIN >> cmd2;
		if (toUpper(cmd2) != "FROM") throw std::runtime_error("Cmd. error");

		cmdIN >> tmpName;
		if (cmdIN >> whr)
		{
			if (toUpper(whr) != "WHERE") throw std::runtime_error("Cmd. error");
			std::getline(cmdIN, tmpClause, ';');
		}
		else
			tmpClause = _NULL;

		tab[tmpName].drop(tmpClause);
	}
	else if (toUpper(cmd1) == "UPDATE")
	{
		cmdIN >> tmpName >> cmd2;
		if (toUpper(cmd2) != "SET") throw std::runtime_error("Cmd. error");

		string tmpAttr, tmpVal;
		std::getline(cmdIN, tmpAttr, '=');
		std::getline(cmdIN, tmpVal, ' ');

		dropSpace(tmpAttr); dropSpace(tmpVal);

		if (cmdIN >> whr)
		{
			if (toUpper(whr) != "WHERE") throw std::runtime_error("Cmd. error");
			std::getline(cmdIN, tmpClause, ';');
		}
		else
			tmpClause = _NULL;

		tab[tmpName].update(tmpAttr, tmpVal, tmpClause);
	}
	else if (toUpper(cmd1) == "SELECT")
	{
		string tmpAttr;
		cmdIN >> tmpAttr >> cmd2 >> tmpName;
		if (toUpper(cmd2) != "FROM") throw std::runtime_error("Cmd. error");

		if (cmdIN >> whr)
		{
			if (toUpper(whr) != "WHERE") throw std::runtime_error("Cmd. error");
			std::getline(cmdIN, tmpClause, ';');
		}
		else
			tmpClause = _NULL;

		tab[tmpName].select(tmpAttr, tmpClause);
	}
	else if (toUpper(cmd1) == "DROP")
	{
		cmdIN >> cmd2;
		if (toUpper(cmd2) != "TABLE")
			throw std::runtime_error("Cmd. error");
		cmdIN >> tmpName;
		tabName.erase(std::find(tabName.begin(), tabName.end(), tmpName));
		tab.erase(tmpName);
	}
	else
		throw std::runtime_error("Cmd. error");

}


void Database::showTab()
{
	std::sort(tabName.begin(), tabName.end());
	std::cout << "Tables_in_" << name << std::endl;
	for (const string & s : tabName)
	{
		std::cout << s << std::endl;
	}
}

void Database::create(const string & _name, const string & _attr)
{
	tabName.push_back(_name);
	tab.emplace(std::make_pair(string(_name), Table(_attr)));
}

void Database::drop(const string & _tabName)
{
	auto found = std::find(tabName.begin(), tabName.end(), _tabName);
	if (found == tabName.end())
		throw std::runtime_error("Deleteing table that not exists");
	tabName.erase(found);
	tab.erase(_tabName);
}
