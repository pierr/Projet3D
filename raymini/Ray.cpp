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
#include <algorithm>

# define PI 3.141592

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
/**
 *@inheaderfile
 */
bool Ray::intersect (const Vertex & v0, const Vertex & v1, const Vertex & v2, Vec3Df & intersectionPoint, float & ir, float & iu, float & iv) const {
        Vec3Df v = v1.getPos() - v0.getPos();
        Vec3Df u = v2.getPos() - v0.getPos();
        Vec3Df nn = Vec3Df::crossProduct(u, v);
        Vec3Df otr = origin - v0.getPos();
        Vec3Df otrv = Vec3Df::crossProduct (otr, v);
        Vec3Df uotr = Vec3Df::crossProduct (u, otr);

        float c = Vec3Df::dotProduct (nn, direction);
        iu = Vec3Df::dotProduct (otrv, direction)/c;
        iv = Vec3Df::dotProduct (uotr, direction)/c;
        ir = -Vec3Df::dotProduct (nn, otr)/c;

        //Test pour voir si le point est dans le triangle
        bool hasIntersection = (0 <= iu && iu <= 1 && 0 <= iv && iv <= 1 && ir >= 0 && iu + iv <= 1);
        if (hasIntersection) {
                nn.normalize();
                intersectionPoint = origin + ir*direction;
        }

        //retrun true si il y a vraiment une intersection
        return hasIntersection;
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

float Ray::retBRDF(Vec3Df & wn, Vec3Df & wi, Vec3Df & wo, float intensity, Material & m){
    float BRDF = 0;
    Vec3Df h = (wi+wo);
    h.normalize();
    //Calcul de la partie diffuse de la brdf (Diffuse Shading)//Ajouter le terme ambiant
    if(param->get_diffactive()){
        BRDF += m.getDiffuse()*intensity*max(0.f,Vec3Df::dotProduct(wn,wi));//abs(Vec3Df::dotProduct(wn,wi)); si on pernait le abs ça revenait à avoir une source symétrique
    }
    if(param->get_specactive()){
        BRDF += m.getSpecular()*pow(abs(Vec3Df::dotProduct(h,wn)),param->get_brillance());
    }
    return BRDF;
}

void Ray::calcBRDF(Vertex & v,  Material & m, Vec3Df& color, kdnode * root){
    Scene* scene = Scene::getInstance();
    std::vector<Light> lights = scene->getLights();
    for(unsigned int i = 0; i<lights.size(); i++){

        Vec3Df material(1,1,1); //material
        Vec3Df BRDFradiance(1,1,1);
        float lightprop = 1; //shadows
        float ambocc = 1;

        Light light = lights.at(i);

        if(param->get_materialactive()) material = m.getColor();
        if(param->get_BRDFactive()){
            Vec3Df wi,wo,wn,wp;

            wi = Vec3Df(light.getPos() - v.getPos()); //Point in the lignt direction from the current pas
            wi.normalize();
            wo = Vec3Df(getOrigin() - v.getPos());
            wo.normalize();
            wn = v.getNormal();

            float BRDF = retBRDF(wn,wi,wo,light.getIntensity(),m);

            BRDFradiance = light.getColor()*BRDF;
        }
        if(param->get_ombresactive()){
            Vertex isv; //inutile
            Material ism; //inutile
            float dist;
            //verifier en quelle proportion le point est cache de chaque lumiere
            Vec3Df normal = v.getPos()-light.getPos();
            normal.normalize();
            std::vector<Vec3Df> lightpoints;
            if(param->get_ombresdouces())
                lightpoints = light.getPoints(normal,param->get_ombresnumr(),param->get_ombresnuma());
            else
                lightpoints.push_back(light.getPos());

            lightprop = lightpoints.size();
            Ray rlight;
            for(int j=0; j<(int)lightpoints.size(); j++){
                Vec3Df dir = v.getPos()-lightpoints.at(j);
                rlight = Ray(lightpoints.at(j),dir,bgColor, param); //prevention: jamais faire des calcBRDF avec ce ray!
                //s'il y a intersection et le triangle est entre le point et la lumiere, il cache
                if(rlight.kd_intersect(root, isv, ism, dist, FLT_MAX) && dist<(1-param->get_epsilon())*Vec3Df::distance(lightpoints.at(j),v.getPos()))
                    lightprop--;
            }

//            if(lightprop<lightpoints.size()){
//                cout << "lp " << lightprop << " so " << lightprop/(float)lightpoints.size() << endl;
//            }

            lightprop = lightprop/(float)lightpoints.size();
        }

        if(param->get_amboccactive()){
            ambocc = calcAmbOcclusion(root,v,Scene::getInstance()->getBoundingBox().getLength()*param->get_amboccrayon(), param->get_ambocctheta());
        }

        //pour chaque lumiere on somme
        color += material*BRDFradiance*lightprop*ambocc;
    }
}

//chercher des intersections dans les boites minimales
bool Ray::kd_intersect(kdnode * root, Vertex & rootisv, Material & rootism, float & rootmindist, float maxdist){

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
            supbool = kd_intersect(supnode,supisv,supism,supmindist,maxdist);
            //si la boite est plus loin que distmax on regarde pas
            if(supbool && Vec3Df::distance(origin,is_point)>maxdist)
                supbool = false;
        }
        //on regarde l'intersection avec la boite inferieure
        if(intersect(infnode->get_box(),is_point)){
            infbool = kd_intersect(infnode,infisv,infism,infmindist,maxdist);
            //si la boite est plus loin que distmax on regarde pas
            if(infbool && Vec3Df::distance(origin,is_point)>maxdist)
                infbool = false;
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
                float iR,iU,iV;
                //Si il y a une intersection avec le triangle alors on appelle
                if(intersect(leaf.get_vertex0(),leaf.get_vertex1(),leaf.get_vertex2(),intersectPt,iR,iU,iV)){
                    float dist = Vec3Df::distance(origin,intersectPt);
                    if(dist < rootmindist){
                        rootmindist = dist;
                        rootbool = true;
                        rootism = leaf.get_Material();
                        //On fait l'interpolation des normales à partir des coordonnées barycentriques.
                        Vec3Df isn = leaf.get_vertex0().getNormal()*(1-iU-iV) + leaf.get_vertex1().getNormal()*iV + leaf.get_vertex2().getNormal()*iU; //leaf.get_normal();
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
    if(kd_intersect(root, isv, ism, dist,FLT_MAX)){
        Vec3Df radiance;

        //RAY TRACING
        calcBRDF(isv, ism, radiance, root);

        //PATH TRACING
        calcPathTracing(root , num, isv,radiance, ism);

        return radiance;
    //sinon le fonds d'ecran
    } else {
        return bgColor/255.f;
    }
}

void Ray::calcPathTracing(kdnode * root,int num,Vertex & isV, Vec3Df & radiance, Material & m){
    if(param->get_pathactive() && num<param->get_pathmaxdeep()){
        Vec3Df rad_rayons;
        for(int i=0; i<param->get_pathnumr(); i++){
            for(int j=0; j<param->get_pathnuma(); j++){
                //aleatoires, direction proche a la normale
                Vec3Df pertVect = rotateVector(isV.getNormal(), i*param->get_paththeta()/param->get_pathnumr(), j*param->get_paththeta()/param->get_pathnuma());
                Ray rlight(isV.getPos()+pertVect*param->get_epsilon(), pertVect, this->bgColor, param);

                Vec3Df wn = isV.getNormal();
                Vec3Df wi = pertVect;
                Vec3Df wo = -direction;

                Vec3Df radl = rlight.calcul_radiance(root, num+1);
                rad_rayons += radl*retBRDF(wn,wi,wo,radl.getLength(),m);
            }
        }
        //ce sont comme des lumieres. on ne doit pas faire la moyenne. on normalisera sur RayTracer avec l'option saturation
        radiance += rad_rayons;
    }
}


float Ray::calcAmbOcclusion(kdnode * root, Vertex & v, float rayonSphere, float theta){
    float ratioIntersection = 0.f;
    for(int i=0; i<param->get_amboccnumr(); i++){
        for(int j=0; j<param->get_amboccnuma(); j++){
            Material ism;
            Vertex isv;
            Ray rlight(v.getPos() + v.getNormal()*param->get_epsilon()/**rayonSphere*/, rotateVector(v.getNormal(), i*theta/param->get_amboccnumr(), j*theta/param->get_amboccnuma()), bgColor, param);
            float mindist; //inutile
            bool isIntersect = rlight.kd_intersect(root, isv, ism, mindist,rayonSphere);
            //On teste si l'intersection est dans une sphère de rayon rayonsphère si il y a eu une intersection
            if(isIntersect && mindist < rayonSphere){
               ratioIntersection += (rayonSphere-mindist)/rayonSphere ;
            }
        }
    }
    int nray = param->get_amboccnumr()*param->get_amboccnuma();
    return ((float) nray - ratioIntersection)/nray;
}


Vec3Df Ray::rotateVector(const Vec3Df & originVecor, float anglephi, float angletheta){
    //On definit une base par rapport au vecteur original
    Vec3Df z = originVecor;
    z.normalize();
    Vec3Df x, y;
    z.getTwoOrthogonals(x,y);
    x.normalize();
    y.normalize();

    float theta = PI*anglephi/180;   //valeur en radians entre [-angle;angle]
    float phi = PI*angletheta/180;     //valeur en radians entre [-angle;angle]

    float coordx = sin( theta ) * cos( phi );
    float coordy = sin( theta ) * sin( phi );
    float coordz = cos( theta );

    Vec3Df rotated = x * coordx + y * coordy + z * coordz;
    rotated.normalize();

    return rotated;
}

Vec3Df Ray::perturbateVector(const Vec3Df & originVecor, float angle){
  return rotateVector(originVecor,angle*param->randf(),angle*param->randf());
}
