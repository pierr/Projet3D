#include "boxtree.h"

using namespace std;

void boxtree::sort(){
    //on melange les triangles de tous les objets dans le meme vecteur<boxleaf>
    leafs.clear();
    for(int i=0; i<(int)kdboxes.size(); i++)
    {
        kdnode kdbox = kdboxes.at(i);
        float distance = Vec3Df::distance(camPos,kdbox.get_box().getCenter());
        leafs.push_back(boxleaf(kdbox,distance));
    }
    //on definit le premier node du boxtree
    boxnode root(leafs);

    //on ordonne le boxtree et on garde le resultat
    this->leafs = root.sort();
}

void boxtree::get_kdboxes(){
    kdboxes.clear();
    for(unsigned int i=0; i<leafs.size(); i++){
        kdboxes.push_back(leafs[i].get_kdbox());
    }
}

void boxtree::print(){
    for(unsigned int i=0; i<leafs.size(); i++){
        boxleaf tmp = leafs.at(i);
        cout << tmp.get_distance() << endl;
    }
}

