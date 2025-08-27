#include <iostream>
#include <string>
using namespace std;

struct Proizvod {
    string kod;
    int cena;
    int brojmagacin;
};

struct Narachka {
    string ime;
    Proizvod proizvodi[10];
    int brNaracani[10];
    int n;
};

void pecatiFaktura(Narachka n) {
    cout << "Faktura za " << n.ime << endl;
    bool daliMoze = true;
    for (int i = 0; i < n.n; i++) {
        if (n.proizvodi[i].brojmagacin < n.brNaracani[i]) {
            daliMoze = false;
            break;
        }
    }
    if (!daliMoze) {
        cout << "Fakturata ne moze da se izgotvi";
    } else {
        for (int i = 0; i < n.n; i++) {
            for (int j = i + 1; j < n.n; j++) {
                if (n.proizvodi[i].kod > n.proizvodi[j].kod) {
                    Proizvod pom = n.proizvodi[i];
                    n.proizvodi[i] = n.proizvodi[j];
                    n.proizvodi[j] = pom;
                }
            }
        }
        int sum = 0;
        for (int i = 0; i < n.n; i++) {
            sum += n.brNaracani[i] * n.proizvodi[i].cena;
            n.proizvodi[i].brojmagacin -= n.brNaracani[i];
            cout << n.proizvodi[i].kod << " "
                 << n.proizvodi[i].cena << " "
                 << n.brNaracani[i] << " "
                 << n.brNaracani[i] * n.proizvodi[i].cena
                 << endl;
        }
        cout << "Vkupnata suma na fakturata e " << sum;
    }
}

int main() {
    Narachka narachka;

    cin >> narachka.ime;
    cin >> narachka.n;
    for (int i = 0; i < narachka.n; ++i) {
        cin >> narachka.proizvodi[i].kod;
        cin >> narachka.proizvodi[i].cena;
        cin >> narachka.proizvodi[i].brojmagacin;
    }
    for (int j = 0; j < narachka.n; ++j) {
        cin >> narachka.brNaracani[j];
    }

    pecatiFaktura(narachka);

    return 0;
}