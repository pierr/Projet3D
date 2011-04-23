#ifndef BOXNODE_H
#define BOXNODE_H

#include <vector>

#include "boxleaf.h"

class boxnode
{
public:
    inline boxnode(std::vector<boxleaf> &leafs) : leafs(leafs) {}
    std::vector<boxleaf> sort();

private:
    std::vector<boxleaf> leafs;
};

#endif // BOXNODE_H
