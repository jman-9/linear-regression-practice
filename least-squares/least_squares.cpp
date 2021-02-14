#include "least_squares.h"
#include <vector>
using namespace linear_regression_practice;
using namespace std;



least_squares::least_squares()
{
}

least_squares::~least_squares()
{
}

void least_squares::solve(residual_list residuals)
{
	if(residuals.empty()) return;

	matrix mbase;
	matrix mcalc;

	mbase.resize(residuals.size());
	for(auto& c : mbase)
		c.resize(1 + 1 + residuals[0].x.size());

	size_t i, j;
	for(i=0; i<residuals.size(); i++)
	{
		residual& re = residuals[i];
		mbase[i][0] = re.y;
		mbase[i][1] = -1;

		j = 2;
		for(auto& x : re.x)
		{
			mbase[i][j++] = -x;
		}
	}

	for(i=1; i<mbase[0].size(); i++)
	{
		mcalc = mbase;
		for(j=0; j<residuals.size(); j++)
		{
			double k = mcalc[j][i];
			for(auto& v : mcalc[j])
			{
				v *= k;
			}
		}
		//mcalc sum
		// make equation matrix
	}

	// goto linear system
}
