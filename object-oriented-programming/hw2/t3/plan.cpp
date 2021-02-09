#include"plan.h"
Plan::Plan() :day(0), month(0), todo("null") {}
Plan::Plan(int a, int b, std::string s) : month(a), day(b), todo(s) {}