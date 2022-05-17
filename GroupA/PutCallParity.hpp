// EuropeanOption.hpp
// Class that represents  solutions to European options. This is
// an implementation using basic C++ syntax only.
// (C) Datasim Component Technology BV 2003-2011

#ifndef PutCallParity_hpp
#define PutCallParity_hpp
#include <string>
#include "EuropeanOption.hpp"
using namespace std;

class PutCallParity : public EuropeanOption {
private:
	//void init();	// Initialise all default values
	//void copy(const PutCallParity& p2);
	// 'Kernel' functions for option calculations
	/**double CallPriceOutput(const EuropeanOption& put) const;
	double PutPriceOutput(const EuropeanOption& call) const;
	double CallDelta(double U) const;
	double PutDelta(double U) const;
	*/
	// Gaussian functions
	//double n(double x) const;
	//double N(double x) const;
	//put call parity formula: C + Ke^-rT = P + S
public:
	// Member data public for convenience; anyway, the format will 
	// not change for a plain option.
	/* all the below should be inherited from EuropeanOption
	double r;		// Interest rate
	double sig;		// Volatility
	double K;		// Strike price
	double T;		// Expiry date
	double b;		// Cost of carry
	double S;		// Stock Price
	string optType;	// Option name (call, put)
	string unam;	// Name of underlying asset*/

public:	// Public functions
	//put call parity formula: C + Ke^-rT = P + S
	PutCallParity();							// Default PC parity object
	PutCallParity(const PutCallParity& p2);	// Copy constructor
	virtual ~PutCallParity();

	PutCallParity& operator = (const PutCallParity& p1);

	double OptionPriceFromParity(const EuropeanOption& o1);
	bool PriceFromParityCheck(EuropeanOption& o1);

	// Functions that calculate option price and sensitivities
	//double Price() const;
	//double Delta(double U) const;

	// Modifier functions
	//void toggle();		// Change option type (C/P, P/C)
};

#endif