#ifndef _TIME_SCHEME_CPP

#include "TimeScheme.h"
#include <iostream>
#include <fstream>
#include <math.h>


using namespace Eigen;
using namespace std;

// Constructeur par défaut (ne pas oublier de mettre votre pointeur à 0 !!)
TimeScheme::TimeScheme(DataFile* data_file, Laplacian* lap) :
_df(data_file), _lap(lap)
{
}

// Destructeur
TimeScheme::~TimeScheme()
{
}


//-------euler scheme


EulerScheme::EulerScheme(DataFile* data_file, Laplacian* lap) :
TimeScheme(data_file,lap)
{
}

void EulerScheme::Integrate(double t)
{
    MatrixXd H;
    VectorXd F,product;
    double dt,sigma;
    int Nx,Ny;
    sigma = _df -> Get_sigma();
    dt = _df -> Get_dt();

    H= _lap -> Get_Matrix();
    F= _lap -> BuildSourceTerm(t);

    Nx=_df -> Get_Nx();
    Ny=_df -> Get_Ny();

    _solution.resize(Nx*Ny);
    product.resize(Nx*Ny);

    product=H * _solution ;

    for (int i=0; _solution.size(); i++)
    {
      _solution[i] = _solution[i] + (product[i]*(-sigma) + F[i] )*dt;
    }
};

VectorXd EulerScheme::solve()
{
  double t0,tfinal,dt,t;
  t0 = _df -> Get_t0();
  tfinal = _df -> Get_tfinal();
  dt = _df -> Get_dt();
  t=t0;
  while(t<tfinal)
  {
    EulerScheme::Integrate(t);
    t=t+dt;
  }
  return _solution;
};


//----implicit euler scheme


ImplicitEulerScheme::ImplicitEulerScheme(DataFile* data_file, Laplacian* lap) :
TimeScheme(data_file,lap)
{
}
void ImplicitEulerScheme::Integrate()
{

}

//
VectorXd TimeScheme::GetSolution()
{

}

void TimeScheme::SaveSol(Eigen::VectorXd sol, std::string name_sol, int n)
{
    string n_file = _df->Get_results() + "/" + name_sol + to_string(n) + ".vtk";
    ofstream solution;
    solution.open(n_file, ios::out);
    int Nx(_df->Get_Nx()), Ny(_df->Get_Ny());
    double xmin(_df->Get_xmin()), ymin(_df->Get_ymin());
    double hx(_df->Get_hx()), hy(_df->Get_hy());
    solution << "# vtk DataFile Version 3.0" << endl;
    solution << "sol" << endl;
    solution << "ASCII" << endl;
    solution << "DATASET STRUCTURED_POINTS" << endl;
    solution << "DIMENSIONS " << Nx << " " << Ny << " " << 1 << endl;
    solution << "ORIGIN " << xmin << " " << ymin << " " << 0 << endl;
    solution << "SPACING " << hx << " " << hy << " " << 1 << endl;;
    solution << "POINT_DATA " << Nx*Ny << endl;
    solution << "SCALARS sol float" << endl;
    solution << "LOOKUP_TABLE default" << endl;
    for(int j=0; j<Ny; ++j)
    {
        for(int i=0; i<Nx; ++i)
        {
            solution << sol(i+j*Nx) << " ";
        }
        solution << endl;
    }
    solution.close();
}

#define _TIME_SCHEME_CPP
#endif
