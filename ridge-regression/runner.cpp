#define _CRT_SECURE_NO_WARNINGS
#include "csv.hpp"
#include <iostream>
using namespace csv;
using namespace std;


int main()
{
    CSVReader reader("../data/BostonHousing.csv");

    for (CSVRow& row: reader)
    {
        for (CSVField& field: row)
        {
            cout << field.get<>() << "\t";
        }
        cout << endl;
    }
}
