// *********************************************************
// Scene Class
// Author : Tamy Boubekeur (boubek@gmail.com).
// Copyright (C) 2010 Tamy Boubekeur.
// All rights reserved.
// *********************************************************

#include "Scene.h"

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

// Changer ce code pour créer des scènes originales
void Scene::buildDefaultScene (bool HD) {
    Mesh groundMesh;
    bool debug = false;
    if (debug){
        groundMesh.loadOFF ("models/sphere.off");
        Material groundMat;
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
        ramMesh.loadOFF ("models/ram.off");
    Material ramMat (1.f, 1.f, Vec3Df (1.f, .6f, .2f));
    Object ram (ramMesh, ramMat);    
    objects.push_back (ram);
    }
    Light l (Vec3Df (3.0f, 3.0f, 3.0f), Vec3Df (1.0f, 1.0f, 1.0f), 1.0f);
    lights.push_back (l);
    //Faire une méthode qui construit un triangles avec tous les index
    //Ainsi que tous les vertex dans un vecteur
    //Peut être faut il le mettre dans le kd tree et pour le kdtree avoir une instance

   buildTriangles();
/*   vector<unsigned int> indextri;
   for(unsigned int i =0; i< triangles.size(); i++){
    indextri.push_back(i);
   }
   //this->kdTree = new KDTreeXYZ(indextri,bbox,0,0);*/
}

void Scene::buildTriangles(){
  for(unsigned int i =0;i<getObjects().size() ; i++){
    Mesh m = getObjects().at(i).getMesh();
   std::vector<Triangle> triMesh = m.getTriangles();
    std::vector<Vertex> vertexMesh = m.getVertices();
    for( unsigned int j = 0;j <m.getTriangles().size(); j++){
        //On récupère la taille du vecteur car ce sera plus facile pour créer un nouveau triangle
        unsigned int size = verteces.size();

        //On ajoute tous les vertex du triangle à la grande liste de vertex
        //on ne se préoccupe pas de savoir si le vertex ets déjà présent dedans
        //Le but étant d'avoir une structure de lecture.
        verteces.push_back(vertexMesh.at(triMesh.at(j).getVertex(0)));
        verteces.push_back(vertexMesh.at(triMesh.at(j).getVertex(1)));
        verteces.push_back(vertexMesh.at(triMesh.at(j).getVertex(2)));

        //On ajoute le triangle correspondant à la liste
        this->triangles.push_back(Triangle(size, size+1, size+2));

    }
  }
}
