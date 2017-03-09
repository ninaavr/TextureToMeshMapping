/*

 * Textured_vertex.h
 *
 *  Created on: 1 Dec 2016
 *      Author: ninaavr
 */

#ifndef TEXTURED_VERTEX_H_
#define TEXTURED_VERTEX_H_

//Textured_vertex is used in Textured_items, used in TexturedPolyhedron
//it has storage for IDs, normals, texture coordinates and tags for pinned and border vertices
template<class Refs, class T, class P, class Norm>
class Textured_vertex: public CGAL::HalfedgeDS_vertex_base<Refs, T, P> {
	// normal
	Norm m_normal;
	double m_u;
	double m_v;
	double m_u2;
	double m_v2;
	int m_id;
public:
	// life cycle
	Textured_vertex() {
		m_u = -1;
		m_v = -1;
		m_u2 = -1;
		m_v2 = -1;

	}

	// repeat mandatory constructors
	Textured_vertex(const P& pt) :
			CGAL::HalfedgeDS_vertex_base<Refs, T, P>(pt) {
		m_u = -1;
		m_v = -1;
		m_u2 = -1;
		m_v2 = -1;
	}

	//normal
	typedef Norm Normal_3;

	/**sets normal*/
	Normal_3& normal() {
		return m_normal;
	}
	/**gets normal*/
	const Normal_3& normal() const {
		return m_normal;
	}
	/**sets (horizontal) coordinate pixel of texture corresponding to this vertex*/
	double& u() {
		return m_u;
	}
	/**gets (horizontal) coordinate pixel of texture corresponding to this vertex*/
	const double& u() const {
		return m_u;
	}
	/**sets (vertical) coordinate pixel of texture corresponding to this vertex*/
	double& v() {
		return m_v;
	}
	/**gets (vertical) coordinate pixel of texture corresponding to this vertex*/
	const double& v() const {
		return m_v;
	}
	double& u2() {
		return m_u2;
	}
	const double& u2() const {
		return m_u2;
	}
	double& v2() {
		return m_v2;
	}
	const double& v2() const {
		return m_v2;
	}
	/**gets or sets ID of the vertex*/
	int& id() {
		return m_id;
	}
};

#endif /* TEXTURED_VERTEX_H_ */
