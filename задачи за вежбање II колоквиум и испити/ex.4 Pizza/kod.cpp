#include <cstring>
#include <iostream>
using namespace std;

enum Size{
    mala, golema, familijarna
};

class Pizza{
protected:
    char ime[20];
    char sostojki[100];
    float cena;
public:
    Pizza(const char *ime=" ", const char *sostojki=" ", float cena=0.0){
        strcpy(this->ime, ime);
        strcpy(this->sostojki,sostojki);
        this->cena=cena;
    }
    virtual float price() const= 0;
    virtual ~Pizza() {}
    friend bool operator<(Pizza &p1, Pizza &p2){
        return p1.price()<p2.price();
    }
};

class FlatPizza : public Pizza{
protected:
    Size golemina;
public:
    FlatPizza(const char *ime=" ", const char *sostojki=" ", float cena=0.0, Size golemina=mala): Pizza(ime, sostojki, cena){
        this->golemina=golemina;
    }
    float price() const override{
        if(golemina==mala){
            return cena*1.1;
        }else if(golemina==golema){
            return cena*1.2;
        }else if(golemina==familijarna){
            return cena*1.3;
        }else{
            return cena;
        }
    }
    friend ostream &operator<<(ostream &o, FlatPizza &fp){
        o<<fp.ime<<": "<<fp.sostojki<<", ";
        if(fp.golemina==mala){
            o<<"small";
        }else if(fp.golemina==golema) {
            o << "big";
        }else{
            o << "family";
        }
        o<<" - "<<fp.price()<<endl;
        return o;
    }
};

class FoldedPizza :public Pizza{
protected:
    bool belo;
public:
    FoldedPizza(const char *ime=" ", const char *sostojki=" ", float cena=0.0, bool belo=true): Pizza(ime, sostojki, cena){
        this->belo=belo;
    }
    float price() const override{
        if(belo){
            return cena*1.1;
        }else if(!belo){
            return cena*1.3;
        }else{
            return cena;
        }
    }
    friend ostream &operator<<(ostream &o, FoldedPizza &fp){
        o<<fp.ime<<": "<<fp.sostojki<<", ";
        if(fp.belo){
            o<<"wf";
        }else{
            o<<"nwf";
        }
        o<<" - "<<fp.price()<<endl;
        return o;
    }
    void setWhiteFlour(bool wf){
        belo=wf;
    }
};
void expensivePizza(Pizza **p, int n){
    float maxCena = p[0]->price();
    int najskapa=0;
    for(int i=0; i<n; i++){
        if(p[i]->price()>maxCena){
            maxCena=p[i]->price();
            najskapa=i;
        }
    }
    FlatPizza *p1 = dynamic_cast<FlatPizza*> (p[najskapa]);
    if(p1) {
        cout << *p1;
    }
    FoldedPizza *p2 = dynamic_cast<FoldedPizza*> (p[najskapa]);
    if(p2) {
        cout << *p2;
    }
}


//не менуваш ништо во main
int main() {
    int test_case;
    char name[20];
    char ingredients[100];
    float inPrice;
    Size size;
    bool whiteFlour;

    cin >> test_case;
    if (test_case == 1) {
        // Test Case FlatPizza - Constructor, operator <<, price
        cin.get();
        cin.getline(name,20);
        cin.getline(ingredients,100);
        cin >> inPrice;
        FlatPizza fp(name, ingredients, inPrice);
        cout << fp;
    } else if (test_case == 2) {
        // Test Case FlatPizza - Constructor, operator <<, price
        cin.get();
        cin.getline(name,20);
        cin.getline(ingredients,100);
        cin >> inPrice;
        int s;
        cin>>s;
        FlatPizza fp(name, ingredients, inPrice, (Size)s);
        cout << fp;

    } else if (test_case == 3) {
        // Test Case FoldedPizza - Constructor, operator <<, price
        cin.get();
        cin.getline(name,20);
        cin.getline(ingredients,100);
        cin >> inPrice;
        FoldedPizza fp(name, ingredients, inPrice);
        cout << fp;
    } else if (test_case == 4) {
        // Test Case FoldedPizza - Constructor, operator <<, price
        cin.get();
        cin.getline(name,20);
        cin.getline(ingredients,100);
        cin >> inPrice;
        FoldedPizza fp(name, ingredients, inPrice);
        fp.setWhiteFlour(false);
        cout << fp;

    } else if (test_case == 5) {
        // Test Cast - operator <, price
        int s;

        cin.get();
        cin.getline(name,20);
        cin.getline(ingredients,100);
        cin >> inPrice;
        cin>>s;
        FlatPizza *fp1 = new FlatPizza(name, ingredients, inPrice, (Size)s);
        cout << *fp1;

        cin.get();
        cin.getline(name,20);
        cin.getline(ingredients,100);
        cin >> inPrice;
        cin>>s;
        FlatPizza *fp2 = new FlatPizza(name, ingredients, inPrice, (Size)s);
        cout << *fp2;

        cin.get();
        cin.getline(name,20);
        cin.getline(ingredients,100);
        cin >> inPrice;
        FoldedPizza *fp3 = new FoldedPizza(name, ingredients, inPrice);
        cout << *fp3;

        cin.get();
        cin.getline(name,20);
        cin.getline(ingredients,100);
        cin >> inPrice;
        FoldedPizza *fp4 = new FoldedPizza(name, ingredients, inPrice);
        fp4->setWhiteFlour(false);
        cout << *fp4;

        cout<<"Lower price: "<<endl;
        if(*fp1<*fp2)
            cout<<fp1->price()<<endl;
        else cout<<fp2->price()<<endl;

        if(*fp1<*fp3)
            cout<<fp1->price()<<endl;
        else cout<<fp3->price()<<endl;

        if(*fp4<*fp2)
            cout<<fp4->price()<<endl;
        else cout<<fp2->price()<<endl;

        if(*fp3<*fp4)
            cout<<fp3->price()<<endl;
        else cout<<fp4->price()<<endl;

    } else if (test_case == 6) {
        // Test Cast - expensivePizza
        int num_p;
        int pizza_type;

        cin >> num_p;
        Pizza **pi = new Pizza *[num_p];
        for (int j = 0; j < num_p; ++j) {

            cin >> pizza_type;
            if (pizza_type == 1) {
                cin.get();
                cin.getline(name,20);

                cin.getline(ingredients,100);
                cin >> inPrice;
                int s;
                cin>>s;
                FlatPizza *fp = new FlatPizza(name, ingredients, inPrice, (Size)s);
                cout << (*fp);
                pi[j] = fp;
            }
            if (pizza_type == 2) {

                cin.get();
                cin.getline(name,20);
                cin.getline(ingredients,100);
                cin >> inPrice;
                FoldedPizza *fp =
                        new FoldedPizza (name, ingredients, inPrice);
                if(j%2)
                    (*fp).setWhiteFlour(false);
                cout << (*fp);
                pi[j] = fp;

            }
        }
        cout << endl;
        cout << "The most expensive pizza:\n";
        expensivePizza(pi,num_p);
    }
    return 0;
}
