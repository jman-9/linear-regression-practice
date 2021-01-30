#include "linear_system.h"
using namespace std;


static int calc_gcd(int a, int b){
	while(b!=0){
		int r = a%b;
		a= b;
		b= r;
	}
	return a;
}

static int calc_lcm(int a, int b){
    return a * b / calc_gcd(a,b);
}

static void calc_mul(linear_system::equation_vector& eq, double k)
{
	for(auto& v : eq)
		v *= k;
}

static void calc_div(linear_system::equation_vector& eq, double k)
{
	for(auto& v : eq)
		v /= k;
}

static void calc_subt(linear_system::equation_vector& eq1, const linear_system::equation_vector& eq2)
{
	size_t i;
	for(i=0; i<eq1.size(); i++)
		eq1[i] -= eq2[i];
}


linear_system::equation_matrix::equation_matrix(int rows /* = 0 */, int cols /* = 0 */)
{
	resize(rows, cols);
}

linear_system::equation_matrix::~equation_matrix()
{
}

void linear_system::equation_matrix::resize(int rows, int cols)
{
	_matrix.resize(rows);
	for(auto& r : _matrix)
	{
		r.resize(cols);
	}
}

void linear_system::equation_matrix::reduce(int reduce_rows, int reduce_cols)
{
	resize((int)_matrix.size() - reduce_rows, (int)_matrix[0].size() - reduce_cols);
}

size_t linear_system::equation_matrix::varcnt() const
{
	return _matrix.size();
}

double& linear_system::equation_matrix::get(int row, int col)
{
	return _matrix[row][col];
}

void linear_system::equation_matrix::set(int row, int col, double v)
{
	get(row, col) = v;
}

vector<double>& linear_system::equation_matrix::operator[](size_t idx)
{
	return _matrix[idx];
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

linear_system::equation_vector linear_system::find_equation(equation_vector e1, equation_vector e2)
{
	if(e1[0] != 0.0) calc_div(e1, e1[0]);
	if(e2[0] != 0.0) calc_div(e2, e2[0]);
	calc_subt(e1, e2);

	return equation_vector(e1.begin()+1, e1.end());
}

linear_system::solution linear_system::solve(equation eq1, equation eq2)
{
	equation xeq1 = eq1, xeq2 = eq2;
	int xlcm = calc_lcm(xeq1.xc, xeq2.xc);
	int xeq1m = xlcm / xeq1.xc;
	int xeq2m = xlcm / xeq2.xc;
	xeq1.mul(xeq1m);
	xeq2.mul(xeq2m);
	equation yeq = xeq1;
	yeq.subt(xeq2);

	equation yeq1 = eq1, yeq2 = eq2;
	int ylcm = calc_lcm(yeq1.yc, yeq2.yc);
	int yeq1m = ylcm / yeq1.yc;
	int yeq2m = ylcm / yeq2.yc;
	yeq1.mul(yeq1m);
	yeq2.mul(yeq2m);
	equation xeq = yeq1;
	xeq.subt(yeq2);

	return solution{{-xeq.k, xeq.xc}, {-yeq.k, yeq.yc}};
}


linear_system::solution_vector linear_system::solve(equation_matrix problem)
{
	solution_vector sol;

	int i, j;

	while(1)
	{
		equation_matrix finder = problem;
		for(i=(int)finder.varcnt()-1; i>0; i--)
		{
			equation_matrix calc(i, i);
			for(j=0; j<i; j++)
			{
				calc[j] = find_equation(finder[j], finder[j+1]);

				int a = 1;
			}
			finder = calc;
		}
		sol.insert( sol.begin(), -finder[0][1] / finder[0][0] );

		for(i=0; i<problem.varcnt(); i++)
		{
			auto& k = problem[i].back();
			auto& lv = *(&problem[i].back() - 1);
			lv = lv * sol.front() + k;
		}
		problem.reduce(1, 1);
		if(problem.varcnt() <= 1)
		{
			sol.insert( sol.begin(), -problem[0][1] / problem[0][0] );
			break;
		}
	}

	return sol;
}
