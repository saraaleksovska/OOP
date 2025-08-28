#include <iostream>
#include <cstring>
using namespace std;

class ExistingGame {
private:
    char msg[256];
public:
    ExistingGame(const char *txt) {
        strncpy(this->msg, txt, 255);
        this->msg[255] = '\0';
    }
    void message() {
        cout << msg << endl;
    }
};

class Game {
protected:
    char ime[100];
    float cena;
    bool rasprodazba;
public:
    Game() {
        ime[0] = '\0';
        cena = 0.0;
        rasprodazba = false;
    }
    Game(const char *ime, float cena, bool rasprodazba) {
        strcpy(this->ime, ime);
        this->cena = cena;
        this->rasprodazba = rasprodazba;
    }
    virtual ~Game() {}

    virtual float get_price() {
        if (rasprodazba) return cena * 0.3f;
        return cena;
    }

    bool operator==(Game &g) {
        return strcmp(this->ime, g.ime) == 0;
    }

    friend ostream &operator<<(ostream &o, const Game &g) {
        o << "Game: " << g.ime << ", regular price: $" << g.cena;
        if (g.rasprodazba) {
            o << ", bought on sale";
        }
        return o;
    }

    friend istream &operator>>(istream &i, Game &g) {
        i.get();
        i.getline(g.ime, 100);
        i >> g.cena >> g.rasprodazba;
        return i;
    }
};

class SubscriptionGame : public Game {
protected:
    float nadomestok;
    int mesec, godina;
public:
    SubscriptionGame() : Game() {
        nadomestok = 0;
        mesec = godina = 0;
    }
    SubscriptionGame(const char *ime, float cena = 0.0, bool rasprodazba = false,float nadomestok = 0.0, int mesec = 0, int godina = 0)
            : Game(ime, cena, rasprodazba) {
        this->nadomestok = nadomestok;
        this->mesec = mesec;
        this->godina = godina;
    }

    float get_price() override {
        int meseci;
        if (godina < 2018) {
            meseci = (12 - mesec) + (2017 - godina) * 12 + 5;
        } else {
            meseci = 5 - mesec;
            if (meseci < 0) {
                meseci = 0;
            }
        }
        return Game::get_price() + meseci * nadomestok;
    }

    friend ostream &operator<<(ostream &o, SubscriptionGame &sg) {
        Game *tmp = &sg;
        o << *tmp;
        o << ", monthly fee: $" << sg.nadomestok
          << ", purchased: " << sg.mesec << "-" << sg.godina;
        return o;
    }

    friend istream &operator>>(istream &is, SubscriptionGame &g) {
        is.get();
        is.getline(g.ime, 100);
        is >> g.cena >> g.rasprodazba;
        is >> g.nadomestok >> g.mesec >> g.godina;
        return is;
    }
};

class User {
private:
    char username[100];
    Game **igri;
    int n;

    void copy(const User &u) {
        strcpy(this->username, u.username);
        this->n = u.n;
        this->igri = new Game *[n];
        for (int i = 0; i < u.n; i++) {
            SubscriptionGame *sg = dynamic_cast<SubscriptionGame *>(u.igri[i]);
            if (sg) {
                this->igri[i] = new SubscriptionGame(*sg);
            } else {
                this->igri[i] = new Game(*u.igri[i]);
            }
        }
    }
public:
    User(const char *username = "") {
        strcpy(this->username, username);
        igri = nullptr;
        n = 0;
    }
    User(const User &u) {
        copy(u);
    }
    ~User() {
        for (int i = 0; i < n; i++) {
            delete igri[i];
        }
        delete[] igri;
    }
    User &operator=(const User &u) {
        if (this != &u) {
            for (int i = 0; i <u.n; i++) {
                delete igri[i];
            }
            delete[] igri;
            copy(u);
        }
        return *this;
    }
    User &operator+=(Game &g) {
        for (int i = 0; i < n; i++) {
            if (*igri[i] == g) {
                throw ExistingGame("The game is already in the collection");
            }
        }
        Game **noviIgri = new Game *[n + 1];
        for (int i = 0; i < n; i++) {
            noviIgri[i] = igri[i];
        }
        SubscriptionGame *sg = dynamic_cast<SubscriptionGame *>(&g);
        if (sg) {
            noviIgri[n] = new SubscriptionGame(*sg);
        } else {
            noviIgri[n] = new Game(g);
        }
        delete[] igri;
        igri = noviIgri;
        n++;
        return *this;
    }
    float total_spent() {
        float sum = 0;
        for (int i = 0; i < n; i++) {
            sum += igri[i]->get_price();
        }
        return sum;
    }
    const char *get_username() {
        return username;
    }
    int get_games_number() {
        return n;
    }

    friend ostream &operator<<(ostream &o, User &u) {
        o << "\nUser: " << u.get_username() << "\n";
        for (int i = 0; i < u.get_games_number(); i++) {
            SubscriptionGame *sg = dynamic_cast<SubscriptionGame *>(u.igri[i]);
            if (sg) {
                o << "- " << *sg;
            } else {
                o << "- " << *u.igri[i];
            }
            o << "\n";
        }
        return o;
    }
};

