// TestBSPDE1.cpp
// Testing 1 factor BS model.
// (C) Datasim Education BV 2005-2011

#include "FDMDirector.hpp"
#include <iostream>
#include <string>
#include <cmath>
using namespace std;
//#include "ExcelDriverLite.hpp"
/*
Batch 1: T = 0.25, K = 65, sig = 0.30, r = 0.08, S = 60 (then C = 2.13337, P = 5.84628).
Batch 2: T = 1.0, K = 100, sig = 0.2, r = 0.0, S = 100 (then C = 7.96557, P = 7.96557).
Batch 3: T = 1.0, K = 10, sig = 0.50, r = 0.12, S = 5 (C = 0.204058, P = 4.07326).
Batch 4: T = 30.0, K = 100.0, sig = 0.30, r = 0.08, S = 100.0 (C = 92.17570, P = 1.24750).
*/

namespace BS {// Black Scholes
	double T = 0.25;
	double K = 65.0;
	double sig = 0.3;
	double r = 0.08;
	double D = 0.0; // aka q
	
	double mySigma (double x, double t) {
		double sigmaS = sig*sig;
		return 0.5 * sigmaS * x * x;
	}

	double myMu (double x, double t) {
		return (r - D) * x;
	}

	double myB (double x, double t) {	
		return  -r;
	}

	double myF (double x, double t) {
		return 0.0;
	}

	double myBCL (double t) {
		// Put
		return K *exp(-r * t);
	}

	double myBCR (double t) {
		// Put
		return 0.0; // P
	}

	double myIC (double x){ // Payoff 
		// Put
		return max(K - x, 0.0);
	}
}

int main() {
	using namespace ParabolicIBVP;
	// Assignment of functions
	sigma = BS::mySigma;
	mu = BS::myMu;
	b = BS::myB;
	f = BS::myF;
	BCL = BS::myBCL;
	BCR = BS::myBCR;
	IC = BS::myIC;

	int J = static_cast<int>(BS::K);
	int N = 10000-1; // k = O(h^2) !!!!!!!!!
	double Smax = 5 * BS::K;			// Magix from Prof Duffy

	cout << "start FDM\n";
	FDMDirector fdir(Smax, BS::T, J, N);

	fdir.doit();
	
	cout << "Finished\n";
	vector<double> resultMatrix;
	resultMatrix = fdir.current();

	for (int i = 0; i < fdir.xarr.size(); i++) {
		cout << "Spot Price: " << fdir.xarr[i] << "   Put Price: " << resultMatrix[i] << "   Abs Diff: " << abs(5.84628 - resultMatrix[i]) << endl;;
	}

	// Have you Excel installed (ExcelImports.cpp)
	//printOneExcel(fdir.xarr, fdir.current(), string("Value"));

	return 0;
}
