#include <iostream>
#include <cstring>

using namespace std;

enum tip {
    pop, rap, rok
};

class Pesna {
private:
    char *ime; //динамички алоцирана низа од знаци
    int minuti;
    tip tip_;
    void copy(const Pesna &p) {
        this->ime = new char[strlen(p.ime) + 1];
        strcpy(this->ime, p.ime);
        this->minuti = p.minuti;
        this->tip_ = p.tip_;
    }
public:
    /*Pesna() { //defaultен конструктор
        ime = new char[0];
        minuti = 0;
        tipp = pop;
    }*/
    Pesna(char *ime=" ", int minuti=0, tip tip_=rok) {
        this->ime = new char[strlen(ime) + 1];
        strcpy(this->ime, ime);
        this->minuti = minuti;
        this->tip_ = tip_;
    }
    Pesna(const Pesna &p) {
        copy(p);
    }
    ~Pesna() {
        delete[] ime;
    }
    Pesna &operator=(const Pesna &p) {
        if (this != &p) {
            delete[] ime;
            copy(p);
        }
        return *this;
    }
    void pecati() {
        cout << "\"" << ime << "\"-" << minuti << "min" << endl;
    }
    int getMinuti() {
        return minuti;
    }
    char *getIme() {
        return ime;
    }
    tip getTip() {
        return tip_;
    }
};

class CD {
private:
    Pesna pesni[10]; //Поле од најмногу 10 објекти од класата Pesna
    int n;
    int maxVreme;
public:
    CD(int maxVreme) {
        this->maxVreme = maxVreme;
        this->n = n;
        for(int i=0; i<n; i++){
            this->pesni[i]=pesni[i];
        }
    }
    Pesna getPesna(int i) { 
        return pesni[i]; 
    }
    int getBroj() { 
        return n;
    }
    int vkupnoVreme() {
        int vkupno = 0;
        for (int i = 0; i < n; i++) {
            vkupno += pesni[i].getMinuti();
        }
        return vkupno;
    }
    void dodadiPesna(Pesna p) {
        if (n>=10) return;
        if (maxVreme < vkupnoVreme()+p.getMinuti()) return;
        bool jaIma = false;
        for (int i = 0; i < n; i++) {
            if (strcmp(pesni[i].getIme(), p.getIme()) == 0) {
                jaIma = true;
            }
        }
        if (jaIma == false) {
            pesni[n++] = p;
        }
    }
    void pecatiPesniPoTip(tip t) {
        for (int i = 0; i < n; i++) {
            if ((int) pesni[i].getTip() == (int) t) {
                pesni[i].pecati();
            }
        }
    }
};




//во main не менуваш ништо
int main() {
    // se testira zadacata modularno
    int testCase, n, minuti, kojtip;
    cin >> testCase;

    char ime[50];

    if (testCase == 1) {
        cout << "===== Testiranje na klasata Pesna ======" << endl;
        cin >> ime >> minuti >> kojtip; //se vnesuva 0 za POP,1 za RAP i 2 za ROK
        Pesna p(ime, minuti, (tip) kojtip);
        p.pecati();
    } else if (testCase == 2) {
        cout << "===== Testiranje na klasata CD ======" << endl;
        CD omileno(20);
        cin >> n;
        for (int i = 0; i < n; i++) {
            cin >> ime >> minuti >> kojtip;
            Pesna p(ime, minuti, (tip) kojtip);
            omileno.dodadiPesna(p);
        }
        for (int i = 0; i < n; i++)
            (omileno.getPesna(i)).pecati();
    } else if (testCase == 3) {
        cout << "===== Testiranje na metodot dodadiPesna() od klasata CD ======" << endl;
        CD omileno(20);
        cin >> n;
        for (int i = 0; i < n; i++) {
            cin >> ime >> minuti >> kojtip;
            Pesna p(ime, minuti, (tip) kojtip);
            omileno.dodadiPesna(p);
        }
        for (int i = 0; i < omileno.getBroj(); i++)
            (omileno.getPesna(i)).pecati();
    } else if (testCase == 4) {
        cout << "===== Testiranje na metodot pecatiPesniPoTip() od klasata CD ======" << endl;
        CD omileno(20);
        cin >> n;
        for (int i = 0; i < n; i++) {
            cin >> ime >> minuti >> kojtip;
            Pesna p(ime, minuti, (tip) kojtip);
            omileno.dodadiPesna(p);
        }
        cin >> kojtip;
        omileno.pecatiPesniPoTip((tip) kojtip);

    } else if (testCase == 5) {
        cout << "===== Testiranje na metodot pecatiPesniPoTip() od klasata CD ======" << endl;
        CD omileno(20);
        cin >> n;
        for (int i = 0; i < n; i++) {
            cin >> ime >> minuti >> kojtip;
            Pesna p(ime, minuti, (tip) kojtip);
            omileno.dodadiPesna(p);
        }
        cin >> kojtip;
        omileno.pecatiPesniPoTip((tip) kojtip);
    }

    return 0;

}


