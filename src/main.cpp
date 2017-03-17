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
		hi3 = hi;
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
		hi4 = hi;

		while (hi->opposite()->vertex()->id() != 3471)
			hi = hi->next_on_vertex();
		hi = hi->opposite();
		bord.push_back(hi);
		hi3 = hi;

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

		//his left leg
		while (hi2->opposite()->vertex()->id() != 839)
		 hi2 = hi2->next_on_vertex();
		 hi2 = hi2->opposite();
		 bord.push_back(hi2);

		 while (hi2->opposite()->vertex()->id() != 871)
		 hi2 = hi2->next_on_vertex();
		 hi2 = hi2->opposite();
		 bord.push_back(hi2);

		 while (hi2->opposite()->vertex()->id() != 900)
		 hi2 = hi2->next_on_vertex();
		 hi2 = hi2->opposite();
		 bord.push_back(hi2);

		 while (hi2->opposite()->vertex()->id() != 899)
		 hi2 = hi2->next_on_vertex();
		 hi2 = hi2->opposite();
		 bord.push_back(hi2);

		 while (hi2->opposite()->vertex()->id() != 1458)
		 hi2 = hi2->next_on_vertex();
		 hi2 = hi2->opposite();
		 bord.push_back(hi2);

		 while (hi2->opposite()->vertex()->id() != 968)
		 hi2 = hi2->next_on_vertex();
		 hi2 = hi2->opposite();
		 bord.push_back(hi2);

		 while (hi2->opposite()->vertex()->id() != 993)
		 hi2 = hi2->next_on_vertex();
		 hi2 = hi2->opposite();
		 bord.push_back(hi2);

		 while (hi2->opposite()->vertex()->id() != 994)
		 hi2 = hi2->next_on_vertex();
		 hi2 = hi2->opposite();
		 bord.push_back(hi2);

		 while (hi2->opposite()->vertex()->id() != 1026)
		 hi2 = hi2->next_on_vertex();
		 hi2 = hi2->opposite();
		 bord.push_back(hi2);

		 while (hi2->opposite()->vertex()->id() != 1040)
		 hi2 = hi2->next_on_vertex();
		 hi2 = hi2->opposite();
		 bord.push_back(hi2);

		 while (hi2->opposite()->vertex()->id() != 997)
		 hi2 = hi2->next_on_vertex();
		 hi2 = hi2->opposite();
		 bord.push_back(hi2);

		 while (hi2->opposite()->vertex()->id() != 998)
		 hi2 = hi2->next_on_vertex();
		 hi2 = hi2->opposite();
		 bord.push_back(hi2);

		 while (hi2->opposite()->vertex()->id() != 1062)
		 hi2 = hi2->next_on_vertex();
		 hi2 = hi2->opposite();
		 bord.push_back(hi2);

		 while (hi2->opposite()->vertex()->id() != 1063)
		 hi2 = hi2->next_on_vertex();
		 hi2 = hi2->opposite();
		 bord.push_back(hi2);

		 while (hi2->opposite()->vertex()->id() != 1080)
		 hi2 = hi2->next_on_vertex();
		 hi2 = hi2->opposite();
		 bord.push_back(hi2);

		 while (hi2->opposite()->vertex()->id() != 1090)
		 hi2 = hi2->next_on_vertex();
		 hi2 = hi2->opposite();
		 bord.push_back(hi2);

		 while (hi2->opposite()->vertex()->id() != 1091)
		 hi2 = hi2->next_on_vertex();
		 hi2 = hi2->opposite();
		 bord.push_back(hi2);

		 while (hi2->opposite()->vertex()->id() != 1108)
		 hi2 = hi2->next_on_vertex();
		 hi2 = hi2->opposite();
		 bord.push_back(hi2);

		 while (hi2->opposite()->vertex()->id() != 1109)
		 hi2 = hi2->next_on_vertex();
		 hi2 = hi2->opposite();
		 bord.push_back(hi2);

		 while (hi2->opposite()->vertex()->id() != 1126)
		 hi2 = hi2->next_on_vertex();
		 hi2 = hi2->opposite();
		 bord.push_back(hi2);

		 while (hi2->opposite()->vertex()->id() != 1127)
		 hi2 = hi2->next_on_vertex();
		 hi2 = hi2->opposite();
		 bord.push_back(hi2);

		 while (hi2->opposite()->vertex()->id() != 3178)
		 hi2 = hi2->next_on_vertex();
		 hi2 = hi2->opposite();
		 bord.push_back(hi2);

		 while (hi2->opposite()->vertex()->id() != 3194)
		 hi2 = hi2->next_on_vertex();
		 hi2 = hi2->opposite();
		 bord.push_back(hi2);

		 while (hi2->opposite()->vertex()->id() != 3200)
		 hi2 = hi2->next_on_vertex();
		 hi2 = hi2->opposite();
		 bord.push_back(hi2);

		 while (hi2->opposite()->vertex()->id() != 3435)
		 hi2 = hi2->next_on_vertex();
		 hi2 = hi2->opposite();
		 bord.push_back(hi2);

		 while (hi2->opposite()->vertex()->id() != 3393)
		 hi2 = hi2->next_on_vertex();
		 hi2 = hi2->opposite();
		 bord.push_back(hi2);

		 while (hi2->opposite()->vertex()->id() != 3388)
		 hi2 = hi2->next_on_vertex();
		 hi2 = hi2->opposite();
		 bord.push_back(hi2);

		 while (hi2->opposite()->vertex()->id() != 3389)
		 hi2 = hi2->next_on_vertex();
		 hi2 = hi2->opposite();
		 bord.push_back(hi2);

		//his left hand
		while (hi3->opposite()->vertex()->id() != 1216)
			 hi3 = hi3->next_on_vertex();
			 hi3 = hi3->opposite();
			 bord.push_back(hi3);

			 while (hi3->opposite()->vertex()->id() != 1215)
			 hi3 = hi3->next_on_vertex();
			 hi3 = hi3->opposite();
			 bord.push_back(hi3);

			 while (hi3->opposite()->vertex()->id() != 732)
			 hi3 = hi3->next_on_vertex();
			 hi3 = hi3->opposite();
			 bord.push_back(hi3);

			 while (hi3->opposite()->vertex()->id() != 730)
			 hi3 = hi3->next_on_vertex();
			 hi3 = hi3->opposite();
			 bord.push_back(hi3);

			 while (hi3->opposite()->vertex()->id() != 1813)
			 hi3 = hi3->next_on_vertex();
			 hi3 = hi3->opposite();
			 bord.push_back(hi3);

			 while (hi3->opposite()->vertex()->id() != 1812)
			 hi3 = hi3->next_on_vertex();
			 hi3 = hi3->opposite();
			 bord.push_back(hi3);

			 while (hi3->opposite()->vertex()->id() != 1243)
			 hi3 = hi3->next_on_vertex();
			 hi3 = hi3->opposite();
			 bord.push_back(hi3);

			 while (hi3->opposite()->vertex()->id() != 1242)
			 hi3 = hi3->next_on_vertex();
			 hi3 = hi3->opposite();
			 bord.push_back(hi3);

			 while (hi3->opposite()->vertex()->id() != 1833)
			 hi3 = hi3->next_on_vertex();
			 hi3 = hi3->opposite();
			 bord.push_back(hi3);

			 while (hi3->opposite()->vertex()->id() != 1886)
			 hi3 = hi3->next_on_vertex();
			 hi3 = hi3->opposite();
			 bord.push_back(hi3);

			 while (hi3->opposite()->vertex()->id() != 1887)
			 hi3 = hi3->next_on_vertex();
			 hi3 = hi3->opposite();
			 bord.push_back(hi3);

			 while (hi3->opposite()->vertex()->id() != 1857)
			 hi3 = hi3->next_on_vertex();
			 hi3 = hi3->opposite();
			 bord.push_back(hi3);

			 while (hi3->opposite()->vertex()->id() != 1855)
			 hi3 = hi3->next_on_vertex();
			 hi3 = hi3->opposite();
			 bord.push_back(hi3);

			 while (hi3->opposite()->vertex()->id() != 1889)
			 hi3 = hi3->next_on_vertex();
			 hi3 = hi3->opposite();
			 bord.push_back(hi3);

			 while (hi3->opposite()->vertex()->id() != 1358)
			 hi3 = hi3->next_on_vertex();
			 hi3 = hi3->opposite();
			 bord.push_back(hi3);

			 while (hi3->opposite()->vertex()->id() != 1355)
			 hi3 = hi3->next_on_vertex();
			 hi3 = hi3->opposite();
			 bord.push_back(hi3);

			 while (hi3->opposite()->vertex()->id() != 2985)
			 hi3 = hi3->next_on_vertex();
			 hi3 = hi3->opposite();
			 bord.push_back(hi3);

			 while (hi3->opposite()->vertex()->id() != 2984)
			 hi3 = hi3->next_on_vertex();
			 hi3 = hi3->opposite();
			 bord.push_back(hi3);

			 while (hi3->opposite()->vertex()->id() != 2896)
			 hi3 = hi3->next_on_vertex();
			 hi3 = hi3->opposite();
			 bord.push_back(hi3);

			 while (hi3->opposite()->vertex()->id() != 2897)
			 hi3 = hi3->next_on_vertex();
			 hi3 = hi3->opposite();
			 bord.push_back(hi3);

			 while (hi3->opposite()->vertex()->id() != 1542)
			 hi3 = hi3->next_on_vertex();
			 hi3 = hi3->opposite();
			 bord.push_back(hi3);

			 while (hi3->opposite()->vertex()->id() != 1378)
			 hi3 = hi3->next_on_vertex();
			 hi3 = hi3->opposite();
			 bord.push_back(hi3);

			 while (hi3->opposite()->vertex()->id() != 1377)
			 hi3 = hi3->next_on_vertex();
			 hi3 = hi3->opposite();
			 bord.push_back(hi3);

			 while (hi3->opposite()->vertex()->id() != 1710)
			 hi3 = hi3->next_on_vertex();
			 hi3 = hi3->opposite();
			 bord.push_back(hi3);

			 while (hi3->opposite()->vertex()->id() != 1711)
			 hi3 = hi3->next_on_vertex();
			 hi3 = hi3->opposite();
			 bord.push_back(hi3);

			 while (hi3->opposite()->vertex()->id() != 1713)
			 hi3 = hi3->next_on_vertex();
			 hi3 = hi3->opposite();
			 bord.push_back(hi3);

			 while (hi3->opposite()->vertex()->id() != 1619)
			 hi3 = hi3->next_on_vertex();
			 hi3 = hi3->opposite();
			 bord.push_back(hi3);

			 while (hi3->opposite()->vertex()->id() != 1620)
			 hi3 = hi3->next_on_vertex();
			 hi3 = hi3->opposite();
			 bord.push_back(hi3);

			 while (hi3->opposite()->vertex()->id() != 1738)
			 hi3 = hi3->next_on_vertex();
			 hi3 = hi3->opposite();
			 bord.push_back(hi3);

			 while (hi3->opposite()->vertex()->id() != 1701)
			 hi3 = hi3->next_on_vertex();
			 hi3 = hi3->opposite();
			 bord.push_back(hi3);

			 while (hi3->opposite()->vertex()->id() != 1911)
			 hi3 = hi3->next_on_vertex();
			 hi3 = hi3->opposite();
			 bord.push_back(hi3);

			 while (hi3->opposite()->vertex()->id() != 1730)
			 hi3 = hi3->next_on_vertex();
			 hi3 = hi3->opposite();
			 bord.push_back(hi3);

			 while (hi3->opposite()->vertex()->id() != 1600)
			 hi3 = hi3->next_on_vertex();
			 hi3 = hi3->opposite();
			 bord.push_back(hi3);

			 while (hi3->opposite()->vertex()->id() != 1599)
			 hi3 = hi3->next_on_vertex();
			 hi3 = hi3->opposite();
			 bord.push_back(hi3);

			 while (hi3->opposite()->vertex()->id() != 1590)
			 hi3 = hi3->next_on_vertex();
			 hi3 = hi3->opposite();
			 bord.push_back(hi3);

			 while (hi3->opposite()->vertex()->id() != 1980)
			 hi3 = hi3->next_on_vertex();
			 hi3 = hi3->opposite();
			 bord.push_back(hi3);

			 while (hi3->opposite()->vertex()->id() != 1968)
			 hi3 = hi3->next_on_vertex();
			 hi3 = hi3->opposite();
			 bord.push_back(hi3);

			 while (hi3->opposite()->vertex()->id() != 1967)
			 hi3 = hi3->next_on_vertex();
			 hi3 = hi3->opposite();
			 bord.push_back(hi3);

			 while (hi3->opposite()->vertex()->id() != 1940)
			 hi3 = hi3->next_on_vertex();
			 hi3 = hi3->opposite();
			 bord.push_back(hi3);

			 while (hi3->opposite()->vertex()->id() != 1943)
			 hi3 = hi3->next_on_vertex();
			 hi3 = hi3->opposite();
			 bord.push_back(hi3);

			 while (hi3->opposite()->vertex()->id() != 2106)
			 hi3 = hi3->next_on_vertex();
			 hi3 = hi3->opposite();
			 bord.push_back(hi3);

			 while (hi3->opposite()->vertex()->id() != 2060)
			 hi3 = hi3->next_on_vertex();
			 hi3 = hi3->opposite();
			 bord.push_back(hi3);

			 while (hi3->opposite()->vertex()->id() != 2033)
			 hi3 = hi3->next_on_vertex();
			 hi3 = hi3->opposite();
			 bord.push_back(hi3);

			 while (hi3->opposite()->vertex()->id() != 2034)
			 hi3 = hi3->next_on_vertex();
			 hi3 = hi3->opposite();
			 bord.push_back(hi3);

			 while (hi3->opposite()->vertex()->id() != 2035)
			 hi3 = hi3->next_on_vertex();
			 hi3 = hi3->opposite();
			 bord.push_back(hi3);

			 while (hi3->opposite()->vertex()->id() != 2256)
			 hi3 = hi3->next_on_vertex();
			 hi3 = hi3->opposite();
			 bord.push_back(hi3);

			 while (hi3->opposite()->vertex()->id() != 2144)
			 hi3 = hi3->next_on_vertex();
			 hi3 = hi3->opposite();
			 bord.push_back(hi3);

			 while (hi3->opposite()->vertex()->id() != 2064)
			 hi3 = hi3->next_on_vertex();
			 hi3 = hi3->opposite();
			 bord.push_back(hi3);

			 while (hi3->opposite()->vertex()->id() != 2063)
			 hi3 = hi3->next_on_vertex();
			 hi3 = hi3->opposite();
			 bord.push_back(hi3);

			 while (hi3->opposite()->vertex()->id() != 2194)
			 hi3 = hi3->next_on_vertex();
			 hi3 = hi3->opposite();
			 bord.push_back(hi3);

			 while (hi3->opposite()->vertex()->id() != 2612)
			 hi3 = hi3->next_on_vertex();
			 hi3 = hi3->opposite();
			 bord.push_back(hi3);

			 while (hi3->opposite()->vertex()->id() != 2613)
			 hi3 = hi3->next_on_vertex();
			 hi3 = hi3->opposite();
			 bord.push_back(hi3);

		//his right hand
		while (hi4->opposite()->vertex()->id() != 4700)
			hi4 = hi4->next_on_vertex();
		 	hi4 = hi4->opposite();
		 	bord.push_back(hi4);

		while (hi4->opposite()->vertex()->id() != 4698)
		 hi4 = hi4->next_on_vertex();
		 hi4 = hi4->opposite();
		 bord.push_back(hi4);

		 while (hi4->opposite()->vertex()->id() != 6343)
		 hi4 = hi4->next_on_vertex();
		 hi4 = hi4->opposite();
		 bord.push_back(hi4);

		 while (hi4->opposite()->vertex()->id() != 4221)
		 hi4 = hi4->next_on_vertex();
		 hi4 = hi4->opposite();
		 bord.push_back(hi4);

		 while (hi4->opposite()->vertex()->id() != 6428)
		 hi4 = hi4->next_on_vertex();
		 hi4 = hi4->opposite();
		 bord.push_back(hi4);

		 while (hi4->opposite()->vertex()->id() != 4222)
		 hi4 = hi4->next_on_vertex();
		 hi4 = hi4->opposite();
		 bord.push_back(hi4);

		 while (hi4->opposite()->vertex()->id() != 4195)
		 hi4 = hi4->next_on_vertex();
		 hi4 = hi4->opposite();
		 bord.push_back(hi4);

		 while (hi4->opposite()->vertex()->id() != 6408)
		 hi4 = hi4->next_on_vertex();
		 hi4 = hi4->opposite();
		 bord.push_back(hi4);

		 while (hi4->opposite()->vertex()->id() != 6407)
		 hi4 = hi4->next_on_vertex();
		 hi4 = hi4->opposite();
		 bord.push_back(hi4);

		 while (hi4->opposite()->vertex()->id() != 6464)
		 hi4 = hi4->next_on_vertex();
		 hi4 = hi4->opposite();
		 bord.push_back(hi4);

		 while (hi4->opposite()->vertex()->id() != 6463)
		 hi4 = hi4->next_on_vertex();
		 hi4 = hi4->opposite();
		 bord.push_back(hi4);

		 while (hi4->opposite()->vertex()->id() != 6462)
		 hi4 = hi4->next_on_vertex();
		 hi4 = hi4->opposite();
		 bord.push_back(hi4);

		 while (hi4->opposite()->vertex()->id() != 6406)
		 hi4 = hi4->next_on_vertex();
		 hi4 = hi4->opposite();
		 bord.push_back(hi4);

		 while (hi4->opposite()->vertex()->id() != 6405)
		 hi4 = hi4->next_on_vertex();
		 hi4 = hi4->opposite();
		 bord.push_back(hi4);

		 while (hi4->opposite()->vertex()->id() != 5350)
		 hi4 = hi4->next_on_vertex();
		 hi4 = hi4->opposite();
		 bord.push_back(hi4);

		 while (hi4->opposite()->vertex()->id() != 4832)
		 hi4 = hi4->next_on_vertex();
		 hi4 = hi4->opposite();
		 bord.push_back(hi4);

		 while (hi4->opposite()->vertex()->id() != 4833)
		 hi4 = hi4->next_on_vertex();
		 hi4 = hi4->opposite();
		 bord.push_back(hi4);

		 while (hi4->opposite()->vertex()->id() != 6442)
		 hi4 = hi4->next_on_vertex();
		 hi4 = hi4->opposite();
		 bord.push_back(hi4);

		 while (hi4->opposite()->vertex()->id() != 6441)
		 hi4 = hi4->next_on_vertex();
		 hi4 = hi4->opposite();
		 bord.push_back(hi4);

		 while (hi4->opposite()->vertex()->id() != 6356)
		 hi4 = hi4->next_on_vertex();
		 hi4 = hi4->opposite();
		 bord.push_back(hi4);

		 while (hi4->opposite()->vertex()->id() != 5011)
		 hi4 = hi4->next_on_vertex();
		 hi4 = hi4->opposite();
		 bord.push_back(hi4);

		 while (hi4->opposite()->vertex()->id() != 4851)
		 hi4 = hi4->next_on_vertex();
		 hi4 = hi4->opposite();
		 bord.push_back(hi4);

		 while (hi4->opposite()->vertex()->id() != 4852)
		 hi4 = hi4->next_on_vertex();
		 hi4 = hi4->opposite();
		 bord.push_back(hi4);

		 while (hi4->opposite()->vertex()->id() != 5181)
		 hi4 = hi4->next_on_vertex();
		 hi4 = hi4->opposite();
		 bord.push_back(hi4);

		 while (hi4->opposite()->vertex()->id() != 5180)
		 hi4 = hi4->next_on_vertex();
		 hi4 = hi4->opposite();
		 bord.push_back(hi4);

		 while (hi4->opposite()->vertex()->id() != 5182)
		 hi4 = hi4->next_on_vertex();
		 hi4 = hi4->opposite();
		 bord.push_back(hi4);

		 while (hi4->opposite()->vertex()->id() != 5088)
		 hi4 = hi4->next_on_vertex();
		 hi4 = hi4->opposite();
		 bord.push_back(hi4);

		 while (hi4->opposite()->vertex()->id() != 5091)
		 hi4 = hi4->next_on_vertex();
		 hi4 = hi4->opposite();
		 bord.push_back(hi4);

		 while (hi4->opposite()->vertex()->id() != 5207)
		 hi4 = hi4->next_on_vertex();
		 hi4 = hi4->opposite();
		 bord.push_back(hi4);

		 while (hi4->opposite()->vertex()->id() != 5221)
		 hi4 = hi4->next_on_vertex();
		 hi4 = hi4->opposite();
		 bord.push_back(hi4);

		 while (hi4->opposite()->vertex()->id() != 5046)
		 hi4 = hi4->next_on_vertex();
		 hi4 = hi4->opposite();
		 bord.push_back(hi4);

		 while (hi4->opposite()->vertex()->id() != 5373)
		 hi4 = hi4->next_on_vertex();
		 hi4 = hi4->opposite();
		 bord.push_back(hi4);

		 while (hi4->opposite()->vertex()->id() != 5070)
		 hi4 = hi4->next_on_vertex();
		 hi4 = hi4->opposite();
		 bord.push_back(hi4);

		 while (hi4->opposite()->vertex()->id() != 5069)
		 hi4 = hi4->next_on_vertex();
		 hi4 = hi4->opposite();
		 bord.push_back(hi4);

		 while (hi4->opposite()->vertex()->id() != 5060)
		 hi4 = hi4->next_on_vertex();
		 hi4 = hi4->opposite();
		 bord.push_back(hi4);

		 while (hi4->opposite()->vertex()->id() != 5058)
		 hi4 = hi4->next_on_vertex();
		 hi4 = hi4->opposite();
		 bord.push_back(hi4);

		 while (hi4->opposite()->vertex()->id() != 5426)
		 hi4 = hi4->next_on_vertex();
		 hi4 = hi4->opposite();
		 bord.push_back(hi4);

		 while (hi4->opposite()->vertex()->id() != 5422)
		 hi4 = hi4->next_on_vertex();
		 hi4 = hi4->opposite();
		 bord.push_back(hi4);

		 while (hi4->opposite()->vertex()->id() != 5423)
		 hi4 = hi4->next_on_vertex();
		 hi4 = hi4->opposite();
		 bord.push_back(hi4);

		 while (hi4->opposite()->vertex()->id() != 5405)
		 hi4 = hi4->next_on_vertex();
		 hi4 = hi4->opposite();
		 bord.push_back(hi4);

		 while (hi4->opposite()->vertex()->id() != 5668)
		 hi4 = hi4->next_on_vertex();
		 hi4 = hi4->opposite();
		 bord.push_back(hi4);

		 while (hi4->opposite()->vertex()->id() != 5667)
		 hi4 = hi4->next_on_vertex();
		 hi4 = hi4->opposite();
		 bord.push_back(hi4);

		 while (hi4->opposite()->vertex()->id() != 5664)
		 hi4 = hi4->next_on_vertex();
		 hi4 = hi4->opposite();
		 bord.push_back(hi4);

		 while (hi4->opposite()->vertex()->id() != 5658)
		 hi4 = hi4->next_on_vertex();
		 hi4 = hi4->opposite();
		 bord.push_back(hi4);

		 while (hi4->opposite()->vertex()->id() != 5657)
		 hi4 = hi4->next_on_vertex();
		 hi4 = hi4->opposite();
		 bord.push_back(hi4);

		 while (hi4->opposite()->vertex()->id() != 5631)
		 hi4 = hi4->next_on_vertex();
		 hi4 = hi4->opposite();
		 bord.push_back(hi4);

		 while (hi4->opposite()->vertex()->id() != 5465)
		 hi4 = hi4->next_on_vertex();
		 hi4 = hi4->opposite();
		 bord.push_back(hi4);

		 while (hi4->opposite()->vertex()->id() != 5462)
		 hi4 = hi4->next_on_vertex();
		 hi4 = hi4->opposite();
		 bord.push_back(hi4);

		 while (hi4->opposite()->vertex()->id() != 5636)
		 hi4 = hi4->next_on_vertex();
		 hi4 = hi4->opposite();
		 bord.push_back(hi4);

		 while (hi4->opposite()->vertex()->id() != 5752)
		 hi4 = hi4->next_on_vertex();
		 hi4 = hi4->opposite();
		 bord.push_back(hi4);

		 while (hi4->opposite()->vertex()->id() != 5753)
		 hi4 = hi4->next_on_vertex();
		 hi4 = hi4->opposite();
		 bord.push_back(hi4);

		 while (hi4->opposite()->vertex()->id() != 5971)
		 hi4 = hi4->next_on_vertex();
		 hi4 = hi4->opposite();
		 bord.push_back(hi4);

		 while (hi4->opposite()->vertex()->id() != 5960)
		 hi4 = hi4->next_on_vertex();
		 hi4 = hi4->opposite();
		 bord.push_back(hi4);

		 while (hi4->opposite()->vertex()->id() != 5939)
		 hi4 = hi4->next_on_vertex();
		 hi4 = hi4->opposite();
		 bord.push_back(hi4);

		 while (hi4->opposite()->vertex()->id() != 5938)
		 hi4 = hi4->next_on_vertex();
		 hi4 = hi4->opposite();
		 bord.push_back(hi4);

		 while (hi4->opposite()->vertex()->id() != 5978)
		 hi4 = hi4->next_on_vertex();
		 hi4 = hi4->opposite();
		 bord.push_back(hi4);

		 while (hi4->opposite()->vertex()->id() != 5980)
		 hi4 = hi4->next_on_vertex();
		 hi4 = hi4->opposite();
		 bord.push_back(hi4);




	hi = tp.halfedges_begin();
	while (hi->vertex()->id() != 385)//385 412
		++hi;
	hi->vertex()->u()[0] = 0.2;
	hi->vertex()->v()[0] = 0.2;
	while (hi->vertex()->id() != 385 )//385 6802
		++hi;
	hi->vertex()->u()[1] = 0.2;
	hi->vertex()->v()[1] = 0.8;

	tp.set_seam(bord);
	cout<<tp.seam->size()<<endl;


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
