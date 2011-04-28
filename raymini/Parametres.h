#ifndef PARAMETRES_H
#define PARAMETRES_H

#include <QObject>
#include <QCheckBox>
#include <iostream>

#define PI 3.141592

using namespace std;

class Parametres : public QObject {
    Q_OBJECT
public:
    inline Parametres(QObject *parent = 0) : QObject(parent) {
        pix_grille =        1;
        material_active =   true;
        BRDF_active =       true;
        diff_active =       true;
        spec_active =       true;
        brillance =         1;

        ombres_active =     false;
        ombres_numa =       2;
        ombres_numr =       2;

        ambocc_active =     false;
        ambocc_nray =       30;
        ambocc_theta =      90;
        ambocc_rayon =      0.05f;

        kd_propdeep =       0.05;

        path_active =       false;
        path_theta =        1;
        path_numrdiff =     20;
        path_numrspec =     1;
        path_pondmin =      0.01;
        path_maxdeep =      3;

        kd_done = -1; //kd to do
        epsilon =           0.0001f;

    }
    inline virtual ~Parametres() {}

    //get qu'on utilise sur le GUI
    inline int get_pixgrille()                      { return pix_grille; }
    inline bool get_materialactive()                { return material_active; }
    inline bool get_BRDFactive()                    { return BRDF_active; }
    inline bool get_diffactive()                    { return diff_active; }
    inline bool get_specactive()                    { return spec_active; }
    inline float get_brillance()                    { return brillance; }

    inline bool get_ombresactive()                  { return ombres_active; }
    inline int get_ombresnuma()                     { return ombres_numa; }
    inline int get_ombresnumr()                     { return ombres_numr; }

    inline bool get_amboccactive()                  { return ambocc_active; }
    inline int get_amboccnray()                     { return ambocc_nray; }
    inline float get_ambocctheta()                  { return ambocc_theta; }
    inline float get_amboccrayon()                  { return ambocc_rayon; }

    inline bool get_kddone()                        { return kd_done!=kd_propdeep; }
    inline float get_kdpropdeep()                   { return kd_propdeep; }

    inline bool get_pathactive()                    { return path_active; }
    inline float get_paththeta()                    { return path_theta; }
    inline int get_pathnumrdiff()                   { return path_numrdiff; }
    inline int get_pathnumrspec()                   { return path_numrspec; }
    inline float get_pathpondmin()                  { return path_pondmin; }
    inline float get_pathmaxdeep()                  { return path_maxdeep; }

    //get internes
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
                   << "kD Tree prof max " << kd_propdeep <<  std::endl
                   << " epsilon "<< epsilon
                   << std::endl;
    }
public slots:
    inline void set_pixgrille(int pix_grille)                   { this->pix_grille = pix_grille; }

    inline void set_materialactive(bool material_active)        { this->material_active = material_active; }
    inline void set_BRDFactive(bool BRDF_active){
        this->BRDF_active = BRDF_active;
        if(ombres_active && !BRDF_active){
            ombres_active = false;
            ombresCheckBox->setChecked(false);
        }
    }
    inline void set_BRDFcheckbox(QCheckBox * BRDFCheckBox)      { this->BRDFCheckBox = BRDFCheckBox; }
    inline void set_diffactive(bool diff_active)                { this->diff_active = diff_active; }
    inline void set_diffcheckbox(QCheckBox * diffCheckBox)      { this->diffCheckBox = diffCheckBox; }
    inline void set_specactive(bool spec_active)                { this->spec_active = spec_active; }
    inline void set_speccheckbox(QCheckBox * specCheckBox)      { this->specCheckBox = specCheckBox; }
    inline void set_brillance(double brillance)                  { this->brillance = (float)brillance; }

    inline void set_ombresactive(bool ombres_active){
        this->ombres_active = ombres_active;
        if(ombres_active && !BRDF_active){
            BRDF_active = true;
            BRDFCheckBox->setChecked(true);
        }
    }
    inline void set_ombrescheckbox(QCheckBox * ombresCheckBox)  { this->ombresCheckBox = ombresCheckBox; }
    inline void set_ombresnuma(int ombres_numa)                 { this->ombres_numa = ombres_numa; }
    inline void set_ombresnumr(int ombres_numr)                 { this->ombres_numr = ombres_numr; }

    inline void set_amboccactive(bool ambocc_active)            { this->ambocc_active = ambocc_active; }
    inline void set_amboccnray(int ambocc_nray)                 { this->ambocc_nray = ambocc_nray; }
    inline void set_ambocctheta(double ambocc_theta)            { this->ambocc_theta = (float)ambocc_theta; }
    inline void set_amboccrayon(double ambocc_rayon)            { this->ambocc_rayon = (float)ambocc_rayon; }

    inline void set_kddone()                                    { this->kd_done = this->kd_propdeep; }
    inline void set_kdpropdeep(double kd_propdeep)              { this->kd_propdeep = (float)kd_propdeep; }

    inline void set_pathactive(bool path_active)                { this->path_active = path_active; }
    inline void set_paththeta(double path_theta)                { this->path_theta = (float) path_theta; }
    inline void set_pathnumrdiff(int path_numrdiff)             { this->path_numrdiff = path_numrdiff; }
    inline void set_pathnumrspec(int path_numrspec)             { this->path_numrspec = path_numrspec; }
    inline void set_pathpondmin(double path_pondmin)             { this->path_pondmin = (float)     path_pondmin; }
    inline void set_pathmaxdeep(int path_maxdeep)               { this->path_maxdeep = path_maxdeep; }

    inline void set_epsilon(float epsilon)                      { this->epsilon = epsilon; }

private:
//rays
    int pix_grille;
    float brillance;
     bool material_active;
     bool BRDF_active;
     QCheckBox * BRDFCheckBox;
     bool diff_active;
     QCheckBox * diffCheckBox;
     bool spec_active;
     QCheckBox * specCheckBox;
//ombres
     bool ombres_active;
     QCheckBox * ombresCheckBox;
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
//pathtracing
     bool path_active;
     QCheckBox * pathCheckBox;
     float path_theta;
     int path_numrdiff;
     int path_numrspec;
     float path_pondmin;
     int path_maxdeep;
//autres
     float epsilon; //pour le ambocc et les ombres
};

#endif // PARAMETRES_H
