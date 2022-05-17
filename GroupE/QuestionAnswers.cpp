/*Answer the following questions:
a) Implement the above formulae for call and put option pricing using the data sets Batch 1 to Batch 4. Check
your answers, as you will need them when we discuss numerical methods for option pricing.

I took Professor Duffy's TestEuropean hpp, cpp, and Test files and did a brute force method of instantiating
one instance of the option class and running through each Batch to calculate the call and option prices.
I made a minor tweak to his price functions so they don't require a parameter of an option object.

	My call and put prices matched pretty closely to the prices in the exercise file with the following output:
	
Call Option Batch 1: 2.13293
Put Option Batch 1: 5.84584

Call Option Batch 2: 7.96632
Put Option Batch 2: 7.96632

Call Option Batch 3: 0.204121
Put Option Batch 3: 4.07333

Call Option Batch 4: 92.1747
Put Option Batch 4: 1.24651

b) Apply the put-call parity relationship to compute call and put option prices. For example, given the call price, 
compute the put price based on this formula using Batches 1 to 4. Check your answers with the prices from
part a). Note that there are two useful ways to implement parity: As a mechanism to calculate the call (or put) 
price for a corresponding put (or call) price, or as a mechanism to check if a given set of put/call prices 
satisfy parity. The ideal submission will neatly implement both approaches.

	I decided to create a derived class from the EuropeanOption class.  While I could have created simple enough functions
within the current EuropeanOption class implementaiton, I felt for me it would be easier to maintain by stripping out this put-call parity
price and sanity checking functionality.  I created a function that first checks if the option instance is a Call or Put,
and then backs out the Put or Call price (the other type) using put-call parity.

c) Say we wish to compute option prices for a monotonically increasing range of underlying values of S, for
example 10, 11, 12, …, 50. To this end, the output will be a vector. This entails calling the option pricing
formulae for each value S and each computed option price will be stored in a std::vector<double>
object. It will be useful to write a global function that produces a mesh array of doubles separated by a mesh
size h.

	I created a function that allows the user to enter a start and end stock price, and an integer to divide the range by.
This slices up my range in X sections incrementing my starting stock price by a step size h.  I used the Batch 1 numbers
and ran a for() loop iterating through changing the stock price per the vector and ran call and put price function calls
to populate two vectors of call and put prices. I output them at the end of the for loop.

d) Now we wish to extend part c and compute option prices as a function of i) expiry time, ii) volatility, or iii) 
any of the option pricing parameters. Essentially, the purpose here is to be able to input a matrix (vector of 
vectors) of option parameters and receive a matrix of option prices as the result. Encapsulate this 
functionality in the most flexible/robust way you can think of.

	I created the matrix by creating a vector of vectors and iterating through each row by going column by column.
I set the optType to C to start before iterating, and then I set each variable as needed before getting to the last
two columns. Once I am in the penultimate column I call the price() function to price the call, and then toggle()
and price a put option for the last column.  I made this a function that requires certain param to be able
to do the row by row iteration.

	In terms of setting each parameter: For the Stock price I use the same Mesh as from part c), and it is something
that can be easily done for all or some of the other parameters if one so chooses.  I thought about the option
of having the user manually enter a value for each point, but that isn't really feasible when it is 6 inputs per row.
Just 5 scenarios would require 30 manual inputs.  

Option Sensitivities, aka the Greeks:

a) Implement the above formulae for gamma for call and put future option pricing using the data set: K = 100,
S = 105, T = 0.5, r = 0.1, b = 0 and sig = 0.36. (exact delta call = 0.5946, delta put = -0.3566).

	For this I do a brute force approach. I set each member element's value as needed, then call the delta and gamma formulas
as needed for the option object.

b) We now use the code in part a to compute call delta price for a monotonically increasing range of
underlying values of S, for example 10, 11, 12, …, 50. To this end, the output will be a vector and it entails
calling the above formula for a call delta for each value S and each computed option price will be store in a
std::vector<double> object. It will be useful to reuse the above global function that produces a mesh
array of double separated by a mesh size h.

	I implement this in the exact same way as I did in the first part of the exercise. The only difference is I call
delta and gammas instead of prices.

c) Incorporate this into your above matrix pricer code, so you can input a matrix of option parameters and receive
a matrix of either Delta or Gamma as the result.

	I created an almost identical function as in the above case, except I call delta and gamma instead of prices.
I use the same mesh for stocks, and it can be easily altered to accept more meshes for other params if needed.

d) We now use divided differences to approximate option sensitivities. In some cases, an exact formula may not
exist (or is difficult to find) and we resort to numerical methods. In general, we can approximate first and
second-order derivatives in S by 3-point second order approximations, for example:

In this case the parameter h is ‘small’ in some sense. By Taylor’s expansion you can show that the above
approximations are second order accurate in h to the corresponding derivatives.
The objective of this part is to perform the same calculations as in parts a and b, but now using divided
differences. Compare the accuracy with various values of the parameter h (In general, smaller values of h
produce better approximations but we need to avoid round-offer errors and subtraction of quantities that are
very close to each other). Incorporate this into your well-designed class structure.

I included these numerical delta and gamma calculations as part of part b's output above. I found h to be quite
small at 0.00000001 for delta.  I never found a real limit for h for delta.  For gamma I couldn't go any smaller than about h = 0.0000005 
without having the value blow up.


B. Perpetual American Options


A European option can only be exercised at the expiry date T and an exact solution is known. An American
option is a contract that can be exercised at any time prior to T. Most traded stock options are American style. In
general, there is no known exact solution to price an American option but there is one exception, namely
perpetual American options. The formulae are:

a) Program the above formulae, and incorporate into your well-designed options pricing classes.
b) Test the data with K = 100, sig = 0.1, r = 0.1, b = 0.02, S = 110 (check C = 18.5035, P = 3.03106).

	I decided to implement this as its own class and included an hpp and cpp file for this particular option type.


c) We now use the code in part a) to compute call and put option price for a monotonically increasing range of
underlying values of S, for example 10, 11, 12, …, 50. To this end, the output will be a vector and this
exercise entails calling the option pricing formulae in part a) for each value S and each computed option
price will be stored in a std::vector<double> object. It will be useful to reuse the above global
function that produces a mesh array of double separated by a mesh size h.


d) Incorporate this into your above matrix pricer code, so you can input a matrix of option parameters and
receive a matrix of Perpetual American option prices
*/