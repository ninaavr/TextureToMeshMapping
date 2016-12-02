#include <iostream>
#include <CGAL/Parameterization_polyhedron_adaptor_3.h>
#include <CGAL/parameterize.h>
#include <CGAL/LSCM_parameterizer_3.h>

#include "TexturedPolyhedron/Textured_polyhedron.h"
#include "PolyhedronBuilder/Textured_polyhedron_builder.h"
#include "PolyhedronBuilder/Polyhedron_builder.h"
#include "IO/Reader.h"
#include "IO/Writer.h"
#include "MatrixLoader.h"

using namespace std;
typedef CGAL::Simple_cartesian<double> K;
typedef CGAL::Polyhedron_3<K> Polyhedron;
typedef Textured_polyhedron<K, Textured_items> TexturedPolyhedron;
typedef TexturedPolyhedron::HalfedgeDS HalfedgeDS;
typedef Textured_Polyhedron_builder<HalfedgeDS, Polyhedron, TexturedPolyhedron, K> Textured_builder;

int main() {
	std::vector<double> coords;
	std::vector<int> tris;

	//loads data from obj file to vectors
	Reader r;
	r.load_obj ("centaur2.obj", coords, tris);

	//builds textured polyhedron builder and from it also textured polyhedron
	Textured_builder tb(coords, tris);
	TexturedPolyhedron tp;
	tp.delegate(tb);
	//sets vertices IDs
	tp.set_vertex_ids();

	//std::list<TexturedPolyhedron::Halfedge_iterator> bord;
	//TexturedPolyhedron::Halfedge_iterator hi = tp.halfedges_begin();
	//bord.push_back(hi);
	//tp.set_border(bord);
	//MatrixLoader ml;
	//Eigen::SparseMatrix<double> M;
	//ml.load_M(tp, M);

	Writer w;
	w.write_obj("test.obj", tp);

	cout << "!!!Hello World!!!" << endl; // prints !!!Hello World!!!
	return 0;
};
