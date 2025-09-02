#include <iostream>
#include <cstdlib>
#include <vector>
#include <algorithm>

#include "TGraph.h"
#include "TH1F.h"
#include "TApplication.h"
#include "TCanvas.h"
#include "TAxis.h"
#include "TLine.h"

#include "funzioni.hpp"

int main(int argc , char** argv){

    if(argc < 2){
        cerr << "Use of program: ./mlk <Data_file.txt>" << endl;
        return 1;
    }

    TApplication app ("app", 0, 0);

    vector<double> charges;
    vector<double> errors;
    Read(argv[1], charges, errors);
    sort(charges.begin(), charges.end());

    double cmin = MinC(charges);
    // cout << "Valore della carica che minimizza lo scarto quadratico: q_min = " << cmin << endl;
    double stddev = sqrt(S_q(charges, cmin)/(charges.size()*(charges.size()-1)));

    double elec = - qMin(charges, cmin);
    double sist_err = sistsig(errors, elec); // Dovrebbe andare... Sperem. 
    double error_def = sqrt(pow(stddev, 2) + pow(sist_err, 2));

    cout << "i = " <<charges.size() << endl;
    cout << "e = "; 
    PrintWUncSc(elec, error_def);
    cout << "Errore sistematico = " << sist_err << endl;
    cout << "Errore casuale = " << stddev << endl;
    //  Magari farlo con le cifre giuste... C'è la funzione giusta in un altro esercizio. 
    // cout << "" << endl;
    // cout << "//================================================================================ " << endl;
    // cout << "//  L'errore qui calcolato è di tipo casuale, \n//  legato al calcolo del valore minimo di S(q) come valor medio.   " << endl;
    // cout << "//  Deve essere effettuata anche una stima \n//  dell'errore sistematico, da sommare in quadratura  " << endl;
    // cout << "//  con l'errore casuale per ottenere \n//  l'incertezza sulla misura di e. " << endl;
    // cout << "//================================================================================ " << endl;
    // cout << "" << endl;

    TGraph* Sq = DoGraphSq<double>(charges, 500);

    TLine* line= new TLine(-elec, S_q(charges, -elec), -elec, 9.);

    TCanvas c ("Square deviation", "Square deviation");

    c.cd();
    c.SetGridx();
    c.SetGridy();

    Sq->SetMarkerSize(0.35);
    Sq->SetMarkerStyle(20);
    Sq->SetFillColor(0);
    Sq->SetLineColor(kBlack);

    line->SetLineColor(7);
    line->SetLineStyle(2);
    line->SetLineWidth(3);

    Sq->SetTitle("S(q)");
    Sq->GetXaxis()->SetTitle("q [C]");
    Sq->GetYaxis()->SetTitle("S(q) [C^{2}]");

    line->Draw();
    Sq->Draw("APE");

    c.Update();
    c.SaveAs("Millikan.png");

    cout << "" << endl;

    app.Run();

}