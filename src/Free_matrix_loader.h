/*
 * FreeMatrixLoader.h
 *
 *  Created on: 2 Dec 2016
 *      Author: ninaavr
 */

#ifndef FREEMATTRIXLOADER_H_
#define FREEMATTRIXLOADER_H_

#include "Matrix_loader.h"
class Free_matrix_loader: public Matrix_loader {
public:
	Free_matrix_loader();
	virtual ~Free_matrix_loader();
	void load_M(TexturedPolyhedron& tp, Vertices& pinnedVertices, Eigen::SparseMatrix<double>& M);
	void get_free_vertices(TexturedPolyhedron& tp, Vertices pinnedVertices, Vertices& freeVertices);
};

#endif /* FREEMATTRIXLOADER_H_ */
