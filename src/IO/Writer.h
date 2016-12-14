/*
 * Writer.h
 *
 *  Created on: 15 Nov 2016
 *      Author: ninaavr
 */

#ifndef WRITER_H_
#define WRITER_H_

#include <fstream>
#include <vector>
#include <CGAL/Simple_cartesian.h>
#include <CGAL/Polyhedron_3.h>
#include "../TexturedPolyhedron/Textured_polyhedron.h"

class Writer {
private:
	typedef CGAL::Simple_cartesian<double> K;
	typedef CGAL::Polyhedron_3<K> Polyhedron;
	typedef Textured_polyhedron<K, Textured_items> TexturedPolyhedron;
public:
	Writer();
	virtual ~Writer();
	/**
	 * writes the mesh in .obj file, if texture or normals exists, they are also written
	 * @param fileName the name of the file where we store the output
	 * @param tp the mesh we write in the .obj file
	 */
	void operator()(const std::string& fileName, TexturedPolyhedron& tp);
};

#endif /* WRITER_H_ */
