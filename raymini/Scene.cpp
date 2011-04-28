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
   // buildDefaultScene (false);
  //buildScene2buffleHD();
  buildSceneSpheres();
//   buildSceneManyCircles();
    // simpleScene();
//buildNormalGround();
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

string getFileName(Object::objName objName){
    string out = "models/";
    switch(objName){
    case Object::apple :
        out+="Apple.off";
        break;
    case Object::triceratops :
        out+="triceratops.off";
        break;
    case Object::threeD :
        out+="3d.off";
        break;
    case Object::bunny2 :
        out+="bunny2.off";
        break;
    case Object::ground_HD :
        out+="ground_HD.off";
        break;
    case Object::sphere :
        out+="sphere.off";
        break;
    case Object::theiere :
        out+="THEIERE.OFF";
    case Object::room_f :
        out+="room_f.off";
        break;
    case Object::room :
        out+="room.off";
        break;
    case Object::cherry :
        out+="CHERRY.OFF";
        break;
    case Object::ram_HD:
        out+="ram_HD.off";
        break;
    case Object::ram:
        out+="ram.off";
        break;
    case Object::coloredGlass:
        out+="coloredGlass0.off";
        break;

    case Object::opened_cube:
        out+="opened_cube.off";
        break;
        /*camel_head.off   horse.off        squirrel.off
    CHERRY.OFF       double-torus.off max.off.off      tri.off
    DAUPHIN.OFF      double_ram.off   max_50K.off      triceratops.off
    THEIERE.OFF      fandisk.off      monkey.off       tweety.off
    armadillo.off    gargoyle.off     ram.off
    bunny.off        ground.off       ram_HD.off
*/
    case Object::ground:
        out+="ground.off";
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
       buildScene2buffleHD();
        //buildSceneManyCircles();
        //simpleScene();
    }else{

        /*Ici on récupère ou on défini les paramêtres de chaque objet*/
        //Param Shape
        string fileNameShape = getFileName(Object::ram_HD);//Nom du fichier à charger
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
        string fileTheiere = getFileName(Object::ram_HD);
        Vec3Df transTheiere = Vec3Df (1.f, -1.795f, 1.504f);// de combien on le translate
        float grandTheiere =0.1f; // de combien on multiplie la forme
        theiere.loadOFF(fileTheiere, transTheiere, grandTheiere, nulRot);
        Material theiMat(0.235f,0.656f, Vec3Df (119.f/255, 181.f/255, 254.f/255));
        Object theier(theiere,theiMat);
        objects.push_back(theier);

    }
    loadLights(0);
}
void Scene::buildScene2buffleHD(){
    buildNormalGround();
    std::cout << "Scene avec le sol et deux buffles" << std::endl;
    /*Ici on récupère ou on défini les paramêtres de chaque objet*/
    //Param Shape
    string fileNameShape = getFileName(Object::ram_HD);//Nom du fichier à charger
    Vec3Df transShape = Vec3Df (0.f, 2.f, 1.f);// de combien on le translate
    float grandShape = 1.f; // de combien on multiplie la forme
    //param Ground
    string fileNameGround = "models/ground.off";
    Vec3Df transGround;//De combien on veut le translater
    float grandGround = 7.f; // de combien on multiplie le fond

    //MatriceDe Rotation
    RotationMatrix nulRot(0., Matrix::X);
    RotationMatrix fortyRot(45., Matrix::Y);
    Mesh groundMesh;
    groundMesh.loadOFF (fileNameGround,transGround, grandGround,  nulRot);
    Material groundMat;
    Object ground (groundMesh, groundMat);    
    //objects.push_back (ground);
    Mesh ramMesh;

    ramMesh.loadOFF (fileNameShape, transShape,grandShape, nulRot);
    //Material ramMat (1.f, 1.f, Vec3Df (1.f, .6f, .2f));//old rammat
    Material ramMat(0.735f,1.656f, Vec3Df (1.f, .795f, .504f));
    Object ram (ramMesh, ramMat);
    objects.push_back (ram);

    Mesh theiere;
    string fileTheiere = getFileName(Object::coloredGlass);
    Vec3Df transTheiere = Vec3Df (1.f, -1.795f, 1.504f);// de combien on le translate
    float grandTheiere =1.f; // de combien on multiplie la forme
    theiere.loadOFF(fileTheiere, transTheiere, grandTheiere, nulRot);
    Material theiMat(0.235f,0.656f, Vec3Df (119.f, 181.f, 254.f));
    Object theier(theiere,theiMat);
    objects.push_back(theier);

    loadLights(1);
}
void Scene::buildSceneSpheres() {
    Mesh groundMesh;
    RotationMatrix nulRot(0., Matrix::X);

    /*Ici on récupère ou on défini les paramêtres de chaque objet*/
    //Param Shape
    string fileNameShape = getFileName(Object::sphere);//Nom du fichier à charger
    Vec3Df transShape = Vec3Df (0.f, 2.f, 1.f);// de combien on le translate
    float grandShape = 1.f; // de combien on multiplie la forme
    //param Ground
    string fileNameGround = "models/ground.off";
    Vec3Df transGround;//De combien on veut le translater
    float grandGround = 7.f; // de combien on multiplie le fond


    groundMesh.loadOFF(fileNameGround,transGround, grandGround,nulRot);
    Material groundMat;
    Object ground (groundMesh, groundMat);
    objects.push_back (ground);
    Mesh ramMesh;

    ramMesh.loadOFF (fileNameShape, transShape,grandShape,nulRot);
    //Material ramMat (1.f, 1.f, Vec3Df (1.f, .6f, .2f));//old rammat
    Material ramMat(0.735f,1.656f, Vec3Df (1.f, .795f, .504f));
    Object ram (ramMesh, ramMat);
    objects.push_back (ram);

    Mesh theiere;
    string fileTheiere = getFileName(Object::sphere);
    Vec3Df transTheiere = Vec3Df (0.f, 0.f, 1.f);// de combien on le translate
    float grandTheiere = 1.0f; // de combien on multiplie la forme
    theiere.loadOFF(fileTheiere, transTheiere, grandTheiere, nulRot);
    Material theiMat(0.235f,0.656f, Vec3Df (0.5f, 0.f, .8f));
    Object theier(theiere,theiMat);
    objects.push_back(theier);

    loadLights(2);
}

