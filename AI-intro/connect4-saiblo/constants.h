#pragma once
#include <ctime>

//choose strategy by macro
//#define NODE_NOT_FULL	//throws exception when node pool is full. Don't enable
//use time limit when releasing and count limit when debugging. (time can't be used under debugger)
#define USE_TIME_LIMIT
//#define USE_COUNT_LIMIT
#define USE_GUIDED_POLICY


//enum
static int USER = 1;
static int MACHINE = 2;

//infinity
static const double DOB_INF = 1e300;
static const double DOB_NEG_INF = -DOB_INF;
static int BIG_INT = (int)1000;

// limit
static const int MAX_M = 12;
static const int MAX_N = 12;
static const int MIN_M = 0;
static const int MIN_N = 9;
static const int MAX_NODE = (int)2.6e6;
static clock_t TIME_LIMIT = 2.5 * CLOCKS_PER_SEC;
static const int COUNT_LIME = (int)1e6;

// hyper-parameter
static const double UCB_EXPLOR = 1;	//'c' in ucb