#ifndef _DATA_FILE_CPP

#include "DataFile.h"
#include <fstream>
#include <iostream>
#include <cmath>
#include <regex>

using namespace std;

// Constructeur
DataFile::DataFile(std::string file_name)
: _file_name(file_name), _if_xmin(false), _if_xmax(false), _if_hx(false), _if_sigma(false),
_if_t0(false), _if_tfinal(false), _if_dt(false), _if_scheme(false), _if_results(false),
_if_LBC(false), _if_RBC(false), _if_UBC(false), _if_DBC(false)
{
}


// Une fonction qui nettoie la chaine de caractères pour correspondre au format attendu.
string DataFile::clean_line(string &s)
{
  string res = s;

  // Remove everything after a possible #
  res = regex_replace( res, regex("#.*$"), string("") );
  // Replace tabulation(s) by space(s)
  res = regex_replace( res, regex("\t"), string(" "), regex_constants::match_any );
  // Replace multiple spaces by 1 space
  //res = regex_replace( res, regex("\\s+"), string(" "), regex_constants::match_any );
  // Remove any leading spaces
  res = regex_replace( res, regex("^ *"), string("") );

  return res;
}

// Lecture du fichier de données
void DataFile::ReadDataFile()
{
  ifstream data_file(_file_name.data());
  if (!data_file.is_open())
  {
    cout << "Unable to open file " << _file_name << endl;
    abort();
  }
  else
  {
    cout << "-----------------------------------------------------" << endl;
    cout << "Reading data file " << _file_name << endl;
  }

  string file_line;

  // Parcourir le fichier pour rechercher les paramètres
  while (!data_file.eof())
  {
    getline(data_file, file_line);
    string proper_file_line = file_line;

    if (proper_file_line.find("xmin") != std::string::npos)
    {
      data_file >> _xmin; _if_xmin = true;
    }

    if (proper_file_line.find("xmax") != std::string::npos)
    {
      data_file >> _xmax; _if_xmax = true;
    }

    if (proper_file_line.find("hx") != std::string::npos)
    {
      data_file >> _hx; _if_hx = true;
    }

    if (proper_file_line.find("ymin") != std::string::npos)
    {
      data_file >> _ymin; _if_ymin = true;
    }

    if (proper_file_line.find("ymax") != std::string::npos)
    {
      data_file >> _ymax; _if_ymax = true;
    }

    if (proper_file_line.find("hy") != std::string::npos)
    {
      data_file >> _hy; _if_hy = true;
    }

    if (proper_file_line.find("t0") != std::string::npos)
    {
      data_file >> _t0; _if_t0 = true;
    }

    if (proper_file_line.find("tfinal") != std::string::npos)
    {
      data_file >> _tfinal; _if_tfinal = true;
    }

    if (proper_file_line.find("dt") != std::string::npos)
    {
      data_file >> _dt; _if_dt = true;
    }

    if (proper_file_line.find("sigma") != std::string::npos)
    {
      data_file >> _sigma; _if_sigma = true;
    }

    if (proper_file_line.find("scheme") != std::string::npos)
    {
      data_file >> _scheme; _if_scheme = true;
      if ((_scheme != "ExplicitEuler") && (_scheme != "ImplicitEuler"))
      {
        cout << "Only Explicit and Inplicit Euler are implemented." << endl;
        exit(0);
      }
    }

    if (proper_file_line.find("results") != std::string::npos)
    {
      data_file >> _results; _if_results = true;
    }

    if (proper_file_line.find("LeftBoundCond") != std::string::npos)
    {
      data_file >> _LBC; _if_LBC = true;
      if ((_LBC != "Dirichlet") && (_LBC != "Neumann"))
      {
        cout << "Only Dirichlet or Neumann boundary conditions are implemented." << endl;
        exit(0);
      }
    }

    if (proper_file_line.find("RightBoundCond") != std::string::npos)
    {
      data_file >> _RBC; _if_RBC = true;
      if ((_RBC != "Dirichlet") && (_RBC != "Neumann"))
      {
        cout << "Only Dirichlet or Neumann boundary conditions are implemented." << endl;
        exit(0);
      }
    }

    if (proper_file_line.find("DownBoundCond") != std::string::npos)
    {
      data_file >> _DBC; _if_DBC = true;
      if ((_DBC != "Dirichlet") && (_DBC != "Neumann"))
      {
        cout << "Only Dirichlet or Neumann boundary conditions are implemented." << endl;
        exit(0);
      }
    }

    if (proper_file_line.find("UpBoundCond") != std::string::npos)
    {
      data_file >> _UBC; _if_UBC = true;
      if ((_UBC != "Dirichlet") && (_UBC != "Neumann"))
      {
        cout << "Only Dirichlet or Neumann boundary conditions are implemented." << endl;
        exit(0);
      }
    }
  }
  // Initialisation par défaut des paramètres non fixés dans le fichier
  // Un message prévient l'utilisateur
  if (!_if_xmin)
  {
    cout << "-----------------------------------------------------" << endl;
    cout << "Beware - The default value (0.) is used for xmin." << endl;
    _xmin = 0.;
  }
  if (!_if_xmax)
  {
    cout << "-----------------------------------------------------" << endl;
    cout << "Beware - The default value (1.) is used for xmax." << endl;
    _xmax = 1.;
  }
  if (!_if_hx)
  {
    cout << "-----------------------------------------------------" << endl;
    cout << "Beware - The default value (0.01) is used for hx." << endl;
    _hx = 0.01;
  }
  if (!_if_ymin)
  {
    cout << "-----------------------------------------------------" << endl;
    cout << "Beware - The default value (0.) is used for ymin." << endl;
    _ymin = 0.;
  }
  if (!_if_ymax)
  {
    cout << "-----------------------------------------------------" << endl;
    cout << "Beware - The default value (1.) is used for ymax." << endl;
    _ymax = 1.;
  }
  if (!_if_hy)
  {
    cout << "-----------------------------------------------------" << endl;
    cout << "Beware - The default value (0.01) is used for hy." << endl;
    _hy = 0.01;
  }
  if (!_if_t0)
  {
    cout << "-----------------------------------------------------" << endl;
    cout << "Beware - The default value (0.) is used for t0." << endl;
    _t0 = 0.;
  }
  if (!_if_tfinal)
  {
    cout << "-----------------------------------------------------" << endl;
    cout << "Beware - The default value (0.1) is used for tfinal." << endl;
    _tfinal = 0.1;
  }
  if (!_if_dt)
  {
    cout << "-----------------------------------------------------" << endl;
    cout << "Beware - The default value (0.001) is used for dt." << endl;
    _dt = 0.001;
  }
  if (!_if_sigma)
  {
    cout << "-----------------------------------------------------" << endl;
    cout << "Beware - The default value (1.) is used for sigma." << endl;
    _sigma = 1.;
  }
  if (!_if_scheme)
  {
    cout << "-----------------------------------------------------" << endl;
    cout << "Beware - The default scheme (Implicit Euler scheme) is used." << endl;
    _scheme = "ImplicitEuler";
  }
  if (!_if_results)
  {
    cout << "-----------------------------------------------------" << endl;
    cout << "Beware - The default results folder name (results) is used." << endl;
    _results = "results";
  }
  if (!_if_LBC)
  {
    cout << "--------------------------------------------------" << endl;
    cout << "Beware - The default left BC is Dirichlet." << endl;
    _LBC = "Dirichlet";
  }
  if (!_if_RBC)
  {
    cout << "--------------------------------------------------" << endl;
    cout << "Beware - The default right BC is Dirichlet." << endl;
    _RBC = "Dirichlet";
  }
  if (!_if_DBC)
  {
    cout << "--------------------------------------------------" << endl;
    cout << "Beware - The default down BC is Dirichlet." << endl;
    _DBC = "Dirichlet";
  }
  if (!_if_UBC)
  {
    cout << "--------------------------------------------------" << endl;
    cout << "Beware - The default up BC is Dirichlet." << endl;
    _UBC = "Dirichlet";
  }


  cout << "--------------------------------------------------" << endl;
  cout << "-------------- Adapt dt, hx and hy ---------------" << endl;
  cout << "-------------- xmax = xmin + (Nx+1)*hx -----------" << endl;
  cout << "-------------- ymax = ymin + (Ny+1)*hy -----------" << endl;
  cout << "-------------- tfinal = t0 + nb_it*dt ------------" << endl;
  // Calcul de _Nx et adaptation de _dx pour que (xmax - xmin) = (Nx+1)*hx
  _Nx = int(ceil((_xmax-_xmin)/_hx)-1);
  _hx = (_xmax-_xmin)/(_Nx+1.);
  // Calcul de _Ny et adaptation de _dy pour que (ymax - ymin) = (Ny+1)*hy
  _Ny = int(ceil((_ymax-_ymin)/_hy)-1);
  _hy = (_ymax-_ymin)/(_Ny+1.);

  // Calcul du pas de temps en fonction de la CFL
  if (_scheme == "ExplicitEuler")
  {
    _dt = 0.95*pow(_hy,2)*pow(_hx,2)/(2*_sigma*(pow(_hx,2)+pow(_hy,2)));
    cout << "The time step is fixed with the CFL condition: dt = " << _dt << "." << endl;
  }

  // Calcul du nombre d'itérations en temps
  int nb_iterations = int(ceil((_tfinal-_t0)/_dt));
  // Adapter le pas de temps pour avoir _tfinal = _t0 + nb_iterations*_dt
  _dt = (_tfinal-_t0) / nb_iterations;
  cout << "--------------------------------------------------" << endl;
}

#define _DATA_FILE_CPP
#endif
