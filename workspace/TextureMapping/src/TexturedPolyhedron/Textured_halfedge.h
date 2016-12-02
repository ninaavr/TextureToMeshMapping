/*
 * Textured_halfedge.h
 *
 *  Created on: 1 Dec 2016
 *      Author: osboxes
 */

#ifndef TEXTURED_HALFEDGE_H_
#define TEXTURED_HALFEDGE_H_

//Textured_halfedge is used in Textured_items, used in TexturedPolyhedron
template<class Refs, class Tprev, class Tvertex, class Tface, class Norm>
class Textured_halfedge: public CGAL::HalfedgeDS_halfedge_base<Refs, Tprev,
		Tvertex, Tface> {
public:
	// life cycle
	Textured_halfedge() {
	}
};




#endif /* TEXTURED_HALFEDGE_H_ */
