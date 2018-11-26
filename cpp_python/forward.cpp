#include"pybind11/pybind11.h"
#include<pybind11/stl.h> // vector用

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
std::vector< std::vector<double> > uniform_rand(int N, double seed, double left, double right) {
    std::mt19937 rand_src(seed);
    std::uniform_real_distribution<double> rand(left, right);
    std::vector< std::vector<double> > uniform_rand_res(N+1);
    for(int i = 0;i <= N; i++){
        uniform_rand_res[i].resize(std::pow(2, i));
        for(int j = 0; j < std::pow(2, i); j++){
            uniform_rand_res[i][j] = rand(rand_src);
            }
    }
    return uniform_rand_res;
}

//norm_rand
std::vector< std::vector<double> > norm_rand(int N, double seed, double mean, double stddev) {
    std::mt19937 rand_src(seed);
    std::normal_distribution<double> normal(mean, stddev);
    std::vector< std::vector<double> > norm_rand_res(N+1);
    for(int i = 0;i <= N; i++){
        norm_rand_res[i].resize(std::pow(2, i));
        for(int j = 0; j < std::pow(2, i); j++){
            norm_rand_res[i][j] = normal(rand_src);
            }
    }
    return norm_rand_res;
}

//up_times
std::vector< std::vector<int> > up_times(int N) {
    std::vector< std::vector<int> > up_times_res(N+1);
    for(int i = 0;i <= N; i++){
        up_times_res[i].resize(std::pow(2, i));
        for(int j = 0; j < std::pow(2, i); j++){
            //up_times_res[i][j] = ((std::pow(2, i)-(j+1)));
            if(i==0 || j+1 == std::pow(2, i)){
                up_times_res[i][j]= 0;
            }
            else if(i!=0 && (j+1)%2!=0){
              up_times_res[i][j]= up_times_res[i-1][j/2]+1;    
            }
            else if(i!=0 && (j+1)%2==0){
                up_times_res[i][j]= up_times_res[i-1][j/2];
            }
        }
    }
    return up_times_res;
}

//down_times
std::vector< std::vector<int> > down_times(int N) {
    std::vector< std::vector<int> > down_times_res(N+1);
    for(int i = 0;i <= N; i++){
        down_times_res[i].resize(std::pow(2, i));
        for(int j = 0; j < std::pow(2, i); j++){
            //down_times_res[i][j] = j;
            if(i==0){
                down_times_res[i][j]=0;
            }
            else if(j+1 == std::pow(2, i)){
                down_times_res[i][j]= i;
            }
            else if(i!=0 && (j+1)%2!=0){
                down_times_res[i][j]= down_times_res[i-1][j/2];
            }
            else if(i!=0 && (j+1)%2==0){
                down_times_res[i][j]= down_times_res[i-1][j/2]+1;
            }
        }
    }
    return down_times_res;
}

//theta
std::vector< std::vector<double> > prm_theta(int N, double theta) {
    std::vector< std::vector<double> > theta_res(N+1);
    for(int i = 0;i <= N; i++){
        theta_res[i].resize(std::pow(2, i));
        for(int j = 0; j < std::pow(2, i); j++){
            theta_res[i][j] = theta;
            }
    }
    return theta_res;
}

//u
std::vector< std::vector<double> > up_r(int N, double u) {
    std::vector< std::vector<double> > up_res(N+1);
    for(int i = 0;i <= N; i++){
        up_res[i].resize(std::pow(2, i));
        for(int j = 0; j < std::pow(2, i); j++){
            up_res[i][j] = u;
            }
    }
    return up_res;
}

//u+norm_rand(初期時点では誤差を含めない)
std::vector< std::vector<double> > up_norm_rand(int N, double u, double seed, double mean, double stddev) {
    std::mt19937 rand_src(seed);
    std::normal_distribution<double> normal(mean, stddev);
    std::vector< std::vector<double> > up_norm_rand_res(N+1);
    for(int i = 0;i <= N; i++){
        up_norm_rand_res[i].resize(std::pow(2, i));
        for(int j = 0; j < std::pow(2, i); j++){
        	if(i==0){    
				up_norm_rand_res[i][j] = u;
            }else{
				up_norm_rand_res[i][j] = u+normal(rand_src);
		}
    }
	}
    return up_norm_rand_res;
}

//d
std::vector< std::vector<double> > down_r(int N, double d) {
    std::vector< std::vector<double> > down_res(N+1);
    for(int i = 0;i <= N; i++){
        down_res[i].resize(std::pow(2, i));
        for(int j = 0; j < std::pow(2, i); j++){
            down_res[i][j] = d;
            }
    }
    return down_res;
}


