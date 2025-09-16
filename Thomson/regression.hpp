#ifndef REGRESSION_HPP
#define REGRESSION_HPP

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <stdexcept>
#include <numeric>
#include <iomanip>

#include "TH1F.h"
#include "TApplication.h"
#include "TCanvas.h"
#include "TGraph.h"

using namespace std;


///////////////////////////////////////////////
//
//
//  Funzioni di acquisizione dati: 
//
//
///////////////////////////////////////////////

//Lettura dati da file: 
void Read(const string& filename, vector<double>& v1, vector<double>& v2, vector<double>& v3);

///////////////////////////////////////////////
//
//
//  Funzioni per il calcolo: 
//
//
///////////////////////////////////////////////

//Calcolo del Delta (pesata): 
double Delta(vector<double>& , vector<double>& , vector<double>&);

//Calcolo del coefficiente angolare A (pesata):
double A(double, vector<double>&, vector<double>&, vector<double>&);

//Errore su A:
double sigA(double, vector<double>&);

//Calcolo dell'intercetta B (pesata):
double B(double, vector<double>&, vector<double>&, vector<double>&);

//Errore su B:
double sigB(double, vector<double>&, vector<double>&);

////////////////////////////////////////
//
//  Funzioni di visualizzazione: 
//
////////////////////////////////////////

void printWithUncertaintyScientific(double , double);

#endif // REGRESSION_HPP
