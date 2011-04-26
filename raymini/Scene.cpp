// *********************************************************
// Scene Class
// Author : Tamy Boubekeur (boubek@gmail.com).
// Copyright (C) 2010 Tamy Boubekeur.
// All rights reserved.
// *********************************************************

#include "Scene.h"
#include <string>
using namespace std;

static Scene * instance = NULL;

Scene * Scene::getInstance () {
    if (instance == NULL)
        instance = new Scene ();
    return instance;
}

void Scene::destroyInstance () {
    if (instance != NULL) {
        delete instance;
        instance = NULL;
    }
}

Scene::Scene () {
    buildDefaultScene (false);
    updateBoundingBox ();
}

Scene::~Scene () {
}

void Scene::updateBoundingBox () {
    if (objects.empty ())
        bbox = BoundingBox ();
    else {
        bbox = objects[0].getBoundingBox ();
        for (unsigned int i = 1; i < objects.size (); i++)
            bbox.extendTo (objects[i].getBoundingBox ());
    }
}

string getFileName(int num){
    string out = "models/";
    switch(num){
    case 1:
        out+="Apple.off";
        break;
    case 2:
        out+="triceratops.off";
        break;
    default:
    out+="monkey.off";

    }
    return out;
}


// Changer ce code pour créer des scènes originales
void Scene::buildDefaultScene (bool HD) {
    Mesh groundMesh;
    bool debug = false;
    if (debug){
        groundMesh.loadOFF (getFileName(2));//"models/sphere.off");
        Material groundMat(0.735f,1.656f, Vec3Df (1.f, .795f, .504f));
    Object ground (groundMesh, groundMat);
    objects.push_back (ground);
    }else{
    if (HD)
        groundMesh.loadOFF ("models/ground_HD.off");
    else
        groundMesh.loadOFF ("models/ground.off");
        Material groundMat;
    Object ground (groundMesh, groundMat);    
    objects.push_back (ground);
    Mesh ramMesh;
    if (HD)
        ramMesh.loadOFF ("models/ram_HD.off");
    else
//        ramMesh.loadOFF ("models/ram.off");
    ramMesh.loadOFF (getFileName(3));
    //Material ramMat (1.f, 1.f, Vec3Df (1.f, .6f, .2f));
    Material ramMat(0.735f,1.656f, Vec3Df (1.f, .795f, .504f));
    Object ram (ramMesh, ramMat);
    objects.push_back (ram);
    }
//    Light l (Vec3Df (3.0f, 3.0f, 3.0f), Vec3Df (1.0f, 1.0f, 1.0f), 1.0f);                                           // point
    Light ldisk (Vec3Df (3.0f, 3.0f, 3.0f), Vec3Df (1.0f, 1.0f, 1.0f), Vec3Df(-1.0f, -1.0f, -1.0f), 0.5f, 1.0f);    // disque
    lights.push_back (ldisk);
}
