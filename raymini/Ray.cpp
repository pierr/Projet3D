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

bool Ray::intersect(Vec3Df & v0 , Vec3Df & v1, Vec3Df & v2, Vec3Df n, Vec3Df & intersectionPoint) const{
  const float epsilon = 0.00000001; //Un epsilon pour éviter de faire des comparaisons a zero
    //Des vecteurs pour faire des calculs sur le triangle (arrêtes, normales)
  Vec3Df u = v1 - v0;
  Vec3Df v = v2 - v0;
  //Vecteur intermédiaire pour calculer la projection sur le plan
  Vec3Df w0 = getOrigin() - v0;
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
   Vec3Df w = intersectionPoint - v0;
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
        color += m.getColor()*(m.getDiffuse()*Vec3Df::dotProduct(wn,wi)+m.getSpecular()*pow(Vec3Df::dotProduct(r,wo),brillance));
    }
}
void Ray::calcBRDF(Vec3Df & p, Vec3Df & n, Material & m, Vec3Df& color){
    Scene* scene = Scene::getInstance();
    std::vector<Light> lights = scene->getLights();
    //Pour cacune des lumières on va chercher pour le triangle sa brdf
   Vec3Df wi,wo,wn,r;
   Light light;
   float brillance = 1;
   for(unsigned int i = 0; i<lights.size(); i++){
       light = lights.at(i);
      // brillance = light.getIntensity(); //on récupère la brillance depuis la lumière.
        wi = Vec3Df(light.getPos() - p);
        //wi = Vec3Df(lights[i]. - mesh.V[mesh.T[i].v[j]].p);
        wi.normalize();
        wo = Vec3Df(getOrigin() - p);
        wo.normalize();
        r = wn*Vec3Df::dotProduct(wi,n)*2-wi;
        color += m.getColor()*(m.getDiffuse()*Vec3Df::dotProduct(wn,wi)+m.getSpecular()*pow(Vec3Df::dotProduct(r,wo),brillance));
    }
}

//reimplementation avec kdtree
Vec3Df Ray::intersectkdScene(Vec3Df camPos, BoundingBox & scenebox, std::vector<kdnode> & kdboxes){

    float mindist = FLT_MAX;
    bool isbool = false;
    Vec3Df isp, isn;
    Material ism;
    Vertex isv;

    Vec3Df tmp; //inutile

    //si ça intersecte avec la scene, on regarde les triangles
    if(intersect(scenebox,tmp)){
        for(unsigned int ib = 0; ib<kdboxes.size(); ib++){
            //s'il y a intersection avec la boite, on regarde les triangles
            kdnode kdbox = kdboxes[ib];
            if(intersect(kdbox.get_box(),tmp)){
                std::vector<kdleaf> leafs = kdbox.get_leafs();
                //triangle par triangle..
                for(unsigned int i = 0; i<leafs.size(); i++){
                    kdleaf leaf = leafs[i];
                    //Appeler la fonction qui vérifie l'intersection avec un triangle
                    Vec3Df intersectPt;
                    bool hasIntersection = intersect(leaf.get_v0(),leaf.get_v1(),leaf.get_v2(),leaf.get_normal(), intersectPt);
                    //Si il y a une intersection avec le triangle alors on appelle
                    if(hasIntersection){
                        float dist = Vec3Df::distance(camPos,intersectPt);
                        if(dist < mindist){
                            mindist = dist;
                            isbool = true;
                            isp = intersectPt;
                            isn = leaf.get_normal();
                            ism = leaf.get_Material();
                            isv = Vertex(intersectPt, isn);
                        }
                    }
                }
            }
        }
    }
    if(isbool){
        Vec3Df radiance;
        this->calcBRDF(isv, ism, radiance);
//      this->calcBRDF(isp,isn,ism,radiance);
        return radiance;
    } else {
        return Vec3Df();
    }
}
