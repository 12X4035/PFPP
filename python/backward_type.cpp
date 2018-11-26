#include<iostream>
#include<iomanip>
#include<cmath>
#include<vector>
#include<math.h>

#include"backward.h"

#define EPS (1.0e-8)
#define f(pi) (p*(theta/(theta-1))*std::pow((1+(pi*(u-1))), 1-(1/theta)))+((1-p)*(theta/(theta-1))*std::pow(1+(pi*(d-1)), 1-(1/theta)))
#define df(pi) p*(u-1)*std::pow(1+pi*(u-1), -1/theta)+(1-p)*(d-1)*std::pow(1+pi*(d-1), -1/theta)



    int N = 10;
    double xo, xn, u, d, p, pi, M, v, theta;
    double last_wealth;

    std::cout << "theta=";
    std::cin >> theta;

    std::cout << "u=";
    std::cin >> u;

    std::cout << "d=";
    std::cin >> d;

    std::cout << "p=";
    std::cin >> p;

    pi = (std::pow((p*(u-1))/((1-p)*(1-d)), theta))/((u - 1)+std::pow((p*(u-1))/((1-p)*(1-d)), theta)*(1 - d));



    std::vector< std::vector<int> > up(N+1,std::vector<int>(N+1));
    std::vector< std::vector<int> > down(N+1,std::vector<int>(N+1));
    std::vector< std::vector<double> > prm_theta(N+1,std::vector<double>(N+1));
    std::vector< std::vector<double> > up_r(N+1,std::vector<double>(N+1));
    std::vector< std::vector<double> > down_r(N+1,std::vector<double>(N+1));
    std::vector< std::vector<double> > prob(N+1,std::vector<double>(N+1));
    std::vector< std::vector<double> > price(N+1,std::vector<double>(N+1));
    std::vector< std::vector<double> > value(N+1,std::vector<double>(N+1));
    std::vector< std::vector<double> > alpha(N+1,std::vector<double>(N+1));


    for(int i = 0;i <= N; i++){
        for(int j = 0; j <= i; j++){

            up[i][j] = i - j;
            down[i][j] = j;
            prob[i][j] = p;
            prm_theta[i][j] = theta;

            if(up[i][j] == 0){
                up_r[i][j] = 0;
            }else{
                up_r[i][j] = std::pow(u, i-j);
            }

            if(down[i][j] == 0){
                down_r[i][j] = 0;
            }else{
                down_r[i][j] = std::pow(d, j);
            }
            if(up_r[i][j] == 0 && down_r[i][j] == 0){
                price[i][j] = 1;
            }else if(up_r[i][j] == 0 || down_r[i][j] == 0){
                price[i][j] = up_r[i][j] + down_r[i][j];
            }else{
                price[i][j] =  up_r[i][j] * down_r[i][j];
            }

            if(up_r[i][j] == 0 ){
                value[i][j] = std::pow(B_Fnc::value_down(pi, d), j);
            }else if(down_r[i][j] == 0){
                value[i][j] = std::pow(B_Fnc::value_up(pi, u), i-j);
            }

            if (i == N){
                value[i][j] = std::pow((1-(1/theta)), -1)*std::pow(price[i][j], (1-(1/theta)));
            }else{
                value[i][j] = p*std::pow((1-(1/theta)), -1)*std::pow(price[i][j]*(1+pi*(u-1)), (1-(1/theta)))+((1-p)*std::pow((1-(1/theta)), -1))*std::pow(price[i][j]*(1+pi*(d-1)), (1-(1/theta)));
            }


            if(i == 0){
                alpha[i][j] = 0;
            }else{
                alpha[i][j] = (pi * value[i][j]) / price[i][j];
            }

            std::cout << std::fixed
                      << std::setprecision(3)
                      << i << ","
                      << j << ","
                      << up[i][j] << ","
                      << down[i][j] << ","
                      << prm_theta[i][j] << ","
                      << prob[i][j] << ","
                      << up_r[i][j] << ","
                      << down_r[i][j] << ","
                      << price[i][j] << ","
                      << value[i][j] << ","
                      << alpha[i][j]
                      << std::endl;
        }
        std::cout << std::endl;
    }
    FILE *fp;
    fp = fopen("test.csv", "w");
    for (int i=0; i <=N; i++){
      for(int j=0;j<=i;j++){
        fprintf(fp, "%d,%d,%d,%d,%f,%f,%f,%f,%f,%f,%f\n", i, j, up[i][j], down[i][j], prm_theta[i][j], up_r[i][j], down_r[i][j], prob[i][j], price[i][j], value[i][j], alpha[i][j]);
         }
     }
    fclose(fp);

    return 0;

}
