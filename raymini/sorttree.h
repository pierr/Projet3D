#ifndef SORTTREE_H
#define SORTTREE_H

#include <vector>
#include "sortnode.h"
#include "kdleaf.h"
#include "Object.h"
#include "Triangle.h"

class sorttree
{
public:
    inline sorttree(std::vector<Object> objects, Vec3Df camPos) : objects(objects), camPos(camPos) {}
    void sort();
    inline const std::vector<kdleaf> get_leafs() const { return leafs; }
    void print();

private:
    std::vector<Object> objects;
    Vec3Df camPos;
    std::vector<kdleaf> leafs;
};

#endif // SORTTREE_H
