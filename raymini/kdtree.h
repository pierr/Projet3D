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
    void split();
    inline std::vector<kdnode> & get_boxes() { return boxes; }

private:
    int max_deep;
    std::vector<kdleaf> leafs;
    BoundingBox scenebox;
    std::vector<kdnode> boxes;
};

#endif // KDTREE_H
