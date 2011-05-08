// *********************************************************
// Ray Class
// Author : Tamy Boubekeur (boubek@gmail.com).
// Copyright (C) 2010 Tamy Boubekeur.
// All rights reserved.
// *********************************************************

#ifndef RAY_H
#define RAY_H

#include <iostream>
#include <vector>

#include "Vec3D.h"
#include "BoundingBox.h"
#include "Triangle.h"
#include "Material.h"
#include "Scene.h"
#include "Light.h"
#include "kdnode.h"
#include "Parametres.h"

class Ray {
public:
    inline Ray () {}
    Ray (const Vec3Df & origin, const Vec3Df & direction, const Vec3Df & bgColor, Parametres * param);
    inline virtual ~Ray () {}

    inline const Vec3Df & getOrigin () const { return origin; }
    inline Vec3Df & getOrigin () { return origin; }
    inline const Vec3Df & getDirection () const { return direction; }
    inline Vec3Df & getDirection () { return direction; }
    inline void setParam(Parametres * param) { this->param = param; }

    bool intersect (const BoundingBox & bbox, Vec3Df & intersectionPoint) const;
    bool intersect ( const Triangle & tri, std::vector<Vertex> & verteces, Vec3Df & intersectionPoint) const;
    bool intersect(Vertex & v0 , Vertex & v1, Vertex & v2, Vec3Df & intersectionPoint) const;
    /**
    * Méthode qui permet de vérifier si il ya bien une intersection entre le rayon et le triangle.
    *@param v0 premier Vertex du triangle
    *@param v1 deuxième Vertex du triangle
    *@param v2 troisième Vertex du triangle
    *@param intersectionPoint Vecteur 3D qui représente les coordonnées du point d'intersection
    *@param ir,iu,iv sont les coordonnées barycentriques du point d'intersection, ces coordonnées sont utiles afin de réaliser une interpolation des normales ou des couleurs
    *@return true si il y a une intersection entre le rayon et le triangles défini par le trois vertex v0,v1,v2
    */
    bool intersect (const Vertex & v0, const Vertex & v1, const Vertex & v2, Vec3Df & intersectionPoint, float & ir, float & iu, float & iv) const;
    /**
      Le but de cette fonction est de calculer la brdf pour l'intersection avec la scène et pour une lumière.
    @param wn est un vecteur unitaire qui est la normal à l'intersection
    @param wi est un vecteur unitaire qui part de la position de l'intersection vers la direction de la lumière.
    @param wO est un vecteur unitaire qui part de la position de l'intersection vers la direction de l'origine du rayon.
    @param intensity l'intensité de la lumière concidérée.
    @param m est le matériau de l'objet intersecté
    @return la valeur de la BRDF pour la lumière concidérée
    */
    float retBRDF(Vec3Df & wn, Vec3Df & wi, Vec3Df & wo, float intensity, Material & m);
    /**
    *Méthode qui permet de calculer la BRDF pour le point d'intersection
    * @param bary Le vecteur correspondant au point d'intersection
    * @param m le matériau de l'objet intersecté
    * @param color la couleur qu'on veut modifier avec le calcul de BRDF
    * @param root un pointeur vers le KDTree
    */
    void calcBRDF(Vertex & bary,  Material & m, Vec3Df& color, kdnode * root);
    /**
      Le but de cette méthode est de calculer pour chaque rayon les triangles qui intersectent ce rayon , les triangles sont issus des objets qui composent la scène.
    */
    bool kd_intersect(kdnode * root, Vertex & isv, Material & ism, float & mindist, float maxdist);
   /**
    *Fonction qui permet de claculer le résultat pour le rayon concidéré le résultat combiné ,
    * en fonction des paramêtres activés:de la brdf,des ombres,de l'ambiant occlusion, et du path Tracing.
    * @param root est la racine du kdTree
    * @param num est le niveau de profondeur (nb de rebond) car cette méthode peut être appellée réccursivement.
    */
    Vec3Df calcul_radiance( kdnode * root, int num);
    /**
    * Méthode qui permet de calculer le facteur d'ambient occlusion pour le rayon.
    * @param root est la racine du kdTree
    * @param v est les coonnées de l'intersection du rayon  avec la scène donc le tree.
    * @param rayonSphere représente le rayon dans lequel on veut bien accepter les triangles de la scène.
    * @param angle représente le demi l'angle du cône à partir duquel on va tirer les rayons.
    */
    float calcAmbOcclusion(kdnode * root, Vertex & v, float rayonSphere, float angle);
    /**
     *Méthode qui permet de calculer le résultat du PathTracing.(C'est une méthode réccursive).
     * @param root est la racine du kdTree
     * @param num est le nombre de rebond
     * @param isV est les coordonnes de l'intersection entre le rayon et la scène.
     * @param radiance est la couleur de la scène + lumière....
     * @param m est le matéerial de l'objet intersecté par le rayon.
    */
    void calcPathTracing(kdnode * root,int num,Vertex & isV,Vec3Df & radiance, Material & m);
    /**
    *Méthode qui permet de générer un vecteur qui aura tourné d'un angle theta et phi dans le repère propre du vecteur d'origine.
    * @param  originVecor vecteur d'origine
    * @param anglePhi coordonnée sphérique
    * @param angletheta coordonnée sphérique
    */
    Vec3Df rotateVector(const Vec3Df & originVecor, float anglephi, float angletheta);
    /**
    *Méthode qui permet d'appelet rotateVector avec des paramètres aléatoires (les angles teta et phi sont issus
    * de la multiplication par des nombres aléatoires entre 0 et 1 de angle.
    * @param originVector vecteur d'origine
    * @param angle max
    */
    Vec3Df perturbateVector(const Vec3Df & originVecor, float angle);

private:
    Vec3Df origin;
    Vec3Df direction;
    Vec3Df bgColor;
    Parametres * param;
};


#endif // RAY_H

// Some Emacs-Hints -- please don't remove:
//
//  Local Variables:
//  mode:C++
//  tab-width:4
//  End:
