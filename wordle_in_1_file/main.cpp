#include <iostream>
#include <cstring>
#include <fstream>
#include <cmath>
#include <ctime>
//5.44124 medie
using namespace std;
const int NUMAR_LITERE = 26;
const int NUMAR_LITERA = 2;
const int NUMAR_CUVINTE = 11456;
const int NUMAR_LITERE_CUVANT = 6;
const int COMBINARI_MAX = 65781;
const int COMBINARI_K = 5;
const int PRODUS_CAR_CARD = 5;
const int PRODUS_CAR_MAX = 3150;

int stiva_combinari[COMBINARI_MAX], a, combinari_n = 26, numar_solutie_combinari, solutie_combinari[COMBINARI_MAX][NUMAR_LITERE_CUVANT];
int stiva_produs_car[PRODUS_CAR_MAX], b, numar_solutie_produs_car, solutie_produs_car[PRODUS_CAR_MAX][NUMAR_LITERE_CUVANT], primmul_produs_car = 1;
int vector_corect[NUMAR_LITERE_CUVANT], vector_incorect[NUMAR_LITERE_CUVANT][NUMAR_LITERE], numar_col_incorect[NUMAR_LITERE_CUVANT];
int index_random, numar_solutii, index_cuvant, numar_incercari;
int vector_frecventa[NUMAR_LITERE];
char cuvant[NUMAR_CUVINTE][NUMAR_LITERE_CUVANT], litera_din_combinari[COMBINARI_MAX][NUMAR_LITERE_CUVANT], cuvant_din_produs_car[NUMAR_LITERE_CUVANT], sir_de_solutii[PRODUS_CAR_MAX][NUMAR_LITERE_CUVANT];
bool gasit_cuvant = false, gasit_solutie = false;
ofstream gout("solutie.txt");

struct alfa {
    float informatie;
    char lit[NUMAR_LITERA];
} litera[NUMAR_LITERE];

//Quick sort
int poz(int l, int r, alfa ax[]) {
    int i = l, j = r, i1 = 0, j1 = -1, c;
    alfa aux;
    while (i < j) {
        if (ax[i].informatie < ax[j].informatie) {
            aux = ax[j];
            ax[j] = ax[i];
            ax[i] = aux;
            c = i1;
            i1 = -j1;
            j1 = -c;
        }
        i = i + i1;
        j = j + j1;
    }
    return i;
}

void quick(int l, int r) {
    int k;
    if (l < r) {
        k = poz(l, r, litera);
        quick(l, k - 1);
        quick(k + 1, r);
    }
}
//sfarsit Quick sort

//Cautare binara
int cautare_binara(char cuv[], long l, long r) {
    if (l > r) return -1;
    long m = l + (r - l) / 2;
    if (strcmp(cuv, cuvant[m]) == 0)
        return 1;
    else if (strcmp(cuv, cuvant[m]) > 0)
        return cautare_binara(cuv, m + 1, r);
    else
        return cautare_binara(cuv, l, m - 1);
}
//sfarsit Cautare binara

//Combinari Backtraking
void combinari_initializare() {
    stiva_combinari[a] = 0;
}

int combinari_succesor() {
    if (stiva_combinari[a] < combinari_n) {
        stiva_combinari[a]++;
        return 1;
    } else
        return 0;
}

int combinari_valid() {
    int i;
    for (i = 1; i < a; i++)
        if (stiva_combinari[a] == stiva_combinari[i])
            return 0;
    if (a > 1 && stiva_combinari[a] <= stiva_combinari[a - 1])
        return 0;
    return 1;
}

int combinari_solutie() {
    return a == COMBINARI_K;
}

void combinari_back() {
    int AScombinari;
    a = 1;
    combinari_initializare();
    while (a > 0) {
        do {
        } while ((AScombinari = combinari_succesor()) && !combinari_valid());
        if (AScombinari)
            if (combinari_solutie()) {
                solutie_combinari[numar_solutie_combinari][0] = stiva_combinari[1];
                solutie_combinari[numar_solutie_combinari][1] = stiva_combinari[2];
                solutie_combinari[numar_solutie_combinari][2] = stiva_combinari[3];
                solutie_combinari[numar_solutie_combinari][3] = stiva_combinari[4];
                solutie_combinari[numar_solutie_combinari][4] = stiva_combinari[5];
                numar_solutie_combinari++;
            } else {
                a++;
                combinari_initializare();
            }
        else
            a--;
    }
}
//sfarsit Combinari Backtraking

