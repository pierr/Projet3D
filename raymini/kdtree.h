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
    inline kdnode * get_root() { return root; }

private:
    int max_deep;
    BoundingBox scenebox;
    std::vector<kdleaf> leafs;
    std::vector<kdnode> boxes;
    kdnode * root;
};

#endif // KDTREE_H
