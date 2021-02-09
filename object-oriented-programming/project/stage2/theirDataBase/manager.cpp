#include"manager.h"
#include<algorithm>
#include <fstream>
#include <io.h>
#include <sstream>
#include "MathFunction.h"
// #define DEBUG

Manager::Manager(bool loadFromFile, const string & _archiveName) :num(0), archiveName(_archiveName)
{
	if (loadFromFile)
	{
		ifstream dbNameIn(archiveName);
		string tmpDBName;
		while (getline(dbNameIn, tmpDBName))
		{
#ifdef DEBUG
			cout << "Read database" << tmpDBName << " from archive file." << endl;
#endif // DEBUG

			databases.push_back(DataBase(tmpDBName));
			num++;

			ifstream tbNameIn(tmpDBName + ".save");
			string tmpTbName, tmpAttrs;

			while (getline(tbNameIn, tmpTbName))
			{
				getline(tbNameIn, tmpAttrs);

				istringstream attrIN(tmpAttrs);
				istringstream singleIN;
				vector<Attribute> attrs;
				vector<string> attrNames;
				string tmpPrimary, tmpSingleAttr, tmpAttrName, tmpAttrNull, tmpAttrType;

				getline(attrIN, tmpPrimary, ';');

				while (getline(attrIN, tmpSingleAttr, ';'))
				{
					singleIN.clear();
					singleIN.str(tmpSingleAttr);
					singleIN >> tmpAttrName >> tmpAttrType >> tmpAttrNull;
					attrNames.emplace_back(tmpAttrName);
					attrs.emplace_back(Attribute(tmpAttrName, tmpAttrType, tmpAttrNull == "true"));
				}

				SQLCreateTable stCT(tmpPrimary, tmpTbName, attrs);

				GetDB(tmpDBName)->CreateTable(stCT);

				SQLLoad stL(tmpDBName + "." + tmpTbName + ".save", tmpTbName, attrNames);

				Table * tb = databases.back().getTB(tmpTbName);

				size_t size = attrNames.size();

				for (auto & j : stL.vals_string)
				{
					vector<ValueBase *> vals;

					for (size_t index = 0; index < size; index++)
					{
						auto type = tb->askType(attrNames[index]);
						switch (type)
						{
						case ATTR_INT:
							vals.emplace_back(new Value<int>(string_to_val<int>(j[index])));
							break;
						case ATTR_CHAR:
							vals.emplace_back(new Value<string>(j[index]));
							break;
						case ATTR_DOUBLE:
							vals.emplace_back(new Value<double>(string_to_val<double>(j[index])));
							break;
						case ATTR_DATE:
							vals.emplace_back(new Value<Date>(string_to_val<Date>(j[index])));
							break;
						case ATTR_TIME:
							vals.emplace_back(new Value<Time>(string_to_val<Time>(j[index])));
							break;
						case ATTR_DATETIME:
							vals.emplace_back(new Value<DateTime>(string_to_val<DateTime>(j[index])));
							break;
						default:
							break;
						}
					}

					if (!tb->insert(attrNames, vals))
					{
						cout << "Insertion failed. " << endl;
					}
				}
			}
		}
	}
}

Manager::~Manager()
{
	ofstream sysOut(archiveName);

	for (auto & db : databases)
	{
		sysOut << db.name << endl;

		ofstream dbOut(db.name + ".save");
		auto tables = db.GetTables();

		for (auto tb : tables)
		{
			dbOut << tb->name << endl;
			dbOut << tb->primary << ';';
			for (auto & attr : tb->attrs)
			{
				dbOut << attr.name << '\t' << attr.type << '\t' << (attr.notNull ? "true" : "false") << ';';
			}

			ofstream tbOut(db.name + "." + tb->name + ".save");

			auto data = tb->getData();
			size_t n = tb->attrs.size();
			for (Record & v : data)
			{
				for (size_t i = 0; i < n; i++)
				{
					if (v[i])
						v[i]->print(tbOut) << '\t';
					else
						tbOut << '\t';
				}
				tbOut << endl;
			}
		}
	}
}

void Manager::CreateDatabase(SQLCreateDatabase & statement)
{
#ifdef DEBUG
	cout << "Creating DataBase: " << statement.get_db_name() << endl;
#endif
//DataBase *temp=new DataBase(statement.get_db_name());//此处应修改为相应构造函数
//databases.push_back(*temp);
	databases.push_back(DataBase(statement.get_db_name()));
	//cout << (databases.back()).name << "---" << endl;
	num++;
}

