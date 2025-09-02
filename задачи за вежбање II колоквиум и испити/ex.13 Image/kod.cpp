#include <iostream>
#include <cstring>

using namespace std;

int const username_dolzina = 100;
int const imeFolder_dolzina = 255;
int const maxFajlovi_folder = 100;

class Image{
protected:
    char *ime;
    char sopstvenik[username_dolzina+1];
    int shirina;
    int visina;
    void copy(const Image &i){
        this->ime = new char[strlen(i.ime)+1];
        strcpy(this->ime, i.ime);
        strncpy(this->sopstvenik, i.sopstvenik, username_dolzina);
        this->sopstvenik[username_dolzina] = '\0';
        this->shirina = i.shirina;
        this->visina = i.visina;
    }
public:
    Image (char *ime="untitled", char *sopstvenik="unknown", int shirina=800, int visina=800) {
        this->ime = new char[strlen(ime)+1];
        strcpy(this->ime, ime);
        strncpy(this->sopstvenik, sopstvenik, username_dolzina);
        this->sopstvenik[50] = '\0';
        this->shirina = shirina;
        this->visina = visina;
    }
    virtual ~Image(){
        delete[] this->ime;
    }
    Image (const Image &i){
        copy(i);
    }
    Image &operator=(const Image &i){
        if (this!=&i){
            delete [] this->ime;
            copy(i);
        }
        return *this;
    }
    virtual int fileSize() const{
        return this->shirina * this->visina * 3;
    }
    friend ostream &operator<<(ostream &o, const Image &i) {
        o << i.ime << " " << i.sopstvenik << " " << i.fileSize() << '\n';
        return o;
    }
    bool operator > (const Image &i){
        return this->fileSize() > i.fileSize();
    }
};

class TransparentImage: public Image{
protected:
    bool transparency_layers;
    void copy(const TransparentImage &ti){
        this->ime = new char[strlen(ti.ime)+1];
        strcpy(this->ime, ti.ime);
        strncpy(this->sopstvenik, ti.sopstvenik, username_dolzina);
        this->sopstvenik[username_dolzina] = '\0';
        this->shirina = ti.shirina;
        this->visina= ti.visina;
        this->transparency_layers = ti.transparency_layers;
    }
public:
    TransparentImage(char *ime="untitled", char *sopstvenik="unknown", int shirina=800, int visina=800, bool tl=true):Image(ime, sopstvenik, shirina, visina) {
        this->transparency_layers = tl;
    }
    TransparentImage(const TransparentImage &ti){
        copy(ti);
    }
    TransparentImage &operator=(const TransparentImage &ti){
        if (this!=&ti){
            delete [] this->ime;
            copy(ti);
        }
        return *this;
    }
    int fileSize() const {
        if (transparency_layers)
            return this->shirina * this->visina * 4;
        else {
            return this->shirina * this->visina + (this->shirina * this->visina)/8;
        }
    }
    friend ostream &operator<<(ostream& o, const TransparentImage &f){
        o << f.ime << " " << f.sopstvenik << " " << f.fileSize() << '\n';
        return o;
    }
};

class Folder{
protected:
    char ime[imeFolder_dolzina+1];
    char username[username_dolzina+1];
    Image * files[maxFajlovi_folder];
    int n;
    void copy(const Folder &f){
        strcpy(this->ime, f.ime);
        strcpy(this->username, f.username);
        this->n = f.n;
        for (int i=0; i<this->n; ++i){
            TransparentImage * tf= dynamic_cast<TransparentImage*>(f.files[i]);
            if (tf){
                this->files[i] = new TransparentImage(*tf);
            }else {
                this->files[i] = new Image(*(f.files[i]));
            }
        }
    }
public:
    Folder(char *ime="untitled", char* username="unknown"){
        strncpy(this->ime,ime,imeFolder_dolzina);
        this->ime[imeFolder_dolzina] = '\n';
        strncpy(this->username,username,username_dolzina);
        this->ime[username_dolzina] = '\n';
        this->n = 0;
    }

    Folder(const Folder &f){
        copy(f);
    }
    ~Folder (){
        for (int i=0; i<this->n; ++i){
            delete files[i];
        }
    }
    Folder &operator=(const Folder &f){
        if (this!=&f){
            for (int i=0; i<this->n; i++){
                delete files[i];
            }
            copy(f);
        }
        return *this;
    }
    int folderSize() const {
        int s = 0;
        TransparentImage* tf;
        for (int i=0; i<n; ++i){
            tf = dynamic_cast<TransparentImage*>(this->files[i]);
            if (tf){
                s+=tf->fileSize();
            }else
                s += files[i]->fileSize();
        }
        return s;
    }
    Folder &operator+=(Image &nf){
        if (this->n < 255){
            TransparentImage* tf= dynamic_cast<TransparentImage*>(&nf);
            if (tf){
                this->files[n] = new TransparentImage(*tf);
            }else {
                this->files[n] = new Image(nf);
            }
            n++;
        }
        return *this;
    }
    Image *operator[](int i){
        if (i<0 && i >= this->n)
            return NULL;
        return this->files[i];
    }
    friend ostream &operator<<(ostream &o, Folder &f){
        o << f.ime << " " << f.username <<"\n--\n";
        TransparentImage *tf;
        for (int i=0; i<f.n; ++i){
            tf = dynamic_cast<TransparentImage*>(f.files[i]);
            if (tf){
                o << *tf;
            }else {
                o << *f.files[i];
            }
        }
        o << "--\nFolder size: " << f.folderSize() << endl;
        return o;
    }
    Image *getMaxFile(){
        int mfs = 0;
        int mi = -1;
        int cfs;
        if (n>0){
            mfs = this->files[0]->fileSize();
            mi = 0;
            for (int i=0; i<this->n; ++i){
                cfs = this->files[i]->fileSize();
                if (cfs > mfs){
                    mfs = cfs;
                    mi = i;
                }
            }
            return files[mi];
        }
        else return NULL;
    }
};

