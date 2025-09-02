#include<iostream>
#include<cstring>
using namespace std;

class Exception{
public:
    void print(){
        cout << "Ne moze da se vnese dadeniot trud" << endl;
    }
};

class Trud{
private:
    char tip;
    int god;
public:
    Trud(const char tip = 'C', int god = 0){
        this->tip = toupper(tip);
        this->god = god;
    }
    int getGod(){
        return god;
    }
    char getTip(){
        return tip;
    }
    friend istream &operator>>(istream &in, Trud &t){
        in >> t.tip >> t.god;
        return in;
    }
};

class Student{
private:
    char ime[30];
    int indeks;
    int god;
    int oceni[50];
    int n;
public:
    Student(){}
    Student(const char *ime, int indeks, int god, int *oceni, int n){
        strcpy(this->ime, ime);
        this->indeks = indeks;
        this->god = god;
        this->n = n;
        for (int i = 0; i < n; i++)
            this->oceni[i] = oceni[i];
    }
    int getGod(){
        return god;
    }
    int getIndeks(){
        return indeks;
    }
    virtual float rang(){
        int suma = 0;
        for (int i = 0; i < n; i++)
            suma += oceni[i];
        return (float)suma / n;
    }
    friend ostream &operator<< (ostream &o, Student &s){
        o << s.indeks << " " << s.ime << " " << s.god << " " << s.rang() << endl;
        return o;
    }
    virtual ~Student(){}
};

class PhDStudent : public Student{
private:
    Trud *trudovi;
    int nt;
    static int konferenciski;
    static int spisanie;
public:
    PhDStudent(const char *ime, int indeks, int god, int *oceni, int n, Trud* trudovi, int nt) :Student(ime, indeks, god, oceni, n){
        this->trudovi = new Trud[100];
        int ok=0;
        for (int i = 0; i < nt; i++){
            try{
                if (this->getGod() > trudovi[i].getGod()) throw Exception();
                this->trudovi[ok] = trudovi[i];
                ok++;
            }
            catch (Exception e){
                e.print();
            }
        }
        this->nt = ok;
    }
    float rang(){
        int suma = 0;
        for (int i = 0; i < nt; i++){
            if (trudovi[i].getTip() == 'C')
                suma += konferenciski;
            else
                suma += spisanie;
        }
        return Student::rang() + suma;
    }
    static void setConf(int c){
        PhDStudent::konferenciski = c;
    }
    static void setJournal(int j){
        PhDStudent::spisanie = j;
    }
    void operator+=(Trud &tr){
        if (this->getGod() > tr.getGod()) throw Exception();
        this->trudovi[nt] = tr;
        this->nt++;
    }
    ~PhDStudent(){
        delete[] trudovi;
    }
};
int PhDStudent::konferenciski = 1;
int PhDStudent::spisanie = 3;


