#ifndef _LAPLACIAN_CPP

#include "Laplacian.h"
#include <iostream>

using namespace std;
using namespace Eigen;

// Constructeur
Laplacian::Laplacian(Function* function, DataFile* data_file) :
_fct(function), _df(data_file)
{
}

VectorXd Laplacian::InitialCondition()
{
  int Nx,Ny;
  double xmin,xmax,ymin,ymax,hx,hy;
  xmin= _df -> Get_xmin();
  // xmax= _df -> Get_xmax();
  ymin= _df -> Get_ymin();
  // ymax= _df -> Get_ymax();
  hx= _df ->Get_hx();
  hy= _df ->Get_hy();

  Nx=_df -> Get_Nx();
  Ny=_df -> Get_Ny();
  VectorXd cond_init;
  cond_init.resize(Nx*Ny);

  for (int i=0; i<Nx; i++ )
  {
    for(int j=0; j<Ny; j++)
    {
      cond_init(i+j*Nx)=_fct -> InitialCondition(xmin+i*hx,ymin+j*hy);
    }
  }
  return cond_init;
}

MatrixXd Laplacian::BuildLaplacianMatrix()
{

  double hx,hy,Nx,Ny;
  Nx=_df -> Get_Nx();
  Ny=_df -> Get_Ny();
  hx=_df -> Get_hx();
  hy=_df -> Get_hy();

  //construction de B
  double a,b;
  a=1./(hx*hx+hy*hy);
  b=-1/(hx*hx);
  SparseMatrix<double> B(Nx,Ny);
  vector<Triplet<double>> triplets;
  for (int i=0; i<B.rows(); ++i)
  {
    triplets.push_back({i,i,a});
    if (i > 0)
      triplets.push_back({i,i-1,b});
    if (i < B.rows()-1)
      triplets.push_back({i,i+1,b});
  }
  B.setFromTriplets(triplets.begin(), triplets.end());
  //contruire T
  b=-1/(hy*hy);
  SparseMatrix<double> T(Nx,Ny);
  vector<Triplet<double>> triplets1;
  for (int i=0; i<T.rows(); ++i)
  {
    triplets1.push_back({i,i,b});
    if (i > 0)
      triplets1.push_back({i,i-1,0.});
    if (i < B.rows()-1)
      triplets1.push_back({i,i+1,0.});
  }
  T.setFromTriplets(triplets1.begin(), triplets1.end());



  return B;
  }





void Laplacian::BuildSourceTerm(double t)
{
  int Nx,Ny;
  double xmin,xmax,ymin,ymax,hx,hy;
  xmin= _df -> Get_xmin();
  // xmax= _df -> Get_xmax();
  ymin= _df -> Get_ymin();
  // ymax= _df -> Get_ymax();
  hx= _df ->Get_hx();
  hy= _df ->Get_hy();

  Nx=_df -> Get_Nx();
  Ny=_df -> Get_Ny();
  VectorXd source_term(Nx*Ny);
    for (int i=0; i<Nx; i++ )
  {
    for(int j=0; j<Ny; j++)
    {
      source_term(i+j*Nx)=_fct -> SourceFunction(xmin+i*hx,ymin+j*hy,t);
    }
  }
  return source_term;
};


MatrixXd Laplacian::Get_Matrix(){};


VectorXd Laplacian::Getsource_term()
{
  int Nx,Ny;
  double xmin,xmax,ymin,ymax,hx,hy;
  xmin= _df -> Get_xmin();
  // xmax= _df -> Get_xmax();
  ymin= _df -> Get_ymin();
  // ymax= _df -> Get_ymax();
  hx= _df ->Get_hx();
  hy= _df ->Get_hy();

  Nx=_df -> Get_Nx();
  Ny=_df -> Get_Ny();
  VectorXd source_term(Nx*Ny);

  //juste por faire fonctionner
  double t=0.;

  for (int i=0; i<Nx; i++ )
  {
    for(int j=0; j<Ny; j++)
    {
      source_term(i+j*Nx)=_fct -> SourceFunction(xmin+i*hx,ymin+j*hy,t);
    }
  }
  return source_term;
};


#define _LAPLACIAN_CPP
#endif
