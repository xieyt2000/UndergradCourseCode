﻿#include "Interpreter.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <corecrt_io.h>

using namespace std;

// #define DEBUG

Interpreter::Interpreter(bool _readFromFile, const string & _archiveName)
	: sql_type(-1), archiveName(_archiveName)
{
	if (_readFromFile && !_access(_archiveName.c_str(), 0))
		manager = new Manager(_readFromFile, _archiveName);
	else
		manager = new Manager(false, _archiveName);
}

Interpreter::~Interpreter()
{
	delete manager;
}

bool seg(char c)
{
	if (c == '=' || c == '>' || c == '<') return true;
	if (c == '(' || c == ')' || c == ',' || c == ';') return true;
	return false;
}

void Interpreter::SplitSQL(string statement)
{
	char * cstr = const_cast<char *>(statement.c_str());
	char current[256];
	size_t i = 0, j = 0;
	while (i < statement.size())
	{
		if (statement[i] == ' ')
		{
			i++;
			if (j)
			{
				current[j] = '\0';
				sql_vector.push_back(current);
				j = 0;
			}
		}
		else if (seg(statement[i]))
		{
			if (j)
			{
				current[j] = '\0';
				sql_vector.push_back(current);
			}
			current[0] = statement[i];
			current[1] = '\0';
			sql_vector.push_back(current);
			j = 0; i++;
		}

		else
		{
			current[j++] = statement[i++];
		}
	}
}

void Interpreter::GetSQLType()
{
	sql_vector[0] = to_lower(sql_vector[0]);
	if (sql_vector.size() == 0)
	{
		sql_type = -1;
		cout << "logging: SQL TYPE: empty" << endl;
		return;
	}

	if (sql_vector[0] == "create")
	{
		if (sql_vector.size() <= 1)
		{
			sql_type = -1;
			cout << "SyntaxError: use 'help;' to get correct command." << endl;
			return;
		}
		sql_vector[1] = to_lower(sql_vector[1]);
		if (sql_vector[1] == "database") { sql_type = 1; } /* CREATE DATABASE */
		else if (sql_vector[1] == "table") { sql_type = 2; } /* CREATE TABLE */
		else { sql_type = -1; }
	}
	else if (sql_vector[0] == "show")
	{
		if (sql_vector.size() <= 1)
		{
			sql_type = -1;
			cout << "SyntaxError: use 'help;' to get correct command." << endl;
			return;
		}
		sql_vector[1] = to_lower(sql_vector[1]);
		if (sql_vector[1] == "databases") { sql_type = 11; } /* SHOW DATABASES */
		else if (sql_vector[1] == "tables") { sql_type = 12; } /* SHOW TABLES */
		else sql_type = 13;/*SHOW COLUMNS*/
	}
	else if (sql_vector[0] == "drop")
	{
		if (sql_vector.size() <= 1)
		{
		}
		sql_vector[1] = to_lower(sql_vector[1]);
		if (sql_vector[1] == "database") { sql_type = 3; } /* DROP DATABASE */
		else if (sql_vector[1] == "table") { sql_type = 4; } /* DROP TABLE */
		else { sql_type = -1; } // undefined operation

	}
	else if (sql_vector[0] == "use") { sql_type = 5; } /* USE */
	else if (sql_vector[0] == "insert") { sql_type = 6; } /* INSERT */
	else if (sql_vector[0] == "select")
	{
		bool intoFile = false;

		for (auto & tmpStr : sql_vector)
		{
			if (to_lower(tmpStr) == "into")
			{
				sql_type = 17;	/* SELECT ... INTO ... */
				intoFile = true;
				break;
			}
		}
		if (!intoFile)
			sql_type = 7;	/* SELECT */
	}
	else if (sql_vector[0] == "delete") { sql_type = 8; } /* DELETE */
	else if (sql_vector[0] == "update") { sql_type = 9; } /* UPDATE */
	else if (sql_vector[0] == "load") { sql_type = 19; }	/* LOAD */
	else
	{
		sql_type = -1;
		cout << "SyntaxError: use 'help;' to get correct command." << endl;
		return;
	}

}

void Interpreter::ParseSQL()
{
	switch (sql_type)
	{
	case 11:
	{
		manager->ShowDatabases();
		break;
	}
	case 12:
	{
		manager->ShowTables();
		break;
	}
	case 13:
	{
		SQLShowColumns * st = new SQLShowColumns(sql_vector);
		manager->ShowColumns(*st);
		delete st;
		break;
	}

	case 1:
	{
		SQLCreateDatabase * st = new SQLCreateDatabase(sql_vector);
		manager->CreateDatabase(*st);
		delete st;
		break;
	}
	case 2:
	{
		SQLCreateTable * st = new SQLCreateTable(sql_vector);
		manager->CreateTable(*st);
		delete st;
		break;
	}

	case 3:
	{
		SQLDropDatabase * st = new SQLDropDatabase(sql_vector);
		manager->DropDatabase(*st);
		delete st;
		break;
	}
	case 4:
	{
		SQLDropTable * st = new SQLDropTable(sql_vector);
		manager->DropTable(*st);
		delete st;
		break;
	}

	case 5:
	{
		SQLUse * st = new SQLUse(sql_vector);
		manager->Use(*st);
		delete st;
		break;
	}
	case 6:
	{
		SQLInsert * st = new SQLInsert(sql_vector);
		manager->Insert(*st);
		delete st;
		break;
	}
	case 19:
	{
		SQLLoad * st = new SQLLoad(sql_vector);
		if (!st->failed())
			manager->Load(*st);
		delete st;
		break;
	}
	case 7:
	{
		SQLSelect * st = new SQLSelect(sql_vector);
		manager->Select(*st);
		delete st;
		break;
	}

	case 17:
	{
		SQLSelect * st = new SQLSelect(sql_vector, true);
		manager->Select(*st);
		delete st;
		break;
	}

	case 8:
	{
		SQLDelete * st = new SQLDelete(sql_vector);
		manager->Delete(*st);
		delete st;
		break;
	}
	case 9:
	{
		SQLUpdate * st = new SQLUpdate(sql_vector);
		manager->Update(*st);
		delete st;
		break;
	}
	default:
		break;
	}
}

void Interpreter::SQL(string statement)
{
	sql_vector.clear();
	sql = statement;  /* get SQL statement */
	SplitSQL(statement);
	GetSQLType();		/* get sql type */
#ifdef DEBUG
	cout << "[debug] split into: ";
	for (auto i : sql_vector) { cout << i << " "; }
	cout << endl;
#endif
	ParseSQL();			/* construct SQL object and pass to manager */
}
