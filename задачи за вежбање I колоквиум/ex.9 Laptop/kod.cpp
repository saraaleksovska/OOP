#include <iostream>
#include <climits> // за INT_MAX

using namespace std;

struct Laptop{
    char firma[100];
    float inchi;
    bool touch;
    int cena;
    void print();
};

void Laptop::print(){
    cout<<firma<<" "<<inchi<<" "<<cena<<endl;
}

struct ITStore {
    char ime[100];
    char lokacija[100];
    Laptop laptopi[100];
    int n;
    void print();
};

void ITStore::print(){
    cout<<ime<<" "<<lokacija<<endl;
    for(int i=0; i<n; i++){
        laptopi[i].print();
    }
}

int najniskaCena(ITStore s){
    int najniska = INT_MAX;
    for(int i=0; i<s.n; i++){
        if(s.laptopi[i].touch == true && najniska > s.laptopi[i].cena)
            najniska = s.laptopi[i].cena;
    }
    return najniska;
}

void najeftina_ponuda(ITStore s[], int n){
    int najniska = najniskaCena(s[0]);
    int prodavnicaSoNajevtin = 0;
    for(int i=1; i<n; i++){
        if(najniskaCena(s[i]) < najniska){
            najniska = najniskaCena(s[i]);
            prodavnicaSoNajevtin = i;
        }
    }
    cout<<"Najeftina ponuda ima prodavnicata: "<<endl;
    cout<<s[prodavnicaSoNajevtin].ime<<" "<<s[prodavnicaSoNajevtin].lokacija<<endl;
    cout<<"Najniskata cena iznesuva: "<<najniskaCena(s[prodavnicaSoNajevtin])<<endl;
}

//во main менуваш кадешто се коментарите

int main() {
    ITStore s[100];
    int n;
    cin >> n;

    //vnesuvanje na prodavnicite edna po edna, zaedno so raspolozlivite laptopvi vo niv
    for(int i=0; i<n; i++){
        cin >> s[i].ime;
        cin >> s[i].lokacija;
        cin >> s[i].n;
        for (int j=0; j<s[i].n; j++){
            cin >> s[i].laptopi[j].firma;
            cin >> s[i].laptopi[j].inchi;
            cin >> s[i].laptopi[j].touch;
            cin >> s[i].laptopi[j].cena;
        }
    }
    //pecatenje na site prodavnici
    for (int i=0; i<n; i++){
        s[i].print();
    }

    najeftina_ponuda(s, n);  //povik na glavnata metoda

    return 0;
}
