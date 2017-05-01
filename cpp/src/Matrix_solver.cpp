/*
 * Matrixsolver.cpp
 *
 *  Created on: 13 Feb 2017
 *      Author: ninaavr
 */

#include "Matrix_solver.h"
using namespace Eigen;

Matrix_solver::Matrix_solver() {
	// TODO Auto-generated constructor stub

}

Matrix_solver::~Matrix_solver() {
	// TODO Auto-generated destructor stub
}

void Matrix_solver::solve_system(Matrix& Mf,  Matrix& Mp,  Matrix& U, VectorXd& textures){
	LeastSquaresConjugateGradient<SparseMatrix<double> > solver;
	solver.compute(Mf);
	
	if(solver.info()!=Success) {
		return;
	}
	textures = solver.solve( - Mp*U);
	
	std::cout << "#iterations:     " << solver.iterations() << std::endl;
	std::cout << "estimated error: " << solver.error()      << std::endl;
	//cout << textures << endl;
}
