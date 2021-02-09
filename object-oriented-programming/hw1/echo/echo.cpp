#include <iostream>
#include <cstring>
using namespace std;
int main(int argc, char** argv)
{
	char order[100] = "";
	for (int i = 1; i < argc; i++)
	{
		strcat(order, argv[i]);
		strcat(order, " ");
	}
	int len = strlen(order);
	order[len - 1] = 0;
	char type[5] = "d";
	int TextStart = 0;
	if (order[0] == '-')
	{
		for (int i = 1; order[i] != ' '; i++)
		{
			if (order[i] == 'n' || order[i] == 'e' || order[i] == 'E')
			{
				type[i - 1] = order[i];
				TextStart = i + 2;
			}
			else
			{
				strcpy(type, "d");
				TextStart = 0;
				break;
			}
		}
	}
	int Type = 0;
	for (int i = 0; i < 5; i++)
	{
		if (order[i] == 'n') Type++;
		if (order[i] == 'e') Type += 10;
		if (order[i] == 'E') Type += 100;
	}
	if (Type == 0 || Type == 100)
	{
		for (int i = TextStart; order[i] != 0; i++)
		{
			if (order[i] == ' ')
			{
				if (order[i + 1] == ' ') continue;
			}
			cout << order[i];
		}
		cout << endl;
		return 0;
	}


	if (Type == 1 || Type == 101)
	{
		for (int i = TextStart; order[i] != 0; i++)
		{
			if (order[i] == ' ')
			{
				if (order[i + 1] == ' ') continue;
			}
			if (order[i] == '"') continue;
			cout << order[i];
		}
		return 0;
	}
	if (Type == 10)
	{
		for (int i = TextStart; order[i] != 0; i++)
		{
			if (order[i] == '"') continue;
			if (order[i] == '\\')
			{
				bool valid = 0;
				if (order[i + 1] == 'a')
				{
					cout << '\a';
					valid = 1;
				}
				if (order[i + 1] == 'b')
				{
					cout << '\b';
					valid = 1;
				}
				if (order[i + 1] == 'c')
				{
					return 0;
				}
				if (order[i + 1] == 'e')
				{
					cout << '\x1B';
					valid = 1;
				}
				if (order[i + 1] == 'E')
				{
					cout << '\x1B';
					valid = 1;
				}
				if (order[i + 1] == 'f')
				{
					cout << '\f';
					valid = 1;
				}
				if (order[i + 1] == 'n')
				{
					cout << '\n';
					valid = 1;
				}
				if (order[i + 1] == 'r')
				{
					cout << '\r';
					valid = 1;
				}
				if (order[i + 1] == 't')
				{
					cout << '\t';
					valid = 1;
				}
				if (order[i + 1] == 'v')
				{
					cout << '\v';
					valid = 1;
				}
				if (valid)
				{
					i++;
					continue;
				}
			}
			cout << order[i];
		}
		cout << endl;
		return 0;
	}
	if (Type == 11)
	{
		for (int i = TextStart; order[i] != 0; i++)
		{
			if (order[i] == '"') continue;
			if (order[i] == '\\')
			{
				bool valid = 0;
				if (order[i + 1] == 'a')
				{
					cout << '\a';
					valid = 1;
				}
				if (order[i + 1] == 'b')
				{
					cout << '\b';
					valid = 1;
				}
				if (order[i + 1] == 'c')
				{
					return 0;
				}
				if (order[i + 1] == 'e')
				{
					cout << '\x1B';
					valid = 1;
				}
				if (order[i + 1] == 'E')
				{
					cout << '\x1B';
					valid = 1;
				}
				if (order[i + 1] == 'f')
				{
					cout << '\f';
					valid = 1;
				}
				if (order[i + 1] == 'n')
				{
					cout << '\n';
					valid = 1;
				}
				if (order[i + 1] == 'r')
				{
					cout << '\r';
					valid = 1;
				}
				if (order[i + 1] == 't')
				{
					cout << '\t';
					valid = 1;
				}
				if (order[i + 1] == 'v')
				{
					cout << '\v';
					valid = 1;
				}
				if (valid)
				{
					i++;
					continue;
				}
			}
			cout << order[i];
		}
		return 0;
	}

	return 0;
}

