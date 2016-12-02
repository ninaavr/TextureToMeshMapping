/*
 * MatrixLoader.h
 *
 *  Created on: 28 Nov 2016
 *      Author: osboxes
 */

#ifndef MATRIXLOADER_H_
#define MATRIXLOADER_H_

#include <CGAL/Simple_cartesian.h>
#include <CGAL/Polyhedron_3.h>
#include <stdlib.h>
#include <Eigen/Dense>
#include <Eigen/Sparse>
#include "TexturedPolyhedron/Textured_polyhedron.h"


class MatrixLoader {
private:
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

	typedef std::map<Vertex_handle, int> Column;
	typedef std::map<Vertex_handle, std::pair<int, int> > Column_border;
	typedef std::map<Facet_handle, int> Row;
public:
	MatrixLoader();
	virtual ~MatrixLoader();
	void load_M(TexturedPolyhedron& tp, Eigen::SparseMatrix<double>& M);
	double calc_W(Facet_iterator f, Vertex_handle& v, bool firstText);
	void calc_W(K::Point_2* p, bool firstText, double* W);
	//orders first the normal vertices, then the border vertices, then the pinned vertices
	//duplicates the border vertices
	void setColumns_M(TexturedPolyhedron& tp, Column& column, Column_border& column_border);
	double calc_dt(K::Point_2* p);
	void project_triangle(Facet_iterator f, K::Point_2* p);
	void calculate_triangle_gradient(Facet_iterator f, double* W, double& dt);
};

#endif /* MATRIXLOADER_H_ */