//d+norm_rand(初期時点では誤差を含めない)
std::vector< std::vector<double> > down_norm_rand(int N, double d, double seed, double mean, double stddev) {
    std::mt19937 rand_src(seed);
    std::normal_distribution<double> normal(mean, stddev);
    std::vector< std::vector<double> > down_norm_rand_res(N+1);
    for(int i = 0;i <= N; i++){
        down_norm_rand_res[i].resize(std::pow(2, i));
        for(int j = 0; j < std::pow(2, i); j++){
        	if(i==0){    
				down_norm_rand_res[i][j] = d;
            }else{
				down_norm_rand_res[i][j] = d+normal(rand_src);
		}
    }
	}
    return down_norm_rand_res;
}


//p
std::vector< std::vector<double> > prob(int N, double p) {
    std::vector< std::vector<double> > prob_res(N+1);
    for(int i = 0;i <= N; i++){
        prob_res[i].resize(std::pow(2, i));
        for(int j = 0; j < std::pow(2, i); j++){
            prob_res[i][j] = p;
            }
    }
    return prob_res;
}

//q
std::vector< std::vector<double> > prm_q(int N, std::vector< std::vector<double> >up_r, std::vector< std::vector<double> >down_r) {
    std::vector< std::vector<double> > prm_q_res(N+1);
    for(int i = 0;i <= N; i++){
        prm_q_res[i].resize(std::pow(2, i));
        for(int j = 0; j < std::pow(2, i); j++){
            prm_q_res[i][j] = (1-down_r[i][j])/(up_r[i][j]-down_r[i][j]);
            }
    }
    return prm_q_res;
}

//a
std::vector< std::vector<double> > prm_a(int N, std::vector< std::vector<double> >prob, std::vector< std::vector<double> >prm_q) {
    std::vector< std::vector<double> > prm_a_res(N+1);
    for(int i = 0;i <= N; i++){
        prm_a_res[i].resize(std::pow(2, i));
        for(int j = 0; j < std::pow(2, i); j++){
            prm_a_res[i][j] = ((1-prob[i][j])/prob[i][j])/((1-prm_q[i][j])/prm_q[i][j]);
            }
    }
    return prm_a_res;
}

//b
std::vector< std::vector<double> > prm_b(int N, std::vector< std::vector<double> >prm_q) {
    std::vector< std::vector<double> > prm_b_res(N+1);
    for(int i = 0;i <= N; i++){
        prm_b_res[i].resize(std::pow(2, i));
        for(int j = 0; j < std::pow(2, i); j++){
            prm_b_res[i][j] = (1-prm_q[i][j])/prm_q[i][j];
            }
    }
    return prm_b_res;
}

//c
std::vector< std::vector<double> > prm_c(int N, std::vector< std::vector<double> >prob, std::vector< std::vector<double> >prm_q) {
    std::vector< std::vector<double> > prm_c_res(N+1);
    for(int i = 0;i <= N; i++){
        prm_c_res[i].resize(std::pow(2, i));
        for(int j = 0; j < std::pow(2, i); j++){
            prm_c_res[i][j] = (1-prob[i][j])/(1-prm_q[i][j]);
            }
    }
    return prm_c_res;
}

//delta
std::vector< std::vector<double> > delta(int N, std::vector< std::vector<double> >prm_theta, std::vector< std::vector<double> >prm_a, std::vector< std::vector<double> >prm_b, std::vector< std::vector<double> >prm_c) {
    std::vector< std::vector<double> > delta_res(N+1);
    for(int i = 0;i <= N; i++){
        delta_res[i].resize(std::pow(2, i));
        for(int j = 0; j < std::pow(2, i); j++){
            delta_res[i][j] = (1+ prm_b[i][j])/(std::pow(prm_c[i][j], prm_theta[i][j])*(std::pow(prm_a[i][j], -prm_theta[i][j])+prm_b[i][j]));
            }
    }
    return delta_res;
}

//pi
std::vector< std::vector<double> > pi(int N, std::vector< std::vector<double> >prm_theta, std::vector< std::vector<double> >up_r, std::vector< std::vector<double> >prob, std::vector< std::vector<double> >prm_q, std::vector< std::vector<double> >delta) {
    std::vector< std::vector<double> > pi_res(N+1);
    for(int i = 0;i <= N; i++){
        pi_res[i].resize(std::pow(2, i));
        for(int j = 0; j < std::pow(2, i); j++){
            pi_res[i][j] = (((delta[i][j] * std::pow((prob[i][j]/prm_q[i][j]), prm_theta[i][j])) - 1 ) / (up_r[i][j]-1));
            }
    }
    return pi_res;
}

//value
std::vector< std::vector<double> > value(int N, double default_value, std::vector< std::vector<double> >up_r, std::vector< std::vector<double> >down_r, std::vector< std::vector<double> >pi) {
    
    std::vector< int > recursive;
    for (int i = 0; i <= std::pow(2, N); i++){
        for(int j = 0; j < 2; j++){
            recursive.push_back(i);
        }
    }
    
    std::vector< std::vector<double> > value_res(N+1);
    for(int i = 0;i <= N; i++){
        value_res[i].resize(std::pow(2, i));
        for(int j = 0; j < std::pow(2, i); j++){
            if(i == 0){
                value_res[i][j] = default_value;
            }else{
                if( (j+1)%2 != 0){
                    value_res[i][j] = value_res[i-1][recursive[j]]*(1+pi[i][j]*(up_r[i][j]-1));
                }
                if( (j+1)%2 == 0){
                    value_res[i][j] = value_res[i-1][recursive[j]]*(1+pi[i][j]*(down_r[i][j]-1));
                }
            }
            }
    }
    return value_res;
}

