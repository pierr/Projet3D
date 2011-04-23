// *********************************************************
// Ray Class
// Author : Tamy Boubekeur (boubek@gmail.com).
// Copyright (C) 2010 Tamy Boubekeur.
// All rights reserved.
// *********************************************************

#include "Ray.h"

#include <float.h>

using namespace std;

static const unsigned int NUMDIM = 3, RIGHT = 0, LEFT = 1, MIDDLE = 2;

bool Ray::intersect (const BoundingBox & bbox, Vec3Df & intersectionPoint) const {
    const Vec3Df & minBb = bbox.getMin ();
    const Vec3Df & maxBb = bbox.getMax ();
    bool inside = true;
    unsigned int  quadrant[NUMDIM];
    register unsigned int i;
    unsigned int whichPlane;
    Vec3Df maxT;
    Vec3Df candidatePlane;
    
    for (i=0; i<NUMDIM; i++)
        if (origin[i] < minBb[i]) {
            quadrant[i] = LEFT;
            candidatePlane[i] = minBb[i];
            inside = false;
        } else if (origin[i] > maxBb[i]) {
            quadrant[i] = RIGHT;
            candidatePlane[i] = maxBb[i];
            inside = false;
        } else	{
            quadrant[i] = MIDDLE;
        }

    if (inside)	{
        intersectionPoint = origin;
        return (true);
    }

    for (i = 0; i < NUMDIM; i++)
        if (quadrant[i] != MIDDLE && direction[i] !=0.)
            maxT[i] = (candidatePlane[i]-origin[i]) / direction[i];
        else
            maxT[i] = -1.;

    whichPlane = 0;
    for (i = 1; i < NUMDIM; i++)
        if (maxT[whichPlane] < maxT[i])
            whichPlane = i;

    if (maxT[whichPlane] < 0.) return (false);
    for (i = 0; i < NUMDIM; i++)
        if (whichPlane != i) {
            intersectionPoint[i] = origin[i] + maxT[whichPlane] *direction[i];
            if (intersectionPoint[i] < minBb[i] || intersectionPoint[i] > maxBb[i])
                return (false);
        } else {
            intersectionPoint[i] = candidatePlane[i];
        }
    return (true);			
}

