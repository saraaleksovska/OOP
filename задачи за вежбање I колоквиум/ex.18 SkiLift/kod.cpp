#include <iostream>
#include <string>
using namespace std;

struct SkiLift {
    string ime;
    int korisnici;
    int voUpotreba;
};
struct SkiCenter {
    string ime;
    string drzava;
    SkiLift liftovi[20];
    int n;
};

int kapacitet(SkiCenter sc) {
    int vkupenKapacitet = 0;
    for (int i = 0; i < sc.n; i++) {
        if (sc.liftovi[i].voUpotreba == 1) {
            vkupenKapacitet += sc.liftovi[i].korisnici;
        }
    }
    return vkupenKapacitet;
}

void najgolemKapacitet(SkiCenter *sc, int n) {
    int max = 0;
    int maxIdx = 0;
    for (int i = 0; i < n; i++) {
        int tmp = kapacitet(sc[i]);
        if (tmp>max || (tmp==max && sc[i].n>sc[maxIdx].n)) {
            max = tmp;
            maxIdx = i;
        }
    }
    cout << sc[maxIdx].ime << endl;
    cout << sc[maxIdx].drzava << endl;
    cout << max << endl;
}

int main() {
    int n;
    cin >> n;
    SkiCenter sc[20];

    for (int i = 0; i < n; i++) {
        cin >> sc[i].ime;
        cin >> sc[i].drzava;
        cin >> sc[i].n;
        for (int j = 0; j < sc[i].n; j++) {
            cin >> sc[i].liftovi[j].ime;
            cin >> sc[i].liftovi[j].korisnici;
            cin >> sc[i].liftovi[j].voUpotreba;
        }
    }
    najgolemKapacitet(sc, n);

    return 0;
}