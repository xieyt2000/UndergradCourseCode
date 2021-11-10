// predict.cc
// This file contains the main function.  The program accepts a single
// parameter: the name of a trace file.  It drives the branch predictor
// simulation by reading the trace file and feeding the traces one at a time
// to the branch predictor.

#include <stdio.h>
#include <stdlib.h>
#include <string.h> // in case you want to use e.g. memset
#include <assert.h>

#include "branch.h"
#include "trace.h"

#include "branch_predictor.h"

#define DEBUG 0

int main(int argc, char *argv[])
{

	// make sure there is one parameter

	if (argc != 2)
	{
		fprintf(stderr, "Usage: %s <filename>.gz\n", argv[0]);
		exit(1);
	}

	// open the trace file for reading

	init_trace(argv[1]);

	// initialize competitor's branch prediction code
	branch_predictor_init();

	// some statistics to keep, currently just for conditional branches

	long long int
		tmiss = 0, // number of target mispredictions
		dmiss = 0; // number of direction mispredictions
	long long cnt = 0;
	// keep looping until end of file

	for (;;)
	{
		// get a trace

		trace *t = read_trace();

		// NULL means end of file

		if (!t)
			break;

		if (t->bi.br_flags & BR_CONDITIONAL)
		{
			// x86 是变长指令集，人为将不跳转的指令 target 设置为 pc + 4
			if (!t->taken)
				t->target = t->bi.address + 4;

			uint32_t target = get_from_branch_predictor(t->bi.address);
			bool taken = (target != t->bi.address + 4);
			// count a direction misprediction
			dmiss += taken != t->taken;
			// count a target misprediction
			tmiss += target != t->target;
			cnt++;
			branch_predictor_update(t->bi.address, t->target);
#if DEBUG
			if (cnt < 100)
				printf("0x%x, %d, %d, 0x%x, 0x%x\n", t->bi.address, t->taken, taken, t->target, target);
#endif
		}
	}

	// done reading traces

	end_trace();

	// give final mispredictions per kilo-instruction and exit.
	// each trace represents exactly 100 million instructions.

	printf("tot instructions = %lld, dmiss rate = %0.3f, tmiss rate = %0.3f\n", cnt, (1. * dmiss) / cnt, (1. * tmiss) / cnt);
	branch_predictor_release();
	exit(0);
}
