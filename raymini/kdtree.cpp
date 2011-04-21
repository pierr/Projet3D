#include "kdtree.h"

#include <vector>

#include "kdnode.h"
#include "kdleaf.h"

using namespace std;

Object object;
Triangle triangle;

void kdtree::sort()
{
    cout << "\tkdtree 1" << endl;
    //on melange les triangles de tous les objets dans le meme vecteur<kdleaf>
    std::vector<kdleaf> leafs;
    for(unsigned int io=0; io<objects.size(); io++)
    {
        cout << "\tkdtree 2 1" << endl;
        object = objects.at(io);
        for(unsigned int it=0; it<object.getMesh().getTriangles().size(); it++){
            cout << "\tkdtree 2 2 1" << endl;
            triangle = object.getMesh().getTriangles().at(it);
            cout << "\tkdtree 2 2 2" << endl;
            //on push l'objet, le triangle et la distance camPos et le barycentre du triangle
            Vec3Df barycentre;
            barycentre += object.getMesh().getVertices().at(triangle.getVertex(0)).getPos();
            barycentre += object.getMesh().getVertices().at(triangle.getVertex(1)).getPos();
            barycentre += object.getMesh().getVertices().at(triangle.getVertex(2)).getPos();
            barycentre = barycentre/3;
            cout << "\tkdtree 2 2 3" << endl;
            leafs.push_back(kdleaf(io,it,Vec3Df::distance(camPos,barycentre)));
        }
        cout << "\tkdtree 2 3" << endl;
    }
    kdnode root(leafs);
    cout << "\tkdtree 3" << endl;
    this->leafs = root.sort();
    cout << "\tkdtree 4" << endl;
}
