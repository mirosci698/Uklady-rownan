#ifndef Klasa_h
#define Klasa_h
#include "Liczba.h"
class macierz {
protected:	//musimy mieæ dostêp do zmiennych klasowych w klasach potomnych
	liczba<double> **pole;	//tablica 2 wymiarowa elementów
	liczba<int> lwierszy;	//informacje o macierzy
	liczba<int> lkolumn;
public:
	macierz();	//potrzebne konstruktory:bezarg, 2 arg i kopiuj¹cy
	macierz(const liczba<int>&, const liczba<int>&);
	macierz(const macierz &);
	~macierz();	//destruktor
	liczba<double>* operator[](int);	//operatory indeksacji dla zwyk³ych i const
	const liczba<double>* operator[](int) const;
	macierz& operator=(const macierz&);	//operator przypisania
	bool dodajdomnie(const macierz &); //metody: operacje matem (bool gdy mog¹ nie byæ wykonalne)
	void mnozskalar(double);
	bool mnozprawo(const macierz&);
	bool domnozzlewej(const macierz &);
	bool zamianawierszy(wektor&);	//metody zamieniaj¹ca wiersze macierzy
	bool robtrapezowa(int);
	void wpis();	//metody I/O
	void wypisz();
};
class macierzkwadratowa: public macierz {
public:
	macierzkwadratowa();	//potrzebne konstruktory:bezarg, arg i kopiuj¹cy
	macierzkwadratowa(const liczba<int>&);
	macierzkwadratowa(const macierzkwadratowa&);
	~macierzkwadratowa(); //destruktor
	macierzkwadratowa zrobL();	//wykonanie z macierzy odpowiednich jej czêœci
	macierzkwadratowa zrobD();
	macierzkwadratowa zrobU(); 
	macierzkwadratowa zrobLU();
	bool odwrocD();	//odwracanie macierzy diagonalnej z informacj¹ czy siê uda³o
	bool dominacja(wektor&); // sprawdzanie dominacji przek¹tniowej dla alg iteracyjnych
	bool Jackobi(const wektor&, wektor&);//metody dla okreœlonych algorytmów obliczenia
	bool GaussSeidel(const wektor&, wektor &);
	bool metGauss(const wektor&, wektor &);
};
class wektor: public macierz {
public:
	wektor();	//potrzebne konstruktory:bezarg, arg i kopiuj¹cy
	wektor(const liczba<int>&);
	wektor(const macierz &);
	~wektor(); // destruktor
};
#endif