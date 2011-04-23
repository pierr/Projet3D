#ifndef BOXLEAF_H
#define BOXLEAF_H

#include <vector>
#include "kdnode.h"

class boxleaf
{
public:
    inline boxleaf(kdnode kdbox, float distance) : kdbox(kdbox), distance(distance) {}
    inline kdnode & get_kdbox()   { return kdbox; }
    inline float   get_distance() { return distance; }

private:
    kdnode kdbox;
    float distance;
};

#endif // BOXLEAF_H
