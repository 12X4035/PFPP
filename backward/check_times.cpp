#include<iostream>
#include<iomanip>
#include<cmath>
#include<vector>
#include<math.h>
#include<numeric>

int main(){
	int rep = 10;
	int default_value = 500;
	std::vector<double> default_arr(rep);
	
	for(int i = 0; i <= rep; i++){
		default_arr[i] = default_value*i;
		
    }
	for(int i=0; i <=rep; i++){
		std::cout << default_arr.at(i);	
}

/*
std::vector< std::vector<int> > up_times(int N) {
    std::vector< std::vector<int> > up_times_res(N+1);
    for(int i = 0;i <= N; i++){
        for(int j = 0; j < std::pow(2, i); j++){
            up_times_res[i][j] = (i-(j+1));
            }	
    }
    return up_times_res;
}
*/
/*
bool IsEven(int i){
	return ( i%2 == 0 );
}

int main(){
	int N = 10;

	std::vector< std::vector<int> > up_times(N+1, std::vector<int>(std::pow(2, N)));
	std::vector< std::vector<int> > down_times(N+1,std::vector<int>());
	std::vector<int> count_up;
	std::vector<int> count_down;

	for(int i = 0;i <= N; i++){
        for(int j = 0; j < std::pow(2, i); j++){
			
            //up_times
			if(i==0){
				up_times[i][j]=0;
			}
			else if(j+1 == std::pow(2, i)){
				up_times[i][j]= i;
			}
			//if(i==0 || j+1 == std::pow(2, i)){
			//	up_times[i][j]= 0;
			//}
			else if(i!=0 && (j+1)%2!=0){
			//	up_times[i][j]= up_times[i-1][j/2]+1;
				up_times[i][j]= up_times[i-1][j/2];
			}
			else if(i!=0 && (j+1)%2==0){
			//	up_times[i][j]= up_times[i-1][j/2];
            	up_times[i][j]= up_times[i-1][j/2]+1;
			}
			

			//down_times
            //down_times[i][j] = j;
			std::cout << std::fixed
                      << std::setprecision(3)
					  << i << ","
					  << j+1 << ","
					  << up_times[i][j]
					  << std::endl;
		}
	}
*/

/*
	std::vector< std::vector<int> > up_times(N+1, std::vector<int>(std::pow(2, N)));
	static const int s[] = {1, 0};
    for (int i = 0; i < (1 << N); i++) {
        //std::cout << i+1;
        for (int j = 0; j < std::pow(2, i); j++){
			up_times[i][j]= s[i >> j & 1];

			std::cout << i <<","
					  << j+1 << ","
					  << up_times[i][j]
					  << std::endl;
		}
		std::cout << std::endl;
    }
*/
    return 0;

}
