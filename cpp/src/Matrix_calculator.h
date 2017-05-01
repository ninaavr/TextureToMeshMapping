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
	typedef TexturedPolyhedron::Facet_handle Facet_handle;
	typedef TexturedPolyhedron::Halfedge_around_facet_circulator HF_circulator;
public:
	Matrix_calculator();
	virtual ~Matrix_calculator();
	/**calculates area of a given triangle
	 * @param f the triangle
	 * @result the area of the triangle*/
	double calc_area(Facet_handle& f);
	/**calculates the values for a vertex and a facet, used in Matrix_loader
	 * calculation for each vertex is the 2D difference of the other two vertices in the triangle
	 * @param f the triangle
	 * @param v is the given vertex
	 * @param W is pointer to array of length 2 which contains the differences in
	 * x and in y coordinates*/
	void calc_W(Facet_handle& f, Vertex_handle& v, double* W);
	/**calculates the values for a facet and its vertices, used in Matrix_loader
	 * calculation for each vertex is the 2D difference of the other two vertices in the triangle
	 * @param f is the triangle
	 * @param W is pointer to array of length 6 which contains the differences in x and in y
	 * coordinates for each vertex, packed in the form diffx1, diffx2, diffx3, diffy1, diffy2, diffy3*/
	void calc_W(Facet_handle& f, double* W);
private:
	/**projects a given triangle with 3D coordinates on its plane
	 * @param f facet that describes the triangle
	 * @param p array where the 2D coordinates of the 3 vertices are stored*/
	void project_triangle(Facet_handle f, K::Point_2* p);
	/**normalises a given vector
	 * @param v the vector to be normalised*/
	void normalise(K::Vector_3& v);
	/**calculates the centre of a triangle
	 * @param f facet that describes the triangle
	 * @param centre vector where the centre is stored*/
	void calc_centre(Facet_handle& f, K::Vector_3& centre);
};

#endif /* MATRIXCALCULATOR_H_ */
