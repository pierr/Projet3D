#include "kdleaf.h"

kdleaf::kdleaf(int object, int triangle, Material material, Vertex vertex0, Vertex vertex1, Vertex vertex2, Vec3Df normal, Vec3Df camPos)
{
    this->object = object;
    this->triangle = triangle;
    this->material = material;
    this->vertex0 = vertex0;
    this->vertex1 = vertex1;
    this->vertex2 = vertex2;
    this->barycentre = (vertex0.getPos()+vertex1.getPos()+vertex2.getPos())/3;
    this->normal = /*(vertex0.getNormal()+vertex1.getNormal()+vertex2.getNormal())/3;*/normal;
    this->distance = Vec3Df::distance(barycentre,camPos);
}
