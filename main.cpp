#include "cpp_tool.hpp"

int main(){
/*
	std::vector<double> v1{1,2,3,4};
	std::vector<double> v2{4,5,6,7};
	std::cout<<correlation_distance(v1, v2)<<std::endl;
	std::cout<<eucliduan_distance(v1, v2)<<std::endl;
*/

    std::vector<double> v1{1,2,3,4};
    auto a = v1.begin();
    auto b = v1.end() - 1;
    std::cout<<&v1[0]<<" "<<*a<<" "<<*b<<std::endl;
    v1.erase(v1.begin());
    std::cout<<&v1[0]<<" "<<*a<<" "<<*b<<std::endl;
    
    return 0;

}
