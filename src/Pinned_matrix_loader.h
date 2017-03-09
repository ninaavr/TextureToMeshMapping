/*
 * Pinnedmatrixloader.h
 *
 *  Created on: 4 Dec 2016
 *      Author: ninaavr
 */

#ifndef PINNEDMATRIXLOADER_H_
#define PINNEDMATRIXLOADER_H_

#include "Matrix_loader.h"

class Pinned_matrix_loader:Matrix_loader {
private:
	typedef TexturedPolyhedron::Halfedge_around_vertex_circulator HV_circulator;
public:
	/**sets the matrix where the calculations for the vertices and their facets are loaded
	 * @param _M the matrix*/
	Pinned_matrix_loader();
	virtual ~Pinned_matrix_loader();
	/**loads a matrix which is used for finding a least square conformal mapping
	 * and contains calculations for vertices with previously fixed texture coordinates
	 * @param tp textured polyhedron
	 * @param pinnedVertices std list of the vertices with predefined texture coordinates*/
	void load_M(TexturedPolyhedron& tp, Eigen::SparseMatrix<double>& M);

	void load_U(TexturedPolyhedron& tp, Eigen::SparseMatrix<double>& U);
private:
	/**sets std map seam to true for the vertices which lie on the virtual cut of the polyhedron
	 * and std map this_type to true for the vertices which texture coordinates are fixed previously
	 * @param tp the textured polyhedron
	 * @param pinned std list of the vertices with predefined texture coordinates*/
	void set_tags(TexturedPolyhedron& tp);
	/**loads the calculations for a given vertex with all the facets that contain it in a given matrix
	 * @param h the given vertex */
	void load_vertex(Vertex_handle& h, Eigen::SparseMatrix<double>& M);
};

#endif /* PINNEDMATRIXLOADER_H_ */
