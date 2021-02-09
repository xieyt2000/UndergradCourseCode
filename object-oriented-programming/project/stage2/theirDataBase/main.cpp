#include<iostream>
#include"Interpreter.h"
using namespace std;

int main()
{
#ifdef ARCHIVE_TEST
	bool readFromFile, validInput = false;
	while (!validInput)
	{
		string tmp;
		cout << "Read From previous archiev files? (Y/N)";
		getline(cin, tmp);
		validInput = true;
		if (to_lower(tmp) == "y")
			readFromFile = true;
		else if (to_lower(tmp) == "n")
			readFromFile = false;
		else
		{
			cout << "INVALID INPUT." << endl;
			validInput = false;
		}
	}

	Interpreter interpreter(readFromFile);
#else	//
	Interpreter interpreter;
#endif // ARCHIVE_TEST

	char * sqlsentence = new char[1024];
	while (true)
	{
		cin.getline(sqlsentence, 1024);
		if (!cin) break;
		interpreter.SQL(sqlsentence);
	}
	//cout << (Value<int>(4) == Value<double>(4.0)) << endl;
	delete[] sqlsentence;
	return 0;
}

