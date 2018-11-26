#include<pybind11/pybind11.h>

int add(int i, int j) {
    return i + j;
}
/*
double pi (double theta, double u, double d, double p){
    return (std::pow((p*(u-1))/((1-p)*(1-d)), theta))/((u - 1)+std::pow((p*(u-1))/((1-p)*(1-d)), theta)*(1 - d));
}
*/
PYBIND11_MODULE(cppmod, m) {
    m.doc() = "pybind11 example plugin";
    m.def("add", &add, "A function which adds tow numbers");
}
