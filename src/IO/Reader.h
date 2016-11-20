/*
 * Reader.h
 *
 *  Created on: 14 Nov 2016
 *      Author: osboxes
 */

#ifndef READER_H_
#define READER_H_

#include<fstream>
#include<vector>
#include<string>
#include<algorithm>
#include <iostream>
#include <stdlib.h>
#include "../Textured_polyhedron.h"
#include "../Textured_polyhedron_builder.h"

class Reader {
private:
	typedef CGAL::Simple_cartesian<double> K;

public:
	Reader();
	virtual ~Reader();
	void load_obj(const char *filename, std::vector<double> &coords,
			std::vector<int> &tris, std::vector<double> &textures,
			std::vector<double> &normals);
private:
	void get_integers(const char *v, int* ival);
};

#endif /* READER_H_ */
