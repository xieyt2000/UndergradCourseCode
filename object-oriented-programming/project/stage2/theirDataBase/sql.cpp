#include"sql.h"	
#include<stack>
#include <fstream>
#include <sstream>
//#define DEBUG

string to_lower(string str)
{
	transform(str.begin(), str.end(), str.begin(), ::tolower);
	return str;
}
string to_upper(string str)
{
	transform(str.begin(), str.end(), str.begin(), ::toupper);
	return str;
}

int buildWhereClauseFrom(vector<string> sql_vector,
	vector<pair<LogicOperation, int> > & o,
	vector<WhereClause::SubSentence> & s,
	int pos = 0)
{
	std::stack<LogicOperation> ss;
	int rank = 0;
	pos++;
	while (true)
	{
		auto logicPriority = [](LogicOperation o)->int {
			switch (o)
			{
			case LOGIC_AND:
				return 1;
				break;
			case LOGIC_OR:
				return 0;
				break;
			case LOGIC_NOT:
				return 2;
				break;
			case LOGIC_XOR:
				return 0;
				break;
			default:
				return -233;	/* UNDEFINED */
				break;
			}		};
#ifdef DEBUG
		cout << "[debug] " << sql_vector[pos] << endl;
#endif
		string lo_str = to_lower(sql_vector[pos]);
		if (lo_str == "and" || lo_str == "or" || lo_str == "xor" || lo_str == "not")
		{
			LogicOperation lo;
			if (lo_str == "and") lo = LOGIC_AND;
			else if (lo_str == "or") lo = LOGIC_OR;
			else if (lo_str == "xor") lo = LOGIC_XOR;
			else if (lo_str == "not") lo = LOGIC_NOT;
			else break;	//	wrong input

			while (ss.size())
			{
				LogicOperation tt = ss.top();
				if (logicPriority(tt) < logicPriority(lo))
					break;
				ss.pop();
				o.push_back(std::make_pair(tt, rank++));
			}
			ss.push(lo);
			pos++;
		}
		else
		{
			string v1 = sql_vector[pos];
			pos++;
			ArithmicOperation ar = ARITH_EQUAL;	//	just to make sure *ar* is initialised 
			if (sql_vector[pos] == "<") ar = ARITH_LESS;
			else if (sql_vector[pos] == "=") ar = ARITH_EQUAL;
			else if (sql_vector[pos] == ">") ar = ARITH_GREATER;
			pos++;
			string v2 = sql_vector[pos];
			pos++;
			// special case: form like 1 < id
			if (v1[0] >= '0' && v1[0] <= '9' || v1[0] == '.' || v1[0] == '\'' || v1[0] == '\"')
			{
				swap(v1, v2);
				if (ar == ARITH_LESS) ar = ARITH_GREATER;
				else if (ar == ARITH_GREATER) ar = ARITH_LESS;
			}
			ValueBase * vb = stringToValue(v2);
			s.push_back(make_tuple(v1, ar, vb, rank++)); // C
		}
		if (sql_vector[pos] == ";") break; /* one where condition, break. */
	}
	while (!ss.empty())
	{
		o.push_back(std::make_pair(ss.top(), rank++));
		ss.pop();
	}
#ifdef DEBUG
	cout << "[debug] where clause build info: " << endl;
	cout << s.size() << " "; for (auto i : s) cout << std::get<3>(i) << " "; cout << endl;
	cout << o.size() << " "; for (auto i : o) cout << i.second << " "; cout << endl;
#endif
	return pos;
}

/* -------------- SQLCreateDatabase ----------------- */
SQLCreateDatabase::SQLCreateDatabase(vector<string> sql) { Parse(sql); }

void SQLCreateDatabase::Parse(vector<string> sql)
{
	sql_type = 1;
	if (sql.size() <= 2) return;
	else
		database_name = sql[2];
}

/* -------------- SQLCreateTable ----------------- */
SQLCreateTable::SQLCreateTable(vector<string> sql) { Parse(sql); }

