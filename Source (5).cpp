#include "Klasa.h"
#include "Liczba.h"
#include <iostream>
#include <conio.h>	//_getch();
#include <Windows.h> //System("cls");
int main()
{
	std::cout << "Projekt PK3 - uklady rownan" << std::endl;	//informacje o programie
	std::cout << "Operujemy na macierzach kwadratowych (n x n) i macierzy wyrazow wolnych (n x 1)" << std::endl;
	std::cout << "Wcisnij dowolny klawisz";
	_getch();
	liczba<int> n;	//odpowiedni wczyt wymiaru macierzy
	do {
		n.wpis("Wpisz wymiar macierzy (calkowita wieksza od 0): ");
	} while (n.niedodatnia());
	macierzkwadratowa A(n);	//utworzebie macierzy wspolczynnikow i wyrazow wolnych
	A.wpis();
	wektor B(n);
	B.wpis();
	system("cls");
	std::cout << "Wybierz metode rozwiazywania: " << std::endl;	//wybór dzia³ania
	std::cout << "1 - metoda Jackobiego" << std::endl;
	std::cout << "2 - metoda Gaussa - Seidla" << std::endl;
	std::cout << "3 - metoda Gaussa (metoda nieiteracyjna)" << std::endl;
	char znak;
	do //odczyt wyboru dzia³ania
	{
		znak = _getch();
	} while (znak < 49 || znak > 51);
	wektor wynik(n);	//zmienna wynikowa przekazywana przez referencjê
	bool powodzenie;	//info o powodzeniu operacji
	switch (znak)
	{
		case '1':
			powodzenie = A.Jackobi(B, wynik);
			break;
		case '2':
			powodzenie = A.GaussSeidel(B, wynik);
			break;
		case '3':
			powodzenie = A.metGauss(B, wynik);
			break;
	}
	if (powodzenie)	//wypis wyniku lub info o b³edzie
	{
		std::cout << "Wynik:" << std::endl;
		wynik.wypisz();
	}
	else
		std::cout << "Blad wykonania" << std::endl;
	std::cout << "Wcisnij dowolny klawisz";	//info o zakoñczeniu
	_getch();
	return 0;
}