#include<iostream>
#include<cstring>
using namespace std;

class Transport {
protected:
    char destinacija[10];
    int osnovna;
    int km;
public:
    Transport (char *destinacija,int osnovna,int km){
        strcpy(this->destinacija, destinacija);
        this->osnovna=osnovna;
        this->km=km;
    }
    int  getKm(){
        return km;
    }
    char  *getDest(){
        return destinacija;
    }
    virtual float cenaTransport(){
        return osnovna;
    }
    bool operator<(Transport s2){
        return (this->km<s2.km);
    }
};
class AvtomobilTransport:public Transport {
private:
    bool broj;
public:
    AvtomobilTransport(char *destinacija,int osnovna,int km,bool broj):Transport (destinacija,osnovna,km){
        this->broj=broj;
    }
    float cenaTransport(){
        if (broj) return (float)1.2*Transport ::cenaTransport();
        return Transport ::cenaTransport();
    }
};

class KombeTransport:public Transport {
private:
    int broj;
public:
    KombeTransport(char *destinacija,int osnovna,int km,int broj):Transport (destinacija,osnovna,km){
        this->broj=broj;
    }
    float cenaTransport(){
        return Transport ::cenaTransport()-broj*200;
    }
};

void pecatiPoloshiPonudi(Transport  **niza,int n,Transport &s){
    for (int i=0;i<n;i++){
        for(int j=i+1;j<n;j++){
            if ((*niza[j])<(*niza[i])){
                Transport* pom=niza[i];
                niza[i]=niza[j];
                niza[j]=pom;
            }
        }
    }
    for (int i=0;i<n;i++){
        if (niza[i]->cenaTransport()>s.cenaTransport()) {
            cout<<niza[i]->getDest();
            cout<<" "<<niza[i]->getKm();
            cout<<" "<<niza[i]->cenaTransport()<<endl;
        }
    }
}


int main(){
    char destinacija[20];
    int tip,cena,rastojanie,lugje;
    bool shofer;
    int n;
    cin>>n;
    Transport  **ponudi;
    ponudi=new Transport *[n];
    for (int i=0;i<n;i++){
        cin>>tip>>destinacija>>cena>>rastojanie;
        if (tip==1) {
            cin>>shofer;
            ponudi[i]=new AvtomobilTransport(destinacija,cena,rastojanie,shofer);
        }
        else {
            cin>>lugje;
            ponudi[i]=new KombeTransport(destinacija,cena,rastojanie,lugje);
        }
    }
    AvtomobilTransport nov("Ohrid",2000,600,false);
    pecatiPoloshiPonudi(ponudi,n,nov);
    for (int i=0;i<n;i++) delete ponudi[i];
    delete [] ponudi;

    return 0;
}
