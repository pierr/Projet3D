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
class RotationMatrix: public Matrix {
public:
	double teta;
	RotationMatrix(double _teta);
	virtual ~RotationMatrix();
};

#endif /* ROTATIONMATRIX_H_ */
