#include<iostream>
#include<cstring>
/*
  1. Чисто виртуелна функција е функција која е само декларирана во главната класа со virtual tip imeFunkcija()=0. И сега кога во главната класа
      ќе се содржи оваа виртуелна функција, класата станува апстрактна.

  2. Чисто виртуелната функција само се декларира во апстрактната класа, но како сакаме да работи се прави во класите наследници.

  3. Aпстрактна класа e класа која мора да има барем една чисто виртуелна функција (декларирана со virtual tip imeFunkcija()=0)

  4. Кога класата е апстрактна, не може да направиш директно објект од нејзе, туку креираш објекти од нејзините наследници класи(кои ја
     имплементираат виртуелната функција)
      или во превод
      Book b("20", "Harry Potter", "Avtor", 500);                     //ова не може
      OnlineBook ob("20", "Harry Potter", "Avtor", 500, "url", 30);  //ова може, бидејќи ОnlineBook е наследник на Book
      PrintBook pb ("20", "Harry Potter", "Avtor", 500, 0.9, true); //ова може бидејќи PrintBook е наследник на Book
 */

using namespace std;
class Book {
protected:
	char isbn[20];
	char naslov[50];
	char avtor[30];
	float cena;
public:
	Book(const char *isbn = "", const char *naslov = "", const char *avtor = "", float cena = 0.0){
        strcpy(this->isbn,isbn);
        strcpy(this->naslov, naslov);
        strcpy(this->avtor,avtor);
        this->cena=cena;
	}
	virtual float bookPrice() = 0; //декларација на чисто виртуелната функција, класата Book станува апстрактна
    virtual ~Book(){}
	friend ostream &operator<< (ostream &o, Book &b){
		o << b.isbn << ": " << b.naslov << ", " << b.avtor << " " << b.bookPrice() << endl;
		return o;
	}
     friend bool operator>(Book &b1, Book &b2){
        return (b1.bookPrice()>b2.bookPrice());
    }
    void setISBN(char *isbn){
        strcpy(this->isbn,isbn);
    }
};

class OnlineBook : public Book {
private:
	char *url;
	int golemina;
    void copy(const OnlineBook &ob){
        strcpy(isbn, ob.isbn);
        strcpy(naslov, ob.naslov);
        strcpy(avtor, ob.avtor);
        this->cena = ob.cena;
        url = new char[strlen(ob.url) + 1];
        strcpy(url, ob.url);
        this->golemina = ob.golemina;
    }
public:
	OnlineBook(const char *isbn = "", const char *naslov = "", const char *avtor = "", float cena = 0.0, const char *url = "", int golemina = 0)
		:Book(isbn, naslov, avtor, cena){
		this->url = new char[strlen(url) + 1];
		strcpy(this->url, url);
		this->golemina = golemina;
	}
	OnlineBook(OnlineBook &ob){
		copy(ob);
	}
	OnlineBook &operator=(OnlineBook &ob){
		if (this != &ob){
			delete[] url;
            copy(ob);
		}
		return *this;
	}
	~OnlineBook(){
		delete[] url;
	}
	float bookPrice() override{ //кажуваме како сакаме да работи виртуелната ф-ја
		if (golemina>20) {
            return cena* 1.2;
        }
		return cena;
	}
};
class PrintBook :public Book {
private:
	float masa;
	bool naZaliha;
public:
	PrintBook(const char *isbn = "", const char *naslov = "", const char *avtor = "", float cena = 0.0, float masa = 0.0, bool naZaliha = false)
		:Book(isbn, naslov, avtor, cena){
		this->masa = masa;
		this->naZaliha = naZaliha;
	}
	float bookPrice() override{ //кажуваме како сакаме да работи виртуелната ф-ја
		if (masa>0.7)
			return cena*1.15;
		return cena;
	}
};
void mostExpensiveBook(Book **books, int n){
	int brOnline = 0;
	int brPrint = 0;
	for (int i = 0; i<n; i++){
		OnlineBook *ob = dynamic_cast<OnlineBook*>(books[i]);
		if (ob != 0)
            brOnline++;
		PrintBook *pb = dynamic_cast<PrintBook*>(books[i]);
		if (pb != 0)
            brPrint++;
	}
	cout << "FINKI-Education" << endl;
	cout << "Total number of online books: " << brOnline << endl;
	cout << "Total number of print books: " << brPrint << endl;
	Book *najskapa = books[0];
	for (int i = 1; i<n; i++)
		if (*books[i] > *najskapa)
            najskapa = books[i];
	cout << "The most expensive book is: " << endl;
	cout << *najskapa;
}

