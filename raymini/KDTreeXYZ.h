#include <vector>
#include "BoundingBox.h"
#include "Triangle.h"
#include "Scene.h"
#include "Ray.h"
#ifndef KDTREEXYZ_H
#define KDTREEXYZ_H
class KDTreeXYZ{
public:
    inline KDTreeXYZ(std::vector<unsigned int> & _indexTriangles, BoundingBox & _box , unsigned int _dim, unsigned int _prof) {
        indexTriangles = _indexTriangles;
        box = _box;
        if(_dim == 4){dim = 0;}
        else {
            dim = _dim;
        }
        prof = _prof;
        fg = NULL;
        fd = NULL;
        constKdTree();
    }
    inline BoundingBox & getBox(){return box;}
    inline std::vector<unsigned int> & getIndexTriangles() { return indexTriangles;}
    inline const std::vector<unsigned int> & getObjects () const { return indexTriangles; }
    static const unsigned int nTMin = 7;
    static const unsigned int profMax = 20;
    void intersect(Ray & ray);
private:
    unsigned int dim;//Dans quelle dimension il faudra qu'on splite la boite
    /**
        @param est la Bounding box du noeud courant
    */
    BoundingBox box;
    /**
        @param indexTriangles est un vecteur qui contient les index des triangles  qui sont contenus dans la classe Scène (à voir si on
        les bougent ici ou non
    */
    std::vector<unsigned int> indexTriangles;
    /**
        @param fg représente un pointeur vers le kdtree fils gauche
    */
    KDTreeXYZ * fg;// Le pointeur vers le fils gauche
    /**
    * @param fd représente un pointeur vers le kdTree fils droit
    */
    KDTreeXYZ * fd;// le ponteur vers le fils droit
    /**
        @param prof représente la profondeur de l'arbre.
     */
    unsigned int prof;
    /**
    Cette méthode sert à construire le KdTree en utilisant les structures de Vertex et de triangles stockées dans Scène
    */
    void constKdTree();

    /** Calcule les intersections entre le rayon et le kdTree (donc les triangles de la scène).
    * @param ray le rayon don on veut calculer les intersections avec la scène
    * @param intersecPts les points d'intersection de rayons et de triangles
    * @param triIndex les triangles qui intersectent la scène
    */

};

#endif