//U0
std::vector< std::vector<double> > U0(int N, std::vector< std::vector<double> >prm_theta, std::vector< std::vector<double> >value) {
    std::vector< std::vector<double> > U0_res(N+1);
    for(int i = 0;i <= N; i++){
        U0_res[i].resize(std::pow(2, i));
        for(int j = 0; j < std::pow(2, i); j++){
            U0_res[i][j] = std::pow((1-(1/prm_theta[i][j])), -1) * std::pow(value[i][j], (1-(1/prm_theta[i][j])));
            }
    }
    return U0_res;
}

//I0
std::vector< std::vector<double> > I0(int N, std::vector< std::vector<double> >prm_theta, std::vector< std::vector<double> >value) {
    std::vector< std::vector<double> > I0_res(N+1);
    for(int i = 0;i <= N; i++){
        I0_res[i].resize(std::pow(2, i));
        for(int j = 0; j < std::pow(2, i); j++){
            I0_res[i][j] = std::pow(std::pow(value[i][j], -(1/prm_theta[i][j])), -1);
            }
    }
    return I0_res;
}

//I1
std::vector< std::vector<double> > I1(int N, std::vector< std::vector<double> >delta, std::vector< std::vector<double> >I0) {
    std::vector< std::vector<double> > I1_res(N+1);
    for(int i = 0;i <= N; i++){
        I1_res[i].resize(std::pow(2, i));
        for(int j = 0; j < std::pow(2, i); j++){
            I1_res[i][j] = delta[i][j]*I0[i][j];
            }
    }
    return I1_res;
}

//U1
std::vector< std::vector<double> > U1(int N, std::vector< std::vector<double> >prm_theta, std::vector< std::vector<double> >delta, std::vector< std::vector<double> >U0) {
    std::vector< std::vector<double> > U1_res(N+1);
    for(int i = 0;i <= N; i++){
        U1_res[i].resize(std::pow(2, i));
        for(int j = 0; j < std::pow(2, i); j++){
            U1_res[i][j] = std::pow(delta[i][j], (1/prm_theta[i][j]))*U0[i][j];
            }
    }
    return U1_res;
}


//exp_U1
std::vector< std::vector<double> > exp_U1(int N, std::vector< std::vector<int> > up_times, std::vector< std::vector<int> > down_times, std::vector< std::vector<double> > prob, std::vector< std::vector<double> >U1) {
    std::vector< std::vector<double> > exp_U1_res(N+1);
    for(int i = 0;i <= N; i++){
        exp_U1_res[i].resize(std::pow(2, i));
        for(int j = 0; j < std::pow(2, i); j++){
              //if(up_times[i][j] != 0 && down_times[i][j] != 0){
                //exp_U1_res[i][j] = comb(std::pow(2, i)-1, up_times[i][j])*std::pow(prob[i][j], up_times[i][j])*std::pow(1-prob[i][j], down_times[i][j])*U1[i][j];
                exp_U1_res[i][j] = std::pow(prob[i][j], up_times[i][j])*std::pow(1-prob[i][j], down_times[i][j])*U1[i][j];
            /*}else{
                if (down_times[i][j] == 0){
                    exp_U1_res[i][j] = std::pow(prob[i][j], up_times[i][j])*U1[i][j];
                }
                if(up_times[i][j] == 0){
                    exp_U1_res[i][j] = std::pow(1-prob[i][j], down_times[i][j])*U1[i][j];
                }
            }*/
        }
    }
    return exp_U1_res;
}


PYBIND11_MODULE(forward, m) {
    m.doc() = "pybind11 example plugin";
    m.def("uniform_rand", &uniform_rand);
    m.def("norm_rand", &norm_rand);
    m.def("up_times", &up_times);
    m.def("down_times", &down_times);
    m.def("prm_theta", &prm_theta);
    m.def("up_r", &up_r);
    m.def("up_norm_rand", &up_norm_rand);
    m.def("down_r", &down_r);
    m.def("down_norm_rand", &down_norm_rand);
    m.def("prob", &prob);
    m.def("prm_q", &prm_q);
    m.def("prm_a", &prm_a);
    m.def("prm_b", &prm_b);
    m.def("prm_c", &prm_c);
    m.def("delta", &delta);
    m.def("pi", &pi);
    m.def("value", &value);
    m.def("U0", &U0);
    m.def("I0", &I0);
    m.def("I1", &I1);
    m.def("U1", &U1);
    m.def("exp_U1", &exp_U1);
}

