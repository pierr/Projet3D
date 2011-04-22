#ifndef KDNODE_H
#define KDNODE_H

#include <vector>

#include "kdleaf.h"
#include "BoundingBox.h"

class kdnode
{
public:
    inline kdnode(int deep, std::vector<kdleaf> &leafs, BoundingBox box) : deep(deep), leafs(leafs), box(box) {}
    void split(int max_deep, std::vector<kdnode>& deepnodes);
    inline std::vector<kdleaf> & get_leafs() { return leafs; }
    inline BoundingBox & get_box() { return box; }

private:
    int deep;
    int axis;
    std::vector<kdleaf> leafs;
    BoundingBox box;
};

#endif // KDNODE_H
