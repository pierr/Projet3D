#include "kdleaf.h"

kdleaf::kdleaf(int object, int triangle, Material material, Vertex vertex0, Vertex vertex1, Vertex vertex2, Vec3Df p0, Vec3Df p1, Vec3Df p2, Vec3Df n0, Vec3Df n1, Vec3Df n2, Vec3Df camPos)
{
    this->object = object;
    this->triangle = triangle;
    this->material = material;
    this->vertex0 = vertex0;
    this->vertex1 = vertex1;
    this->vertex2 = vertex2;
    this->p0 = p0;
    this->p1 = p1;
    this->p2 = p2;
    this->barycentre = (p0+p1+p2)/3;
    this->normal = (n0+n1+n2)/3;
    this->distance = Vec3Df::distance(barycentre,camPos);
}
