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
	int index3 = index2 + tp.seam->size()-1;
	for (vi = tp.vertices_begin(); vi != tp.vertices_end(); ++vi) {
		id[vi] = new int[3];
		id[vi][0] = -1;
		id[vi][1] = -1;
		id[vi][2] = -1;
		fs << "v " << vi->point() << '\n';
		id[vi][0] = index;
		++index;
		if (vi->u()[1] != -1) {
			id[vi][1] = index2;
			++index2;
		}
		if (vi->u()[2] != -1) {
			id[vi][2] = index3;
			++index3;
		}
	}

	if (tp.texturesExist) {
		for (vi = tp.vertices_begin(); vi != tp.vertices_end(); ++vi) {
			fs << "vt " << vi->u()[0] << " " << vi->v()[0] << '\n';
		}
		//second value for seam vertices
		for (vi = tp.vertices_begin(); vi != tp.vertices_end(); ++vi) {
			if (vi->u()[1] != -1)
				fs << "vt " << vi->u()[1] << " " << vi->v()[1] << '\n';
		}
		for (vi = tp.vertices_begin(); vi != tp.vertices_end(); ++vi) {
			if (vi->u()[2] != -1)
				fs << "vt " << vi->u()[2] << " " << vi->v()[2] << '\n';
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
	int i;
	for (fi = tp.facets_begin(); fi != tp.facets_end(); ++fi) {
		fs << "f ";
		TexturedPolyhedron::Halfedge_around_facet_circulator h = fi->facet_begin();
		i=0;
		do {
			switch (type) {
			case (1): //textures and normals
					fs << id[h->vertex()][0] + 1 << '/' << id[h->vertex()][fi->is_side()[i]] + 1 << '/' << id[h->vertex()][0] + 1 << ' ';
				break;
			case (2): //normals
				fs << id[h->vertex()][0] + 1 << '/' << '/' << id[h->vertex()][0] + 1 << ' ';
				break;
			case (3): //textures
					fs << id[h->vertex()][0] + 1 << '/' << id[h->vertex()][fi->is_side()[i]] + 1 << ' ';
				break;
			case (4): //no additional info
				fs << id[h->vertex()][0] + 1 << ' ';
				break;
			}
			++i;
		} while (++h != fi->facet_begin());
		fs << '\n';
	}
	fs.close();
	for (vi = tp.vertices_begin(); vi != tp.vertices_end(); ++vi) {
		delete id[vi];
	}
}
