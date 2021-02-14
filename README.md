# Practice of Linear Regression


# Objectives
- implementing a solution of linear regression problem for C++
- ...

# Needs
- ~~partial derivative~~
- ~~system of linear equations~~
- ~~linear least squares method~~
- regularization
- ...
  
# Achieved
- system of linear equations
- linear least squares method
- ...
  
# Usage of linear_system
## Code
```C++
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
for(int i=0; i<mat.varcnt(); i++)
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
for(int i=0; i<mat.varcnt(); i++)
  printf("%dx + %dy + %dz + %d = 0\n", (int)mat[i][0], (int)mat[i][1], (int)mat[i][2], (int)mat[i][3]);
printf("solution :\n");
printf("x=%.6lf, y=%.6lf z=%.6lf\n", s2[0], s2[1], s2[2]);
printf("---------\n");
```
## Result
```
---------
problem :
2x + 3y + 2 = 0
5x + 4y + 1 = 0
solution :
x=-5/-7, y=-8/7
---------
---------
problem :
2x + 3y + 2 = 0
5x + 4y + 1 = 0
solution :
x=0.714286, y=-1.142857
---------
---------
problem :
1x + 1y + 1z + 1 = 0
1x + 2y + 3z + 4 = 0
2x + 1y + 2z + 3 = 0
solution :
x=0.000000, y=1.000000 z=-2.000000
---------
```
  
  
# Usage of linear_least_squares
## Code
```C++
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
```
## Result
```
---------
residuals :
no. 1 - y:8.700000, x1:0.500000
no. 2 - y:7.500000, x1:0.800000
no. 3 - y:7.100000, x1:1.100000
no. 4 - y:6.800000, x1:1.500000
parameters :
w0:9.283562, w1:-1.803653
---------
```
