#include <iostream>

#include "regression.hpp"
#include "TApplication.h"
#include "TGraphErrors.h"
#include "TCanvas.h"
#include "TLine.h"
#include "TAxis.h"

using namespace std;

int main(int argc, char** argv) {

    if(argc < 2) {
        cerr << "Use of program: " << argv[0] << " <datafile.txt> " << endl;
        exit(-1);
    }

    TApplication app ("app", 0, 0);

    const string filename = argv[1];

    vector<double> x;
    vector<double> y;
    vector<double> sig;

    Read(filename, x, y, sig);

    double delta = Delta(x, y, sig);
    double a = A(delta, x, y, sig);
    double b = B(delta, x, y, sig);
    double sig_a = sigA(delta, sig);
    double sig_b = sigB(delta, x, sig);
    double minx = *min_element(x.begin(), x.end());
    double maxx = *max_element(x.begin(), x.end());

    double sum = 0;

    for(unsigned int i = 0 ; i < x.size(); i++) {
        cout << "A = " << y[i]/x[i] << endl;
        sum += y[i]/x[i];
    }
    cout << "<A> = " << sum/x.size() << endl;

    cout << "A = "; 
    printWithUncertaintyScientific(a, sig_a);
    cout << " kg/C  \n" << endl;
    cout << "B = ";
    printWithUncertaintyScientific(b, sig_b);
    cout << "(T*m)^2 \n" << endl;
    cout << "e/m = ";
    printWithUncertaintyScientific(-1/a, (pow(1/a, 2))*sig_a);
    cout << " C/kg \n" << endl;

    TGraphErrors e_m;

    for(unsigned int i = 0; i < x.size(); i++) {
        e_m.SetPoint(i, x[i], y[i]);
        e_m.SetPointError(i, 0., sig[i]);
    }

    TLine regression{0.93*minx, a*0.93*minx+b, 1.015*maxx, a*1.015*maxx+b};

    TCanvas canv ("Linear regression e/m", "Linear regression e/m");

    canv.cd();

    e_m.GetXaxis()->SetRangeUser(280, 600);
    e_m.GetYaxis()->SetRangeUser(1E-09, 4E-09);
    e_m.SetMarkerSize(0.5);
    e_m.SetMarkerStyle(20);
    e_m.SetFillColor(0);
    e_m.SetLineWidth(1);

    regression.SetLineColor(kRed);
    regression.SetLineStyle(1);
    regression.SetLineWidth(1);

    e_m.SetTitle("Linear regression e/m");
    e_m.GetXaxis()->SetTitle("2#DeltaV_{i}  [V]");
    e_m.GetYaxis()->SetTitle("(R_{i}B_{i})^{2}   [(T*m)^{2}]");

    e_m.Draw("APE");
    regression.Draw("SAME");

    canv.Update();
    canv.SaveAs("Thomson.png");

    cout << "" << endl;

    app.Run();
}
