#include "sorttree.h"

using namespace std;

void sorttree::sort()
{
    //on melange les triangles de tous les objets dans le meme vecteur<kdleaf>
    std::vector<kdleaf> leafs;
    for(int io=0; io<(int)objects.size(); io++)
    {
        Object object = objects.at(io);
        for(int it=0; it<(int)object.getMesh().getTriangles().size(); it++){
            Triangle triangle = object.getMesh().getTriangles().at(it);
            //on push l'objet, le triangle et la distance(camPos, barycentre du triangle)
            Material mat = object.getMaterial();
            Vec3Df v0 = object.getMesh().getVertices().at(triangle.getVertex(0)).getPos();
            Vec3Df v1 = object.getMesh().getVertices().at(triangle.getVertex(1)).getPos();
            Vec3Df v2 = object.getMesh().getVertices().at(triangle.getVertex(2)).getPos();
            Vec3Df n0 = object.getMesh().getVertices().at(triangle.getVertex(0)).getNormal();
            Vec3Df n1 = object.getMesh().getVertices().at(triangle.getVertex(1)).getNormal();
            Vec3Df n2 = object.getMesh().getVertices().at(triangle.getVertex(2)).getNormal();
            leafs.push_back(kdleaf(io,it,mat,v0,v1,v2,n0,n1,n2,camPos));
        }
    }
    //on definit le premier node du sorttree
    sortnode root(leafs);
    //on ordonne le sorttree et on garde le resultat
    this->leafs = root.sort();
}

void sorttree::print(){
    for(unsigned int i=0; i<leafs.size(); i++){
        kdleaf tmp = leafs.at(i);
        cout << tmp.get_distance() << endl;
    }
}
