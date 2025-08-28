#include<iostream>
#include<cstring>
using namespace std;

class NoCourseException{
private:
    int indeks;
public:
    NoCourseException(int indeks){
        this->indeks=indeks;
    }
    void print(){
        cout<<"Demonstratorot so indeks "<<indeks<<" ne drzi laboratoriski vezbi\n";
    }
};

class Kurs{
private:
    char ime[20];
    int krediti;
public:
    Kurs (const char *ime,int krediti){
        strcpy(this->ime,ime);
        this->krediti=krediti;
    }
    Kurs (){
        strcpy(this->ime,"");
        krediti=0;
    }
    bool operator==(const char *ime) const{
        return strcmp(this->ime,ime)==0;
    }
    void pecati ()const{cout<<ime<<" "<<krediti<<"ECTS";}
};

class Student{
private:
    int *ocenki;
    int brOcenki;
    void copy(const Student &s){
        this->indeks=s.indeks;
        this->brOcenki=s.brOcenki;
        this->ocenki=new int[s.brOcenki];
        for (int i=0;i<s.brOcenki;i++) {
            this->ocenki[i]=s.ocenki[i];
        }
    }
protected:
    int indeks;
public:
    Student(int indeks,int *ocenki, int brOcenki){
        this->indeks=indeks;
        this->brOcenki=brOcenki;
        this->ocenki=new int[brOcenki];
        for (int i=0;i<brOcenki;i++) this->ocenki[i]=ocenki[i];
    }
    Student(const Student &s){
        copy(s);
    }
    Student operator=(const Student &s){
        if (this!=&s) {
            delete [] ocenki;
            copy(s);
        }
        return *this;
    }
    virtual ~Student(){
        delete [] ocenki;
    }
    virtual int getBodovi() {
        int count=0;
        for (int i=0;i<brOcenki;i++) {
            if (ocenki[i]>5) count++;
        }
        return (count*100)/brOcenki;
    }
    virtual void pecati(){
        cout<<indeks;
    }
};
class Predavach{
private:
    Kurs kursevi[10];
    int brKursevi;
    void copy(const Predavach &p){
        this->brKursevi=p.brKursevi;
        for (int i=0;i<p.brKursevi;i++) this->kursevi[i]=p.kursevi[i];
        this->ime=new char[strlen(p.ime)+1];
        strcpy(this->ime,p.ime);
    }
protected:
    char *ime;
public:
    Predavach(const char *ime,Kurs *kursevi,int brKursevi){
        this->brKursevi=brKursevi;
        for (int i=0;i<brKursevi;i++) {
            this->kursevi[i]=kursevi[i];
        }
        this->ime=new char[strlen(ime)+1];
        strcpy(this->ime,ime);
    }
    Predavach(const Predavach &p){
        copy(p);
    }
    Predavach operator=(const Predavach &p){
        if (this!=&p) {
            delete[] ime;
            copy(p);
        }
        return *this;
    }
    virtual ~Predavach(){
        delete[] ime;
    }
    int getBrojKursevi() const {
        return brKursevi;
    }
    Kurs operator[](int i) const {
        if (i<brKursevi && i>=0) {
            return kursevi[i];
        }else {
            return Kurs();
        }
    }
    void pecati() const  {
        cout<<ime<<" (";
        for (int i=0;i<brKursevi;i++)
        {kursevi[i].pecati();
            if (i<brKursevi-1) cout<<", ";
            else cout<<")";
        }
    }
};

class Demonstrator:public Student, public Predavach{
private:
    int brCasovi;
public:
    Demonstrator(int indeks,int *ocenki, int brOcenki,const char *ime,Kurs *kursevi, int brKursevi,int brCasovi)
            :Student(indeks,ocenki,brOcenki),Predavach(ime,kursevi,brKursevi) {
        this->brCasovi=brCasovi;
    }
    void pecati(){
        Student::pecati();
        cout<<": ";
        Predavach::pecati();
    }
    int getBodovi() {
        if (Predavach::getBrojKursevi()==0) {
            throw NoCourseException(indeks);
        }
        return Student::getBodovi()+(20*brCasovi)/Predavach::getBrojKursevi();
    }
};

