#ifndef _LAPLACIAN_H

#include <string>
#include "Dense"
#include "Sparse"
#include "Function.h"

class Laplacian
{
private:
	Function* _fct;
	DataFile* _df;

public:
	// Constructeur
	Laplacian(Function* function, DataFile* data_file);
	//méthodes
	Eigen::VectorXd InitialCondition();

	Eigen::MatrixXd BuildLaplacianMatrix();///

	void BuildSourceTerm(double t);

	Eigen::MatrixXd Get_Matrix();

	Eigen::VectorXd Getsource_term();

};

#define _LAPLACIAN_H
#endif
