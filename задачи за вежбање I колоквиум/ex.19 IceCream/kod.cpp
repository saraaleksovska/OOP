#include <iostream>
#include <cstring>

using namespace std;

class IceCream {
private:
    char *ime;
    char sostav[100];
    float cena;
    int popust;
    void copy(const IceCream &ic) {
        this->ime = new char[strlen(ic.ime) + 1];
        strcpy(ime, ic.ime);
        strcpy(this->sostav,ic.sostav);
        cena = ic.cena;
        popust = ic.popust;
    }
public:
    IceCream(const char *ime = "", const char *sostav = "", float cena = 0) {
        this->ime = new char[strlen(ime) + 1];
        strcpy(this->ime, ime);
        strcpy(this->sostav,sostav);
        this->cena = cena;
        this->popust = 0;
    }
    IceCream(const IceCream &ic) {
        copy(ic);
    }
    IceCream &operator=(const IceCream &ic) {
        if (this == &ic) return *this;
        delete[] ime;
        copy(ic);
        return *this;
    }
    friend ostream &operator<<(ostream &out, const IceCream &ic) {
        out << ic.ime << ": ";
        out << ic.sostav << " ";
        out << ic.cena << " ";
        if (ic.popust > 0) {
            out << "(" << ic.cena * (100 - ic.popust) / 100 << ")";
        }
        return out;
    }
    void setName(char *n) {
        delete[] ime;
        ime = new char[strlen(n) + 1];
        strcpy(ime, n);
    }
    IceCream &operator++() {
        popust += 5;
        return *this;
    }
    IceCream operator+(const char *extra) {
        char *nov = new char[strlen(ime) + strlen(extra) + 4];
        nov[0] = '\0';
        strcat(nov, ime);
        strcat(nov, " + ");
        strcat(nov, extra);
        IceCream res(nov, sostav, cena + 10);
        res.setDiscount(popust);
        return res;
    }
    void setName(const char *ime) {
        delete[] ime;
        this->ime = new char[strlen(ime) + 1];
        strcpy(this->ime, ime);
    }
    void setDiscount(int d) {
        if(d>=0 && d<=100)
            popust = d;
    }
    ~IceCream() {
        delete[] ime;
    }
};

class IceCreamShop {
private:
    char ime[50];
    IceCream *sladoledi;
    int n;
    void copy(const IceCreamShop &ics) {
        strcpy(ime, ics.ime);
        n = ics.n;
        sladoledi = new IceCream[n];
        for (int i = 0; i < n; ++i) {
            sladoledi[i] = ics.sladoledi[i];
        }
    }
public:
    IceCreamShop(const char *i) {
        strcpy(ime, i);
        sladoledi = NULL;
        n = 0;
    }
    IceCreamShop(const IceCreamShop &ics) {
        copy(ics);
    }
    IceCreamShop &operator=(const IceCreamShop &ics) {
        if (this == &ics) return *this;
        delete[] sladoledi;
        copy(ics);
        return *this;
    }
    ~IceCreamShop() {
        delete[] sladoledi;
    }
    IceCreamShop &operator+= (IceCream &ic) {
        IceCream *tmp = sladoledi;
        sladoledi = new IceCream[n + 1];
        for (int i = 0; i < n; ++i) {
            sladoledi[i] = tmp[i];
        }
        sladoledi[n] = ic;
        ++n;
        delete [] tmp;
        return *this;
    }
    friend ostream &operator<<(ostream &out, const IceCreamShop &ics) {
        cout << ics.ime << endl;
        for (int i = 0; i < ics.n; ++i) {
            out << ics.sladoledi[i] << endl;
        }
        return out;
    }

};

// не менуваш во main

int main() {
    char name[100];
    char ingr[100];
    float price;
    int discount;

    int testCase;

    cin >> testCase;
    cin.get();
    if(testCase == 1) {
        cout << "====== TESTING IceCream CLASS ======" << endl;
        cin.getline(name,100);
        cin.getline(ingr,100);
        cin >> price;
        cin >> discount;
        cout << "CONSTRUCTOR" << endl;
        IceCream ic1(name, ingr, price);
        ic1.setDiscount(discount);
        cin.get();
        cin.getline(name,100);
        cin.getline(ingr,100);
        cin >> price;
        cin >> discount;
        IceCream ic2(name, ingr, price);
        ic2.setDiscount(discount);
        cout << "OPERATOR <<" << endl;
        cout << ic1 << endl;
        cout << ic2 << endl;
        cout << "OPERATOR ++" << endl;
        ++ic1;
        cout << ic1 << endl;
        cout << "OPERATOR +" << endl;
        IceCream ic3 = ic2 + "chocolate";
        cout << ic3 << endl;
    } else if(testCase == 2) {
        cout << "====== TESTING IceCream CONSTRUCTORS ======" << endl;
        cin.getline(name,100);
        cin.getline(ingr,100);
        cin >> price;
        //cin >> discount;
        cout << "CONSTRUCTOR" << endl;
        IceCream ic1(name, ingr, price);
        cout << ic1 << endl;
        cout << "COPY CONSTRUCTOR" << endl;
        IceCream ic2(ic1);
        cin.get();
        cin.getline(name,100);
        ic2.setName(name);
        cout << ic1 << endl;
        cout << ic2 << endl;
        cout << "OPERATOR =" << endl;
        ic1 = ic2;
        cin.getline(name,100);
        ic2.setName(name);
        cout << ic1 << endl;
        cout << ic2 << endl;
        cin >> discount;
        ic1.setDiscount(discount);
    } else if(testCase == 3) {
        cout << "====== TESTING IceCreamShop ======" << endl;
        char icsName[50];
        cin.getline(icsName,100);
        cout << "CONSTRUCTOR" << endl;
        IceCreamShop ics(icsName);
        int n;
        cin >> n;
        cout << "OPERATOR +=" << endl;
        for(int i = 0; i < n; ++i) {
            cin.get();
            cin.getline(name,100);
            cin.getline(ingr,100);
            cin >> price;
            IceCream ic(name, ingr, price);
            ics += ic;
        }
        cout << ics;
    } else if(testCase == 4) {
        cout << "====== TESTING IceCreamShop CONSTRUCTORS ======" << endl;
        char icsName[50];
        cin.getline(icsName,100);
        IceCreamShop ics(icsName);
        int n;
        cin >> n;
        for(int i = 0; i < n; ++i) {
            cin.get();
            cin.getline(name,100);
            cin.getline(ingr,100);
            cin >> price;
            IceCream ic(name, ingr, price);
            ics += ic;
        }
        IceCream x("FINKI fruits", "strawberry ice cream, raspberry ice cream, blueberry ice cream", 60);
        IceCreamShop icp = ics;
        ics+=x;
        cout << ics << endl;
        cout << icp << endl;
    }
    return 0;
}


