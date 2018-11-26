#include<iostream>
#include<iomanip>
#include<cmath>
#include<vector>
#include<math.h>

#include"backward.h"

double func(double theta, double u, double d, double p, double pi){
  return (p*(theta/(theta-1))*std::pow((1+(pi*(u-1))), 1-(1/theta)));
  /*+((1-p)*(theta/(theta-1))*std::pow(1+(pi*(d-1)), 1-(1/theta)))*/
}

int main(){
    int N = 10;
    double xo, xn, u, d, p, pi, M, v, theta, default_value;
    double last_wealth;

    std::cout << "theta=";
    std::cin >> theta;

    std::cout << "u=";
    std::cin >> u;

    std::cout << "d=";
    std::cin >> d;

    std::cout << "p=";
    std::cin >> p;

    std::cout << "default_value=";
    std::cin >> default_value;

    
    pi = ((std::pow((p*(u-1))/((1-p)*(1-d)), theta))-1)/(u-1+(std::pow((p*(u-1))/((1-p)*(1-d)), theta)*(1-d)));
    
    //べき型に関してはRunggaldierに載ってるものを使う
    M = std::pow(p*(1+pi*(u-1)), 1-(1/theta))+std::pow((1-p)*(1+pi*(d-1)), 1-(1/theta));
    
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
    std::vector< std::vector<double> > prm_M(N+1,std::vector<double>(std::pow(2, N+1)));
    std::vector< std::vector<double> > value(N+1,std::vector<double>(std::pow(2, N+1)));
    std::vector< std::vector<double> > wealth(N+1,std::vector<double>(std::pow(2, N+1)));
    std::vector< std::vector<double> > utility(N+1,std::vector<double>(std::pow(2, N+1)));
    std::vector< std::vector<double> > exp_val(N+1,std::vector<double>(std::pow(2, N+1)));
    std::vector< std::vector<double> > Wn(N+1,std::vector<double>(std::pow(2, N+1)));

    for(int i = 0;i <= N; i++){
        for(int j = 0; j < std::pow(2, i); j++){
            
            //up_times 
            up_times[i][j] = i-(j+1);
            
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
            
            //M
            prm_M[i][j] = prob[i][j]*std::pow(1+pi*(up_r[i][j]-1), 1-(1/prm_theta[i][j]))+(1-prob[i][j])*std::pow(1+pi*(down_r[i][j]-1), 1-(1/prm_theta[i][j]));

            //value
            if(i == 1){
                value[i][j] = default_value;
            }else{
                if( (j+1)%2 != 0){
                    value[i][j] = value[i-1][recursive[j]]*(1+pi*(up_r[i][j]-1));
                }
                if( (j+1)%2 == 0){
                    value[i][j] = value[i-1][recursive[j]]*(1+pi*(down_r[i][j]-1));
                }
            }

            //wealth
            wealth[i][j] = std::pow(prm_M[i][j], (N+1-i))*std::pow(1-(1/prm_theta[i][j]), -1)*std::pow(value[i][j], 1-(1/prm_theta[i][j]));

            //utility
            utility[i][j] = std::pow(1-(1/prm_theta[i][j]), -1)*std::pow(value[i][j], 1-(1/prm_theta[i][j]));

            //exp_utility
            if(up_times[i][j] != 0 && down_times[i][j] != 0){
                exp_val[i][j] = B_Fnc::comb(i-1, up_times[i][j])*std::pow(p, up_times[i][j])*std::pow(1-p, down_times[i][j])*utility[i][j];
            }else{
                if (down_times[i][j] == 0){
                    exp_val[i][j] = std::pow(prob[i][j], up_times[i][j])*utility[i][j];
                }
                if(up_times[i][j] == 0){
                    exp_val[i][j] = std::pow(1-prob[i][j], down_times[i][j])*utility[i][j]; 
                }
            }
            //Wn
            if(up_times[i][j] != 0 && down_times[i][j] != 0){
                Wn[i][j] = B_Fnc::comb(std::pow(2, i)-1, up_times[i][j])*std::pow(prob[i][j], up_times[i][j])*std::pow(1-prob[i][j], down_times[i][j])*wealth[i][j]; 
            }else{
                if(down_times[i][j] == 0){
                    Wn[i][j] = std::pow(prob[i][j], up_times[i][j])*wealth[i][j];
                }
                if(up_times[i][j] == 0){
                    Wn[i][j] = std::pow(1-prob[i][j], down_times[i][j])*wealth[i][j]; 
                }
            }


            std::cout << std::fixed
                      << std::setprecision(3)
                      << i << ","
                      << j+1 << ","
                      << up_times[i][j] << ","
                      << down_times[i][j]  << ","
                      << prm_theta[i][j] << ","
                      << prob[i][j] << ","
                      << up_r[i][j] << ","
                      << down_r[i][j] << ","
                      << prm_M[i][j] << ","
                      << value[i][j] << ","
                      << wealth[i][j] << ","
                      << utility[i][j] << ","
                      << exp_val[i][j] << ","
                      << Wn[i][j] 
                      << std::endl;

        }
        std::cout << std::endl;
    }
    /*
    FILE *fp;
    fp = fopen("test.csv", "w");
    for (int i=0; i <=N; i++){
      for(int j=0;j<=i;j++){
        fprintf(fp, "%d,%d,%d,%d,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f\n", i, j+1, up_times[i][j], down_times[i][j], prm_theta[i][j], up_r[i][j], down_r[i][j], prob[i][j], prm_M[i][j], value[i][j], wealth[i][j], utility[i][j], exp_val[i][j], Wn[i][j]);
         }
     }
    fclose(fp);
*/
    return 0;

}

