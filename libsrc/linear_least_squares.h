#pragma once
#include "equation_matrix.h"
#include <vector>


class linear_least_squares
{
public:
	struct residual
	{
		double y;
		std::vector<double> x;
	};

	typedef std::vector<std::vector<double>> matrix;

	typedef std::vector<residual> residual_list;
	typedef std::vector<double> parameter_vector;

public:
	linear_least_squares();
	virtual ~linear_least_squares();

	equation_matrix make_linear_system(const residual_list& residuals) const;
	parameter_vector solve(const residual_list& residuals) const;
};
