#include<iostream>
using namespace std;

struct Igrac {
    char ime[15];
    int nivo;
    int poeni;
};

struct KompjuterskaIgra {
    char ime[20];
    Igrac igraci[30];
    int n;
};

void najdobarIgrac(KompjuterskaIgra *igri,int n) {
    int brIgraci=0;
    for (int i=1; i<n; i++) {
        if (igri[i].n>igri[brIgraci].n)
            brIgraci=i;
    }
    KompjuterskaIgra najpopularna=igri[brIgraci];
    int maxIgraci=0;
    for (int i=1; i<najpopularna.n; i++) {
        if (najpopularna.igraci[i].poeni>najpopularna.igraci[maxIgraci].poeni)
            maxIgraci=i;
        else if (najpopularna.igraci[i].poeni==najpopularna.igraci[maxIgraci].poeni) {
            if (najpopularna.igraci[i].nivo>najpopularna.igraci[maxIgraci].nivo)
                maxIgraci=i;
        }
    }
    cout<<"Najdobar igrac e igracot so korisnicko ime "<<najpopularna.igraci[maxIgraci].ime
        <<" koj ja igra igrata "<<najpopularna.ime;
}


int main() {
    int n;
    cin>>n;

    KompjuterskaIgra igri[100];

    for (int i=0; i<n; i++) {
        KompjuterskaIgra igra;
        cin>>igra.ime>>igra.n;

        for (int j=0; j<igra.n; j++) {
            Igrac nov;
            cin>>nov.ime>>nov.nivo>>nov.poeni;
            igra.igraci[j]=nov;
        }
        igri[i]=igra;
    }

    najdobarIgrac(igri,n);

    return 0;
}
