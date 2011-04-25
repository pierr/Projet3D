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
    Ray (const Vec3Df & origin, const Vec3Df & direction);
    inline virtual ~Ray () {}

    inline const Vec3Df & getOrigin () const { return origin; }
    inline Vec3Df & getOrigin () { return origin; }
    inline const Vec3Df & getDirection () const { return direction; }
    inline Vec3Df & getDirection () { return direction; }

    bool intersect (const BoundingBox & bbox, Vec3Df & intersectionPoint) const;
    bool intersect ( const Triangle & tri, std::vector<Vertex> & verteces, Vec3Df & intersectionPoint) const;
    bool intersect(Vertex & v0 , Vertex & v1, Vertex & v2, Vec3Df & intersectionPoint) const;

    /**
      Le but de cette fonction est de calculer la brdf pour chacun des triangles pour chacun des rayons qui sont tracés.
    @param v est le barycentre du triangle
    @param m est le material du triangle
    @param radiance est la radiance qu'on va modifier.
    */
    void calcBRDF(Vertex & bary,  Material & m, Vec3Df& color, kdnode * root);
    /**
      Le but de cette méthode est de calculer pour chaque rayon les triangles qui intersectent ce rayon , les triangles sont issus des objets qui composent la scène.
    */
    bool kd_intersect(kdnode * root, Vertex & isv, Material & ism, float & mindist);

    Vec3Df calcul_radiance( kdnode * root);
    float calcAmbOcclusion(kdnode * root, Vertex & isv, float & rayonSphere, float & theta);
   // Vec3Df perturbateVector(Vec3Df & originVecor, float  & teta);
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
