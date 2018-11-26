#include<iostream>
#include<iomanip>
#include<cmath>
#include<vector>
#include<math.h>

#include"backward.h"
/*
int comb(int n, int r){
    std::vector<std::vector<long long> > v(n + 1,std::vector<long long>(n + 1, 0));
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
*/
int main(){
    int m, n;
    std::cout << "m=";
    std::cin >> m;
    
    std::cout << "n=";
    std::cin >> n;
    
    int comb = B_Fnc::comb(m, n); 
    //std::cout << comb << std::endl;
    
    return 0;
}
