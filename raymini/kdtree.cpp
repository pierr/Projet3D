#include "kdtree.h"

using namespace std;

void kdtree::split()
{
    //on definit le premier node du kdtree
    kdnode root(1,leafs,scenebox);
    //on ordonne le kdtree et on garde le resultat
    root.split(max_deep, boxes);
}

