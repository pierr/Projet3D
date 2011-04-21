#ifndef KDLEAF_H
#define KDLEAF_H

#include <vector>

class kdleaf
{
public:
    inline kdleaf(int object, int triangle, float distance) : object(object), triangle(triangle), distance(distance) {}
    inline int   get_object()   { return object; }
    inline int   get_triangle() { return triangle; }
    inline float get_distance() { return distance; }

private:
    int object;
    int triangle;
    float distance;
};

#endif // KDLEAF_H
