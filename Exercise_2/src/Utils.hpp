#pragma once
#include "iostream"


using namespace std;

// ImportVectors reads the input data from file
// inputFilePath: path name of the input file
// S: initial wealth
// n: number of assets
// w: weight of the assets
// r: resulting rate of return
// return the result of the reading, true is success, false is error

bool ImportVectors(const string& inputFilePath,
                double& S,
                size_t& n,
                double*& w,
                double*& r);

// ComputeRate computes the rate of return and the final wealth
//rateR: rate of return
//V: final wealth
void ComputeRate(const double& S,
                 const size_t& n,
                 const double* const& w,
                 const double* const& r,
                 double& rateR,
                 double& V);

//ExportResult exports results on the output file
void ExportResult(ostream& outputFile,
                const double& S,
                const size_t& n,
                const double* const& w,
                const double* const& r,
                const double& rateR,
                const double& V);
// Convert a vector into a string
// n: size of the vector
// v: vector
// return the resulting string

string ArrayToString(const size_t& n,
                     const double* const& v);
