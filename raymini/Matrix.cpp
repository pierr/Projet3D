/*
 * Matrix.cpp
 *
 *  Created on: 27 avril 2011
 *      Author: pierr
 */

#include "Matrix.h"
Matrix::Matrix(){
	new (this)Matrix(0);
}
/**
 * Constructeur qui initialise une matrice 4*4 non nulle
 * */
Matrix::Matrix(double valeur){
	for(int i = 0 ; i < dim ; i++){
        for(int j = 0 ; j < dim ; j++){
            this->matrix[i][j] = valeur;
        }
	}
}
/*
 * Constrcteur qui cree une nouvelle matrice a partir d'une autre
 * */
Matrix::Matrix(const Matrix &source){
	for(int i = 0 ; i < dim ; i++){
		for(int j = 0 ; j < dim ; j++){
			this->matrix[i][j] = source.matrix[i][j];
		}
	}
}
/**
 * Constructeur qui initialise une matrice avce la valeur de chacun de ces coeffs
 * */
Matrix::Matrix(
               double l0v0,double l0v1, double l0v2, double l0v3,
               double l1v0,double l1v1, double l1v2, double l1v3,
               double l2v0,double l2v1, double l2v2, double l2v3,
               double l3v0,double l3v1, double l3v2, double l3v3
               ){
    this->matrix[0][0] = l0v0;
    this->matrix[0][1] = l0v1;
    this->matrix[0][2] = l0v2;
    this->matrix[0][3] = l0v3;
    
    this->matrix[1][0] = l1v0;
    this->matrix[1][1] = l1v1;
    this->matrix[1][2] = l1v2;
    this->matrix[1][3] = l1v3;
    
    this->matrix[2][0] = l2v0;
    this->matrix[2][1] = l2v1;
    this->matrix[2][2] = l2v2;
    this->matrix[2][3] = l2v3;
    
    this->matrix[3][0] = l3v0;
    this->matrix[3][1] = l3v1;
    this->matrix[3][2] = l3v2;
    this->matrix[3][3] = l3v3;
}
/*
 * Destructeur de matrice
 * */
Matrix::~Matrix(){
    //il n'y a rien a detruire
}
/*
 * Methode qui permet de changer une valeur dans la matrice
 * line -> numero de la ligne
 * col -> numero de la colonne
 * value -> la valeur
 * */
void Matrix::setValue(int line, int col, double value){
    this->matrix[line][col] = value;
    //		/this->mat
}

Matrix & Matrix::operator*=(const Matrix &mat){
    Matrix m(0);
    for(int i=0; i<dim; i++){ //pour chq ligne...
        for(int j=0; j<dim; j++){ // pour chaque colone
            for( int k=0; k<dim; k++){ // produit scalaire
                m.matrix[i][j] += this->matrix[i][k]*mat.matrix[k][j];
            }
        }
    }
    new (this)Matrix(m);
    return *this;
}

Matrix  Matrix::operator*(const Matrix &mat){
    Matrix m(0);
    for(int i=0; i<dim; i++){ //pour chq ligne...
        for(int j=0; j<dim; j++){ // pour chaque colone
            for( int k=0; k<dim; k++){ // produit scalaire
                m.matrix[i][j] += this->matrix[i][k]*mat.matrix[k][j];
            }
        }
        
    }
    //std::cout << m << std::endl;
    return m;
}

/**
PROJECTION D'UN VECTEUR
*/
Vec3Df  Matrix::operator*( Vec3Df &vec){
    Vec3Df v;
    //std::cout  << *this << std::endl;
    //std::cout << vec << std::endl;
    v[0] = this->matrix[0][0]*vec[0]+matrix[0][1]*vec[1]+matrix[0][2]*vec[2];//+matrix[0][3];
    v[1] = this->matrix[1][0]*vec[0]+matrix[1][1]*vec[1]+matrix[1][2]*vec[2];//+matrix[1][3];
    v[2] = this->matrix[2][0]*vec[0]+matrix[2][1]*vec[1]+matrix[2][2]*vec[2];//+matrix[2][3];
    //std::cout << "mat * vec " << v << std::endl;
    return v;

}

/*
 * On va redefinir l'operateur * de maniere a faire un produit matriciel
 * */
Matrix & Matrix::operator=(const Matrix &mat){
    new (this)Matrix(mat);
    return *this;
}
/*
 * On redefini l'operateur * avec un double pour qu'il multiplie chacun des coeffs
 * */
Matrix & Matrix::operator*=(const double nb){
    for(int i =0 ; i<dim; i++){
        for(int j =0 ; j<dim ; j++){
            this->matrix[i][j] = nb*this->matrix[i][j];
        }
    }
    return *this;
}
/*
 * Redefinition de l'operateur + de maniere a faire une addition de matrice
 * */
Matrix & Matrix::operator+=(const Matrix &mat){
    for(int i =0 ; i<dim; i++){
        for(int j =0 ; j<dim ; j++){
            this->matrix[i][j] += mat.matrix[i][j];
        }
    }
    return *this;
}
/*
 * Redefinition de l'operateur - de maniere * faire une soustraction de matrice
 * */
Matrix & Matrix::operator-=(const Matrix &mat){
    for(int i =0 ; i<dim; i++){
        for(int j =0 ; j<dim ; j++){
            this->matrix[i][j] -= mat.matrix[i][j];
        }
    }
    return *this;
}
/*
 * On redefini l'operateur d'affichage de maniere a bien afficher une matrice
 * */
std::ostream & operator<<(std::ostream &os,const Matrix &mat){
    os << "{" << std::endl;
    for(int i =0 ; i<mat.dim; i++){
        os << "[ ";
        for(int j =0 ; j<mat.dim ; j++){
            os << mat.matrix[i][j]<< " ";
        }
        os << "]" << std::endl;
    }
    os << "}" << std::endl;
    return os;
}
/*Methode qui permet d'avoir la dimension de la matrice qui est 4 ici*/
int Matrix::getDim(){
    return 4;
}
