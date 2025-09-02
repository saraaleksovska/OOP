#include <iostream>
#include <cstring>
#include <cstdlib>

using namespace std;
class NegativnaVrednost{
    char tekst[100];
public:
    NegativnaVrednost(const char *tekst = ""){
        strncpy(this->tekst,tekst,99);
        this->tekst[99]='\0';
    }
    void pecati(){
        cout<<tekst<<endl;
    }
};

class Oglas{
private:
    char naslov[50];
    char kategorija[30];
    char opis[100];
    float cena;
public:
    Oglas(const char *naslov = "", const char *kategorija = "", const char *opis = "", float cena = 0){
        strncpy(this->naslov,naslov, 49);
        this->naslov[49]='\0';
        strncpy(this->kategorija,kategorija, 29);
        this->kategorija[29]='\0';
        strncpy(this->opis,opis, 99);
        this->opis[99]='\0';
        this->cena=cena;
    }
    const char* getKategorija() const{
        return kategorija;
    }
    float getCena() const{
        return cena;
    }
    bool operator>(const Oglas &o){
        return cena > o.cena;
    }
    friend ostream &operator<<(ostream &o,const Oglas &og){
        return o << og.naslov << endl << og.opis<<endl<< og.cena << " evra" <<endl<<endl;
    }
};

class Oglasnik{
private:
    char naziv[50];
    Oglas *oglasi;
    int n;
public:
    Oglasnik(const char *naziv=""){
        strncpy(this->naziv,naziv, 49);
        this->naziv[49]='\0';
        n=0;
        oglasi=NULL;
    }
    ~Oglasnik(){
        delete [] oglasi;
    }
    Oglasnik(const Oglasnik &a){
        strcpy(naziv, a.naziv);
        n=a.n;
        oglasi = new Oglas[n];
        for(int i = 0; i < n; i++)
            oglasi[i] = a.oglasi[i];
    }
    Oglasnik &operator=(const Oglasnik &a){
        if (&a != this){
            delete[]oglasi;
            strcpy(naziv, a.naziv);
            n=a.n;
            oglasi = new Oglas[n];
            for(int i = 0; i < n; i++)
                oglasi[i] = a.oglasi[i];
        }
        return *this;
    }
    Oglasnik &operator+=(const Oglas &og){
        if (og.getCena()<0) throw NegativnaVrednost("Oglasot ima nevalidna vrednost za cenata i nema da bide evidentiran!");
        Oglas* temp = oglasi;
        oglasi = new Oglas[n + 1];
        for(int i = 0; i < n; ++i) {
            oglasi[i] = temp[i];
        }
        delete [] temp;
        oglasi[n] = og;
        ++n;
        return *this;
    }
    friend ostream &operator<<(ostream &o, const Oglasnik &og){
        o<<og.naziv<<endl;
        for (int i = 0; i < og.n; i++){
            o<<og.oglasi[i];
        }
        return o;
    }
    void oglasiOdKategorija(const char *k){
        for (int i=0;i<n;i++){
            if(!strcmp(oglasi[i].getKategorija(),k))
                cout<<oglasi[i];
        }
    }
    void najniskaCena(){
        Oglas min = oglasi[0];
        for (int i=1;i<n;i++){
            if(min > oglasi[i])
                min = oglasi[i];
        }
        cout<<min;
    }
};

