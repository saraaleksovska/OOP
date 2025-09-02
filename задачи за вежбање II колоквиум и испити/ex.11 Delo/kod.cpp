#include<iostream>
#include<cstring>

using namespace std;

class Delo{
private:
    char ime[50];
    int godina;
    char zemja[50];
public:
    Delo(){}
    Delo(char *ime,int godina,char *zemja){
        strcpy(this->ime, ime);
        this->godina=godina;
        strcpy(this->zemja, zemja);
    }
    bool operator==(Delo d){
        return strcmp(ime,d.ime)==0;
    }
    char *getIme(){
        return ime;
    }
    int getGodina(){return godina;}
    char *getZemja(){return zemja;}
};
class Pretstava{
private:
    Delo delo;
    int n;
    char datum[15];
protected:
    double pomCena(){
        int M=0,N=0;
        if (delo.getGodina()>=1900 && delo.getGodina()<2100) M=50;
        else if (delo.getGodina()<1900 && delo.getGodina()>=1800) M=75;
        else M=100; //dali za 50 e 75 ili 100
        if (strcmp(delo.getZemja(),"Italija")==0) N=100;
        else if (strcmp(delo.getZemja(),"Rusija")==0) N=150;
        else N=80;
        return N+M;
    }

public:
    Pretstava(Delo delo,int n,char *datum){
        this->delo=delo;
        this->n=n;
        strcpy(this->datum, datum);
    }
    int getBrojProdadeni(){
        return n;
    }
    Delo getDelo(){
        return delo;
    }
    virtual double cena()=0;
};

class Balet: public Pretstava{
    static int dodadic;
public:
    Balet(Delo f,int brs,char *d):Pretstava(f,brs,d){
    }
    double cena(){
        return Pretstava::pomCena()+dodadic;
    }
    static void setCenaBalet(int cena){
        dodadic=cena;
    }
};
int Balet::dodadic=150;

class Opera: public Pretstava{
public:
    Opera(Delo delo,int brs,char *d):Pretstava(delo,brs,d){
    }
    double cena(){
        return Pretstava::pomCena();
    }
};

double prihod(Pretstava **pole,int n){
    double sum=0;
    for (int i=0;i<n;i++){
        sum+=pole[i]->cena()*pole[i]->getBrojProdadeni();
    }
    return sum;
}
int brojPretstaviNaDelo (Pretstava **p, int n, Delo d){
    int brojsite=0,broj2d=0,broj3d=0;
    for (int i=0;i<n;i++){
        if (p[i]->getDelo()==d){
            brojsite++;
        }
            Balet *pom3= dynamic_cast<Balet*>(p[i]);
            if (pom3!=0) broj3d++;
            else continue;
            Opera *pom2= dynamic_cast<Opera*>(p[i]);
            if (pom2!=0) broj2d++;
            else continue;
        }
    return brojsite;
}

Delo readDelo(){
    char ime[50];
    int godina;
    char zemja[50];
    cin>>ime>>godina>>zemja;
    return Delo(ime,godina,zemja);
}
Pretstava *readPretstava(){
    int tip; //0 za Balet , 1 za Opera
    cin>>tip;
    Delo d=readDelo();
    int brojProdadeni;
    char data[15];
    cin>>brojProdadeni>>data;
    if (tip==0) {
        return new Balet(d,brojProdadeni,data);
    }else return new Opera(d,brojProdadeni,data);
}


int main(){
    int test_case;
    cin>>test_case;
    switch(test_case){
        case 1:
//Testiranje na klasite Opera i Balet
        {
            cout<<"======TEST CASE 1======="<<endl;
            Pretstava* p1=readPretstava();
            cout<<p1->getDelo().getIme()<<endl;
            Pretstava* p2=readPretstava();
            cout<<p2->getDelo().getIme()<<endl;
        }break;
        case 2:
//Testiranje na  klasite Opera i Balet so cena
        {cout<<"======TEST CASE 2======="<<endl;
            Pretstava* p1=readPretstava();
            cout<<p1->cena()<<endl;
            Pretstava* p2=readPretstava();
            cout<<p2->cena()<<endl;}
            break;
        case 3:
//Testiranje na operator ==
        {cout<<"======TEST CASE 3======="<<endl;
            Delo f1=readDelo();
            Delo f2=readDelo();
            Delo f3=readDelo();

            if (f1==f2) cout<<"Isti se"<<endl; else cout<<"Ne se isti"<<endl;
            if (f1==f3) cout<<"Isti se"<<endl; else cout<<"Ne se isti"<<endl;
        }
            break;

        case 4:
//testiranje na funkcijata prihod
        {cout<<"======TEST CASE 4======="<<endl;
            int n;
            cin>>n;
            Pretstava **pole=new Pretstava*[n];
            for (int i=0;i<n;i++){
                pole[i]=readPretstava();
            }
            cout<<prihod(pole,n);}
            break;

        case 5:
//testiranje na prihod so izmena na cena za 3d proekcii
        {cout<<"======TEST CASE 5======="<<endl;
            int cenaBalet;
            cin>>cenaBalet;
            Balet::setCenaBalet(cenaBalet);
            int n;
            cin>>n;
            Pretstava **pole=new Pretstava*[n];
            for (int i=0;i<n;i++){
                pole[i]=readPretstava();
            }
            cout<<prihod(pole,n);}
            break;
        case 6:
//testiranje na brojPretstaviNaDelo
        {cout<<"======TEST CASE 6======="<<endl;
            int n;
            cin>>n;
            Pretstava **pole=new Pretstava*[n];
            for (int i=0;i<n;i++){
                pole[i]=readPretstava();
            }
            Delo f=readDelo();
            cout<<brojPretstaviNaDelo(pole,n,f);}
            break;
    };
    return 0;
}
