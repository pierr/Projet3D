/*
 * Matrix.h
 *
 *  Created on: 27 avril 2011
 *      Author: pierr
 */

#ifndef MATRIX_H_
#define MATRIX_H_
#include <iostream>
#include "Vec3D.h"
class Matrix {
private:

public:
        double matrix[4][4];
        //double** matrix;
        static int const dim = 4;
        enum Axis
           {
              X,
              Y,
              Z,
              Other
           };
        /*
         * Constructeur qui initialise une matrice 4*4 nulle
         * */
        Matrix();
        /**
         * Constructeur qui initialise une matrice 4*4 non nulle
         * */
        Matrix(double valeur);
        /*
         * Constrcteur qui crée une nouvelle matrice à partir d'une autre
         * */
        Matrix(const Matrix &source);
        /**
         * Constructeur qui initialise une matrice avce la valeur de chacun de ces coeffs
         * */
        Matrix(
                        double l0v0,double l0v1, double l0v2, double l0v3,
                        double l1v0,double l1v1, double l1v2, double l1v3,
                        double l2v0,double l2v1, double l2v2, double l2v3,
                        double l3v0,double l3v1, double l3v2, double l3v3

        );
        /*
         * Destructeur de matrice
         * */
        virtual ~Matrix();
        /*
         * Méthode qui permet de changer une valeur dans la matrice
         * line -> numéro de la ligne
         * col -> numéro de la colonne
         * value -> la valeur
         * */
        void setValue(int line, int col, double value);
        Matrix & operator=(const Matrix &mat);
        /*
         * On va redéfinir l'opérateur * de manière à faire un produit matriciel
         * */
        Matrix & operator*=(const Matrix &mat);
        Matrix  operator*(const Matrix &mat);
        Vec3Df  operator*( Vec3Df &vec);
        /*
         * On redéfini l'opérateur * avec un double pour qu'il multiplie chacun des coeffs
         * */
        Matrix & operator*=(const double nb);

        /*
         * Redéfinition de l'opérateur + de manière à faire une addition de matrice
         * */
        Matrix & operator+=(const Matrix &mat);
        /*
         * Redéfinition de l'opérateur - de manière * faire une soustraction de matrice
         * */
        Matrix & operator-=(const Matrix &mat);
        /*
         * On redéfini l'opérateur d'affichage de manière à bien afficher une matrice
         * */
    friend std::ostream & operator<<(std::ostream &os,const Matrix &mat);
    /*Méthode qui permet d'avoir la dimension de la matrice qui est 4 ici*/
    int const getDim();
    //double[4][4] getMatrix();
};
std::ostream & operator<<(std::ostream &os,const Matrix &mat);
#endif /* MATRIX_H_ */
