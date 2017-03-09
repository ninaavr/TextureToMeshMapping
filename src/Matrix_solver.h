/*
 * Matrixsolver.h
 *
 *  Created on: 13 Feb 2017
 *      Author: ninaavr
 */

#ifndef MATRIXSOLVER_H_
#define MATRIXSOLVER_H_

#include <Eigen/Sparse>
#include <Eigen/SparseQR>
#include <Eigen/SparseLU>
#include <Eigen/OrderingMethods>
#include <Eigen/IterativeLinearSolvers>
#include <stdlib.h>
#include <iostream>
#include "Matrix_loader.h"
#include "TexturedPolyhedron/Textured_polyhedron.h"

class Matrix_solver {
	typedef Eigen::SparseMatrix<double> Matrix;
	typedef CGAL::Simple_cartesian<double> K;
	typedef Textured_polyhedron<K, Textured_items> TexturedPolyhedron;
	typedef std::map<TexturedPolyhedron::Vertex_handle, std::pair<int, int> > Column;
public:
	Matrix_solver();
	virtual ~Matrix_solver();
	void solve_system(Matrix& Mf, Matrix& Mp, Matrix& U, Eigen::VectorXd& textures);
};

#endif /* MATRIXSOLVER_H_ */
