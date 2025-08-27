#include<iostream>
#include<cstring>

using namespace std;

class Zichara{
private:
    char *mesto;
    int cena;
    void copy(const Zichara &z){
        this->mesto=new char[strlen(z.mesto)+1];
        strcpy(this->mesto, z.mesto);
        this->cena=z.cena;
    }
public:
    Zichara(){
        mesto = new char[1];
        mesto[0] = '\0';
    }
    Zichara(char *mesto, int cena){
        this->mesto=new char[strlen(mesto)+1];
        strcpy(this->mesto, mesto);
        this->cena=cena;
    }
    Zichara(const Zichara &z){
        copy(z);
    }
    ~Zichara(){
        delete[] mesto;
    }
    Zichara &operator=(const Zichara &z){
        if (this!=&z) {
            delete[] mesto;
            copy(z);
            }
        return *this;
    }
    int getCena(){
        return cena;
    }
};

class PlaninarskiDom{
private:
    char ime[15];
    int *ceni;
    char klasa;
    bool ima;
    Zichara *zichara;
    void copy(const PlaninarskiDom &pd){
        strcpy(this->ime,pd.ime);
        this->ceni=new int[2]; //2= 1 за зимска и 1 летна
        for(int i=0;i<2;i++) {
            this->ceni[i] = pd.ceni[i];
        }
        this->klasa=pd.klasa;
        this->ima=pd.ima;
        if (this->ima) { //прави copy на жичарата само кога постои
            this->zichara = new Zichara(*pd.zichara);
        }
    }
public:
    PlaninarskiDom(){
        ceni=new int[2];
        ima=false;
    }
    PlaninarskiDom(char *ime, int *ceni,char klasa){
        strcpy(this->ime,ime);
        this->ceni=new int[2];
        for(int i=0;i<2;i++) {
            this->ceni[i] = ceni[i];
        }
        this->klasa = klasa;
        ima=false;
    }
    PlaninarskiDom(const PlaninarskiDom &pd){
        copy(pd);
    }
    PlaninarskiDom operator=(const PlaninarskiDom &pd){
        if(this!=&pd){
            delete[] ceni;
            if (ima) delete zichara; //бришеме стара жичара ако постои
            copy(pd);
        }
        return *this;
    }
    ~PlaninarskiDom(){
        delete[] ceni;
        if (ima) {
            delete zichara;
        }
    }
    friend ostream &operator<<(ostream &out, PlaninarskiDom &pd){
        out<<pd.ime<<" klasa:"<<pd.klasa;
        if (pd.ima){
            out<<" so Zichara";
        }
        out<<endl;
        return out;
    }
    void setZichara(Zichara z){
        this->ima=true;
        this->zichara=new Zichara(z);
    }
    void operator--(){
        if (klasa!='F')
            this->klasa++;
    }
    bool operator<=(char k){
        if(this->klasa>=k) return true;
        else return false;
    }
    void presmetajDnevenPrestoj(int den,int mesec,int &cena){
        if (mesec<1 || mesec>12 ||den<1 || den>31) throw 1;
        if (mesec>=4 && mesec<=8){
            cena=0;
            cena+=this->ceni[0];
            if (this->ima)
                cena+=this->zichara->getCena();
        }
        else {
            cena=0;
            cena+=this->ceni[1];
            if (this->ima)
                cena+=this->zichara->getCena();
        }
    }
};

// не менуваш ништо во main

int main(){
    PlaninarskiDom p; //креирање на нов објект од класата планинарски дом

    //во следниот дел се вчитуваат информации за планинарскиот дом
    char imePlaninarskiDom[15],mestoZichara[30],klasa;
    int ceni[12];
    int dnevnakartaZichara;
    bool daliZichara;
    cin>>imePlaninarskiDom;
    for (int i=0;i<2;i++) cin>>ceni[i];
    cin>>klasa;
    cin>>daliZichara;

    //во следниот дел се внесуваат информации и за жичарата ако постои
    if (daliZichara) {
        cin>>mestoZichara>>dnevnakartaZichara;
        PlaninarskiDom pom(imePlaninarskiDom,ceni,klasa);
        Zichara r(mestoZichara,dnevnakartaZichara);
        pom.setZichara(r);
        p=pom;
    }
    else{
        PlaninarskiDom *pok=new PlaninarskiDom(imePlaninarskiDom,ceni,klasa);
        p=*pok;
    }

    //се намалува класата на планинарскиот дом за 2
    --p;
    --p;

    int cena;
    int den,mesec;
    cin>>den>>mesec;
    try{
        p.presmetajDnevenPrestoj(den,mesec,cena);
        cout<<"Informacii za PlaninarskiDomot:"<<endl;
        cout<<p;
        if (p<='D')
            cout<<"Planinarskiot dom za koj se vneseni informaciite ima klasa poniska ili ista so D\n";

        cout<<"Cenata za "<<den<<"."<<mesec<<" e "<<cena; //се печати цената за дадениот ден и месец
    }
    catch (int){
        cout<<"Mesecot ili denot e greshno vnesen!";
    }
}
