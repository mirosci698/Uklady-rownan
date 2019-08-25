#ifndef Klasa_h
#define Klasa_h
#include "Liczba.h"
class macierz {
protected:	//musimy mie� dost�p do zmiennych klasowych w klasach potomnych
	liczba<double> **pole;	//tablica 2 wymiarowa element�w
	liczba<int> lwierszy;	//informacje o macierzy
	liczba<int> lkolumn;
public:
	macierz();	//potrzebne konstruktory:bezarg, 2 arg i kopiuj�cy
	macierz(const liczba<int>&, const liczba<int>&);
	macierz(const macierz &);
	~macierz();	//destruktor
	liczba<double>* operator[](int);	//operatory indeksacji dla zwyk�ych i const
	const liczba<double>* operator[](int) const;
	macierz& operator=(const macierz&);	//operator przypisania
	bool dodajdomnie(const macierz &); //metody: operacje matem (bool gdy mog� nie by� wykonalne)
	void mnozskalar(double);
	bool mnozprawo(const macierz&);
	bool domnozzlewej(const macierz &);
	bool zamianawierszy(wektor&);	//metody zamieniaj�ca wiersze macierzy
	bool robtrapezowa(int);
	void wpis();	//metody I/O
	void wypisz();
};
class macierzkwadratowa: public macierz {
public:
	macierzkwadratowa();	//potrzebne konstruktory:bezarg, arg i kopiuj�cy
	macierzkwadratowa(const liczba<int>&);
	macierzkwadratowa(const macierzkwadratowa&);
	~macierzkwadratowa(); //destruktor
	macierzkwadratowa zrobL();	//wykonanie z macierzy odpowiednich jej cz�ci
	macierzkwadratowa zrobD();
	macierzkwadratowa zrobU(); 
	macierzkwadratowa zrobLU();
	bool odwrocD();	//odwracanie macierzy diagonalnej z informacj� czy si� uda�o
	bool dominacja(wektor&); // sprawdzanie dominacji przek�tniowej dla alg iteracyjnych
	bool Jackobi(const wektor&, wektor&);//metody dla okre�lonych algorytm�w obliczenia
	bool GaussSeidel(const wektor&, wektor &);
	bool metGauss(const wektor&, wektor &);
};
class wektor: public macierz {
public:
	wektor();	//potrzebne konstruktory:bezarg, arg i kopiuj�cy
	wektor(const liczba<int>&);
	wektor(const macierz &);
	~wektor(); // destruktor
};
#endif