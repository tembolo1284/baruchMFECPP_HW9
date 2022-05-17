/*
a) Compile and run the project as in and make sure that you get Excel output. Examine the code and try to get
an idea of what is going on. The following files should be in the project:

b) In this exercise we test the FD scheme. We run the programs using the data from Batches 1 to 4. Compare
your answers with those from the previous exercises. That’s all.

Batch 1: T = 0.25, K = 65, sig = 0.30, r = 0.08, S = 60 (then C = 2.13337, P = 5.84628).

Spot Price: 60  Put Price: 5.84207  Abs Diff: 0.00421172

This is very close! Heck of a lot quicker than monte carlo I can tell you that much :)

Batch 2: T = 1.0, K = 100, sig = 0.2, r = 0.0, S = 100 (then C = 7.96557, P = 7.96557).
Spot Price: 100  Put Price: 7.96321  Abs Diff: 0.00235914

Batch 3: T = 1.0, K = 10, sig = 0.50, r = 0.12, S = 5 (C = 0.204058, P = 4.07326).
Spot Price: 5  Put Price: 4.07128  Abs Diff: 0.00197546

Batch 4: T = 30.0, K = 100.0, sig = 0.30, r = 0.08, S = 100.0 (C = 92.17570, P = 1.24750).

Interestingly enough, on first pass I got nan as a result for the put price.
I entered some really small values of J = 100 and N = 75, and I got bad results.

Spot Price: 100   Put Price: 7.21518e+125   Abs Diff: 7.21518e+125

I notice the put price is flipping postive to negative as the spot prices are climbing:
Spot Price: 35   Put Price: -1.68122e+107   Abs Diff: 1.68122e+107
Spot Price: 40   Put Price: 1.29466e+109   Abs Diff: 1.29466e+109
Spot Price: 45   Put Price: -7.83647e+110   Abs Diff: 7.83647e+110
Spot Price: 50   Put Price: 3.83318e+112   Abs Diff: 3.83318e+112
Spot Price: 55   Put Price: -1.54885e+114   Abs Diff: 1.54885e+114
Spot Price: 60   Put Price: 5.26268e+115   Abs Diff: 5.26268e+115
Spot Price: 65   Put Price: -1.52595e+117   Abs Diff: 1.52595e+117
Spot Price: 70   Put Price: 3.82271e+118   Abs Diff: 3.82271e+118
Spot Price: 75   Put Price: -8.36102e+119   Abs Diff: 8.36102e+119
Spot Price: 80   Put Price: 1.61109e+121   Abs Diff: 1.61109e+121
Spot Price: 85   Put Price: -2.75644e+122   Abs Diff: 2.75644e+122

Something is clearly going wrong with the scheme's ability to converge. Hope to learn more
about what exactly is going on in Prof Duffy's ODE/PDE course.  :)

In the end I cut J down to 50, and left N = 10000 and got the below results:

Spot Price: 100   Put Price: 1.18474   Abs Diff: 0.0627563

This was about as good as I could do.


Remark: since we are using an explicit method, there is a relationship N = J*J where J is the number of mesh
points in space and N is the number of mesh points in time. This is somewhat pessimistic and you can try with
smaller values of N
*/