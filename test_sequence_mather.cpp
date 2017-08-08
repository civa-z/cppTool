#include "sequence_matcher.hpp"


int main(){
    NormalSequenceMather<unsigned int> a1({1,2,3,4}, 4);
    LoopSequenceMather<unsigned int> a2({1,2,3,4}, 4);
    std::vector<unsigned int> b{3,4,5,1,1,2,3,5,1,2,3,4,1,2,1,1};
    for (auto c : b){
        int result = a1.pushItem(c);
        std::cout<<"Put: "<<c<<" "<<result<<std::endl;
    }
    std::cout<<std::endl; 
    for (auto c : b){
        int result = a2.pushItem(c);
        std::cout<<"Put: "<<c<<" "<<result<<std::endl;
    }
    return 0;

}
