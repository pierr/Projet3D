#ifndef K3DTREE_H
#define K3DTREE_H
//----------------------------------------------------------------------
// Classe pour le kd-tree
//----------------------------------------------------------------------

class K3DTree {

        Vertex V;
        int splitDim; 		//0=x, 1=y, 2=z
        K3DTree *supTree;
        K3DTree *infTree;

        public:
                //void initMidRange(PointSet *psinit);
                void initA(PointSet *psinit, int dim, int ini, int fin);
                void initB(PointSet *psinit, int ini, int fin);
                void afficher(int level);
                int profondeur(void);
                void sumVoisins(Vec3Df centre, float ray, Vec3Df *sump, Vec3Df *sumn, int *i);

};
#endif
