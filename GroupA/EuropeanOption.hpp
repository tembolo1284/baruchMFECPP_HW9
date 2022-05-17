// EuropeanOption.hpp
// Class that represents  solutions to European options. This is
// an implementation using basic C++ syntax only.
// (C) Datasim Component Technology BV 2003-2011

#ifndef EuropeanOption_hpp
#define EuropeanOption_hpp
#include <string>
#include <vector>
using namespace std;

class EuropeanOption {
private:		
	void init();	// Initialise all default values
	void copy(const EuropeanOption& o2);
	// 'Kernel' functions for option calculations
	double CallPrice() const;
	double PutPrice() const;
	double NumericalCallDelta(EuropeanOption& o1, double h) const;
	double NumericalPutDelta(EuropeanOption& o1, double h) const;
	double CallDelta() const;
	double PutDelta() const;
	//double CallGamma() const;
	//double PutGamma() const;
	
	// Gaussian functions
	double n(double x) const;
	double N(double x) const;

public:
	// Member data public for convenience; anyway, the format will 
	// not change for a plain option.
	double r;		// Interest rate
	double sig;		// Volatility
	double K;		// Strike price
	double T;		// Expiry date
	double b;		// Cost of carry
	double S;		// Stock Price

	string optType;	// Option name (call, put)
	string unam;	// Name of underlying asset

public:	// Public functions
	EuropeanOption();							// Default call option
	EuropeanOption(const EuropeanOption& option2);	// Copy constructor
	EuropeanOption (const string& optionType);	// Create option type
	virtual ~EuropeanOption();	

	EuropeanOption& operator = (const EuropeanOption& option2);

	// Functions that calculate option price and sensitivities
	double Price() const;
	double Delta() const;
	double NumericalDelta(EuropeanOption& o1, double h) const;
	double Gamma() const;
	double NumericalGamma(EuropeanOption& o1, double h) const;

	// Modifier functions
	void toggle();		// Change option type (C/P, P/C)
	vector<vector<double>> MatrixPricing(EuropeanOption& o1, const double row, const double col, vector<double> myStockMesh);
	vector<vector<double>> MatrixGreeks(EuropeanOption& o1, const double row, const double col, vector<double> myStockMesh);
};

#endif