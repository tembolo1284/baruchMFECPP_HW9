// HardCoded.cpp
// C++ code to price an option, essential algorithms.
// We take CEV model with a choice of the elaticity parameter
// and the Euler method. We give option price and number of times
// S hits the origin.
// (C) Datasim Education BC 2008-2011
#include "OptionData.hpp" 
#include "NormalGenerator.hpp"
#include "Range.hpp"
#include <cmath>
#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
using namespace std;

template <class T> void print(const std::vector<T>& myList) {  // A generic print function for vectors
	cout << endl << "Size of vector is " << myList.size() << "\n[";
	// We must use a const iterator here, otherwise we get a compiler error.
	typename vector<T>::const_iterator i;
	for (i = myList.begin(); i != myList.end(); ++i) {
		cout << *i << ",";
	}
	std::cout << "]\n";
}

namespace SDEDefinition { // Defines drift + diffusion + data
	OptionData* data;				// The data for the option MC
	double drift(double t, double X)

{ // Drift term
		return (data->r) * X; // r - D
}


	double diffusion(double t, double X) { // Diffusion term
		double betaCEV = 1.0;
		return data->sig * pow(X, betaCEV);
	}

	double diffusionDerivative(double t, double X) { // Diffusion term, needed for the Milstein method
		double betaCEV = 1.0;
		return 0.5 * (data->sig) * (betaCEV)*pow(X, 2.0 * betaCEV - 1.0);
	}
} // End of namespace

double MCStdDev(vector<double>& Vec, double r, double t) {
	double sum{};
	double CSum{};
	double CSquared{};
	double discount = exp(-1 * r * t);
	double N = Vec.size();
	double denominator = 1 / (N - 1);
	for (int i = 0; i < Vec.size(); i++) {
		CSquared += Vec[i] * Vec[i]; //This is C_tj^2 from std dev formula
		CSum += Vec[i];  //Sigma C_tj from std dev formula. Need to square this in final result
	}
	double numerator{ 0 };
	numerator = (CSquared) - ((1/(N))* CSum* CSum); // C_tj^2/N -  1/N^2 * (sigma C_tj)^2

	return (discount * sqrt(numerator/denominator));
}

int main() {
	//Batch 1: T = 0.25, K = 65, sig = 0.30, r = 0.08, S = 60 (then C = 2.13337, P = 5.84628).
	//Batch 2 : T = 1.0, K = 100, sig = 0.2, r = 0.0, S = 100 (then C = 7.96557, P = 7.96557).
	//Batch 4: T = 30.0, K = 100.0, sig = 0.30, r = 0.08, S = 100.0 (C = 92.17570, P = 1.24750)
	std::cout <<  "1 factor MC with explicit Euler\n";
	OptionData myOption1;
	myOption1.K = 100.0;
	myOption1.T = 1.0;
	myOption1.r = 0.0;
	myOption1.sig = 0.2;
	myOption1.type = 1;	// Put -1, Call +1
	double S_0 = 100.0;

	long N = 100;
	std::cout << "Number of subintervals in time: ";
	std::cin >> N;

	// Create the basic SDE (Context class)
	Range<double> range(0.0, myOption1.T);
	double VOld = S_0;
	double VNew{ 0 };

	std::vector<double> x = range.mesh(N);

	// V2 mediator stuff
	long NSim = 50000;
	std::cout << "Number of simulations: ";
	std::cin >> NSim;

	double k = myOption1.T / double(N);
	double sqrk = sqrt(k);

	// Normal random number
	double dW;
	double price = 0.0;	// Option price

	// NormalGenerator is a base class
	NormalGenerator* myNormal = new BoostNormal();

	using namespace SDEDefinition;
	SDEDefinition::data = &myOption1;

	std::vector<double> res;
	int coun = 0; // Number of times S hits origin

	// A.
	//Create a vector to store all prices, V, of option. Size will be N
	vector<double> valVec(NSim+1);
	valVec[0] = S_0;
	for (long i = 1; i <= NSim; ++i)
	{ // Calculate a path at each iteration

		if ((i / 10000) * 10000 == i)
		{// Give status after each 1000th iteration

			std::cout << i << std::endl;
		}

		VOld = S_0;
		for (unsigned long index = 1; index < x.size(); ++index) {

			// Create a random number
			dW = myNormal->getNormal();


			// The FDM (in this case explicit Euler)
			VNew = VOld + (k * drift(x[index - 1], VOld))
				+ (sqrk * diffusion(x[index - 1], VOld) * dW);
			
			VOld = VNew;
			// Spurious values
			if (VNew <= 0.0) coun++;
		}
		
		double tmp = myOption1.myPayOffFunction(VNew);
		price += (tmp) / double(NSim);
		valVec[i] = price; // insert latest value of option from the simulation into valVec vector
	}

	// D. Finally, discounting the average price
	price *= exp(-myOption1.r * myOption1.T);

	//After simulation is done call SD and SE formulas
	double stdDev = MCStdDev(valVec, myOption1.r, myOption1.T); //function call I have in main above.
	double stdErr = stdDev / (sqrt(NSim));  //std divided by (1/sqrt(NSim))

	
	// Cleanup; V2 use scoped pointer
	delete myNormal;

	cout << "Price, after discounting: " << price << ", " << endl;
	cout << "Abs Diff: " << abs(price - 7.96557) << ", " << endl;

	cout << "StdDev of MC: " << stdDev << ", " << endl;
	cout << "StdErr of MC: " << stdErr << ", " << endl;
	cout << "Number of times origin is hit: " << coun << endl;

	return 0;
}