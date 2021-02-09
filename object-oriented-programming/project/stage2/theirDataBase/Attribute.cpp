#include "Attribute.h"
#include <iostream>

std::ostream & operator<<(std::ostream & out, AttributeType attp)
{
	switch (attp)
	{
	case ATTR_INT:
		out << "INT";
		break;
	case ATTR_CHAR:
		out << "CHAR";
		break;
	case ATTR_DOUBLE:
		out << "DOUBLE";
		break;
	case ATTR_DATE:
		out << "DATE";
		break;
	case ATTR_TIME:
		out << "TIME";
		break;
	case ATTR_DATETIME:
		out << "DATETIME";
		break;
	default:
		break;
	}

	return out;
}

AttributeType fromStringToAttrType(const string & s)
{
	if (s == "INT")
		return ATTR_INT;
	else if (s == "CHAR")
		return ATTR_CHAR;
	else if (s == "DOUBLE")
		return ATTR_DOUBLE;
	else if (s == "DATE")
		return ATTR_DATE;
	else if (s == "TIME")
		return ATTR_TIME;
	else if (s == "DATETIME")
		return ATTR_DATETIME;
	else
	{
		std::cerr << "Error from Attribute.cpp::fromStringToAttrType(const string &): " << std::endl;
		std::cerr << "\tInvalid AttributeType name. Check if it is UPPER case and is one of INT, CHAR and DOUBLE." << std::endl;
		return ATTR_INT;
	}
}