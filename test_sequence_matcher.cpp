#include "ScrlSequenceRecognizer.hpp"


int main(){
    /*
    NormalSequenceMather<unsigned int> a1({1,2,3,4}, 4);
    LoopSequenceMather<unsigned int> a2({1,2}, 4);
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
    */

    
    std::vector<unsigned int> b{11,12,11,21,11,12,21,12,31,32,31,41,42,43,41,43,42,41,11,51,12,51,21,51,61,62,71,72,71};
    ScrlSequenceRecognizer ssr;
    for ( auto label : b ){
        std::cout<<"Label: "<<label<<" result: "<<ssr.pushItem(label)<<std::endl;
    }

    return 0;

}