void SQLCreateTable::Parse(vector<string> sql_vector)
{
	sql_type = 2;
	unsigned int pos = 2;
	if (sql_vector.size() <= pos) return;

	//cout << "SQLCreateTable::Parse().logging: Table Name: " << sql_vector[pos] << endl;
	table_name = sql_vector[pos];
	pos++;

	if (sql_vector[pos] != "(") return;
	// pos ++;

	bool is_attr = true;
	bool has_primary_key = false;

	while (sql_vector[pos] != ")")
	{
		// is_attr = false;
		pos++;

		if (to_lower(sql_vector[pos]) != "primary" || to_lower(sql_vector[pos + 1]) != "key")
		{
			bool notnull = false;
			if (pos + 4 <= sql_vector.size() && to_lower(sql_vector[pos + 2]) == "not" && to_lower(sql_vector[pos + 3]) == "null")
				notnull = true;
			Attribute attr(sql_vector[pos], to_upper(sql_vector[pos + 1]), notnull);
			attrs.push_back(attr);

			if (notnull) pos += 4; // [name] [type] not null -> ,/)
			else pos += 2; // [name] [type] -> ,/)
			// if (sql_vector[pos] != ")") is_attr = true;
		}
		else  /* primary key */
		{
			if (has_primary_key) return;
			pos += 3; // primary key ( -> [name]
			primary = sql_vector[pos];
			/*for (auto att = attrs.begin(); att != attrs.end() ; att++)
			{
				if ((*att).name == sql_vector[pos])
				{
					(*att).type=1;//设定为主键
				}
			}*/
			pos += 2; // [name] ) -> ,/)
			has_primary_key = true;
		}
	}
}

/* -------------- SQLShowColumns -------------------- */
SQLShowColumns::SQLShowColumns(vector<string> sql_vector) { Parse(sql_vector); }

string SQLShowColumns::get_tb_name() { return tb_name; }

void SQLShowColumns::Parse(vector<string> sql_vector)
{
	sql_type = 13;
	tb_name = sql_vector[3];
}


/* -------------- SQLDropDatabase ----------------- */
SQLDropDatabase::SQLDropDatabase(vector<string> sql_vector) { Parse(sql_vector); }

string SQLDropDatabase::get_db_name() { return db_name; }

void SQLDropDatabase::set_db_name(string dbname) { db_name = dbname; }

void SQLDropDatabase::Parse(vector<string> sql_vector)
{
	sql_type = 3;
	db_name = sql_vector[2];
}

/* -------------- SQLDropTable -------------------- */
SQLDropTable::SQLDropTable(vector<string> sql_vector) { Parse(sql_vector); }

string SQLDropTable::get_tb_name() { return tb_name; }

void SQLDropTable::set_tb_name(string tbname) { tb_name = tbname; }

void SQLDropTable::Parse(vector<string> sql_vector)
{
	sql_type = 4;
	tb_name = sql_vector[2];
}



/* -------------- SQLUse ----------------- */
SQLUse::SQLUse(vector<string> sql_vector) { Parse(sql_vector); }

string SQLUse::get_db_name() { return db_name; }

void SQLUse::set_db_name(string dbname) { db_name = dbname; }

void SQLUse::Parse(vector<string> sql_vector)
{
	sql_type = 5;
	db_name = sql_vector[1];
}

/* ----------------- SQLInsert ------------------ */
SQLInsert::SQLInsert(vector<string> sql_vector) { Parse(sql_vector); }

string SQLInsert::get_tb_name() { return tb_name; }

void SQLInsert::Parse(vector<string> sql_vector)
{
	sql_type = 6;
	unsigned int pos = 2;
	bool is_attr = true;
	tb_name = sql_vector[pos];
	pos += 2;
	int num = 0;
	while (is_attr)
	{
		is_attr = false;
		attrNames.push_back(sql_vector[pos]);
		num++;
		pos++;
		if (sql_vector[pos] != ")") is_attr = true;
		pos++;
	}

	for (int i = 0; i < num; i++)
	{
		pos += 2;
		vals.push_back(stringToValue(sql_vector[pos]));
	}
}

SQLInsert::~SQLInsert()
{
	for (auto i : vals) delete i;
	vals.clear();
}

/* ---------------- SQLLoad -------------------- */

SQLLoad::SQLLoad(vector<string> sql_vector) : failbit(false) { Parse(sql_vector); }

SQLLoad::SQLLoad(const string & _fileName, const string & _tbName, const vector<string> & _attrNames)
	: fileName(_fileName), tbName(_tbName), attrNames(_attrNames), failbit(false)
{
	ifstream fileIN(fileName);
	string buffer, tmp;
	while (getline(fileIN, buffer))
	{
		vals_string.emplace_back(vector<string>());
		istringstream sIN(buffer);

		while (getline(sIN, tmp, '\t'))
		{
			vals_string.back().emplace_back(tmp);
		}
	}

}