//не менуваш ништо во main

int main(){
	char isbn[20], title[50], author[30], url[100];
	int size, tip;
	float price, weight;
	bool inStock;
	Book  **books;
	int n;

	int testCase;
	cin >> testCase;

	if (testCase == 1){
		cout << "====== Testing OnlineBook class ======" << endl;
		cin >> n;
		books = new Book *[n];

		for (int i = 0; i < n; i++){
			cin >> isbn;
			cin.get();
			cin.getline(title, 50);
			cin.getline(author, 30);
			cin >> price;
			cin >> url;
			cin >> size;
			cout << "CONSTRUCTOR" << endl;
			books[i] = new OnlineBook(isbn, title, author, price, url, size);
			cout << "OPERATOR <<" << endl;
			cout << *books[i];
		}
		cout << "OPERATOR >" << endl;
		cout << "Rezultat od sporedbata e: " << endl;
		if (*books[0] > *books[1])
			cout << *books[0];
		else
			cout << *books[1];
	}
	if (testCase == 2){
		cout << "====== Testing OnlineBook CONSTRUCTORS ======" << endl;
		cin >> isbn;
		cin.get();
		cin.getline(title, 50);
		cin.getline(author, 30);
		cin >> price;
		cin >> url;
		cin >> size;
		cout << "CONSTRUCTOR" << endl;
		OnlineBook ob1(isbn, title, author, price, url, size);
		cout << ob1 << endl;
		cout << "COPY CONSTRUCTOR" << endl;
		OnlineBook ob2(ob1);
		cin >> isbn;
		ob2.setISBN(isbn);
		cout << ob1 << endl;
		cout << ob2 << endl;
		cout << "OPERATOR =" << endl;
		ob1 = ob2;
		cin >> isbn;
		ob2.setISBN(isbn);
		cout << ob1 << endl;
		cout << ob2 << endl;
	}
	if (testCase == 3){
		cout << "====== Testing PrintBook class ======" << endl;
		cin >> n;
		books = new Book *[n];
		for (int i = 0; i < n; i++){
			cin >> isbn;
			cin.get();
			cin.getline(title, 50);
			cin.getline(author, 30);
			cin >> price;
			cin >> weight;
			cin >> inStock;
			cout << "CONSTRUCTOR" << endl;
			books[i] = new PrintBook(isbn, title, author, price, weight, inStock);
			cout << "OPERATOR <<" << endl;
			cout << *books[i];
		}
		cout << "OPERATOR >" << endl;
		cout << "Rezultat od sporedbata e: " << endl;
		if (*books[0] > *books[1])
			cout << *books[0];
		else
			cout << *books[1];
	}
	if (testCase == 4){
		cout << "====== Testing method mostExpensiveBook() ======" << endl;
		cin >> n;
		books = new Book *[n];
		for (int i = 0; i<n; i++){
			cin >> tip >> isbn;
			cin.get();
			cin.getline(title, 50);
			cin.getline(author, 30);
			cin >> price;
			if (tip == 1) {
				cin >> url;
				cin >> size;
				books[i] = new OnlineBook(isbn, title, author, price, url, size);
			}
			else {
				cin >> weight;
				cin >> inStock;
				books[i] = new PrintBook(isbn, title, author, price, weight, inStock);
			}
		}
		mostExpensiveBook(books, n);
	}
	for (int i = 0; i<n; i++) delete books[i];
		delete[] books;
	return 0;
}
