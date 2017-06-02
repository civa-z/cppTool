#include "cpp_tool.hpp"

void normalization(std::vector<float> &inputs, double lowerBound, double upperBound){
    auto minmaxValueIt = std::minmax_element(inputs.begin(), inputs.end());
    auto minValue = *(minmaxValueIt.first);
    auto maxValue = *(minmaxValueIt.second);
    auto boundRange = upperBound - lowerBound;
    auto valueRange = maxValue - minValue;
    for (auto& element : inputs){
        element = (element - minValue) * boundRange / valueRange + lowerBound;
    }
}

