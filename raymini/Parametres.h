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
        BRDF_active =   true;
        ombres_active = true;
        ombres_numa =   2;
        ombres_numr =   2;
        ambocc_active = true;
        ambocc_nray =   30;
        ambocc_theta =  90;
        ambocc_rayon =  0.05f;
        kd_maxdeep =    5;
        epsilon =       0.0001f;
        kd_borneInf = 3;
        kd_borneSup = 20;
        kd_initValue = 8;
    }
    inline virtual ~Parametres() {}

    inline int get_pixgrille() { return pix_grille; }

    inline bool get_BRDFactive() { return BRDF_active; }

    inline bool get_ombresactive() { return ombres_active; }
    inline int get_ombresnuma() { return ombres_numa; }
    inline int get_ombresnumr() { return ombres_numr; }

    inline bool get_amboccactive() { return ambocc_active; }
    inline int get_amboccnray() { return ambocc_nray; }
    inline int get_ambocctheta() { return ambocc_theta; }
    inline float get_amboccrayon() { return ambocc_rayon; }

    inline int get_kdmaxdeep() { return kd_maxdeep; }
    inline int get_kdBorneInf() { return kd_borneInf; }
    inline int get_kdBorneSup(){ return kd_borneSup;}
    inline int get_kdinitValue(){ return kd_initValue;}

    inline float get_epsilon() { return epsilon; }
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
                   << "kD Tree prof max " << kd_maxdeep <<  std::endl
                   << " epsilon "<< epsilon
                   << std::endl;
    }
public slots:
    inline void set_pixgrille(int pix_grille)       { this->pix_grille = pix_grille; }

    inline void set_BRDFactive(bool BRDF_active)    { this->BRDF_active = BRDF_active; }
    inline void set_BRDFcheckbox(QCheckBox * BRDFCheckBox)  { this->BRDFCheckBox = BRDFCheckBox; }

    inline void set_ombresactive(bool ombres_active){
        this->ombres_active = ombres_active;
        if(ombres_active && !BRDF_active){
            BRDF_active = true;
            BRDFCheckBox->setChecked(true);
        }
    }    inline void set_ombresnuma(int ombres_numa)     { this->ombres_numa = ombres_numa; }
    inline void set_ombresnumr(int ombres_numr)     { this->ombres_numr = ombres_numr; }

    inline void set_amboccactive(bool ambocc_active){ this->ambocc_active = ambocc_active; }
    inline void set_amboccnray(int ambocc_nray)     { this->ambocc_nray = ambocc_nray; }
    inline void set_ambocctheta(int ambocc_theta)   { this->ambocc_theta = ambocc_theta; }
    inline void set_amboccrayon(float ambocc_rayon) { this->ambocc_rayon = ambocc_rayon; }

    inline void set_kdmaxdeep(int kd_maxdeep)       { this->kd_maxdeep = kd_maxdeep; }

    inline void set_epsilon(float epsilon)          { this->epsilon = epsilon; }

private:
//pixels
     int pix_grille;
//BRDF
     bool BRDF_active;
     QCheckBox * BRDFCheckBox;
//ombres
     bool ombres_active;
     int ombres_numa;
     int ombres_numr;

//ambocc
     bool ambocc_active;
     int ambocc_nray;
     int ambocc_theta;
     float ambocc_rayon;

//kdtree
     int kd_maxdeep;
     int kd_borneInf;
     int kd_borneSup;
     int kd_initValue;

//autres
     float epsilon;
};

#endif // PARAMETRES_H
