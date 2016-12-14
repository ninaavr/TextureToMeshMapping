/*
 * Textured_halfedge.h
 *
 *  Created on: 1 Dec 2016
 *      Author: ninaavr
 */

#ifndef TEXTURED_HALFEDGE_H_
#define TEXTURED_HALFEDGE_H_

//Textured_halfedge is used in Textured_items, used in TexturedPolyhedron
template<class Refs, class Tprev, class Tvertex, class Tface, class Norm>
class Textured_halfedge: public CGAL::HalfedgeDS_halfedge_base<Refs, Tprev,
		Tvertex, Tface> {
	bool m_seam;
public:
	// life cycle
	Textured_halfedge() {
		m_seam = false;
	}
	/**returns true if edge lies where the object is virtually cut*/
	const bool& is_seam() {
		return m_seam;
	}
	/**sets tag if edge lies on the virtual cut, needs to be set also for opposite halfedge
	 * @param b bool value to set the tag*/
	void set_seam(bool b) {
		m_seam = b;
	}
};

#endif /* TEXTURED_HALFEDGE_H_ */
