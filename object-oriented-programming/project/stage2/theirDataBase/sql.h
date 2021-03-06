﻿#pragma once
/*sql类解析输入sql的语句*/
#include<string>
#include<vector>
#include <utility>
#include<algorithm>
#include"Attribute.h"
#include"WhereClause.h"
#include<iostream>
using namespace std;

string to_lower(string str);
string to_upper(string str);

// 语句被切割后放在sql_vector中，本函数将sql_vector中从pos下标开始的where子句转换为其组成要素。

int buildWhereClauseFrom(vector<string> sql_vector,
	vector<pair<LogicOperation, int> > & o,
	vector<WhereClause::SubSentence> & s,
	int pos);

class SQL
{
public:
	SQL() :sql_type(-1) {}
	SQL(int type) :sql_type(type) {}
	int get_sql_type() { return sql_type; }
	void set_sql_type(int type) { sql_type = type; }
	virtual void Parse(vector<string> sql) = 0;
protected:
	int sql_type;
};

// class: SQLCreateDatabase 

class SQLCreateDatabase : public SQL
{
public:
	SQLCreateDatabase(vector<string> sql);
	string get_db_name() { return database_name; }
	void set_db_name(string dbname) { database_name = dbname; }
	void Parse(vector<string> sql);//对sql命令进行语法分析
private:
	string database_name;
};

/* class: SQLCreateTable: create table tbname (attr1, char(100), attr2, char(20), primary key(attr1));*/
class SQLCreateTable : public SQL
{
public:
	SQLCreateTable(vector<string> sql);
	SQLCreateTable(const string & _primary, const string & _table_name, const vector<Attribute> _attrs)
		: primary(_primary), table_name(_table_name), attrs(_attrs)
	{};
	string get_tb_name() { return table_name; }
	string get_primary() { return primary; }
	void set_tb_name(string name) { table_name = name; }
	vector<Attribute> GetAttributes() { return attrs; }
	void SetAttributes(vector<Attribute> attr) { attrs = vector<Attribute>(attr); }
	void Parse(vector<string> sql);
private:
	string primary;
	string table_name;
	vector<Attribute> attrs;
};


class SQLShowColumns : public SQL
{
public:
	SQLShowColumns(vector<string> sql);
	string get_tb_name();
	void Parse(vector<string> sql);
private:
	string tb_name;
};

class SQLDropDatabase : public SQL
{
public:
	SQLDropDatabase(vector<string> sql);
	string get_db_name();
	void set_db_name(string dbname);
	void Parse(vector<string> sql);
private:
	string db_name;
};


class SQLDropTable : public SQL
{
public:
	SQLDropTable(vector<string> sql);
	string get_tb_name();
	void set_tb_name(string tbname);
	void Parse(vector<string> sql);
private:
	string tb_name;
};

/* class: SQLUse: use dbname; */
class SQLUse : public SQL
{
public:
	SQLUse(vector<string> sql);
	string get_db_name();
	void set_db_name(string dbname);
	void Parse(vector<string> sql);
private:
	string db_name;
};


class SQLInsert : public SQL
{
public:
	SQLInsert(vector<string> sql);
	~SQLInsert();
	string get_tb_name();
	void Parse(vector<string> sql);
	vector<string> attrNames;
	vector<ValueBase *> vals;
	string tb_name;
};

class SQLLoad : public SQL
{
public:
	SQLLoad(vector<string> sql);
	SQLLoad(const string & _fileName, const string & _tbName, const vector<string> & _attrNames);
	~SQLLoad();

	string getTbName() { return tbName; }
	void Parse(vector<string> sql) override;
	
	string fileName;
	string tbName;
	vector<string> attrNames;
	vector<vector<string>> vals_string;

	bool failed() const { return failbit; }
private:
	bool failbit;
};

class SQLSelect : public SQL
{
public:
	SQLSelect(vector<string> sql, bool intoFile = false);
	string get_tb_name();
	void Parse(vector<string> sql);
	vector<string> attrFilter;
	vector<WhereClause::SubSentence> s;
	vector<pair<LogicOperation, int> > o;
	string getFileName() const;
	bool isToFile() const { return intoFile; }
	bool isMathFuntion = false;
	vector<string> MathClause;

	//add
	bool hasCount;
	string countwhat;
	bool hasGroupBy;
	vector<string> groupbywhat;
	bool hasOrderBy;
	string orderbywhat;
	//add

	~SQLSelect();
protected:
	string tb_name;
	bool intoFile;
	string fileName;
};
//class SQLSelectFile : public SQL
//{
//public:
//	SQLSelectFile(vector<string>);
//	bool is_cout() const;
//	string get_tb_name();
//	void Parse(vector<string> sql) override;
//	vector<string> attrFilter;
//	vector<WhereClause::SubSentence> s;
//	vector<pair<LogicOperation, int> > o;
//	~SQLSelectFile();
//
//private:
//	string fileName;
//	string tb_name;
//};

class SQLDelete : public SQL
{
public:
	SQLDelete(vector<string> sql);
	string get_tb_name();
	void Parse(vector<string> sql);
	vector<WhereClause::SubSentence> s;
	vector<pair<LogicOperation, int> > o;
	~SQLDelete();
private:
	string tb_name;

};

class SQLUpdate : public SQL
{
public:
	SQLUpdate(vector<string> sql);
	string get_tb_name();
	void Parse(vector<string> sql);
	vector<string> attrNames;
	vector<ValueBase *> vals;
	vector<WhereClause::SubSentence> s;
	vector<pair<LogicOperation, int> > o;
	~SQLUpdate();
private:
	string tb_name;
};

