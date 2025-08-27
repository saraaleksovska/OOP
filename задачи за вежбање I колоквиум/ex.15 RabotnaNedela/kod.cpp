#include <iostream>
#define NEDELI 4
#define DENOVI 5
using namespace std;

struct RabotnaNedela {
    int casovi[DENOVI];
    int brNedela;
};
struct Rabotnik {
    char ime[50];
    RabotnaNedela nedeli[NEDELI];
};
typedef struct Rabotnik R;

int rabotniCasovi(int *casovi, int brDenovi) { //функција за пресметување на вкупно работни часа во една недела
    int vkupno = 0;
    for (int i = 0; i < brDenovi; i++) {
        vkupno += casovi[i];
    }
    return vkupno;
}

int maxNedela(R *r) {
    int max = 0; //број на неделата со најмногу работни часа
    int maxi = 0; //индекс на неделата со најмногу работни чаца (0–3)
    for (int i = 0; i < NEDELI; ++i) {
        int vkupno = rabotniCasovi(r->nedeli[i].casovi, DENOVI);
        if (vkupno > max) {
            max = vkupno;
            maxi = i;
        }
    }
    return maxi + 1;
}
void table(R *r, int n) {
    cout << "Rab\t";
    for (int i = 0; i < NEDELI; ++i) {
        cout << i + 1 << "\t";
    }
    cout << "Vkupno"<<endl;

    for (int i = 0; i < n; ++i) {
        cout << r[i].ime << "\t";
        int vkupno = 0;
        for (int j = 0; j < NEDELI; j++) {
            int casovi = rabotniCasovi(r[i].nedeli[j].casovi, DENOVI);
            cout << casovi << "\t";
            vkupno += casovi;
        }
        cout << vkupno << "\n";
    }
}


//не менуваш во main

int main() {
    int n;
    cin >> n;

    R rabotnici[n];

    for (int i = 0; i < n; ++i) {
        cin >> rabotnici[i].ime;
        for (int j = 0; j < NEDELI; ++j) {
            for (int k = 0; k < DENOVI; ++k) {
                cin >> rabotnici[i].nedeli[j].casovi[k];
            }
        }
    }
    cout << "TABLE" << endl;
    table(rabotnici, n);

    cout << "MAX NEDELA NA RABOTNIK: " << rabotnici[n / 2].ime << endl;
    cout << maxNedela(&rabotnici[n / 2]) << endl;
    return 0;
}
