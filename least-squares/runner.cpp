#include "least_squares.h"
#include <stdio.h>
#include <iostream>
using namespace std;
using namespace linear_regression_practice;


int main(int argc, char **argv)
{
	least_squares ls;
	least_squares::residual_list rl(4);
	rl[0] = { .y = 8.7, .x { 0.5 } };
	rl[1] = { .y = 7.5, .x { 0.8 } };
	rl[2] = { .y = 7.1, .x { 1.1 } };
	rl[3] = { .y = 6.8, .x { 1.5 } };
	ls.solve(rl);

	system("pause");
	return 0;
}
