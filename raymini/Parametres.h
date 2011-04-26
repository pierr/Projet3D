#ifndef PARAMETRES_H
#define PARAMETRES_H

#include <QObject>
#include <QCheckBox>
#include <iostream>

using namespace std;

class Parametres : public QObject {
    Q_OBJECT
public:
    inline Parametres(QObject *parent = 0) : QObject(parent) {
        pix_grille =    1;
        material_active = true;
        BRDF_active =   true;
        ombres_active = true;
        ombres_numa =   2;
        ombres_numr =   2;
        ambocc_active = true;
        ambocc_nray =   30;
        ambocc_theta =  90;
        ambocc_rayon =  0.05f;
        kd_propdeep =    0.05;

        kd_done = -1; //kd to do
        epsilon =       0.0001f;
        kd_borneInf = 3;
        kd_borneSup = 20;
        kd_initValue = 8;
        path_active = true;
        path_nray = 20;
        path_theta = 10;
        path_rayon = 0.5;

    }
    inline virtual ~Parametres() {}

    inline int get_pixgrille()                      { return pix_grille; }
    inline bool get_materialactive()                { return material_active; }
    inline bool get_BRDFactive()                    { return BRDF_active; }

    inline bool get_ombresactive()                  { return ombres_active; }
    inline int get_ombresnuma()                     { return ombres_numa; }
    inline int get_ombresnumr()                     { return ombres_numr; }

    inline bool get_amboccactive()                  { return ambocc_active; }
    inline int get_amboccnray()                     { return ambocc_nray; }
    inline float get_ambocctheta()                  { return ambocc_theta; }
    inline float get_amboccrayon()                  { return ambocc_rayon; }

    inline bool get_kddone()                        { return kd_done!=kd_propdeep; }
    inline float get_kdpropdeep()                   { return kd_propdeep; }

    inline float get_epsilon() { return epsilon; }
    bool get_path_active(){return path_active;}
    int get_pathnray(){return path_nray;}
    float get_paththeta(){return path_theta;}
    float get_pathrayon(){ return path_rayon;}
    inline void print(){

        std::cout  <<"AMBIANT OCCLUSION PARAMETERS "
                   << "ao active " << ambocc_active
                   << " ao nRay " << ambocc_nray
                   << " arayon "  << ambocc_rayon
                   << " ao teta  " << ambocc_theta
                   << std::endl
                   << "nombre de pixel par grille"<< pix_grille << std::endl
                   << " is BRDF " << BRDF_active << std::endl
                   << " isOmbres "<< ombres_active << std::endl
                   << "Ombres numA "  << ombres_numa << " Ombres numR" << ombres_numr <<  std::endl
                   << "kD Tree prof max " << kd_propdeep <<  std::endl
                   << " epsilon "<< epsilon
                   << std::endl;
    }
public slots:
    inline void set_pixgrille(int pix_grille)               { this->pix_grille = pix_grille; }

    inline void set_materialactive(bool material_active)    { this->material_active = material_active; }
    inline void set_BRDFactive(bool BRDF_active)            { this->BRDF_active = BRDF_active; }
    inline void set_BRDFcheckbox(QCheckBox * BRDFCheckBox)  { this->BRDFCheckBox = BRDFCheckBox; }

    inline void set_ombresactive(bool ombres_active){
        this->ombres_active = ombres_active;
        if(ombres_active && !BRDF_active){
            BRDF_active = true;
            BRDFCheckBox->setChecked(true);
        }
    }    inline void set_ombresnuma(int ombres_numa)        { this->ombres_numa = ombres_numa; }
    inline void set_ombresnumr(int ombres_numr)             { this->ombres_numr = ombres_numr; }

    inline void set_amboccactive(bool ambocc_active)        { this->ambocc_active = ambocc_active; }
    inline void set_amboccnray(int ambocc_nray)             { this->ambocc_nray = ambocc_nray; }
    inline void set_ambocctheta(double ambocc_theta)        { this->ambocc_theta = (float)ambocc_theta; }
    inline void set_amboccrayon(double ambocc_rayon)        { this->ambocc_rayon = (float)ambocc_rayon; }

    inline void set_kddone()                                { this->kd_done = this->kd_propdeep; }
    inline void set_kdpropdeep(double kd_propdeep)          { this->kd_propdeep = (float)kd_propdeep; }

    inline void set_epsilon(float epsilon)                  { this->epsilon = epsilon; }

private:
//rays
    int pix_grille;
     bool material_active;
     bool BRDF_active;
     QCheckBox * BRDFCheckBox;
//ombres
     bool ombres_active;
     int ombres_numa;
     int ombres_numr;

//ambocc
     bool ambocc_active;
     int ambocc_nray;
     float ambocc_theta;
     float ambocc_rayon;

//kdtree
     float kd_done; //pour voir si on doit refaire le kdtree
     float kd_propdeep;

     int kd_maxdeep;
     int kd_borneInf;
     int kd_borneSup;
     int kd_initValue;
//pathtracing
     bool path_active;
     int path_nray;
     float path_theta;
     float path_rayon;
//autres
     float epsilon; //pour le ambocc et les ombres
};

#endif // PARAMETRES_H