int main(){
    char naslov[50];
    char kategorija[30];
    char opis[100];
    float cena;
    char naziv[50];
    char k[30];
    int n;

    int tip;
    cin>>tip;

    if (tip==1){
        cout<<"-----Test Oglas & operator <<-----" <<endl;
        cin.get();
        cin.getline(naslov,49);
        cin.getline(kategorija,29);
        cin.getline(opis,99);
        cin>>cena;
        Oglas o(naslov, kategorija, opis, cena);
        cout<<o;
    }
    else if (tip==2){
        cout<<"-----Test Oglas & operator > -----" <<endl;
        cin.get();
        cin.getline(naslov,49);
        cin.getline(kategorija,29);
        cin.getline(opis,99);
        cin>>cena;
        Oglas o1(naslov, kategorija, opis, cena);
        cin.get();
        cin.getline(naslov,49);
        cin.getline(kategorija,29);
        cin.getline(opis,99);
        cin>>cena;
        Oglas o2(naslov, kategorija, opis, cena);
        if (o1>o2) cout<<"Prviot oglas e poskap."<<endl;
        else cout<<"Prviot oglas ne e poskap."<<endl;
    }
    else if (tip==3){
        cout<<"-----Test Oglasnik, operator +=, operator << -----" <<endl ;
        cin.get();
        cin.getline(naziv,49);
        cin>>n;
        Oglasnik ogl(naziv);
        for (int i = 0; i < n; i++){
            cin.get();
            cin.getline(naslov,49);
            cin.getline(kategorija,29);
            cin.getline(opis,99);
            cin>>cena;
            Oglas o(naslov, kategorija, opis, cena);
            ogl+=o;
        }
        cout<<ogl;
    }
    else if (tip==4){
        cout<<"-----Test oglasOdKategorija -----" <<endl ;
        cin.get();
        cin.getline(naziv,49);
        cin>>n;
        Oglasnik ogl(naziv);
        for (int i = 0; i < n; i++){
            cin.get();
            cin.getline(naslov,49);
            cin.getline(kategorija,29);
            cin.getline(opis,99);
            cin>>cena;
            Oglas o(naslov, kategorija, opis, cena);
            ogl+=o;
        }
        cin.get();
        cin.getline(k,29);
        cout<<"Oglasi od kategorijata: " <<k<<endl;
        ogl.oglasiOdKategorija(k);

    }
    else if (tip==5){
        cout<<"-----Test Exception -----" <<endl ;
        cin.get();
        cin.getline(naziv,49);
        cin>>n;
        Oglasnik ogl(naziv);
        for (int i = 0; i < n; i++){
            cin.get();
            cin.getline(naslov,49);
            cin.getline(kategorija,29);
            cin.getline(opis,99);
            cin>>cena;
            Oglas o(naslov, kategorija, opis, cena);
            try{
                ogl+=o;
            }
            catch(NegativnaVrednost nv){
                nv.pecati();
            }
        }
        cout<<ogl;

    }
    else if (tip==6){
        cout<<"-----Test najniskaCena -----" <<endl ;
        cin.get();
        cin.getline(naziv,49);
        cin>>n;
        Oglasnik ogl(naziv);
        for (int i = 0; i < n; i++){
            cin.get();
            cin.getline(naslov,49);
            cin.getline(kategorija,29);
            cin.getline(opis,99);
            cin>>cena;
            Oglas o(naslov, kategorija, opis, cena);
            ogl+=o;
        }
        cout<<"Oglas so najniska cena:"<<endl;
        ogl.najniskaCena();

    }
    else if (tip==7){
        cout<<"-----Test All -----" <<endl ;
        cin.get();
        cin.getline(naziv,49);
        cin>>n;
        Oglasnik ogl(naziv);
        for (int i = 0; i < n; i++){
            cin.get();
            cin.getline(naslov,49);
            cin.getline(kategorija,29);
            cin.getline(opis,99);
            cin>>cena;
            Oglas o(naslov, kategorija, opis, cena);
            try{
                ogl+=o;
            }
            catch(NegativnaVrednost nv){
                nv.pecati();
            }
        }
        cout<<ogl;

        cin.get();
        cin.get();
        cin.getline(k,29);
        cout<<"Oglasi od kategorijata: " <<k<<endl;
        ogl.oglasiOdKategorija(k);

        cout<<"Oglas so najniska cena:"<<endl;
        ogl.najniskaCena();

    }

    return 0;
}