void Scene::loadLights(int type){
    Light l (Vec3Df (3.0f, 0.0f, 1.0f), Vec3Df (1.0f, 1.0f, 1.0f), 1.0f);
    Light ldisk (Vec3Df (3.0f, 3.0f, -3.0f), Vec3Df (1.0f, 1.0f, 1.0f), Vec3Df(-3.0f, -3.0f, 10.0f), 0.5f, 10.0f);
Light ldisk2 (Vec3Df (-3.0f, -3.0f, 3.0f), Vec3Df (1.0f, 1.0f, -1.0f), Vec3Df(-1.0f, -1.0f, 1.0f), 0.5f, 1.0f);
    lights.push_back (ldisk);
    switch(type){
    case 0:
        lights.push_back (l);
        break;
    case 1:
        lights.push_back (ldisk);
        lights.push_back (ldisk2);
        break;
    default:
        break;
    }


}
//Juste pour charger un mur dans la scène
void Scene::buildGroundWall(){
    Mesh sol;
    string fileName = getFileName(Object::ground);
    Vec3Df transGround;//De combien on veut le translater
    float grandGround = 1.f; // de combien on multiplie le fond
    RotationMatrix nulRot(0., Matrix::X);
    sol.loadOFF(fileName,transGround,grandGround,nulRot);
    Material groundMat;
    Object soll (sol, groundMat);
    objects.push_back(soll);
    //float len = soll.getBoundingBox().getWidth();
    float xmax =0.f;
    float ymax =0.f;
    float zmax =0.f;
    float xmin =100.f;
    float ymin =100.f;
    float zmin =100.f;
    for(unsigned int i =0; i< sol.getVertices().size(); i++){
        Vertex v = sol.getVertices().at(i);
        Vec3Df s = v.getPos();
        if(s[0] > xmax){xmax = s[0];}
        if(s[1] > ymax){ymax = s[1];}
        if(s[2] > zmax){zmax = s[2];}
        if(s[0] < xmin){xmin = s[0];}
        if(s[1] < ymin){ymin = s[1];}
        if(s[2] < zmin){zmin = s[2];}
    }
    //soll.updateBoundingBox();
    std::cout << soll.getBoundingBox().getHeight() << " " <<  soll.getBoundingBox().getWidth() << " "  <<  soll.getBoundingBox().getLength() << std::endl;
    std::cout << xmax -xmin << " " << ymax-ymin << " " << zmax-zmin << std::endl;
    Mesh sol2;
    RotationMatrix ninetyRot(90.,Matrix::Y);
     Vec3Df transGround2( (xmax -xmin)/2,(ymax-ymin)/2,0.f);
     transGround2.normalize();
     //std::cout << len << std::endl;
     //std::cout << transGround2 << std::endl;
    sol2.loadOFF(fileName,transGround2,grandGround, ninetyRot);
    Object soll2(sol2, groundMat);
    objects.push_back(soll2);

}

