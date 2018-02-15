#ifndef ACTIONSWITHVECTORS_H
#define ACTIONSWITHVECTORS_H

#include<vector>

static const int LENGTH_VECTORS = 300;

class ActionsWithVectors
{
public:
    ActionsWithVectors();
    double getSimilarityMeasure(const std::vector<double> &, const std::vector<double> &);
};

#endif // ACTIONSWITHVECTORS_H
