/*
 * Writer.cpp
 *
 *  Created on: 15 Nov 2016
 *      Author: osboxes
 */

#include "Writer.h"

Writer::Writer() {
	// TODO Auto-generated constructor stub

}

Writer::~Writer() {
	// TODO Auto-generated destructor stub
}

void Writer::write_obj(const std::string& fileName, TexturedPolyhedron& tp) {
	std::fstream fs;
	int type = 4;
	fs.open((fileName).c_str(), std::fstream::out);
	fs << "mtllib " << fileName << ".mtl" << '\n';
	TexturedPolyhedron::Vertex_iterator vi;
	for (vi = tp.vertices_begin(); vi != tp.vertices_end(); ++vi) {
		fs << "v " << vi->point() << '\n';
	}

	if (tp.texturesExist) {
		for (vi = tp.vertices_begin(); vi != tp.vertices_end(); ++vi) {
			fs << "vt " << vi->u() << " " << vi->v() << '\n';
		}
		type = 3;
	}
	if (tp.normalsExist) {
		for (vi = tp.vertices_begin(); vi != tp.vertices_end(); ++vi) {
			fs << "vn " << vi->normal() << '\n';
		}
		type = 2;
	}
	if (tp.texturesExist&&tp.normalsExist)
		type = 1;
	fs << "usemtl material" << '\n';
	TexturedPolyhedron::Face_iterator fi;

	for (fi = tp.facets_begin(); fi != tp.facets_end(); ++fi) {
		fs << "f ";
		TexturedPolyhedron::Halfedge_around_facet_circulator h =
				fi->facet_begin();
		do {
			switch(type){
			case(1):
				fs << h->vertex()->id() + 1 << '/' << h->vertex()->id() + 1
						<< '/' << h->vertex()->id() + 1 << ' ';
				break;
			case(2):
				fs << h->vertex()->id() + 1 << '/' << '/' << h->vertex()->id() + 1 << ' ';
			break;
			case(3):
				fs << h->vertex()->id() + 1 << '/' << h->vertex()->id() + 1 << ' ';
			break;
			case(4):
				fs << h->vertex()->id() + 1 ;
			break;
			}
		} while (++h != fi->facet_begin());
		fs << '\n';
	}
	 fs.close();
/*TexturedPolyhedron::Halfedge_around_facet_circulator fc;
		 if (tp.normalsExist && tp.texturesExist) {
		 for (fc = fi; fc != fi; ++fc) {
		 fs << fc->vertex()->id() + 1 << '/' << fc->vertex()->id() + 1 << '/'
		 << fc->vertex()->id() + 1 << ' ';
		 }
		 } else if (tp.normalsExist) {
		 fs << fc->vertex()->id() + 1 << "//" << fc->vertex()->id() + 1 << ' ';
		 } else if (tp.texturesExist)
		 fs << fc->vertex()->id() + 1 << "/" << fc->vertex()->id() + 1 << ' ';
		 else {
		 fs << fc->vertex()->id() + 1 << ' ';
		 }
		 fs << '\n';
		 }
		 fs.close();*/
	}
