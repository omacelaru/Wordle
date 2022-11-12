#include <iostream>
#include <cstring>
#include <fstream>
#include <cmath>
#include <ctime>

using namespace std;
const int NUMAR_LITERE = 26;
const int NUMAR_CUVINTE = 11456;
const int NUMAR_LITERE_CUVANT = 6;


int index_random, numar_incercari;
char cuvant[NUMAR_CUVINTE][NUMAR_LITERE_CUVANT];
bool gasit_solutie = false;
char cuvant_citit[NUMAR_LITERE];

//Cautare binara
int cautare_binara(char cuv[], long l, long r) {
    if (l > r) return -1;
    long m = l + (r - l) / 2;
    if (stricmp(cuv, cuvant[m]) == 0)
        return 1;
    else if (stricmp(cuv, cuvant[m]) > 0)
        return cautare_binara(cuv, m + 1, r);
    else
        return cautare_binara(cuv, l, m - 1);
}
//sfarsit Cautare binara

//Citire baza de date
void citire() {
    ifstream f("cuvinte_wordle.txt");
    for (int i = 0; i < NUMAR_CUVINTE; i++) {
        f >> cuvant[i];
    }
    f.close();
}

//Alegere cuvant
void cuvant_random() {
    srand(time(0));
    for (int i = 0; i < 10; i++)
        index_random = rand() % 11454;
}

//Verifiacre cuvant
void verificare(char cuvant_gasit[]) {
    cout << cuvant_gasit << endl;
    if (strcmp(cuvant[index_random], cuvant_gasit) == 0) {
        gasit_solutie = true;
        for (int i = 0; i < 5; i++)
            cout << cuvant_gasit[i] << " 1" << endl;
        cout << endl << "Felicitari ai ghicit cuvantul " << cuvant[index_random] << " din " << numar_incercari + 1
             << " incercari"
             << endl;
    } else {
        for (int i = 0; i < 5; i++) {
            if (cuvant[index_random][i] == cuvant_gasit[i]) {
                cout << cuvant_gasit[i] << " 1" << endl;
            } else {
                int litera_buna = 0;
                for (int j = 0; j < 6 && !litera_buna; j++)
                    if (cuvant[index_random][j] == cuvant_gasit[i])
                        litera_buna = 1;
                if (litera_buna == 1) {
                    cout << cuvant_gasit[i] << " 0" << endl;
                } else {
                    cout << cuvant_gasit[i] << " -1" << endl;
                }
            }
        }
    }
    cout << endl;
    numar_incercari++;
}

//Regulile jocului
void reguli() {
    cout << "Am ales un cuvant! Incearca sa-l ghicesti! Nu uita sa folosesti litere mari!" << endl;
    cout << "Pentru fiecare incercare iti voi da detalii despre literele folosite:" << endl;
    cout << "1 - litera apartine cuvantului ales si este pe pozitia corecta" << endl;
    cout << "0 - litera apartine cuvantului ales si NU este pe pozitia corecta" << endl;
    cout << "-1 - litera NU apartine cuvantului ales" << endl;
    cout << cuvant[index_random] << endl;
}

//Citirea de la tastatura
void citire_cuvant() {
    bool cuvant_nepermis = false;
    do {
        cin.get(cuvant_citit, 20);
        cin.get();
        if (strlen(cuvant_citit) < 1) {
            cout << "Ai tastat un carcater nepermis.. ai distrus jocul" << endl;
            cuvant_nepermis = true;
            break;
        }

        if (strlen(cuvant_citit) == 5) {
            int gasit_in_db = cautare_binara(cuvant_citit, 0, 11454);

            if (gasit_in_db == 1)
                break;
            else
                cout << "Nu ai introdus un cuvant din baza de date!Incearca din nou!" << endl;
        } else
            cout << "Nu ai introdus un cuvant de 5 litere.Incearca din nou!" << endl;
    } while (1);
    if (cuvant_nepermis == true)
        exit(0);
    for (int i = 0; i < strlen(cuvant_citit); i++)
        if (cuvant_citit[i] >= 'a' && cuvant_citit[i] <= 'z')
            cuvant_citit[i] -= 32;
}

int main() {
    citire();
    cuvant_random();
    reguli();
    do {
        citire_cuvant();
        verificare(cuvant_citit);
    } while (!gasit_solutie);
    return 0;
}
