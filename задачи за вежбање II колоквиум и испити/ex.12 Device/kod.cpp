#include <iostream>
#include <cstring>

using namespace std;

enum tip{
    smartfon, kompjuter
};

class InvalidRegistrationDate{
public:
    void print(){
        cout<<"Невалидна година на производство"<<endl;}
};

class Device{
private:
    char model[100];
    tip tip_;
    int godina;
    static int vremetraenje;
public:
    Device(char *model ="", tip tip_ = (tip)0, int godina =0){
        strcpy(this->model,model);
        this->tip_ = tip_;
        this->godina = godina;
    }
    int Casovi(){
        int v = vremetraenje;
        if(tip_==(tip)1){
            v+=2;
        }
        if(godina>2015)
            v+=2;
        return v;
    }
    int getGodina(){
        return godina;
    }
    friend ostream &operator<<(ostream &out, Device &i){
        out<<i.model<<endl;
        if(i.tip_==(tip)0){
            out<<"Mobilen";
        }else
            out<<"Laptop";
        out<<" "<<i.Casovi()<<endl;
        return out;
    }
    static void setPocetniCasovi(int newP){
        vremetraenje = newP;
    }
};
int Device::vremetraenje = 1;

class MobileServis {
private:
    char ime[100];
    Device *uredi;
    int n;
public:
    MobileServis(char * ime){
        this->uredi = NULL;
        n = 0;
        strcpy(this->ime, ime);
    }
    ~MobileServis(){
        delete [] uredi;
    }
    MobileServis(const MobileServis &m){
        strcpy(this->ime, m.ime);
        this->n = m.n;
        uredi = new Device[m.n];
        for(int i = 0;i<n;i++){
            this->uredi[i] = m.uredi[i];
        }
    }
    MobileServis &operator=(MobileServis &m){
        if(this!=&m){
            strcpy(this->ime, m.ime);
            this->n = m.n;
            delete [] uredi;
            uredi = new Device[m.n];
            for(int i = 0;i<n;i++){
                this->uredi[i] = m.uredi[i];
            }
        }
        return *this;
    }
    MobileServis &operator+=(Device &d){
        if(d.getGodina()>2019 || d.getGodina()<2000){
            throw InvalidRegistrationDate();
        }
        Device *tmp = new Device[n+1];
        for(int i=0;i<n;i++){
            tmp[i] = uredi[i];
        }
        tmp[n++] = d;
        delete [] uredi;
        uredi = tmp;
        return *this;
    }
    void pecatiCasovi(){
        cout<<"Ime: "<<ime<<endl;
        for(int i =0;i<n;i++)
            cout<<uredi[i];
    }
};

int main(){
    int testCase;
    cin >> testCase;
    char ime[100];
    int tipDevice;
    int godina;
    int n;
    Device devices[50];
    if (testCase == 1){
        cout << "===== Testiranje na klasite ======" << endl;
        cin >> ime;
        cin >> tipDevice;
        cin >> godina;
        Device ig(ime,(tip)tipDevice,godina);
        cin>>ime;
        MobileServis t(ime);
        cout<<ig;
    }
    if (testCase == 2){
        cout << "===== Testiranje na operatorot += ======" << endl;
        cin>>ime;
        cin >> n;
        MobileServis t(ime);
        for(int i=0;i<n;i++)
        {
            cin >> ime;
            cin >> tipDevice;
            cin >> godina;
            Device tmp(ime,(tip)tipDevice,godina);
            t+=tmp;
        }
        t.pecatiCasovi();
    }
    if (testCase == 3){
        cout << "===== Testiranje na isklucoci ======" << endl;
        cin>>ime;
        cin >> n;
        MobileServis t(ime);
        for(int i=0;i<n;i++)
        {
            cin >> ime;
            cin >> tipDevice;
            cin >> godina;
            Device tmp(ime,(tip)tipDevice,godina);
            try{
                t+=tmp;
            }
            catch(InvalidRegistrationDate ex)
            {
                ex.print();
            }
        }
        t.pecatiCasovi();
    }
    if (testCase == 4){
        cout <<"===== Testiranje na konstruktori ======"<<endl;
        cin>>ime;
        cin >> n;
        MobileServis t(ime);
        for(int i=0;i<n;i++)
        {
            cin >> ime;
            cin >> tipDevice;
            cin >> godina;
            Device tmp(ime,(tip)tipDevice,godina);
            try{
                t+=tmp;
            }
            catch(InvalidRegistrationDate ex)
            {
                ex.print();
            }
        }
        MobileServis t2 = t;
        t2.pecatiCasovi();
    }
    if (testCase == 5){
        cout << "===== Testiranje na static clenovi ======" << endl;
        cin>>ime;
        cin >> n;
        MobileServis t(ime);
        for(int i=0;i<n;i++)
        {
            cin >> ime;
            cin >> tipDevice;
            cin >> godina;
            Device tmp(ime,(tip)tipDevice,godina);

            t+=tmp;
        }
        t.pecatiCasovi();
        cout << "===== Promena na static clenovi ======" << endl;
        Device::setPocetniCasovi(2);
        t.pecatiCasovi();
    }

    if (testCase == 6){
        cout << "===== Testiranje na kompletna funkcionalnost ======" << endl;
        cin>>ime;
        cin >> n;
        MobileServis t(ime);
        for(int i=0;i<n;i++){
            cin >> ime;
            cin >> tipDevice;
            cin >> godina;
            Device tmp(ime,(tip)tipDevice,godina);
            try{
                t+=tmp;
            }
            catch(InvalidRegistrationDate ex){
                ex.print();
            }
        }
        Device::setPocetniCasovi(3);
        MobileServis t2 = t;
        t2.pecatiCasovi();
    }

    return 0;

}