Student &vratiNajdobroRangiran(Student **studenti, int n ) {
    int max=0,max_ind=-1;
    for (int i=0;i<n;i++){
        try{
            if (studenti[i]->getBodovi()>max) {
                max=studenti[i]->getBodovi();
                max_ind=i;
            }
        }catch(NoCourseException e){e.print();}
    }
    return (*studenti[max_ind]);
}
void pecatiDemonstratoriKurs(char *kurs, Student **studenti, int n){
    for (int i=0;i<n;i++){
        Demonstrator* dPok = dynamic_cast<Demonstrator*> (studenti[i]);
        if (dPok!=0) {
            int m=dPok->getBrojKursevi();
            for (int j=0;j<m;j++)
                if ((*dPok)[j]==kurs) {dPok->pecati(); cout<<endl;}
        }
    }
}

//не менуваш ништо во main

int main(){
    Kurs kursevi[10];
    int indeks,brojKursevi, ocenki[20],ocenka,brojOcenki,tip,brojCasovi,krediti;
    char ime[20],imeIPrezime[50];

    cin>>tip;

    if (tip==1) //test class Demonstrator
    {
        cout<<"-----TEST Demonstrator-----"<<endl;
        cin>>indeks>>brojOcenki;
        for (int i=0;i<brojOcenki;i++){
            cin>>ocenka;
            ocenki[i]=ocenka;
        }
        cin>>imeIPrezime>>brojKursevi;
        for (int i=0;i<brojKursevi;i++){
            cin>>ime>>krediti;
            kursevi[i]=Kurs(ime,krediti);
        }
        cin>>brojCasovi;

        Demonstrator d(indeks,ocenki,brojOcenki,imeIPrezime,kursevi,brojKursevi,brojCasovi);
        cout<<"Objekt od klasata Demonstrator e kreiran";

    } else if (tip==2) //funkcija pecati vo Student
    {
        cout<<"-----TEST pecati-----"<<endl;
        cin>>indeks>>brojOcenki;
        for (int i=0;i<brojOcenki;i++){
            cin>>ocenka;
            ocenki[i]=ocenka;
        }

        Student s(indeks,ocenki,brojOcenki);
        s.pecati();

    } else if (tip==3) //funkcija getVkupnaOcenka vo Student
    {
        cout<<"-----TEST getVkupnaOcenka-----"<<endl;
        cin>>indeks>>brojOcenki;
        for (int i=0;i<brojOcenki;i++){
            cin>>ocenka;
            ocenki[i]=ocenka;
        }
        Student s(indeks,ocenki,brojOcenki);
        cout<<"Broj na bodovi: "<<s.getBodovi()<<endl;

    } else if (tip==4) //funkcija getVkupnaOcenka vo Demonstrator
    {
        cout<<"-----TEST getVkupnaOcenka-----"<<endl;
        cin>>indeks>>brojOcenki;
        for (int i=0;i<brojOcenki;i++){
            cin>>ocenka;
            ocenki[i]=ocenka;
        }
        cin>>imeIPrezime>>brojKursevi;
        for (int i=0;i<brojKursevi;i++){
            cin>>ime>>krediti;
            kursevi[i]=Kurs(ime,krediti);
        }
        cin>>brojCasovi;

        Demonstrator d(indeks,ocenki,brojOcenki,imeIPrezime,kursevi,brojKursevi,brojCasovi);
        cout<<"Broj na bodovi: "<<d.getBodovi()<<endl;

    } else if (tip==5) //funkcija pecati vo Demonstrator
    {
        cout<<"-----TEST pecati -----"<<endl;
        cin>>indeks>>brojOcenki;
        for (int i=0;i<brojOcenki;i++){
            cin>>ocenka;
            ocenki[i]=ocenka;
        }
        cin>>imeIPrezime>>brojKursevi;
        for (int i=0;i<brojKursevi;i++){
            cin>>ime>>krediti;
            kursevi[i]=Kurs(ime,krediti);
        }
        cin>>brojCasovi;

        Demonstrator d(indeks,ocenki,brojOcenki,imeIPrezime,kursevi,brojKursevi,brojCasovi);
        d.pecati();

    } else if (tip==6) //site klasi
    {
        cout<<"-----TEST Student i Demonstrator-----"<<endl;
        cin>>indeks>>brojOcenki;
        for (int i=0;i<brojOcenki;i++){
            cin>>ocenka;
            ocenki[i]=ocenka;
        }
        cin>>imeIPrezime>>brojKursevi;
        for (int i=0;i<brojKursevi;i++){
            cin>>ime>>krediti;
            kursevi[i]=Kurs(ime,krediti);
        }
        cin>>brojCasovi;

        Student *s=new Demonstrator(indeks,ocenki,brojOcenki,imeIPrezime,kursevi,brojKursevi,brojCasovi);
        s->pecati();
        cout<<"\nBroj na bodovi: "<<s->getBodovi()<<endl;
        delete s;


    } else if (tip==7) //funkcija vratiNajdobroRangiran
    {
        cout<<"-----TEST vratiNajdobroRangiran-----"<<endl;
        int k, opt;
        cin>>k;
        Student **studenti=new Student*[k];
        for (int j=0;j<k;j++){
            cin>>opt; //1 Student 2 Demonstrator
            cin>>indeks>>brojOcenki;
            for (int i=0;i<brojOcenki;i++)
            {
                cin>>ocenka;
                ocenki[i]=ocenka;
            }
            if (opt==1){
                studenti[j]=new Student(indeks,ocenki,brojOcenki);
            }else{
                cin>>imeIPrezime>>brojKursevi;
                for (int i=0;i<brojKursevi;i++)
                {
                    cin>>ime>>krediti;
                    kursevi[i]=Kurs(ime,krediti);
                }
                cin>>brojCasovi;
                studenti[j]=new Demonstrator(indeks,ocenki,brojOcenki,imeIPrezime,kursevi,brojKursevi,brojCasovi);
            }
        }
        Student& najdobar=vratiNajdobroRangiran(studenti,k);
        cout<<"Maksimalniot broj na bodovi e:"<<najdobar.getBodovi();
        cout<<"\nNajdobro rangiran:";
        najdobar.pecati();

        for (int j=0;j<k;j++) delete studenti[j];
        delete [] studenti;

    } else if (tip==8) //funkcija pecatiDemonstratoriKurs
    {
        cout<<"-----TEST pecatiDemonstratoriKurs-----"<<endl;
        int k, opt;
        cin>>k;
        Student **studenti=new Student*[k];
        for (int j=0;j<k;j++){
            cin>>opt; //1 Student 2 Demonstrator
            cin>>indeks>>brojOcenki;
            for (int i=0;i<brojOcenki;i++)
            {
                cin>>ocenka;
                ocenki[i]=ocenka;
            }
            if (opt==1){
                studenti[j]=new Student(indeks,ocenki,brojOcenki);
            }else{
                cin>>imeIPrezime>>brojKursevi;
                for (int i=0;i<brojKursevi;i++)
                {
                    cin>>ime>>krediti;
                    kursevi[i]=Kurs(ime,krediti);
                }
                cin>>brojCasovi;
                studenti[j]=new Demonstrator(indeks,ocenki,brojOcenki,imeIPrezime,kursevi,brojKursevi,brojCasovi);
            }
        }
        char kurs[20];
        cin>>kurs;
        cout<<"Demonstratori na "<<kurs<<" se:"<<endl;
        pecatiDemonstratoriKurs (kurs,studenti,k);
        for (int j=0;j<k;j++) delete studenti[j];
        delete [] studenti;
    }

    return 0;
}

