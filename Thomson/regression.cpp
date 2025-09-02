#include "regression.hpp"

using namespace std;

//==================================
//  Funzioni di acquisizione dati: 
//==================================

//Lettura x, y, errore sulle y da file: 
void Read(const string& filename, vector<double>& v1, vector<double>& v2, vector<double>& v3){
    ifstream inputFile(filename);
    if (!inputFile.is_open()) {
        throw runtime_error("Cannot open file: " + filename);
    }
    else{
        double column1, column2, column3;
        while (inputFile >> column1 >> column2 >> column3){
            v1.push_back(column1);
            v2.push_back(column2);
            v3.push_back(column3);
        }
    }

    inputFile.close();
}

//==================================
//  Funzioni di calcolo: 
//==================================

//Calcolo del Delta (pesata):
double Delta(vector<double>& x, vector<double>& y, vector<double>& sig) {
    
    if(x.size() != y.size()) {
        cerr << "Error: vectors must have equal size. x, y. " << endl;
        exit(-1);
    }
    if(x.size() != sig.size()) {
        cerr << "Error: vectors must have equal size. x, sig.  " << endl;
        exit(-1);
    }
    if(y.size() != sig.size()) {
        cerr << "Error: vectors must have equal size. y, sig.  " << endl;
        exit(-1);
    }
    double t1 = 0;
    double t2 = 0;
    double t3 = 0;

    for(unsigned int i = 0; i < x.size(); i++) {
        t1 += pow(1/sig[i], 2);
        t2 += pow(x[i]/sig[i], 2);
        t3 += x[i]/(sig[i]*sig[i]);
    }

    //  cout << "Delta: somma 1/sigma_i^2 = " << t1 << endl;
    //  cout << "Delta: somma x_i^2/sigma_i^2 = " << t2 << endl;
    //  cout << "Delta: (somma x_i/sigma_i^2)^2 = " << t3*t3 << endl;

    //  cout << "Delta = " << t1*t2 - pow(t3, 2) << endl;

    return t1*t2 - pow(t3, 2);
}

//Calcolo del coefficiente angolare a (pesata):
double A(double Delta, vector<double>& x, vector<double>& y, vector<double>& sig) {

    if(x.size() != y.size()) {
        cerr << "Error: vectors must have equal size. x, y. " << endl;
        exit(-1);
    }
    if(x.size() != sig.size()) {
        cerr << "Error: vectors must have equal size. x, sig.  " << endl;
        exit(-1);
    }
    if(y.size() != sig.size()) {
        cerr << "Error: vectors must have equal size. y, sig.  " << endl;
        exit(-1);
    }

    double t1 = 0;
    double t2 = 0;
    double t3 = 0;
    double t4 = 0;

    for(unsigned int i = 0; i < x.size(); i++) {
        t1 += pow(1/sig[i], 2);
        t2 += (x[i]*y[i])/pow(sig[i], 2);
        t3 += x[i]/pow(sig[i], 2);
        t4 += y[i]/pow(sig[i], 2);
    }

    //  cout << "A: somma 1/sigma_i^2 = " << t1 << endl;
    //  cout << "A: somma x_i*y_i/sigma_i^2 = " << t2 << endl;
    //  cout << "A: somma x_i/sigma_i^2 = " << t3 << endl;
    //  cout << "A: somma y_i/sigma_i^2 = " << t4 << endl;


    return (t1*t2 - t3*t4)/Delta;
}

//Errore su A:
double sigA(double Delta, vector<double>& sig) {

    double t = 0;

    for(unsigned int i = 0; i < sig.size(); i++) {
        t += pow(1/sig[i], 2);
    }

    return sqrt(t/Delta);
}


//Calcolo dell'intercetta b (pesata):
double B(double Delta, vector<double>& x, vector<double>& y, vector<double>& sig) {

    if(x.size() != y.size()) {
        cerr << "Error: vectors must have equal size. x, y. " << endl;
        exit(-1);
    }
    if(x.size() != sig.size()) {
        cerr << "Error: vectors must have equal size. x, sig.  " << endl;
        exit(-1);
    }
    if(y.size() != sig.size()) {
        cerr << "Error: vectors must have equal size. y, sig.  " << endl;
        exit(-1);
    }

    double t1 = 0;
    double t2 = 0;
    double t3 = 0;
    double t4 = 0;

    for(unsigned int i = 0; i < x.size(); i++) {
        t1 += pow(x[i]/sig[i], 2);
        t2 += y[i]/pow(sig[i], 2);
        t3 += x[i]/pow(sig[i], 2);
        t4 += (x[i]*y[i])/pow(sig[i], 2);
    }

    //  cout << "B: somma x_i^2/sigma_i^2 = " << t1 << endl;
    //  cout << "B: somma y_i/sigma_i^2 = " << t2 << endl;
    //  cout << "B: somma x_i/sigma_i^2 = " << t3 << endl;
    //  cout << "B: somma x_i*y_i/sigma_i^2 = " << t4 << endl;

    return (t1*t2 - t3*t4)/Delta;
}

//Errore su B:
double sigB(double Delta, vector<double>& x, vector<double>& sig) {

    if(x.size() != sig.size()) {
        cerr << "Error: vectors must have equal size. sigB. " << endl;
        exit(-1);
    }

    double t = 0;

    for(unsigned int i = 0; i < x.size(); i++) {
        t += pow(x[i]/sig[i], 2);
    }

    return sqrt(t/Delta);
}

//==================================
//  Funzioni di visualizzazione: 
//==================================

void printWithUncertaintyScientific(double A, double sigma_A) {
    // Calcola l'ordine di grandezza di sigma_A
    int order = static_cast<int>(floor(log10(sigma_A))); 

    // Arrotonda sigma_A alle prime due cifre significative
    double rounded_sigma_A = round(sigma_A / pow(10, order - 1)) * pow(10, order - 1);

    // Calcola il numero di cifre decimali richieste
    int decimals = -(order - 1);  // Numero di decimali significativi

    // Arrotonda A alla precisione di sigma_A
    double rounded_A = round(A * pow(10, decimals)) / pow(10, decimals);

    // Stampa il risultato in notazione scientifica
    cout << scientific << setprecision(2)
        << rounded_A << " ± " << rounded_sigma_A;
}
