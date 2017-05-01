/*
 * Textured_items.h
 *
 *  Created on: 1 Dec 2016
 *      Author: ninaavr
 */

#ifndef TEXTURED_ITEMS_H_
#define TEXTURED_ITEMS_H_

#include "Textured_facet.h"
#include "Textured_halfedge.h"
#include "Textured_vertex.h"

//consists of three types of items: vertex, halfedge and face
//inherits properties of items of Polyhedron_3
//also uses properties of Textured_facet, Textured_vertex and Textured_halfedge
//is used in Textured_polyhedron

struct Textured_items: public CGAL::Polyhedron_items_3 {
	// wrap vertex
	template<class Refs, class Traits> struct Vertex_wrapper {
		typedef typename Traits::Point_3 Point;
		typedef typename Traits::Vector_3 Normal;
		typedef Textured_vertex<Refs, CGAL::Tag_true, Point, Normal> Vertex;
	};

	// wrap face
	template<class Refs, class Traits> struct Face_wrapper {
		typedef typename Traits::Point_3 Point;
		typedef typename Traits::Vector_3 Normal;
		typedef Textured_facet<Refs, CGAL::Tag_true, Point, Normal> Face;
	};

	// wrap halfedge
	template<class Refs, class Traits> struct Halfedge_wrapper {
		typedef typename Traits::Vector_3 Normal;
		typedef Textured_halfedge<Refs, CGAL::Tag_true, CGAL::Tag_true,
				CGAL::Tag_true, Normal> Halfedge;
	};
};



#endif /* TEXTURED_ITEMS_H_ */
