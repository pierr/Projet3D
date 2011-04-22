#ifndef SORTNODE_H
#define SORTNODE_H

#include <vector>

#include "sortleaf.h"

class sortnode
{
public:
    inline sortnode(std::vector<sortleaf> &leafs) : leafs(leafs) {}
    std::vector<sortleaf> sort();

private:
    std::vector<sortleaf> leafs;
};

#endif // SORTNODE_H
