#include "kdtree.h"

using namespace std;

void kdtree::split()
{
    //on melange les triangles de tous les objets dans le meme vecteur<kdleaf>
    std::vector<kdleaf> leafs;
    for(unsigned int io=0; io<objects.size(); io++)
    {
        Object object = objects.at(io);
        for(unsigned int it=0; it<object.getMesh().getTriangles().size(); it++){
            Triangle triangle = object.getMesh().getTriangles().at(it);
            //on push l'objet, le triangle et la distance(camPos, barycentre du triangle)
            Vec3Df v0 = object.getMesh().getVertices().at(triangle.getVertex(0)).getPos();
            Vec3Df v1 = object.getMesh().getVertices().at(triangle.getVertex(1)).getPos();
            Vec3Df v2 = object.getMesh().getVertices().at(triangle.getVertex(2)).getPos();
            leafs.push_back(kdleaf(io,it,v0,v1,v2));
        }
    }
    //on definit le premier node du kdtree
    kdnode root(1,leafs,scenebox);
    //on ordonne le kdtree et on garde le resultat
    root.split(max_deep, boxes);
}

