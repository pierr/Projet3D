// *********************************************************
// Ray Tracer Class
// Author : Tamy Boubekeur (boubek@gmail.com).
// Copyright (C) 2010 Tamy Boubekeur.
// All rights reserved.
// *********************************************************

#include "RayTracer.h"

#include <time.h>

using namespace std;

static RayTracer * instance = NULL;

RayTracer * RayTracer::getInstance () {
    if (instance == NULL)
        instance = new RayTracer ();
    return instance;
}

void RayTracer::destroyInstance () {
    if (instance != NULL) {
        delete instance;
        instance = NULL;
    }
}

inline int clamp (float f, int inf, int sup) {
    int v = static_cast<int> (f);
    return (v < inf ? inf : (v > sup ? sup : v));
}

// POINT D'ENTREE DU PROJET.
// Le code suivant ray trace uniquement la boite englobante de la scene.
// Il faut remplacer ce code par une veritable raytracer
QImage RayTracer::render (const Vec3Df & camPos,
                          const Vec3Df & direction,
                          const Vec3Df & upVector,
                          const Vec3Df & rightVector,
                          float fieldOfView,
                          float aspectRatio,
                          unsigned int screenWidth,
                          unsigned int screenHeight) {
    time_t tstart, tstop;
    tstart = time (NULL);
  
    QImage image (QSize (screenWidth, screenHeight), QImage::Format_RGB888);
    
    Scene * scene = Scene::getInstance ();

    //splitter l'espace en boundingbox a travers un kdtree..
    if(param->get_kddone()){
        BoundingBox scenebox = scene->getBoundingBox();
        kdt = new kdtree(scene->getObjects(), camPos, scenebox);
        kdt->split(param->get_kdpropdeep());
        param->set_kddone();
    }

    float pctstep = 0.01;
    float pct = -pctstep;

#pragma omp parallel for
    for (unsigned int i = 0; i < screenWidth; i++){
        for (unsigned int j = 0; j < screenHeight; j++) {
            float tanX = tan (fieldOfView);
            float tanY = tanX/aspectRatio;
            Vec3Df col;
            for(int k1=0; k1<param->get_pixgrille(); k1++){
                for(int k2=0; k2<param->get_pixgrille(); k2++){
                    Vec3Df stepX = (float (i+(k1/param->get_pixgrille())) - screenWidth/2.f)/screenWidth * tanX * rightVector;
                    Vec3Df stepY = (float (j+(k2/param->get_pixgrille())) - screenHeight/2.f)/screenHeight * tanY * upVector;
                    Vec3Df step = stepX + stepY;
                    Vec3Df dir = direction + step;
                    Ray ray (camPos, dir, backgroundColor, param);
                    //Si on choisit la méthode de rendu path tracing
                    if(param->get_pathactive()){
                        Material m();
                        col+=255.f*ray.pathTracing(kdt->get_root(),1.0f,0);
                    } else {
                    //Sinon on applique les autres méthodes de rendu
                        col += 255.f*ray.calcul_radiance(kdt->get_root());
                    }
                }
            }
            col = col/(param->get_pixgrille()*param->get_pixgrille());
            image.setPixel (i, ((screenHeight-1)-j), qRgb (clamp (col[0], 0, 255),
                                                           clamp (col[1], 0, 255),
                                                           clamp (col[2], 0, 255)));
            if((float)(i*screenHeight+j)/(screenHeight*screenWidth) > pct){
                pct += pctstep;
                cout << pct << endl;
            }
        }
    }

    tstop = time (NULL);
    cout << "time " << tstop-tstart << endl;

    return image;
}