int main(){
    int testCase;
    cin >> testCase;
    int god, indeks, n, god_tr, m, n_tr;
    int izbor; //0 za Student, 1 za PhDStudent
    char ime[30];
    int oceni[50];
    char tip;
    Trud trud[50];

    if (testCase == 1){
        cout << "===== Testiranje na klasite ======" << endl;
        cin >> ime;
        cin >> indeks;
        cin >> god;
        cin >> n;
        for (int j = 0; j < n; j++)
            cin >> oceni[j];
        Student s(ime, indeks, god, oceni, n);
        cout << s;

        cin >> ime;
        cin >> indeks;
        cin >> god;
        cin >> n;
        for (int j = 0; j < n; j++)
            cin >> oceni[j];
        cin >> n_tr;
        for (int j = 0; j < n_tr; j++){
            cin >> tip;
            cin >> god_tr;
            Trud t(tip, god_tr);
            trud[j] = t;
        }
        PhDStudent phd(ime, indeks, god, oceni, n, trud, n_tr);
        cout << phd;
    }
    if (testCase == 2){
        cout << "===== Testiranje na operatorot += ======" << endl;
        Student **niza;
        cin >> m;
        niza = new Student *[m];
        for (int i = 0; i<m; i++){
            cin >> izbor;
            cin >> ime;
            cin >> indeks;
            cin >> god;
            cin >> n;
            for (int j = 0; j < n; j++)
                cin >> oceni[j];

            if (izbor == 0){
                niza[i] = new Student(ime, indeks, god, oceni, n);
            }
            else{
                cin >> n_tr;
                for (int j = 0; j < n_tr; j++){
                    cin >> tip;
                    cin >> god_tr;
                    Trud t(tip, god_tr);
                    trud[j] = t;
                }
                niza[i] = new PhDStudent(ime, indeks, god, oceni, n, trud, n_tr);
            }
        }
        // pecatenje na site studenti
        cout << "\nLista na site studenti:\n";
        for (int i = 0; i < m; i++)
            cout << *niza[i];

        // dodavanje nov trud za PhD student spored indeks
        Trud t;
        cin >> indeks;
        cin >> t;
        int flag = 1;
        for (int i = 0; i < m; i++){
            if ((*niza[i]).getIndeks() == indeks) {
                PhDStudent* nov = dynamic_cast<PhDStudent*>(niza[i]);
                if (nov != 0){
                    (*nov) += t;
                    flag = 0;
                    break;
                }
            }
        }
        if (flag)
            cout << "Ne postoi PhD student so indeks " << indeks << endl;


        // pecatenje na site studenti
        cout << "\nLista na site studenti:\n";
        for (int i = 0; i < m; i++)
            cout << *niza[i];
    }
    if (testCase == 3){
        cout << "===== Testiranje na operatorot += ======" << endl;
        Student **niza;
        cin >> m;
        niza = new Student *[m];
        for (int i = 0; i<m; i++){
            cin >> izbor;
            cin >> ime;
            cin >> indeks;
            cin >> god;
            cin >> n;
            for (int j = 0; j < n; j++)
                cin >> oceni[j];

            if (izbor == 0){
                niza[i] = new Student(ime, indeks, god, oceni, n);
            }
            else{
                cin >> n_tr;
                for (int j = 0; j < n_tr; j++){
                    cin >> tip;
                    cin >> god_tr;
                    Trud t(tip, god_tr);
                    trud[j] = t;
                }
                niza[i] = new PhDStudent(ime, indeks, god, oceni, n, trud, n_tr);
            }
        }
        // pecatenje na site studenti
        cout << "\nLista na site studenti:\n";
        for (int i = 0; i < m; i++)
            cout << *niza[i];

        // dodavanje nov trud za PhD student spored indeks
        Trud t;
        cin >> indeks;
        cin >> t;
        int flag = 1;
        for (int i = 0; i < m; i++){
            if ((*niza[i]).getIndeks() == indeks) {
                PhDStudent* nov = dynamic_cast<PhDStudent*>(niza[i]);
                if (nov != 0){
                    (*nov) += t;
                    flag = 0;
                    break;
                }
            }
        }
        if (flag)
            cout << "Ne postoi PhD student so indeks " << indeks << endl;


        // pecatenje na site studenti
        cout << "\nLista na site studenti:\n";
        for (int i = 0; i < m; i++)
            cout << *niza[i];
    }
    if (testCase == 4){
        cout << "===== Testiranje na isklucoci ======" << endl;
        cin >> ime;
        cin >> indeks;
        cin >> god;
        cin >> n;
        for (int j = 0; j < n; j++)
            cin >> oceni[j];
        cin >> n_tr;
        for (int j = 0; j < n_tr; j++){
            cin >> tip;
            cin >> god_tr;
            Trud t(tip, god_tr);
            trud[j] = t;
        }
        PhDStudent phd(ime, indeks, god, oceni, n, trud, n_tr);
        cout << phd;
    }
    if (testCase == 5){
        cout << "===== Testiranje na isklucoci ======" << endl;
        Student **niza;
        cin >> m;
        niza = new Student *[m];
        for (int i = 0; i<m; i++){
            cin >> izbor;
            cin >> ime;
            cin >> indeks;
            cin >> god;
            cin >> n;
            for (int j = 0; j < n; j++)
                cin >> oceni[j];

            if (izbor == 0){
                niza[i] = new Student(ime, indeks, god, oceni, n);
            }
            else{
                cin >> n_tr;
                for (int j = 0; j < n_tr; j++){
                    cin >> tip;
                    cin >> god_tr;
                    Trud t(tip, god_tr);
                    trud[j] = t;
                }
                niza[i] = new PhDStudent(ime, indeks, god, oceni, n, trud, n_tr);
            }
        }
        // pecatenje na site studenti
        cout << "\nLista na site studenti:\n";
        for (int i = 0; i < m; i++)
            cout << *niza[i];

        // dodavanje nov trud za PhD student spored indeks
        Trud t;
        cin >> indeks;
        cin >> t;
        int flag = 1;
        for (int i = 0; i < m; i++){
            if ((*niza[i]).getIndeks() == indeks) {
                PhDStudent* nov = dynamic_cast<PhDStudent*>(niza[i]);
                if (nov != 0){
                    try{
                        flag = 0;
                        (*nov) += t;
                        break;
                    }
                    catch (Exception e){
                        e.print();
                    }
                }
            }
        }
        if (flag)
            cout << "Ne postoi PhD student so indeks " << indeks << endl;


        // pecatenje na site studenti
        cout << "\nLista na site studenti:\n";
        for (int i = 0; i < m; i++)
            cout << *niza[i];
    }
    if (testCase == 6){
        cout << "===== Testiranje na static clenovi ======" << endl;
        Student **niza;
        cin >> m;
        niza = new Student *[m];
        for (int i = 0; i<m; i++){
            cin >> izbor;
            cin >> ime;
            cin >> indeks;
            cin >> god;
            cin >> n;
            for (int j = 0; j < n; j++)
                cin >> oceni[j];

            if (izbor == 0){
                niza[i] = new Student(ime, indeks, god, oceni, n);
            }
            else{
                cin >> n_tr;
                for (int j = 0; j < n_tr; j++){
                    cin >> tip;
                    cin >> god_tr;
                    Trud t(tip, god_tr);
                    trud[j] = t;
                }
                niza[i] = new PhDStudent(ime, indeks, god, oceni, n, trud, n_tr);
            }
        }
        // pecatenje na site studenti
        cout << "\nLista na site studenti:\n";
        for (int i = 0; i < m; i++)
            cout << *niza[i];

        int conf, journal;
        cin >> conf;
        cin >> journal;
        PhDStudent::setConf(conf);
        PhDStudent::setJournal(journal);

        // pecatenje na site studenti
        cout << "\nLista na site studenti:\n";
        for (int i = 0; i < m; i++)
            cout << *niza[i];
    }

    return 0;
}