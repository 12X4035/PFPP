#include<iostream>
#include<cmath>


/*Parameter*/
/*q*/
double param_q(double u, double d){

    double q;
    q = (1-d) / (u-d);

    return q;
}

/*a*/
double param_a(double p, double q){

    double a;
    a = ((1-p)/p)*((1-q)/q);

    return a;
}


/*b*/
double param_b(double q){

    double b;
    b = (1-q)/q;

    return b;
}


/*c*/
double param_c(double p, double q){

    double c;
    c = (1-p)/(1-q);

    return c;
}

/*rho_u*/
double rho_u(double p, double q){

    double rho_u;
    rho_u = q/p;

    return rho_u;
}

/*rho_d*/
double rho_d(double p, double q){

    double rho_d;
    rho_d = (1-q)/(1-p);

    return rho_d;
}
