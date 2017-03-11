/*
 * Textured_facet.h
 *
 *  Created on: 1 Dec 2016
 *      Author: ninaavr
 */
#ifndef _TEXTURED_FACET_H
#define _TEXTURED_FACET_H

//Textured_facet is used in Textured_items, used in TexturedPolyhedron
//it has storage for normals and their computation
template<class Refs, class T, class P, class Norm>
class Textured_facet: public CGAL::HalfedgeDS_face_base<Refs, T> {
	// normal
	Norm m_normal;
	//id for debugging purposes
	int m_id;
	int m_side;
public:

	// life cycle
	// no constructors to repeat, since only
	// default constructor mandatory

	Textured_facet() {
		m_side = -1;
	}

	typedef Norm Normal_3;
	/**sets normal*/
	Normal_3& normal() {
		return m_normal;
	}
	/**gets normal*/
	const Normal_3& normal() const {
		return m_normal;
	}
	/**gets or sets ID of the facet*/
	int& id() {
		return m_id;
	}
	int& is_side(){
		return m_side;
	}
};

// compute facet normal
struct Facet_normal // (functor)
{
	template<class Facet> void operator()(Facet& f) {
		typename Facet::Normal_3 sum = CGAL::NULL_VECTOR;
		typename Facet::Halfedge_around_facet_circulator h = f.facet_begin();
		do {
			typename Facet::Normal_3 normal = CGAL::cross_product(
					h->next()->vertex()->point() - h->vertex()->point(),
					h->next()->next()->vertex()->point()
							- h->next()->vertex()->point());
			double sqnorm = normal * normal;
			if (sqnorm != 0)
				normal = normal / (float) std::sqrt(sqnorm);
			sum = sum + normal;
		} while (++h != f.facet_begin());
		float sqnorm = sum * sum;
		if (sqnorm != 0.0)
			f.normal() = sum / std::sqrt(sqnorm);
		else
			f.normal() = CGAL::NULL_VECTOR;
	}
};

/*struct Plane_equation {
	template <class Facet>
	typename Facet::Plane_3 operator()(Facet& f) {
		typename Facet::Halfedge_handle h = f.halfedge();
		typedef typename Facet::Plane_3 Plane;
		return Plane(h->vertex()->point(), h->next()->vertex()->point(),
				h->next()->next()->vertex()->point());
	}
};*/
#endif
