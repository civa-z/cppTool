#include "cpp_tool.hpp"
#include <algorithm>
#include <assert.h>

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

double correlation_distance(std::vector<double>v1, std::vector<double>v2){
    assert(v1.size() == v2.size());
    auto length = v1.size();

    //v1 * v2
    std::vector<double> v1m2;
    for (unsigned int i = 0; i < length; ++i)
        v1m2.push_back(v1[i] * v2[i]);

    //mean
    auto mean1 = std::accumulate(v1.begin(), v1.end(), 0.0) / length;
    auto mean2 = std::accumulate(v2.begin(), v2.end(), 0.0) / length;
    auto mean1m2 = std::accumulate(v1m2.begin(), v1m2.end(), 0.0) / length;

    //covariance
    double covariance = mean1m2 - mean1 * mean2;
    //variance
    double accum1 = 0.0;
    double accum2 = 0.0;
    std::for_each(std::begin(v1), std::end(v1), [&](const double d){accum1 += (d - mean1)*(d -mean1);});
    std::for_each(std::begin(v2), std::end(v2), [&](const double d){accum2 += (d - mean2)*(d -mean2);});
    auto stdev1 = std::sqrt(accum1 / (length));//should we do this
    auto stdev2 = std::sqrt(accum2 / (length));//should we do this

    //correlation distance
    auto corre_distance = 1 - covariance / (stdev1 * stdev2);
    return corre_distance;
}

double eucliduan_distance(std::vector<double> v1, std::vector<double> v2){
    assert(v1.size() == v2.size());
    auto length = v1.size();

    //element distance
    std::vector<double> v1m2;
    for (unsigned int i = 0; i < length; ++i){
        v1m2.push_back((v1[i] - v2[i]) * (v1[i] - v2[i]));
    }

    auto eu_distance = std::sqrt(std::accumulate(v1m2.begin(), v1m2.end(), 0.0));
    return eu_distance;
}


