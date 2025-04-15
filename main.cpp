#include "Utils.hpp"
#include <iostream> // Per std::cerr
#include <string>   // Per std::string

using namespace std;


int main() {
    const string inputFile = "data.txt";
    const string outputFile = "result.txt";

    double S = 0.0;
    int n = 0;
    double* w = nullptr;
    double* r = nullptr;

    // Carico i dati in memoria
    if (!readData(inputFile, S, n, w, r)) {
        // stampa degli errori su readData
        delete[] w; 
        delete[] r;
        return 1;
    }

    // Calcolo il tasso di rendimento del portafoglio
    double portfolioRate = calculatePortfolioRateOfReturn(n, w, r);

    // Calcolo il valore finale del portafoglio
    double V = calculateFinalValue(S, portfolioRate);

    // Scrivo i risultati nel file
    if (!writeResults(outputFile, S, n, w, r, portfolioRate, V)) {
        // stampa degli errori su writeResults
        delete[] w;
        delete[] r;
        return 1;
    }

    // Dealloca la memoria allocata dinamicamente
    delete[] w;
    delete[] r;

    cout << "Operazione completata. Risultati salvati in " << outputFile << endl;

    return 0;
}
