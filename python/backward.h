#ifndef BACKWARD_HPP
#define BACKWARD_HPP


class B_Fnc{

    private:
    static double theta, x, a, b, c, v, pi;

    public:

    static double last_wealth(double v, double theta);
    static double wealth_M(double p, double pi, double u, double d);
    static double value_up(double pi, double u);
    static double value_down(double pi, double d);
};
#endif
