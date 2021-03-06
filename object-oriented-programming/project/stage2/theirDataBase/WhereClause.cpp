﻿// encodings=UTF-8
#include "WhereClause.h"
#include <stack>

bool WhereClause::test(const Record & r, const vector<Attribute> & va) const
{
	vector<bool> res;
	// 用lambda函数简化代码
	auto check = [](SubSentence s, const ValueBase * v, bool & flag, AttributeType tp) -> bool {
		ValueBase * sv = nullptr;
		ValueBase * nv = const_cast<ValueBase *>(v);
		if (tp == ATTR_CHAR)
		{
			sv = convert<string>(std::get<2>(s));
			v = convert<string>(const_cast<ValueBase *>(v));
		}
		else if (tp == ATTR_DOUBLE || tp == ATTR_INT)
		{
			sv = convert<double>(std::get<2>(s));
			v = convert<double>(const_cast<ValueBase *>(v));
		}
		else if (tp == ATTR_DATE)
		{
			sv = convert<Date>(std::get<2>(s));
			v = convert<Date>(const_cast<ValueBase *>(v));
		}
		else if (tp == ATTR_TIME)
		{
			sv = convert<Time>(std::get<2>(s));
			v = convert<Time>(const_cast<ValueBase *>(v));
		}
		else if (tp == ATTR_DATETIME)
		{
			sv = convert<DateTime>(std::get<2>(s));
			v = convert<DateTime>(const_cast<ValueBase *>(v));
		}

		if (std::get<1>(s) == ARITH_GREATER)
		{
			return v && *v > * sv;
		}
		else if (std::get<1>(s) == ARITH_LESS)
		{
			return v && *v < *sv;
		}
		else if (std::get<1>(s) == ARITH_EQUAL)
		{
			return v && *v == *sv;
		}
		else {/* undefined */ }
		flag = false;
		return false;
	};
	// 将每个子句转化为对应的判断结果
	for (auto & i : subsentences)
	{
		bool flag = true;
		bool result;
		for (size_t j = 0; j < va.size(); j++)
		{
			if (va[j].name == std::get<0>(i))
			{
				result = check(i, r[j], flag, va[j].type);
				if (!flag) return false;
				break;
			}
		}
		res.push_back(result);
	}
	if (res.size() == 0)
		return true;
	// 用逆波兰表达式对逻辑表达式求值，计算判断结果
	vector<bool> stack;
	stack.push_back(res[0]);
	int i = 1, j = 0, n = subsentences.size(), m = operation.size();
	for (; j < m; )
	{
// 将优先级高（rank较小）的一方（子句或运算符）入栈
		if (i < n && std::get<3>(subsentences[i]) < operation[j].second)
		{
			stack.push_back(res[i]);
			i++;
		}
		else
		{
			LogicOperation lo = operation[j].first;
			switch (lo)
			{
			case LOGIC_AND:
			{
				bool v1 = stack.back(); stack.pop_back();
				bool v2 = stack.back(); stack.pop_back();
				stack.push_back(v1 && v2);
				break;
			}
			case LOGIC_OR:
			{
				bool v1 = stack.back(); stack.pop_back();
				bool v2 = stack.back(); stack.pop_back();
				stack.push_back(v1 || v2);
				break;
			}
			case LOGIC_NOT:
			{
				bool v1 = stack.back(); stack.pop_back();
				stack.push_back(!v1);
				break;
			}
			case LOGIC_XOR:
			{
				bool v1 = stack.back(); stack.pop_back();
				bool v2 = stack.back(); stack.pop_back();
				stack.push_back(v1 ^ v2);
				break;
			}
			default:
				break;
			}
			j++;
		}
	}
	return stack[0];
}