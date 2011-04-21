#include "kdnode.h"
#include "float.h"

#include <iostream>

using namespace std;

std::vector<kdleaf> kdnode::sort()
{
    std::vector<kdleaf> supleafs;
    std::vector<kdleaf> infleafs;

    //si le vecteur a plus d'un leaf on doit ordonner
    cout << "leafs = " << leafs.size() << endl;
    if(leafs.size()>1){

        //calcul rapide(?) de la mediane
        float median;
        float min_median = 0; //min_vecteur
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
                median = ileaf.get_distance();
                if(count_under > count_over) max_median = ileaf.get_distance();
                else if(count_under < count_over) min_median = ileaf.get_distance();
                else break;
            }
        }

        // on divise notre vecteur en 2 vecteurs en coupant par la mediane
        for(unsigned int i=0; i<leafs.size(); i++){
            kdleaf ileaf = leafs.at(i);
            if(ileaf.get_distance() > median)
                supleafs.push_back(leafs.at(i));
            else
                infleafs.push_back(leafs.at(i));
        }
        cout << "sup = " << supleafs.size() << "\tinf = " << infleafs.size() << endl;
        leafs.clear();

        //on cree les deux nouveaux noeuds
        kdnode supnode = kdnode(supleafs);
        kdnode infnode = kdnode(infleafs);

        //les deux noeuds ordonnent chaque vecteur
        supleafs = supnode.sort();
        infleafs = infnode.sort();
        delete &supnode;
        delete &infnode;

        //on rassemble les deux vecteurs
        for(unsigned int i=0; i<infleafs.size(); i++){
            leafs.push_back(infleafs.at(i));
        }
        for(unsigned int i=0; i<supleafs.size(); i++){
            leafs.push_back(supleafs.at(i));
        }
    }
    return leafs;
}
