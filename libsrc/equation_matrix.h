#pragma once
#include <vector>


typedef std::vector<double> equation_vector;

class equation_matrix
{
public:
	equation_matrix(int rows = 0, int cols = 0);
	virtual ~equation_matrix();

	void resize(int rows, int cols);
	void reduce(int reduce_rows, int reduce_cols);

	size_t varcnt() const;
	size_t rows() const;
	size_t cols() const;

	double& get(int row, int col);
	void set(int row, int col, double v);

	std::vector<double>& operator[](size_t idx);

protected:
	std::vector<equation_vector> _matrix;
};
