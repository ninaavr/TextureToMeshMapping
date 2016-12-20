#include <iostream>
#include <CGAL/Parameterization_polyhedron_adaptor_3.h>
#include <CGAL/parameterize.h>
#include <CGAL/LSCM_parameterizer_3.h>



#include "TexturedPolyhedron/Textured_polyhedron.h"
#include "PolyhedronBuilder/Textured_polyhedron_builder.h"
#include "PolyhedronBuilder/Polyhedron_builder.h"
#include "IO/Reader.h"
#include "IO/Writer.h"
#include "Free_matrix_loader.h"
#include "Pinned_matrix_loader.h"
#include "CPPUnitTests/SeamPinnedTestSuite.h"
#include "CPPUnitTests/CalculationsTestSuite.h"
#include "CPPUnitTests/LoadingTestSuite.h"
#include "CPPUnitTests/Runner.h"

using namespace std;
typedef CGAL::Simple_cartesian<double> K;
typedef CGAL::Polyhedron_3<K> Polyhedron;
typedef Textured_polyhedron<K, Textured_items> TexturedPolyhedron;
typedef TexturedPolyhedron::HalfedgeDS HalfedgeDS;
typedef Textured_Polyhedron_builder<HalfedgeDS, Polyhedron, TexturedPolyhedron, K> Textured_builder;

int main() {
	std::vector<double> coords;
	std::vector<int> tris;

	//loads data from .obj file to vectors
	Reader r;
	r("human.obj", coords, tris);

	//builds textured polyhedron builder and from it also textured polyhedron
	Textured_builder tb(coords, tris);
	TexturedPolyhedron tp;
	tp.delegate(tb);
	//sets vertices IDs
	tp.set_ids();

	//run(TestSeamAndPinn::suite());
	run(CalculationsTest::suite());
	run(LoadingTest::suite());

	std::list<TexturedPolyhedron::Halfedge_iterator> bord;
	TexturedPolyhedron::Halfedge_iterator hi = tp.halfedges_begin();
	bord.push_back(hi);

	std::list<TexturedPolyhedron::Vertex_handle> pv;

	hi = hi->next_on_vertex()->opposite();
	pv.push_back(hi->vertex());
	bord.push_back(hi);
	hi = hi->next_on_vertex()->opposite();

	bord.push_back(hi);
	hi = hi->next_on_vertex()->opposite();
	bord.push_back(hi);

	tp.set_seam(bord);
	tp.compute_normals_per_facet();

	Eigen::SparseMatrix<double> Mf;
	Free_matrix_loader fml;
	fml.load_M(tp,pv, Mf);

	Eigen::SparseMatrix<double> Mp;
	Eigen::SparseMatrix<double> U;
	Pinned_matrix_loader pml;
	pml.load_M(tp, pv, Mp);
	pml.load_U(pv, U);
	//writes textured polyhedron in  an .obj file
	Writer w;
	w("test.obj", tp);
	cout << "!!!Hello World!!!" << endl; // prints !!!Hello World!!!
	return 0;
};
