/*
 * Writer.h
 *
 *  Created on: 15 Nov 2016
 *      Author: osboxes
 */

#ifndef WRITER_H_
#define WRITER_H_

#include <fstream>
#include <boost/foreach.hpp>
#include <vector>
#include <CGAL/Simple_cartesian.h>
#include <CGAL/Polyhedron_3.h>
#include "../Textured_polyhedron.h"

class Writer {
private:
	typedef CGAL::Simple_cartesian<double> K;
	typedef CGAL::Polyhedron_3<K> Polyhedron;
	typedef Textured_polyhedron<K, Textured_items> TexturedPolyhedron;
public:
	Writer();
	virtual ~Writer();
	void write_obj(const std::string& fileName, TexturedPolyhedron& tp);
};

#endif /* WRITER_H_ */
