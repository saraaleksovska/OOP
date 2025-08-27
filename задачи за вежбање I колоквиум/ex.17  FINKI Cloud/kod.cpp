#include <iostream>
#include <cstring>

using namespace std;

enum Tip {
    LINUX, UNIX, WINDOWS
};

class OperativenSistem {
private:
    char *ime;
    float verzija;
    Tip tip;
    float GB;
    void copy(const OperativenSistem &os) {
        this->ime = new char[strlen(ime) + 1];
        strcpy(this->ime, os.ime);
        this->verzija = os.verzija;
        this->tip = os.tip;
        this->GB = os.GB;
    }
public:
    OperativenSistem() {
        this->ime = new char[0];
        this->verzija = 0;
        this->tip = LINUX;
        this->GB = 0;
    }
    OperativenSistem(const char *ime, const float verzija, const Tip tip, const float GB) {
        this->ime = new char[strlen(ime) + 1];
        strcpy(this->ime, ime);
        this->verzija = verzija;
        this->tip = tip;
        this->GB = GB;
    }
    bool ednakviSe(const OperativenSistem &os) {
        return strcmp(this->ime, os.ime)==0 && this->verzija == os.verzija && tip == os.tip && GB == os.GB;
    }
    int sporediVerzija(const OperativenSistem &os) {
        if (verzija == os.verzija) return 0;
        if (verzija > os.verzija) return 1;
        return -1;
    }
    bool istaFamilija(const OperativenSistem &os) {
        return strcmp(ime, os.ime)==0 && tip==os.tip;
    }
    ~OperativenSistem() {
        delete[] ime;
    }
    OperativenSistem &operator=(const OperativenSistem &os) {
        if (&os != this) {
            delete[] ime;
            copy(os);
        }
        return *this;
    }
    OperativenSistem(const OperativenSistem &os) {
        copy(os);
    }
    void pecati(){
        cout<<"Ime: "<<ime<<" Verzija: "<<verzija<<" Tip: "<<tip<<" Golemina:"<<GB<<"GB"<<endl;
    }
};

class Repozitorium {
private:
    char ime[20];
    int n;
    OperativenSistem *operativniSistemi;
public:
    Repozitorium(const char *ime) {
        strcpy(this->ime, ime);
        this->n = 0;
        this->operativniSistemi = 0;
    }
    void izbrishi(const OperativenSistem &os) {
        int idx = -1;
        for (int i = 0; i < n; i++) {
            if (operativniSistemi[i].ednakviSe(os)) {
                idx = i;
            }
        }
        if (idx != -1) {
            OperativenSistem *tmp = operativniSistemi;
            this->operativniSistemi = new OperativenSistem[n - 1];
            for (int i = 0, j = 0; i<n; i++) {
                if (i != idx) {
                    operativniSistemi[j++] = tmp[i];
                }
            }
            n--;
        }
    }
    void dodadi(const OperativenSistem &os) {
        for (int i = 0; i < n; i++) {
            if (operativniSistemi[i].istaFamilija(os) && operativniSistemi[i].sporediVerzija(os)<0) {
                operativniSistemi[i] = os;
                return;
            }
        }
        OperativenSistem *tmp = operativniSistemi;
        this->operativniSistemi = new OperativenSistem[n + 1];
        for (int i = 0; i < n; i++) {
            operativniSistemi[i] = tmp[i];
        }
        operativniSistemi[n++] = os;
    }
    void pecatiOperativniSistemi(){
        cout<<"Repozitorium: "<<ime<<endl;
        for (int i=0; i<n; i++){
            operativniSistemi[i].pecati();
        }
    }
};

//не менуваш во main

int main() {
    char repoName[20];
    cin>>repoName;
    Repozitorium repozitorium=Repozitorium(repoName);
    int brojOperativniSistemi = 0;
    cin>>brojOperativniSistemi;
    char ime[20];
    float verzija;
    int tip;
    float golemina;
    for (int i = 0; i<brojOperativniSistemi; i++){
        cin>>ime;
        cin>>verzija;
        cin>>tip;
        cin>>golemina;
        OperativenSistem os = OperativenSistem(ime, verzija, (Tip)tip, golemina);
        repozitorium.dodadi(os);
    }
    repozitorium.pecatiOperativniSistemi();
    cin>>ime;
    cin>>verzija;
    cin>>tip;
    cin>>golemina;
    OperativenSistem os = OperativenSistem(ime, verzija, (Tip)tip, golemina);
    cout<<"=====Brishenje na operativen sistem====="<<endl;
    repozitorium.izbrishi(os);
    repozitorium.pecatiOperativniSistemi();
}