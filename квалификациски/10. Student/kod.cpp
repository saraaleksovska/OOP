#include<iostream>
#include <cstring>
using namespace std;

class Student{
private:
    string id;
    int poeni;
public:
    Student(string id="NO_ID", int poeni=0){
        this->id=id;
        this->poeni=poeni;
    }
    void addPoints(int points){
        poeni+=points;
        if(poeni>100){
            poeni=100;
        }
    }
    void print(){
        cout<<id<<" - "<<poeni<<" ";
        if(poeni<50){
            cout<<"FAILED"<<endl;
        } else if(poeni>=50 && poeni<90) {
            cout<<"PASSED"<<endl;
        } else if(poeni>=90){
            cout<<"BEST"<<endl;
        }
    }
};

int main() {
    string command;
    Student s;
    string id;
    int points;

    while (cin >> command) {
        if (command == "constructor1") {
            cin >> id >> points;
            s = Student(id, points);
        } else if (command == "constructor2") {
            cin >> id;
            s = Student(id);
        } else if (command == "addPoints") {
            cin >> points;
            s.addPoints(points);
        } else if (command == "print") {
            s.print();
        }
    }


    return 0;
}