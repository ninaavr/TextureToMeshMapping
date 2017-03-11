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
	/*SparseQR<SparseMatrix<double>, COLAMDOrdering<int> > solver;
	Mf.makeCompressed();
	solver.compute(Mf);
	textures = solver.solve(-Mp*U);*/
	LeastSquaresConjugateGradient<SparseMatrix<double> > solver;
	solver.compute(Mf);
	//cout << "Mf   "<< Mf << endl;
	if(solver.info()!=Success) {
		return;
	}
	textures = solver.solve( - Mp*U);
	//cout << "Mp   "<< Mp << endl;
	//cout << "-Mp*U   "<< - Mp*U << endl;
	std::cout << "#iterations:     " << solver.iterations() << std::endl;
	std::cout << "estimated error: " << solver.error()      << std::endl;
	//cout << textures << endl;
}
