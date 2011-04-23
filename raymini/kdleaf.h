#ifndef KDLEAF_H
#define KDLEAF_H

#include <vector>

#include "Material.h"
#include "Vertex.h"
#include "Vec3D.h"

class kdleaf
{
public:
    kdleaf(int object, int triangle, Material material, Vertex vertex0, Vertex vertex1, Vertex vertex2, Vec3Df p0, Vec3Df p1, Vec3Df p2, Vec3Df n0, Vec3Df n1, Vec3Df n2, Vec3Df camPos);
    inline int       get_object()     { return object; }
    inline int       get_triangle()   { return triangle; }
    inline Material& get_Material()   { return material; }
    inline Vertex&   get_vertex0()    { return vertex0; }
    inline Vertex&   get_vertex1()    { return vertex1; }
    inline Vertex&   get_vertex2()    { return vertex2; }
    inline Vec3Df&   get_p0()         { return p0; }
    inline Vec3Df&   get_p1()         { return p1; }
    inline Vec3Df&   get_p2()         { return p2; }
    inline Vec3Df&   get_barycentre() { return barycentre; }
    inline Vec3Df&   get_n0()         { return n0; }
    inline Vec3Df&   get_n1()         { return n1; }
    inline Vec3Df&   get_n2()         { return n2; }
    inline Vec3Df&   get_normal()     { return normal; }
    inline float     get_distance()   { return distance; }

private:
    int object;
    int triangle;
    Material material;
    Vertex vertex0;
    Vertex vertex1;
    Vertex vertex2;
    Vec3Df p0;
    Vec3Df p1;
    Vec3Df p2;
    Vec3Df barycentre;
    Vec3Df n0;
    Vec3Df n1;
    Vec3Df n2;
    Vec3Df normal;
    float distance;
};

#endif // KDLEAF_H
