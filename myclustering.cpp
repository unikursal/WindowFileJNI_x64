#include "myclustering.h"

#include<vector>
#include<QTextStream>
#include<actionswithvectors.h>
#include <stdexcept>

MyClustering::MyClustering()
{

}

void MyClustering::clustering(std::vector<Vertex*>& vertices){
    using namespace dlib;

    ActionsWithVectors awv;

    QTextStream out(stdout);
    std::vector<sample_pair> pairs;
    std::vector<unsigned long> labels;

    for(int i = 0; i < vertices.size(); i++){
        std::vector<int> ref = vertices[i]->getReferences();

        for(int j = 0; j < ref.size(); j++){
            int k = ref[j];
            int similarity = 0;
            try{
               similarity  = awv.getSimilarityMeasure(vertices[i]->getWeights(), vertices[k]->getWeights());

            }catch(std::overflow_error e){            }

            //value of w must more 1;
            double w = 1 + similarity;

            pairs.push_back(sample_pair(i, k, w));
        }
    }

    out<<"clustering res  " << newman_cluster(pairs,labels);

    for(int i = 0; i < labels.size(); i++){
        out<<vertices[i]->getWords().at(0) << "  "<<labels[i]<<"\n";
    }
}
