#pragma once

#include <iostream>
#include <fstream>
#include <string>

// Funzione per leggere i dati dal file di input
// Restituisce true se la lettura ha successo, false altrimenti.
// Alloca dinamicamente la memoria per w e r.
bool readData(const std::string& filename, double& S, int& n, double*& w, double*& r);

// Funzione per calcolare il tasso di rendimento del portafoglio
double calculatePortfolioRateOfReturn(int n, const double* w, const double* r);

// Funzione per calcolare il valore finale del portafoglio
double calculateFinalValue(double S, double portfolioRate);

// Funzione per scrivere i risultati nel file di output
// Restituisce true se la scrittura ha successo, false altrimenti.
bool writeResults(const std::string& filename, double S, int n, const double* w, const double* r, double portfolioRate, double V);
