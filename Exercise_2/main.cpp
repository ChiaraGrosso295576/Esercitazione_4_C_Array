#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include "Utils.hpp"


int main()
{
    string inputFileName = "./data.csv";
    double S = 0.0;
    size_t n = 0;
    double* w = nullptr;
    double* r = nullptr;

    if (!ImportVectors(inputFileName, S, n, w, r))
    {
        cerr<< "Something goes wrong with import"<< endl;
        return -1;
    }

    // Compute the rate of return of the portfolio and the final wealth V
    double rateR;
    double V;
    ComputeRate(S, n, w, r, rateR, V);


    // Export data on the standard output
    ExportResult(cout, S, n, w, r, rateR, V);


    // Write data output file
    string outputFileName = "./result.txt";
    ofstream file;
    file.open(outputFileName);

    if (!file.fail())
    {
        ExportResult(file, S, n, w, r, rateR, V);
    }

    file.close();

    delete[] w;
    delete[] r;

    return 0;
}
