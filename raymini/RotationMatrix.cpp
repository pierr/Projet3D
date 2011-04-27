/*
 * RotationMatrix.cpp
 *
 *  Created on: 27 avril 2011
 *      Author: pierr
 */

#include "RotationMatrix.h"
#include "Matrix.h"
#define PI 3.14159265
RotationMatrix::RotationMatrix(double _teta): Matrix::Matrix(
            std::cos(_teta*PI/180.),-1.*std::sin(_teta*PI/180.),0.,0.,
		std::sin(_teta*PI/180.),std::cos(_teta*PI/180.), 0.,0.,
                0.,0.,1.,0.,
		0.,0.,0.,1.
) {
	this->teta = _teta;
        //std::cout << "_ teta "<< _teta;
}

RotationMatrix::~RotationMatrix() {
	// TODO Auto-generated destructor stub
}
