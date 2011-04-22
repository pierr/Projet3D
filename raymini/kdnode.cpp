#include "kdnode.h"
#include "float.h"

#include <iostream>

using namespace std;

void kdnode::split(int max_deep, std::vector<kdnode>& deepnodes)
{
    //si on na pas arrive a deep==max_deep ou le vecteur a plus d'un leaf, on doit diviser
    if(leafs.size()>1 && deep<max_deep){
        //l'axe de division
        axis = deep%3;
        //calcul rapide(?) de la mediane
        float median = 0;
        float min_median = -FLT_MAX;
        float max_median = FLT_MAX;
        for(unsigned int i=0; i<leafs.size(); i++){
            kdleaf ileaf = leafs[i];
            Vec3Df ibar = ileaf.get_barycentre();
            if(min_median<ibar[axis] && ibar[axis]<max_median){
                unsigned int count_over = 0;
                unsigned int count_under = 0;
                for(unsigned int j=0; j<leafs.size(); j++){
                    kdleaf jleaf = leafs[j];
                    Vec3Df jbar = jleaf.get_barycentre();
                    if(jbar[axis] < ibar[axis]) count_under++;
                    else if(jbar[axis] > ibar[axis]) count_over++;
                }
                if(count_under > count_over)        max_median = ibar[axis];
                else if(count_under < count_over)   min_median = ibar[axis];
                else {
                    median = ibar[axis];
                    break;
                }
            }
        }
        if(median==0) median=(min_median+max_median)/2;

        // on divise leafs en 2 vecteurs en coupant par la mediane
        std::vector<kdleaf> supleafs;
        std::vector<kdleaf> infleafs;
        for(unsigned int i=0; i<leafs.size(); i++){
            kdleaf ileaf = leafs[i];
            Vec3Df iv0 = ileaf.get_v0();
            Vec3Df iv1 = ileaf.get_v1();
            Vec3Df iv2 = ileaf.get_v2();
            //il n'intersecte pas avec le plan de division
//            cout << iv0[axis] << " " << iv1[axis] << " " << iv2[axis] << endl;
            if(iv0[axis]<median && iv1[axis]<median && iv2[axis]<median)
                infleafs.push_back(leafs[i]);
            else if(iv0[axis]>median && iv1[axis]>median && iv2[axis]>median)
                supleafs.push_back(leafs[i]);
            //il intersecte avec le plan de division
            else {
                infleafs.push_back(leafs[i]);
                supleafs.push_back(leafs[i]);
            }
        }
        leafs.clear();

        //on cree les deux nouveaux noeuds
        //les deux noeuds divisent a nouveau chaque vecteur
        //on push les kdnode de maximum profondeur
        if(infleafs.size()>0){
            Vec3Df box_max = box.getMax();
            Vec3Df box_min = box.getMin();
            box_max[axis] = median;
            BoundingBox infbox(box_min, box_max);
            kdnode infnode = kdnode(deep+1,infleafs,infbox);
            infnode.split(max_deep, deepnodes);
            infleafs = infnode.get_leafs();
        }

        if(supleafs.size()>0){
            Vec3Df box_max = box.getMax();
            Vec3Df box_min = box.getMin();
            box_min[axis] = median;
            BoundingBox supbox(box_min, box_max);
            kdnode supnode = kdnode(deep+1,supleafs,supbox);
            supnode.split(max_deep, deepnodes);
            supleafs = supnode.get_leafs();
        }
    } else {
        deepnodes.push_back(*this);
    }
}
