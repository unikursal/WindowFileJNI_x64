#include "myclustering.h"

#include<vector>
#include<QTextStream>

#include <dlib/clustering.h>

MyClustering::MyClustering()
{

}

void MyClustering::clustering(){
    using namespace dlib;

    QTextStream out(stdout);

    std::vector<sample_pair> pairs;

    pairs.push_back(sample_pair(1,2,1));
    pairs.push_back(sample_pair(1,3,1));
    pairs.push_back(sample_pair(2,3,1));

    pairs.push_back(sample_pair(3,4,5));
    pairs.push_back(sample_pair(3,5,6));
    pairs.push_back(sample_pair(3,12,7));


    pairs.push_back(sample_pair(4,5,2));
    pairs.push_back(sample_pair(4,6,2));

    pairs.push_back(sample_pair(5,7,2));
    pairs.push_back(sample_pair(5,12,6));

    pairs.push_back(sample_pair(6,7,2));

    pairs.push_back(sample_pair(8,9,2));
    pairs.push_back(sample_pair(8,10,1));
    pairs.push_back(sample_pair(8,12,1));

    pairs.push_back(sample_pair(9,10,1));
    pairs.push_back(sample_pair(10,11,1));
    pairs.push_back(sample_pair(10,12,2));
    pairs.push_back(sample_pair(11,12,1));




    std::vector<unsigned long> labels;

    out<<newman_cluster(pairs, labels);

}

