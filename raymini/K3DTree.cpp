#include "K3DTree.h"

void K3DTree::initA(PointSet *psinit, int dim, int ini, int fin){

        int imed;
        PointSet infPs, supPs;

        //Cas de base
        if(ini>fin)
                return;
        if(ini==fin){
                V = psinit->V[ini];
                supTree = NULL;
                infTree = NULL;
                splitDim = 0;
                return;
        }

        //Ordonner donn√©es dans la dimension "dim"
        psinit->quickSort(dim, ini, fin);

        // Affecter donn√©e pour le node
        imed = (ini+fin)/2;
        V = psinit->V[imed];
        splitDim = dim;

        // Construire recursivement les fils
        if(ini < imed){
                infTree = new K3DTree();
                infTree->initA(psinit, (dim+1)%3, ini, imed-1);
        }
        else infTree = NULL;

        if(imed < fin){
                supTree = new K3DTree();
                supTree->initA(psinit, (dim+1)%3, imed+1, fin);
        }
        else supTree = NULL;
}


void K3DTree::initB(PointSet *psinit, int ini, int fin){

        int dim, i, icentre;
        PointSet infPs, supPs;
        float min[3], max[3], centre, dist;

        //Cas de base
        if(ini>fin)
                return;
        if(ini==fin){
                V = psinit->V[ini];
                supTree = NULL;
                infTree = NULL;
                splitDim = 0;
                return;
        }

    // Trouver min et max dans chaque dimension
        for(dim=0; dim<3; dim++) {

                min[dim] = max[dim] = psinit->V[ini].p[dim];

                for(i=ini+1; i<fin; i++){

                        if(psinit->V[i].p[dim] > max[dim]){
                                max[dim] = psinit->V[i].p[dim];
                        }

                        if(psinit->V[i].p[dim] < min[dim]){
                                min[dim] = psinit->V[i].p[dim];
                        }
                }
        }

        // Choisir dimension avec range maximal
        splitDim = 0;
        if(max[1]-min[1] > max[0]-min[0])
                splitDim = 1;
        if(max[2]-min[2] > max[splitDim]-min[splitDim])
                splitDim = 2;

        //Ordonner donn√©es dans la dimension selection√©e
        psinit->quickSort(splitDim, ini, fin);

    // Chercher le point le plus proche au milieu dans la dimension splitDim
        centre = (max[splitDim] + min[splitDim])/2;
        icentre = ini;
        dist = abs(psinit->V[ini].p[splitDim] - centre);
        for(i=ini; i<fin; i++){
                if( abs(psinit->V[i].p[splitDim] - centre) < dist ){
                        icentre = i;
                        dist = abs(psinit->V[i].p[splitDim] - centre);
                }
        }

        // Choisir comme donn√©e pour le node
        V = psinit->V[icentre];

        // Construire recursivement les fils
        if(ini < icentre){
                infTree = new K3DTree();
                infTree->initB(psinit, ini, icentre-1);
        }
        else infTree = NULL;

        if(icentre < fin){
                supTree = new K3DTree();
                supTree->initB(psinit, icentre+1, fin);
        }
        else supTree = NULL;

}


// Additionner les points dans un rayon RAY du point CENTRE
// Avec la ponderation de Wendland par rapport a la distance normalis√©e
void K3DTree::sumVoisins(Vec3Df centre, float ray, Vec3Df *sump,Vec3Df *sumn, int *i) {

    float cw;
    float dist = (centre - V.p).getLength(), r;

        globalCount++;

        if ( dist <= ray ){
                r = dist/ray;
                cw = (1-r)*(1-r)*(1-r)*(1-r)*(4*r + 1);
                (*sump) += cw*V.p;
                (*sumn) += cw*V.n;
                (*i)++;
        }

        if ( infTree != NULL && centre[splitDim] - ray < V.p[splitDim] ) {
                infTree->sumVoisins(centre, ray, sump, sumn, i);
        }

        if (supTree != NULL && centre[splitDim] + ray > V.p[splitDim] ) {
                supTree->sumVoisins(centre, ray, sump, sumn, i);
        }
}


// Imprimer l'arbre: seulement pour tester, ne pas utiliser avec le nuage complet!
void K3DTree::afficher(int level){

        for(int i=0; i<level; i++)
                cout << "  ";

        // Afficher racine
        cout << "(" << V.p[0] << "," << V.p[1] << "," << V.p[2] << ") - split: " << splitDim << endl;

        if(infTree != NULL)
                infTree->afficher(level+1);
        if(supTree != NULL)
                supTree->afficher(level+1);
}


// Calculer la profondeur de l'arbre
int K3DTree::profondeur(){

        int profSup=0, profInf=0;

        if(supTree == NULL && infTree == NULL)
                return 1;

        if(supTree != NULL)
                profSup = supTree->profondeur();
        if(infTree != NULL)
                profInf = infTree->profondeur();

        if(profSup > profInf)
                return profSup + 1;
        else
                return profInf + 1;
}
