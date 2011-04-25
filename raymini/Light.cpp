// *********************************************************
// Light Class
// Author : Tamy Boubekeur (boubek@gmail.com).
// Copyright (C) 2010 Tamy Boubekeur.
// All rights reserved.
// *********************************************************

#include "Light.h"
#define PI 3.141592

using namespace std;

const std::vector<Vec3Df> & Light::getPoints (int numr, int numa) const {
    std::vector<Vec3Df> * ret = new std::vector<Vec3Df>;

    //si c'est un disque, on prend plusierus points
    if(disk && numr>0 && numa>0){
        Vec3Df u, v;
        normal.getTwoOrthogonals(u,v);
        u.normalize();
        v.normalize();

        float stepr = (float)rayon/(numr*numa);
        float stepa = (float)2*PI/numa;
        int inita = 1;
        int diva = 1;
        float a = 0;

        //pour chaque rayon
        float r = 0;
        for(int i=0; i<numr; i++){
            //pour chaque angle
            for(int j=0; j<numa; j++){
                ret->push_back(pos+u*(r*cos(a))+v*(r*sin(a)));
                a += stepa;
                r += stepr;
            }
            //si numa=2, au debut de chaque for a=0, puis stepa * 0.5, 0.25, 0.75, 0.125, 0.375, 0.625, 0.875, ...
            //seuelement des impaires
            inita += 2;
            if(a>1){
                inita = 1;
                diva *= 2;
            }
            a = (float)stepa*inita/diva;
        }
    } else {
        //si ce n'est pas un disque, on a seulement la position
        ret->push_back(pos);
    }

    //on retourne l'ensemble de points
    return * ret;
}
