#include <cstring>
#include <iostream>
using namespace std;

enum Size{
    mala,
    golema,
    familijarna
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
    virtual float price() = 0;
    friend bool operator < (Pizza &p1, Pizza &p2){
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
    float price() override{
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
    friend ostream &operator<<(ostream &out, FlatPizza &fp){
        out<<fp.ime<<": "<<fp.sostojki<<", ";
        if(fp.golemina==mala){
            out<<"small";
        }else if(fp.golemina==golema) {
            out << "big";
        }else{
            out << "family";
        }
        out<<" - "<<fp.price()<<endl;
        return out;
    }
};

class FoldedPizza :public Pizza{
protected:
    bool beloBrasno;
public:
    FoldedPizza(const char *ime=" ", const char *sostojki=" ", float cena=0.0, bool beloBrasno=true): Pizza(ime, sostojki, cena){
        this->beloBrasno=beloBrasno;
    }
    float price() override{
        if(beloBrasno){
            return cena*1.1;
        }else if(!beloBrasno){
            return cena*1.3;
        }else{
            return cena;
        }
    }
    friend ostream &operator<<(ostream &out, FoldedPizza &fp){
        out<<fp.ime<<": "<<fp.sostojki<<", ";
        if(fp.beloBrasno){
            out<<"wf";
        }else{
            out<<"nwf";
        }
        out<<" - "<<fp.price()<<endl;
    }
    void setWhiteFlour(bool wf){
        beloBrasno=wf;
    }
};
void expensivePizza(Pizza **p, int n){
    float najvisokaCena = p[0]->price();
    int najskapaPica=0;
    for(int i=0; i<n; i++){
        if(p[i]->price()>najvisokaCena){
            najvisokaCena=p[i]->price();
            najskapaPica=i;
        }
    }
    FlatPizza *p1 = dynamic_cast<FlatPizza*> (p[najskapaPica]);
    if(p1) {
        cout << *p1;
    }
    FoldedPizza *p2 = dynamic_cast<FoldedPizza*> (p[najskapaPica]);
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
