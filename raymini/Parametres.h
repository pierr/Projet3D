#ifndef PARAMETRES_H
#define PARAMETRES_H

#include <QObject>
#include <QCheckBox>
#include <iostream>

#include "Vec3D.h"

#define PI 3.141592

using namespace std;

class Parametres : public QObject {
    Q_OBJECT
public:
    //atributs
    int screenheight, screenweight;
    Vec3Df render_col[1000][1000];

    inline Parametres(QObject *parent = 0) : QObject(parent) {
        for(unsigned int i=0; i<1000; i++)
            for(unsigned int j=0; j<1000; j++)
                render_col[i][j] = Vec3Df();

        pix_grille =        1;
        material_active =   true;
        BRDF_active =       true;
        diff_active =       true;
        spec_active =       true;
        brillance =         1;
        ambiantLight =      0;
        saturation =        1;

        ombres_active =     false;
        ombres_douces =     false;
        ombres_numa =       2;
        ombres_numr =       2;

        ambocc_active =     false;
        ambocc_nray =       30;
        ambocc_theta =      90;
        ambocc_rayon =      1.0f;

        kd_propdeep =       0.05;

        path_active =       false;
        path_theta =        90;
        path_nray =         30;
        path_maxdeep =      2;

        kd_done = -1; //kd to do
        epsilon =           0.0001f;
    }
    inline virtual ~Parametres() {}

    //get qu'on utilise sur le GUI
    inline bool get_renderdone()                    { return render_done; }
    inline int get_pixgrille()                      { return pix_grille; }
    inline bool get_materialactive()                { return material_active; }
    inline bool get_BRDFactive()                    { return BRDF_active; }
    inline bool get_diffactive()                    { return diff_active; }
    inline bool get_specactive()                    { return spec_active; }
    inline float get_brillance()                    { return brillance; }
    inline float get_ambiantLight()                 { return ambiantLight; }
    inline float get_saturation()                   { return saturation; }

    inline bool get_ombresactive()                  { return ombres_active; }
    inline bool get_ombresdouces()                  { return ombres_douces; }
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
    inline int get_pathnray()                       { return path_nray; }
    inline float get_pathmaxdeep()                  { return path_maxdeep; }

    //get internes
    inline float get_epsilon() { return epsilon; }
    inline void print(){

        std::cout  << "RAYS PARAMETERS " << std::endl
                   << "nombre de pixel par grille"<< pix_grille << std::endl
                   << "is Material " << material_active << std::endl
                   << "is BRDF " << BRDF_active << std::endl
                   << "briallance "<< brillance << std::endl
                   << "ambiant Light" << ambiantLight << std::endl
                   << "diff active " << diff_active << std::endl
                   << "spec active" << std::endl
                   <<"AMBIANT OCCLUSION PARAMETERS " << std::endl
                   << "ao active " << ambocc_active << std::endl
                   << "ao nRay " << ambocc_nray << std::endl
                   << "ao rayon "  << ambocc_rayon << std::endl
                   << "ao teta  " << ambocc_theta << std::endl
                   << std::endl


                   <<"OMBRES PARAMETERS "<< std::endl
                   << "isOmbres "<< ombres_active << std::endl
                   << "isOmbres douce "<< ombres_douces << std::endl
                   << "Ombres numA "  << ombres_numa << std::endl
                   << "Ombres numR" << ombres_numr <<  std::endl

                   << "KD TREE PARAMETERS" << std::endl
                   << "kD Tree prof max " << kd_propdeep <<  std::endl
                   << "KD done " << kd_done << std::endl
                   << "epsilon "<< epsilon << std::endl
                   << std::endl
                   << "PATH TRACING PARAMETERS" << std::endl
                   << "is Active "<< path_active << std::endl
                      //<< "is diff coeff " << path_diff << std::endl
                      //<< "is spec coeff "<<  path_spec << std::endl
                   << "path teta cone" <<  path_theta << std::endl
                   << "num Ray" << path_nray << std::endl
                   << "path max deep" <<  path_maxdeep << std::endl
                   << std::endl;
    }
public slots:
    inline void set_renderdone(bool render_done)                { this->render_done = render_done; }

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
    inline void set_brillance(double brillance)                 { this->brillance = (float)brillance; }
    inline void set_ambiantLight(double ambiant)                { this->ambiantLight = (float) ambiant; }
    inline void set_saturation (double saturation)              { this->saturation = (float) saturation; }

    inline void set_ombresactive(bool ombres_active){
        this->ombres_active = ombres_active;
        if(ombres_active && !BRDF_active){
            BRDF_active = true;
            BRDFCheckBox->setChecked(true);
        }
    }
    inline void set_ombrescheckbox(QCheckBox * ombresCheckBox)  { this->ombresCheckBox = ombresCheckBox; }
    inline void set_ombresdouces(bool ombres_douces)            { this->ombres_douces = ombres_douces; }
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
    inline void set_pathnray(int path_nray)                     { this->path_nray = path_nray; }
    inline void set_pathmaxdeep(int path_maxdeep)               { this->path_maxdeep = path_maxdeep; }

    inline void set_epsilon(float epsilon)                      { this->epsilon = epsilon; }

private:

    //render
    bool render_done;
    //rays
    int pix_grille;
    float brillance;
    float ambiantLight;
    float saturation;
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
    bool ombres_douces;
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
    int path_nray;
    float path_theta;
    int path_maxdeep;
    //autres
    float epsilon; //pour le ambocc et les ombres
};

#endif // PARAMETRES_H
