#pragma once
#include <vector>


namespace linear_regression_practice
{
using namespace std;


class least_squares
{
public:
	struct residual
	{
		double y;
		vector<double> x;
	};

	typedef vector<vector<double>> matrix;

	typedef vector<residual> residual_list;

public:
	least_squares();
	virtual ~least_squares();

	void solve(residual_list residuals);

protected:

};


}
