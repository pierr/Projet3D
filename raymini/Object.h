// *********************************************************
// Object Class
// Author : Tamy Boubekeur (boubek@gmail.com).
// Copyright (C) 2010 Tamy Boubekeur.
// All rights reserved.
// *********************************************************

#ifndef OBJECT_H
#define OBJECT_H

#include <iostream>
#include <vector>

#include "Mesh.h"
#include "Material.h"
#include "BoundingBox.h"

class Object {
public:
    inline Object () {}
    inline Object (const Mesh & mesh, const Material & mat) :mesh (mesh), mat (mat) {
        updateBoundingBox ();
    }
    virtual ~Object () {}

    inline const Mesh & getMesh () const { return mesh; }
    inline Mesh & getMesh () { return mesh; }
    
    inline const Material & getMaterial () const { return mat; }
    inline Material & getMaterial () { return mat; }

    inline const BoundingBox & getBoundingBox () const { return bbox; }
    void updateBoundingBox ();
    enum objName {
        threeD,
        camel_head,
        max,
        sphere,
        apple,
        dbtorus,
        max_50K,
        squirrel,
        cherry,
        double_ram,
        monkey,
        tri,
        dauphin,
        fandisk,
        paysage,
        triceratops,
        theiere,
        gargoyle,
        ram,
        tweety,
        armadillo,
        ground,
        ram_HD,
        bunny,
        ground_HD,
        room,
        bunny2,
        horse,
        room_f,
        coloredGlass,
        opened_cube,
        cubeoff,
        cubeFloor,
        cubeWallRight,
        cubeWallLeft,
        cubebackWall,
        cubeFaceWall,
        cubeRoof,
    };
private:
    Mesh mesh;
    Material mat;
    BoundingBox bbox;
};


#endif // OBJECT_H

// Some Emacs-Hints -- please don't remove:
//
//  Local Variables:
//  mode:C++
//  tab-width:4
//  End:
