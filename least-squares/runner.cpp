#include "linear_least_squares.h"
#include <stdio.h>
#include <iostream>
using namespace std;


int main(int argc, char **argv)
{
	linear_least_squares ls;
	linear_least_squares::residual_list rl(4);
	rl[0] = { .y = 8.7, .x { 0.5 } };
	rl[1] = { .y = 7.5, .x { 0.8 } };
	rl[2] = { .y = 7.1, .x { 1.1 } };
	rl[3] = { .y = 6.8, .x { 1.5 } };
	linear_least_squares::parameter_vector pv = ls.solve(rl);

	printf("---------\n");
	printf("residuals :\n");
	for(size_t i=0; i<rl.size(); i++)
	{
		printf("no.%2u - y:%lf", (int)i+1, rl[i].y);
		for(size_t j=0; j<rl[i].x.size(); j++)
			printf(", x%u:%lf", (int)j+1, rl[i].x[j]);
		printf("\n");
	}
	printf("parameters :\n");
	for(size_t i=0; i<pv.size(); i++)
	{
		printf("w%u:%lf", (int)i, pv[pv.size() - i - 1]);
		if(i+1 >= pv.size()) break;
		printf(", ");
	}
	printf("\n");
	printf("---------\n");

	system("pause");
	return 0;
}
