#include<iostream>
#include<cstring>
using namespace std;

class OutOfBoundException{
public:
    void print(){
        cout<<"Brojot na pin kodovi ne moze da go nadmine dozvolenoto"<<endl;
    }
};

class Karticka{
protected:
    char smetka[16];
    int pin;
    bool povekjePinovi;
public:
    Karticka(const char *smetka="",int pin=0){
        strcpy(this->smetka,smetka);
        this->pin=pin;
        this->povekjePinovi=false;
    }
    virtual int tezinaProbivanje(){
        int brCifri=0;
        int tmp=pin;
        while (tmp!=0) {
            brCifri++;
            tmp/=10;
        }
        return brCifri;
    }
    friend ostream &operator<<(ostream &o,Karticka &u){
        o<<u.smetka<<": "<<u.tezinaProbivanje()<<endl;
        return o;
    }
    bool getDopolnitelenPin(){
        return povekjePinovi;
    }
    char *getSmetka(){
        return smetka;
    }
};
class SpecijalnaKarticka: public Karticka{
private:
    int *dopolnitelniPinKodovi;
    int n;
    void copy(const SpecijalnaKarticka &s) {
        n=s.n;
        dopolnitelniPinKodovi=new int[P];
        for (int i=0;i<n;i++) {
            dopolnitelniPinKodovi[i] = s.dopolnitelniPinKodovi[i];
        }
    }
public:
    const static int P=4;
    SpecijalnaKarticka(const char *smetka="",int pin=0):Karticka(smetka,pin){
        this->povekjePinovi=true;
        n=0;
        dopolnitelniPinKodovi=new int[P];
    }
    SpecijalnaKarticka(const SpecijalnaKarticka &s) : Karticka(s){
        copy(s);
    }
    SpecijalnaKarticka &operator=(const SpecijalnaKarticka &s) {
        if (this != &s) {
            delete[] dopolnitelniPinKodovi;
            copy(s);
        }
        return *this;
    }
    ~SpecijalnaKarticka(){
        delete[] dopolnitelniPinKodovi;
    }
    int tezinaProbivanje(){
        return n + Karticka::tezinaProbivanje();
    }
    friend void operator +=(SpecijalnaKarticka &s,int nov){
        if (s.n==s.P) {
            throw OutOfBoundException();
        }
        s.dopolnitelniPinKodovi[s.n++]=nov;
    }
};

class Banka {
private:
    char ime[30];
    Karticka *karticki[20];
    int n;
    int static LIMIT;
public:
    Banka(char *ime, Karticka **karticki,int n){
        strcpy(this->ime,ime);
        for (int i=0;i<n;i++){
            if (karticki[i]->getDopolnitelenPin()){
                this->karticki[i]=new SpecijalnaKarticka(*dynamic_cast<SpecijalnaKarticka*>(karticki[i]));
            }
            else this->karticki[i]=new Karticka(*karticki[i]);
        }
        this->n=n;
    }
    ~Banka(){
        for (int i=0;i<n;i++) {
            delete karticki[i];
        }
    }

    //да се дополни класата
    static void setLIMIT(int novaVrednost){
        LIMIT=novaVrednost;
    }
    void pecatiKarticki(){
        cout<<"Vo bankata "<<ime<<" moze da se probijat kartickite:"<<endl;
        for (int i=0;i<n;i++)
            if (karticki[i]->tezinaProbivanje()<=LIMIT){
                cout<<(*karticki[i]);
            }
    }
    void dodadiDopolnitelenPin(char *smetka,int novPin){
        for (int i=0;i<n;i++)
            if (strcmp(karticki[i]->getSmetka(),smetka)==0){
                SpecijalnaKarticka *nov=dynamic_cast<SpecijalnaKarticka*>(karticki[i]);
                if (nov!=0){
                    (*nov)+=novPin;
                }
            }
    }

};
int Banka::LIMIT=7;



int main(){
    Karticka **niza;
    int n,m,pin;
    char smetka[16];
    bool daliDopolnitelniPin;
    cin>>n;
    niza=new Karticka*[n];
    for (int i=0;i<n;i++){
        cin>>smetka;
        cin>>pin;
        cin>>daliDopolnitelniPin;
        if (!daliDopolnitelniPin)
            niza[i]=new Karticka(smetka,pin);
        else
            niza[i]=new SpecijalnaKarticka(smetka,pin);
    }

    Banka komercijalna("Komercijalna",niza,n);
    for (int i=0;i<n;i++) delete niza[i];
    delete [] niza;
    cin>>m;
    for (int i=0;i<m;i++){
        cin>>smetka>>pin;
        try{
            komercijalna.dodadiDopolnitelenPin(smetka,pin);
        }
        catch(OutOfBoundException i){
            i.print();
        }
    }

    Banka::setLIMIT(5);
    komercijalna.pecatiKarticki();

}
