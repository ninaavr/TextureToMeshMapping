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
#include "Matrix_solver.h"
//#include "CPPUnitTests/SeamPinnedTestSuite.h"
//#include "CPPUnitTests/CalculationsTestSuite.h"
//#include "CPPUnitTests/LoadingTestSuite.h"
//#include "CPPUnitTests/Runner.h"

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


	/*std::list<TexturedPolyhedron::Halfedge_iterator> bord;
	TexturedPolyhedron::Halfedge_iterator hi = tp.halfedges_begin();
	while(hi->vertex()->id()!=0 || hi->opposite()->vertex()->id()!=6)
	++hi;
	bord.push_back(hi);
	cout << hi->vertex()->id() << endl;
	while(hi->opposite()->vertex()->id()!=1)
	hi = hi -> next_on_vertex();
	hi = hi->opposite();
	bord.push_back(hi);
	cout << hi->vertex()->id() << endl;
	while(hi->opposite()->vertex()->id()!=3)
	hi = hi -> next_on_vertex();
	hi = hi->opposite();
	bord.push_back(hi);
	cout << hi->vertex()->id() << endl;*/



	//run(TestSeamAndPinn::suite());
	//run(CalculationsTest::suite());
	//run(LoadingTest::suite());

	std::list<TexturedPolyhedron::Halfedge_iterator> bord;
	TexturedPolyhedron::Halfedge_iterator hi, hi2, hi3, hi4;
	hi = tp.halfedges_begin();
	while (hi->vertex()->id() != 413)
		++hi;
	bord.push_back(hi);

	while (hi->opposite()->vertex()->id() != 385)
		hi = hi->next_on_vertex();
	hi = hi->opposite();
	bord.push_back(hi);

	while (hi->opposite()->vertex()->id() != 384)
		hi = hi->next_on_vertex();
	hi = hi->opposite();
	bord.push_back(hi);

	while (hi->opposite()->vertex()->id() != 457)
		hi = hi->next_on_vertex();
	hi = hi->opposite();
	bord.push_back(hi);

	while (hi->opposite()->vertex()->id() != 446)
		hi = hi->next_on_vertex();
	hi = hi->opposite();
	bord.push_back(hi);

	while (hi->opposite()->vertex()->id() != 445)
		hi = hi->next_on_vertex();
	hi = hi->opposite();
	bord.push_back(hi);

	while (hi->opposite()->vertex()->id() != 463)
		hi = hi->next_on_vertex();
	hi = hi->opposite();
	bord.push_back(hi);

	while (hi->opposite()->vertex()->id() != 303)
		hi = hi->next_on_vertex();
	hi = hi->opposite();
	bord.push_back(hi);

	while (hi->opposite()->vertex()->id() != 302)
		hi = hi->next_on_vertex();
	hi = hi->opposite();
	bord.push_back(hi);

	while (hi->opposite()->vertex()->id() != 460)
		hi = hi->next_on_vertex();
	hi = hi->opposite();
	bord.push_back(hi);

	while (hi->opposite()->vertex()->id() != 3164)
		hi = hi->next_on_vertex();
	hi = hi->opposite();
	bord.push_back(hi);

	while (hi->opposite()->vertex()->id() != 829)
		hi = hi->next_on_vertex();
	hi = hi->opposite();
	bord.push_back(hi);

	while (hi->opposite()->vertex()->id() != 828)
		hi = hi->next_on_vertex();
	hi = hi->opposite();
	bord.push_back(hi);

	while (hi->opposite()->vertex()->id() != 3470)
		hi = hi->next_on_vertex();
	hi = hi->opposite();
	bord.push_back(hi);

	while (hi->opposite()->vertex()->id() != 3012)
		hi = hi->next_on_vertex();
	hi = hi->opposite();
	bord.push_back(hi);

	while (hi->opposite()->vertex()->id() != 1306)
		hi = hi->next_on_vertex();
	hi = hi->opposite();
	bord.push_back(hi);

	while (hi->opposite()->vertex()->id() != 1305)
		hi = hi->next_on_vertex();
	hi = hi->opposite();
	bord.push_back(hi);

	while (hi->opposite()->vertex()->id() != 2878)
		hi = hi->next_on_vertex();
	hi = hi->opposite();
	bord.push_back(hi);

	while (hi->opposite()->vertex()->id() != 2877)
		hi = hi->next_on_vertex();
	hi = hi->opposite();
	bord.push_back(hi);

	while (hi->opposite()->vertex()->id() != 3471)
		hi = hi->next_on_vertex();
	hi = hi->opposite();
	bord.push_back(hi);
	hi3 = hi;
	hi4 = hi;

	//below hands
	while (hi->opposite()->vertex()->id() != 1755)
		hi = hi->next_on_vertex();
	hi = hi->opposite();
	bord.push_back(hi);

	while (hi->opposite()->vertex()->id() != 1754)
		hi = hi->next_on_vertex();
	hi = hi->opposite();
	bord.push_back(hi);

	while (hi->opposite()->vertex()->id() != 3482)
		hi = hi->next_on_vertex();
	hi = hi->opposite();
	bord.push_back(hi);

	while (hi->opposite()->vertex()->id() != 3029)
		hi = hi->next_on_vertex();
	hi = hi->opposite();
	bord.push_back(hi);

	while (hi->opposite()->vertex()->id() != 3028)
		hi = hi->next_on_vertex();
	hi = hi->opposite();
	bord.push_back(hi);

	while (hi->opposite()->vertex()->id() != 3027)
		hi = hi->next_on_vertex();
	hi = hi->opposite();
	bord.push_back(hi);

	while (hi->opposite()->vertex()->id() != 3508)
		hi = hi->next_on_vertex();
	hi = hi->opposite();
	bord.push_back(hi);

	while (hi->opposite()->vertex()->id() != 3015)
		hi = hi->next_on_vertex();
	hi = hi->opposite();
	bord.push_back(hi);

	while (hi->opposite()->vertex()->id() != 3014)
		hi = hi->next_on_vertex();
	hi = hi->opposite();
	bord.push_back(hi);

	while (hi->opposite()->vertex()->id() != 3505)
		hi = hi->next_on_vertex();
	hi = hi->opposite();
	bord.push_back(hi);

	while (hi->opposite()->vertex()->id() != 3017)
		hi = hi->next_on_vertex();
	hi = hi->opposite();
	bord.push_back(hi);

	while (hi->opposite()->vertex()->id() != 3016)
		hi = hi->next_on_vertex();
	hi = hi->opposite();
	bord.push_back(hi);

	while (hi->opposite()->vertex()->id() != 3173)
		hi = hi->next_on_vertex();
	hi = hi->opposite();
	bord.push_back(hi);

	while (hi->opposite()->vertex()->id() != 3024)
		hi = hi->next_on_vertex();
	hi = hi->opposite();
	bord.push_back(hi);

	while (hi->opposite()->vertex()->id() != 3023)
		hi = hi->next_on_vertex();
	hi = hi->opposite();
	bord.push_back(hi);

	while (hi->opposite()->vertex()->id() != 3502)
		hi = hi->next_on_vertex();
	hi = hi->opposite();
	bord.push_back(hi);

	while (hi->opposite()->vertex()->id() != 3022)
		hi = hi->next_on_vertex();
	hi = hi->opposite();
	bord.push_back(hi);

	while (hi->opposite()->vertex()->id() != 3021)
		hi = hi->next_on_vertex();
	hi = hi->opposite();
	bord.push_back(hi);

	while (hi->opposite()->vertex()->id() != 1784)
		hi = hi->next_on_vertex();
	hi = hi->opposite();
	bord.push_back(hi);

	while (hi->opposite()->vertex()->id() != 1783)
		hi = hi->next_on_vertex();
	hi = hi->opposite();
	bord.push_back(hi);

	while (hi->opposite()->vertex()->id() != 3159)
		hi = hi->next_on_vertex();
	hi = hi->opposite();
	bord.push_back(hi);

	while (hi->opposite()->vertex()->id() != 3158)
		hi = hi->next_on_vertex();
	hi = hi->opposite();
	bord.push_back(hi);

	while (hi->opposite()->vertex()->id() != 3484)
		hi = hi->next_on_vertex();
	hi = hi->opposite();
	bord.push_back(hi);

	while (hi->opposite()->vertex()->id() != 3120)
		hi = hi->next_on_vertex();
	hi = hi->opposite();
	bord.push_back(hi);

	while (hi->opposite()->vertex()->id() != 3119)
		hi = hi->next_on_vertex();
	hi = hi->opposite();
	bord.push_back(hi);

	while (hi->opposite()->vertex()->id() != 3141)
		hi = hi->next_on_vertex();
	hi = hi->opposite();
	bord.push_back(hi);

	while (hi->opposite()->vertex()->id() != 3481)
		hi = hi->next_on_vertex();
	hi = hi->opposite();
	bord.push_back(hi);

	while (hi->opposite()->vertex()->id() != 3102)
		hi = hi->next_on_vertex();
	hi = hi->opposite();
	bord.push_back(hi);

	while (hi->opposite()->vertex()->id() != 1540)
		hi = hi->next_on_vertex();
	hi = hi->opposite();
	bord.push_back(hi);
	hi2 = hi;

	//his right leg
	while (hi->opposite()->vertex()->id() != 1539)
		hi = hi->next_on_vertex();
	hi = hi->opposite();
	bord.push_back(hi);

	while (hi->opposite()->vertex()->id() != 4356)
		hi = hi->next_on_vertex();
	hi = hi->opposite();
	bord.push_back(hi);

	while (hi->opposite()->vertex()->id() != 4836)
		hi = hi->next_on_vertex();
	hi = hi->opposite();
	bord.push_back(hi);

	while (hi->opposite()->vertex()->id() != 4419)
		hi = hi->next_on_vertex();
	hi = hi->opposite();
	bord.push_back(hi);

	while (hi->opposite()->vertex()->id() != 4422)
		hi = hi->next_on_vertex();
	hi = hi->opposite();
	bord.push_back(hi);

	while (hi->opposite()->vertex()->id() != 4454)
		hi = hi->next_on_vertex();
	hi = hi->opposite();
	bord.push_back(hi);

	while (hi->opposite()->vertex()->id() != 4451)
		hi = hi->next_on_vertex();
	hi = hi->opposite();
	bord.push_back(hi);

	while (hi->opposite()->vertex()->id() != 4480)
		hi = hi->next_on_vertex();
	hi = hi->opposite();
	bord.push_back(hi);

	while (hi->opposite()->vertex()->id() != 4477)
		hi = hi->next_on_vertex();
	hi = hi->opposite();
	bord.push_back(hi);

	while (hi->opposite()->vertex()->id() != 4990)
		hi = hi->next_on_vertex();
	hi = hi->opposite();
	bord.push_back(hi);

	while (hi->opposite()->vertex()->id() != 4991)
		hi = hi->next_on_vertex();
	hi = hi->opposite();
	bord.push_back(hi);

	while (hi->opposite()->vertex()->id() != 4992)
		hi = hi->next_on_vertex();
	hi = hi->opposite();
	bord.push_back(hi);

	while (hi->opposite()->vertex()->id() != 4993)
		hi = hi->next_on_vertex();
	hi = hi->opposite();
	bord.push_back(hi);

	while (hi->opposite()->vertex()->id() != 4994)
		hi = hi->next_on_vertex();
	hi = hi->opposite();
	bord.push_back(hi);

	while (hi->opposite()->vertex()->id() != 4995)
		hi = hi->next_on_vertex();
	hi = hi->opposite();
	bord.push_back(hi);

	while (hi->opposite()->vertex()->id() != 4998)
		hi = hi->next_on_vertex();
	hi = hi->opposite();
	bord.push_back(hi);

	while (hi->opposite()->vertex()->id() != 4997)
		hi = hi->next_on_vertex();
	hi = hi->opposite();
	bord.push_back(hi);

	while (hi->opposite()->vertex()->id() != 4999)
		hi = hi->next_on_vertex();
	hi = hi->opposite();
	bord.push_back(hi);

	while (hi->opposite()->vertex()->id() != 5000)
		hi = hi->next_on_vertex();
	hi = hi->opposite();
	bord.push_back(hi);

	while (hi->opposite()->vertex()->id() != 5001)
		hi = hi->next_on_vertex();
	hi = hi->opposite();
	bord.push_back(hi);

	while (hi->opposite()->vertex()->id() != 5002)
		hi = hi->next_on_vertex();
	hi = hi->opposite();
	bord.push_back(hi);

	while (hi->opposite()->vertex()->id() != 5003)
		hi = hi->next_on_vertex();
	hi = hi->opposite();
	bord.push_back(hi);

	while (hi->opposite()->vertex()->id() != 6596)
		hi = hi->next_on_vertex();
	hi = hi->opposite();
	bord.push_back(hi);

	while (hi->opposite()->vertex()->id() != 6597)
		hi = hi->next_on_vertex();
	hi = hi->opposite();
	bord.push_back(hi);

	while (hi->opposite()->vertex()->id() != 6610)
		hi = hi->next_on_vertex();
	hi = hi->opposite();
	bord.push_back(hi);

	while (hi->opposite()->vertex()->id() != 6834)
		hi = hi->next_on_vertex();
	hi = hi->opposite();
	bord.push_back(hi);

	while (hi->opposite()->vertex()->id() != 6816)
		hi = hi->next_on_vertex();
	hi = hi->opposite();
	bord.push_back(hi);

	while (hi->opposite()->vertex()->id() != 6813)
		hi = hi->next_on_vertex();
	hi = hi->opposite();
	bord.push_back(hi);

	while (hi->opposite()->vertex()->id() != 6814)
		hi = hi->next_on_vertex();
	hi = hi->opposite();
	bord.push_back(hi);


	hi = tp.halfedges_begin();
	while (hi->vertex()->id() != 385)
		++hi;
	hi->vertex()->u() = 0.1;
	hi->vertex()->v() = 0.1;
	hi->vertex()->u2() = 0.1;
	hi->vertex()->v2() = 0.9;

	tp.set_seam(bord);
	tp.compute_normals_per_facet();

	Eigen::SparseMatrix<double> Mf;
	Free_matrix_loader fml;
	fml.load_M(tp, Mf);

	Eigen::SparseMatrix<double> Mp;
	Eigen::SparseMatrix<double> U;
	Pinned_matrix_loader pml;
	pml.load_M(tp, Mp);
	pml.load_U(tp, U);
	Matrix_solver ms;
	Eigen::VectorXd x;
	ms.solve_system(Mf, Mp, U, x);
	fml.store_result(x, tp);
	//writes textured polyhedron in  an .obj file
	Writer w;
	w("test.obj", tp);
	cout << "!!!Hello World!!!" << endl; // prints !!!Hello World!!!
	return 0;
};
