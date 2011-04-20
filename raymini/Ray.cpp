// *********************************************************
// Ray Class
// Author : Tamy Boubekeur (boubek@gmail.com).
// Copyright (C) 2010 Tamy Boubekeur.
// All rights reserved.
// *********************************************************

#include "Ray.h"

using namespace std;

static const unsigned int NUMDIM = 3, RIGHT = 0, LEFT = 1, MIDDLE = 2;

bool Ray::intersect (const BoundingBox & bbox, Vec3Df & intersectionPoint) const {
    const Vec3Df & minBb = bbox.getMin ();
    const Vec3Df & maxBb = bbox.getMax ();
    bool inside = true;
    unsigned int  quadrant[NUMDIM];
    register unsigned int i;
    unsigned int whichPlane;
    Vec3Df maxT;
    Vec3Df candidatePlane;
    
    for (i=0; i<NUMDIM; i++)
        if (origin[i] < minBb[i]) {
            quadrant[i] = LEFT;
            candidatePlane[i] = minBb[i];
            inside = false;
        } else if (origin[i] > maxBb[i]) {
            quadrant[i] = RIGHT;
            candidatePlane[i] = maxBb[i];
            inside = false;
        } else	{
            quadrant[i] = MIDDLE;
        }

    if (inside)	{
        intersectionPoint = origin;
        return (true);
    }

    for (i = 0; i < NUMDIM; i++)
        if (quadrant[i] != MIDDLE && direction[i] !=0.)
            maxT[i] = (candidatePlane[i]-origin[i]) / direction[i];
        else
            maxT[i] = -1.;

    whichPlane = 0;
    for (i = 1; i < NUMDIM; i++)
        if (maxT[whichPlane] < maxT[i])
            whichPlane = i;

    if (maxT[whichPlane] < 0.) return (false);
    for (i = 0; i < NUMDIM; i++)
        if (whichPlane != i) {
            intersectionPoint[i] = origin[i] + maxT[whichPlane] *direction[i];
            if (intersectionPoint[i] < minBb[i] || intersectionPoint[i] > maxBb[i])
                return (false);
        } else {
            intersectionPoint[i] = candidatePlane[i];
        }
    return (true);			
}

bool Ray::intersection(Vec3Df v0, Vec3Df v1, Vec3Df v2){
	//on doit normaliser la normale!
	Vec3Df n = Vec3Df::crossProduct(v1-v0,v2-v0);
	n.normalize();
	//on projete (is =  intersection)
	Vec3Df oproj = o.projectOn(n,v0);
	Vec3Df dproj = d.projectOn(n,v0);

        float dprojoproj = Vec3Df::distance(dproj,oproj);
        float ooproj = Vec3Df::distance(o,oproj);
        float oprojis = dprojoproj*ooproj/sqrt(1-pow(dprojoproj,2));

        Vec3Df is = oproj+dproj*oprojis/dproj.getLength();
	//on regarde si la projection "is" est dans le triangle
	if(Vec3Df::dotProduct(v0-is,v0-(v1+v2)*0.5)<0)		return false;
	else if(Vec3Df::dotProduct(v1-is,v0-(v0+v2)*0.5)<0)	return false;
	else if(Vec3Df::dotProduct(v2-is,v0-(v0+v1)*0.5)<0)	return false;
	return true;
}