SQLLoad::~SQLLoad()
{}

void SQLLoad::Parse(vector<string> sql_vector)
{
	sql_type = 19;
	size_t pos = 3;	//	0:LOAD, 1:DATA, 2:INFILE

	if (to_lower(sql_vector[pos]) == "local") pos++;

	fileName = sql_vector[pos];
	if (fileName.front() == '\'') fileName.erase(0, 1);
	if (fileName.back() == '\'') fileName.pop_back();

	ifstream fileIN(fileName);
	if (!fileIN.is_open())
	{
		cerr << "File cannot be opened" << endl;
		failbit = true;
		return;
	}


	pos += 3;	//	[fileName] -> INTO -> TABLE -> [tbName]

	tbName = sql_vector[pos];

	bool is_attr = true;
	pos += 2;	//	[tbName] -> "(" -> [some_attr]

	while (is_attr)
	{
		is_attr = false;
		attrNames.push_back(sql_vector[pos]);
		pos++;	//	[some_attr] -> "," / ")"
		if (sql_vector[pos] != ")") is_attr = true;
		pos++;	//	"," -> [another_attr]
	}

	string buffer, tmp;
	while (getline(fileIN, buffer))
	{
		vals_string.emplace_back(vector<string>());
		istringstream sIN(buffer);

		while (getline(sIN, tmp, '\t'))
		{
			vals_string.back().emplace_back(tmp);
		}
	}
}


/* ---------------- SQLSelect ----------------- */
SQLSelect::SQLSelect(vector<string> sql_vector, bool intoFile) : intoFile(intoFile) { Parse(sql_vector); }

string SQLSelect::get_tb_name() { return tb_name; }
string SQLSelect::getFileName() const { return fileName; }

