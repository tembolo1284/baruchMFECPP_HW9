#include "EuropeanOption.hpp"
#include "PutCallParity.hpp"
#include "PerpetualOption.hpp"
#include <iostream>
#include <iomanip>      
#include <vector>
#include <fstream>
using namespace std;

vector<double> Xarr(double firstPx, double lastPx, int J) { // Return as an STL vector
	double h = (lastPx - firstPx) / double(J);
	int size = J;
	int start = 1;

	vector<double> result(size, start);
	result[0] = firstPx;

	for (unsigned int j = 1; j < result.size(); j++) {
		result[j] = result[j - 1] + h;
	}
	return result;
}

void printMatrix(vector<vector<double>> m) {
	for (vector<double> oneRow : m) {
		for (double singleCellInCurrentRow : oneRow) {
			cout << singleCellInCurrentRow << "   ";
		}
		cout << "\n";
	}
}
int main() { // All options are European until perpetual option section at the very bottom.
	
	cout << "--------Vector of Prices time --------" << endl;
	vector<double> myStockMesh;
	const double S0{ 10 }, SN{ 110 };
	const int N{ 10 };
	const double cols = (SN - S0) / N;
	myStockMesh =Xarr(S0, SN, N);
	
	EuropeanOption stockOption3;
	//Batch 1: T = 0.25, K = 65, sig = 0.30, r = 0.08, S = 60 (then C = 2.13337, P = 5.84628).
	stockOption3.optType = "C";
	stockOption3.K = 65.0;
	stockOption3.T = 0.25;
	stockOption3.r = 0.08;
	stockOption3.sig = 0.30;
	stockOption3.b = stockOption3.r; // optType, K, T, r, sig, b, S

	vector<double> CallOptionOutput(cols+1);
	vector<double> PutOptionOutput(cols+1);
	std::ofstream myfile;
	myfile.open("cppOptionOutput.csv");
	myfile << "Stock Px,Call Px, Put Px,\n";
		for (int y = 0; y < myStockMesh.size(); y++) {
			stockOption3.S = myStockMesh[y];
			if (stockOption3.optType == "C") {
				CallOptionOutput[y] = stockOption3.Price();
				stockOption3.toggle();
				PutOptionOutput[y] = stockOption3.Price();
			}
			else {
				PutOptionOutput[y] = stockOption3.Price();
				stockOption3.toggle();
				CallOptionOutput[y] = stockOption3.Price();
			}
			cout << "Stock Px: " << myStockMesh[y] <<"       Call Px: " << setprecision(5) << CallOptionOutput[y] << "      Put Px : " << setprecision(5) << PutOptionOutput[y] << endl;
			myfile << myStockMesh[y] << "," << setprecision(5) << CallOptionOutput[y] << "," << setprecision(5) << PutOptionOutput[y] << endl;
		}

		myfile.close();
	return 0;
};
