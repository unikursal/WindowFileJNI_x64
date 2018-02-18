#include "actionswithvectors.h"

#include<cmath>
#include <stdexcept>

ActionsWithVectors::ActionsWithVectors()
{

}

double ActionsWithVectors::getSimilarityMeasure(const std::vector<double>& v1, const std::vector<double>& v2){
    double sum_multiply = 0, sum_pow1 = 0, sum_pow2 = 0, res;

    for(int i = 0; i < LENGTH_VECTORS; i++){
        sum_multiply += v1[i] * v2[i];

        sum_pow1 += std::pow(v1[i], 2);
        sum_pow2 += std::pow(v2[i], 2);
    }

    if(sum_pow1 == 0 || sum_pow2 == 0){
        throw std::overflow_error("Divide by zero exception");
    }

    res = sum_multiply / (std::sqrt(sum_pow1) * std::sqrt(sum_pow2));

    return res;
}
