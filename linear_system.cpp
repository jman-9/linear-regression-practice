#include "linear_system.h"


static int gcd(int a, int b){
	while(b!=0){
		int r = a%b;
		a= b;
		b= r;
	}
	return a;
}

static int lcm(int a, int b){
    return a * b / gcd(a,b);
}


void linear_system::equation::mul(int sk)
{
	xc *= sk;
	yc *= sk;
	k *= sk;
}

void linear_system::equation::subt(equation rhs)
{
	xc -= rhs.xc;
	yc -= rhs.yc;
	k -= rhs.k;
}


linear_system::linear_system()
{
}

linear_system::~linear_system()
{
}

linear_system::solution linear_system::solve(equation eq1, equation eq2)
{
	equation xeq1 = eq1, xeq2 = eq2;
	int xlcm = lcm(xeq1.xc, xeq2.xc);
	int xeq1m = xlcm / xeq1.xc;
	int xeq2m = xlcm / xeq2.xc;
	xeq1.mul(xeq1m);
	xeq2.mul(xeq2m);
	equation yeq = xeq1;
	yeq.subt(xeq2);

	equation yeq1 = eq1, yeq2 = eq2;
	int ylcm = lcm(yeq1.yc, yeq2.yc);
	int yeq1m = ylcm / yeq1.yc;
	int yeq2m = ylcm / yeq2.yc;
	yeq1.mul(yeq1m);
	yeq2.mul(yeq2m);
	equation xeq = yeq1;
	xeq.subt(yeq2);

	return solution{{-xeq.k, xeq.xc}, {-yeq.k, yeq.yc}};
}