void SQLSelect::Parse(vector<string> sql_vector) /* only support "select * ". */
{
	bool hasFrom = false;

	//add
	hasCount = false;
	hasGroupBy = false;
	hasOrderBy = false;
	//add

	for (auto & i : sql_vector)
	{
		if (to_lower(i) == "from")
		{
			hasFrom = true;
			break;
		}
	}
	if (!hasFrom)
	{
		isMathFuntion = true;
		MathClause = sql_vector;
		return;
	}
	//	UNDER : has FROM

	//add
	for (auto i = sql_vector.begin(); i != sql_vector.end(); i++)
	{
		if (to_upper((*i)) == "GROUP")
		{
			if (to_upper((*(i + 1))) == "BY")
			{
				hasGroupBy = true;
				while (true)
				{
					int pos = 0;
					groupbywhat.push_back((*(i + 2 + pos)));
					pos++;
					if (to_upper((*(i + 2 + pos))) == "ORDER" || (*(i + 2 + pos)) == ";")
					{
						break;
					}
				}
				break;
			}
		}
	}

	for (auto i = sql_vector.begin(); i != sql_vector.end(); i++)
	{
		if (to_upper((*i)) == "ORDER")
		{
			if (to_upper((*(i + 1))) == "BY")
			{
				hasOrderBy = true;
				orderbywhat = (*(i + 2));
				break;
			}
		}
	}
	//add

	if (!intoFile)
	{
		sql_type = 7;
		unsigned int pos = 1;
		while (true)
		{

			//add
			if (to_upper(sql_vector[pos]) == "COUNT")
			{
				hasCount = true;
				pos = pos + 2;//"("
				countwhat = sql_vector[pos];
				pos = pos + 2;//")"
				if (to_lower(sql_vector[pos]) == "from")
				{
					if (attrFilter.size() == 0)
					{
						attrFilter.push_back(countwhat);
					}
					break;
				}
			}
			//add

			if (sql_vector[pos] == "*")
			{
				attrFilter.push_back("*");
				pos++;
				break;
			}
			else
			{
				attrFilter.push_back(sql_vector[pos++]);
				if (to_lower(sql_vector[pos]) == "from") break;
				pos++;
			}
		}
		pos++; // from -> [table_name]
		tb_name = sql_vector[pos];
		pos++; // [table_name] -> ; / where
		if (sql_vector.size() == pos + 1)
			return; /* sql statement like: "select * from tb;". */
		if (!hasGroupBy && !hasOrderBy)
			pos = buildWhereClauseFrom(sql_vector, o, s, pos);
	}
	else // intoFile == true
	{
		sql_type = 17;

		unsigned int pos = 1;

		bool fromIsFirst = true;

		while (true)
		{
			if (sql_vector[pos] == "*")
			{
				attrFilter.push_back("*");
				pos++;
				if (to_lower(sql_vector[pos]) == "into")
					fromIsFirst = false;
				break;
			}
			else
			{
				attrFilter.push_back(sql_vector[pos++]);
				if (to_lower(sql_vector[pos]) == "from") break;
				else if (to_lower(sql_vector[pos]) == "into")
				{
					fromIsFirst = false;
					break;
				}
				pos++;
			}
		}
		if (fromIsFirst)
		{
			pos++; // from -> [table_name]
			tb_name = sql_vector[pos];
			pos++; // [table_name] -> ( ; / where / into )
			if (sql_vector.size() == pos + 1)
				return; /* sql statement like: "select * from tb;" */
			else if (to_lower(sql_vector[pos]) == "where")
				pos = buildWhereClauseFrom(sql_vector, o, s, pos);
				/* sql statement like: "select ... from [...] where [...]" */
			else if (to_lower(sql_vector[pos]) == "into")
			{
				pos++;	//	into -> [file_name]
				fileName = sql_vector[pos];

				if (fileName.front() == '\'') fileName.erase(0);
				if (fileName.back() == '\'') fileName.pop_back();

				pos++;	//	[file_name] -> ( ; / where )
				if (sql_vector.size() == pos + 1)
					return; /* sql statement like: "select ... from ... into ...;" */
				else if (to_lower(sql_vector[pos]) == "where")
					pos = buildWhereClauseFrom(sql_vector, o, s, pos);
					/* sql statement like: "select ... from [...] into [...] where [...]" */
			}
		}
		else // FROM goes after INTO
		{
			pos += 2; // into-> outfile -> [file_name]
			fileName = sql_vector[pos];

			if (fileName.front() == '\'') fileName.erase(0, 1);
			if (fileName.back() == '\'') fileName.pop_back();

			pos += 2; // [file_name] -> from -> [[table_name]
			tb_name = sql_vector[pos];
			pos++;	//	[tb_name] -> ( ; / where )
			if (sql_vector.size() == pos + 1)
				return; /* sql statement like: "select * into ... from ...;". */
			pos = buildWhereClauseFrom(sql_vector, o, s, pos);

		}
	}
}

SQLSelect::~SQLSelect()
{
	for (auto i : s)
		delete std::get<2>(i);
}

/* ---------------- SQLDelete ---------------- */
SQLDelete::SQLDelete(vector<string> sql_vector) { Parse(sql_vector); }

string SQLDelete::get_tb_name() { return tb_name; }


void SQLDelete::Parse(vector<string> sql_vector)
{
	sql_type = 8;
	unsigned int pos = 2;
	tb_name = sql_vector[pos];
	pos++;

	if (sql_vector.size() == pos + 1) return; /* sql statement like: "delete from tb;". */
	pos = buildWhereClauseFrom(sql_vector, o, s, pos);
}

SQLDelete::~SQLDelete()
{
	for (auto i : s)
		delete std::get<2>(i);
}

/* ---------------  SQLUpdate ----------------*/
SQLUpdate::SQLUpdate(vector<string> sql_vector) { Parse(sql_vector); }

string SQLUpdate::get_tb_name() { return tb_name; }

void SQLUpdate::Parse(vector<string> sql_vector)
{
	sql_type = 9;
	unsigned int pos = 1;
	if (sql_vector.size() <= 1) return;
	tb_name = sql_vector[pos];
	pos += 2;

	while (true)
	{
		attrNames.push_back(sql_vector[pos]);
		pos += 2;
		vals.push_back(stringToValue(sql_vector[pos]));
		//vals.back()->print(cout << "[debug] ") << " " << sql_vector[pos] << endl;
		pos++;

		if (sql_vector[pos] == ",") pos++;
		else if (to_lower(sql_vector[pos]) == "where") break;
	}
	pos = buildWhereClauseFrom(sql_vector, o, s, pos);
}

SQLUpdate::~SQLUpdate()
{
	for (auto i : s)
		delete std::get<2>(i);
}