//не менуваш ништо во main
int main() {
    int test_case_num;
    cin>>test_case_num;

    // for Game
    char game_name[100];
    float game_price;
    bool game_on_sale;

    // for SubscritionGame
    float sub_game_monthly_fee;
    int sub_game_month, sub_game_year;

    // for User
    char username[100];
    int num_user_games;

    if (test_case_num == 1){
        cout<<"Testing class Game and operator<< for Game"<<std::endl;
        cin.get();
        cin.getline(game_name,100);
        //cin.get();
        cin>>game_price>>game_on_sale;

        Game g(game_name, game_price, game_on_sale);

        cout<<g;
    }
    else if (test_case_num == 2){
        cout<<"Testing class SubscriptionGame and operator<< for SubscritionGame"<<std::endl;
        cin.get();
        cin.getline(game_name, 100);
        cin>>game_price>>game_on_sale;
        cin>>sub_game_monthly_fee;
        cin>>sub_game_month>>sub_game_year;
        SubscriptionGame sg(game_name, game_price, game_on_sale, sub_game_monthly_fee, sub_game_month, sub_game_year);
        cout<<sg;
    }
    else if (test_case_num == 3){
        cout<<"Testing operator>> for Game"<<std::endl;
        Game g;
        cin>>g;
        cout<<g;
    }
    else if (test_case_num == 4){
        cout<<"Testing operator>> for SubscriptionGame"<<std::endl;
        SubscriptionGame sg;
        cin>>sg;
        cout<<sg;
    }
    else if (test_case_num == 5){
        cout<<"Testing class User and operator+= for User"<<std::endl;
        cin.get();
        cin.getline(username,100);
        User u(username);
        int num_user_games;
        int game_type;
        cin >>num_user_games;
        try {
            for (int i=0; i<num_user_games; ++i){
                cin >> game_type;
                Game *g;
                // 1 - Game, 2 - SubscriptionGame
                if (game_type == 1){
                    cin.get();
                    cin.getline(game_name, 100);
                    cin>>game_price>>game_on_sale;
                    g = new Game(game_name, game_price, game_on_sale);
                }
                else if (game_type == 2){
                    cin.get();
                    cin.getline(game_name, 100);
                    cin>>game_price>>game_on_sale;
                    cin>>sub_game_monthly_fee;
                    cin>>sub_game_month>>sub_game_year;
                    g = new SubscriptionGame(game_name, game_price, game_on_sale, sub_game_monthly_fee, sub_game_month, sub_game_year);
                }
                u+=(*g);
            }
        }catch(ExistingGame &ex){
            ex.message();
        }

        cout<<u;
    }
    else if (test_case_num == 6){
        cout<<"Testing exception ExistingGame for User"<<std::endl;
        cin.get();
        cin.getline(username,100);
        User u(username);
        int num_user_games;
        int game_type;
        cin >>num_user_games;
        for (int i=0; i<num_user_games; ++i){
            cin >> game_type;
            Game *g;
            // 1 - Game, 2 - SubscriptionGame
            if (game_type == 1){
                cin.get();
                cin.getline(game_name, 100);
                cin>>game_price>>game_on_sale;
                g = new Game(game_name, game_price, game_on_sale);
            }
            else if (game_type == 2){
                cin.get();
                cin.getline(game_name, 100);
                cin>>game_price>>game_on_sale;
                cin>>sub_game_monthly_fee;
                cin>>sub_game_month>>sub_game_year;
                g = new SubscriptionGame(game_name, game_price, game_on_sale, sub_game_monthly_fee, sub_game_month, sub_game_year);
            }
            try {
                u+=(*g);
            }
            catch(ExistingGame &ex){
                ex.message();
            }
        }
        cout<<u;
    }
    else if (test_case_num == 7){
        cout<<"Testing total_spent method() for User"<<std::endl;
        cin.get();
        cin.getline(username,100);
        User u(username);
        int num_user_games;
        int game_type;
        cin >>num_user_games;
        for (int i=0; i<num_user_games; ++i){
            cin >> game_type;
            Game *g;
            // 1 - Game, 2 - SubscriptionGame
            if (game_type == 1){
                cin.get();
                cin.getline(game_name, 100);
                cin>>game_price>>game_on_sale;
                g = new Game(game_name, game_price, game_on_sale);
            }
            else if (game_type == 2){
                cin.get();
                cin.getline(game_name, 100);
                cin>>game_price>>game_on_sale;
                cin>>sub_game_monthly_fee;
                cin>>sub_game_month>>sub_game_year;
                g = new SubscriptionGame(game_name, game_price, game_on_sale, sub_game_monthly_fee, sub_game_month, sub_game_year);
            }
            u+=(*g);
        }
        cout<<u<<endl;
        cout<<"Total money spent: $"<<u.total_spent()<<endl;
    }

    return 0;
}
