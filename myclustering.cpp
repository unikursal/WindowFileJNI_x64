#include "myclustering.h"

#include<vector>
#include<QTextStream>
#include <stdexcept>

MyClustering::MyClustering()
{
}

void MyClustering::clustering(std::vector<MyWord*>& words){
    QTextStream out(stdout);
    std::vector<dlib::sample_pair> pairs;
    std::vector<unsigned long> labels;

    MyWmdModel model(words);
    int count = model.getCount();

    int i, j;
    for(i = 0; i < count; i++){
        j = (i > 10) ? (i - 10) : 0;
        int maxJ = (i < count - 10) ? (i + 10) : count;

        for(; j < maxJ; j++){
            if(i == j)
                continue;

            double w = model.getSimilarity(i, j, words);

            if(w != -1.0)
                pairs.push_back(dlib::sample_pair(i, j, w));
        }
    }


    labels.reserve(pairs.size() + 1);
    int cluster_size = dlib::newman_cluster(pairs,labels);
    out<<"clustering res  " << cluster_size << "\n";

    for(i = 0; i < cluster_size; i++){
        for(j = 0; j < labels.size(); j++)
            if(labels[j] == i)
                out<<j<<" ";

        out<<"\n";
    }

}
