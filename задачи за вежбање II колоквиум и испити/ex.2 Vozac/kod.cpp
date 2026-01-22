// vashiot kod ovde

#include <iostream>
#include <cstring>
using namespace std;

class Vozac{
protected:
    char ime[101];
    int vozrast;
    int trki;
    bool veteran;
public:
    Vozac(const char *ime="", int vozrast=0, int trki=0, bool veteran= true){
        strcpy(this->ime, ime);
        this->vozrast=vozrast;
        this->trki=trki;
        this->veteran=veteran;
    }
    friend ostream &operator<<(ostream &o, Vozac &v){
        o<<v.ime<<endl<<v.vozrast<<endl<<v.trki<<endl;
        if(v.veteran){
            o<<"VETERAN"<<endl;
        }
        return o;
    }
    virtual float zarabotuvacka() const = 0;
    virtual float danok()=0;
    bool operator==(const Vozac &v) {
        return zarabotuvacka()==v.zarabotuvacka();
    }
};
class Avtomobilist : public Vozac{
private:
    float cena;
public:
    Avtomobilist(const char *ime="", int vozrast=0, int trki=0, bool veteran= true, float cena=0.0)
    : Vozac(ime, vozrast, trki, veteran){
        this->cena=cena;
    }
    float zarabotuvacka() const override{
        return cena/5;
    }
    float danok() override{
        if(trki>10){
            return zarabotuvacka()*0.15;
        }
        return zarabotuvacka()*0.1;
    }
};
class Motociklist : public Vozac{
private:
    int mokjnost;
public:
    Motociklist(const char *ime="", int vozrast=0, int trki=0, bool veteran= true, int mokjnost=0)
    : Vozac(ime, vozrast, trki, veteran){
        this->mokjnost=mokjnost;
    }
    float zarabotuvacka() const override{
        return mokjnost*20;
    }
    float danok() override{
        if(veteran){
            return zarabotuvacka()*0.25;
        }
        return zarabotuvacka()*0.2;
    }
};
int soIstaZarabotuvachka(Vozac **v, int n, Vozac *vozac){
    int br=0;
    for(int i=0; i<n; i++){
        if(*v[i]==*vozac){
            br++;
        }
    }
    return br;
}


//не менуваш во main
int main() {
	int n, x;
	cin >> n >> x;
	Vozac **v = new Vozac*[n];
	char ime[100];
	int vozrast;
	int trki;
	bool vet;
	for(int i = 0; i < n; ++i) {
		cin >> ime >> vozrast >> trki >> vet;
		if(i < x) {
			float cena_avto;
			cin >> cena_avto;
			v[i] = new Avtomobilist(ime, vozrast, trki, vet, cena_avto);
		} else {
			int mokjnost;
			cin >> mokjnost;
			v[i] = new Motociklist(ime, vozrast, trki, vet, mokjnost);
		}
	}
	cout << "=== DANOK ===" << endl;
	for(int i = 0; i < n; ++i) {
		cout << *v[i];
		cout << v[i]->danok() << endl;
	}
	cin >> ime >> vozrast >> trki >> vet;
	int mokjnost;
	cin >> mokjnost;
	Vozac *vx = new Motociklist(ime, vozrast, trki, vet, mokjnost);
	cout << "=== VOZAC X ===" << endl;
	cout << *vx;
	cout << "=== SO ISTA ZARABOTUVACKA KAKO VOZAC X ===" << endl;
	cout << soIstaZarabotuvachka(v, n, vx);
    for(int i = 0; i < n; ++i) {
        delete v[i];
    }
    delete [] v;
    delete vx;
	return 0;
}
