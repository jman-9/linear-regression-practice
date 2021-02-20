#include "pch.h"
#include "../least-squares/linear_least_squares.h"
#include "../linear-system/equation_matrix.h"
#include "../linear-system/linear_system.h"
#include <stdio.h>
using namespace csv;
using namespace std;


int main()
{
	linear_system les;
	linear_least_squares ls;
	linear_least_squares::residual_list bhd;
	linear_least_squares::parameter_vector pv;
	equation_matrix em;

	CSVReader reader("../data/BostonHousing.csv");
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

	pv = ls.solve(bhd);
	printf("---------\n");
	printf("parameters (not regularized) :\n");
	printf("%s:%lf", colnames[0].c_str(), pv[0]);
	for(size_t i=1; i<pv.size(); i++)
		printf(", %s:%lf", colnames[i].c_str(), pv[i]);
	printf("\n");

	em = ls.make_linear_system(bhd);
	//applying L2-norm for regularizing
	for(size_t i=0; i<em.varcnt() - 1; i++)
	{
		em[i][i] += 1.0; // lambda (controller)
	}

	pv = les.solve(em);
	printf("---------\n");
	printf("parameters (regularized) :\n");
	printf("%s:%lf", colnames[0].c_str(), pv[0]);
	for(size_t i=1; i<pv.size(); i++)
		printf(", %s:%lf", colnames[i].c_str(), pv[i]);
	printf("\n");
	printf("=========\n");

	return 0;
}
