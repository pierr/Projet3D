#ifndef KDNODE_H
#define KDNODE_H

#include <vector>

#include "kdleaf.h"

class kdnode
{
public:
    inline kdnode(std::vector<kdleaf> &leafs) : leafs(leafs) {}
    std::vector<kdleaf> sort();

private:
    std::vector<kdleaf> leafs;
};

#endif // KDNODE_H
