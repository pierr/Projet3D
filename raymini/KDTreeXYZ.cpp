#include "KDTreeXYZ.h"
void KDTreeXYZ::constKdTree(){
    //Condition d'arrêt , il faut qu'il ya ait plus d'un certain nombre de triangle dans la box ou que l'on ait dépassé la profondeur de l'arbre max
    if(indexTriangles.size() <= KDTreeXYZ::nTMin || prof > KDTreeXYZ::profMax ){
        std::vector<BoundingBox> bbxs;
        //On divise la boîte en deux boites suivant la dimention dim
        this->box.subdivide(bbxs , dim);

        // On va créée les deux listes d'index de triangles
        std::vector<unsigned int> triG;
        std::vector<unsigned int> triD;

        //On classe les triangles de la liste en fg ou fd
        for(unsigned int i = 0; i < this->indexTriangles.size(); i++){
            unsigned int indexCurTriangle = indexTriangles.at(i);
            Triangle t = Scene::getInstance()->getTriangles().at(indexCurTriangle);
            //On regarde si ce triangle est contenu dans la boîte
            //C'est le cas si un de ses vertex est contenu dans la boîte

            //Boite gauche
            if(bbxs[0].contains( Scene::getInstance()->getVerteces().at(t.getVertex(0)).getPos()) ||
                    bbxs[0].contains(Scene::getInstance()->getVerteces().at(t.getVertex(1)).getPos()) ||
                    bbxs[0].contains(Scene::getInstance()->getVerteces().at(t.getVertex(2)).getPos())
                    ){
                triG.push_back(indexCurTriangle);
            }

            //Boite droite
            if(bbxs[1].contains( Scene::getInstance()->getVerteces().at(t.getVertex(0)).getPos()) ||
                    bbxs[1].contains(Scene::getInstance()->getVerteces().at(t.getVertex(1)).getPos()) ||
                    bbxs[1].contains(Scene::getInstance()->getVerteces().at(t.getVertex(2)).getPos())
                    ){
                triD.push_back(indexCurTriangle);
            }

        }

        //On construit les deux fils
        fg = new KDTreeXYZ(triG,bbxs[0],dim+1,prof+1);
        fd = new KDTreeXYZ(triD,bbxs[1],dim+1,prof+1);

    }
}


 void KDTreeXYZ::intersect(Ray & ray){
    Vec3Df intersecPt;

    //On teste qi ce n'est pas une feuille de l'arbre
    if(fg == NULL){ //Normalement fils gauche et fils droit sont null si c'est une feuille
        for(unsigned int i = 0 ; i++;  i< indexTriangles.size()){
            //Si on a une intersection entre le rayon et le triangle, on ajoute les coordonnées de l'intersection et le numéto du triangle au ray
            if(ray.intersect(Scene::getInstance()->getTriangles().at(indexTriangles.at(i)), Scene::getInstance()->getVerteces(), intersecPt)){
                ray.addIntersectPt(intersecPt);
                ray.addTriangleToIndex(indexTriangles.at(i));
            }
        }

    }
    //Il faut rester si le rayon s'intersecte avec le kdTree
   //Pour cela on le parcours en regardat si il s'intersecte avec la box courante si oui on va explorer les box filles.
   //Si on explore les filles
    else if(ray.intersect(box, intersecPt)){
        fg->intersect(ray);
        fd->intersect(ray);
    }

 }
