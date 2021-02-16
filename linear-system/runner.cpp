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
	printf("---------\n");
	printf("problem :\n");
	printf("%dx + %dy + %d = 0\n", 2, 3, 2);
	printf("%dx + %dy + %d = 0\n", 5, 4, 1);
	printf("solution :\n");
	printf("x=%d/%d, y=%d/%d\n", sol.x.num, sol.x.den, sol.y.num, sol.y.den );
	printf("---------\n");

	linear_system::equation_matrix mat(2, 3);
	mat[0][0] = 2;
	mat[0][1] = 3;
	mat[0][2] = 2;
	mat[1][0] = 5;
	mat[1][1] = 4;
	mat[1][2] = 1;
	linear_system::solution_vector s1 = ls.solve(mat);
	printf("---------\n");
	printf("problem :\n");
	for(size_t i=0; i<mat.varcnt(); i++)
		printf("%dx + %dy + %d = 0\n", (int)mat[i][0], (int)mat[i][1], (int)mat[i][2]);
	printf("solution :\n");
	printf("x=%.6lf, y=%.6lf\n", s1[0], s1[1]);
	printf("---------\n");

	mat.resize(3, 4);
	mat[0][0] = 1;
	mat[0][1] = 1;
	mat[0][2] = 1;
	mat[0][3] = 1;
	mat[1][0] = 1;
	mat[1][1] = 2;
	mat[1][2] = 3;
	mat[1][3] = 4;
	mat[2][0] = 2;
	mat[2][1] = 1;
	mat[2][2] = 2;
	mat[2][3] = 3;
	linear_system::solution_vector s2 = ls.solve(mat);
	printf("---------\n");
	printf("problem :\n");
	for(size_t i=0; i<mat.varcnt(); i++)
		printf("%dx + %dy + %dz + %d = 0\n", (int)mat[i][0], (int)mat[i][1], (int)mat[i][2], (int)mat[i][3]);
	printf("solution :\n");
	printf("x=%.6lf, y=%.6lf z=%.6lf\n", s2[0], s2[1], s2[2]);
	printf("---------\n");

	system("pause");

	return 0;
}
