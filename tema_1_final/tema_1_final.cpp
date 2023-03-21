#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

struct Tranzitie {
    int nod;
    char simbol;
    int nodViitor;
};

class Automat {
private:
    int nodInitial;
    vector<int> noduriFinale;
    vector<Tranzitie> tranzitii;

public:
    Automat() {}

    void loadDfaFromFile(string filename) {
        ifstream file(filename);

        file >> nodInitial;

        int nrNoduriFinale;
        file >> nrNoduriFinale;

        for (int i = 0; i < nrNoduriFinale; i++) {
            int nod;
            file >> nod;
            noduriFinale.push_back(nod);
        }

        int nrTranzii;
        file >> nrTranzii;

        for (int i = 0; i < nrTranzii; i++) {
            int from, to;
            char symbol;
            file >> from >> symbol >> to;
            tranzitii.push_back({ from, symbol, to });
        }

        file.close();
    }

    void printDFA() {
        cout << this->nodInitial << endl;
        for (int state : noduriFinale) {
            cout << state << " ";
        }
        cout << endl;
        for (Tranzitie t : tranzitii) {
            cout << t.nod << t.simbol << t.nodViitor << " ";
        }
        cout << endl;
    }

    bool accepts(string word) {
        int nodCurent = nodInitial;

        for (char c : word) {
            bool tranzitieGasita = false;

            for (Tranzitie t : tranzitii) {
                if (t.nod == nodCurent && t.simbol == c) {
                    nodCurent = t.nodViitor;
                    tranzitieGasita = true;
                    break;
                }
            }

            if (!tranzitieGasita) {
                return false;
            }
        }

        for (int nod : noduriFinale) {
            if (nodCurent == nod) {
                return true;
            }
        }

        return false;
    }
};

int main() {
    Automat dfa;
    string numeFisier, cuvant;

    cout << "Enter filename: ";
    cin >> numeFisier;

    dfa.loadDfaFromFile(numeFisier);
    // dfa.printDFA();

    while (true) {
        cout << "Enter word to check (or type 9999 to exit): ";
        cin >> cuvant;

        if (cuvant == "9999") {
            break;
        }

        if (dfa.accepts(cuvant)) {
            cout << "Accepted" << endl;
        }
        else {
            cout << "NOT accepted" << endl;
        }
    }
    return 0;
}
