#ifndef KDTREE_H
#define KDTREE_H

#include <vector>
#include "kdleaf.h"
#include "Object.h"

class kdtree
{
public:
    inline kdtree(std::vector<Object> objects, Vec3Df camPos) : objects(objects), camPos(camPos) {}
    void sort();
    inline const std::vector<kdleaf> get_leafs() const { return leafs; }

private:
    std::vector<Object> objects;
    Vec3Df camPos;
    std::vector<kdleaf> leafs;
};

#endif // KDTREE_H
