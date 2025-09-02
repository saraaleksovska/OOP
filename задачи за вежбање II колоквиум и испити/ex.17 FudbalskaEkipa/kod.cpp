#include <iostream>
#include <cstring>
using namespace std;

class FudbalskaEkipa {
protected:
    char trener[100];
    int golovi[10];
public:
    FudbalskaEkipa(const char *trener = "", int *golovi = NULL) {
        strcpy(this->trener,trener);
        for (int i = 0; i < 10; ++i) {
            this->golovi[i] = golovi[i];
        }
    }
    virtual int uspeh() const = 0;
    FudbalskaEkipa &operator+=(int x) {
        for (int i = 0; i < 9; ++i) {
            golovi[i] = golovi[i + 1];
        }
        golovi[9] = x;
        return *this;
    }
    virtual const char *getIme() const = 0;
    int totalPoints() const {
        int total = 0;
        for (int i = 0; i < 10; ++i) {
            total += golovi[i];
        }
        return total;
    }
    bool operator>(const FudbalskaEkipa &f) {
        return uspeh() > f.uspeh();
    }
    friend ostream &operator<<(ostream &out, const FudbalskaEkipa &f) {
        out << f.getIme() << endl;
        out << f.trener << endl;
        out << f.uspeh() << endl;
        return out;
    }
    virtual ~FudbalskaEkipa() {}
};

class Klub : public FudbalskaEkipa {
private:
    char ime[100];
    int tituli;
public:
    Klub(const char *trener, int golovi[], const char *ime, int tituli): FudbalskaEkipa(trener, golovi) {
        strcpy(this->ime,ime);
        this->tituli=tituli;
    }
    int uspeh() const {
        return totalPoints() * 3 + tituli * 1000;
    }
    const char *getIme() const {
        return ime;
    }
};

class Reprezentacija : public FudbalskaEkipa {
private:
    char drzava[100];
    int nastapi;
public:
    Reprezentacija(const char *trener, int golovi[], const char *drzava, int nastapi): FudbalskaEkipa(trener, golovi)  {
        strcpy(this->drzava, drzava);
        this->nastapi=nastapi;
    }
    int uspeh() const {
        return totalPoints() * 3 + nastapi * 50;
    }
    const char *getIme() const {
        return drzava;
    }
};

void najdobarTrener(FudbalskaEkipa **ekipi, int n) {
    FudbalskaEkipa* max = ekipi[0];
    for (int i = 1; i < n; ++i) {
        if (*ekipi[i] > *max) {
            max = ekipi[i];
        }
    }
    cout << *max;
}



int main() {
    int n;
    cin >> n;
    FudbalskaEkipa **ekipi = new FudbalskaEkipa*[n];
    char coach[100];
    int points[10];
    char x[100];
    int tg;
    for (int i = 0; i < n; ++i) {
        int type;
        cin >> type;
        cin.getline(coach, 100);
        cin.getline(coach, 100);
        for (int j = 0; j < 10; ++j) {
            cin >> points[j];
        }
        cin.getline(x, 100);
        cin.getline(x, 100);
        cin >> tg;
        if (type == 0) {
            ekipi[i] = new Klub(coach, points, x, tg);
        } else if (type == 1) {
            ekipi[i] = new Reprezentacija(coach, points, x, tg);
        }
    }
    cout << "===== SITE EKIPI =====" << endl;
    for (int i = 0; i < n; ++i) {
        cout << *ekipi[i];
    }
    cout << "===== DODADI GOLOVI =====" << endl;
    for (int i = 0; i < n; ++i) {
        int p;
        cin >> p;
        cout << "dodavam golovi: " << p << endl;
        *ekipi[i] += p;
    }
    cout << "===== SITE EKIPI =====" << endl;
    for (int i = 0; i < n; ++i) {
        cout << *ekipi[i];
    }
    cout << "===== NAJDOBAR TRENER =====" << endl;
    najdobarTrener(ekipi, n);
    for (int i = 0; i < n; ++i) {
        delete ekipi[i];
    }
    delete [] ekipi;
    return 0;
}