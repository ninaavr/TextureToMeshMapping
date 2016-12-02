/*
 * Reader.h
 *
 *  Created on: 14 Nov 2016
 *      Author: ninaavr
 */

#ifndef READER_H_
#define READER_H_

#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <stdlib.h>
#include <algorithm>

class Reader {


public:
	Reader();
	virtual ~Reader();
	/**
	 * reads .obj file and stores results in arrays coords and tris
	 * @param filename contains name and path of the .obj file
	 * @param coords stores coordinates of vertices, packed [x0,y0,z0,x1,y1,z1,...]
	 * @param tris stores facets, given by corresponding vertices, packed [F0a,F0b,F0c,F1a,F1b,F1c,...]
	 */
	void load_obj(const char *filename, std::vector<double> &coords,
			std::vector<int> &tris);
private:
	/**
	 * reads the integers from a string with slashes by stripping them forward and
	 * scanning the result, the integers are then stored in ival
	 * @param v string of numbers, separated by slashes or space
	 * @param ival array of integers which stores the scanned values
	 */
	void get_integers(const char *v, int* ival);
};

#endif /* READER_H_ */
