/*
 * Matrixcalculator.h
 *
 *  Created on: 4 Dec 2016
 *      Author: ninaavr
 */

#ifndef MATRIXCALCULATOR_H_
#define MATRIXCALCULATOR_H_
#include <CGAL/Simple_cartesian.h>
#include <CGAL/Polyhedron_3.h>
#include <CGAL/aff_transformation_tags.h>
#include <CGAL/Aff_transformation_3.h>
#include <stdlib.h>
#include "TexturedPolyhedron/Textured_polyhedron.h"

class Matrix_calculator {
	typedef CGAL::Simple_cartesian<double> K;
	typedef Textured_polyhedron<K, Textured_items> TexturedPolyhedron;
	typedef TexturedPolyhedron::Facet_iterator Facet_iterator;
	typedef TexturedPolyhedron::Vertex_handle Vertex_handle;
	typedef TexturedPolyhedron::Halfedge_around_facet_circulator HF_circulator;
public:
	Matrix_calculator();
	virtual ~Matrix_calculator();
	double calc_W(const Facet_iterator f, const Vertex_handle& v, const bool firstText);
	void calc_W(K::Point_2* p, bool firstText, double* W);
	double calc_dt(K::Point_2* p);
	void project_triangle(Facet_iterator f, K::Point_2* p);
	void normalise(K::Vector_3& v);
	double calc_area(TexturedPolyhedron::Face_handle& f);
	void calculate_triangle_gradient(Facet_iterator f, double* W);

};

#endif /* MATRIXCALCULATOR_H_ */
