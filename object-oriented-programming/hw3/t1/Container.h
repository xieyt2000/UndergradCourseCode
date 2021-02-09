#ifndef CONTAINER_H
#define CONTAINER_H
#include "BasicContainer.h"
#include <vector>
#include <iostream>
#include <algorithm>
#include <map>
#include <string>
using std::vector;
using std::map;
using std::string;
template<class A>
struct Point {
    Pos pos;
    A value;
    Point (Pos p, A v): pos(p), value(v) {}
	//my code below
	bool operator < (const Point& x) const {
		return (pos < x.pos);
	}
};
//my code below
template<class A>
const bool cmp(const Point<A>& pt, const Pos& ps) {
	return (pt.pos < ps);
}
template<class A, class C>
class Container : public BasicContainer<A> {
public:
    void insert(const Pos &p, const A &v) {};
    A* find(Pos p) { return NULL; };
};

template <class A>
class Container<A, vector<A> > : public BasicContainer<A> {
    vector< Point<A> > base;
	bool findBegain = false;//my code
public:
    void insert(const Pos &p, const A &v) {
        base.push_back(Point<A>(p, v));
    }

    A* find(Pos p) {
		//my code below
		if (findBegain == false) {
			sort(base.begin(), base.end());
			findBegain = true;
		}
		auto t = lower_bound(base.begin(), base.end(), p, cmp<A>);
		if (t->pos == p) return &(t->value);
		//end my code
        /*for(auto t = base.begin(); t != base.end(); ++t) {
            if(p == t->pos) return &(t->value);
        }*/		//ori code
        return NULL;
    }
};
//my code below
template <class A>
class Container<A, map<Pos,A> > : public BasicContainer<A> {
	map<Pos, A> base;
public:
	void insert(const Pos& p, const A& v) {
		base[p] = v;
	}
	A* find(Pos p) {
		auto t = base.find(p);;
		if (t == base.end()) return NULL;
		return &(t->second);
	}
};
#endif

