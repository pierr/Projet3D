// *********************************************************
// Ray Class
// Author : Tamy Boubekeur (boubek@gmail.com).
// Copyright (C) 2010 Tamy Boubekeur.
// All rights reserved.
// *********************************************************

#ifndef RAY_H
#define RAY_H

#include <iostream>
#include <vector>

#include "Vec3D.h"
#include "BoundingBox.h"
#include "Triangle.h"
#include "Material.h"
#include "Scene.h"
#include "Light.h"
#include "kdnode.h"
class Ray {
public:
    inline Ray () {}
    inline Ray (const Vec3Df & origin, const Vec3Df & direction)
        : origin (origin), direction (direction) {
//			this.direction.normalize();
}
    inline virtual ~Ray () {}

    inline const Vec3Df & getOrigin () const { return origin; }
    inline Vec3Df & getOrigin () { return origin; }
    inline const Vec3Df & getDirection () const { return direction; }
    inline Vec3Df & getDirection () { return direction; }

    bool intersect (const BoundingBox & bbox, Vec3Df & intersectionPoint) const;
    bool intersect ( const Triangle & tri, std::vector<Vertex> & verteces, Vec3Df & intersectionPoint) const;
    bool intersect(Vec3Df & v0 , Vec3Df & v1, Vec3Df & v2, Vec3Df n, Vec3Df & intersectionPoint) const;

    /**
      Le but de cette fonction est de calculer la brdf pour chacun des triangles pour chacun des rayons qui sont tracés.
    @param v est le barycentre du triangle
    @param m est le material du triangle
    @param radiance est la radiance qu'on va modifier.
    */
    void calcBRDF(Vec3Df & p, Vec3Df & n, Material & m,  Vec3Df & color);
    /**
      Le but de cette méthode est de calculer pour chaque rayon les triangles qui intersectent ce rayon , les triangles sont issus des objets qui composent la scène.
    */
    Vec3Df intersectkdScene(BoundingBox & scenebox, std::vector<kdnode> & kdboxes);
private:
    Vec3Df origin;
    Vec3Df direction;
};


#endif // RAY_H

// Some Emacs-Hints -- please don't remove:
//
//  Local Variables:
//  mode:C++
//  tab-width:4
//  End:
