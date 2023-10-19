#include "ComplexNum.hpp"

int main(){
	std::vector<ComplexNum> vec =  {{1, 2}, {-1, 1}, {2.1, 0}, {-, -2}};
	std::sort(vec.begin(), vec.end());

	for(int i = 0;i < vec.size();++i){
		std::cout << vec[i] << std::endl;
	}
}
