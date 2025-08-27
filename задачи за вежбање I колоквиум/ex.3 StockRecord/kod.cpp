#include<iostream>
#include<cstring>
using namespace std;

class StockRecord{
private:
    char id[12];
    char kompanija[50];
    double kupovnaCena;
    double momentalnaCena;
    int brAkcii;
public:
    StockRecord(const char *id = "", const char *kompanija = "", double kupovnaCena = 0.0, int brAkcii = 0){
        strcpy(this->id, id);
        strcpy(this->kompanija, kompanija);
        this->kupovnaCena = kupovnaCena;
        this->momentalnaCena = 0.0;
        this->brAkcii = brAkcii;
    }
    ~StockRecord(){}
    void setNewPrice(double mC){
        momentalnaCena = mC;
    }
    double value(){
        return brAkcii * momentalnaCena;
    }
    double profit(){
        return brAkcii * (momentalnaCena - kupovnaCena);
    }
    friend ostream &operator<<(ostream &out, StockRecord &sr){
        out << sr.kompanija << " " << sr.brAkcii << " " << sr.kupovnaCena << " " << sr.momentalnaCena << " " << sr.profit() << endl;
        return out;
    }

};

class Client{
private:
    char ime[50];
    int id;
    StockRecord *kompanii;
    int n;
public:
    Client(const char *ime = "", int id = 0){
        strcpy(this->ime, ime);
        this->id = id;
        kompanii = NULL;
        n = 0;
    }
    ~Client(){
        delete[] kompanii;
    }
    double totalValue(){
        double suma = 0.0;
        for(int i = 0; i < n; i++){
            suma += kompanii[i].value();
        }
        return suma;
    }
    Client &operator+=(StockRecord &sr){
        StockRecord *tmp = new StockRecord[n+1];
        for(int i = 0; i < n; i++){
            tmp[i] = kompanii[i];
        }
        tmp[n++] = sr;
        delete [] kompanii;
        kompanii = tmp;
        return *this;
    }
    friend ostream &operator<<(ostream &out, Client &c){
        out << c.id << " " << c.totalValue() << endl;
        for(int i = 0; i < c.n; ++i){
            out << c.kompanii[i];
        }
        return out;
    }
};

//не менуваш ништо во main

int main(){
    int test;
    cin >> test;

    if(test == 1){
        double price;
        cout << "=====TEST NA KLASATA StockRecord=====" << endl;
        StockRecord sr("1", "Microsoft", 60.0, 100);
        cout << "Konstruktor OK" << endl;
        cin >> price;
        sr.setNewPrice(price);
        cout << "SET metoda OK" << endl;
    }
    else if(test == 2){
        cout << "=====TEST NA METODITE I OPERATOR << OD KLASATA StockRecord=====" << endl;
        char id[12], company[50];
        double price, newPrice;
        int n, shares;
        cin >> n;
        for(int i = 0; i < n; ++i){
            cin >> id;
            cin >> company;
            cin >> price;
            cin >> newPrice;
            cin >> shares;
            StockRecord sr(id, company, price, shares);
            sr.setNewPrice(newPrice);
            cout << sr.value() << endl;
            cout << sr;
        }
    }
    else if(test == 3){
        cout << "=====TEST NA KLASATA Client=====" << endl;
        char companyID[12], companyName[50], clientName[50];
        int clientID, n, shares;
        double oldPrice, newPrice;
        bool flag = true;
        cin >> clientName;
        cin >> clientID;
        cin >> n;
        Client c(clientName, clientID);
        cout << "Konstruktor OK" << endl;
        for(int i = 0; i < n; ++i){
            cin >> companyID;
            cin >> companyName;
            cin >> oldPrice;
            cin >> newPrice;
            cin >> shares;
            StockRecord sr(companyID, companyName, oldPrice, shares);
            sr.setNewPrice(newPrice);
            c += sr;
            if(flag){
                cout << "Operator += OK" << endl;
                flag = false;
            }
        }
        cout << c;
        cout << "Operator << OK" << endl;
    }
    return 0;

}