#ifndef KDTREE_H
#define KDTREE_H

#include <vector>

#include "Object.h"
#include "BoundingBox.h"
#include "Triangle.h"
#include "kdnode.h"
#include "kdleaf.h"

class kdtree
{
public:
    kdtree(std::vector<Object> objects, Vec3Df camPos, BoundingBox & scenebox);
    void split(float propdeep);
    inline kdnode * get_root() { return root; }

private:
    BoundingBox scenebox;
    std::vector<kdleaf> leafs;
    kdnode * root;
};

#endif // KDTREE_H
