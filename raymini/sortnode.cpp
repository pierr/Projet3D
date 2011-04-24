#include "sortnode.h"
#include "float.h"

#include <iostream>

using namespace std;

std::vector<kdleaf> sortnode::sort()
{
    std::vector<kdleaf> supleafs;
    std::vector<kdleaf> midleafs;
    std::vector<kdleaf> infleafs;

    //si le vecteur a plus d'un leaf on doit ordonner
    if(leafs.size()>1){

        //calcul rapide(?) de la mediane
        float median = 0;
        float min_median = 0;
        float max_median = FLT_MAX;
        for(unsigned int i=0; i<leafs.size(); i++){
            kdleaf ileaf = leafs.at(i);
            if(min_median<ileaf.get_distance() && ileaf.get_distance()<max_median){
                unsigned int count_over = 0;
                unsigned int count_under = 0;
                for(unsigned int j=0; j<leafs.size(); j++){
                    kdleaf jleaf = leafs.at(j);
                    if(jleaf.get_distance() < ileaf.get_distance()) count_under++;
                    else if(jleaf.get_distance() > ileaf.get_distance()) count_over++;
                }
                if(count_under > count_over) max_median = ileaf.get_distance();
                else if(count_under < count_over) min_median = ileaf.get_distance();
                else {
                    median = ileaf.get_distance();
                    break;
                }
            }
        }
        if(median==0) median=(min_median+max_median)/2;

        // on divise notre vecteur en 2 vecteurs en coupant par la mediane
        for(unsigned int i=0; i<leafs.size(); i++){
            kdleaf ileaf = leafs.at(i);
            if(ileaf.get_distance() > median)
                supleafs.push_back(leafs.at(i));
            else if(ileaf.get_distance() < median)
                infleafs.push_back(leafs.at(i));
            else
                midleafs.push_back(leafs.at(i));
        }
        leafs.clear();

        //on cree les deux nouveaux noeuds
        //les deux noeuds ordonnent chaque vecteur
        //on rassemble les vecteurs
        if(infleafs.size()>0){
            sortnode infnode = sortnode(infleafs);
            infleafs = infnode.sort();
            for(unsigned int i=0; i<infleafs.size(); i++)
                leafs.push_back(infleafs.at(i));
        }
        if(midleafs.size()>0){
            for(unsigned int i=0; i<midleafs.size(); i++)
                leafs.push_back(midleafs.at(i));
        }
        if(supleafs.size()>0){
            sortnode supnode = sortnode(supleafs);
            supleafs = supnode.sort();
            for(unsigned int i=0; i<supleafs.size(); i++)
                leafs.push_back(supleafs.at(i));
        }

    }
    return leafs;
}
