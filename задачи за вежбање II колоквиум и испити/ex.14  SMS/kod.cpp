#include<iostream>
#include<cstring>
using namespace std;

class SMS {
protected:
    char tel[16];
    float cena;
public:
    SMS(const char *tel = "", float cena = 0.0){
        strcpy(this->tel, tel);
        this->cena = cena;
    }
    void setTel(char *tel){
        strcpy(this->tel, tel);
    }
    virtual float SMS_cena() = 0;
    friend ostream &operator<< (ostream &o, SMS &sms){
        o << "Tel: " << sms.tel << " - cena: "<< sms.SMS_cena() << "den." << endl;
        return o;
    }
    float get_price(){
        return cena;
    }
    virtual ~SMS(){}
};

class RegularSMS :public SMS {
private:
    char *tekst;
    bool roaming;
    const static int danok;
    static int r_procent;

public:
    RegularSMS(const char *tel = "", float cena = 0.0, const char *tekst = "", bool roaming = false) : SMS(tel, cena){
        this->tekst = new char[strlen(tekst) + 1];
        strcpy(this->tekst, tekst);
        this->roaming = roaming;
    }
    float SMS_cena(){
        if (roaming){
            return get_price()*(strlen(tekst) / 160 + 1)*(1+r_procent/100.0);
        }
        else return get_price()*(strlen(tekst) / 160 + 1)*(1+danok/100.0);
    }
    static void set_rProcent(int p){
        RegularSMS::r_procent = p;
    }
};
const int RegularSMS::danok = 18;
int RegularSMS::r_procent = 300;

class SpecialSMS :public SMS {
private:
    bool hum;
    static int s_procent;
public:
    SpecialSMS(const char *tel = "", float cena = 0.0, bool hum = false) : SMS(tel, cena){
        this->hum = hum;
    }
    float SMS_cena(){
        if (hum){
            return get_price();
        }
        else return get_price()*(1+s_procent/100.0);
    }
    static void set_sProcent(int p){
        SpecialSMS::s_procent = p;
    }
};
int SpecialSMS::s_procent = 150;

void vkupno_SMS(SMS **sms, int n){
    int rSMS = 0, sSMS = 0;
    float sum_rSMS = 0.0, sum_sSMS = 0.0;
    for (int i = 0; i<n; i++){
        RegularSMS *ob1 = dynamic_cast<RegularSMS*>(sms[i]);
        if (ob1 != 0){
            rSMS ++;
            sum_rSMS += ob1->SMS_cena();
        }
        SpecialSMS *ob2 = dynamic_cast<SpecialSMS*>(sms[i]);
        if (ob2 != 0){
            sSMS++;
            sum_sSMS += ob2->SMS_cena();
        }
    }
    cout << "Vkupno ima " << rSMS<< " regularni SMS poraki i nivnata cena e: " << sum_rSMS << endl;
    cout << "Vkupno ima " << sSMS<< " specijalni SMS poraki i nivnata cena e: " << sum_sSMS << endl;
}


int main(){
    char tel[20], msg[1000];
    float cena;
    int p;
    bool roam, hum;
    SMS  **sms;
    int n;
    int tip;
    int testCase;
    cin >> testCase;
    if (testCase == 1){
        cout << "====== Testing RegularSMS class ======" << endl;
        cin >> n;
        sms = new SMS *[n];
        for (int i = 0; i < n; i++){
            cin >> tel;
            cin >> cena;
            cin.get();
            cin.getline(msg, 1000);
            cin >> roam;
            cout << "CONSTRUCTOR" << endl;
            sms[i] = new RegularSMS(tel, cena, msg, roam);
            cout << "OPERATOR <<" << endl;
            cout << *sms[i];
        }
        for (int i = 0; i<n; i++) delete sms[i];
        delete[] sms;
    }
    if (testCase == 2){
        cout << "====== Testing SpecialSMS class ======" << endl;
        cin >> n;
        sms = new SMS *[n];

        for (int i = 0; i < n; i++){
            cin >> tel;
            cin >> cena;
            cin >> hum;
            cout << "CONSTRUCTOR" << endl;
            sms[i] = new SpecialSMS(tel, cena, hum);
            cout << "OPERATOR <<" << endl;
            cout << *sms[i];
        }
        for (int i = 0; i<n; i++) delete sms[i];
        delete[] sms;
    }
    if (testCase == 3){
        cout << "====== Testing method vkupno_SMS() ======" << endl;
        cin >> n;
        sms = new SMS *[n];
        for (int i = 0; i<n; i++){
            cin >> tip;
            cin >> tel;
            cin >> cena;
            if (tip == 1) {
                cin.get();
                cin.getline(msg, 1000);
                cin >> roam;
                sms[i] = new RegularSMS(tel, cena, msg, roam);
            }
            else {
                cin >> hum;
                sms[i] = new SpecialSMS(tel, cena, hum);
            }
        }
        vkupno_SMS(sms, n);
        for (int i = 0; i<n; i++) delete sms[i];
        delete[] sms;
    }
    if (testCase == 4){
        cout << "====== Testing RegularSMS class with a changed percentage======" << endl;
        SMS *sms1, *sms2;
        cin >> tel;
        cin >> cena;
        cin.get();
        cin.getline(msg, 1000);
        cin >> roam;
        sms1 = new RegularSMS(tel, cena, msg, roam);
        cout << *sms1;
        cin >> tel;
        cin >> cena;
        cin.get();
        cin.getline(msg, 1000);
        cin >> roam;
        cin >> p;
        RegularSMS::set_rProcent(p);
        sms2 = new RegularSMS(tel, cena, msg, roam);
        cout << *sms2;
        delete sms1, sms2;
    }
    if (testCase == 5){
        cout << "====== Testing SpecialSMS class with a changed percentage======" << endl;
        SMS *sms1, *sms2;
        cin >> tel;
        cin >> cena;
        cin >> hum;
        sms1 = new SpecialSMS(tel, cena, hum);
        cout << *sms1;
        cin >> tel;
        cin >> cena;
        cin >> hum;
        cin >> p;
        SpecialSMS::set_sProcent(p);
        sms2 = new SpecialSMS(tel, cena, hum);
        cout << *sms2;
        delete sms1, sms2;
    }

    return 0;
}
