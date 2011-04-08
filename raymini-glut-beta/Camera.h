// --------------------------------------------------------------------------
// Camera
//
// Copyright(C) 2010                
// Tamy Boubekeur
//                                                                            
// All rights reserved.                                                       
//                                                                            
// This program is free software; you can redistribute it and/or modify       
// it under the terms of the GNU General Public License as published by       
// the Free Software Foundation; either version 2 of the License, or          
// (at your option) any later version.                                        
//                                                                            
// This program is distributed in the hope that it will be useful,            
// but WITHOUT ANY WARRANTY; without even the implied warranty of             
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the              
// GNU General Public License (http://www.gnu.org/licenses/gpl.txt)           
// for more details.                                                          
//                                                                          
// --------------------------------------------------------------------------

#pragma once

#include "Vec3D.h"

class Camera {
public:
    Camera ();
    Camera (const Vec3Df & eye, const Vec3Df & center);
    virtual ~Camera () {}
  
    inline const Vec3Df & getEye () const { return eye; }
    inline const Vec3Df & getCenter () const { return center; }
    inline Vec3Df getViewDirection () const {
        Vec3Df v = center - eye;
        v.normalize ();
        return v;
    }
    inline Vec3Df getUpVector () const {
        Vec3Df Y (0.f, 1.f, 0.f);
        Vec3Df v = getViewDirection ();
        Vec3Df t = Vec3Df::crossProduct (Y, v);
        Vec3Df up = Vec3Df::crossProduct (v, t);
        up.normalize ();
        return up;
    }
    inline Vec3Df getRightVector () const {
        Vec3Df v (getViewDirection ());
        Vec3Df up (getUpVector ());
        return Vec3Df::crossProduct (v, up);
    }
    inline void setEye (const Vec3Df & e) { eye = e; }
    inline void setCenter (const Vec3Df & c) { center = c; }
    inline float getFovAngle () const { return fovAngle; }
    inline void setFovAngle (float newFovAngle) { fovAngle = newFovAngle; }
    inline float getAspectRatio () const { return aspectRatio; }
    inline float getNearPlane () const { return nearPlane; }
    inline void setNearPlane (float newNearPlane) { nearPlane = newNearPlane; }
    inline float getFarPlane () const { return farPlane; }
    inline void setFarPlane (float newFarPlane) { farPlane = newFarPlane; }
  
    void resize (int W, int H);
  
    void initDefault (const Vec3Df & eye, const Vec3Df & center);
    void showScene (const Vec3Df center, float radius);
    
    void move (const Vec3Df & d);
    void rotate (float theta, float phi);
    void zoom (float factor);
    void apply ();
  
    
private:
    Vec3Df eye;
    Vec3Df center;
    float fovAngle;
    float aspectRatio;
    float nearPlane;
    float farPlane;
};

// Some Emacs-Hints -- please don't remove:
//
//  Local Variables:
//  mode:C++
//  tab-width:4
//  End:
