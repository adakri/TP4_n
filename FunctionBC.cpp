#ifndef _FUNCTION_CPP

#include "Function.h"
#include <cmath>

Function::Function(DataFile* data_file)
: _sigma(data_file->Get_sigma()),
_xmin(data_file->Get_xmin()), _xmax(data_file->Get_xmax()),
_ymin(data_file->Get_ymin()), _ymax(data_file->Get_ymax())
{
}

// Condition initiale
double Function::InitialCondition(const double x, const double y) const
{
  return ExactSolution(x, y, 0);
}

// Solution exacte
double Function::ExactSolution(const double x, const double y, const double t) const
{
  return cos(3.*M_PI*x)*(y-(_ymax+_ymin)/4.)/(t+1.);
}

// Terme source
double Function::SourceFunction(const double x, const double y, const double t) const
{
  return -cos(3*M_PI*x)/pow(t+1.,2)*(y-(_ymin+_ymax)/4)
  +9*_sigma*pow(M_PI,2)*cos(3*M_PI*x)*(y-(_ymax+_ymin)/4)/(t+1.);
}

// Conditions limites - Dirichlet
double Function::DirichletLeftBC(const double y, const double t) const
{
  return ExactSolution(_xmin, y, t);
}

double Function::DirichletRightBC(const double y, const double t) const
{
  return ExactSolution(_xmax, y, t);
}

double Function::DirichletDownBC(const double x, const double t) const
{
  return ExactSolution(x, _ymin, t);
}

double Function::DirichletUpBC(const double x, const double t) const
{
  return ExactSolution(x, _ymax, t);
}

// Conditions limites - Neumann
double Function::NeumannLeftBC(const double y, const double t) const
{
  return  -3*M_PI*sin(3.*M_PI*_xmin)*(y-(_ymin+_ymax)/4)/(t+1.0);
}

double Function::NeumannRightBC(const double y, const double t) const
{
  return  -3*M_PI*sin(3.*M_PI*_xmax)*(y-(_ymin+_ymax)/4)/(t+1.0);
}

double Function::NeumannDownBC(const double x, const double t) const
{
  return cos(3.*M_PI*x)/(t+1.0);
}

double Function::NeumannUpBC(const double x, const double t) const
{
  return cos(3.*M_PI*x)/(t+1.0);
}

#define _FUNCTION_CPP
#endif
