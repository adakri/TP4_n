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
  return (y-_ymin)*(x-_xmin)*sin(y-_ymax)*sin(2*M_PI*(x-_xmax))*pow(t+1,2);
}

// Terme source
double Function::SourceFunction(const double x, const double y, const double t) const
{
  return -_sigma*(4*pow(M_PI,2)*(-_xmin + x)*(-_ymin + y)*pow(t+1,2)*sin(2*M_PI*(-_xmax + x))*sin(_ymax - y)
  - 4*M_PI*(-_ymin + y)*pow(t+1,2)*sin(_ymax - y)*cos(2*M_PI*(-_xmax + x)) + (-_xmin + x)*(-_ymin + y)*pow(t+1,2)*sin(2*M_PI*(-_xmax + x))*sin(_ymax - y)
  + 2*(-_xmin + x)*pow(t+1,2)*sin(2*M_PI*(-_xmax + x))*cos(_ymax - y)) + (-_xmin + x)*(-_ymin + y)*(-2*t - 2)*sin(2*M_PI*(-_xmax + x))*sin(_ymax - y);
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
  double x = _xmin;
  double diffux = -2*M_PI*(-_xmin + x)*(-_ymin + y)*pow(t+1,2)*sin(_ymax - y)*cos(2*M_PI*(-_xmax + x)) - (-_ymin + y)*pow(t+1,2)*sin(2*M_PI*(-_xmax + x))*sin(_ymax - y);

  return diffux;
}

double Function::NeumannRightBC(const double y, const double t) const
{
  double x = _xmax;
  double diffux = -2*M_PI*(-_xmin + x)*(-_ymin + y)*pow(t+1,2)*sin(_ymax - y)*cos(2*M_PI*(-_xmax + x)) - (-_ymin + y)*pow(t+1,2)*sin(2*M_PI*(-_xmax + x))*sin(_ymax - y);

  return diffux;
}

double Function::NeumannDownBC(const double x, const double t) const
{
  double y = _ymin;
  double diffuy = (-_xmin + x)*(-_ymin + y)*pow(t+1,2)*sin(2*M_PI*(-_xmax + x))*cos(_ymax - y) - (-_xmin + x)*pow(t+1,2)*sin(2*M_PI*(-_xmax + x))*sin(_ymax - y);

  return diffuy;
}

double Function::NeumannUpBC(const double x, const double t) const
{
  double y = _ymax;
  double diffuy = (-_xmin + x)*(-_ymin + y)*pow(t+1,2)*sin(2*M_PI*(-_xmax + x))*cos(_ymax - y) - (-_xmin + x)*pow(t+1,2)*sin(2*M_PI*(-_xmax + x))*sin(_ymax - y);

  return diffuy;
}

#define _FUNCTION_CPP
#endif
