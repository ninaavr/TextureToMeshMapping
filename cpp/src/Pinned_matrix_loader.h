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
	Pinned_matrix_loader();
	virtual ~Pinned_matrix_loader();
	/**loads a matrix which is used for finding a least square conformal mapping
	 * and contains calculations for vertices with previously fixed texture coordinates
	 * @param tp textured polyhedron
	 * @param M matrix which is loaded*/
	void load_M(TexturedPolyhedron& tp, Eigen::SparseMatrix<double>& M);
	/**loads the texture coordinate for the previously fixed vertices
	 * @param tp textured polyhedron
	 * @param U vector which is loaded*/
	void load_U(TexturedPolyhedron& tp, Eigen::SparseMatrix<double>& U);
private:
	/**sets std has_textures to 2 for normal seam and to 3 for branches
	 * sets std map seam to true for the vertices which lie on the virtual cut of the polyhedron
	 * and std map this_type to true for the vertices which texture coordinates are fixed previously
	 * @param tp the textured polyhedron*/
	void set_tags(TexturedPolyhedron& tp);
	/**loads the calculations for a given vertex with all the facets that contain it in a given matrix
	 * @param h the given vertex
	 * @param M matrix which is loaded */
	void load_vertex(Vertex_handle& h, Eigen::SparseMatrix<double>& M);
};

#endif /* PINNEDMATRIXLOADER_H_ */
