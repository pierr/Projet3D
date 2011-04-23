// *********************************************************
// Scene Class
// Author : Tamy Boubekeur (boubek@gmail.com).
// Copyright (C) 2010 Tamy Boubekeur.
// All rights reserved.
// *********************************************************

#ifndef SCENE_H
#define SCENE_H

#include <iostream>
#include <vector>

#include "Object.h"
#include "Light.h"
#include "BoundingBox.h"
#include "Triangle.h"
#include "Vertex.h"
#include "KDTreeXYZ.h"

class Scene {
public:
    static Scene * getInstance ();
    static void destroyInstance ();
    
    inline std::vector<Object> & getObjects () { return objects; }
    inline const std::vector<Object> & getObjects () const { return objects; }
    
    inline std::vector<Light> & getLights () { return lights; }
    inline const std::vector<Light> & getLights () const { return lights; }

    inline std::vector<Triangle> & getTriangles () { return triangles; }
    inline const std::vector<Triangle> & getTriangles () const { return triangles; }

    inline std::vector<Vertex> & getVerteces () { return verteces; }
    inline const std::vector<Vertex> & getVerteces () const { return verteces; }

    
    inline const BoundingBox & getBoundingBox () const { return bbox; }
     inline KDTreeXYZ * getKDTree () { return kdTree; }
    void updateBoundingBox ();
protected:
    Scene ();
    virtual ~Scene ();
    
private:
    void buildDefaultScene (bool HD);
    void buildTriangles();
    std::vector<Object> objects;
    std::vector<Light> lights;
    BoundingBox bbox;
    KDTreeXYZ * kdTree;
    /**
     @var triangles représente tous les triangles de la scène, tout objets confondus
    */
    std::vector<Triangle> triangles;
    /**
     @var verteces représente tous les vertex de la scène (même si certains sont duppliqués, le but étant d'avoir une structure rapide à lire)
    */
    std::vector<Vertex> verteces;
};


#endif // SCENE_H

// Some Emacs-Hints -- please don't remove:
//
//  Local Variables:
//  mode:C++
//  tab-width:4
//  End:
