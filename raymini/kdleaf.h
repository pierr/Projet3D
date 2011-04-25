#ifndef KDLEAF_H
#define KDLEAF_H

#include <vector>

#include "Material.h"
#include "Vertex.h"
#include "Vec3D.h"

class kdleaf
{
public:
    kdleaf(int object, int triangle, Material material, Vertex vertex0, Vertex vertex1, Vertex vertex2, Vec3Df normal, Vec3Df camPos);
    inline int              get_object()     { return object; }
    inline int              get_triangle()   { return triangle; }
    inline Material&        get_Material()   { return material; }
    inline Vertex&          get_vertex0()    { return vertex0; }
    inline Vertex&          get_vertex1()    { return vertex1; }
    inline Vertex&          get_vertex2()    { return vertex2; }
    inline const Vec3Df&    get_p0()         { return vertex0.getPos(); }
    inline const Vec3Df&    get_p1()         { return vertex1.getPos(); }
    inline const Vec3Df&    get_p2()         { return vertex2.getPos(); }
    inline Vec3Df&          get_barycentre() { return barycentre; }
    inline Vec3Df&          get_normal()     { return normal; }
    inline float            get_distance()   { return distance; }

private:
    int object;
    int triangle;
    Material material;
    Vertex vertex0;
    Vertex vertex1;
    Vertex vertex2;
    Vec3Df barycentre;
    Vec3Df normal;
    float distance;
};

#endif // KDLEAF_H
