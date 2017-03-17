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
	int sizeSeamHalfedges;
	int sizeBranch;
	std::list<Halfedge_handle>* seam;
public:
	// initialises with default values
	Textured_polyhedron() {
		texturesExist = false;
		normalsExist = false;
		sizeSeamHalfedges = 0;
		sizeBranch = 0;
		seam = NULL;
	}

	virtual ~Textured_polyhedron() {
	}

	/** computes normals per facet, uses structure from "Textured_facet.h*/
	void compute_normals_per_facet() {
		std::for_each(this->facets_begin(), this->facets_end(), Facet_normal());
	}

	/**sets vertex and face IDs after they are added
	 * used for debugging purposes*/
	void set_ids() {
		Vertex_iterator vi;
		int index = 0;
		for (vi = this->vertices_begin(); vi != this->vertices_end(); ++vi) {
			vi->id() = index;
			++index;
		}
		index = 0;
		Facet_iterator fi;
		for (fi = this->facets_begin(); fi != this->facets_end(); ++fi){
			fi->id() = index;
			++index;
		}
	}

	/**sets tag of halfedges that lie on the seam given by a list
	 * and stores the list in the property seam
	 * @param l list of halfedges that describe the seam*/
	void set_seam(std::list<Halfedge_handle>& l) {
		seam = &l;
		Halfedge_handle prev = *l.begin();
		typename std::list<Halfedge_handle>::iterator it;
		for (it = l.begin(); it != l.end(); ++it) {
			//remove duplicated edges
			if(prev == (*it)->opposite()){
				cout << "edge must be given by 1 halfedge!!" << endl;
				std::exit(-1);
			}
			if(prev->vertex() != (*it)->opposite()->vertex() && it!=l.begin()){
				++sizeBranch;
			}
			//seam has to be a path
			/*if(prev->vertex() != (*it)->opposite()->vertex() && it!=l.begin()){
				cout << "invalid seam!!" << endl;
				std::exit(-1);
			}*/
			(*it)->set_seam(true);
			(*it)->opposite()->set_seam(true);
			prev = *it;
			++sizeSeamHalfedges;
		}
	}

	/**clears the seam list seam from the textured polyhedron and
	 * resets the tags for seam of all halfedges*/
	void reset_seam() {
		typename std::list<Halfedge_handle>::iterator it;
		for (it = this->seam->begin(); it != this->seam->end(); ++it)
			(*it)->vertex()->set_seam(false);
		this->seam->clear();
		sizeSeamHalfedges = 0;
	}

	/**returns the number of seam halfedges
	 * @return number of seam halfedges*/
	int size_of_seam_halfedges() {
		return sizeSeamHalfedges;
	}
	int size_of_branch_vertices(){
		return sizeBranch;
	}

};
// end class Textured_polyhedron

#endif // _TEXTURED_MESH_

