#ifndef MYCLUSTERING_H
#define MYCLUSTERING_H

#include <dlib/clustering.h>

#include "vertex.h"

class MyClustering
{
public:
    MyClustering();
    void clustering(std::vector<Vertex*>&);
};

#endif // MYCLUSTERING_H
