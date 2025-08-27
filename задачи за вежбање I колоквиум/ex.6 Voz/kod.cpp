#include<iostream>
#include <cstring>
using namespace std;

struct Voz {
    char relacija[50];
    float km;
    int brPatnici;
};

struct ZeleznickaStanica {
    char grad[20];
    Voz vozovi[30];
    int n;
};

void najkratkaRelacija(ZeleznickaStanica *zs, int n, char *grad) {
    int minKm=1000, minI = 0, minJ = 0;
    for (int i=0; i<n; i++)
        if(!strcmp(zs[i].grad, grad))
            for (int j=0; j<zs[i].n; j++)
                if (zs[i].vozovi[j].km <= minKm){
                    minKm=zs[i].vozovi[j].km;
                    minI = i;
                    minJ = j;
                }
    cout<<"Najkratka relacija: ";
    cout<<zs[minI].vozovi[minJ].relacija;
    cout<<" ("<<minKm<<" km)";
}
int main() {
    int n;
    cin>>n;
    ZeleznickaStanica zStanica[100];

    for (int i=0;i<n;i++){
        //од тука
        cin>>zStanica[i].grad;
        cin>>zStanica[i].n;
        for (int j=0; j<zStanica[i].n; j++) {
            cin>>zStanica[i].vozovi[j].relacija;
            cin>>zStanica[i].vozovi[j].km;
            cin>>zStanica[i].vozovi[j].brPatnici;
        }
        //до тука пишуваш ти
    }

    char grad[25];
    cin>>grad;
    najkratkaRelacija(zStanica,n,grad);
    return 0;
}
