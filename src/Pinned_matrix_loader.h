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
	typedef TexturedPolyhedron::Halfedge_around_facet_circulator HV_circulator;
public:
	Pinned_matrix_loader();
	virtual ~Pinned_matrix_loader();
	virtual void load_M(TexturedPolyhedron& tp, Halfedges& pinnedVertices, Eigen::SparseMatrix<double>& M);
	void load_vertex_in_M(Halfedge_handle h, Eigen::SparseMatrix<double>& M);
};

#endif /* PINNEDMATRIXLOADER_H_ */
