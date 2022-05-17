// EurpeanOption.cpp
//
//	Author: Daniel Duffy
//
// (C) Datasim Component Technology BV 2003-2011

#include "EuropeanOption.hpp"
#include <cmath>
#include <iostream>
#include <vector>

//////////// Gaussian functions ////////////////////////////////
// In general, we would use similar functions in Boost::Math Toolkit

double EuropeanOption::n(double x) const{ 
	double A = 1.0/sqrt(2.0 * 3.1415);
	return A * exp(-x*x*0.5);
}

double EuropeanOption::N(double x) const
{ // The approximation to the cumulative normal distribution

	double a1 = 0.4361836;
	double a2 = -0.1201676;
	double a3 = 0.9372980;
	double k = 1.0/(1.0 + (0.33267 * x));
	if (x >= 0.0) {
		return 1.0 - n(x)* (a1*k + (a2*k*k) + (a3*k*k*k));
	}
	else {
		return 1.0 - N(-x);
	}
}
double EuropeanOption::CallPrice() const {
	double tmp = sig * sqrt(T);
	double d1 = ( log(S/K) + (b+ (sig*sig)*0.5 ) * T )/ tmp;
	double d2 = d1 - tmp;
	return (S * exp((b-r)*T) * N(d1)) - (K * exp(-r * T)* N(d2));
}
double EuropeanOption::PutPrice() const {

	double tmp = sig * sqrt(T);
	double d1 = ( log(S/K) + (b+ (sig*sig)*0.5 ) * T )/ tmp;
	double d2 = d1 - tmp;
	return (K * exp(-r * T)* N(-d2)) - (S * exp((b-r)*T) * N(-d1));

}

double EuropeanOption::NumericalGamma(EuropeanOption& o1, double h) const {
	double currPx = o1.Price();
	o1.S += h;
	double plusH = o1.Price();
	o1.S -= (2 * h);
	double minusH = o1.Price();
	return ((plusH - (2 * currPx) + minusH) / (h*h)); // [V(s+h) - 2 V(s) + V(s-h)] / h^2
}


double EuropeanOption::CallDelta() const
{
	double tmp = sig * sqrt(T);
	double d1 = ( log(S/K) + (b+ (sig*sig)*0.5 ) * T )/ tmp;
	return exp((b-r)*T) * N(d1);
}

double EuropeanOption::NumericalCallDelta(EuropeanOption& o1, double h) const {
	o1.S += h;
	double plusH = o1.Price();
	o1.S -= (2*h);
	double minusH = o1.Price();
	return ((plusH - minusH)/(2*h));
}

double EuropeanOption::PutDelta() const {
	double tmp = sig * sqrt(T);
	double d1 = ( log(S/K) + (b+ (sig*sig)*0.5 ) * T )/ tmp;
	return exp((b-r)*T) * (N(d1) - 1.0);
}

double EuropeanOption::NumericalPutDelta(EuropeanOption& o1, double h) const {
	o1.S += h;
	double plusH = o1.Price();
	o1.S -= (2 * h);
	double minusH = o1.Price();
	return ((plusH - minusH) / (2 * h));
}

/////////////////////////////////////////////////////////////////////////////////////
void EuropeanOption::init()
{	// Initialise all default values
	// Default values
	r = 0.05;
	sig= 0.2;

	K = 110.0;
	T = 0.5;

	b = r;			// Black and Scholes stock option model (1973)
	
	optType = "C";		// European Call Option (this is the default type)
}

void EuropeanOption::copy(const EuropeanOption& o2) {

	r	= o2.r;
	sig = o2.sig;	
	K	= o2.K;
	T	= o2.T;
	b	= o2.b;
	optType = o2.optType;
}

EuropeanOption::EuropeanOption() 
{ // Default call option

	init();
}

EuropeanOption::EuropeanOption(const EuropeanOption& o2) { // Copy constructor

	copy(o2);
}

EuropeanOption::EuropeanOption (const string& optionType) {	// Create option type
	init();
	optType = optionType;

	if (optType == "c")
		optType = "C";
}


EuropeanOption::~EuropeanOption(){
}


EuropeanOption& EuropeanOption::operator = (const EuropeanOption& option2) {
	if (this == &option2) return *this;
	copy (option2);
	return *this;
}

// Functions that calculate option price and sensitivities
double EuropeanOption::Price() const {
	if (optType == "C") {	
		//cout << "calling call\n";
		return CallPrice();
	}
	else {
		//cout << "calling put\n";
		return PutPrice();
	}
}	