Folder &max_folder_size(Folder *f, int nf){
    int ms=f[0].folderSize();
    int mi = 0;
    for (int i=0; i<nf; ++i){
        if (f[i].folderSize()>ms){
            mi=i;
            ms=f[i].folderSize();
        }
    }
    return f[mi];
}



int main() {
    int tc; // Test Case
    char name[255];
    char user_name[51];
    int w, h;
    bool tl;

    cin >> tc;

    if (tc==1){
        // Testing constructor(s) & operator << for class File

        cin >> name;
        cin >> user_name;
        cin >> w;
        cin >> h;


        Image f1;

        cout<< f1;

        Image f2(name);
        cout<< f2;

        Image f3(name, user_name);
        cout<< f3;

        Image f4(name, user_name, w, h);
        cout<< f4;
    }
    else if (tc==2){
        // Testing constructor(s) & operator << for class TextFile
        cin >> name;
        cin >> user_name;
        cin >> w >> h;
        cin >> tl;

        TransparentImage tf1;
        cout<< tf1;

        TransparentImage tf4(name, user_name, w, h, tl);
        cout<< tf4;
    }
    else if (tc==3){
        // Testing constructor(s) & operator << for class Folder
        cin >> name;
        cin >> user_name;

        Folder f3(name, user_name);
        cout<< f3;
    }
    else if (tc==4){
        // Adding files to folder
        cin >> name;
        cin >> user_name;

        Folder dir(name, user_name);

        Image * f;
        TransparentImage *tf;

        int sub, fileType;

        while (1){
            cin >> sub; // Should we add subfiles to this folder
            if (!sub) break;

            cin >>fileType;
            if (fileType == 1){ // Reading File
                cin >> name;
                cin >> user_name;
                cin >> w >> h;
                f = new Image(name,user_name, w, h);
                dir += *f;
            }
            else if (fileType == 2){
                cin >> name;
                cin >> user_name;
                cin >> w >> h;
                cin >> tl;
                tf = new TransparentImage(name,user_name, w, h, tl);
                dir += *tf;
            }
        }
        cout<<dir;
    }
    else if(tc==5){
        // Testing getMaxFile for folder

        cin >> name;
        cin >> user_name;

        Folder dir(name, user_name);

        Image* f;
        TransparentImage* tf;

        int sub, fileType;

        while (1){
            cin >> sub; // Should we add subfiles to this folder
            if (!sub) break;

            cin >>fileType;
            if (fileType == 1){ // Reading File
                cin >> name;
                cin >> user_name;
                cin >> w >> h;
                f = new Image(name,user_name, w, h);
                dir += *f;
            }
            else if (fileType == 2){
                cin >> name;
                cin >> user_name;
                cin >> w >> h;
                cin >> tl;
                tf = new TransparentImage(name,user_name, w, h, tl);
                dir += *tf;
            }
        }
        cout<< *(dir.getMaxFile());
    }
    else if(tc==6){
        // Testing operator [] for folder

        cin >> name;
        cin >> user_name;

        Folder dir(name, user_name);

        Image* f;
        TransparentImage* tf;

        int sub, fileType;

        while (1){
            cin >> sub; // Should we add subfiles to this folder
            if (!sub) break;

            cin >>fileType;
            if (fileType == 1){ // Reading File
                cin >> name;
                cin >> user_name;
                cin >> w >> h;
                f = new Image(name,user_name, w, h);
                dir += *f;
            }
            else if (fileType == 2){
                cin >> name;
                cin >> user_name;
                cin >> w >> h;
                cin >> tl;
                tf = new TransparentImage(name,user_name, w, h, tl);
                dir += *tf;
            }
        }

        cin >> sub; // Reading index of specific file
        cout<< *dir[sub];
    }
    else if(tc==7){
        // Testing function max_folder_size
        int folders_num;

        Folder dir_list[10];

        Folder dir;
        cin >> folders_num;

        for (int i=0; i<folders_num; ++i){
            cin >> name;
            cin >> user_name;
            dir = Folder(name, user_name);


            Image* f;
            TransparentImage *tf;

            int sub, fileType;

            while (1){
                cin >> sub; // Should we add subfiles to this folder
                if (!sub) break;

                cin >>fileType;
                if (fileType == 1){ // Reading File
                    cin >> name;
                    cin >> user_name;
                    cin >> w >> h;
                    f = new Image(name,user_name, w, h);
                    dir += *f;
                }
                else if (fileType == 2){
                    cin >> name;
                    cin >> user_name;
                    cin >> w >> h;
                    cin >> tl;
                    tf = new TransparentImage(name,user_name, w, h, tl);
                    dir += *tf;
                }
            }
            dir_list[i] = dir;
        }

        cout<<max_folder_size(dir_list, folders_num);
    }
    return 0;
};
