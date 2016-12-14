/*
 * Polyhedron_builder.h
 *
 *  Created on: 1 Dec 2016
 *      Author: ninaavr
 */
#ifndef _TEXTURED_POLYHEDRON_BUILDER_
#define _TEXTURED_POLYHEDRON_BUILDER_

#include<CGAL/Simple_cartesian.h>
#include<CGAL/Polyhedron_incremental_builder_3.h>
#include<CGAL/Polyhedron_3.h>

//makes builder for TexturedPolyhedron
template<class HDS, class Polyhedron, class Textured_polyhedron, class Kernel>
class Textured_Polyhedron_builder: public CGAL::Modifier_base<HDS> {
private:
	typedef CGAL::Simple_cartesian<double> K;
private:
	std::vector<double> &coords;
	std::vector<int> &tris;

public:
	/**sets coordinates of vertices and IDs of corresponding vertices of the faces
	 * @param coords 3D coordinates of vertices
	 * @param tris stores IDs of the vertices for each facet, packed [F0a,F0b,F0c,F1a,F1b,F1c,...]*/
	Textured_Polyhedron_builder(std::vector<double> &_coords, std::vector<int> &_tris) :
			coords(_coords), tris(_tris) {
	}
	/**builds Textured_Polyhedron_builder from vertices in coords and faces in tris
	 * with it we can make textured polyhedron*/
	void operator()(HDS& hds) {
		// create a cgal incremental builder
		CGAL::Polyhedron_incremental_builder_3<HDS> B(hds, true);

		B.begin_surface(coords.size() / 3, tris.size() / 3);
		//add polyhedron vertices
		for (int i = 0; i < (int) coords.size(); i += 3) {
			B.add_vertex((K::Point_3(coords[i + 0], coords[i + 1], coords[i + 2])));
		}
		// add the polyhedron triangles
		for (int i = 0; i < (int) tris.size(); i += 3) {
			B.begin_facet();
			B.add_vertex_to_facet(tris[i + 0]);
			B.add_vertex_to_facet(tris[i + 1]);
			B.add_vertex_to_facet(tris[i + 2]);
			B.end_facet();
		}
		// finish up the surface
		B.end_surface();
	}
};

#endif // _TEXTURED_POLYHEDRON_BUILDER_
