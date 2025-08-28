#include <iostream>
#include <cstring>
#define MAX 50
using namespace std;

class UserExistsException{
public:
    void print(){
        cout << "The user already exists in the list!" << endl;
    }
};
enum typeC{
    standard,
    loyal,
    vip
};
class Customer{
protected:
    char ime[MAX];
    char email[MAX];
    typeC vid;
    static int osnoven;
    static const int dopolitelen;
    int brProizvodi;
public:
    Customer(const char *ime="", const char *email="", typeC vid=standard, int brProizvodi=0){
        strcpy(this->ime,ime);
        strcpy(this->email,email);
        this->vid=vid;
        this->brProizvodi=brProizvodi;
    }
    int calcDiscount(){
        switch(vid){
            case loyal: return osnoven;
            case vip: return osnoven+dopolitelen;
            default: return 0;
        }
    }
    friend ostream &operator<<(ostream &out, Customer &c){
        out << c.ime << endl<< c.email << endl<< c.brProizvodi << endl;
        switch(c.vid){
            case standard: out << "standard "; break;
            case loyal: out << "loyal "; break;
            case vip: out << "vip "; break;
            default: break;
        }
        out << c.calcDiscount() << endl;
        return out;
    }
    char *getEmail(){
        return email;
    }
    typeC getTypeC(){
        return vid;
    }
    int getNumProducts() {
        return brProizvodi;
    }
    void setTypeC(typeC t){
        vid=t;
    }
    static void setDiscount1(int p){
        Customer :: osnoven = p;
    }
};
class FINKI_bookstore{
protected:
    Customer *kupuvaci;
    int n;
    void copy(const FINKI_bookstore &f){
        this->n = f.n;
        this->kupuvaci = new Customer[f.n];
        for (int i = 0; i < n; i++) {
            kupuvaci[i] = f.kupuvaci[i];
        }
    }
public:
    FINKI_bookstore(){
        kupuvaci = nullptr;
        n=0;
    }
    FINKI_bookstore (const FINKI_bookstore &f){
        copy(f);
    }
    FINKI_bookstore &operator=(const FINKI_bookstore &f) {
        if (this != &f){
            delete[] kupuvaci;
            copy(f);
        }
        return *this;
    }
    ~FINKI_bookstore() {
        delete[] kupuvaci;
    }
    FINKI_bookstore &operator+= (Customer &c) {
        for (int i = 0; i < n; i++) {
            if (!strcmp(kupuvaci[i].getEmail(), c.getEmail())){
                throw UserExistsException();
            }
        }
        Customer *tmp = new Customer[n+1];
        for (int i=0; i<n; i++) {
            tmp[i]=kupuvaci[i];
        }
        delete[] kupuvaci;
        tmp[n++] = c;
        kupuvaci = tmp;
        return *this;
    }
    void update() {
        for (int i=0; i<n; i++) {
            switch(kupuvaci[i].getTypeC()){
                case standard:
                    if(kupuvaci[i].getNumProducts()>5) {
                        kupuvaci[i].setTypeC(loyal);
                        break;
                    }
                case loyal:
                    if(kupuvaci[i].getNumProducts()>10){
                        kupuvaci[i].setTypeC(vip);
                        break;
                    }
                default: break;
            }
        }
    }
    friend ostream &operator<<(ostream &out, FINKI_bookstore &f){
        for(int i=0; i<f.n; i++)
            out<<f.kupuvaci[i];
        return out;
    }
    void setCustomers(Customer *c, int br){
        n = br;
        kupuvaci = new Customer[n];
        for (int i = 0; i < n; ++i) {
            kupuvaci[i] = c[i];
        }
    }
};

int Customer::osnoven = 10;
const int Customer::dopolitelen = 20;

int main(){
    int testCase;
    cin >> testCase;
    char name[MAX];
    char email[MAX];
    int tC;
    int numProducts;

    if (testCase == 1){
        cout << "===== Test Case - Customer Class ======" << endl;
        cin.get();
        cin.getline(name,MAX);
        cin.getline(email,MAX);
        cin >> tC;
        cin >> numProducts;
        cout << "===== CONSTRUCTOR ======" << endl;
        Customer c(name, email, (typeC) tC, numProducts);
        cout << c;
    }

    if (testCase == 2){
        cout << "===== Test Case - Static Members ======" << endl;
        cin.get();
        cin.getline(name,MAX);
        cin.getline(email,MAX);
        cin >> tC;
        cin >> numProducts;
        cout << "===== CONSTRUCTOR ======" << endl;
        Customer c(name, email, (typeC) tC, numProducts);
        cout << c;

        c.setDiscount1(5);

        cout << c;
    }

    if (testCase == 3){
        cout << "===== Test Case - FINKI-bookstore ======" << endl;
        FINKI_bookstore fc;
        int n;
        cin >> n;
        Customer customers[MAX];
        for(int i = 0; i < n; ++i) {
            cin.get();
            cin.getline(name,MAX);
            cin.getline(email,MAX);
            cin >> tC;
            cin >> numProducts;
            Customer c(name, email, (typeC) tC, numProducts);
            customers[i] = c;
        }

        fc.setCustomers(customers, n);

        cout << fc <<endl;
    }

    if (testCase == 4){
        cout << "===== Test Case - operator+= ======" << endl;
        FINKI_bookstore fc;
        int n;
        cin >> n;
        Customer customers[MAX];
        for(int i = 0; i < n; ++i) {
            cin.get();
            cin.getline(name,MAX);
            cin.getline(email,MAX);
            cin >> tC;
            cin >> numProducts;
            Customer c(name, email, (typeC) tC, numProducts);
            customers[i] = c;
        }

        fc.setCustomers(customers, n);
        cout << "OPERATOR +=" << endl;
        cin.get();
        cin.getline(name,MAX);
        cin.getline(email,MAX);
        cin >> tC;
        cin >> numProducts;
        Customer c(name, email, (typeC) tC, numProducts);
        fc+=c;

        cout << fc;
    }

    if (testCase == 5){
        cout << "===== Test Case - operator+= (exception) ======" << endl;
        FINKI_bookstore fc;
        int n;
        cin >> n;
        Customer customers[MAX];
        for(int i = 0; i < n; ++i) {
            cin.get();
            cin.getline(name,MAX);
            cin.getline(email,MAX);
            cin >> tC;
            cin >> numProducts;
            Customer c(name, email, (typeC) tC, numProducts);
            customers[i] = c;
        }

        fc.setCustomers(customers, n);
        cout << "OPERATOR +=" << endl;
        cin.get();
        cin.getline(name,MAX);
        cin.getline(email,MAX);
        cin >> tC;
        cin >> numProducts;
        Customer c(name, email, (typeC) tC, numProducts);
        try{
            fc+=c;
        }catch(UserExistsException e){
            e.print();
        }

        cout << fc;
    }

    if (testCase == 6){
        cout << "===== Test Case - update method  ======" << endl << endl;
        FINKI_bookstore fc;
        int n;
        cin >> n;
        Customer customers[MAX];
        for(int i = 0; i < n; ++i) {
            cin.get();
            cin.getline(name,MAX);
            cin.getline(email,MAX);
            cin >> tC;
            cin >> numProducts;
            Customer c(name, email, (typeC) tC, numProducts);
            customers[i] = c;
        }

        fc.setCustomers(customers, n);

        cout << "Update:" << endl;
        fc.update();
        cout << fc;
    }
    return 0;

}
