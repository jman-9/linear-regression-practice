#include "linear_least_squares.h"
#include "../linear-system/linear_system.h"
using namespace std;



linear_least_squares::linear_least_squares()
{
}

linear_least_squares::~linear_least_squares()
{
}

linear_least_squares::parameter_vector linear_least_squares::solve(const residual_list& residuals) const
{
	if(residuals.empty()) return {};

	matrix mbase;

	mbase.resize(residuals.size());
	for(auto& c : mbase)
		c.resize(1 + 1 + residuals[0].x.size());

	size_t i, j, k;
	for(i=0; i<residuals.size(); i++)
	{
		const residual& re = residuals[i];
		j = 0;
		for(auto& x : re.x)
		{
			mbase[i][j++] = -x;
		}
		mbase[i][j++] = -1;
		mbase[i][j++] = re.y;
	}

	linear_system::equation_matrix em;
	em.resize((int)mbase[0].size() - 1, (int)mbase[0].size());

	for(i=0; i<mbase[0].size()-1; i++)
	{
		for(j=0; j<residuals.size(); j++)
		{
			double scalar = mbase[j][i];
			for(k=0; k<mbase[j].size(); k++)
			{
				em[i][k] += mbase[j][k] * scalar;
			}
		}
	}

	linear_system ls;
	linear_system::solution_vector sv = ls.solve(em);
	return sv;	// auto conversion
}
