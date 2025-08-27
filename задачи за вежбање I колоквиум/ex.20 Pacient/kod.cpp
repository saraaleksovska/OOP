#include <iostream>
#include <string>

using namespace std;

struct Pacient {
    string ime;
    int zdrastveno;
    int pregledi;
};

struct MaticenDoktor {
    string ime;
    Pacient pacienti[200];
    int n;
    float cena;
};

float zarabotkaOdPrivatno(MaticenDoktor md) {
    float zarabotka = 0;
    for (int i = 0; i < md.n; i++) {
        if (md.pacienti[i].zdrastveno == 0)
            zarabotka += md.pacienti[i].pregledi;
    }
    return zarabotka * md.cena;
}

int pregledi(MaticenDoktor md) {
    int suma = 0;
    for (int i = 0; i < md.n; i++) {
        suma += md.pacienti[i].pregledi;
    }
    return suma;
}

void najuspesen_doktor(MaticenDoktor *md, int n) {
    float maxZarabotka = 0.0;
    int najuspesen = 0;
    for (int i = 0; i < n; i++) {
        float zarabotka = zarabotkaOdPrivatno(md[i]);
        if (zarabotka == maxZarabotka) {
            int preglediMomentalenDoktor = pregledi(md[i]);
            int preglediNajuspesen = pregledi(md[najuspesen]);
            if (preglediMomentalenDoktor > preglediNajuspesen) {
                maxZarabotka = zarabotka;
                najuspesen = i;
            }
        } else if (zarabotka > maxZarabotka) {
            maxZarabotka = zarabotka;
            najuspesen = i;
        }
    }

    cout << md[najuspesen].ime << " " << fixed;
    cout.precision(2);
    cout << maxZarabotka << " " << pregledi(md[najuspesen]) << endl;
}

int main() {
    int n;
    cin >> n;
    MaticenDoktor md[200];

    for (int i = 0; i < n; i++) {
        cin >> md[i].ime;
        cin >> md[i].n;
        cin >> md[i].cena;
        for (int j = 0; j < md[i].n; j++) {
            cin >> md[i].pacienti[j].ime;
            cin >> md[i].pacienti[j].zdrastveno;
            cin >> md[i].pacienti[j].pregledi;
        }
    }
    najuspesen_doktor(md, n);
    return 0;
}
