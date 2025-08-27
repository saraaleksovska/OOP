#include<iostream>
#include<cstring>
using namespace std;

class Patnik{
private:
    char ime[100];
    int klasa;
    bool velosiped;
public:
    Patnik(const char *ime = "", int klasa = 2, bool velosiped = false){
        strcpy(this->ime, ime);
        this->klasa=klasa;
        this->velosiped=velosiped;
    }
    int getKlasa() { return klasa; }
    bool getVelosiped() { return velosiped; }
    friend ostream &operator<<(ostream& out, Patnik &p){
        out << p.ime << endl;
        out << p.klasa << endl;
        out << p.velosiped << endl;
        return out;
    }
};

class Voz{
private:
    char destinacija[100];
    Patnik *patnici;
    int n;
    int maxVelosipedi;
public:
    Voz(const char *destinacija = "", int maxVelosipedi = 0){
        strcpy(this->destinacija,destinacija);
        patnici = NULL;
        n = 0;
        this->maxVelosipedi=maxVelosipedi;
    }
    ~Voz(){
        delete[] patnici;
    }
    Voz &operator+=(Patnik &p){
        if ((p.getVelosiped() && maxVelosipedi > 0) || !p.getVelosiped()){
            Patnik *tmp = new Patnik[n + 1];
            for (int i = 0; i<n; i++){
                tmp[i] = patnici[i];
            }
            tmp[n] = p;
            n++;
            delete[] patnici;
            patnici = tmp;
        }
        return *this;
    }
    friend ostream &operator<<(ostream &out, Voz &v){
        out << v.destinacija << endl;
        for (int i = 0; i < v.n; i++)
            out << v.patnici[i] << endl;
        return out;
    }

    void patniciNemaMesto(){
        int vlezeniPrva = 0, vlezeniVtora = 0, nevlezeniPrva = 0, nevlezeniVtora = 0;
        for (int i = 0; i < n; i++){
            if (patnici[i].getKlasa()==1 && patnici[i].getVelosiped()){
                vlezeniPrva++;
                if (vlezeniPrva>maxVelosipedi){
                    nevlezeniPrva++;
                }
            }
        }
        for (int i = 0; i < n; i++){
            if (patnici[i].getKlasa()==2 && patnici[i].getVelosiped()){
                vlezeniVtora++;
                if ((vlezeniPrva+vlezeniVtora) > maxVelosipedi){
                    nevlezeniVtora++;
                }
            }
        }
        cout << "Brojot na patnici od 1-va klasa koi ostanale bez mesto e: " << nevlezeniPrva << endl;
        cout << "Brojot na patnici od 2-ra klasa koi ostanale bez mesto e: " << nevlezeniVtora << endl;
    }
};

//не менуваш ништо во main

int main(){
    Patnik p;
    char ime[100], destinacija[100];
    int n, klasa, maxv;
    bool velosiped;
    cin >> destinacija >> maxv>> n;
    Voz v(destinacija, maxv);
    for (int i = 0; i < n; i++){
        cin >> ime >> klasa >> velosiped;
        Patnik p(ime, klasa, velosiped);
        v += p;
    }
    cout << v;
    v.patniciNemaMesto();
    return 0;
}
