// *********************************************************
// Light Class
// Author : Tamy Boubekeur (boubek@gmail.com).
// Copyright (C) 2010 Tamy Boubekeur.
// All rights reserved.
// *********************************************************

#include "Light.h"
#define PI 3.141592

using namespace std;

const std::vector<Vec3Df> & Light::getPoints (Vec3Df & normal, int numr, int numa) const {
    std::vector<Vec3Df> * ret = new std::vector<Vec3Df>;

    //si c'est un disque, on prend plusierus points
    if(disk){
        Vec3Df u, v;
        normal.getTwoOrthogonals(u,v);
        u.normalize();
        v.normalize();

        float r;
        float a;
        float x;
        float y;

        for(int i=0; i<numr; i++){
            for(int j=0; j<numa; j++){
                r = i*rayon/(float)(numr);
                a = j*2*PI/(float)(numa);
                x = r*cos(a);
                y = r*sin(a);

                ret->push_back(pos + u*x + v*y);
            }
        }
    } else {
        //si ce n'est pas un disque, on a seulement la position
        ret->push_back(pos);
    }

    //on retourne l'ensemble de points
    return * ret;
}
