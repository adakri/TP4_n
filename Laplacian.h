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

	Eigen::MatrixXd BuildLaplacianMatrix();///to be continued

	Eigen::VectorXd BuildSourceTerm(double t);

	Eigen::MatrixXd BuildidentityMatrix();

	Eigen::MatrixXd Get_Matrix();

	Eigen::MatrixXd Get_idendityMatrix(); //dummy

	Eigen::VectorXd Getsource_term(); //dummy

};

#define _LAPLACIAN_H
#endif
