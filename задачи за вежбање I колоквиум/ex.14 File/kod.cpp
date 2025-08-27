#include<iostream>
#include<cstring>

using namespace std;

enum Extension {
    PDF,TXT,EXE
};

class File {
private:
    char *ime;
    Extension ekstenzija;
    char *sopstvenik;
    int megabajti;
    void copy(const File &f) {
        this->ime = new char[strlen(f.ime) + 1];
        strcpy(this->ime, f.ime);
        this->sopstvenik = new char[strlen(f.sopstvenik) + 1];
        strcpy(this->sopstvenik, f.sopstvenik);
        this->megabajti = f.megabajti;
        this->ekstenzija = f.ekstenzija;
    }
public:
    File() {
        this->ime = new char[0];
        this->sopstvenik = new char[0];
        this->megabajti = 0;
    }
    File(const char *ime, const char *sopstvenik, const int megabajti, const Extension ekstenzija) {
        this->ime = new char[strlen(ime) + 1];
        strcpy(this->ime, ime);
        this->sopstvenik = new char[strlen(sopstvenik) + 1];
        strcpy(this->sopstvenik, sopstvenik);
        this->megabajti = megabajti;
        this->ekstenzija = ekstenzija;
    }
    File(const File &f) {
        copy(f);
    }
    ~File() {
        delete[] ime;
        delete[] sopstvenik;
    }
    File &operator = (const File &f) {
        if (&f != this) {
            delete[] ime;
            delete[] sopstvenik;
            copy(f);
        }
        return *this;
    }
    void print() {
        char* ext = "";
        if (ekstenzija == 0) ext = "pdf";
        if (ekstenzija == 1) ext = "txt";
        if (ekstenzija == 2) ext = "exe";
        cout << "File name: " << ime << "." << ext << endl;
        cout << "File owner: " << sopstvenik << endl;
        cout << "File size: " << megabajti << endl;
    }
    bool equals(const File &f) {
        return equalsType(f) && strcmp(this->sopstvenik, f.sopstvenik) == 0;
    }
    bool equalsType(const File &f) {
        return strcmp(this->ime, f.ime)==0 && this->ekstenzija==f.ekstenzija;
    }
};

class Folder {
private:
    char *ime;
    int n; //број на датотеки
    File *datoteki;
public:
    Folder(const char *ime) {
        this->ime = new char[strlen(ime) + 1];
        strcpy(this->ime, ime);
        this->n = 0;
        this->datoteki = 0;
    }
    ~Folder() {
        delete [] ime;
        delete [] datoteki;
    }
    void print() {
        cout << "Folder name: " << ime << endl;
        for (int i = 0; i < n; i++)
            datoteki[i].print();
    }
    void add(const File &f) {
        File *tmp = datoteki;
        this->datoteki = new File[n + 1];
        for (int i = 0; i < n; i++)
            datoteki[i] = tmp[i];
        datoteki[n++] = f;
    }
    void remove(const File &f) {
        int indexToDelete = -1;
        for (int i = 0; i < n; i++)
            if (datoteki[i].equals(f)) {
                indexToDelete = i;
                break;
            }
        if (indexToDelete != -1) {
            File* tmp = datoteki;
            this->datoteki = new File[n - 1];
            for (int i = 0, j = 0; i < n; i++)
                if (i != indexToDelete)
                    datoteki[j++] = tmp[i];
            n--;
        }
    }
};

//не менуваш во main

int main() {
    char fileName[20];
    char fileOwner[20];
    int ext;
    int fileSize;

    int testCase;
    cin >> testCase;
    if (testCase == 1) {
        cout << "======= FILE CONSTRUCTORS AND = OPERATOR =======" << endl;
        cin >> fileName;
        cin >> fileOwner;
        cin >> fileSize;
        cin >> ext;

        File created = File(fileName, fileOwner, fileSize, (Extension) ext);
        File copied = File(created);
        File assigned = created;

        cout << "======= CREATED =======" << endl;
        created.print();
        cout << endl;
        cout << "======= COPIED =======" << endl;
        copied.print();
        cout << endl;
        cout << "======= ASSIGNED =======" << endl;
        assigned.print();
    }
    else if (testCase == 2) {
        cout << "======= FILE EQUALS & EQUALS TYPE =======" << endl;
        cin >> fileName;
        cin >> fileOwner;
        cin >> fileSize;
        cin >> ext;

        File first(fileName, fileOwner, fileSize, (Extension) ext);
        first.print();

        cin >> fileName;
        cin >> fileOwner;
        cin >> fileSize;
        cin >> ext;

        File second(fileName, fileOwner, fileSize, (Extension) ext);
        second.print();

        cin >> fileName;
        cin >> fileOwner;
        cin >> fileSize;
        cin >> ext;

        File third(fileName, fileOwner, fileSize, (Extension) ext);
        third.print();

        bool equals = first.equals(second);
        cout << "FIRST EQUALS SECOND: ";
        if (equals)
            cout << "TRUE" << endl;
        else
            cout << "FALSE" << endl;

        equals = first.equals(third);
        cout << "FIRST EQUALS THIRD: ";
        if (equals)
            cout << "TRUE" << endl;
        else
            cout << "FALSE" << endl;

        bool equalsType = first.equalsType(second);
        cout << "FIRST EQUALS TYPE SECOND: ";
        if (equalsType)
            cout << "TRUE" << endl;
        else
            cout << "FALSE" << endl;

        equalsType = second.equals(third);
        cout << "SECOND EQUALS TYPE THIRD: ";
        if (equalsType)
            cout << "TRUE" << endl;
        else
            cout << "FALSE" << endl;

    }
    else if (testCase == 3) {
        cout << "======= FOLDER CONSTRUCTOR =======" << endl;
        cin >> fileName;
        Folder folder(fileName);
        folder.print();

    }
    else if (testCase == 4) {
        cout << "======= ADD FILE IN FOLDER =======" << endl;
        char name[20];
        cin >> name;
        Folder folder(name);

        int iter;
        cin >> iter;

        while (iter > 0) {
            cin >> fileName;
            cin >> fileOwner;
            cin >> fileSize;
            cin >> ext;

            File file(fileName, fileOwner, fileSize, (Extension) ext);
            folder.add(file);
            iter--;
        }
        folder.print();
    }
    else {
        cout << "======= REMOVE FILE FROM FOLDER =======" << endl;
        char name[20];
        cin >> name;
        Folder folder(name);

        int iter;
        cin >> iter;

        while (iter > 0) {
            cin >> fileName;
            cin >> fileOwner;
            cin >> fileSize;
            cin >> ext;

            File file(fileName, fileOwner, fileSize, (Extension) ext);
            folder.add(file);
            iter--;
        }
        cin >> fileName;
        cin >> fileOwner;
        cin >> fileSize;
        cin >> ext;

        File file(fileName, fileOwner, fileSize, (Extension) ext);
        folder.remove(file);
        folder.print();
    }
    return 0;
}