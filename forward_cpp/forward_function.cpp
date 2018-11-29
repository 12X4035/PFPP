#include<iostream>
#include<cmath>
#include<vector>

#include"forward.h"
/*Function*/

double Fnc::alpha(double theta){

    double alpha;
    alpha = 1-(1/theta);

    return alpha;
}

/*U_0*/
double Fnc::U_0(double theta, double x){

    double U_0;
    U_0 = std::pow(alpha(theta), -1) * std::pow(x, alpha(theta));

    return U_0;
}

/*I_0*/
double Fnc::I_0(double theta, double x){
  static
    double I_0;
    I_0 = std::pow(std::pow(x, -(1/theta)), -1);

    return I_0;
}

/*Delta*/
double Fnc::Delta(double theta, double a, double b, double c){

    double Delta;
    Delta = (1+b)/(std::pow(c, theta)*(std::pow(a, -theta)+b));

    return Delta;
}


/*I_1*/
double Fnc::I_1(double Delta, double I_0){

    double I_1;
    I_1 = Delta*I_0;

    return I_1;
}

/*U_1*/
double Fnc::U_1(double theta, double Delta, double U_0){

    double U_1;
    U_1 = std::pow(Delta, (1/theta))*U_0;

    return U_1;
}
/*Pi*/
/*
double Fnc::Pi(double theta,  double p, double q, double u, double Delta, double x){

    double Pi;
    Pi = Fnc::I_1(Fnc::Delta(theta, a, b, c)/(u-d));

    return Pi;
}
*/

double Fnc::Pi(double theta,  double p, double q, double u, double Delta){

    double Pi;
    Pi = (((Delta * std::pow((p/q), theta)) - 1 ) / (u-1));

    return Pi;
}


/*微分*/
double Fnc::diff(double theta, double x, double delta){

    double diff_f_x;
    diff_f_x = (U_0(theta, (x + delta) )-U_0(theta,  (x - delta) ))/( 2.0 * delta);

    return diff_f_x;
}

int Fnc::comb(int n, int r){

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

