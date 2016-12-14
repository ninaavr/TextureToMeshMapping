/*
 * Reader.cpp
 *
 *  Created on: 14 Nov 2016
 *      Author: ninaavr
 */

#include "Reader.h"

Reader::Reader() {
	// TODO Auto-generated constructor stub

}

Reader::~Reader() {
	// TODO Auto-generated destructor stub
}

void Reader::operator()(const char *filename, std::vector<double> &coords,
		std::vector<int> &tris) {
	//file has different format if textures or normals are given
	bool textures, normals = false;
	//allocates memory for temporal variables
	double x, y, z;
	char line[1024];
	// open the file, return if open fails
	FILE *fp = fopen(filename, "r");
	if (!fp) {
		std::cout << "OBJ file not found!" << std::endl;
		return;
	}
	//reads file line by line
	while (fgets(line, 1024, fp)) {
		//if line starts with 'v ', we are reading vertex
		if (line[0] == 'v'&& line[1] != 't'&& line[1] != 'n') {
			sscanf(line, "%*s%lf%lf%lf", &x, &y, &z);
			coords.push_back(x);
			coords.push_back(y);
			coords.push_back(z);
			//checks if textures are given
		} if (line[0] == 'v'&& line[1] == 't' && !textures) {
			textures = true;
			//checks if normals are given
		} if (line[0] == 'v' && line[1] == 'n' && !normals) {
			normals = true;
		} else if (line[0] == 'f') {
			int ids[9];
			get_integers(line, ids);
			//line is of the form "2 9 3"
			if (!textures && !normals) {
				for(int k = 0; k < 3;++k)
					tris.push_back(ids[k] - 1);
			//line is of the form "1//2 9//11 3//9"
			} else if (!normals) {
				for(int k = 0; k < 6; k += 2)
					tris.push_back(ids[k] - 1);
			//line is of the form "1/2 9/11 3/7"
			} else if (!textures) {
				for(int k = 0; k < 6; k += 2)
					tris.push_back(ids[k] - 1);
			//line is of the form "1/2 9/11 3/7"
			} else {
				for(int k = 0; k < 9; k += 3)
					tris.push_back(ids[k] - 1);
			}
		}
	}

	fclose(fp);
}

void Reader::get_integers(const char *v, int* ival) {
	std::string s(v);
	std::replace(s.begin(), s.end(), '/', ' ');
	std::remove(s.begin(), s.end(), 'f');
	std::remove(s.begin(), s.end(), '\n');
	sscanf(s.c_str(), "%d %d %d %d %d %d %d %d %d", &ival[0], &ival[1], &ival[2], &ival[3], &ival[4], &ival[5], &ival[6], &ival[7], &ival[8]);
}
