// EuropeanOption.hpp
// Class that represents  solutions to European options. This is
// an implementation using basic C++ syntax only.
// (C) Datasim Component Technology BV 2003-2011

#ifndef PerpetualOption_hpp
#define PerpetualOption_hpp
#include <string>
#include <vector>
using namespace std;

class PerpetualOption {
private:
	void init();	// Initialise all default values
	void copy(const PerpetualOption& p2);
	// 'Kernel' functions for option calculations
	double CallPrice() const;
	double PutPrice() const;

public:
	// Member data public for convenience; anyway, the format will 
	// not change for a plain option.
	double r;		// Interest rate
	double sig;		// Volatility
	double K;		// Strike price
	//double T;		// Expiry date not present in perpetual options
	double b;		// Cost of carry
	double S;		// Stock Price

	string optType;	// Option name (call, put)
	string unam;	// Name of underlying asset

public:	// Public functions
	PerpetualOption();							// Default call option
	PerpetualOption(const PerpetualOption& perp2);	// Copy constructor
	PerpetualOption(const string& optionType);	// Create option type
	virtual ~PerpetualOption();

	PerpetualOption& operator = (const PerpetualOption& perp2);

	// Functions that calculate option price and sensitivities
	double Price() const;

	// Modifier functions
	void toggle();		// Change option type (C/P, P/C)
	vector<vector<double>> PerpMatrixPricing(PerpetualOption& o1, const double row, const double col, vector<double> myStockMesh);
};

#endif