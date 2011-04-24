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
    const BoundingBox & bbox = scene->getBoundingBox ();
    const Vec3Df & minBb = bbox.getMin ();
    const Vec3Df & maxBb = bbox.getMax ();
    const Vec3Df rangeBb = maxBb-minBb;

    //ordonner les triangles selon distance
    sorttree * sdt = new sorttree(scene->getObjects(), camPos);
    sdt->sort();
    std::vector<kdleaf> leafs = sdt->get_leafs();

    //splitter l'espace en boundingbox a travers un kdtree..
    int kddeep = 5;
    BoundingBox scenebox = scene->getBoundingBox();
    kdtree * kdt = new kdtree(kddeep, leafs, scenebox);
    kdt->split();
    std::vector<kdnode> kdboxes = kdt->get_boxes();
    delete kdt;
    delete sdt;
    kdt = 0;
    sdt = 0;

    //ordonner les boites selon distance
//    boxtree * bt = new boxtree(kdboxes,camPos);
//    bt->sort();
//    bt->get_kdboxes();

    //on calcule pixel par pixel
    cout << "npixel = " << screenHeight*screenWidth << endl;

    float pctstep = 0.01;
    float pct = -pctstep;
    #pragma omp parallel for
    for (unsigned int i = 0; i < screenWidth; i++){
        for (unsigned int j = 0; j < screenHeight; j++) {
            float tanX = tan (fieldOfView);
            float tanY = tanX/aspectRatio;
            Vec3Df stepX = (float (i) - screenWidth/2.f)/screenWidth * tanX * rightVector;
            Vec3Df stepY = (float (j) - screenHeight/2.f)/screenHeight * tanY * upVector;
            Vec3Df step = stepX + stepY;
            Vec3Df dir = direction + step;
            dir.normalize ();
            Ray ray (camPos, dir);
            Vec3Df col = 255.f*ray.intersectkdScene(camPos, scenebox, kdboxes);
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
