#include <iostream>
#include <cstring>
using namespace std;

class Gitara{
private:
    char seriski[25];
    double nabavna;
    int godinaProizvodstvo;
    char tip[40];
    void copy(const Gitara &g){
        strcpy(this->tip,g.tip);
        strcpy(this->seriski,g.seriski);
        this->godinaProizvodstvo = g.godinaProizvodstvo;
        this->nabavna = g.nabavna;
    }
public:
    Gitara(const char *tip="",const char *seriski ="", int godinaProizvodstvo=0, double nabavna=0){
        strcpy(this->tip,tip);
        strcpy(this->seriski,seriski);
        this->godinaProizvodstvo = godinaProizvodstvo;
        this->nabavna = nabavna;
    }
    Gitara(const Gitara &g){
       copy(g);
    }
    Gitara &operator=(const Gitara &g){
        strcpy(this->tip,g.tip);
        strcpy(this->seriski,g.seriski);
        this->godinaProizvodstvo = g.godinaProizvodstvo;
        this->nabavna = g.nabavna;
        return *this;
    }
    ~Gitara(){}
    bool daliIsti(Gitara &g){
        return strcmp(this->seriski,g.seriski)==0;
    }
    void pecati(){
        cout<<seriski<<" "<<tip<<" "<<nabavna<<endl;
    }
    double getNabavna(){return nabavna;}

    char *getTip(){return tip;}
    char *getSeriski(){return seriski;}
    int getGodina(){return godinaProizvodstvo;}
};

class Magacin{
private:
    char lokacija[60];
    char ime[50];
    int godinaOtvaranje;
    Gitara *gitari;
    int n;
    void copy(const Magacin &m){
        strcpy(this->lokacija,m.lokacija);
        strcpy(this->ime,m.ime);
        this->godinaOtvaranje = m.godinaOtvaranje;
        gitari = new Gitara[m.n];
        for(int i =0;i<m.n;i++) {
            gitari[i] = m.gitari[i];
        }
        n = m.n;
    }
public:
    Magacin(const char *ime="", const char *lokacija="", int godinaOtvaranje=0){
        strcpy(this->lokacija,lokacija);
        strcpy(this->ime,ime);
        this->godinaOtvaranje = godinaOtvaranje;
        gitari = NULL;
        n = 0;
    }
    Magacin(const Magacin &m){
       copy(m);
    }
    Magacin &operator=(const Magacin & m){
        copy(m);
        return *this;
    }
    ~Magacin(){
        delete[] gitari;
    }
    double vrednost(){
        double sum=0;
        for(int i=0;i<n;i++)
            sum+=gitari[i].getNabavna();
        return sum;
    }
    void dodadi(Gitara &g){
        Gitara *tmp = new Gitara[n+1];
        for(int i=0;i<n;i++)
            tmp[i] = gitari[i];
        tmp[n++]=g;
        delete[] gitari;
        gitari=tmp;
    }
    void prodadi(Gitara &g){
        int newBr = 0;
        for(int i=0;i<n;i++){
            if(gitari[i].daliIsti(g)==false){
                newBr++;
            }
        }
        Gitara *tmp = new Gitara[newBr];
        int j=0;
        for(int i=0;i<n;i++){
            if(gitari[i].daliIsti(g)==false){
                tmp[j] = gitari[i];
                j++;
            }
        }
        delete[] gitari;
        gitari = tmp;
        n = newBr;
    }
    void pecati(bool daliNovi){
        cout<<ime<<" "<< lokacija<<endl;
        for(int i=0;i<n;i++){
            if(daliNovi==true && gitari[i].getGodina()>godinaOtvaranje){
                gitari[i].pecati();
            }
            else if(daliNovi==false){
                gitari[i].pecati();
            }
        }
    }
};

//не менуваш ништо во main

int main() {
    // se testira zadacata modularno
    int testCase;
    cin >> testCase;
    int n, godina;
    float cena;
    char seriski[50],tip[50];
    if(testCase == 1) {
        cout << "===== Testiranje na klasata Gitara ======" << endl;
        cin>>tip;
        cin>>seriski;
        cin >> godina;
        cin >> cena;
        Gitara g(tip,seriski, godina,cena);
        cout<<g.getTip()<<endl;
        cout<<g.getSeriski()<<endl;
        cout<<g.getGodina()<<endl;
        cout<<g.getNabavna()<<endl;
    } else if(testCase == 2){
        cout << "===== Testiranje na klasata Magacin so metodot print() ======" << endl;
        Magacin kb("Magacin1","Lokacija1");
        kb.pecati(false);
    }
    else if(testCase == 3) {
        cout << "===== Testiranje na klasata Magacin so metodot dodadi() ======" << endl;
        Magacin kb("Magacin1","Lokacija1",2005);
        cin>>n;
        for (int i=0;i<n;i++){
            cin>>tip;
            cin>>seriski;
            cin >> godina;
            cin >> cena;
            Gitara g(tip,seriski, godina,cena);
            cout<<"gitara dodadi"<<endl;
            kb.dodadi(g);
        }
        kb.pecati(true);
    }
    else if(testCase == 4) {
        cout << "===== Testiranje na klasata Magacin so metodot prodadi() ======" << endl;
        Magacin kb("Magacin1","Lokacija1",2012);
        cin>>n;
        Gitara brisi;
        for (int i=0;i<n;i++){
            cin>>tip;
            cin>>seriski;
            cin >> godina;
            cin >> cena;
            Gitara g(tip,seriski, godina,cena);
            if(i==2)
                brisi=g;
            cout<<"gitara dodadi"<<endl;
            kb.dodadi(g);
        }
        kb.pecati(false);
        kb.prodadi(brisi);
        kb.pecati(false);
    }
    else if(testCase == 5) {
        cout << "===== Testiranje na klasata Magacin so metodot prodadi() i pecati(true) ======" << endl;
        Magacin kb("Magacin1","Lokacija1",2011);
        cin>>n;
        Gitara brisi;
        for (int i=0;i<n;i++){
            cin>>tip;
            cin>>seriski;
            cin >> godina;
            cin >> cena;

            Gitara g(tip,seriski, godina,cena);
            if(i==2)
                brisi=g;
            cout<<"gitara dodadi"<<endl;
            kb.dodadi(g);
        }
        kb.pecati(true);
        kb.prodadi(brisi);
        cout<<"Po brisenje:"<<endl;
        Magacin kb3;
        kb3=kb;
        kb3.pecati(true);
    }
    else if(testCase ==6){
        cout << "===== Testiranje na klasata Magacin so metodot vrednost()======" << endl;
        Magacin kb("Magacin1","Lokacija1",2011);
        cin>>n;
        Gitara brisi;
        for (int i=0;i<n;i++){
            cin>>tip;
            cin>>seriski;
            cin >> godina;
            cin >> cena;
            Gitara g(tip,seriski, godina,cena);
            if(i==2)
                brisi=g;
            kb.dodadi(g);
        }
        cout<<kb.vrednost()<<endl;
        kb.prodadi(brisi);
        cout<<"Po brisenje:"<<endl;
        cout<<kb.vrednost();
        Magacin kb3;
        kb3=kb;
    }
    return 0;
}
