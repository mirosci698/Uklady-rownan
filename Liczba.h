#ifndef Liczba_h
#define Liczba_h
#include <iostream>
#include <Windows.h>
//przy przekazywaniu liczb u�ywamy referencji z const, opr�cz operatora >> gdzie musimy zmienia� warto�� i metody zamieniaj�cej
//nie mo�na zdefiniowa� w .cpp - linker si� nie zgadza dlatego tutaj
template<class T> //wzorzec klasy bo prawie to samo robimy dla int i double
class liczba {
	friend class macierz;	//zaprzyja�nienie w celu mo�liwo�ci dost�pu do czystej warto�ci przez klas�
	friend class macierzkwadratowa;
	friend class wektor;
	T wartosc;	//czysta wartosc
public:
	liczba(); //potrzebne konstruktory:bezarg (daj�cy 0), wpisuj�cy z komunikatem i kopiuj�cy
	liczba(char*);
	liczba(const liczba<T>&);
	~liczba();	//destruktor
	liczba& operator=(const liczba<T> &);	//operatory przypisania, r�nowarto�ciowy, dodaj�cy ca�kowit�, inkrementacji prefiksowy
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
	void wpis(char*);	//metody wpisu (komunikat), matematyczne z kontrol� wykonania, zamiany
	bool odwrotnosc();
	bool niedodatnia();
	void zamien(liczba<T>&);
	friend std::istream& operator >> (std::istream& is, liczba<T>& t) //zaprzyja�nione operatory strumieniowe I/O (jako funkcje)
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
liczba<T>::liczba(char* kom)	//kons wpisuj�cy z komentarzem
{
	wpis(kom);
}
template<class T>
void liczba<T>::wpis(char* kom) //metoda wpisu warto�ci do liczby
{
	bool blad; //zmienne pomocnicze
	char c;
	do
	{
		std::cin.clear();	//czyszczenie bufora b��du
		system("cls");	//od�wie�enie okna
		std::cout << kom;	//wypis informacji
		std::cin >> wartosc;	//wpis bez whitespace'�w
		blad = std::cin.fail();	//sprawdzenie buforu b��d�w
		std::cin.get(c);
		if (c != 10)	//sprawdzenie czy ostatni znak to enter (zabezp na np. 98nu)
			blad = true;
		if (blad)	//w przypadku b��d�w
		{
			system("cls");	//od�wie�enie ekranu
			std::cout << "Blad odczytu liczby" << std::endl;	//informacja
			std::cin.clear();
			std::cin.sync();	//wyczyszczenie buforu b��du i klawiatury (linux i win)
			std::cin.ignore(1000, '\n');
			Sleep(1000);	//wy�w informacji przez sekund�
			system("cls");
		}
	} while (blad);	//powtarzanie dop�ki z�a
	std::cin.clear(); //oczyszczenie bufora b��du (bufor klawiatury oczyszczony zczytem warto�ci)
}
template<class T>
liczba<T>::liczba(const liczba &l) :wartosc(l.wartosc) {} //kopiowanie wymaga tylko przepisania warto�ci, domy�lny te� by mog� byc
template<class T>
liczba<T>::~liczba() {} //wystarczy dzia�anie domy�lne
template<class T>
liczba<T> & liczba<T>::operator=(const liczba<T> &li)	//operator przypisania (musi zwraca� referencje ze wzgl na ��czno��)
{
	if (this == &li)
		return *this; //sprawdzenie czy a=a
	wartosc = li.wartosc;	//przepisanie warto�ci
	return *this;
}
template<class T>
bool liczba<T>::operator!=(const liczba<T>& por) //operator r�nowarto�ciowy, zwraca info o tym
{
	if ((*this).wartosc != por.wartosc)	//sprawdzenie relacji mi�dzy warto�ciami liczb
		return true;
	else
		return false;
}
template<class T>
bool liczba<T>::odwrotnosc() //metoda to odwracania liczb, zwraca info czy si� uda�o
{
	if (wartosc == 0)	//nie mozna dzielic na 0, info o bledzie
		return false;
	else
		wartosc = 1 / wartosc; //odwrocenie liczby
	return true;
}
template<class T>
bool liczba<T>::niedodatnia() //metoda sprawdzaj�ca niedodatnio�� liczby, zwraca info o tym
{
	if (wartosc > 0)
		return false; //w zaleznosci od wartosci liczby zwroc info
	else
		return true;
}
template<class T>
void liczba<T>::zamien(liczba<T> & licz) //metoda zamieniaj�ca dwie liczby
{
	liczba tmp = *this; //zamiana
	*this = licz;
	licz = tmp;
}
#endif