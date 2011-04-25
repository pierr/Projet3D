#ifndef KDNODE_H
#define KDNODE_H

#include <vector>

#include "kdleaf.h"
#include "BoundingBox.h"

class kdnode
{
public:
    inline kdnode() {}
    inline kdnode(int deep, std::vector<kdleaf> & leafs, BoundingBox & box) : deepest(false), deep(deep), leafs(leafs), box(box) {}
    void split(int max_deep, std::vector<kdnode> & deepnodes);
    inline bool get_deepest() { return deepest; }
    inline std::vector<kdleaf> & get_leafs() { return leafs; }
    inline BoundingBox & get_box() { return box; }
    inline kdnode* get_supnode() { return supnode; }
    inline kdnode* get_infnode() { return infnode; }


private:
    bool deepest;
    int deep;
    int axis;
    std::vector<kdleaf> leafs;
    BoundingBox box;
    kdnode *supnode;
    kdnode *infnode;
};

#endif // KDNODE_H
