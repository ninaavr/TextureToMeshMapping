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
	/**loads a matrix which is used for finding a least square conformal mapping
	 *  and contains calculations for vertices with previously fixed texture coordinates
	 * @param tp textured polyhedron
	 * @param pinnedVertices std list of the vertices with predefined texture coordinates*/
	void load_M(TexturedPolyhedron& tp, Eigen::SparseMatrix<double>& M);
	/**stores the soluton of Matrix_solver from the vector to the mesh*/
	void store_result(Eigen::VectorXd& textures,  TexturedPolyhedron& tp);
private:
	/**sets std map has_textures to 2 if it is a simpl seam vertex and to 3 if it is branch vertex
	 * sets std map seam to true for the vertices which lie on the virtual cut of the polyhedron
	 * and std map this_type to true for the vertices which texture coordinates are not fixed previously
	 * @param tp the textured polyhedron */
	void set_tags(TexturedPolyhedron& tp);
};

#endif /* FREEMATTRIXLOADER_H_ */
