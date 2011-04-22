#include "kdleaf.h"

kdleaf::kdleaf(int object, int triangle, Vec3Df v0, Vec3Df v1, Vec3Df v2){
    this->object = object;
    this->triangle = triangle;
    this->v0 = v0;
    this->v1 = v1;
    this->v2 = v2;
    this->barycentre = (v0+v1+v2)/3;
}
