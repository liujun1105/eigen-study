#include <Eigen/Core>
#include <Spectra/SymEigsSolver.h>
#include <iostream>

#include <Eigen/Eigenvalues>

using Eigen::MatrixXd;
using Eigen::EigenSolver;
using namespace Spectra;

int main()
{
	int MATRIX_SIZE = 3;
	MatrixXd m(MATRIX_SIZE, MATRIX_SIZE);	
	// m <<
	// 	1, -0.6189, -0.8744, -0.3488,
	// 	-0.6189, 1, -0.6204, -0.4864,
	// 	-0.8744, -0.6204, 1, 0.8251,
	// 	-0.3488, -0.4864, 0.8251, 1
	// 	;
	// m <<
	// 	33, 24,
	// 	48, 57
	// 	;
	m <<
		3, 2, 4,
		2, 0, 2,
		4, 2, 3
		;
	std::cout << "matrix\n" << m << std::endl;
	std::cout << "size " << m.size() << std::endl;

	DenseSymMatProd<double> op(m);

	// Construct eigen solver object, requesting the largest three eigenvalues
	SymEigsSolver< double, BOTH_ENDS, DenseSymMatProd<double> > eigs(&op, MATRIX_SIZE, MATRIX_SIZE);

	// Initialize and compute
	eigs.init();
	int nconv = eigs.compute();
	std::cout << "nconv: " << nconv << std::endl;

	std::cout << "===================================================================" << std::endl;
    // Retrieve results
	Eigen::VectorXd evalues;
	Eigen::MatrixXd evectors;
	if (eigs.info() == SUCCESSFUL) {
		evalues = eigs.eigenvalues();
		evectors = eigs.eigenvectors();
	}

	std::cout << "Eigenvalues found: " << evalues.size() << "\n" << evalues << std::endl;
	std::cout << "Eigenvector found: " << evectors.size() << "\n" << evectors << std::endl;
	std::cout << "===================================================================" << std::endl;
	EigenSolver<MatrixXd> es;
	es.compute(m, true);

	std::cout << "Eigenvalues found: " << es.eigenvalues().size() << " \n" << es.eigenvalues() << std::endl;
	std::cout << "Eigenvectors found: " << es.eigenvectors().size() << " \n" << es.eigenvectors() << std::endl;
}
