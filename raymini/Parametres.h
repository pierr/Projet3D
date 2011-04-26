#ifndef PARAMETRES_H
#define PARAMETRES_H

class Parametres{
public:
//pixels
    const static int pix_grille = 1;
//BRDF
    const static bool BRDF_active = false;
//ombres
    const static bool ombres_active = false;
    const static int ombres_numa = 2;
    const static int ombres_numr = 2;

//ambocc
    const static bool ambocc_active = true;
    const static int ambocc_nray = 30;
    const static int ambocc_angle = 45;
    const static float ambocc_rayon;

//kdtree
    const static int kd_maxdeep = 5;

//autres
    const static float epsilon = 0.0001f;
};

#endif // PARAMETRES_H
