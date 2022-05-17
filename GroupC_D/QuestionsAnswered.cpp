/*a) Study the source code in the file TestMC.cpp and relate it to the theory that we have just discussed. The
project should contain the following source files and you need to set project settings in VS to point to the
correct header files:
Compile and run the program as is and make sure there are no errors.


b) Run the MC program again with data from Batches 1 and 2. Experiment with different value of NT (time
steps) and NSIM (simulations or draws). In particular, how many time steps and draws do you need in order
to get the same accuracy as the exact solution? How is the accuracy affected by different values for 
NT/NSIM?

Batch 1: T = 0.25, K = 65, sig = 0.30, r = 0.08, S = 60 (then C = 2.13337, P = 5.84628).
Increasing NT but maintaining NSIM at 100.

NT - 100, NSIM - 100 -> C = 2.0949, P = 6.58781
NT - 1000, NSIM - 100 -> C = 2.55215, P = 6.30289
NT - 10000, NSIM - 100 -> C = 1.87013, P = 6.22307  
NT - 25000, NSIM - 100 -> C = 1.3276, P = 6.97928

Now will try increasing NSIM and keeping NT constant
NT - 100, NSIM - 1000 -> C = 2.0741, P = 5.84851  <-- this one got pretty close for the put!
NT - 100, NSIM - 10000 -> C = 2.1378, P = 5.90807
NT - 100, NSIM - 25000 -> C = 2.07861, P = 5.91523
NT - 100, NSIM - 50000 -> C = 2.11675, P = 5.87749   <-- no convergence sadly

Now will increase both to see if I can't hit the answers precisely
NT - 1000, NSIM - 1000 -> C = 2.17041 , P = 6.07412
NT - 10000, NSIM - 10000 -> C = 2.11864, P = 5.88494
NT - 25000, NSIM - 25000 -> C = 2.11047, P = 5.82274
NT - 50000, NSIM - 50000 -> C = 2.11494, P = 5.81216  <--- hit a wall it seems

--------------------------------------------------------------------------------------------- 

Batch 2 : T = 1.0, K = 100, sig = 0.2, r = 0.0, S = 100 (then C = 7.96557, P = 7.96557).
NT - 100, NSIM - 100 -> C = 7.77513, P = 9.44836
NT - 1000, NSIM - 100 -> C = 8.86798 , P = 8.88433
NT - 10000, NSIM - 100 -> C = 7.31172 , P = 8.75049
NT - 25000, NSIM - 100 -> C = 5.48695, P = 9.80526  <-- bouncing around

Trying to increase NSIM now:
NT - 100, NSIM - 1000 -> C = 7.73557, P = 7.88494
NT - 100, NSIM - 10000 -> C = 7.94097, P = 8.06336
NT - 100, NSIM - 25000 -> C = 7.78598, P = 8.06243
NT - 100, NSIM - 50000 -> C = 7.90889 P = 8.0132  <--still bouncing around no real convergence

//Now will increase both to see if I can't hit the answers precisely
NT - 250, NSIM - 250 -> C = 7.13083, P =  7.82807
NT - 2500, NSIM - 2500 -> C = 7.81722, P = 8.27423
NT - 25000, NSIM - 25000 -> C =  7.90888, P = 7.91587
NT - 25000, NSIM - 50000 -> C =  7.93405, P = 7.87954  <-- about as close as I can get

Seems like NSIM is more sensitive and reacts to coming closest to the solution.
Need high tens of thousands or hundreds of thousands of NT and NSIM to get a decent solution.


c) Now we do some stress-testing of the MC method. Take Batch 4. What values do we need to assign to NT
and NSIM in order to get an accuracy to two places behind the decimal point? How is the accuracy affected 
by different values for NT/NSIM 

//Batch 4: T = 30.0, K = 100.0, sig = 0.30, r = 0.08, S = 100.0 (C = 92.17570, P = 1.24750).
NT - 100, NSIM - 100 -> C = 76.4804, P = 
NT - 1000, NSIM - 100 -> C = 88.2088, P = 
NT - 10000, NSIM - 100 -> C = 62.7653, P =    <-- ouch 
NT - 25000, NSIM - 100 -> C = 72.2298, P =   <-- bouncing around

Trying to increase NSIM now:
NT - 100, NSIM - 1000 -> C = 85.7761, P = 
NT - 100, NSIM - 10000 -> C = 88.0412, P = 
NT - 100, NSIM - 25000 -> C = 87.3961, P = 
NT - 100, NSIM - 50000 -> C = 89.6513, P =   
NT - 100, NSIM - 100000 -> C = 89.4248, P =  <--still bouncing around, no obvious convergence

//Now will increase both to see if I can't hit the answers precisely
NT - 250, NSIM - 250 -> C = 75.5793, P =  
NT - 2500, NSIM - 2500 -> C = 84.9238, P = 
NT - 25000, NSIM - 25000 -> C = 88.7901, P = 
NT - 50000, NSIM - 50000 -> C = 93.2111, P =  
NT - 50000, NSIM - 100000 -> C =  92.8916, P = 
NT - 75000, NSIM - 150000 -> C =  91.7089, P =   <-- about as close as I can get.  This took nearly 50 minutes to run.

Just as in part 1 above, I need upper 100s of thousands(maybe even over a million NSIM!) to get the answer to two decimal places
after the decimal point.

-----------------------------------------------------


a) Create generic functions to compute the standard deviation and standard error based on the above formulae.
The inputs are a vector of size M (M = NSIM), the interest-free rate and expiry time T. Integrate this new
code into TestMC.cpp. Make sure that the code compiles.

	I simply created a function at the top of main to calc the standard deviation.  I initialize a vector and put it in the 
outer for loop after the price is calculated.  In the function I calculated the running C_tj Sum and (sigma C_tj)^2 values
and do the calculation.  As I say I brute forced it rather than put it in a class.

b) Run the MC program again with data from Batches 1 and 2. Experiment with different values of NT (time
steps) and NSIM (simulations or draws). How do SD and SE react for these different run parameters, and is
there any pattern in regards to the accuracy of the MC (when compared to the exact method)?

//Batch 1: T = 0.25, K = 65, sig = 0.30, r = 0.08, S = 60 (then C = 2.13337, P = 5.84628).
NT increases only:

NT - 5000, NSIM - 5000 -> C = 2.2048, stdDev = 5195.63, stdErr = 73.4773
NT - 10000, NSIM - 5000 -> C = 2.17187, stdDev = 5188.45, stdErr = 73.3757
NT - 25000, NSIM - 5000 -> C = 2.01896 , stdDev = 5024.77, stdErr = 71.061
NT - 50000, NSIM - 5000 -> C = 2.05083, stdDev = 5024.61, stdErr = 71.0587
NT - 100000, NSIM - 5000 -> C = 2.08002, stdDev = 5066.12, stdErr = 71.6458

NSIM increases only:
NT - 5000, NSIM - 5000 -> C = 2.2048, stdDev = 5195.63, stdErr = 73.4773
NT - 5000, NSIM - 10000 -> C = 2.18333, stdDev = 8671.67, stdErr = 86.7167
NT - 5000, NSIM - 25000 -> C = 2.13883, stdDev = 17934.8, stdErr = 113.43
NT - 5000, NSIM - 50000 -> C = 2.1221, absDiff = 0.0112689, stdDev = 33140.2, stdErr = 148.208
NT - 5000, NSIM - 100000 -> C = 2.13585, absDiff = 0.0024786, stdDev = 64161.8, stdErr = 202.897
NT - 5000, NSIM - 500000 -> C = 2.14116, absDiff = 0.00778739, stdDev = 311656, stdErr = 440.749
NT - 5000, NSIM - 1000000 -> C = 2.13596 ,absDiff = 0.00259394, stdDev = 619259 , stdErr = 619.259 

Raise both NT and NSIM
NT - 5000, NSIM - 5000 -> C = 2.2048, absDiff = 0.071426, stdDev = 5195.63, stdErr = 73.4773
NT - 10000, NSIM - 10000 -> C = 2.11864, absDiff = 0.0147289, stdDev = 8391.7, stdErr = 83.917
NT - 25000, NSIM - 25000 -> C = 2.11047, absDiff = 0.022902, stdDev = 17836.4, stdErr = 112.807

//Batch 2 : T = 1.0, K = 100, sig = 0.2, r = 0.0, S = 10 (then C = 7.96557, P = 7.96557).
NSIM increases only:
NT - 5000, NSIM - 5000 -> C = 8.16036, absDiff = 0.19479, stdDev = 13703.4, stdErr = 193.795
NT - 5000, NSIM - 10000 -> C = 8.10004, absDiff = 0.134474, stdDev = 25706.6, stdErr = 257.066
NT - 5000, NSIM - 50000 -> C = 7.92605, absDiff = 0.0395162, stdDev = 116038 , stdErr = 518.936
NT - 5000, NSIM - 100000 -> C = 7.97973, absDiff = 0.0141605, stdDev = 231938, stdErr = 733.454
NT - 5000, NSIM - 500000 -> C = 7.99031, absDiff = 0.024742, stdDev = 1.15501e+06, stdErr = 1633.42
NT - 10000, NSIM - 1000000 -> C = 7.95716, absDiff = 0.00841401, stdDev = 2.29847e+06, stdErr = 2298.47

One quick note is I hardcoded the call or put price in the absDiff calculation to compare to the simulated result.
Make sure if you run you replace the appropriate price so you get a valid number.

It's obvious the higher the NT and NSIM numbers are, the stdDev and stdErr increase.
The stdDev and stdErr are more sensitive to the NSIM than the NT, with stdDev growing by
nearly a factor of 6-7 when I increased NSIM by about a factor of 10.

I notice if I increase the NSIM by a factor of 100, my absDiff improves by barely a factor of 10.
That hurts! That means the convergence is on a scale of about an order of 1/2.  Seriously heartbreaking
order of convergence.  The time to run the simulation has to go up by the same factor
as I increase my step size by a factor of X.  I'll stick to finite diff methods I guess haha.

*/