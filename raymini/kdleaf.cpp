#include "kdleaf.h"

kdleaf::kdleaf(int object, int triangle, Material material, Vec3Df v0, Vec3Df v1, Vec3Df v2, Vec3Df n0, Vec3Df n1, Vec3Df n2, Vec3Df camPos){
    this->object = object;
    this->triangle = triangle;
    this->material = material;
    this->v0 = v0;
    this->v1 = v1;
    this->v2 = v2;
    this->barycentre = (v0+v1+v2)/3;
    this->n0 = n0;
    this->n1 = n1;
    this->n2 = n2;
    this->normal = (n0+n1+n2)/3;
    this->distance = Vec3Df::distance(barycentre,camPos);
}
