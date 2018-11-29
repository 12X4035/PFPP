#include<iostream>
#include<iomanip>
#include<random>
#include<vector>

#include "forward.h"

int main(){
    int N = 3;
    double theta, x, u, d, p, default_value;

    std::cout << "theta=";
    std::cin >> theta;

    double alpha = Fnc::alpha(theta);

    std::cout << "u=";
    std::cin >> u;


    std::cout << "d=";
    std::cin >> d;


    std::cout << "p=";
    std::cin >> p;

    std::cout << "default_value=";
    std::cin >> default_value;

    double q = Prm::param_q(u, d);

    double a = Prm::param_a(p, q);

    double b = Prm::param_b(q);

    double c = Prm::param_c(p, q);

    double U_0 = Fnc::U_0( theta, x);
    
    //value導出時のときに使うベクトル
    std::vector< int > recursive;
    for (int i = 0; i <= std::pow(2, N); i++){
        for(int j = 0; j < 2; j++){
            recursive.push_back(i);
        }
    }

    std::vector< std::vector<int> > up_times(N+1,std::vector<int>(std::pow(2, N+1)));
    std::vector< std::vector<int> > down_times(N+1,std::vector<int>(std::pow(2, N+1)));
    std::vector< std::vector<double> > prm_theta(N+1,std::vector<double>(std::pow(2, N+1)));
    std::vector< std::vector<double> > up_r(N+1,std::vector<double>(std::pow(2, N+1)));
    std::vector< std::vector<double> > down_r(N+1,std::vector<double>(std::pow(2, N+1)));
    std::vector< std::vector<double> > prob(N+1,std::vector<double>(std::pow(2, N+1)));
    std::vector< std::vector<double> > prm_q(N+1,std::vector<double>(std::pow(2, N+1)));
    std::vector< std::vector<double> > prm_a(N+1,std::vector<double>(std::pow(2, N+1)));
    std::vector< std::vector<double> > prm_b(N+1,std::vector<double>(std::pow(2, N+1)));
    std::vector< std::vector<double> > prm_c(N+1,std::vector<double>(std::pow(2, N+1)));
    std::vector< std::vector<double> > delta(N+1,std::vector<double>(std::pow(2, N+1)));
    std::vector< std::vector<double> > pi(N+1,std::vector<double>(std::pow(2, N+1)));
    std::vector< std::vector<double> > value(N+1,std::vector<double>(std::pow(2, N+1)));
    std::vector< std::vector<double> > wealth(N+1,std::vector<double>(std::pow(2, N+1)));
    std::vector< std::vector<double> > U0(N+1,std::vector<double>(std::pow(2, N+1)));
    std::vector< std::vector<double> > I0(N+1,std::vector<double>(std::pow(2, N+1)));
    std::vector< std::vector<double> > I1(N+1,std::vector<double>(std::pow(2, N+1)));
    std::vector< std::vector<double> > U1(N+1,std::vector<double>(std::pow(2, N+1)));
    std::vector< std::vector<double> > Exp_U1(N+1,std::vector<double>(std::pow(2, N+1)));
    
    for(int i = 0;i <= N; i++){
        for(int j = 0;j < std::pow(2, i); j++){
            
            //up_times
            up_times[i][j] = std::pow(2, i)-(j+1);

            //down_times
            down_times[i][j] = j;

            //theta
            prm_theta[i][j] = theta;

            //u
            up_r[i][j] = u;

            //d
            down_r[i][j] = d;

            //p
            prob[i][j] = p;

            //q
            prm_q[i][j] = Prm::param_q(up_r[i][j], down_r[i][j]);
            
            //a
            prm_a[i][j] = Prm::param_a(prob[i][j], prm_q[i][j]);
            
            //b
            prm_b[i][j] = Prm::param_b(prm_q[i][j]);
            
            //c
            prm_c[i][j] = Prm::param_c(prob[i][j], prm_q[i][j]);
            
            //delta
            delta[i][j] = Fnc::Delta(prm_theta[i][j], prm_a[i][j], prm_b[i][j], prm_c[i][j]);
            //pi
            pi[i][j] = Fnc::Pi(prm_theta[i][j], prob[i][j], prm_q[i][j], up_r[i][j], delta[i][j]);

            //value
            if(i == 0){
                value[i][j] = default_value;
            }else{
                if( (j+1)%2 != 0){
                    value[i][j] = value[i-1][recursive[j]]*(1+pi[i][j]*(up_r[i][j]-1));
                }
                if( (j+1)%2 == 0){
                    value[i][j] = value[i-1][recursive[j]]*(1+pi[i][j]*(down_r[i][j]-1));
                }
            }

            //wealth
            
            //U0
            U0[i][j] = Fnc::U_0(prm_theta[i][j], value[i][j]);

            //I0
            I0[i][j] = Fnc::I_0(prm_theta[i][j], value[i][j]);

            //I1
            I1[i][j] = Fnc::I_1(Fnc::Delta(prm_theta[i][j], prm_a[i][j], prm_b[i][j], prm_c[i][j]), I0[i][j]);

            //U1
            U1[i][j] = Fnc::U_1(prm_theta[i][j], Fnc::Delta(prm_theta[i][j], prm_a[i][j], prm_b[i][j], prm_c[i][j]), U0[i][j]);
            
            
            //Exp_U1
            if(up_times[i][j] != 0 && down_times[i][j] != 0){
                Exp_U1[i][j] = Fnc::comb(std::pow(2, i)-1, up_times[i][j]);
                //*std::pow(p, up_times[i][j])*std::pow(1-p, down_times[i][j])*value[i][j];
            }else{
                if (down_times[i][j] == 0){
                    Exp_U1[i][j] = std::pow(prob[i][j], up_times[i][j])*value[i][j];
                }
                if(up_times[i][j] == 0){
                    Exp_U1[i][j] = std::pow(1-prob[i][j], down_times[i][j])*value[i][j]; 
                }
            }

            std::cout << std::fixed
                      << std::setprecision(3)
                      << i << ","
                      << j+1 << ","
                      << up_times[i][j] << ","
                      << down_times[i][j] << ","
                      << prm_theta[i][j] << ","
                      << up_r[i][j] << ","
                      << down_r[i][j] << ","
                      << prob[i][j] << ","
                      << prm_q[i][j] << ","
                      << prm_a[i][j] << ","
                      << prm_b[i][j] << ","
                      << prm_c[i][j] << ","
                      << pi[i][j] << ","
                      << value[i][j] << ","
                      << U0[i][j] << ","
                      << U1[i][j] << ","
//                    << I1[i][j] << ","
                      << Exp_U1[i][j]
                      << std::endl;
                      
        }
        std::cout << std::endl;
    
    }
/*    
   FILE *fp;
    fp = fopen("test.csv", "w");
    for(int i = 0;i <= N; i++){
        for(int j = 0;j < std::pow(2, i); j++){
            fprintf(fp, "%d,%d,%d,%d,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f\n", i, j+1, up_times[i][j], down_times[i][j], prm_theta[i][j], up_r[i][j], down_r[i][j], prob[i][j], prm_q[i][j], prm_a[i][j], prm_b[i][j], prm_c[i][j], pi[i][j], value[i][j], U0[i][j], I0[i][j], I1[i][j], U1[i][j], Exp_U1[i][j]);
        }
    }
    fclose(fp);
*/
    return 0;
}
