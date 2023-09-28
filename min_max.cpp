#include <iostream>
#include <vector>
#include <algorithm>

int main(int argc, char** argv){
	std::vector<int> v(3);
	v[0] = std::stoi(argv[1]);
	v[1] = std::stoi(argv[2]);
	v[2] = std::stoi(argv[3]);

	std::sort(v.begin(),v.end());

	std::cout<< v[0] << ' ' << v[2];
	
	return 0;
}