DataBase * Manager::GetDB()
{
	for (int i = 0; i < num; i++)
		if (databases[i].name == current_db)
			return &(databases[i]);
	return NULL;
}

DataBase * Manager::GetDB(string db)
{
	for (int i = 0; i < num; i++)
		if (databases[i].name == db)
			return &(databases[i]);
	return NULL;
}

void Manager::CreateTable(SQLCreateTable & statement)
{
#ifdef DEBUG
	cout << "Creating table: " << statement.get_tb_name() << endl;
#endif

	DataBase * db = GetDB();
	db->CreateTable(statement);
}

void Manager::ShowDatabases()
{
	//cout << "here" << endl;
	if (num == 0)
	{
		cout << "No databases exist now." << endl;
		cout << "Use 'create DataBase' command to create a new DataBase." << endl;
		return;
	}
	cout << "Database" << endl;
	vector<string> output;
	for (int i = 0; i < num; i++)
		output.push_back(databases[i].name);
	std::sort(output.begin(), output.end());
	for (auto & i : output)
		cout << i << endl;
}

void Manager::ShowTables()
{
	if (current_db.size() == 0) return;
	DataBase * db = GetDB();
	if (db == NULL) return;
	if (db->GetTables().size() == 0)
	{
		cout << "No table exist now." << endl;
		cout << "Use 'create table' command to create a new table." << endl;
		return;
	}
	// cout << "| " << setw(22) << "Tables_in_"+ current_db << " |" << endl;
	cout << "Tables_in_" << current_db << endl;

	vector<string> output;
	auto tables = db->GetTables();
	for (auto tb = tables.begin(); tb != tables.end(); tb++)
		output.push_back((*tb)->name);
	std::sort(output.begin(), output.end());
	for (auto & i : output) cout << i << endl;
	// for (auto tb = db->GetTables().begin(); tb != db->GetTables().end(); tb++)
	// 	cout << "| " << setw(22) << (*tb)->name << " |" << endl;

}

void Manager::ShowColumns(SQLShowColumns & statement)
{
	if (current_db.size() == 0) return;
	DataBase * db = GetDB();
	if (db == NULL) return;
	if (db->GetTables().size() == 0)
	{
		cout << "No table exist now." << endl;
		cout << "Use 'create table' command to create a new table." << endl;
		return;
	}
	Table * tb = db->getTB(statement.get_tb_name());
	/*列出制定表项的各项信息，包括属性、属性类型、主键 信息。*/
	tb->show(cout);

}

void Manager::DropDatabase(SQLDropDatabase & statement)
{
#ifdef DEBUG
	cout << "Droping DataBase: " << statement.get_db_name() << endl;
#endif

//to be finished: delete statement.get_db_name; 
	for (auto iter = databases.begin(); iter != databases.end(); iter++)
	{
		if (iter->name == statement.get_db_name())
		{
			databases.erase(iter);
			num--;
			break;
		}
	}

	if (statement.get_db_name() == current_db)
	{
		current_db = "";
	}
}

void Manager::DropTable(SQLDropTable & statement)
{
#ifdef DEBUG
	cout << "Droping table: " << statement.get_tb_name() << endl;
#endif
	if (current_db.length() == 0) return;

	DataBase * db = GetDB();
	if (db == NULL) return;

	Table * tb = db->getTB(statement.get_tb_name());
	if (tb == NULL) return;

	db->DropTable(statement.get_tb_name());
}

void Manager::Use(SQLUse & statement)
{
	DataBase * db = GetDB(statement.get_db_name());
	if (db == NULL) return;
	current_db = statement.get_db_name();
}

void Manager::Insert(SQLInsert & statement)
{
	if (current_db.length() == 0) return;
	DataBase * db = GetDB();
	if (db == NULL) return;

	string tb_name = statement.get_tb_name();
	Table * tb = db->getTB(tb_name);
#ifdef DEBUG
	cout << "Item Info: ***" << endl;
	for (auto i : statement.attrNames) cout << i << " "; cout << endl;
	for (auto i : statement.vals) (i->print(cout)) << " "; cout << endl << "*****" << endl;
#endif
	if (!tb->insert(statement.attrNames, statement.vals))
	{
		cout << "Insertion failed. " << endl;
	}
}

