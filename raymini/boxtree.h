#ifndef BOXTREE_H
#define BOXTREE_H

#include <vector>
#include "kdleaf.h"
#include "boxnode.h"
#include "boxleaf.h"

class boxtree
{
public:
    inline boxtree(std::vector<kdnode> & kdboxes, Vec3Df camPos) : kdboxes(kdboxes), camPos(camPos) {}
    void sort();
    inline const std::vector<boxleaf> get_leafs() const { return leafs; }
    void get_kdboxes();
    void print();

private:
    std::vector<kdnode> kdboxes;
    Vec3Df camPos;
    std::vector<boxleaf> leafs;
};

#endif // BOXTREE_H
