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
	/**sets the matrix where the calculations for the vertices and their facets are loaded
	 * @param _M the matrix*/
	Free_matrix_loader();
	virtual ~Free_matrix_loader();
	/**loads a matrix which is used for finding a least square conformal mapping
	 *  and contains calculations for vertices with previously fixed texture coordinates
	 * @param tp textured polyhedron
	 * @param pinnedVertices std list of the vertices with predefined texture coordinates*/
	void load_M(TexturedPolyhedron& tp, Vertices& pinnedVertices, Eigen::SparseMatrix<double>& M);
private:
	/**sets std map seam to true for the vertices which lie on the virtual cut of the polyhedron
	 * and std map this_type to true for the vertices which texture coordinates are not fixed previously
	 * @param tp the textured polyhedron
	 * @param pinned std list of the vertices with predefined texture coordinates*/
	void set_tags(TexturedPolyhedron& tp, Vertices& pinned);
};

#endif /* FREEMATTRIXLOADER_H_ */
