#ifndef Liczba_h
#define Liczba_h
#include <iostream>
#include <Windows.h>
//przy przekazywaniu liczb u¿ywamy referencji z const, oprócz operatora >> gdzie musimy zmieniaæ wartoœæ i metody zamieniaj¹cej
//nie mo¿na zdefiniowaæ w .cpp - linker siê nie zgadza dlatego tutaj
template<class T> //wzorzec klasy bo prawie to samo robimy dla int i double
class liczba {
	friend class macierz;	//zaprzyjaŸnienie w celu mo¿liwoœci dostêpu do czystej wartoœci przez klasê
	friend class macierzkwadratowa;
	friend class wektor;
	T wartosc;	//czysta wartosc
public:
	liczba(); //potrzebne konstruktory:bezarg (daj¹cy 0), wpisuj¹cy z komunikatem i kopiuj¹cy
	liczba(char*);
	liczba(const liczba<T>&);
	~liczba();	//destruktor
	liczba& operator=(const liczba<T> &);	//operatory przypisania, ró¿nowartoœciowy, dodaj¹cy ca³kowit¹, inkrementacji prefiksowy
	bool operator!=(const liczba<T> &);
	liczba<int> operator+(int i) 
	{
		liczba l = *this;
		l.wartosc += i;
		return l;
	}
	liczba<int>& operator++()
	{
		++wartosc;
		return *this;
	}
	void wpis(char*);	//metody wpisu (komunikat), matematyczne z kontrol¹ wykonania, zamiany
	bool odwrotnosc();
	bool niedodatnia();
	void zamien(liczba<T>&);
	friend std::istream& operator >> (std::istream& is, liczba<T>& t) //zaprzyjaŸnione operatory strumieniowe I/O (jako funkcje)
	{
		is >> t.wartosc;
		return is;
	}
	friend std::ostream& operator<<(std::ostream& os, const liczba<T>& t)
	{
		os << t.wartosc;
		return os;
	}
};
template<class T>
liczba<T>::liczba() :wartosc(0) {} //konstrukcja bezarg - 0
template<class T>
liczba<T>::liczba(char* kom)	//kons wpisuj¹cy z komentarzem
{
	wpis(kom);
}
template<class T>
void liczba<T>::wpis(char* kom) //metoda wpisu wartoœci do liczby
{
	bool blad; //zmienne pomocnicze
	char c;
	do
	{
		std::cin.clear();	//czyszczenie bufora b³êdu
		system("cls");	//odœwie¿enie okna
		std::cout << kom;	//wypis informacji
		std::cin >> wartosc;	//wpis bez whitespace'ów
		blad = std::cin.fail();	//sprawdzenie buforu b³êdów
		std::cin.get(c);
		if (c != 10)	//sprawdzenie czy ostatni znak to enter (zabezp na np. 98nu)
			blad = true;
		if (blad)	//w przypadku b³êdów
		{
			system("cls");	//odœwie¿enie ekranu
			std::cout << "Blad odczytu liczby" << std::endl;	//informacja
			std::cin.clear();
			std::cin.sync();	//wyczyszczenie buforu b³êdu i klawiatury (linux i win)
			std::cin.ignore(1000, '\n');
			Sleep(1000);	//wyœw informacji przez sekundê
			system("cls");
		}
	} while (blad);	//powtarzanie dopóki z³a
	std::cin.clear(); //oczyszczenie bufora b³êdu (bufor klawiatury oczyszczony zczytem wartoœci)
}
template<class T>
liczba<T>::liczba(const liczba &l) :wartosc(l.wartosc) {} //kopiowanie wymaga tylko przepisania wartoœci, domyœlny te¿ by mog³ byc
template<class T>
liczba<T>::~liczba() {} //wystarczy dzia³anie domyœlne
template<class T>
liczba<T> & liczba<T>::operator=(const liczba<T> &li)	//operator przypisania (musi zwracaæ referencje ze wzgl na ³¹cznoœæ)
{
	if (this == &li)
		return *this; //sprawdzenie czy a=a
	wartosc = li.wartosc;	//przepisanie wartoœci
	return *this;
}
template<class T>
bool liczba<T>::operator!=(const liczba<T>& por) //operator ró¿nowartoœciowy, zwraca info o tym
{
	if ((*this).wartosc != por.wartosc)	//sprawdzenie relacji miêdzy wartoœciami liczb
		return true;
	else
		return false;
}
template<class T>
bool liczba<T>::odwrotnosc() //metoda to odwracania liczb, zwraca info czy siê uda³o
{
	if (wartosc == 0)	//nie mozna dzielic na 0, info o bledzie
		return false;
	else
		wartosc = 1 / wartosc; //odwrocenie liczby
	return true;
}
template<class T>
bool liczba<T>::niedodatnia() //metoda sprawdzaj¹ca niedodatnioœæ liczby, zwraca info o tym
{
	if (wartosc > 0)
		return false; //w zaleznosci od wartosci liczby zwroc info
	else
		return true;
}
template<class T>
void liczba<T>::zamien(liczba<T> & licz) //metoda zamieniaj¹ca dwie liczby
{
	liczba tmp = *this; //zamiana
	*this = licz;
	licz = tmp;
}
#endif