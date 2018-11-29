# include <iostream>
# include <random>
#include<vector>
int main()
{
    /*std::mt19937 rand_src(12345);
	std::uniform_real_distribution<double> rand(-0.1, 0.1);
	for(int i=0; i<=10; ++i)
	{
		std::cout << 500*i << '\n';
	}*/
    int N=10;
    std::vector< int > recursive;
    for (int i = 0; i <= std::pow(2, N); i++){
        for(int j = 0; j < 2; j++){
            recursive.push_back(i);
        }
    }

    for(int i = 0; i<= std::pow(2, N)*2; i++){
        std::cout << recursive[i] << std::endl;
    }
}
