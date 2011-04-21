#include "kdtree.h"

#include <vector>

#include "kdnode.h"
#include "kdleaf.h"

using namespace std;

Object object;
Triangle triangle;

void kdtree::sort()
{
    //on melange les triangles de tous les objets dans le meme vecteur<kdleaf>
    std::vector<kdleaf> leafs;
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
            leafs.push_back(kdleaf(io,it,Vec3Df::distance(camPos,barycentre)));
        }
    }
    //on definit le premier node du kdtree
    kdnode root(leafs);
    //on ordonne le kdtree et on garde le resultat
    this->leafs = root.sort();
}

void kdtree::print(){
    for(unsigned int i=0; i<leafs.size(); i++){
        kdleaf tmp = leafs.at(i);
        cout << tmp.get_distance() << endl;
    }
}
