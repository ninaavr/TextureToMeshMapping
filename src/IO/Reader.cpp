/*
 * Reader.cpp
 *
 *  Created on: 14 Nov 2016
 *      Author: osboxes
 */

#include "Reader.h"

Reader::Reader() {
	// TODO Auto-generated constructor stub

}

Reader::~Reader() {
	// TODO Auto-generated destructor stub
}

// reads the first integer from a string in the form
// "334/455/234" by stripping forward slashes and
// scanning the result
void Reader::get_integers(const char *v, int* ival) {
	std::string s(v);
	int k0, k1, k2, k3, k4, k5, k6, k7, k8;
	std::replace(s.begin(), s.end(), '/', ' ');
	std::remove(s.begin(), s.end(), 'f');
	std::remove(s.begin(), s.end(), '\n');
	sscanf(s.c_str(), "%d %d %d %d %d %d %d %d %d", &ival[0], &ival[1], &ival[2], &ival[3], &ival[4], &ival[5], &ival[6], &ival[7], &ival[8]);
}

// barebones .OFF file reader, throws away texture coordinates, normals, etc.
// stores results in input coords array, packed [x0,y0,z0,x1,y1,z1,...] and
// tris array packed [T0a,T0b,T0c,T1a,T1b,T1c,...]
void Reader::load_obj(const char *filename, std::vector<double> &coords,
		std::vector<int> &tris, std::vector<double> &textures,
		std::vector<double> &normals) {
	//make sure they are empty for the files, that don't provide them
	textures.clear();
	normals.clear();

	double x, y, z;
	char line[1024], v0[1024], v1[1024], v2[1024];
	char t0[1024], t1[1024], t2[1024], n0[1024], n1[1024], n2[1024];

	// open the file, return if open fails
	FILE *fp = fopen(filename, "r");
	if (!fp) {
		std::cout << "OBJ file not found!" << std::endl;
		return;
	}
	// read lines from the file, if the first character of the
	// line is 'v', we are reading a vertex, otherwise, if the
	// first character is a 'f' we are reading a facet
	while (fgets(line, 1024, fp)) {
		if (line[0] == 'v'&& line[1] != 't'&& line[1] != 'n') {
			sscanf(line, "%*s%lf%lf%lf", &x, &y, &z);
			coords.push_back(x);
			coords.push_back(y);
			coords.push_back(z);
		} if (line[0] == 'v' && line[1] == 't') {
			sscanf(line, "%*s%lf%lf", &x, &y);
			textures.push_back(x);
			textures.push_back(y);
		} if (line[0] == 'v' && line[1] == 'n') {
			sscanf(line, "%*s%lf%lf%lf", &x, &y, &z);
			normals.push_back(x);
			normals.push_back(y);
			normals.push_back(z);
		} else if (line[0] == 'f') {
			int ids[9];
			get_integers(line, ids);
			if (textures.empty() && normals.empty()) {
				for(int k = 0; k < 3;++k)
					tris.push_back(ids[k] - 1);
				//sscanf(line, "%*s%s%s%s", v0, v1, v2);
				//tris.push_back(get_first_integer(v0) - 1);
				//tris.push_back(get_first_integer(v1) - 1);
				//tris.push_back(get_first_integer(v2) - 1);
			} else if (normals.empty()) {
				for(int k = 0; k < 6; ++k)
					tris.push_back(ids[k] - 1);
				//sscanf(line, "%*s%s%s%s%s%s%s", v0, t0, v1, t1, v2, t2);
				//tris.push_back(get_first_integer(v0) - 1);
				//tris.push_back(get_first_integer(t0) - 1);
				//tris.push_back(get_first_integer(v1) - 1);
				//tris.push_back(get_first_integer(t1) - 1);
				//tris.push_back(get_first_integer(v2) - 1);
				//tris.push_back(get_first_integer(t2) - 1);
			} else if (textures.empty()) {
				for(int k = 0; k < 6; ++k)
					tris.push_back(ids[k] - 1);
				//sscanf(line, "%*s%s%s%s%s%s%s", v0, n0, v1, n1, v2, n2);
				/*tris.push_back(get_first_integer(v0) - 1);
				tris.push_back(get_first_integer(n0) - 1);
				tris.push_back(get_first_integer(v1) - 1);
				tris.push_back(get_first_integer(n1) - 1);
				tris.push_back(get_first_integer(v2) - 1);
				tris.push_back(get_first_integer(n2) - 1);*/
			} else {
				for(int k = 0; k < 9; ++k)
					tris.push_back(ids[k] - 1);
				//sscanf(line, "%*s%s%s%s%*s%s%s%s%*s%s%s%s", v0, t0, n0, v1, t1, n1, v2, t2, n2);
				/*tris.push_back(get_first_integer(v0) - 1);
				tris.push_back(get_first_integer(t0) - 1);
				tris.push_back(get_first_integer(n0) - 1);
				tris.push_back(get_first_integer(v1) - 1);
				tris.push_back(get_first_integer(t1) - 1);
				tris.push_back(get_first_integer(n1) - 1);
				tris.push_back(get_first_integer(v2) - 1);
				tris.push_back(get_first_integer(t2) - 1);
				tris.push_back(get_first_integer(n2) - 1);*/
			}
		}
	}
	/*for (int i = 0; i < tris.size(); ++i){
		cout << tris[i]<<endl;
		if (i==15)
			break;
	}*/

	fclose(fp);
}


