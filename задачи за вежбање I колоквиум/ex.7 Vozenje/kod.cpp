#include <iostream>
#include <iomanip>
#include <cstring>
using namespace std;

struct Vozenje {
    char ime[100];
    int minuti;
    float cena;
    int popust; // 1-да, 0-не
};

struct ZabavenPark {
    char ime[100];
    char lokacija[100];
    Vozenje vozenja[100];
    int n;
};

void pecati(ZabavenPark *zp, int n) {
    for (int i = 0; i < n; i++) {
        cout << zp[i].ime << " " << zp[i].lokacija << endl;
        for (int j = 0; j < zp[i].n; j++) {
            cout << zp[i].vozenja[j].ime << " "
                 << zp[i].vozenja[j].minuti << " "
                 << fixed << setprecision(2) << zp[i].vozenja[j].cena<< endl;
        }
    }
}

void najdobar_park(ZabavenPark *zp, int n) {
    int najevtin = 0, maxVozenjaPopust = -1, maxVremetraenje = -1;

    for (int i = 0; i < n; i++) {
        int vozenjaSoPopust = 0;
        int vremetraenje = 0;

        for (int j = 0; j < zp[i].n; j++) {
            if (zp[i].vozenja[j].popust == 1)
                vozenjaSoPopust++;
            vremetraenje += zp[i].vozenja[j].minuti;
        }

        if (vozenjaSoPopust > maxVozenjaPopust ||
            (vozenjaSoPopust == maxVozenjaPopust && vremetraenje > maxVremetraenje)) {
            maxVozenjaPopust = vozenjaSoPopust;
            najevtin = i;
            maxVremetraenje = vremetraenje;
        }
    }
    cout << "Najdobar park: " << zp[najevtin].ime << " " << zp[najevtin].lokacija << endl;
}

//во main правиш сам кадешто се дадени коментари

int main() {
    int n;

    ZabavenPark parkovi[100]; //kreiraj niza od maksimum 100 zabavni parkovi

    cin >> n;

    for (int i = 0; i < n; i++) {
        //citanje na podatocite
        cin >> parkovi[i].ime;
        cin >> parkovi[i].lokacija;
        cin >> parkovi[i].n;
        for (int j = 0; j < parkovi[i].n; j++) {
            cin >> parkovi[i].vozenja[j].ime;
            cin >> parkovi[i].vozenja[j].minuti;
            cin >> parkovi[i].vozenja[j].cena;
            cin >> parkovi[i].vozenja[j].popust;
        }
        //
    }

    pecati(parkovi, n);
    najdobar_park(parkovi, n);

    return 0;
}