#ifndef KDLEAF_H
#define KDLEAF_H

#include <vector>
#include <Vec3D.h>

class kdleaf
{
public:
    kdleaf(int object, int triangle, Vec3Df v0, Vec3Df v1, Vec3Df v2);
    inline int      get_object()   { return object; }
    inline int      get_triangle() { return triangle; }
    inline Vec3Df&  get_v0()      { return v0; }
    inline Vec3Df&  get_v1()      { return v1; }
    inline Vec3Df&  get_v2()      { return v2; }
    inline Vec3Df&  get_barycentre(){ return barycentre; }

private:
    int object;
    int triangle;
    Vec3Df v0;
    Vec3Df v1;
    Vec3Df v2;
    Vec3Df barycentre;
};

#endif // KDLEAF_H
