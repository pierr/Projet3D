// *********************************************************
// Scene Class
// Author : Tamy Boubekeur (boubek@gmail.com).
// Copyright (C) 2010 Tamy Boubekeur.
// All rights reserved.
// *********************************************************

#include "Scene.h"
#include <string>
#include "Vec3D.h"
#include "Matrix.h"
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
    case 3:
        out+="3d.off";
    break;
    case 4:
        out+="bunny2.off";
    break;
    case 5:
        out+="ground_HD.off";
    break;
    case 6:
        out+="sphere.off";
    break;
    case 7:
        out+="THEIERE.OFF";
    case 8:
        out+="room.off";
        break;
    case 9:
        out+="CHERRY.OFF";
        break;
    case 10:
        out+="sphere.off";
        break;
    /*camel_head.off   horse.off        squirrel.off
    CHERRY.OFF       double-torus.off max.off.off      tri.off
    DAUPHIN.OFF      double_ram.off   max_50K.off      triceratops.off
    THEIERE.OFF      fandisk.off      monkey.off       tweety.off
    armadillo.off    gargoyle.off     ram.off
    bunny.off        ground.off       ram_HD.off
*/
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
        groundMesh.loadOFF (getFileName(10));//"models/sphere.off");
        Material groundMat(0.735f,1.656f, Vec3Df (1.f, .795f, .504f));
    Object ground (groundMesh, groundMat);
    objects.push_back (ground);
    }else{

    /*Ici on récupère ou on défini les paramêtres de chaque objet*/
    //Param Shape
    string fileNameShape = getFileName(6);//Nom du fichier à charger
    Vec3Df transShape = Vec3Df (0.f, 2.f, 1.f);// de combien on le translate
    float grandShape = 1.f; // de combien on multiplie la forme
    //param Ground
    string fileNameGround = "models/ground.off";
    Vec3Df transGround;//De combien on veut le translater
    float grandGround = 7.f; // de combien on multiplie le fond

    //MatriceDe Rotation
    //cout << "X" << endl;
    RotationMatrix nulRot(0., Matrix::X);
   // RotationMatrix fortyRot(45., Vec3Df(1.,1.,1.));//
    RotationMatrix fortyRot(45., Matrix::Y);
    //std::cout << fortyRot << std::endl;

    if (HD)
        groundMesh.loadOFF ("models/ground_HD.off", transGround, grandGround, nulRot);
    else
        groundMesh.loadOFF (fileNameGround,transGround, grandGround,  nulRot);
    Material groundMat;
    Object ground (groundMesh, groundMat);    
    objects.push_back (ground);
    Mesh ramMesh;
    if (HD)
        ramMesh.loadOFF ("models/ram_HD.off");
    else
    ramMesh.loadOFF (fileNameShape, transShape,grandShape, nulRot);
    //Material ramMat (1.f, 1.f, Vec3Df (1.f, .6f, .2f));//old rammat
    Material ramMat(0.735f,1.656f, Vec3Df (1.f, .795f, .504f));
    Object ram (ramMesh, ramMat);
    objects.push_back (ram);

    Mesh theiere;
    string fileTheiere = getFileName(10);
    Vec3Df transTheiere = Vec3Df (1.f, -1.795f, 1.504f);// de combien on le translate
    float grandTheiere =1.f; // de combien on multiplie la forme
    theiere.loadOFF(fileTheiere, transTheiere, grandTheiere, nulRot);
    Material theiMat(0.235f,0.656f, Vec3Df (119.f/255, 181.f/255, 254.f/255));
    Object theier(theiere,theiMat);
    objects.push_back(theier);

}
    Light l (Vec3Df (3.0f, 1.0f, 3.0f), Vec3Df (1.0f, 1.0f, 1.0f), 1.0f);                                           // point
//    Light ldisk (Vec3Df (3.0f, 3.0f, -10.0f), Vec3Df (1.0f, 1.0f, 1.0f), Vec3Df(-1.0f, -1.0f, -1.0f), 0.5f, 1.0f);    // disque
    lights.push_back (l);
}
