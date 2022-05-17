// EurpeanOption.cpp
//
//	Author: Daniel Duffy
//
// (C) Datasim Component Technology BV 2003-2011

#include "EuropeanOption.hpp"
#include "PerpetualOption.hpp"
#include <cmath>
#include <iostream>
#include <vector>

double PerpetualOption::CallPrice() const {
	//C = (K/(y1-1)) * ((y1-1/y1)(S/K))^y1
	//y1 = 0.5 - (b/sig^2) + [((b/sig^2) - 0.5)^2 + (2*r/sig^2)]^0.5
	//pow(base, power);
	double bDivSig = b / (sig * sig);
	double bDivSigMinusSq = (bDivSig - 0.5) * (bDivSig - 0.5);
	double sByk = S / K;

	double y1 = 0.5 - bDivSig + sqrt(bDivSigMinusSq + ((2 * r) / (sig * sig)));
	double y1MinusOne = y1 - 1;
	double firstTerm = K / y1MinusOne;
	double secondTerm = (y1MinusOne/y1) * (sByk);

	return ((firstTerm)*pow(secondTerm, y1));

}
double PerpetualOption::PutPrice() const {
	//P = (K/(1-y2)) *((y2-1/y2) *(S/K))^y2
	//= 0.5 - (b/sig^2) - [((b/sig^2) - 0.5)^2 + (2*r/sig^2)]^0.5
	double bDivSig = b / (sig * sig);
	double bDivSigMinusSq = (bDivSig - 0.5) * (bDivSig - 0.5);
	double sByk = S / K;

	double y2 = 0.5 - bDivSig - sqrt(bDivSigMinusSq + ((2 * r) / (sig * sig)));
	double y2MinusOne = y2 - 1;
	double firstTerm = K / (1-y2);
	double secondTerm = (y2MinusOne / y2) * (sByk);

	return ((firstTerm)*pow(secondTerm, y2));
}

/////////////////////////////////////////////////////////////////////////////////////
void PerpetualOption::init()
{	// Initialise all default values
	// Default values
	r = 0.05;
	sig = 0.2;
	K = 110.0;
	b = r;			// Black and Scholes stock option model (1973)
	optType = "C";		// European Call Option (this is the default type)
}

void PerpetualOption::copy(const PerpetualOption& p2) {

	r = p2.r;
	sig = p2.sig;
	K = p2.K;
	b = p2.b;
	optType = p2.optType;
}

PerpetualOption::PerpetualOption()
{ // Default call option

	init();
}

PerpetualOption::PerpetualOption(const PerpetualOption& p2) { // Copy constructor

	copy(p2);
}

PerpetualOption::PerpetualOption(const string& optionType) {	// Create option type
	init();
	optType = optionType;

	if (optType == "c")
		optType = "C";
}


PerpetualOption::~PerpetualOption() {
}


PerpetualOption& PerpetualOption::operator = (const PerpetualOption& option2) {
	if (this == &option2) return *this;
	copy(option2);
	return *this;
}

// Functions that calculate option price and sensitivities
double PerpetualOption::Price() const {
	if (optType == "C") {
		//cout << "calling call\n";
		return CallPrice();
	}
	else {
		//cout << "calling put\n";
		return PutPrice();
	}
}

// Modifier functions
void PerpetualOption::toggle() { // Change option type (C/P, P/C)
	if (optType == "C") {
		optType = "P";
	}
	else {
		optType = "C";
	}
}

vector<vector<double>> PerpetualOption::PerpMatrixPricing(PerpetualOption& o1, const double row, const double col, vector<double> myStockMesh) {
	vector<vector<double>> mat(row, vector<double>(col, 0));
	for (int i = 0; i < row; ++i) {
		for (int j = 0; j < col; ++j) {
			switch (j) {
				//Test data : K = 100, sig = 0.1, r = 0.1, b = 0.02, S = 110 (check C = 18.5035, P = 3.03106)
			case 0:
				o1.S = myStockMesh[i]; //or you can hardcode the vector's slot or use a number to keep Stock Px constant
				mat[i][j] = o1.S; // Stock Price S0, S1,...., SN
				continue;
			case 1:
				o1.K = 100;
				mat[i][j] = o1.K; //Strike Price. I can make it a manual cin entry or feed it another vector like myMesh for stock prices
				continue;
			case 2:
				o1.r = 0.1;
				mat[i][j] = o1.r;//interest rate r
				continue;
			case 3:
				o1.sig = 0.1;
				mat[i][j] = o1.sig;// sigma volatility
				continue;
			case 4:
				o1.b = 0.02;
				mat[i][j] = o1.b;// b cost of carry. We'll make it equal to whatever r is for this case.
				continue;
			case 5: // Call option price
				if (o1.optType == "C") {
					mat[i][j] = o1.Price();
				}
				else {
					o1.toggle();
					mat[i][j] = o1.Price();
				}
				continue;
			case 6: // Put option price
				if (o1.optType == "P") {
					mat[i][j] = o1.Price();
				}
				else {
					o1.toggle();
					mat[i][j] = o1.Price();
				}
				continue;
			}
		}
	}
	return mat;
}
