#include "myclustering.h"

#include<vector>
#include<QTextStream>
#include<actionswithvectors.h>

MyClustering::MyClustering()
{

}

void MyClustering::clustering(std::vector<Vertex*>& wertices){
    using namespace dlib;

    ActionsWithVectors awv;

    QTextStream out(stdout);
    std::vector<sample_pair> pairs;
    std::vector<unsigned long> labels;

    for(int i = 0; i < wertices.size(); i++){
        std::vector<int> ref = wertices[i]->getReferences();

        for(int j = 0; j < ref.size(); j++){
            int k = ref[j];

            int similarity = awv.getSimilarityMeasure(wertices[i]->getWeights(), wertices[k]->getWeights());

            //value of w must more 1;
            double w = 1 + similarity;

            pairs.push_back(sample_pair(i, k, w));
        }
    }

    out<<"clustering res  " << newman_cluster(pairs,labels);
}
