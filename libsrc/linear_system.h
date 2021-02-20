#pragma once
#include "equation_matrix.h"
#include <vector>


class linear_system
{
public:
	struct fraction
	{
		int num;
		int den;
	};

	typedef std::vector<double> solution_vector;

	struct equation
	{
		int xc;
		int yc;
		int k;

		void mul(int sk);
		void subt(equation rhs);
	};

	struct solution
	{
		fraction x, y;
	};

public:
	linear_system();
	virtual ~linear_system();

	solution solve(equation eq1, equation eq2) const;
	solution_vector solve(equation_matrix problem) const;

protected:
	equation_vector find_equation(equation_vector e1, equation_vector e2) const;
};
