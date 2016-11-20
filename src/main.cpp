#include <iostream>
#include <CGAL/Simple_cartesian.h>
#include<CGAL/Polyhedron_incremental_builder_3.h>
#include<CGAL/Polyhedron_3.h>
#include<CGAL/IO/Polyhedron_iostream.h>
#include "Textured_polyhedron.h"
#include "Textured_polyhedron_builder.h"
//#include "Polyhedron_builder.h"
#include "IO/Reader.h"
#include "IO/Writer.h"
#include <CGAL/Parameterization_polyhedron_adaptor_3.h>
#include <CGAL/parameterize.h>
#include <CGAL/LSCM_parameterizer_3.h>

#include <CGAL/Timer.h>
#include <CGAL/parameterize.h>
#include <CGAL/Parameterization_mesh_patch_3.h>
#include <CGAL/Circular_border_parameterizer_3.h>
#include <CGAL/Square_border_parameterizer_3.h>
#include <CGAL/Two_vertices_parameterizer_3.h>
#include <CGAL/Barycentric_mapping_parameterizer_3.h>
#include <CGAL/Discrete_conformal_map_parameterizer_3.h>
#include <CGAL/Discrete_authalic_parameterizer_3.h>
#include <CGAL/Mean_value_coordinates_parameterizer_3.h>
#include <CGAL/LSCM_parameterizer_3.h>
#include <CGAL/Parameterization_mesh_feature_extractor.h>
#include <CGAL/OpenNL/linear_solver.h>

using namespace std;
typedef CGAL::Simple_cartesian<double> K;
typedef CGAL::Polyhedron_3<K> Polyhedron;
typedef Textured_polyhedron<K, Textured_items> TexturedPolyhedron;
int main() {
	std::vector<double> coords;
	std::vector<int> tris;
	std::vector<double> textures;
	std::vector<double> normals;

	//loads data from obj file to vectors
	Reader r;
	r.load_obj("centaur2.obj", coords, tris, textures, normals);

	Textured_polyhedron<K, Textured_items> tp;
	//loads vectors in Polyhedron
	Polyhedron_builder<Polyhedron::HalfedgeDS> pb(coords, tris, textures,
			normals);

	Textured_polyhedron_builder<Polyhedron,
			Textured_polyhedron<K, Textured_items>, K> tpbuilder;
	Polyhedron mesh;
	mesh.delegate(pb);

	/*Polyhedron::Vertex_const_iterator pVertex;
	for (pVertex = mesh.vertices_begin(); pVertex != mesh.vertices_end();
			pVertex++) {
		// (u,v) pair is stored in any halfedge
		double u = mesh_adaptor.info(pVertex->halfedge())->uv().x();
		double v = mesh_adaptor.info(pVertex->halfedge())->uv().y();
		std::cout << "(u,v) = (" << u << "," << v << ")" << std::endl;
	}*/

	/*tpbuilder.run(mesh, tp);

	 tp.set_vertex_properties(normals, textures);
	 Writer w;
	 w.write_obj("test.obj", tp);*/

	cout << "!!!Hello World!!!" << endl; // prints !!!Hello World!!!
	return 0;
}
;
