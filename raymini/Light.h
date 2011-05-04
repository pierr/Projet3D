// *********************************************************
// Light Class
// Author : Tamy Boubekeur (boubek@gmail.com).
// Copyright (C) 2010 Tamy Boubekeur.
// All rights reserved.
// *********************************************************

#ifndef LIGHT_H
#define LIGHT_H

#include <stdlib.h>
#include <iostream>
#include <vector>

#include "Vec3D.h"

class Light {
public:
    inline Light () : disk(false), color (Vec3Df (1.0f, 1.0f, 1.0f)), intensity (1.0f) {}
    inline Light (const Vec3Df & pos, const Vec3Df & color, float intensity)
        : disk(false), pos (pos), color (color),                               intensity (intensity) {}
    inline Light (const Vec3Df & pos, const Vec3Df & color, float rayon, float intensity)
        : disk(true),  pos (pos), color (color), rayon(rayon), intensity (intensity) {}
    virtual ~Light () {}

    inline const Vec3Df & getPos () const { return pos; }
    inline const Vec3Df & getColor () const { return color; }
    inline float getIntensity () const { return intensity; }
    const std::vector<Vec3Df> & getPoints (Vec3Df & normal, int numr, int numa) const;

    inline void setPos (const Vec3Df & p) { pos = p; }
    inline void setColor (const Vec3Df & c) { color = c; }
    inline void setIntensity (float i) { intensity = i; }

    
private:
    bool disk;
    Vec3Df pos;
    Vec3Df color;
    float rayon;
    float intensity;
};


#endif // LIGHT_H

// Some Emacs-Hints -- please don't remove:
//
//  Local Variables:
//  mode:C++
//  tab-width:4
//  End:
