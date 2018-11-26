#include<iostream>
#include<cmath>
#include<math.h>
#include<vector>

#include"backward.h"

double B_Fnc::last_wealth(double v, double theta){
    double last_wealth;
    last_wealth = (theta/(theta-1)) *std::pow(v, (1-(1/theta)));
    return last_wealth;
}

/*
double B_Fnc::wealth_M(double p, double pi, double u, double d){

    double M;
    M = p*last_wealth(1+(pi*(u-1)))+(1-p)*last_wealth(1+(pi*(d-1)));

    return M;
}
*/

double B_Fnc::value_up(double pi, double u){

    double value_up;
    value_up = 1+(pi*(u-1));

    return value_up;
}

double B_Fnc::value_down(double pi, double d){

    double value_down;
    value_down = 1+(pi*(d-1));

    return value_down;
}

int B_Fnc::comb(int n, int r){

    std::vector<std::vector<long long> > v(n + 1, std::vector<long long>(n + 1, 0));
    for (int i = 0; i < v.size(); i++){
        v[i][0] = 1;
        v[i][i] = 1;
    }
    for (int j = 1; j < v.size(); j++){
        for (int k = 1; k < j; k++){
        v[j][k] = (v[j - 1][k - 1] + v[j - 1][k]);
    }
  }
  return v[n][r];
}
