#ifndef _TEXTURED_POLYHEDRON_BUILDER_
#define _TEXTURED_POLYHEDRON_BUILDER_

#include<CGAL/Simple_cartesian.h>
#include<CGAL/Polyhedron_incremental_builder_3.h>
#include<CGAL/Polyhedron_3.h>

template<class Vertex_handle>
struct Vertex_cmp {
	bool operator()(Vertex_handle a, Vertex_handle b) const {
		return &*a < &*b;
	}
};

template<class HDS, class Polyhedron, class Textured_polyhedron, class Kernel>
class Modifier_textured_polyhedron: public CGAL::Modifier_base<HDS> {
private:
	typedef typename Kernel::Point_3 Point;
	typedef typename HDS::Vertex Vertex;
	typedef typename HDS::Face_handle Face_handle;
	typedef typename HDS::Halfedge_handle Halfedge_handle;

	typedef typename Polyhedron::Vertex_handle Vertex_handle;
	typedef typename Polyhedron::Facet_iterator Facet_iterator;
	typedef typename Polyhedron::Vertex_iterator Vertex_iterator;
	typedef typename Polyhedron::Halfedge_around_facet_circulator HF_circulator;

	typedef typename CGAL::Polyhedron_incremental_builder_3<HDS> builder;
	Polyhedron *m_pMesh;
	std::map<Vertex_handle, int, Vertex_cmp<Vertex_handle> > m_vertex_map;

public:

	// life cycle
	Modifier_textured_polyhedron(Polyhedron *pMesh) {
		CGAL_assertion(pMesh != NULL);
		m_pMesh = pMesh;
	}
	~Modifier_textured_polyhedron() {
	}

	void operator()(HDS& hds) {
		builder B(hds, true);
		B.begin_surface(3, 1, 6);
		add_vertices(B);
		add_facets(B);
		B.end_surface();
	}

	// add vertices
	void add_vertices(builder &B) {
		int index = 0;
		typename Polyhedron::Vertex_iterator it;
		for (it = m_pMesh->vertices_begin(); it != m_pMesh->vertices_end();
				it++) {
			typename Polyhedron::Vertex_handle v = it;
			m_vertex_map[v] = index++;
			B.add_vertex(v->point());
		}
	}

	// add facets
	void add_facets(builder &B) {
		typename Polyhedron::Facet_iterator it;
		for (it = m_pMesh->facets_begin(); it != m_pMesh->facets_end(); it++) {
			B.begin_facet();
			HF_circulator he = it->facet_begin();
			HF_circulator end = he;
			CGAL_For_all(he,end)
				B.add_vertex_to_facet(m_vertex_map[he->vertex()]);
			B.end_facet();
		}
	}

};

template<class Polyhedron, class Textured_polyhedron, class Kernel>
class Textured_polyhedron_builder {
public:
	typedef typename Textured_polyhedron::HalfedgeDS HalfedgeDS;
	Textured_polyhedron_builder() {
	}
	~Textured_polyhedron_builder() {
	}

public:
	void run(Polyhedron &input, Textured_polyhedron &output) {
		Modifier_textured_polyhedron<HalfedgeDS, Polyhedron,
				Textured_polyhedron, Kernel> copier(&input);
		output.delegate(copier);
	}
};

template<class HDS>
class Polyhedron_builder: public CGAL::Modifier_base<HDS> {
private:
	typedef CGAL::Simple_cartesian<double> K;
	typedef CGAL::Polyhedron_3<K> Polyhedron;
	//typedef Polyhedron::HalfedgeDS HalfedgeDS;
private:
	std::vector<double> &coords;
	std::vector<int> &tris;
	std::vector<double> &textures;
	std::vector<double> &normals;
public:
	Polyhedron_builder(std::vector<double> &_coords, std::vector<int> &_tris,
			std::vector<double> &_textures, std::vector<double> &_normals) :
			coords(_coords), tris(_tris), textures(_textures), normals(_normals) {
	}
	void operator()(HDS& hds) {
		//tris can also hold the ids for texture and normal
		bool textureExists = !textures.empty();
		bool normalExists = !normals.empty();
		// create a cgal incremental builder
		CGAL::Polyhedron_incremental_builder_3<HDS> B(hds, true);
		B.begin_surface(coords.size() / 3, tris.size() / 3);
		//store normals and textures in the same sequence as vertices
		double* tmp_normals;
		int nlength = normals.size();
		tmp_normals = new double[nlength];
		double* tmp_textures;
		int tlength = textures.size();
		tmp_textures = new double[tlength];

		for (int i = 0; i < (int) coords.size(); i += 3) {
			B.add_vertex(
					(K::Point_3(coords[i + 0], coords[i + 1], coords[i + 2])));
		}
		// add the polyhedron triangles
		if (textureExists && normalExists) {
			for (int i = 0; i < (int) tris.size(); i += 9) {
				B.begin_facet();
				for (int j = i; j < i + 9; j += 3) {
					B.add_vertex_to_facet(tris[j]);
					addTextureID(tmp_textures, tris[j], tris[j + 1]);
					addNormalID(tmp_normals, tris[j], tris[j + 2]);
				}
				B.end_facet();
			}
		}
		else if (textureExists)
			for (int i = 0; i < (int) tris.size(); i += 6) {
				B.begin_facet();
				for (int j = i; j < i + 6; j += 2) {
					B.add_vertex_to_facet(tris[j]);
					addTextureID(tmp_textures, tris[j], tris[j + 1]);
				}
				B.end_facet();
			}
		else if (normalExists)
			for (int i = 0; i < (int) tris.size(); i += 6) {
				B.begin_facet();
				for (int j = i; j < i + 6; j += 2) {
					B.add_vertex_to_facet(tris[j]);
					addNormalID(tmp_normals, tris[j], tris[j + 1]);
				}
				B.end_facet();
			}
		else {
			for (int i = 0; i < (int) tris.size(); i += 3) {
				B.begin_facet();
				B.add_vertex_to_facet(tris[i + 0]);
				B.add_vertex_to_facet(tris[i + 1]);
				B.add_vertex_to_facet(tris[i + 2]);
				B.end_facet();
			}
		}
		// finish up the surface
		B.end_surface();
		textures.clear();
		normals.clear();
		for (int i = 0; i < nlength; ++i) {
			normals.push_back(tmp_normals[i]);
		}
		for (int i = 0; i < tlength; ++i) {
			textures.push_back(tmp_textures[i]);
		}
	}
	void addTextureID(double* tmp_textures, int src_id, int dst_id) {
		tmp_textures[src_id * 2] = textures[dst_id * 2];
		tmp_textures[src_id * 2 + 1] = textures[dst_id * 2 + 1];
	}
	void addNormalID(double* tmp_normals, int src_id, int dst_id) {
		tmp_normals[src_id * 3] = normals[dst_id * 3];
		tmp_normals[src_id * 3 + 1] = normals[dst_id * 3 + 1];
		tmp_normals[src_id * 3 + 2] = normals[dst_id * 3 + 2];
	}
};

#endif // _TEXTURED_POLYHEDRON_BUILDER_