float rand2(){
    return  rand()/(float)RAND_MAX  ;
}

//Juste pour charger
void Scene::buildSceneManyCircles(){
    buildNormalGround();

     string fileName = getFileName(Object::ram);
// Material mat(rand2(),rand2(), Vec3Df (rand2(), rand2(), rand2()));
 Vec3Df trans;
 for(int i =0; i < 16; i++){
 Material mat(rand2(),rand2(), Vec3Df (rand2(), rand2(), rand2()));
     Mesh m;
         float grand = 1.f;//*i/3;
         if(i < 8){
            Vec3Df trans1(1.f,2.5f*i,1.f);
            trans = trans1;
         }else {

         Vec3Df trans2(2.5f*(i-8),1.f,1.f);
            trans = trans2;
         }
         if(i ==1 ){
        Vec3Df trasn(-3.0f, -3.0f, 10.0f);
            trans = trasn;
         }
         RotationMatrix rot(180./4*(i+1.),Matrix::Z);
        // std::cout << rot << std::endl;

        m.loadOFF(fileName,trans,grand, rot);
        Object obj(m, mat);
        objects.push_back(obj);
    }

    loadLights(1);
}

void Scene::buildNormalGround(){
    Mesh sol;
    string fileName = getFileName(Object::ground);
    Vec3Df transGround;//De combien on veut le translater
    float grandGround = 8.f; // de combien on multiplie le fond
    RotationMatrix nulRot(0., Matrix::X);
    sol.loadOFF(fileName,transGround,grandGround,nulRot);
    Material groundMat(rand2(),rand2(), Vec3Df (0.f,255.f/255, 255.f/255));
    Object soll (sol, groundMat);
    objects.push_back(soll);
    //loadLights(1);
}

void Scene::simpleScene(){
    buildNormalGround();
        Mesh groundMesh;
        RotationMatrix nulRot(0., Matrix::X);

        /*Ici on récupère ou on défini les paramêtres de chaque objet*/
        //Param Shape
        string fileNameShape = getFileName(Object::ram);//Nom du fichier à charger
        Vec3Df transShape = Vec3Df (0.f, 2.f, 1.f);// de combien on le translate
        float grandShape = 1.f; // de combien on multiplie la forme
        //param Ground
        string fileNameGround = "models/ground.off";
        Vec3Df transGround;//De combien on veut le translater
        float grandGround = 7.f; // de combien on multiplie le fond


        groundMesh.loadOFF(fileNameShape,transGround, grandGround,nulRot);
        Material groundMat;
        Object ground (groundMesh, groundMat);
        objects.push_back (ground);
        Mesh ramMesh;

        ramMesh.loadOFF (fileNameShape, transShape,grandShape,nulRot);
        //Material ramMat (1.f, 1.f, Vec3Df (1.f, .6f, .2f));//old rammat
        Material ramMat(0.735f,1.656f, Vec3Df (1.f, .795f, .504f));
        Object ram (ramMesh, ramMat);
        objects.push_back (ram);

        Mesh theiere;
        string fileTheiere = getFileName(Object::ram);
        Vec3Df transTheiere = Vec3Df (0.f, 0.f, 1.f);// de combien on le translate
        float grandTheiere = 1.f; // de combien on multiplie la forme
        theiere.loadOFF(fileTheiere, transTheiere, grandTheiere, nulRot);
        Material theiMat(0.235f,0.656f, Vec3Df (0.5f, 0.f, .8f));
        Object theier(theiere,theiMat);
        objects.push_back(theier);

    loadLights(1);
 }
