#include "Utils.hpp"
#include <iomanip>
#include "iostream"
#include "fstream"
#include "sstream"

using namespace std;
bool ImportVectors(const string& inputFilePath,
                double& S,
                size_t& n,
                double*& w,
                double*& r)
{
    ifstream file;
    file.open(inputFilePath);
    if(file.fail())
    {
        cerr<< "file open failed"<<endl;
        return false;
    }

    string weight;
    string rate;
    string line;
    string temporary;
    int i = 1;
    istringstream w0;
    istringstream r0;

    while(!file.eof())
    {
        if(i==1)
        {
            getline(file,temporary, ';'); //store data before ";" in 'temporary'
            getline(file,line); //store the rest of the line in 'line'
            istringstream S0;
            S0.str(line);
            S0 >> S;
        }
        else if(i==2)
        {
            getline(file,temporary, ';'); //store data before ";" in 'temporary'
            getline(file,line); //store the rest of the line in 'line'
            istringstream n0;
            n0.str(line);
            n0 >> n;
            w = new double[n]; //now I know the dimension of the vectors and I can create them
            r = new double[n];
        }

        else if(i==3) //There's no need to store information written in the third line
        {
            getline(file,temporary);
        }
        else
        {
            getline(file,weight, ';');
            getline(file,rate);
            w0.str(weight);
            r0.str(rate);
            w0 >> w[i-4]; //in each line starting from the 4th one there's a component of w
            r0 >> r[i-4];//in each line starting from the 4th one there's a component of r
            w0.clear();
            r0.clear();
        }
        i = i+1;

    }

    file.close();
    return true;
}


void ComputeRate(const double& S,
                         const size_t& n,
                         const double* const& w,
                         const double* const& r,
                         double& rateR,
                         double& V)
{
    for (unsigned int i=0; i<n; i++) //V is obtained as a sum over i of w[i]*S multiplyed by (1+r[i])
        V += (1+r[i])*S*w[i];
    rateR = (V/S)-1; //rate of return is the number such that V = (1+rateR)*S
}


void ExportResult(ostream& outputFile,
                const double& S,
                const size_t& n,
                const double* const& w,
                const double* const& r,
                const double& rateR,
                const double& V)
{

    outputFile<< fixed<< showpoint<< setprecision(2)<< "S = "<< S<< ", n = "<< n<< endl;

    outputFile<< "w = "<< ArrayToString(n,w)<< endl;

    outputFile<< "r = "<< ArrayToString(n,r)<< endl;
//showpoint tells an output stream to write a decimal point for floating-point output
    outputFile<< fixed<< showpoint<< setprecision(4)<< "Rate of return of the portfolio: "<< rateR<< endl;
    outputFile<< fixed<< showpoint<< setprecision(2)<< "V: "<< V<< endl;

}
string ArrayToString(const size_t& n,
                     const double* const& v)
{

    ostringstream toString;
    toString << "[ ";
    for (unsigned int i = 0; i < n; i++)
        toString<< v[i]<< " ";
    toString << "]";

    return toString.str();

}
