#ifndef SORTTREE_H
#define SORTTREE_H

#include <vector>
#include "sortleaf.h"
#include "Object.h"

class sorttree
{
public:
    inline sorttree(std::vector<Object> objects, Vec3Df camPos) : objects(objects), camPos(camPos) {}
    void sort();
    inline const std::vector<sortleaf> get_leafs() const { return leafs; }
    void print();

private:
    std::vector<Object> objects;
    Vec3Df camPos;
    std::vector<sortleaf> leafs;
};

#endif // SORTTREE_H
