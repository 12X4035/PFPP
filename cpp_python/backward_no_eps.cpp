#include "pybind11/pybind11.h"
#include <pybind11/stl.h> // vector用

#include<random>

int comb(int n, int r){
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

//uniform_rand
std::vector< std::vector<double> > uniform_rand(int N, double seed) {
    std::mt19937 rand_src(seed);
    std::uniform_real_distribution<double> rand(-0.1, 0.1);
    std::vector< std::vector<double> > uniform_rand_res(N+1);
    for(int i = 0;i <= N; i++){
        uniform_rand_res[i].resize(i);
        for(int j = 0; j < i; j++){
            uniform_rand_res[i][j] = rand(rand_src);
            }
    }
    return uniform_rand_res;
}

//norm_rand
std::vector< std::vector<double> > norm_rand(int N, double seed, double mean, double var) {
    std::mt19937 rand_src(seed);
    std::normal_distribution<double> normal(mean, var);
    std::vector< std::vector<double> > norm_rand_res(N+1);
    for(int i = 0;i <= N; i++){
        norm_rand_res[i].resize(i);
        for(int j = 0; j < i; j++){
            norm_rand_res[i][j] = normal(rand_src);
            }
    }
    return norm_rand_res;
}

//up_times
std::vector< std::vector<int> > up_times(int N) {
    std::vector< std::vector<int> > up_times_res(N+1);
    for(int i = 0;i <= N; i++){
        up_times_res[i].resize(i);
        for(int j = 0; j < i; j++){
            up_times_res[i][j] = (i-(j+1));
            }
    }
    return up_times_res;
}

//down_times
std::vector< std::vector<int> > down_times(int N) {
    std::vector< std::vector<int> > down_times_res(N+1);
    for(int i = 0;i <= N; i++){
        down_times_res[i].resize(i);
        for(int j = 0; j < i; j++){
            down_times_res[i][j] = j;
            }
    }
    return down_times_res;
}

//theta
std::vector< std::vector<double> > prm_theta(int N, double theta) {
    std::vector< std::vector<double> > theta_res(N+1);
    for(int i = 0;i <= N; i++){
        theta_res[i].resize(i);
        for(int j = 0; j < i; j++){
            theta_res[i][j] = theta;
            }
    }
    return theta_res;
}

//u
std::vector< std::vector<double> > up_r(int N, double u) {
    std::vector< std::vector<double> > up_res(N+1);
    for(int i = 0;i <= N; i++){
        up_res[i].resize(i);
        for(int j = 0; j < i; j++){
            up_res[i][j] = u;
            }
    }
    return up_res;
}

//d
std::vector< std::vector<double> > down_r(int N, double d) {
    std::vector< std::vector<double> > down_res(N+1);
    for(int i = 0;i <= N; i++){
        down_res[i].resize(i);
        for(int j = 0; j < i; j++){
            down_res[i][j] = d;
            }
    }
    return down_res;
}

//p
std::vector< std::vector<double> > prob(int N, double p) {
    std::vector< std::vector<double> > prob_res(N+1);
    for(int i = 0;i <= N; i++){
        prob_res[i].resize(i);
        for(int j = 0; j < i; j++){
            prob_res[i][j] = p;
            }
    }
    return prob_res;
}

//M
std::vector< std::vector<double> > prm_M(int N, double pi, std::vector< std::vector<double> > prm_theta, std::vector< std::vector<double> > up_r, std::vector< std::vector<double> > down_r, std::vector< std::vector<double> > prob) {
    std::vector< std::vector<double> > prm_M_res(N+1);
    for(int i = 0;i <= N; i++){
        prm_M_res[i].resize(i);
        for(int j = 0; j < i; j++){
            prm_M_res[i][j] = prob[i][j]*std::pow(1+pi*(up_r[i][j]-1), 1-(1/prm_theta[i][j]))+(1-prob[i][j])*std::pow(1+pi*(down_r[i][j]-1), 1-(1/prm_theta[i][j]));
            }
    }
    return prm_M_res;
}

//value
std::vector< std::vector<double> > value(int N,double pi, double default_value, std::vector< std::vector<double> >up_r, std::vector< std::vector<double> >down_r) {
    
    std::vector< int > recursive;
    for (int i = 0; i <= std::pow(2, N); i++){
        for(int j = 0; j < 2; j++){
            recursive.push_back(i);
        }
    }
    
    std::vector< std::vector<double> > value_res(N+1);
    for(int i = 0;i <= N; i++){
        value_res[i].resize(i);
        for(int j = 0; j < i; j++){
            if(i == 0){
                value_res[i][j] = default_value;
            }else{
                if( (j+1)%2 != 0){
                    value_res[i][j] = value_res[i-1][recursive[j]]*(1+pi*(up_r[i][j]-1));
                }
                if( (j+1)%2 == 0){
                    value_res[i][j] = value_res[i-1][recursive[j]]*(1+pi*(down_r[i][j]-1));
                }
            }
            }
    }
    return value_res;
}

//wealth
std::vector< std::vector<double> > wealth(int N, std::vector< std::vector<double> > prm_theta, std::vector< std::vector<double> > prm_M, std::vector< std::vector<double> > value) {
    std::vector< std::vector<double> > wealth_res(N+1);
    for(int i = 0;i <= N; i++){
        wealth_res[i].resize(i);
        for(int j = 0; j < i; j++){
            wealth_res[i][j] = std::pow(prm_M[i][j], N-i)*std::pow(1-(1/prm_theta[i][j]), -1)*std::pow(value[i][j], 1-(1/prm_theta[i][j]));;
            }
    }
    return wealth_res;
}

//utility
std::vector< std::vector<double> > utility(int N, std::vector< std::vector<double> > prm_theta, std::vector< std::vector<double> > value) {
    std::vector< std::vector<double> > utility_res(N+1);
    for(int i = 0;i <= N; i++){
        utility_res[i].resize(i);
        for(int j = 0; j < i; j++){
            utility_res[i][j] = std::pow(1-(1/prm_theta[i][j]), -1)*std::pow(value[i][j], 1-(1/prm_theta[i][j]));
            }
    }
    return utility_res;
}

//exp_utility
std::vector< std::vector<double> > exp_utility(int N, std::vector< std::vector<int> > up_times, std::vector< std::vector<int> > down_times, std::vector< std::vector<double> > prob, std::vector< std::vector<double> >utility) {
    std::vector< std::vector<double> > exp_utility_res(N+1);
    for(int i = 0;i <= N; i++){
        exp_utility_res[i].resize(i);
        for(int j = 0; j < i; j++){
              if(up_times[i][j] != 0 && down_times[i][j] != 0){
                exp_utility_res[i][j] = comb(i-1, up_times[i][j])*std::pow(prob[i][j], up_times[i][j])*std::pow(1-prob[i][j], down_times[i][j])*utility[i][j];
            }else{
                if (down_times[i][j] == 0){
                    exp_utility_res[i][j] = std::pow(prob[i][j], up_times[i][j])*utility[i][j];
                }
                if(up_times[i][j] == 0){
                    exp_utility_res[i][j] = std::pow(1-prob[i][j], down_times[i][j])*utility[i][j];
                }
            }
        }
    }
    return exp_utility_res;
}

//Wn
std::vector< std::vector<double> > Wn(int N, std::vector< std::vector<int> >up_times, std::vector< std::vector<int> >down_times, std::vector< std::vector<double> >prob, std::vector< std::vector<double> >wealth) {
    std::vector< std::vector<double> > Wn_res(N+1);
    for(int i = 0;i <= N; i++){
        Wn_res[i].resize(i);
        for(int j = 0; j < i; j++){
            if(up_times[i][j] != 0 && down_times[i][j] != 0){
                Wn_res[i][j] = comb(i-1, up_times[i][j])*std::pow(prob[i][j], up_times[i][j])*std::pow(1-prob[i][j], down_times[i][j])*wealth[i][j];
            }else{
                if(down_times[i][j] == 0){
                    Wn_res[i][j] = std::pow(prob[i][j], up_times[i][j])*wealth[i][j];
                }
                if(up_times[i][j] == 0){
                    Wn_res[i][j] = std::pow(1-prob[i][j], down_times[i][j])*wealth[i][j];
				}
			}
        }
    }
    return Wn_res;
}



PYBIND11_MODULE(backward_no_eps, m) {
    m.doc() = "pybind11 example plugin";
    m.def("uniform_rand", &uniform_rand);
    m.def("norm_rand", &norm_rand);
    m.def("up_times", &up_times);
    m.def("down_times", &down_times);
    m.def("prm_theta", &prm_theta);
    m.def("up_r", &up_r);
    m.def("down_r", &down_r);
    m.def("prob", &prob);
    m.def("prm_M", &prm_M);
    m.def("value", &value);
    m.def("wealth", &wealth);
    m.def("utility", &utility);
    m.def("exp_utility", &exp_utility);
    m.def("Wn", &Wn);
}
