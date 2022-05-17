// EurpeanOption.cpp
//	Author: Daniel Duffy
// (C) Datasim Component Technology BV 2003-2011

#include "EuropeanOption.hpp"
#include "PutCallParity.hpp"
#include <cmath>
#include <iostream>
PutCallParity::PutCallParity() { //default
}

PutCallParity::PutCallParity(const PutCallParity& p1) { // Copy constructor
}

PutCallParity::~PutCallParity() { //destructor
}


PutCallParity& PutCallParity::operator = (const PutCallParity& p2) {
	if (this == &p2) {
		return *this;
	}
	else {
		*this = p2;
		return *this;
	}
}

//put call parity formula: C + Ke^-rT = P + S
double PutCallParity::OptionPriceFromParity(const EuropeanOption& o1) {
	if (o1.optType == "C") {
		return (o1.Price() + (o1.K * exp(-1 * o1.r * o1.T)) - o1.S);
	}
	else {
		return (o1.Price() - (o1.K * exp(-1 * o1.r * o1.T)) + o1.S);

	}
}
//put call parity formula: C - P = S - Ke^-rT
bool PutCallParity::PriceFromParityCheck(EuropeanOption& o1) {
	double rightSide = (o1.S - (o1.K * exp(-1 * o1.r * o1.T))); // S - Ke^rT
	double CallPx{}, PutPx{};
	if (o1.optType == "C") {
		CallPx = o1.Price(); // call Price
		o1.toggle();
		PutPx = o1.Price(); //put price
		return ((CallPx - PutPx) == rightSide);
	}
	else {
		PutPx = o1.Price(); // call Price
		o1.toggle();
		CallPx = o1.Price(); //put price
		return ((CallPx - PutPx) == rightSide);
	}
}




