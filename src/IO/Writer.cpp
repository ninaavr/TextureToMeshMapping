/*
 * Writer.cpp
 *
 *  Created on: 15 Nov 2016
 *      Author: ninaavr
 */

#include "Writer.h"

Writer::Writer() {
	// TODO Auto-generated constructor stub

}

Writer::~Writer() {
	// TODO Auto-generated destructor stub
}

void Writer::operator()(const std::string& fileName, TexturedPolyhedron& tp) {
	std::fstream fs;
	int type = 4;
	fs.open((fileName).c_str(), std::fstream::out);
	std::string::size_type pos = fileName.find('.');
	fs << "mtllib " << fileName.substr(0, pos) << ".mtl" << '\n';
	TexturedPolyhedron::Vertex_iterator vi;
	int index = 0;
	int index2 = tp.size_of_vertices();
	for (vi = tp.vertices_begin(); vi != tp.vertices_end(); ++vi) {
		fs << "v " << vi->point() << '\n';
		id[vi].first = index;
		++index;
		if (vi->u2() != -1) {
			id[vi].second = index2;
			++index2;
		}
	}

	if (tp.texturesExist) {
		for (vi = tp.vertices_begin(); vi != tp.vertices_end(); ++vi) {
			fs << "vt " << vi->u() << " " << vi->v() << '\n';
		}
		//second value for seam vertices
		for (vi = tp.vertices_begin(); vi != tp.vertices_end(); ++vi) {
			if (vi->u2() != -1)
				fs << "vt " << vi->u2() << " " << vi->v2() << '\n';
		}
		type = 3;
	}
	if (tp.normalsExist) {
		for (vi = tp.vertices_begin(); vi != tp.vertices_end(); ++vi) {
			fs << "vn " << vi->normal() << '\n';
		}
		type = 2;
	}
	if (tp.texturesExist && tp.normalsExist)
		type = 1;
	fs << "usemtl material" << '\n';
	TexturedPolyhedron::Face_iterator fi;

	for (fi = tp.facets_begin(); fi != tp.facets_end(); ++fi) {
		fs << "f ";
		TexturedPolyhedron::Halfedge_around_facet_circulator h =
				fi->facet_begin();
		do {
			switch (type) {
			case (1): //textures and normals
				if (fi->is_side()==0 || h->vertex()->u2() == -1)
					fs << id[h->vertex()].first + 1 << '/' << id[h->vertex()].first + 1 << '/'
							<< id[h->vertex()].first + 1 << ' ';
				else
					fs << id[h->vertex()].first + 1 << '/' << id[h->vertex()].second + 1 << '/'
							<< id[h->vertex()].first + 1 << ' ';
				break;
			case (2): //normals
				fs << id[h->vertex()].first + 1 << '/' << '/' << id[h->vertex()].first + 1 << ' ';
				break;
			case (3): //textures
				if (fi->is_side()==0 || h->vertex()->u2() == -1){
					fs << id[h->vertex()].first + 1 << '/' << id[h->vertex()].first + 1 << ' ';
				}else{
					fs << id[h->vertex()].first + 1 << '/' << id[h->vertex()].second + 1 << ' ';
				}
				break;
			case (4): //no additional info
				fs << id[h->vertex()].first + 1 << ' ';
				break;
			}
		} while (++h != fi->facet_begin());
		fs << '\n';
	}
	fs.close();
}
