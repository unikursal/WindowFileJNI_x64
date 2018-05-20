#ifndef MYCLUSTERING_H
#define MYCLUSTERING_H

#include <dlib/clustering.h>

#include "myword.h"
#include "mywmdmodel.h"

class MyClustering
{
public:
    MyClustering();
    void clustering(std::vector<MyWord*>&);
};

#endif // MYCLUSTERING_H
