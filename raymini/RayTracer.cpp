// *********************************************************
// Ray Tracer Class
// Author : Tamy Boubekeur (boubek@gmail.com).
// Copyright (C) 2010 Tamy Boubekeur.
// All rights reserved.
// *********************************************************

#include <vector>

#include "RayTracer.h"
#include "Ray.h"
#include "Scene.h"
#include "sorttree.h"
#include "kdtree.h"

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
    QImage image (QSize (screenWidth, screenHeight), QImage::Format_RGB888);
    
    Scene * scene = Scene::getInstance ();
    const BoundingBox & bbox = scene->getBoundingBox ();
    const Vec3Df & minBb = bbox.getMin ();
    const Vec3Df & maxBb = bbox.getMax ();
    const Vec3Df rangeBb = maxBb-minBb;

    //ordonner les triangles selon distance avec un sorttree
    sorttree* sortt = new sorttree(scene->getObjects(),camPos);
    sdt->sort();
    std::vector<sortleaf> sortleafs = sortt->get_leafs();
    delete sortt;
    sortt = 0;


    //ordonner les triangles selon pixels
    kdtree* kdt = new kdtree(sortleafs,screenHeight,screenWidth,fieldOfView,aspectRatio,rightVector,upVector);
    kdtree->sort();
    std::vector<kdleaf> kdleafs = kdt->get_leafs();
    delete kdt;
    kdt = 0;

    //on calcule pixel par pixel
    cout << "npixel = " << screenHeight*screenWidth << endl;
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
            Vec3Df col = 255.f*ray.intersectkdScene(kdleafs);
            image.setPixel (i, ((screenHeight-1)-j), qRgb (clamp (col[0], 0, 255),
                                                           clamp (col[1], 0, 255),
                                                           clamp (col[2], 0, 255)));
            cout << (float)(i*screenHeight+j)/(screenHeight*screenWidth) << endl;
        }
    }
    return image;
}
