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
      cond_init(i+j*Nx)=_fct -> InitialCondition(xmin+(i+1)*hx,ymin+(j+1)*hy);
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

  //construction de H
  double a,b,c;
  a=2./(hx*hx)+2./(hy*hy);
  b=-1/(hx*hx);
  c=-1/(hy*hy);
  SparseMatrix<double> H(Nx*Ny,Nx*Ny);
  vector<Triplet<double>> triplets;
  for (int i=0; i<Ny; i++)
  {
    int k= i*Nx;
    for (int j=0; j<Nx; j++)
    {
      triplets.push_back({k+j,k+j,a});
      if (j <Nx-1)
        triplets.push_back({k+j,k+j+1,b});
      if (k+j+Nx < H.rows())
        triplets.push_back({k+j,k+j+Nx,c});
      if (j < Nx-1)
        triplets.push_back({k+j+1,k+j,b});
      if (k+j+Nx < H.rows())
        triplets.push_back({k+j+Nx,k+j,c});
    }
  }
  H.setFromTriplets(triplets.begin(), triplets.end());
  //construction de H à continuer


  return H;
  }





VectorXd Laplacian::BuildSourceTerm(double t)
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


MatrixXd Laplacian::Get_Matrix()
{

  MatrixXd M=Laplacian::BuildLaplacianMatrix();
  return M;
};


VectorXd Laplacian::Getsource_term()
{

};

//idendity matrix

MatrixXd Laplacian::BuildidentityMatrix()
{

  int Nx,Ny;
  Nx=_df -> Get_Nx();
  Ny=_df -> Get_Ny();
  SparseMatrix<double> I(Nx*Ny,Nx*Ny);
  vector<Triplet<double>> triplets;
  for (int i=0; i<I.rows(); ++i)
  {
    triplets.push_back({i,i,1.});
    if (i > 0)
      triplets.push_back({i,i-1,0.});
    if (i < I.rows()-1)
      triplets.push_back({i,i+1,0.});
  }
  I.setFromTriplets(triplets.begin(), triplets.end());
  return I;
};

MatrixXd Laplacian::Get_idendityMatrix()
{
  MatrixXd I=Laplacian::BuildidentityMatrix(); //dummy
  return I;
};


#define _LAPLACIAN_CPP
#endif
