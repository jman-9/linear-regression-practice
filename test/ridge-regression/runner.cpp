#include "pch.h"
#include "../../libsrc/linear_least_squares.h"
#include "../../libsrc/ridge_regression.h"
#include <stdio.h>
using namespace csv;
using namespace std;


int main()
{
	ridge_regression rr;
	linear_least_squares::residual_list bhd;
	linear_least_squares::parameter_vector pv;

	CSVReader reader("data/BostonHousing.csv");
    for (CSVRow& row: reader)
    {
		bhd.push_back({});
		bhd.back().y = row["medv"].get<double>();

		for(size_t i=0; i<row.size()-1; i++)
		{
			bhd.back().x.push_back(row[i].get<double>());
		}
	}

	auto colnames = reader.get_col_names();
	colnames.back() = "bias";

	printf("=========\n");
	printf("solving Boston Housing Dataset\n");

	pv = rr.solve(bhd, 0.0);
	printf("---------\n");
	printf("parameters (not regularized) :\n");
	printf("%s:%lf", colnames[0].c_str(), pv[0]);
	for(size_t i=1; i<pv.size(); i++)
		printf(", %s:%lf", colnames[i].c_str(), pv[i]);
	printf("\n");

	pv = rr.solve(bhd, 1.0);
	printf("---------\n");
	printf("parameters (regularized) :\n");
	printf("%s:%lf", colnames[0].c_str(), pv[0]);
	for(size_t i=1; i<pv.size(); i++)
		printf(", %s:%lf", colnames[i].c_str(), pv[i]);
	printf("\n");
	printf("=========\n");

	return 0;
}
