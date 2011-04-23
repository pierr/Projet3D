#ifndef KDLEAF_H
#define KDLEAF_H

#include <vector>

#include "Material.h"
#include "Vec3D.h"

class kdleaf
{
public:
    kdleaf(int object, int triangle, Material material, Vec3Df v0, Vec3Df v1, Vec3Df v2, Vec3Df n0, Vec3Df n1, Vec3Df n2, Vec3Df camPos);
    inline int       get_object()     { return object; }
    inline int       get_triangle()   { return triangle; }
    inline Material& get_Material()   { return material; }
    inline Vec3Df&   get_v0()         { return v0; }
    inline Vec3Df&   get_v1()         { return v1; }
    inline Vec3Df&   get_v2()         { return v2; }
    inline Vec3Df&   get_barycentre() { return barycentre; }
    inline Vec3Df&   get_n0()         { return v0; }
    inline Vec3Df&   get_n1()         { return v1; }
    inline Vec3Df&   get_n2()         { return v2; }
    inline Vec3Df&   get_normal()     { return normal; }
    inline float     get_distance()   { return distance; }

private:
    int object;
    int triangle;
    Material material;
    Vec3Df v0;
    Vec3Df v1;
    Vec3Df v2;
    Vec3Df barycentre;
    Vec3Df n0;
    Vec3Df n1;
    Vec3Df n2;
    Vec3Df normal;
    float distance;
};

#endif // KDLEAF_H
