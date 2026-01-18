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
    tip tipp;
    void copy(const Pesna &p) {
        this->ime = new char[strlen(p.ime) + 1];
        strcpy(this->ime, p.ime);
        this->minuti = p.minuti;
        this->tipp = p.tipp;
    }
public:
    /*Pesna() { //defaultен конструктор
        ime = new char[0];
        minuti = 0;
        tipp = pop;
    }*/
    Pesna(char *ime=" ", int minuti=0, tip tipp=rok) {
        this->ime = new char[strlen(ime) + 1];
        strcpy(this->ime, ime);
        this->minuti = minuti;
        this->tipp = tipp;
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
        return tipp;
    }
};

class CD {
private:
    Pesna pesni[10]; //Поле од најмногу 10 објекти од класата Pesna
    int brPesni;
    int maxVreme;
    void copy(const CD &cd) {
        this->brPesni = cd.brPesni;
        this->maxVreme = cd.maxVreme;
        for (int i = 0; i < brPesni; i++) {
            this->pesni[i] = cd.pesni[i];
        }
    }
public:
    CD(int maxVreme) {
        this->maxVreme = maxVreme;
        this->brPesni = brPesni;
        for(int i=0; i<brPesni; i++){
            this->pesni[i]=pesni[i];
        }
    }
    CD(const CD &cd){
        copy(cd);
    }
    int getVkupnoVreme() {
        int vkupno = 0;
        for (int i = 0; i < brPesni; i++) {
            vkupno += pesni[i].getMinuti();
        }
        return vkupno;
    }
    void dodadiPesna(Pesna p) {
        if (brPesni>=10) return;
        if (maxVreme < getVkupnoVreme()+p.getMinuti()) return;
        bool jaIma = false;
        for (int i = 0; i < brPesni; i++) {
            if (strcmp(pesni[i].getIme(), p.getIme()) == 0) jaIma = true;
        }
        if (jaIma == false) pesni[brPesni++] = p;
    }
    void pecatiPesniPoTip(tip t) {
        for (int i = 0; i < brPesni; i++) {
            if ((int) pesni[i].getTip() == (int) t) {
                pesni[i].pecati();
            }
        }
    }
    Pesna getPesna(int i) { 
        return pesni[i]; 
    }
    int getBroj() { 
        return brPesni;
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
