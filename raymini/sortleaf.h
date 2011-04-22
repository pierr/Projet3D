#ifndef SORTLEAF_H
#define SORTLEAF_H

#include <vector>

class sortleaf
{
public:
    inline sortleaf(int object, int triangle, float distance) : object(object), triangle(triangle), distance(distance) {}
    inline int   get_object()   { return object; }
    inline int   get_triangle() { return triangle; }
    inline float get_distance() { return distance; }

private:
    int object;
    int triangle;
    float distance;
};

#endif // SORTLEAF_H
