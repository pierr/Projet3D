#ifndef SORTNODE_H
#define SORTNODE_H

#include <vector>

#include "kdleaf.h"

class sortnode
{
public:
    inline sortnode(std::vector<kdleaf> &leafs) : leafs(leafs) {}
    std::vector<kdleaf> sort();

private:
    std::vector<kdleaf> leafs;
};

#endif // SORTNODE_H
