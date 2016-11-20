/*#include<CGAL/Simple_cartesian.h>
#include<CGAL/Polyhedron_incremental_builder_3.h>
#include<CGAL/Polyhedron_3.h>
// A modifier creating a triangle with the incremental builder.
template<class HDS>
class polyhedron_builder: public CGAL::Modifier_base<HDS> {
private:
	typedef CGAL::Simple_cartesian<double> Kernel;
	typedef CGAL::Polyhedron_3<Kernel> Polyhedron;
	typedef Polyhedron::HalfedgeDS HalfedgeDS;
public:
	std::vector<double> &coords;
	std::vector<int> &tris;
	std::vector<double> &textures;
	std::vector<double> &normals;
	polyhedron_builder(std::vector<double> &_coords, std::vector<int> &_tris,
			std::vector<double> &_textures, std::vector<double> &_normals) :
			coords(_coords), tris(_tris), textures(_textures), normals(_normals) {
	}
	void operator()(HDS& hds) {

		// create a cgal incremental builder
		CGAL::Polyhedron_incremental_builder_3<HDS> B(hds, true);
		B.begin_surface(coords.size() / 3, tris.size() / 3);

		// add the polyhedron vertices
		//typedef typename HDS::Vertex Vertex;
		//typedef typename Vertex::Point Point;
		for (int i = 0; i < (int) coords.size(); i += 3) {
			B.add_vertex(
					(Kernel::Point_3(coords[i + 0], coords[i + 1],
							coords[i + 2])));
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
		//Vertex v(Kernel::Point_3(0,0,0), Kernel::Point_2(0,0), Kernel::Point_3(0,0,0));
		//Vertex v = Vertex(Kernel::Point_3(0,0,0), Kernel::Point_2(0,0), Kernel::Point_3(0,0,0));
	}
};*/
