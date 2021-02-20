#include "ridge_regression.h"
using residual_list = linear_least_squares::residual_list;
using solution_vector = linear_system::solution_vector;


ridge_regression::ridge_regression()
{}

ridge_regression::~ridge_regression()
{}

solution_vector ridge_regression::solve(const residual_list& rl, double lambda /*= 1.0*/) const
{
	linear_system les;
	linear_least_squares ls;
	equation_matrix em;

	em = ls.make_linear_system(rl);
	//applying L2-norm for regularizing
	for(size_t i=0; i<em.varcnt() - 1; i++)
	{
		em[i][i] += lambda; // controller
	}

	return les.solve(em);
}
