#pragma once
#include "../linear-system/linear_system.h"
#include "../least-squares/linear_least_squares.h"


class ridge_regression
{
public:
	ridge_regression();
	virtual ~ridge_regression();

	linear_system::solution_vector solve(const linear_least_squares::residual_list& rl, double lambda = 1.0) const;
};
