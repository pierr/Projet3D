// --------------------------------------------------------------------------
//
// Camera Class
//
// Copyright(C) 2007-2009                
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

#include "Camera.h"
#include <GL/gl.h>
#include <GL/glu.h>
#include <iostream>

using namespace std;

Camera::Camera () {
    initDefault (Vec3Df (0.f, 0.f, 1.f), Vec3Df (0.f, 0.f, 0.f));
}

Camera::Camera (const Vec3Df & eye, const Vec3Df & center) {
    initDefault (eye, center);
}

void Camera::resize (int W, int H) {
  glViewport (0, 0, (GLint)W, (GLint)H);
  glMatrixMode (GL_PROJECTION);
  glLoadIdentity ();
  aspectRatio = static_cast<float>(W)/static_cast<float>(H);
  gluPerspective (fovAngle, aspectRatio, nearPlane, farPlane);
  glMatrixMode (GL_MODELVIEW);
}

void Camera::initDefault (const Vec3Df & e, const Vec3Df & c) {
    eye = e;
    center = c;
    fovAngle = 45.f;
    aspectRatio = 1.f;
    nearPlane = 1.f;
    farPlane = 10000.f;
}

void Camera::showScene (const Vec3Df c, float radius) {
    center = c;
    eye = center + Vec3Df (0.f, 0.f, radius);
}

void Camera::move (const Vec3Df & d) {
    eye += d;
    center += d;
}

void Camera::rotate (float theta, float phi) {
    Vec3Df up (getUpVector ());
    Vec3Df right (getRightVector ());
    Vec3Df ce (eye - center);
    float d = ce.getLength ();
    ce.normalize ();
    Vec3Df c = Vec3Df (sin (theta), sin (phi), cos (theta));
    eye = center + d * (c[0]*right + c[1]*up + c[2]*ce);
}

void Camera::zoom (float factor) {
    eye = center + factor*(eye-center);
}

void Camera::apply () {
    glLoadIdentity();
    Vec3Df up = getUpVector ();
    gluLookAt (eye[0], eye[1], eye[2],
               center[0], center[1], center[2],
               up[0], up[1], up[2]);
}