void Manager::Load(SQLLoad & statement)
{
	if (current_db.length() == 0) return;
	DataBase * db = GetDB();
	if (db == NULL) return;

	string tbName = statement.getTbName();
	Table * tb = db->getTB(tbName);

#ifdef DEBUG
	cout << "Item Info: ***" << endl;
	for (auto i : statement.attrNames) cout << i << " "; cout << endl;
	for (auto i : statement.vals)
	{
		for (auto & j : i)
			j->print(cout) << " ";
		cout << endl;
}
	cout << "*****" << endl;
#endif
	size_t size = statement.attrNames.size();

	for (auto & j : statement.vals_string)
	{
		vector<ValueBase *> vals;

		for (size_t index=0;index<size;index++)
		{
			auto type = tb->askType(statement.attrNames[index]);
			switch (type)
			{
			case ATTR_INT:
				vals.emplace_back(new Value<int>(string_to_val<int>(j[index])));
				break;
			case ATTR_CHAR:
				vals.emplace_back(new Value<string>(j[index]));
				break;
			case ATTR_DOUBLE:
				vals.emplace_back(new Value<double>(string_to_val<double>(j[index])));
				break;
			case ATTR_DATE:
				vals.emplace_back(new Value<Date>(string_to_val<Date>(j[index])));
				break;
			case ATTR_TIME:
				vals.emplace_back(new Value<Time>(string_to_val<Time>(j[index])));
				break;
			case ATTR_DATETIME:
				vals.emplace_back(new Value<DateTime>(string_to_val<DateTime>(j[index])));
				break;
			default:
				break;
			}
		}

		if (!tb->insert(statement.attrNames, vals))
		{
			cout << "Insertion failed. " << endl;
		}
	}
}

void Manager::Select(SQLSelect & statement)
{
	if (current_db.length() == 0) return;
	Table * tb = GetDB()->getTB(statement.get_tb_name());
	if (tb == NULL) return;

	if (statement.isMathFuntion)
	{
		PrintMathFunction(statement.MathClause);
		return;
	}

	WhereClause c(statement.s, statement.o);
	if (!statement.isToFile())
	{
		//tb->select(statement.attrFilter, c)->print(cout, true);
		//add
		if (statement.hasGroupBy == false)
			if (statement.hasCount == false)
				if (statement.hasOrderBy == false)
					tb->select(statement.attrFilter, c)->print(cout, true);//select ...
				else
					tb->select(statement.attrFilter, c)->orderprint(cout, statement.orderbywhat);//select ... ORDER BY
			else
				tb->select(statement.attrFilter, c)->countprint(cout, statement.countwhat);// select ... COUNT
		else
			tb->select(statement.attrFilter, c)->groupprint(cout, statement.hasCount, statement.countwhat, statement.groupbywhat, statement.hasOrderBy, statement.orderbywhat);
			//select ... GROUP BY
			//select ... GROUP BY ... ORDER BY
			//select ... COUNT ... GROUP BY
			//select ... COUNT ... GROUP BY ... ORDER BY...	
		//add

	}
	else
	{
		string fileName = statement.getFileName();

		if (_access(fileName.c_str(), 0) == 0)
		{
			cerr << "ERROR : file already exists" << endl;
			return;
		}

		ofstream fileOut;
		fileOut.open(fileName);

		WhereClause c(statement.s, statement.o);
		tb->select(statement.attrFilter, c)->print(fileOut, false);
	}
}

void Manager::Delete(SQLDelete & statement)
{
	if (current_db.length() == 0) return;
	Table * tb = GetDB()->getTB(statement.get_tb_name());
	if (tb == NULL) return;
	WhereClause c(statement.s, statement.o);
	tb->del(c);
}

void Manager::Update(SQLUpdate & statement)
{
	if (current_db.length() == 0) return;
	DataBase * db = GetDB();
	if (db == NULL) return;

	Table * tb = db->getTB(statement.get_tb_name());
	if (tb == NULL) return;
	WhereClause c(statement.s, statement.o);
	if (!tb->update(statement.attrNames, statement.vals, c))
	{
		cout << "Updating failed. Error Meesage: " << tb->getErrorMsg() << endl;
	}
}
