#include "Table.h"
#include <algorithm>
#include <utility>


using std::endl;
using std::pair;
using std::make_pair;

bool cmp(const pair<ValueBase *, int> & l, const pair<ValueBase *, int> & r)
{
	return *(l.first) < *(r.first);
}



ostream & PrintableTable::print(ostream & out, bool isCOUT) const
{
	if (data.empty()) return out;
	int n = attrs.size();
	if (isCOUT){
		for (int i = 0; i < n; i++) out << attrs[i].name << "\t";
		out << endl;
	}
	for (auto & j : data)
	{
		for (int i = 0; i < n; i++)
		{
			if (j[i]) 
				out << (*j[i]);
			else 
				out << "NULL";

			out << "\t";
		}
		out << endl;
	}
	return out;
}

PrintableTable::~PrintableTable()
{
	int n = attrs.size();
	for (auto item : data)
	{
		for (int j = 0; j < n; j++)
		{
			delete item[j];
		}
		delete[] item;
	}
	data.clear();
}

ostream & PrintableTable::orderprint(ostream & out, string orderbywhat) const
{
	if (data.empty()) return out;

	int n = attrs.size();
	int pos = -1;
	for (int i = 0; i < n; i++)
	{
		if (attrs[i].name == orderbywhat)
		{
			pos = i;
			break;
		}
	}
	int m = 0;
	vector<pair<ValueBase *, int>> tmp;
	for (auto & j : data)
	{
		auto p = make_pair(j[pos], m);
		tmp.push_back(p);
		m++;
	}
	sort(tmp.begin(), tmp.end(), cmp);
	for (int i = 0; i < n; i++) out << attrs[i].name << "\t";
	out << endl;
	for (auto & j : tmp)
	{
		for (int i = 0; i < n; i++)
		{
			if (data[j.second][i]) out << (*data[j.second][i]);
			else out << "NULL";
			out << "\t";
		}
		out << endl;
	}
	return out;
}

ostream & PrintableTable::countprint(ostream & out, string countwhat) const
{
	if (data.empty())
	{
		out << "COUNT(" << countwhat << ")" << endl;
		out << 0 << endl;
		return out;
	}
	int count = 0;
	int pos = -1;
	int n = attrs.size();
	for (int i = 0; i < n; i++)
	{
		if (attrs[i].name == countwhat || countwhat == "*")
		{
			pos = i;
			break;
		}
	}
	if (pos == -1)
	{
		out << "COUNT(" << countwhat << ")" << endl;
		out << 0 << endl;
		return out;
	}
	if (countwhat == "*")
	{
		for (auto & j : data)
		{
			count++;
		}
		out << "COUNT(" << countwhat << ")" << endl;
		out << count << endl;
		return out;
	}
	else
	{
		for (auto & j : data)
		{
			if (j[pos])
			{
				count++;
			}
		}
		out << "COUNT(" << countwhat << ")" << endl;
		out << count << endl;
		return out;
	}
}

