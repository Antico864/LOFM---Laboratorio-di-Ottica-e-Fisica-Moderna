#include "funzioni.hpp"

using namespace std;

//==================================
//  Funzioni di acquisizione dati: 
//==================================

//Lettura dati da file: 
vector<double> Read(const string& filename){
    vector<double> v;
    ifstream inputFile(filename);
    if (!inputFile.is_open()) {
        throw runtime_error("Cannot open file: " + filename);
    }
    else{
        double val;
        while (inputFile >> val){
            v.push_back(val);
        }
    }

    inputFile.close();
    return v;
}

void Read(const string& filename, vector<double>& v1, vector<double>& v2){
    ifstream inputFile(filename);
    if (!inputFile.is_open()) {
        throw runtime_error("Cannot open file: " + filename);
    }
    else{
        double column1, column2;
        while (inputFile >> column1 >> column2){
            v1.push_back(column1);
            v2.push_back(column2);
        }
    }

    inputFile.close();
}

//==================================
//  Funzioni di calcolo: 
//==================================

//Media: 
double Avg(vector<double>& a) {
    double avg = 0;
    for (size_t i = 0; i < a.size(); ++i) {
        avg += (a[i] - avg) / (i + 1);
    }
    return avg;
}

//Approssimazione intera:
int kof(double a, double b){
    if (b == 0) {
        cout << "Errore: divisione per zero." << endl;
        return 0;
    }
    int k = static_cast<int>(round(a/b)+0.5);
    return (k == 0) ? 1 : k;  // Ritorna 1 invece di zero
}

//Errore sistematico:
double sistsig(vector<double>& s, double x) {
    double sum2 = 0.;
    for(unsigned int i = 0; i < s.size(); i++) {
        sum2 += pow((s[i]/kof(s[i], x)), 2);
    }
    return sqrt(sum2)/s.size();
}

//Scarto quadratico: 
double S_q(vector<double> a , double c){
    double Sq = 0.;
    for(int i = 0 ; i < a.size() ; i++){
            //Calcolo lo scarto quadratico:
        if(kof( a[i] , c ) != 0){
            int k = kof(a[i], c);
            Sq += pow((a[i]/k) - c , 2);
        }
        else{ 
            cout << "Error: division by zero" << endl;
            exit(11);
        }
    }
    return Sq;
}

// Minimo sulle cariche: La funzione riempie i vettori e al tempo stesso cerca il valore minimo delle cariche. 
double MinC(vector<double>& q) {
    double min_image = S_q(q, 1.5E-19);
    double c_0 = 0.;

    for(double c = 1.5E-19 ; c < 1.7E-19 ; c+=1E-22){
        double image = S_q( q , c ); //  Calcola il valore dello scarto quadratico;
        if(image < min_image) { //  Controllo sul minimo di carica: 
            min_image = image;
            c_0 = c;
        }
    }
    return c_0;
}

double qMin(vector<double>& q, double xmin) {
    double sum = 0.;
    for(unsigned int k = 0; k < q.size(); k++) {
        sum += q[k]/kof(q[k], xmin);
    }
    double c = sum/q.size();
    return c;
}

void PrintWUncSc(double value, double uncertainty) {
    // Calcolare l'ordine di grandezza dell'incertezza
    int exponent_unc = floor(log10(abs(uncertainty))); // Esponente della notazione scientifica per l'incertezza

    // Arrotondare l'incertezza alla seconda cifra significativa
    double rounded_unc = round(uncertainty * pow(10, -exponent_unc + 1)) * pow(10, exponent_unc - 1);

    // Determinare l'ordine di grandezza del valore
    int exponent_val = exponent_unc;

    // Arrotondare il valore alla stessa precisione dell'incertezza
    double rounded_val = round(value * pow(10, -exponent_val + 1)) * pow(10, exponent_val - 1);

    // Stampare il valore e l'incertezza in notazione scientifica
    cout << scientific << setprecision(3) << rounded_val << " ± "
         << scientific << setprecision(1) << rounded_unc << endl;
}
