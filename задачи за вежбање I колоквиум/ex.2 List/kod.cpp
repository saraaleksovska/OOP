#include <iostream>
using namespace std;

class List{
private:
    int *broevi;
    int n;
    void copy(const List &l){
        this->n=l.n;
        broevi = new int[l.n+1];
        for (int i=0;i<n;i++)
            this->broevi[i]=l.broevi[i];
    }
public:
    List (int *broevi=nullptr, int n=0) {
        this->n=n;
        this->broevi = new int[n+1];
        for (int i=0;i<n;i++){
            this->broevi[i]=broevi[i];
        }
    }
    /*List(){
        broevi=new int[0];
        n=0;
    }*/
    List (const List &l) {
        copy(l);
    }
    List &operator = (const List &l){
        if (this!=&l){
            delete[] broevi;
            copy(l);
        }
        return *this;
    }
    ~List() {
        delete[] broevi;
    }
    int sum() {
        int suma = 0;
        for (int i=0;i<n;i++){
            suma+=broevi[i];
        }
        return suma;
    }
    double average() {
        return (double) sum() / n;
    }
    void print() {
        cout<<n<<": ";
        for (int i=0;i<n;i++){
            cout<<broevi[i]<<" ";
        }
        cout<<"sum: "<<sum()<<" average: "<<average()<<endl;
    }
    int getN () {
        return n;
    }
};

class ListContainer{
private:
    List *listi;
    int m;
    int obidi;
    void copy(const ListContainer &lc){
        this->obidi = lc.obidi;
        this->m=lc.m;
        listi = new List[lc.m+1];
        for (int i=0;i<lc.m;i++)
            listi[i]=lc.listi[i];
    }
public:
    ListContainer () { //defaultен конструктор
        m = obidi = 0; //цел број првично поставен на нула
        listi = new List[0];
    }
    ListContainer (const ListContainer &lc){
        copy(lc);
    }
    ListContainer &operator = (const ListContainer &lc){
        if (this!=&lc){
            delete[] listi;
            copy(lc);
        }
        return *this;
    }
    ~ListContainer() {
        delete[] listi;
    }
    int sum() {
        int suma = 0;
        for (int i=0;i<m;i++){
            suma+=listi[i].sum();
        }
        return suma;
    }
    double average() {
        int suma = 0;
        for (int i=0;i<m;i++){
            suma+=listi[i].getN();
        }
        return (double) sum() / suma;
    }
    void addNewList(List l){
        for (int i=0;i<m;i++)
            if (listi[i].sum()==l.sum()){
                obidi++;
                return;
            }
        List *tmp = new List[m+1];
        for (int i=0;i<m;i++) {
            tmp[i] = listi[i];
        }
        tmp[m++]=l;
        delete[] listi;
        listi = tmp;
    }
    void print () {
        if (m==0){
            cout<<"The list is empty"<<endl;
            return;
        }
        for (int i=0;i<m;i++){
            cout<<"List number: "<<i+1<<" List info: ";
            listi[i].print();
        }
        cout<<"Sum: "<<sum()<<" Average: "<<average()<<endl;
        cout<<"Successful attempts: "<<m<<" Failed attempts: "<<obidi<<endl;
    }
};




//не менуваш ништо во main
int main() {
    ListContainer lc;
    int N;
    cin>>N;
    for (int i=0;i<N;i++) {
        int n;
        int niza[100];
        cin>>n;
        for (int j=0;j<n;j++){
            cin>>niza[j];
        }
        List l=List(niza,n);
        lc.addNewList(l);
    }
    int testCase;
    cin>>testCase;
    if (testCase==1) {
        cout<<"Test case for operator ="<<endl;
        ListContainer lc1;
        lc1.print();
        cout<<lc1.sum()<<" "<<lc.sum()<<endl;
        lc1=lc;
        lc1.print();
        cout<<lc1.sum()<<" "<<lc.sum()<<endl;
        lc1.sum();
        lc1.average();
    }
    else {
        lc.print();
    }
}


