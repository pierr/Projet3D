/*
 * RotationMatrix.h
 *
 *  Created on: 27 avril 2011
 *      Author: pierr
 */

#ifndef ROTATIONMATRIX_H_
#define ROTATIONMATRIX_H_

#include "Matrix.h"
#include <cmath>
#include "Vec3D.h"
class RotationMatrix: public Matrix {
public:
	double teta;
        RotationMatrix(double _teta, Matrix::Axis axis);
        RotationMatrix(double _teta, Vec3Df axis);
        RotationMatrix(
                double l0v0,double l0v1, double l0v2, double l0v3,
                double l1v0,double l1v1, double l1v2, double l1v3,
                double l2v0,double l2v1, double l2v2, double l2v3,
                double l3v0,double l3v1, double l3v2, double l3v3,
                double _teta
                );

        virtual ~RotationMatrix();
private:
        void initAxisX(double teta);
        void initAxisY(double teta);
        void initAxisZ(double teta);
        void initAxisOther(double teta);
    };

#endif /* ROTATIONMATRIX_H_ */
