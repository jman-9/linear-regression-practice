#pragma once
#include <vector>


class linear_system
{
public:
	struct fraction
	{
		int num;
		int den;
	};

	typedef std::vector<double> equation_vector;
	typedef std::vector<double> solution_vector;

	class equation_matrix
	{
	public:
		equation_matrix(int rows = 0, int cols = 0);
		virtual ~equation_matrix();

		void resize(int rows, int cols);
		void reduce(int reduce_rows, int reduce_cols);

		size_t varcnt() const;

		double& get(int row, int col);
		void set(int row, int col, double v);

		std::vector<double>& operator[](size_t idx);

	protected:
		std::vector<equation_vector> _matrix;
	};

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

	solution solve(equation eq1, equation eq2);
	solution_vector solve(equation_matrix problem);

protected:
	equation_vector find_equation(equation_vector e1, equation_vector e2);
};
