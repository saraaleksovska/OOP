#include<iostream>
#include<cstring>
using namespace std;

struct Tanc{
    char zemja[15];
    char ime[15];
};

struct Tancer{
    char ime[20];
    char prezime[20];
    Tanc tanci[5];
};

void tancuvanje(Tancer *t, int n, char *zemja){
    for(int i = 0; i < n; i++){
        for(int j = 0; j < 3; j++){
            if(strcmp(t[i].tanci[j].zemja, zemja) == 0){
                cout << t[i].ime << " " << t[i].prezime << ", " << t[i].tanci[j].ime << endl;
                break;
            }
        }
    }
}
int main(){
    int i, j, n;
    char zemja[15];
    Tancer tanceri[5];
    cin >> n;
    for(i = 0; i < n; i++){
        cin >> tanceri[i].ime;
        cin >> tanceri[i].prezime;
        for(j = 0; j < 3; j++){
            cin >> tanceri[i].tanci[j].ime;
            cin >> tanceri[i].tanci[j].zemja;
        }
    }
    cin >> zemja;
    tancuvanje(tanceri, n, zemja);
    return 0;
}