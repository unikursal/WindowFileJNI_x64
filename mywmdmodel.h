#ifndef MYWMDMODEL_H
#define MYWMDMODEL_H

#include<vector>

#include "myword.h"
#include "mysentences.h"
#include "actionswithvectors.h"

class MyWmdModel
{
private:
    std::vector<MySentences> sentences;
    int count, maxSentSize;
public:
    MyWmdModel(std::vector<MyWord*>&);
    double getSimilarity(int i, int j, std::vector<MyWord*>&);
    int getCount();
};

#endif // MYWMDMODEL_H
