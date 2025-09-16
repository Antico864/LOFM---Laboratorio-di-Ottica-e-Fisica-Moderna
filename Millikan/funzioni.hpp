#ifndef FUNZIONI_HPP
#define FUNZIONI_HPP

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <stdexcept>
#include <numeric>

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
vector<double> Read(const string& filename);

//Lettura di dati ed errori:
void Read(const string& filename, vector<double>& v1, vector<double>& v2);

///////////////////////////////////////////////
//
//
//  Funzioni per il calcolo: 
//
//
///////////////////////////////////////////////

//Media: 
double Avg(vector<double>& a);

//Errore sistematico (serve che i dati siano stato di carica  --  incertezza nel file .txt):
double sistsig(vector<double>& s, double x);

//Approssimazione intera:
int kof(double a, double b);

//Scarto quadratico: 
double S_q(vector<double> a , double c);

//Minimo sulle cariche:
double MinC(vector<double>& a);

//Minimo sulle cariche, secondo la dispensa. 
//xmin gli serve per capire quanto vale k_i:
double qMin(vector<double>& q, double xmin);

//Stampa a video con taglio cifre significative: 
void PrintWUncSc(double value, double uncertainty);

///////////////////////////////////////////////
//
//
// Funzioni per riempimento/visualizzazione: 
//
//
///////////////////////////////////////////////


//Grafico cartesiano bidimensionale: 
template<typename T> TGraph* DoGraphSq(const vector<double>& a , int n){

    if(n > 2000){
        cout << "Errore: numero di punti nel grafico troppo elevato. " << endl;
        exit(2);
    }

    if(n < 100){
        cout << "Errore: numero di punti nel grafico troppo basso. " << endl;
        exit(2);
    }
    TGraph* graph = new TGraph;
    unsigned int ind = 0;
    for(double c = 1.5E-19 ; c < 1.7E-19 ; c+=1E-23){
        double image = S_q( a , c ); //  Calcola il valore dello scarto quadratico;
        graph->SetPoint(ind , c , image); //  Imposto il punto di graph:
        ind++;
    }
    return graph;
};

#endif // FUNZIONI_HPP
