#include "EuropeanOption.hpp"
#include "PutCallParity.hpp"
#include "PerpetualOption.hpp"
#include <iostream>
#include <iomanip>      // std::setprecision
#include <vector>
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
	// Call option on a stock (b = r by default)
	EuropeanOption stockCallOption;
	//Batch 1: T = 0.25, K = 65, sig = 0.30, r = 0.08, S = 60 (then C = 2.13337, P = 5.84628).
	stockCallOption.optType = "C";
	stockCallOption.K = 65.0;
	stockCallOption.T = 0.25;
	stockCallOption.r = 0.08;
	stockCallOption.sig = 0.30;
	stockCallOption.S = 60.0;
	stockCallOption.b = stockCallOption.r;
	cout << "Call Option Batch 1: " << stockCallOption.Price() << endl;
	stockCallOption.toggle();
	cout << "Put Option Batch 1: " << stockCallOption.Price() << endl;
	cout << "----------------------------------" << endl;

	//Batch 2: T = 1.0, K = 100, sig = 0.2, r = 0.0, S = 100 (then C = 7.96557, P = 7.96557).
	stockCallOption.optType = "C";
	stockCallOption.K = 100.0;
	stockCallOption.T = 1.0;
	stockCallOption.r = 0.00;
	stockCallOption.sig = 0.20;
	stockCallOption.S = 100.0;
	stockCallOption.b = stockCallOption.r;
	cout << "Call Option Batch 2: " << stockCallOption.Price() << endl;
	stockCallOption.toggle();
	cout << "Put Option Batch 2: " << stockCallOption.Price() << endl;
	cout << "----------------------------------" << endl;

	//Batch 3: T = 1.0, K = 10, sig = 0.50, r = 0.12, S = 5 (C = 0.204058, P = 4.07326).
	stockCallOption.optType = "C";
	stockCallOption.K = 10.0;
	stockCallOption.T = 1.00;
	stockCallOption.r = 0.12;
	stockCallOption.sig = 0.50;
	stockCallOption.S = 5.0;
	stockCallOption.b = stockCallOption.r;
	cout << "Call Option Batch 3: " << stockCallOption.Price() << endl;
	stockCallOption.toggle();
	cout << "Put Option Batch 3: " << stockCallOption.Price() << endl;
	cout << "----------------------------------" << endl;

	//Batch 4: T = 30.0, K = 100.0, sig = 0.30, r = 0.08, S = 100.0 (C = 92.17570, P = 1.24750).
	stockCallOption.optType = "C";
	stockCallOption.K = 100.0;
	stockCallOption.T = 30.0;
	stockCallOption.r = 0.08;
	stockCallOption.sig = 0.30;
	stockCallOption.S = 100.0;
	stockCallOption.b = stockCallOption.r;
	cout << "Call Option Batch 4: " << stockCallOption.Price() << endl;
	stockCallOption.toggle();
	cout << "Put Option Batch 4: " << stockCallOption.Price() << endl;
	cout << "--------Put Call Parity check--------\n" << endl;

	EuropeanOption stockCallOption2;
	PutCallParity StockCallOption2Parity;

	//Batch 1: T = 0.25, K = 65, sig = 0.30, r = 0.08, S = 60 (then C = 2.13337, P = 5.84628).
	stockCallOption2.optType = "C";
	stockCallOption2.K = 65.0;
	stockCallOption2.T = 0.25;
	stockCallOption2.r = 0.08;
	stockCallOption2.sig = 0.30;
	stockCallOption2.S = 60.0;
	stockCallOption2.b = stockCallOption2.r;
	cout << "Put Option from P/C Parity Batch 1: " << StockCallOption2Parity.OptionPriceFromParity(stockCallOption2) << endl;
	stockCallOption2.toggle();
	cout << "Call Option from P/C Parity Batch 1: " << StockCallOption2Parity.OptionPriceFromParity(stockCallOption2) << endl;
	cout << "Call + Put matches S - Ke^-rT: " << boolalpha << StockCallOption2Parity.PriceFromParityCheck(stockCallOption2) << endl;
	cout << "----------------------------------" << endl;

	//Batch 2: T = 1.0, K = 100, sig = 0.2, r = 0.0, S = 100 (then C = 7.96557, P = 7.96557).
	stockCallOption2.optType = "C";
	stockCallOption2.K = 100.0;
	stockCallOption2.T = 1.0;
	stockCallOption2.r = 0.00;
	stockCallOption2.sig = 0.20;
	stockCallOption2.S = 100.0;
	stockCallOption2.b = stockCallOption2.r;
	cout << "Put Option from P/C Parity Batch 2: " << StockCallOption2Parity.OptionPriceFromParity(stockCallOption2) << endl;
	stockCallOption2.toggle();
	cout << "Call Option from P/C Parity Batch 2: " << StockCallOption2Parity.OptionPriceFromParity(stockCallOption2) << endl;
	cout << "Call + Put matches S - Ke^-rT: " << boolalpha << StockCallOption2Parity.PriceFromParityCheck(stockCallOption2) << endl;
	cout << "----------------------------------" << endl;

	//Batch 3: T = 1.0, K = 10, sig = 0.50, r = 0.12, S = 5 (C = 0.204058, P = 4.07326).
	stockCallOption2.optType = "C";
	stockCallOption2.K = 10.0;
	stockCallOption2.T = 1.00;
	stockCallOption2.r = 0.12;
	stockCallOption2.sig = 0.50;
	stockCallOption2.S = 5.0;
	stockCallOption2.b = stockCallOption2.r;
	cout << "Put Option from P/C Parity Batch 3: " << StockCallOption2Parity.OptionPriceFromParity(stockCallOption2) << endl;
	stockCallOption2.toggle();
	cout << "Call Option from P/C Parity Batch 3: " << StockCallOption2Parity.OptionPriceFromParity(stockCallOption2) << endl;
	cout << "Call + Put matches S - Ke^-rT: " << boolalpha << StockCallOption2Parity.PriceFromParityCheck(stockCallOption2) << endl;
	cout << "----------------------------------" << endl;

	//Batch 4: T = 30.0, K = 100.0, sig = 0.30, r = 0.08, S = 100.0 (C = 92.17570, P = 1.24750).
	stockCallOption2.optType = "C";
	stockCallOption2.K = 100.0;
	stockCallOption2.T = 30.0;
	stockCallOption2.r = 0.08;
	stockCallOption2.sig = 0.30;
	stockCallOption2.S = 100.0;
	stockCallOption2.b = stockCallOption2.r;
	cout << "Put Option from P/C Parity Batch 4: " << StockCallOption2Parity.OptionPriceFromParity(stockCallOption2) << endl;
	stockCallOption2.toggle();
	cout << "Call Option from P/C Parity Batch 4: " << StockCallOption2Parity.OptionPriceFromParity(stockCallOption2) << endl;
	cout << "Call + Put matches S - Ke^-rT: " << boolalpha << StockCallOption2Parity.PriceFromParityCheck(stockCallOption2) << endl;
	cout << "----------------------------------" << endl;
	
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
			cout << "Stock Px: " << myStockMesh[y] <<"       Call Px : " << setprecision(5) << CallOptionOutput[y] << "      Put Px : " << setprecision(5) << PutOptionOutput[y] << endl;
		}
		
		cout << "--------------------Matrix Time----------------------" << endl;
		EuropeanOption stockOption4;
		stockOption4.optType = "C"; //set object to Call to start, toggle and price Put later
		//Number of rows
		double row = myStockMesh.size(); // size of Stock mesh +2 will be number of columns of matrix
		// Number of colums
		double col = 8.0; // S, K, T, r, sig, b --->  6 variables + 2 extra columns for a call and put price at the bottom
		
		//fat function to feed in array and price and output prices
		vector<vector<double>> mat = stockOption4.MatrixPricing(stockOption4, row, col, myStockMesh);
		cout << "\n";
		//sad header attempt:
		
		cout << "Batch 1: T = 0.25, K = 65, sig = 0.30, r = 0.08, S = 60 (then C = 2.13337, P = 5.84628)" << endl;

		cout << "S     K     T     r     sig     b       C        P" << endl; //Need a front-end development course :)
		printMatrix(mat);
		
		cout << "--------------Option Sensitivities, aka the Greeks-------------\n" << endl;

		EuropeanOption optionForGreeks;
		//Test case: K = 100, S = 105, T = 0.5, r = 0.1, b = 0 and sig = 0.36. (exact delta call = 0.5946, delta put = -0.3566).
		optionForGreeks.optType = "C";
		optionForGreeks.K = 100;
		optionForGreeks.S = 105;
		optionForGreeks.T = 0.5;
		optionForGreeks.r = 0.1;
		optionForGreeks.b = 0.0;
		optionForGreeks.sig = 0.36;
		double h = 0.0000005; //used for numerical delta and gamma calculation

		cout << "Delta Call is : " << optionForGreeks.Delta() << endl;
		optionForGreeks.toggle();
		cout << "Delta Put is : " << optionForGreeks.Delta()<< endl;
		cout << "Option Gamma is : " << optionForGreeks.Gamma() << endl;
		optionForGreeks.toggle(); //flip back to call
		cout << "Numerical Delta Call is : " << optionForGreeks.NumericalDelta(optionForGreeks, h) << endl;
		optionForGreeks.toggle(); //flip to put
		optionForGreeks.S = 105; //reset S to 105
		cout << "Numerical Put Call is : " << optionForGreeks.NumericalDelta(optionForGreeks, h) << endl;
		optionForGreeks.S = 105; // reset S to 105
		cout << "Numerical Gamma is : " << optionForGreeks.NumericalGamma(optionForGreeks, h) << endl << endl;

		//Vector of values
		vector<double> myDeltaMesh;
		const double S_0{ 90 }, S_N{ 110 };
		const int n{ 10 };
		const double step = (S_N - S_0) / n;
		myDeltaMesh = Xarr(S_0, S_N, n);

		vector<double> CallDeltaOutput(myDeltaMesh.size() + 1);
		vector<double> PutDeltaOutput(myDeltaMesh.size() +1);
		vector<double> GammaOutput(myDeltaMesh.size() + 1);
		vector<double> NumCallDeltaOutput(myDeltaMesh.size() + 1);
		vector<double> NumPutDeltaOutput(myDeltaMesh.size() + 1);
		vector<double> NumGammaOutput(myDeltaMesh.size() + 1);

		optionForGreeks.S = 105; // reset S to 105
		for (int y = 0; y < myDeltaMesh.size(); y++) {
			optionForGreeks.S = myDeltaMesh[y];
			GammaOutput[y] = optionForGreeks.Gamma();
			NumGammaOutput[y] = optionForGreeks.NumericalGamma(optionForGreeks, h);
			optionForGreeks.S = myDeltaMesh[y];
			if (optionForGreeks.optType == "C") {
				CallDeltaOutput[y] = optionForGreeks.Delta();
				NumCallDeltaOutput[y] = optionForGreeks.NumericalDelta(optionForGreeks, h);
				optionForGreeks.toggle();
				optionForGreeks.S = myDeltaMesh[y];
				PutDeltaOutput[y] = optionForGreeks.Delta();
				NumPutDeltaOutput[y] = optionForGreeks.NumericalDelta(optionForGreeks, h);
			}
			else {
				PutDeltaOutput[y] = optionForGreeks.Delta();
				NumPutDeltaOutput[y] = optionForGreeks.NumericalDelta(optionForGreeks, h);
				optionForGreeks.toggle();
				optionForGreeks.S = myDeltaMesh[y];
				CallDeltaOutput[y] = optionForGreeks.Delta();
				NumCallDeltaOutput[y] = optionForGreeks.NumericalDelta(optionForGreeks, h);
			}
			cout << "S(x): " << myDeltaMesh[y] << "  C Delta: " << CallDeltaOutput[y] << "  P Delta: " \
				<< setprecision(4) << PutDeltaOutput[y] << "  Gamma: " << GammaOutput[y] << endl; 
			cout << "Num C Delta: " << setprecision(4) << NumCallDeltaOutput[y] << "  Num P Delta: " << NumPutDeltaOutput[y] \
				<< "  Num Gamma: " << setprecision(4) << NumGammaOutput[y] << endl << endl;
		}
		cout << endl;

		cout << "--------------------GREEKS Matrix Time----------------------" << endl;

		cout << "S     K     T     r     sig     b     C Delta     P Delta    Gamma" << endl;
		vector<vector<double>> mat2 = optionForGreeks.MatrixGreeks(optionForGreeks, row, col+1, myDeltaMesh);
		printMatrix(mat2);
		
		cout << "--------------------Perpetual Option Time----------------------" << endl;
		//B. Perpetual American Options----------------------------------------------------------------
		//Test the data with K = 100, sig = 0.1, r = 0.1, b = 0.02, S = 110 (check C = 18.5035, P = 3.03106).
		PerpetualOption PerpOption1;
		PerpOption1.optType = "C";
		PerpOption1.K = 100;
		PerpOption1.S = 110;
		PerpOption1.r = 0.1;
		PerpOption1.sig = 0.1;
		PerpOption1.b = 0.02;

		cout << "check C = 18.5035, P = 3.03106" << endl;
		cout << "Call Px: " << PerpOption1.Price() << endl;
		PerpOption1.toggle();
		cout << "Put Px: " << PerpOption1.Price() << endl;

		//vector output for perpetual options
		vector<double> myPerpOptionMesh;
		const double SFirst{ 100 }, SLast{ 120 };
		const int m{ 10 };
		const double hike = (SLast - SFirst) / m;
		myPerpOptionMesh = Xarr(SFirst, SLast, m);

		vector<double> PerpCallOutput(myPerpOptionMesh.size() + 1);
		vector<double> PerpPutOutput(myPerpOptionMesh.size() + 1);
	
		cout << "Test data : K = 100, sig = 0.1, r = 0.1, b = 0.02, S = 110 (check C = 18.5035, P = 3.03106)" << endl;
		for (int y = 0; y < myPerpOptionMesh.size(); y++) {
			PerpOption1.S = myPerpOptionMesh[y];
			if (PerpOption1.optType == "C") {
				PerpCallOutput[y] = PerpOption1.Price();
				PerpOption1.toggle();
				PerpPutOutput[y] = PerpOption1.Price();
			}
			else {
				PerpPutOutput[y] = PerpOption1.Price();
				PerpOption1.toggle();
				PerpCallOutput[y] = PerpOption1.Price();
			}
			cout << "S(x): " << myPerpOptionMesh[y] << "  Call Px: " << PerpCallOutput[y] << "  Put Px: " << PerpPutOutput[y] << endl;
		}
		cout << endl;

		double perpRow = myPerpOptionMesh.size(); // size of Stock mesh +2 will be number of columns of matrix
		// Number of colums
		double perpCol = 7.0; // S, K, r, s, b, call px, put px
		//vector for pricing
		vector<vector<double>> perpMat = PerpOption1.PerpMatrixPricing(PerpOption1, perpRow, perpCol, myPerpOptionMesh);

		cout << "S     K     r     sig     b     C Px     P Px" << endl;
		printMatrix(perpMat);




	return 0;
};
