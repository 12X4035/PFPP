#ifndef FORWARD_HPP
#define FORWARD_HPP


class Prm{

    private:

    public:
    static double u, d, p, q;

    static double param_q(double u, double d){ return (1-d)/(u-d);}
    static double param_a(double p, double q){ return ((1-p)/p)*(q/(1-q));}
    static double param_b(double q){ return (1-q)/q ;}
    static double param_c(double p, double q){ return (1-p)/(1-q);}
    static double rho_u(double u, double d, double p){ return (((1-u)/(u-d))/p);}
    static double rho_d(double u, double d, double p){ return ((1-((1-u)/(u-d)))/(1-p));}
};


class Fnc{
    
    private:
    static int n, r;
    static double theta, x, a, b, c;

    public:

    static double alpha(double theta);
    static double U_0(double theta, double x);
    static double I_0(double theta, double x);
    static double Delta(double theta, double a, double b, double c);
    static double diff(double theta, double x, double delta);
    static double I_1(double Delta, double I_0);
    static double U_1(double theta, double Delta, double U_0);
    static double Pi(double theta, double p, double q, double u,double Delta);
    static int comb(int n, int r);
};
#endif
