#include "sorttree.h"

#include <vector>

#include "sortnode.h"
#include "sortleaf.h"

using namespace std;

Object object;
Triangle triangle;

void sorttree::sort()
{
    //on melange les triangles de tous les objets dans le meme vecteur<sortleaf>
    std::vector<sortleaf> leafs;
    for(unsigned int io=0; io<objects.size(); io++)
    {
        object = objects.at(io);
        for(unsigned int it=0; it<object.getMesh().getTriangles().size(); it++){
            triangle = object.getMesh().getTriangles().at(it);
            //on push l'objet, le triangle et la distance(camPos, barycentre du triangle)
            Vec3Df barycentre;
            barycentre += object.getMesh().getVertices().at(triangle.getVertex(0)).getPos();
            barycentre += object.getMesh().getVertices().at(triangle.getVertex(1)).getPos();
            barycentre += object.getMesh().getVertices().at(triangle.getVertex(2)).getPos();
            barycentre = barycentre/3;
            leafs.push_back(sortleaf(io,it,Vec3Df::distance(camPos,barycentre)));
        }
    }
    //on definit le premier node du sorttree
    sortnode root(leafs);
    //on ordonne le sorttree et on garde le resultat
    this->leafs = root.sort();
}

void sorttree::print(){
    for(unsigned int i=0; i<leafs.size(); i++){
        sortleaf tmp = leafs.at(i);
        cout << tmp.get_distance() << endl;
    }
}
