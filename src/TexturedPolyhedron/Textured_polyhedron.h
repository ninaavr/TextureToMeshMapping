//============================================================================
// Name        : Textured_polyhedron.cpp
// Author      : ninaavr
// Version     :
// Copyright   : Your copyright notice
// Description :
//============================================================================

#ifndef _TEXTURED_MESH_
#define _TEXTURED_MESH_

#include <CGAL/Cartesian.h>
#include <CGAL/Polyhedron_3.h>
#include <CGAL/HalfedgeDS_default.h>
#include <stdlib.h>
#include "Textured_items.h"

using namespace std;

//inherits Polyhedron_3 and has additionally the properties of Textured_vertex,
//Textured_halfedge and Textured_facet
template<class Kernel, class Items>
class Textured_polyhedron: public CGAL::Polyhedron_3<Kernel, Items> {
public:
	typedef typename Kernel::FT FT;
	typedef typename Kernel::Point_3 Point;
	typedef typename Kernel::Vector_3 Vector;
	typedef typename CGAL::Polyhedron_3<Kernel, Items> Base;
	typedef typename CGAL::Polyhedron_3<Kernel, CGAL::Polyhedron_items_3> Basic_polyhedron;

	typedef typename Base::Vertex_handle Vertex_handle;
	typedef typename Base::Vertex_iterator Vertex_iterator;
	typedef typename Base::Halfedge_handle Halfedge_handle;
	typedef typename Base::Halfedge_iterator Halfedge_iterator;
	typedef typename Base::Halfedge_around_facet_circulator Halfedge_around_facet_circulator;
	typedef typename Base::Halfedge_around_vertex_circulator Halfedge_around_vertex_circulator;
	typedef typename Base::Edge_iterator Edge_iterator;
	typedef typename Base::Facet Facet;
	typedef typename Base::Facet_iterator Facet_iterator;
	typedef typename Base::Facet_handle Facet_handle;
	// set to true after they are calculated
	bool texturesExist;
	bool normalsExist;

	int sizePinnedVertices;
	int sizeBorderVertices;
	std::list<Halfedge_iterator> border;
public:
	// initialises with default values
	Textured_polyhedron() {
		texturesExist = false;
		normalsExist = false;
		sizePinnedVertices = 0;
		sizeBorderVertices = 0;
		Vertex_iterator vi;
	}

	virtual ~Textured_polyhedron() {
	}

	/** computes normals per facet, uses structure from "Textured_facet.h*/
	void compute_normals_per_facet() {
		std::for_each(this->facets_begin(), this->facets_end(), Facet_normal());
	}

	/**sets vertex IDs only after they are added*/
	void set_vertex_ids() {
		Vertex_iterator vi;
		int index = 0;
		for (vi = this->vertices_begin(); vi != this->vertices_end(); ++vi) {
			vi->id() = index;
			++index;
		}
	}

	/**sets which vertices are manually set to texture coordinates
	 * @param list list of the vertices that have pinned texture coordinates*/
	void set_pinned_vertices(std::list<Vertex_iterator> &list) {
		typename std::list<Vertex_iterator>::iterator vi;
		for (vi = list.begin(); vi != list.end(); ++vi) {
			(*vi)->m_pinned = true;
			++sizePinnedVertices;
		}
	}

	/**sets tag of all vertices to be not pinned*/
	void reset_pinned_vertices() {
		Vertex_iterator vi;
		for (vi = this->vertices_begin(); vi != this->vertices_end(); ++vi)
			vi->set_pinned(false);
		sizePinnedVertices = 0;
	}

	/**returns the number of pinned to texture vertices
	 * @return number of pinned vertices*/
	int size_of_pinned_vertices() {
		return sizePinnedVertices;
	}

	/**sets tag of vertices that lie on the border given by a list of halfedges
	 * and stores the list in the property border
	 * @param l list of halfedges that describe the border*/
	void set_border(std::list<Halfedge_iterator>& l) {
		border = l;
		typename std::list<Halfedge_iterator>::iterator it;
		for (it = l.begin(); it != l.end(); ++it) {
			(*it)->vertex()->set_border(true);
			++sizeBorderVertices;
		}
	}

	/**clears the border list border from the textured polyhedron and
	 * resets the tags for border of all vertices*/
	void reset_border() {
		Halfedge_iterator it;
		for (it = this->border->begin(); it != this->border->end(); ++it)
			it->vertex()->set_border(false);
		this->border->clear();
		sizeBorderVertices = 0;
	}

	/**returns the number of border vertices
	 * @return number of border vertices*/
	int size_of_border_vertices() {
		return sizeBorderVertices;
	}

};
// end class Textured_polyhedron

#endif // _TEXTURED_MESH_

