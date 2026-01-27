#include<iostream>
#include <cstring>
using namespace std;

class Book{
private:
    string name;
    int pg;
public:
    Book(string name="TEST_BOOK", int pg=0){
        this->name=name;
        this->pg=pg;
    }
    int readPages(int pages){
        pg+=pages;
        if(pg>200){
            pg=200;
        }
        return pages;
    }
    void print(){
        cout<<name<<" - ";
        cout<<"/200";
        if(pg<100){
            cout<<" - IN PROGRESS"<<endl;
        }else if(pg>=100 && pg<200){
            cout<<" - ALMOST DONE"<<endl;
        }else if(pg==200){
            cout<<" - FINISHED"<<endl;
        }
    }
};

int main() {
    string command;
    Book s;
    string name;
    int pagesRead;

    while (cin >> command) {
        if (command == "constructor1") {
            cin >> name >> pagesRead;
            s = Book(name, pagesRead);
        } else if (command == "constructor2") {
            cin >> name;
            s = Book(name);
        } else if (command == "readPages") {
            cin >> pagesRead;
            s.readPages(pagesRead);
        } else if (command == "print") {
            s.print();
        }
    }


    return 0;
}