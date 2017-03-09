/*
 * MatrixLoader.h
 *
 *  Created on: 28 Nov 2016
 *      Author: ninaavr
 */

#ifndef MATRIXLOADER_H_
#define MATRIXLOADER_H_

#include <CGAL/Simple_cartesian.h>
#include <CGAL/Polyhedron_3.h>
#include <stdlib.h>
#include <Eigen/Dense>
#include <Eigen/Sparse>
#include "TexturedPolyhedron/Textured_polyhedron.h"
#include "Matrix_calculator.h"


class Matrix_loader {
protected:
	typedef CGAL::Simple_cartesian<double> K;
	typedef CGAL::Polyhedron_3<K> Polyhedron;
	typedef Textured_polyhedron<K, Textured_items> TexturedPolyhedron;
	typedef TexturedPolyhedron::Facet_iterator Facet_iterator;
	typedef TexturedPolyhedron::Facet_handle Facet_handle;
	typedef TexturedPolyhedron::Vertex_iterator Vertex_iterator;
	typedef TexturedPolyhedron::Halfedge_iterator Halfedge_iterator;
	typedef TexturedPolyhedron::Halfedge_handle Halfedge_handle;
	typedef TexturedPolyhedron::Vertex_handle Vertex_handle;
	typedef TexturedPolyhedron::Halfedge_around_facet_circulator HF_circulator;
	typedef TexturedPolyhedron::Halfedge_around_vertex_circulator HV_circulator;

	typedef std::map<Vertex_handle, std::pair<int, int> > Column;
	typedef std::map<Facet_handle, int> Row;
	typedef std::map<Vertex_handle, bool > Tag;
	typedef std::list<Halfedge_handle> Halfedges;
	typedef std::list<Vertex_handle> Vertices;
protected:
	Matrix_calculator mc;
	//std map for each vertex to its corresponding column in the matrix
	Column column;
	//std map for each facet to its corresponding row in the matrix
	Row row;
	//std mapping of vertices with boolean variables that define if a vertex is seam
	Tag seam;
	//std mapping of vertices with boolean variables that define if a vertex is this type
	Tag this_type;
public:
	Matrix_loader();
	virtual ~Matrix_loader();
	/**loads a matrix which is used for finding a least square conformal mapping
	 * must be implemented in the subclasses for matrices with pinned and free vertices
	 * @param tp textured polyhedron
	 * @param pinnedVertices std list of the vertices with predefined texture coordinates*/
	virtual void load_M(TexturedPolyhedron& tp, Eigen::SparseMatrix<double>& M) = 0;
protected:
	/**sets std map seam to true for the vertices which lie on the virtual cut of the polyhedron
	 * and std map this_type to true if they correspond to the type used in the subclass
	 * must be implemented in the subclasses for matrices with pinned and free vertices
	 * @param tp the textured polyhedron
	 * @param pinned std list of the vertices with predefined texture coordinates*/
	virtual void set_tags(TexturedPolyhedron& tp) = 0;
	/**sets column, i.e. maps the vertices with integers corresponding to their column in the matrix,
	 * seam vertices need 2 texture coordinates for left and right side of the virtual cut,
	 * hence they have 2 columns in the matrix
	 * @param tp the textured polyhedron which contains the vertices*/
	void set_columns(TexturedPolyhedron& tp);
	/**sets row, i.e. maps the facets to their corresponding rows in the matrix
	 * @param tp the textured polyhedron which contains the facets*/
	void set_rows(TexturedPolyhedron& tp);
	/**loads the vertices that lie on the virtual cut in the matrix
	 * @param tp the textured polyhedron which contains a halfedge std list with the seam vertices
	 * @param the matrix where the result is stored*/
	void load_seam(TexturedPolyhedron& tp, Eigen::SparseMatrix<double>& M);
	/**counts the number of vertices from this type (pinned or free) which lie on the virtual cut
	 * @return their number*/
	int count_this_seam();
	/**counts the number of vertices from this type with fixed texture coordinates (pinned) or otherwise (free)
	 * @return their number*/
	int count_this_type();
private:
	/**loads the calculations for a given vertex and given facet that lie on the virtual cut
	 * @param v the given vertex
	 * @param f the given facet
	 * @param left is true if the facet belongs to the left side of the virtual cut, otherwise false*/
	void load_seam_face(Vertex_handle v, Facet_handle f, const bool left, Eigen::SparseMatrix<double>& M);
};

#endif /* MATRIXLOADER_H_ */
