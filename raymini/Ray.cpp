// *********************************************************
// Ray Class
// Author : Tamy Boubekeur (boubek@gmail.com).
// Copyright (C) 2010 Tamy Boubekeur.
// All rights reserved.
// *********************************************************

#include "Ray.h"

#include <float.h>
#include <cstdlib>
#include <cmath>
using namespace std;

Vec3Df perturbateVector(const Vec3Df & originVecor, float theta);

static const unsigned int NUMDIM = 3, RIGHT = 0, LEFT = 1, MIDDLE = 2;
Ray::Ray (const Vec3Df & origin, const Vec3Df & direction, const Vec3Df & bgColor, Parametres * param) {
    this->origin = origin;
    this->direction = direction;
    this->direction.normalize();
    this->bgColor = bgColor;
    this->param = param;
}

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

bool Ray::intersect(Vertex & v0 , Vertex & v1, Vertex & v2, Vec3Df & intersectionPoint) const{
  const float epsilon = 0.00000001; //Un epsilon pour éviter de faire des comparaisons a zero
    //Des vecteurs pour faire des calculs sur le triangle (arrêtes, normales)
  Vec3Df u = v1.getPos() - v0.getPos();
  Vec3Df v = v2.getPos() - v0.getPos();
  Vec3Df n = Vec3Df::crossProduct(u,v);
  //Vecteur intermédiaire pour calculer la projection sur le plan
  Vec3Df w0 = getOrigin() - v0.getPos();
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
   float uu = u.getSquaredLength();
   float uv = Vec3Df::dotProduct(u,v);
   float vv = v.getSquaredLength();
   Vec3Df w = intersectionPoint - v0.getPos();
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

void Ray::calcBRDF(Vertex & v,  Material & m, Vec3Df& color, kdnode * root){
    Scene* scene = Scene::getInstance();
    std::vector<Light> lights = scene->getLights();
    //Pour chacune des lumières on va chercher pour le triangle sa brdf
    Vec3Df wi,wo,wn,wp, r;
    for(unsigned int i = 0; i<lights.size(); i++){

        Vec3Df material(1,1,1); //material
        Vec3Df BRDFradiance(1,1,1);
        float lightprop = 1; //shadows
        float ambocc = 1;

        Light light = lights.at(i);

        if(param->get_materialactive()) material = m.getColor();
        if(param->get_BRDFactive()){
            float BRDF = 1;  //BRDF

            wi = Vec3Df(light.getPos() - v.getPos());
            wi.normalize();
            wo = Vec3Df(getOrigin() - v.getPos());
            wo.normalize();
            wn = v.getNormal();
            wp = v.getPos();
            r = wn*Vec3Df::dotProduct(wi,wn)*2-wi;

            BRDF = 0;
            if(param->get_diffactive())
                BRDF += m.getDiffuse()*abs(Vec3Df::dotProduct(wn,wi));
            if(param->get_specactive())
                BRDF += m.getSpecular()*pow(abs(Vec3Df::dotProduct(r,wo)),param->get_brillance());

            BRDFradiance = light.getColor()*BRDF;
        }
        if(param->get_ombresactive()){
            Vertex isv; //inutile
            Material ism; //inutile
            float dist;
            //verifier en quelle proportion le point est cache de chaque lumiere
            std::vector<Vec3Df> lightpoints = light.getPoints(param->get_ombresnumr(),param->get_ombresnuma());
            lightprop = lightpoints.size();
            Ray rlight;
            for(int j=0; j<(int)lightpoints.size(); j++){
                Vec3Df dir = v.getPos()-lightpoints.at(j);
                rlight = Ray(lightpoints.at(j),dir,bgColor, param); //prevention: jamais faire des calcBRDF avec ce ray!
                //s'il y a intersection et le triangle est entre le point et la lumiere, il cache
                //ombres douces
                if(param->get_ombresdouces())
                    if(rlight.kd_intersect(root, isv, ism, dist) && dist<(1-param->get_epsilon())*Vec3Df::distance(lightpoints.at(j),v.getPos()))
                        lightprop--;
                    //ombres fortes
                else
                        if(rlight.kd_intersect(root, isv, ism, dist) && dist<(1-param->get_epsilon())*Vec3Df::distance(light.getPos(),v.getPos()))
                            lightprop--;
            }
            lightprop = lightprop/lightpoints.size();
        }
        if(param->get_amboccactive()){
            ambocc = calcAmbOcclusion(root,v,Scene::getInstance()->getBoundingBox().getLength()*param->get_amboccrayon(), param->get_ambocctheta());
        }

        //pour chaque lumiere on somme
        color += material*BRDFradiance*lightprop*ambocc;
    }
}

//chercher des intersections dans les boites minimales
bool Ray::kd_intersect(kdnode * root, Vertex & rootisv, Material & rootism, float & rootmindist){
    //si on est dans les nodes intermediaires on passe le message..
    if(!root->get_deepest()){

        kdnode *supnode = root->get_supnode();
        bool supbool = false;
        Vertex supisv;
        Material supism;
        float supmindist;

        kdnode *infnode = root->get_infnode();
        bool infbool = false;
        Vertex infisv;
        Material infism;
        float infmindist;

        //on regarde l'intersection avec la boite superieure
        Vec3Df is_point; //inutile
        if(intersect(supnode->get_box(),is_point)){
            supbool = kd_intersect(supnode,supisv,supism,supmindist);
        }
        //on regarde l'intersection avec la boite inferieure
        if(intersect(infnode->get_box(),is_point)){
            infbool = kd_intersect(infnode,infisv,infism,infmindist);
        }
        //aucune intersection
        if(!supbool && !infbool){
            return false;
        //interesection d'un seul cote, on garde ces valeurs
        } else if(!supbool){
            rootisv = infisv;
            rootism = infism;
            rootmindist = infmindist;
        } else if(!infbool){
            rootisv = supisv;
            rootism = supism;
            rootmindist = supmindist;
        //intersection des deux cotes
        } else {
            //si l'intersection de supnode est plus proche on garde celle-ci
            if(supmindist < infmindist){
                rootisv = supisv;
                rootism = supism;
                rootmindist = supmindist;
            } else {
                rootisv = infisv;
                rootism = infism;
                rootmindist = infmindist;
            }
        }
        return true;
    //si on est dans le dernier node il faut passer par les leafs
    } else {
        rootmindist = FLT_MAX;
        bool rootbool = false;
        Vec3Df tmp; //inutile
        if(intersect(root->get_box(),tmp)){
            std::vector<kdleaf> leafs = root->get_leafs();
            //triangle par triangle..
            for(unsigned int i = 0; i<leafs.size(); i++){
                kdleaf leaf = leafs[i];
                //Appeler la fonction qui vérifie l'intersection avec un triangle
                Vec3Df intersectPt;
                bool hasIntersection = intersect(leaf.get_vertex0(),leaf.get_vertex1(),leaf.get_vertex2(),intersectPt);
                //Si il y a une intersection avec le triangle alors on appelle
                if(hasIntersection){
                    float dist = Vec3Df::distance(origin,intersectPt);
                    if(dist < rootmindist){
                        rootmindist = dist;
                        rootbool = true;
                        rootism = leaf.get_Material();
                        Vec3Df isn = leaf.get_normal();
                        rootisv = Vertex(intersectPt, isn);
                    }
                }
            }
        }
        return rootbool;
    }
}

Vec3Df Ray::calcul_radiance(kdnode * root, int num){
    Material ism;
    Vertex isv;
    float dist; //inutile

    //s'il y a intersection, on retourne la radiance
    if(kd_intersect(root, isv, ism, dist)){
        Vec3Df radiance;

        //RAY TRACING
        calcBRDF(isv, ism, radiance, root);

        //PATH TRACING
        if(param->get_pathactive() && num<param->get_pathmaxdeep()){
            Vec3Df rad_rayons;
            for(int i=0; i<param->get_pathnray(); i++){
                //aleatoires, direction proche a la normale
                Vec3Df pertVect = perturbateVector(isv.getNormal(), param->get_paththeta());
                Ray rlight(isv.getPos()+pertVect*param->get_epsilon(), pertVect, this->bgColor, param);
                rad_rayons += rlight.calcul_radiance(root, num+1);
            }
            rad_rayons = rad_rayons/param->get_pathnray();

            radiance += rad_rayons;
        }
        return radiance;
    //sinon le fonds d'ecran
    } else {
        return bgColor/255.f;
    }
}

//Nombre aléatoire entre -1 et 1
float randf(){
    return ( rand()/(double)RAND_MAX ) * 2. - 1.;
}


float rand1(){
    return  rand()/(float)RAND_MAX  ;
}
float Ray::calcAmbOcclusion(kdnode * root, Vertex & v, float rayonSphere, float theta){
    float ratioIntersection = 0.f;
    for(int i =0; i < param->get_amboccnray(); i++){
        Material ism;
        Vertex isv;
         Ray rlight(v.getPos() + v.getNormal()*param->get_epsilon()*rayonSphere, perturbateVector(v.getNormal(), theta), bgColor, param);

         float mindist; //inutile
         bool isIntersect = rlight.kd_intersect(root, isv, ism, mindist);
         //On teste si l'intersection est dans une sphère de rayon rayonsphère si il y a eu une intersection
         if(isIntersect && Vec3Df::distance(isv.getPos(), v.getPos()) < rayonSphere){
            ratioIntersection =  ratioIntersection +1.f;
         }
    }
    return ( -ratioIntersection +(float) param->get_amboccnray())/param->get_amboccnray();
}

Vec3Df perturbateVector(const Vec3Df & originVecor, float theta){
  float pi = 3.14;
  float thetaRad = pi*theta/180;
  //originVecor.normalize();
  Vec3Df basis1 (-originVecor[1],originVecor[0],0);
  basis1.normalize();
  Vec3Df basis2 = Vec3Df::crossProduct(originVecor,basis1);
  basis2.normalize();
  //On a maintenant une base.
  float s = rand1();//( 0, 1 );
  float r = rand1();//( 0, 1 );
  float h = cos(thetaRad);

  float phi = 2 * pi * s;
  float z = h + ( 1 - h ) * r;
  float sinT = sqrt( 1 - z * z );
  float x = cos( phi ) * sinT;
  float y = sin( phi ) * sinT;

  Vec3Df perturbated = basis1 * x + basis2 * y + originVecor * z;
  //Debug to see the perturbated Vector
return perturbated;
}
