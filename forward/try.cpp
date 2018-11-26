#include<iostream>
#include<cmath>
#include<vector>
/*
vector< vector<double> > binominal_tree(const double& X0,
                                        const double& u,
                                        const double& d,
                                        const int& no_steps){
    vector< vector<double> >tree;
    for (int i=1; i<=no_steps; i++){
        vector< double > X(i);
        for (int j=0; j<i; j++){
            X[j] = X0*pow(u,j)
        }
    }
}


#include <cmath> #include <algorithm> #include <vector> using namespace std;
// standard mathematical library // defining the max() operator // STL vector templates
double option price call european binomial multi period given ud(const double& S, // spot price
const double& K, // exercice price
const double& r, // interest rate (per period)
const double& u, // up movement
const double& d, // down movement
const int& no periods){// no steps in binomial tree

double Rinv = exp( r);
double uu = u*u;
double p up = (exp(r) d)/(u d);
double p down = 1.0 p up;

vector<double> prices(no periods+1); // price of underlying

prices[0] = S*pow(d, no periods); // fill in the endnodes.

for (int i=1; i<=no periods; ++i) prices[i] = uu*prices[i 1];

vector<double> call values(no periods+1); // value of corresponding call

for (int i=0; i<=no periods; ++i) { call values[i] = max(0.0, (prices[i] K));}; // call payoffs at maturity for (int step=no periods 1; step>=0;   step) {
for (int i=0; i<=step; ++i) {
call values[i] = (p up*call values[i+1]+p down*call values[i])*Rinv;
}; };
return call values[0]; };

*/

    