//Produs cartezian Backtraking
void produs_car_initializare() {
    stiva_produs_car[b] = 0;
}

int produs_car_succesor() {
    if (stiva_produs_car[b] < PRODUS_CAR_CARD) {
        stiva_produs_car[b]++;
        return 1;
    } else
        return 0;
}

int produs_car_valid() {

    int x, v[26], nr = 0, j, i, l;
    if (primmul_produs_car == 1) {
        for (i = 0; i < b; i++)
            if (stiva_produs_car[i] == stiva_produs_car[b])
                return 0;
    }

    for (i = 0; i < 5; i++)
        if (vector_corect[i] != -1 && b == i + 1) {
            for (j = 0; j < 5; j++) {
                if (litera_din_combinari[j][0] == char('A' + vector_corect[i] - 1))
                    x = j;
            }
            if (stiva_produs_car[b] != x + 1)
                return 0;
        }

    for (i = 0; i < 5; i++) {
        if (vector_incorect[i][0] != -1 && b == i + 1) {
            nr = 0;
            for (j = 0; j < numar_col_incorect[i]; j++) {
                for (l = 0; l < 5; l++)
                    if (litera_din_combinari[l][0] == char('A' + vector_incorect[i][j] - 1)) {
                        v[j] = l;
                        nr++;
                    }
            }
            for (int w = 0; w < nr; w++)
                if (stiva_produs_car[b] == v[w] + 1)
                    return 0;
        }

    }
    return 1;
}

int produs_car_solutie() {
    return b == PRODUS_CAR_CARD;
}

void produs_car_back() {
    int AS;
    b = 1;
    produs_car_initializare();
    while (b > 0) {
        do {

        } while ((AS = produs_car_succesor()) && !produs_car_valid());
        if (AS)
            if (produs_car_solutie()) {
                solutie_produs_car[numar_solutie_produs_car][0] = stiva_produs_car[1];
                solutie_produs_car[numar_solutie_produs_car][1] = stiva_produs_car[2];
                solutie_produs_car[numar_solutie_produs_car][2] = stiva_produs_car[3];
                solutie_produs_car[numar_solutie_produs_car][3] = stiva_produs_car[4];
                solutie_produs_car[numar_solutie_produs_car][4] = stiva_produs_car[5];
                numar_solutie_produs_car++;
            } else {
                b++;
                produs_car_initializare();
            }
        else
            b--;
    }
}
//sfarsit Produs cartezian Backtraking

//Initializari
void initializare() {
    int i;
    for (i = 0; i < NUMAR_LITERE; i++)
        vector_frecventa[i] = 0;
    for (i = 0; i < 5; i++)
        vector_corect[i] = -1;
    for (i = 0; i < 5; i++)
        vector_incorect[i][0] = -1;
    for (i = 0; i < 5; i++)
        numar_col_incorect[i] = 0;
}

//Citire baza de date
void citire() {
    ifstream f("cuvinte_wordle.txt");
    for (int i = 0; i < NUMAR_CUVINTE; i++) {
        f >> cuvant[i];
        for (int j = 0; j < strlen(cuvant[i]); j++)
            vector_frecventa[cuvant[i][j] - 'A']++;
    }
    f.close();
}

//Alegere cuvant
void cuvant_random() {
    srand(time(0));
    for (int i = 0; i < 10; i++)
        index_random = rand() % 11454;
    gout << "\n" << cuvant[index_random] << ",";
}

//Calcul pentru informatia fiecarei litere
void calc_informatie() {
    ofstream g("informatie.txt");
    int i;
    for (i = 0; i < 26; i++) {
        litera[i].informatie = log(vector_frecventa[i]) / log(2);
        litera[i].lit[0] = char('A' + i);
        litera[i].lit[1] = '\0';
        g << litera[i].lit[0] << " " << litera[i].informatie << endl;
    }
    g.close();
}

//Initializari pentru generarea cuvantului
void initializare_generare() {
    int i, j;
    for (i = 0; i < numar_solutie_combinari; i++)
        for (j = 0; j < 5; j++)
            solutie_combinari[i][j] = -1;
    numar_solutie_combinari = 0;
    gasit_cuvant = 0;
    combinari_n = 0;
    for (i = 0; i < 26; i++)
        if (litera[i].informatie != -1)
            combinari_n++;
}


