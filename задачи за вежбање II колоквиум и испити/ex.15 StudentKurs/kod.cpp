#include<iostream>
#include<cstring>
using namespace std;

class StudentKurs{
protected:
    char ime[30];
    int ocenka;
    bool usno;
public:
    static int M;
    StudentKurs(char *ime,int finalenIspit){
        strcpy(this->ime,ime);
        this->ocenka=finalenIspit;
        this->usno=false;
    }
    static void setMAX(int val){
        M=val;
    }
    virtual ~StudentKurs(){}
    StudentKurs(const StudentKurs &u){
        strcpy(this->ime,u.ime);
        this->ocenka=u.ocenka;
        this->usno=u.usno;
    }
    bool getDaliUsno(){
        return usno;
    }
    char *getIme(){
        return ime;
    }
    virtual int osvoeniPoeni(){
        return ocenka;
    }
    friend ostream &operator<<(ostream &o,StudentKurs &u){
        o<<u.ime<<" --- "<<u.osvoeniPoeni()<<endl;
        return o;
    }
};

int StudentKurs::M=10;
class BadInputException{
public:
    void print(){
        cout<<"Greshna opisna ocenka"<<endl;
    }
};
class StudentKursUsno: public StudentKurs{
private:
    char *poeni;
public:
    ~StudentKursUsno(){
        delete []poeni;
    }
    StudentKursUsno(char *ime,int finalenIspit):StudentKurs(ime,finalenIspit){
        this->usno=true;
        poeni=new char[0];
    }
    StudentKursUsno(const StudentKursUsno &u):StudentKurs(u){
        poeni=new char[strlen(u.poeni)+1];
        strcpy(poeni,u.poeni);
    }
    int osvoeniPoeni(){
        if (strcmp(poeni,"odlicen")==0&&StudentKurs::osvoeniPoeni()<M-1)
            return StudentKurs::osvoeniPoeni() + 2;
        if (strcmp(poeni,"odlicen")==0&&StudentKurs::osvoeniPoeni()==M-1)
            return StudentKurs::osvoeniPoeni() + 1;
        if (strcmp(poeni,"dobro")==0&&StudentKurs::osvoeniPoeni()<M)
            return StudentKurs::osvoeniPoeni() + 1;
        if (strcmp(poeni,"losho")==0 && StudentKurs::osvoeniPoeni()>0)
            return StudentKurs::osvoeniPoeni() - 1;
        return StudentKurs::osvoeniPoeni();
    }
    friend void operator +=(StudentKursUsno &u,char *novi){
        bool dali=false;
        for (int i=0;i<strlen(novi);i++)
            if (!isalpha(novi[i])) {dali=true; }
        if (dali) throw BadInputException();
        delete [] u.poeni;
        u.poeni=new char[strlen(novi)+1];
        strcpy(u.poeni,novi);
    }
};

class KursFakultet{
private:
    char naziv[30];
    StudentKurs *studenti[20];
    int broj;
    int const static P=6;
public:
    KursFakultet(char *naziv, StudentKurs **studenti,int broj ){
        strcpy(this->naziv,naziv);
        for (int i=0;i<broj;i++){
            //ako studentot ima usno isprashuvanje
            if (studenti[i]->getDaliUsno()){
                this->studenti[i]=new StudentKursUsno(*dynamic_cast<StudentKursUsno*>(studenti[i]));
            }
            else this->studenti[i]=new StudentKurs(*studenti[i]);
        }
        this->broj=broj;
    }
    ~KursFakultet(){
        for (int i=0;i<broj;i++) delete studenti[i];
    }
    void pecatiStudenti(){
        cout<<"Kursot "<<naziv<<" go polozile:"<<endl;
        for (int i=0;i<broj;i++)
            if (studenti[i]->osvoeniPoeni()>=P) cout<<(*studenti[i]);
    }
    void postaviOpisnaOcenka(char *ime,char * poeniA){
        for (int i=0;i<broj;i++)
            if (strcmp(studenti[i]->getIme(),ime)==0)
            {
                StudentKursUsno* nov=dynamic_cast<StudentKursUsno*>(studenti[i]);
                if (nov!=0){
                    (*nov)+=poeniA;
                }
            }
    }
};



int main(){
    StudentKurs **niza;
    int n,m,ocenka;
    char ime[30],opisna[10];
    bool daliUsno;
    cin>>n;
    niza=new StudentKurs*[n];
    for (int i=0;i<n;i++){
        cin>>ime;
        cin>>ocenka;
        cin>>daliUsno;
        if (!daliUsno)
            niza[i]=new StudentKurs(ime,ocenka);
        else
            niza[i]=new StudentKursUsno(ime,ocenka);
    }
    KursFakultet programiranje("OOP",niza,n);
    for (int i=0;i<n;i++) delete niza[i];
    delete [] niza;
    cin>>m;
    for (int i=0;i<m;i++){
        cin>>ime>>opisna;
        try{
            programiranje.postaviOpisnaOcenka(ime,opisna);
        }
        catch(BadInputException i){
            char nova[10];int k=0;
            for  (int j=0;j<strlen(opisna);j++) if (isalpha(opisna[j])) nova[k++]=opisna[j];
            nova[k]=0;
            programiranje.postaviOpisnaOcenka(ime,nova);
            i.print();
        }
    }
    StudentKurs::setMAX(9);
    programiranje.pecatiStudenti();

}