bool Ray::intersect(const Triangle &tri , vector<Vertex> & verteces, Vec3Df & intersectionPoint) const{
  const float epsilon = 0.00000001; //Un epsilon pour éviter de faire des comparaisons a zero
    //Des vecteurs pour faire des calculs sur le triangle (arrêtes, normales)
  Vec3Df u = verteces.at(tri.getVertex(1)).getPos() - verteces.at(tri.getVertex(0)).getPos();
  Vec3Df v = verteces.at(tri.getVertex(2)).getPos() - verteces.at(tri.getVertex(0)).getPos();
  Vec3Df n = Vec3Df::crossProduct(u,v);
  //Si n est le vecteur null alors ce triangle n'en est pas un.
  if( n == Vec3Df()){
    return false;
  }
  //Vecteur intermédiaire pour calculer la projection sur le plan
  Vec3Df w0 = getOrigin() - verteces.at(tri.getVertex(0)).getPos();
  float a = - Vec3Df::dotProduct(n,w0);
  float b = Vec3Df::dotProduct(n,getDirection());

  if(fabs(b) < epsilon){
    if(a ==  0){
        return true; //Mais le triangle est dans le plan du triaangle
    } return false;
  }
float r = a/b;

  if( r < 0){ //Le rayon ne va pas dans la direction du plan
    return false;
  }

  intersectionPoint = getOrigin() + r*getDirection();

  //Il faut maintenant déterminer si le point est dans le triangle
  //getDirection()
   float uu = u.getSquaredLength();
   float uv = Vec3Df::dotProduct(u,v);
   float vv = v.getSquaredLength();
   Vec3Df w = intersectionPoint - verteces.at(tri.getVertex(0)).getPos();
   float wu = Vec3Df::dotProduct(w,u);
   float wv = Vec3Df::dotProduct(w,v);
   float D = uv * uv - uu * vv;

   float s = (uv * wv - vv * wu) / D;
   if(s < 0.0 || s > 1.0){
        return false;
   }

   float t = (uv * wu - uu * wv) / D;
   if(t < 0.0 || (s + t) > 1.0){
        return false;
   } return true;

    //return intersection(verteces.at(tri.getVertex(0)).getPos(), verteces.at(tri.getVertex(1)).getPos(), verteces.at(tri.getVertex(0)).getPos());
}
void Ray::calcBRDF(Vertex & bary,  Material & m, Vec3Df& color){
    Scene* scene = Scene::getInstance();
    std::vector<Light> lights = scene->getLights();
    //Pour cacune des lumières on va chercher pour le triangle sa brdf
   Vec3Df wi,wo,wn,wp, r;
   Light light;
   float brillance = 1;
   for(unsigned int i = 0; i<lights.size(); i++){
       light = lights.at(i);
      // brillance = light.getIntensity(); //on récupère la brillance depuis la lumière.
        wi = Vec3Df(light.getPos() - bary.getPos());
        //wi = Vec3Df(lights[i]. - mesh.V[mesh.T[i].v[j]].p);
        wi.normalize();
        wo = Vec3Df(getOrigin() - bary.getPos());
        wo.normalize();
        wn = bary.getNormal();
        wp = bary.getPos();
        r = wn*Vec3Df::dotProduct(wi,wn)*2-wi;
        color = m.getColor()*(m.getDiffuse()*Vec3Df::dotProduct(wn,wi)+m.getSpecular()*pow(Vec3Df::dotProduct(r,wo),brillance));
    }
}
Vec3Df Ray::intersectScene(Vec3Df camPos){
    Scene* scene = Scene::getInstance();
    std::vector<Object> objects = scene->getObjects();

    float mindist = FLT_MAX;
    Vec3Df pos;
    Object is_obj;
    Vertex is_bary;

    Vec3Df radiance;
    for(unsigned int i = 0; i<objects.size(); i++){
        //On récupère l'objet i
        Object obj = objects.at(i);
        //On récupère l'ensemble des triangles qui composent cet objet
        vector<Triangle> triangles = obj.getMesh().getTriangles();
        //On récupère l'ensemble des verteces
        vector<Vertex> verteces = obj.getMesh().getVertices();
        for(unsigned int j = 0; j< triangles.size(); j++){
             Triangle tri = triangles.at(j);
            //Appeler la fonction qui vérifie l'intersection avec un triangle triangles.at(j)
            Vec3Df intersectPt;
             bool hasIntersection = intersect(tri, verteces, intersectPt);
            //Si il y a une intersection avec le triangle alors on appelle
            if(hasIntersection){
                //On calcule le barycentre de
                pos = Vec3Df(verteces.at(tri.getVertex(0)).getPos() + verteces.at(tri.getVertex(1)).getPos() + verteces.at(tri.getVertex(2)).getPos())/3;
                float dist = Vec3Df::distance(camPos,pos);
                if(dist < mindist){
                    //valeurs du triangle de l'intersection(is) necessaires pour la BRDF
                    mindist = dist;
                    is_obj = obj;
                    Vec3Df is_norm = Vec3Df(verteces.at(tri.getVertex(0)).getNormal() + verteces.at(tri.getVertex(1)).getNormal() + verteces.at(tri.getVertex(2)).getNormal())/3;
                    is_bary = Vertex(intersectPt, is_norm);
                }
            }

        }

    }

    this->calcBRDF(is_bary, is_obj.getMaterial(), radiance);
    return radiance;
}
//reimplementation avec kdtree
Vec3Df Ray::intersectkdScene(std::vector<kdleaf> leafs){
    Scene* scene = Scene::getInstance();
    std::vector<Object> objects = scene->getObjects();

    Vec3Df pos;
    Object is_obj;
    Vertex is_bary;

    Vec3Df radiance;


    for(unsigned int i = 0; i<leafs.size(); i++){
        kdleaf leaf = leafs.at(i);
        //On récupère l'objet i
        Object obj = objects.at(leaf.get_object());
        //On récupère l'ensemble des triangles qui composent cet objet
        vector<Triangle> triangles = obj.getMesh().getTriangles();
        //On récupère l'ensemble des verteces
        vector<Vertex> verteces = obj.getMesh().getVertices();
        Triangle tri = triangles.at(leaf.get_triangle());
        //Appeler la fonction qui vérifie l'intersection avec un triangle
        Vec3Df intersectPt;
        bool hasIntersection = intersect(tri, verteces, intersectPt);
        //Si il y a une intersection avec le triangle alors on appelle
        if(hasIntersection){
            //On calcule le barycentre de
            pos = Vec3Df(verteces.at(tri.getVertex(0)).getPos() + verteces.at(tri.getVertex(1)).getPos() + verteces.at(tri.getVertex(2)).getPos())/3;
            is_obj = obj;
            Vec3Df is_norm = Vec3Df(verteces.at(tri.getVertex(0)).getNormal() + verteces.at(tri.getVertex(1)).getNormal() + verteces.at(tri.getVertex(2)).getNormal())/3;
            is_bary = Vertex(intersectPt, is_norm);
            this->calcBRDF(is_bary, is_obj.getMaterial(), radiance);
            return radiance;
        }
    }

    return radiance;
}

void Ray::calcBRDF(Vec3Df & color){
    Material mat;
    for(unsigned int i = 0; i< triIndex.size(); i++){
        Triangle t = Scene::getInstance()->getTriangles().at(triIndex.at(i));
        Vec3Df n = Vec3Df((Scene::getInstance()->getVerteces().at(t.getVertex(0)).getNormal () +Scene::getInstance()->getVerteces().at(t.getVertex(1)).getNormal () + Scene::getInstance()->getVerteces().at(t.getVertex(2)).getNormal ())/3);
        Vertex ver(intersectPts.at(i), n);
        calcBRDF(ver,mat,color);
    }
}
