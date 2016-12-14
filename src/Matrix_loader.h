/*
 * MatrixLoader.h
 *
 *  Created on: 28 Nov 2016
 *      Author: ninaavr
 */

#ifndef MATRIXLOADER_H_
#define MATRIXLOADER_H_

#include <CGAL/Simple_cartesian.h>
#include <CGAL/Polyhedron_3.h>
#include <stdlib.h>
#include <Eigen/Dense>
#include <Eigen/Sparse>
#include "TexturedPolyhedron/Textured_polyhedron.h"
#include "Matrix_calculator.h"


class Matrix_loader {
protected:
	typedef CGAL::Simple_cartesian<double> K;
	typedef CGAL::Polyhedron_3<K> Polyhedron;
	typedef Textured_polyhedron<K, Textured_items> TexturedPolyhedron;
	typedef TexturedPolyhedron::Facet_iterator Facet_iterator;
	typedef TexturedPolyhedron::Facet_handle Facet_handle;
	typedef TexturedPolyhedron::Vertex_iterator Vertex_iterator;
	typedef TexturedPolyhedron::Halfedge_iterator Halfedge_iterator;
	typedef TexturedPolyhedron::Halfedge_handle Halfedge_handle;
	typedef TexturedPolyhedron::Vertex_handle Vertex_handle;
	typedef TexturedPolyhedron::Halfedge_around_facet_circulator HF_circulator;
	typedef TexturedPolyhedron::Halfedge_around_vertex_circulator HV_circulator;

	typedef std::map<Vertex_handle, std::pair<int, int> > Column;
	typedef std::map<Facet_handle, int> Row;
	typedef std::map<Vertex_handle, bool > Tag;
	typedef std::list<Halfedge_handle> Halfedges;
	typedef std::list<Vertex_handle> Vertices;
protected:
	Matrix_calculator mc;
	Column column;
	Row row;
	Tag seam;
	Tag pinned;
public:
	Matrix_loader();
	virtual ~Matrix_loader();
	virtual void load_M(TexturedPolyhedron& tp, Vertices& pinnedVertices, Eigen::SparseMatrix<double>& M) = 0;
	void set_tags(TexturedPolyhedron& tp, Vertices& pinnedVertices);
	int count_seam_vertices(Vertices& vertices);
	void setColumns_M(Vertices& vertices);
	void load_list_in_M(std::list<Halfedge_handle>& list, Eigen::SparseMatrix<double>& M);
	void load_halfedge_in_M(Halfedge_handle h, Eigen::SparseMatrix<double>& M, const bool secondBorder = false);
	void load_seam_vertices_M(TexturedPolyhedron& tp, Eigen::SparseMatrix<double>& M);
	void load_seam_face(Vertex_handle v, Facet_handle f, const bool first, Eigen::SparseMatrix<double>& M);
private:
	bool is_pinned(const Vertex_handle& v, Vertices& pinned);
	bool is_seam(const Vertex_handle& v);
};

#endif /* MATRIXLOADER_H_ */
