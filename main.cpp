#include "cpp_tool.hpp"

int main(){
	std::vector<double> v1{1,2,3,4};
	std::vector<double> v2{4,5,6,7};
	std::cout<<correlation_distance(v1, v2)<<std::endl;
	std::cout<<eucliduan_distance(v1, v2)<<std::endl;
}