//Generare cuvant
int generare() {
    initializare_generare();
    combinari_back();
    quick(0, 25);
    for (int i = 0; i < numar_solutie_combinari && !gasit_cuvant; i++) {
        for (int j = 0; j < 5; j++) {
            litera_din_combinari[j][0] = litera[solutie_combinari[i][j] - 1].lit[0];
            litera_din_combinari[j][1] = '\0';
        }
        numar_solutie_produs_car = 0;
        produs_car_back();
        numar_solutii = 0;
        for (int k = 0; k < numar_solutie_produs_car; k++) {
            cuvant_din_produs_car[0] = litera_din_combinari[solutie_produs_car[k][0] - 1][0];
            cuvant_din_produs_car[1] = litera_din_combinari[solutie_produs_car[k][1] - 1][0];
            cuvant_din_produs_car[2] = litera_din_combinari[solutie_produs_car[k][2] - 1][0];
            cuvant_din_produs_car[3] = litera_din_combinari[solutie_produs_car[k][3] - 1][0];
            cuvant_din_produs_car[4] = litera_din_combinari[solutie_produs_car[k][4] - 1][0];
            cuvant_din_produs_car[5] = '\0';

            if (cautare_binara(cuvant_din_produs_car, 0, 11454) == 1) {
                strcpy(sir_de_solutii[numar_solutii++], cuvant_din_produs_car);
                gasit_cuvant = 1;
            }

        }
    }
    primmul_produs_car = 0;
    int i = 0, j, l, stg, len, lmax, car, lit, poz1 = 0, poz2 = numar_solutii - 1;
    for (int re = 0; re < 5 && poz1 < poz2; re++) {
        i = poz1;
        j = poz2;
        lit = re;
        lmax = -1;
        do {
            car = int(sir_de_solutii[i][lit]);
            stg = i + 1;
            while (stg <= j && car == int(sir_de_solutii[stg][lit]))
                stg++;
            l = stg - i;
            i = stg;
            if (lmax < l) {
                lmax = l;
                poz2 = stg - 1;
                poz1 = stg - l;
            }
        } while (i < j);
    }
    numar_solutii = 0;
    return i;
}

//Verifiacre cuvant
void verificare() {
    char cuvant_gasit[NUMAR_LITERE_CUVANT];
    strcpy(cuvant_gasit, sir_de_solutii[index_cuvant]);
    cuvant_gasit[5] = '\0';
    cout << cuvant_gasit << endl;
    gout << cuvant_gasit << ",";

    if (strcmp(cuvant[index_random], cuvant_gasit) == 0) {
        gasit_solutie = true;
        for (int i = 0; i < 5; i++)
            cout << cuvant_gasit[i] << " 1" << endl;
        cout << endl << "Bravo MIE! Am ghicit cuvantul " << cuvant[index_random] << " din " << numar_incercari + 1
             << " incercari"
             << endl;
    } else {
        for (int i = 0; i < 5; i++) {
            if (cuvant[index_random][i] == cuvant_gasit[i]) {
                cout << cuvant_gasit[i] << " 1" << endl;

                vector_corect[i] = int(cuvant_gasit[i]) - 'A' + 1;
                for (int r = 0; r < 26; r++)
                    if (litera[r].lit[0] == cuvant_gasit[i])
                        litera[r].informatie = 16;
            } else {
                int litera_buna = 0;
                for (int j = 0; j < 6 && !litera_buna; j++)
                    if (cuvant[index_random][j] == cuvant_gasit[i])
                        litera_buna = 1;
                if (litera_buna == 1) {
                    cout << cuvant_gasit[i] << " 0" << endl;


                    vector_incorect[i][numar_col_incorect[i]] = int(cuvant_gasit[i]) - 'A' + 1;
                    numar_col_incorect[i]++;
                    for (int r = 0; r < 26; r++)
                        if (litera[r].lit[0] == cuvant_gasit[i] && litera[r].lit[0] != 16)
                            litera[r].informatie = 15;
                } else {
                    cout << cuvant_gasit[i] << " -1" << endl;
                    for (int r = 0; r < 26; r++)
                        if (litera[r].lit[0] == cuvant_gasit[i])
                            litera[r].informatie = -1;
                }
            }
        }
    }
    cout << endl;
    numar_incercari++;
}

int main() {
    initializare();
    citire();
    cuvant_random();
    calc_informatie();
    do {
        index_cuvant = generare();
        verificare();
    } while (!gasit_solutie);
    return 0;
}
