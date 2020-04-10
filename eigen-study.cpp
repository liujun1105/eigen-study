#include <Eigen/Core>
#include <Spectra/SymEigsSolver.h>
#include <iostream>
#include <Spectra/SymEigsShiftSolver.h>
using Eigen::MatrixXd;
using namespace Spectra;

int main()
{
	int MATRIX_SIZE = 4;
	MatrixXd m(4, 4);	
	m <<
		1, -0.6189, -0.8744, -0.3488,
		-0.6189, 1, -0.6204, -0.4864,
		-0.8744, -0.6204, 1, 0.8251,
		-0.3488, -0.4864, 0.8251, 1
		;
	std::cout << "matrix\n" << m << std::endl;
	std::cout << "size " << m.size() << std::endl;

	DenseSymMatProd<double> op(m);

	// Construct eigen solver object, requesting the largest three eigenvalues
	SymEigsSolver< double, BOTH_ENDS, DenseSymMatProd<double> > eigs(&op, 4, 4);

	// Initialize and compute
	eigs.init();
	int nconv = eigs.compute();
	std::cout << "nconv: " << nconv << std::endl;
	// Retrieve results
	Eigen::VectorXd evalues;
	Eigen::MatrixXd evectors;
	if (eigs.info() == SUCCESSFUL) {
		evalues = eigs.eigenvalues();
		evectors = eigs.eigenvectors();
	}

	std::cout << "Eigenvalues found: " << evalues.size() << "\n" << evalues << std::endl;
	std::cout << "Eigenvector found: " << evectors.size() << "\n" << evectors << std::endl;

}
