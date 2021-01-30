#include "linear_system.h"
#include <stdio.h>
#include <iostream>
using namespace std;


int main(int argc, char **argv)
{
	linear_system ls;

	linear_system::equation eq1{2, 3, 2};
	linear_system::equation eq2{5, 4, 1};


	linear_system::solution sol = ls.solve(eq1, eq2);

	printf("x{%d/%d}, y{%d/%d}\n", sol.x.num, sol.x.den, sol.y.num, sol.y.den );


	system("pause");

	return 0;
}