double EuropeanOption::Delta() const {
	if (optType == "C")
		return CallDelta();
	else
		return PutDelta();
}
double EuropeanOption::NumericalDelta(EuropeanOption& o1, double h) const {
	if (optType == "C")
		return NumericalCallDelta(o1, h);
	else
		return NumericalPutDelta(o1, h);
}

double EuropeanOption::Gamma() const {
	double tmp = sig * sqrt(T);
	double d1 = (log(S / K) + (b + (sig * sig) * 0.5) * T) / tmp;
	return (exp((b - r) * T) * N(d1) / (S * tmp));  //n(d1) * e ^(b-r)T / (S * sig * sqrt(T))
}
// Modifier functions
void EuropeanOption::toggle() { // Change option type (C/P, P/C)
	if (optType == "C") {
		optType = "P";
	}
	else {
		optType = "C";
	}
}

vector<vector<double>> EuropeanOption::MatrixPricing(EuropeanOption& o1, const double row, const double col, vector<double> myStockMesh) {
	vector<vector<double>> mat(row, vector<double>(col, 0));
	for (int i = 0; i < row; ++i) {
		for (int j = 0; j < col; ++j) {
			switch (j) {
			case 0:
				o1.S = myStockMesh[i]; //or you can hardcode the vector's slot or use a number to keep Stock Px constant
				mat[i][j] = o1.S; // Stock Price S0, S1,...., SN
				continue;
			case 1:
				o1.K = 65;
				mat[i][j] = o1.K; //Strike Price. I can make it a manual cin entry or feed it another vector like myMesh for stock prices
				continue;
			case 2:
				o1.T = 0.25;
				mat[i][j] = o1.T; //Time to maturity T
				continue;
			case 3:
				o1.r = 0.08;
				mat[i][j] = o1.r;//interest rate r
				continue;
			case 4:
				o1.sig = 0.3;
				mat[i][j] = o1.sig;// sigma volatility
				continue;
			case 5:
				o1.b = o1.r;
				mat[i][j] = o1.b;// b cost of carry. We'll make it equal to whatever r is for this case.
				continue;
			case 6: // Call option price
				if (o1.optType == "C") {
					mat[i][j] = o1.Price();
				}
				else {
					o1.toggle();
					mat[i][j] = o1.Price();
				}
				continue;
			case 7: // Put option price
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

vector<vector<double>> EuropeanOption::MatrixGreeks(EuropeanOption& o1, const double row, const double col, vector<double> myStockMesh) {
	vector<vector<double>> mat(row, vector<double>(col, 0));
	//Test case: K = 100, S = 105, T = 0.5, r = 0.1, b = 0 and sig = 0.36. (exact delta call = 0.5946, delta put = -0.3566).
	for (int i = 0; i < row; ++i) {
		for (int j = 0; j < col; ++j) {
			switch (j) {
			case 0:
				o1.S = myStockMesh[i]; //or you can hardcode the vector's slot or use a number to keep Stock Px constant
				mat[i][j] = o1.S; // Stock Price S0, S1,...., SN
				continue;
			case 1:
				o1.K = 100;
				mat[i][j] = o1.K; //Strike Price. I can make it a manual cin entry or feed it another vector like myMesh for stock prices
				continue;
			case 2:
				o1.T = 0.5;
				mat[i][j] = o1.T; //Time to maturity T
				continue;
			case 3:
				o1.r = 0.1;
				mat[i][j] = o1.r;//interest rate r
				continue;
			case 4:
				o1.sig = 0.36;
				mat[i][j] = o1.sig;// sigma volatility
				continue;
			case 5:
				o1.b = 0.0;
				mat[i][j] = o1.b;// b cost of carry. We'll make it equal to whatever r is for this case.
				continue;
			case 6: // Call delta
				if (o1.optType == "C") {
					mat[i][j] = o1.Delta();
				}
				else {
					o1.toggle();
					mat[i][j] = o1.Delta();
				}
				continue;
			case 7: // Put option price
				if (o1.optType == "P") {
					mat[i][j] = o1.Delta();
				}
				else {
					o1.toggle();
					mat[i][j] = o1.Delta();
				}
				continue;
			case 8:
				mat[i][j] = o1.Gamma();
				continue;
			}
		}
	}
	return mat;
}

