#include <iostream>
#include <cstring>
using namespace std;

class Ucesnik {
private:
    char *ime;
    bool pol;
    int vozrast;
    void copy(const Ucesnik &u){
        ime = new char[strlen(u.ime) + 1];
        strcpy(ime, u.ime);
        this->pol = u.pol;
        this->vozrast = u.vozrast;
    }
public:
    Ucesnik(const char *ime="", bool pol= true, int vozrast=0) {
        this->ime = new char[strlen(ime) + 1];
        strcpy(this->ime, ime);
        this->pol = pol;
        this->vozrast = vozrast;
    }
    Ucesnik(const Ucesnik &u) {
        copy(u);
    }
    Ucesnik &operator=(const Ucesnik &u) {
        if (this == &u) {
            return *this;
        }
        delete[] ime;
        copy(u);
        return *this;
    }
    ~Ucesnik() {
        delete[] ime;
    }
    bool operator>(const Ucesnik &u) {
        return vozrast > u.vozrast;
    }
    friend ostream &operator<<(ostream &out, const Ucesnik &u) {
        out << u.ime << endl;
        if(u.pol) cout << "mashki" << endl;
        else cout << "zhenski" << endl;
        out << u.vozrast << endl;
        return out;
    }
    int getVozrast() {
        return vozrast;
    }
};

class Maraton {
private:
    char lokacija[100];
    Ucesnik *ucesnici;
    int n;
public:
    Maraton(const char *lokacija="") {
        strcpy(this->lokacija,lokacija);
        ucesnici = NULL;
        n = 0;
    }
    ~Maraton() {
        delete[] ucesnici;
    }
    Maraton& operator+=(const Ucesnik &u) {
        Ucesnik *tmp = ucesnici;
        ucesnici = new Ucesnik[n + 1];
        for (int i = 0; i < n; i++) {
            ucesnici[i] = tmp[i];
        }
        ucesnici[n] = u;
        n++;
        delete[] tmp;
        return *this;
    }
    void pecatiPomladi(Ucesnik &u) {
        for(int i = 0; i < n; ++i) {
            if(u > ucesnici[i]) {
                cout << ucesnici[i];
            }
        }
    }
    float prosecnoVozrast() {
        float suma = 0;
        for(int i = 0; i < n; ++i) {
            suma += ucesnici[i].getVozrast() ;
        }
        return suma / n;
    }
};

//не менуваш ништо во main

int main() {
    char ime[100];
    bool maski;
    int vozrast, n;
    cin >> n;
    char lokacija[100];
    cin >> lokacija;
    Maraton m(lokacija);
    Ucesnik **u = new Ucesnik*[n];
    for(int i = 0; i < n; ++i) {
        cin >> ime >> maski >> vozrast;
        u[i] = new Ucesnik(ime, maski, vozrast);
        m += *u[i];
    }
    m.pecatiPomladi(*u[n - 1]);
    cout << m.prosecnoVozrast() << endl;
    for(int i = 0; i < n; ++i) {
        delete u[i];
    }
    delete [] u;
    return 0;
}
