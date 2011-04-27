/*
 * RotationMatrix.cpp
 *
 *  Created on: 27 avril 2011
 *      Author: pierr
 */

#include "RotationMatrix.h"
#include "Matrix.h"
#define PI 3.14159265
RotationMatrix::RotationMatrix(double _teta, Matrix::Axis axis) {
    switch (axis){
    case X:
        new (this) RotationMatrix( 1.,0.,0.,0.,
                                   0.,std::cos(_teta*PI/180.),-1.*std::sin(_teta*PI/180.),0.,
                                   0.,std::sin(_teta*PI/180.),std::cos(_teta*PI/180.), 0.,
                                   0.,0.,0.,1.,
                                   _teta
                             );
        break;
    case Y:
        new (this) RotationMatrix( std::cos(_teta*PI/180.) , 0. , std::sin(_teta*PI/180.) , 0. ,
                                   0. , 1., 0., 0.,
                                  -1* std::sin(_teta*PI/180.) ,0., std::cos(_teta*PI/180.) ,  0.  ,
                                   0., 0. , 0. , 1. ,
                                   _teta
                                 );
        break;
    case Z://Rotation autour de l'axe Z
        new (this) RotationMatrix( std::cos(_teta*PI/180.),-1.*std::sin(_teta*PI/180.),0.,0.,
                                   std::sin(_teta*PI/180.),std::cos(_teta*PI/180.), 0.,0.,
                                   0.,0.,1.,0.,
                                   0.,0.,0.,1.,
                                   _teta
                                 );
        break;
    case Other:
    default:
        break;
    }
    this->teta = _teta;
        //std::cout << "_ teta "<< _teta;
}
RotationMatrix::RotationMatrix(double _teta, Vec3Df axis){
    axis.normalize();
    float c = std::cos(_teta*PI/180.);
    float s = std::sin(_teta*PI/180.);
    float ux = axis[0];
    float uy = axis[1];
    float uz = axis[2];
    new (this) RotationMatrix( ux*ux +(1.-ux*ux)*c , ux*uy*(1-c) - uz*s ,ux*uz*(1-c) + uy*s , 0.,
                               ux*uy*(1-c) + uz*s, uy*uy +(1.-uy*uy)*c, uy*uz*(1-c) - ux*s , 0. ,
                               ux*uz*(1-c) - uy*s, uy*uz*(1-c) + ux*s ,uz*uz +(1.-uz*uz)*c  , 0.,
                               0., 0., 0., 0.,
                               _teta
                             );
}
RotationMatrix::RotationMatrix(
        double l0v0, double l0v1, double l0v2, double l0v3,
        double l1v0, double l1v1, double l1v2, double l1v3,
        double l2v0, double l2v1, double l2v2, double l2v3,
        double l3v0, double l3v1, double l3v2, double l3v3
        , double _teta
        ): Matrix::Matrix( l0v0,  l0v1,  l0v2,  l0v3,
                           l1v0,  l1v1,  l1v2,  l1v3,
                           l2v0,  l2v1,  l2v2,  l2v3,
                           l3v0,  l3v1,  l3v2,  l3v3){
    this->teta = _teta;
}

RotationMatrix::~RotationMatrix() {
	// TODO Auto-generated destructor stub
}
