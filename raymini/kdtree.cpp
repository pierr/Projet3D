#include "kdtree.h"

using namespace std;

kdtree::kdtree(std::vector<Object> objects, Vec3Df camPos, BoundingBox & scenebox){

    //on melange les triangles de tous les objets dans le meme vecteur<kdleaf>
    leafs.clear();
    for(int io=0; io<(int)objects.size(); io++){
        Object object = objects.at(io);
        for(int it=0; it<(int)object.getMesh().getTriangles().size(); it++){
            Triangle triangle = object.getMesh().getTriangles().at(it);
            Material mat = object.getMaterial();
            Vertex vertex0 = object.getMesh().getVertices().at(triangle.getVertex(0));
            Vertex vertex1 = object.getMesh().getVertices().at(triangle.getVertex(1));
            Vertex vertex2 = object.getMesh().getVertices().at(triangle.getVertex(2));
            Vec3Df v0 = object.getMesh().getVertices().at(triangle.getVertex(0)).getPos();
            Vec3Df v1 = object.getMesh().getVertices().at(triangle.getVertex(1)).getPos();
            Vec3Df v2 = object.getMesh().getVertices().at(triangle.getVertex(2)).getPos();
            Vec3Df n0 = object.getMesh().getVertices().at(triangle.getVertex(0)).getNormal();
            Vec3Df n1 = object.getMesh().getVertices().at(triangle.getVertex(1)).getNormal();
            Vec3Df n2 = object.getMesh().getVertices().at(triangle.getVertex(2)).getNormal();
            Vec3Df normal = (n0+n1+n2)/3;
            leafs.push_back(kdleaf(io,it,mat,vertex0,vertex1,vertex2,normal,camPos));
        }
    }
    this->scenebox = scenebox;
}

void kdtree::split(float propdeep)
{
    //on definit le premier node du kdtree
    root = new kdnode(1,leafs,scenebox);
    //on ordonne le kdtree et on garde le resultat
    int maxtriangles = (int)leafs.size()*propdeep;
    if(maxtriangles<1) maxtriangles=1;
    root->split(maxtriangles);
}

