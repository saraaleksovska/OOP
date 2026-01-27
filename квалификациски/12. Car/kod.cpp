#include<iostream>
#include <cstring>
using namespace std;

class Car{
private:
    string id;
    double  litri;
public:
    Car(string id="SK-0001-AA", double litri=0.0){
        this->id=id;
        this->litri=litri;
    }
    void refuel(double liters){
        litri+=liters;
        if(litri>50){
            litri=50;
        }
    }
    void print(){
        cout<<id<<" - "<<litri<<" - ";
        if(litri==0){
            cout<<"EMPTY "<<endl;
        }else if(litri<10){
            cout<<"LOW"<<endl;
        }else if(litri>=10){
            cout<<"ENOUGH "<<endl;
        }
    }
};
int main() {
    string command;
    Car s;
    string id;
    double liters;

    while (cin >> command) {
        if (command == "constructor1") {
            cin >> id >> liters;
            s = Car(id, liters);
        } else if (command == "constructor2") {
            cin >> id;
            s = Car(id);
        } else if (command == "refuel") {
            cin >> liters;
            s.refuel(liters);
        } else if (command == "print") {
            s.print();
        }
    }


    return 0;
}