ostream & PrintableTable::groupprint(ostream & out, bool hasCount, string countwhat, vector<string> groupbywhat, bool hasOrderBy, string orderbywhat) const
{
	if (data.empty()) return out;
	int n = attrs.size();
	vector<int> groupbypos;
	vector<int> count;
	vector<pair<vector<ValueBase *>, pair<int, bool>>> tmp;
	for (auto & j : groupbywhat)
	{
		for (int i = 0; i < n; i++)
		{
			if (attrs[i].name == j)
			{
				groupbypos.push_back(i);
				break;
			}
		}
	}
	int m = 0;
	for (auto & j : data)
	{
		vector<ValueBase *> gbw;
		for (size_t i = 0; i < groupbypos.size(); i++)
		{
			gbw.push_back(j[groupbypos[i]]);
		}
		auto p1 = make_pair(m, true);
		auto p2 = make_pair(gbw, p1);
		tmp.push_back(p2);
		m++;
	}
	for (int i = 0; i < m; i++)
	{
		count.push_back(1);
	}
	for (auto & j : tmp)
	{
		for (int i = 0; i < j.second.first; i++)
		{
			bool theSame = true;
			for (size_t k = 0; k < tmp[i].first.size(); k++)
			{
				if (!(*(tmp[i].first[k]) == *(j.first[k])))
				{
					theSame = false;
					break;
				}
			}
			if (theSame)
			{
				j.second.second = false;
				count[i]++;
			}
		}
	}
	if (hasOrderBy == false)
	{
		if (hasCount == false)
		{
			for (int i = 0; i < n; i++) 
				out << attrs[i].name << "\t";
			out << endl;
			for (auto & j : tmp)
			{
				if (j.second.second == true)
				{
					for (int i = 0; i < n; i++)
					{
						if (data[j.second.first][i]) 
							out << (*data[j.second.first][i]);
						else 
							out << "NULL";
						out << "\t";
					}
					out << endl;
				}

			}
		}
		else
		{
			for (int i = 0; i < n; i++) out << attrs[i].name << "\t";
			out << "COUNT(" << countwhat << ")" << "\t";
			out << endl;
			if (countwhat == "*")
			{
				for (auto & j : tmp)
				{
					if (j.second.second == true)
					{
						for (int i = 0; i < n; i++)
						{
							if (data[j.second.first][i]) out << (*data[j.second.first][i]);
							else out << "NULL";
							out << "\t";
						}
						out << count[j.second.first] << "\t";
						out << endl;
					}

				}
			}
			else
			{
				int countpos = -1;
				for (int i = 0; i < n; i++)
				{
					if (attrs[i].name == countwhat)
					{
						countpos = i;
						break;
					}
				}
				for (auto & j : tmp)
				{
					if (j.second.second == true)
					{
						for (int i = 0; i < n; i++)
						{
							if (data[j.second.first][i]) out << (*data[j.second.first][i]);
							else out << "NULL";
							out << "\t";
						}
						if (data[j.second.first][countpos])
						{
							out << count[j.second.first] << "\t";
						}
						else
						{
							out << 0 << "\t";
						}
						out << endl;
					}
				}
			}
		}
	}
	else
	{
		if (hasCount == false)
		{
			int orderpos = 0;
			for (int i = 0; i < n; i++)
			{
				if (attrs[i].name == orderbywhat)
				{
					orderpos = i;
					break;
				}
			}
			int o = 0;
			vector<pair<ValueBase *, int>> ordertmp;
			for (auto & j : data)
			{
				auto p = make_pair(j[orderpos], o);
				ordertmp.push_back(p);
				o++;
			}
			sort(ordertmp.begin(), ordertmp.end(),cmp);
			for (int i = 0; i < n; i++) out << attrs[i].name << "\t";
			out << endl;
			for (auto & j : ordertmp)
			{
				if (tmp[j.second].second.second)
				{
					for (int i = 0; i < n; i++)
					{
						if (data[j.second][i]) out << (*data[j.second][i]);
						else out << "NULL";
						out << "\t";
					}
				}
				out << endl;
			}
		}
		else
		{
			if (orderbywhat == "COUNT")
			{
				for (int i = 0; i < n; i++) out << attrs[i].name << "\t";
				out << "COUNT(" << countwhat << ")" << "\t";
				out << endl;
				if (countwhat == "*")
				{
					int o = 0;
					vector<pair<int, int>> ordertmp;
					for (auto & j : count)
					{
						auto p = make_pair(j, o);
						ordertmp.push_back(p);
						o++;
					}
					sort(ordertmp.begin(), ordertmp.end());
					for (auto & j : ordertmp)
					{
						if (tmp[j.second].second.second)
						{
							for (int i = 0; i < n; i++)
							{
								if (data[j.second][i]) out << (*data[j.second][i]);
								else out << "NULL";
								out << "\t";
							}
							out << count[j.second] << "\t";
							out << endl;
						}
					}
				}
				else
				{
					int countpos = -1;
					for (int i = 0; i < n; i++)
					{
						if (attrs[i].name == countwhat)
						{
							countpos = i;
							break;
						}
					}
					int o = 0;
					vector<pair<int, int>> ordertmp;
					for (auto & j : tmp)
					{
						if (data[j.second.first][countpos])
						{
							auto p = make_pair(count[j.second.first], o);
							ordertmp.push_back(p);
						}
						else
						{
							auto p = make_pair(0, o);
							ordertmp.push_back(p);
						}
						o++;
					}
					sort(ordertmp.begin(), ordertmp.end());
					for (auto & j : ordertmp)
					{
						if (tmp[j.second].second.second)
						{
							for (int i = 0; i < n; i++)
							{
								if (data[j.second][i]) out << (*data[j.second][i]);
								else out << "NULL";
								out << "\t";
							}
							if (data[j.second][countpos])
							{
								out << count[j.second] << "\t";
							}
							else
							{
								out << 0 << "\t";
							}
						}
						out << endl;
					}
				}
			}
			else
			{
				for (int i = 0; i < n; i++) out << attrs[i].name << "\t";
				out << "COUNT(" << countwhat << ")" << "\t";
				out << endl;
				int orderpos = 0;
				for (int i = 0; i < n; i++)
				{
					if (attrs[i].name == orderbywhat)
					{
						orderpos = i;
						break;
					}
				}
				int o = 0;
				vector<pair<ValueBase *, int>> ordertmp;
				for (auto & j : data)
				{
					auto p = make_pair(j[orderpos], o);
					ordertmp.push_back(p);
					o++;
				}
				sort(ordertmp.begin(), ordertmp.end(),cmp);
				if (countwhat == "*")
				{
					for (auto & j : ordertmp)
					{
						if (tmp[j.second].second.second)
						{
							for (int i = 0; i < n; i++)
							{
								if (data[j.second][i]) out << (*data[j.second][i]);
								else out << "NULL";
								out << "\t";
							}
							out << count[j.second] << "\t";
						}
						out << endl;
					}
				}
				else
				{
					int countpos = -1;
					for (int i = 0; i < n; i++)
					{
						if (attrs[i].name == countwhat)
						{
							countpos = i;
							break;
						}
					}
					for (auto & j : ordertmp)
					{
						if (tmp[j.second].second.second)
						{
							for (int i = 0; i < n; i++)
							{
								if (data[j.second][i]) out << (*data[j.second][i]);
								else out << "NULL";
								out << "\t";
							}
							if (data[j.second][countpos])
								out << count[j.second] << "\t";
							else
								out << 0 << "\t";
						}
						out << endl;
					}
				}
			}
		}
	}
	return out;
}
