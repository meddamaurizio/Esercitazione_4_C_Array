#include "Utils.hpp"

#include <fstream>
#include <iomanip>
#include <string>
#include <iostream>

using namespace std;

// Funzione per leggere i dati dal file
bool readData(const string& filename, double& S, int& n, double*& w, double*& r) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Errore: Impossibile aprire il file di input: " << filename << endl;
        return false;
    }

    char separator; // Per leggere i caratteri separatori ';' e l'identificatore

    // S
    if (!(file >> separator >> separator >> S)) {
        cerr << "Errore: Impossibile leggere S." << endl;
        file.close();
        return false;
    }

    // n
    if (!(file >> separator >> separator >> n)) {
        cerr << "Errore durante la lettura di n." << endl;
        file.close();
        return false;
    }

    // Sanità di n
    if (n <= 0) {
        cerr << "Errore: n deve essere un intero positivo." << endl;
        file.close();
        return false;
    }

    // Leggi l'intestazione "w;r"
    if (!(file >> separator >> separator >> separator)) {
         cerr << "Errore durante la lettura dell'intestazione w;r." << endl;
         file.close();
         return false;
    }

    // Alloca memoria per gli array w e r
    w = new double[n];
    r = new double[n];

    // Leggi i valori di w e r
    for (int i = 0; i < n; ++i) {

        if (!(file >> w[i] >> separator >> r[i])) {
            cerr << "Errore: lettura dei dati w/r (linea " << i + 4 << " del file)." << endl;
            delete[] w;
            delete[] r;
            file.close();
            return false;
        }
    }

    file.close();
    return true;
}

double calculatePortfolioRateOfReturn(int n, const double* w, const double* r) {
    double portfolioRate = 0.0;
    for (int i = 0; i < n; ++i) {
        portfolioRate += w[i] * r[i];
    }
    return portfolioRate;
}

double calculateFinalValue(double S, double portfolioRate) {
    return S * (1.0 + portfolioRate);
}

void printArray(ostream& os, const char* name, const double* arr, int n) {
    os << name << " = [";
    for (int i = 0; i < n; ++i) {
        os << " " << arr[i];
    }
    os << " ]";
}

bool writeResults(const string& filename, double S, int n, const double* w, const double* r, double portfolioRate, double V) {
    ofstream file(filename);
    if (!file.is_open()) {
        cerr << "Errore: Impossibile creare/aprire il file di output: " << filename << endl;
        return false;
    }

    // Imposta la precisione per S e V
    file << fixed << setprecision(2);
    file << "S = " << S << ", n = " << n << endl;

    // Stampa array
    printArray(file, "w", w, n);
    file << endl;
    printArray(file, "r", r, n);
    file << endl;

    // Stampa r (modifica della precisione come nell'esempio)
    file << "Rate of return of the portfolio: " << fixed << setprecision(4) << portfolioRate << endl;

    // Stampa V (reimposto la precisione a 2 decimali fissi)
    file << "V: " << fixed << setprecision(2) << V << endl;

    file.close();
    return true;
}
