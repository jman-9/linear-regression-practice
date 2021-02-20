#include "equation_matrix.h"
using namespace std;




equation_matrix::equation_matrix(int rows /* = 0 */, int cols /* = 0 */)
{
	resize(rows, cols);
}

equation_matrix::~equation_matrix()
{
}

void equation_matrix::resize(int rows, int cols)
{
	_matrix.resize(rows);
	for(auto& r : _matrix)
	{
		r.resize(cols);
	}
}

void equation_matrix::reduce(int reduce_rows, int reduce_cols)
{
	resize((int)_matrix.size() - reduce_rows, (int)_matrix[0].size() - reduce_cols);
}

size_t equation_matrix::varcnt() const
{
	return _matrix.size();
}

size_t equation_matrix::rows() const
{
	return _matrix.size();
}

size_t equation_matrix::cols() const
{
	return _matrix.empty() ? 0 : _matrix[0].size();
}

double& equation_matrix::get(int row, int col)
{
	return _matrix[row][col];
}

void equation_matrix::set(int row, int col, double v)
{
	get(row, col) = v;
}

vector<double>& equation_matrix::operator[](size_t idx)
{
	return _matrix[idx];
}