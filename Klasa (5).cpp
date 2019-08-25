#include "Klasa.h"
//#include <cstring>
#include <iostream>	//potrzebne ze wzgl. na cout i cin
//w metodach potrzebuj¹cych macierzy (lub potomnych) jako argumentu przekazujemy jako referencja (oszcz. pamiêci) z const (brak mo¿liwoœci zmiany)
//w niektórych przekazana bez const celowo, ze wzglêdu na umieszczenie wyniku w macierzy lub zamianê jej wierszy
//staramy siê operowaæ na obiektach typu liczba, czysta wartoœæ wyci¹gana w przypadku pêtli i operatorów indeksowania (int)
//lub w przypadku operacji arytmetycznych na liczbach (problem z utworzeniem operatorów we wzorcu)
macierz::macierz()	//konstruktor bezargumentowy macierzy
{
	pole = nullptr;	//wystarczy tylko oznaczyæ wskaŸnik jako pusty, bo obiekty liczba skonstruuj¹ siê bezargumentowo z zerami
}
macierz::macierz(const liczba<int>& lw, const liczba<int>& lk):lwierszy(lw), lkolumn(lk)
{//konstruktor 2-arg. macierzy który tworzy w oparciu o dwa obiekty liczba<int>
	pole = new liczba<double>* [lwierszy.wartosc];	//alokacja pola 2-wym. liczb (konstrukcja bezargumentowa liczb - wartosc 0)
	for (int i = 0; i < lwierszy.wartosc; i++)
		pole[i] = new liczba<double>[lkolumn.wartosc];
}
macierz::macierz(const macierz &p):lwierszy(p.lwierszy), lkolumn(p.lkolumn) 
{ //konstruktor kopiuj¹cy macierz
	pole = new liczba<double>*[lwierszy.wartosc];	//alokacja pola 2-wym. liczb (konstrukcja bezargumentowa liczb - wartosc 0)
	for (int i = 0; i < lwierszy.wartosc; i++)
		pole[i] = new liczba<double>[lkolumn.wartosc];
	for (int i = 0; i < lwierszy.wartosc; i++)	//przepisanie wartosci liczb w macierzy
		for (int j = 0; j < lkolumn.wartosc; j++)
			pole[i][j] = p[i][j];
}
macierz::~macierz()
{ //destruktor macierzy
	for (int i = 0; i < lwierszy.wartosc; i++)	//dealokacja ka¿dego wiersza
		delete[] pole[i];
	delete[] pole;	//dealokacja pola
}
macierzkwadratowa::macierzkwadratowa() :macierz() {}	//pusta macierz jest tez macierza kwadratowa, dlatego wykorzystujemy jej konstruktor bezargum.
macierzkwadratowa::macierzkwadratowa(const liczba<int>& wymiar) : macierz(wymiar, wymiar) {}	//macierz kwadratowa jest macierz¹ gdzie lwierszy rowna jest lkolumn, wiec wykorzystujemyonstruktor 2-arg.
macierzkwadratowa::macierzkwadratowa(const macierzkwadratowa & pk) : macierz(pk) {}	//kopiowanie zawsze przebiega tak samo wiêc musimy jedynie dobrze okreœliæ argument konstruktora
macierzkwadratowa::~macierzkwadratowa() {} //i tak zostanie wywo³any destruktor macierzy, który zdealokuje pole a liczby równie¿ siê zdealokuj¹
macierzkwadratowa macierzkwadratowa::zrobL() // wykonanie macierzy L z macierzy kwadratowej (dolnotrójk¹tna bez elem na przek¹tnej)
{
	macierzkwadratowa L(lwierszy);
	for (int i = 0; i < lwierszy.wartosc; i++)
		for (int j = 0; j < lkolumn.wartosc; j++)
			if (i > j)
				L[i][j] = (*this)[i][j];	//przepisanie wartoœci spod przek¹tnej do macierzy wynikowej
	return L;
}
macierzkwadratowa macierzkwadratowa::zrobD()	//wykonanie macierzy diagonalnej
{
	macierzkwadratowa D(lwierszy);
	for (int i = 0; i < lwierszy.wartosc; i++)
		D[i][i] = (*this)[i][i];   //przepisanie wartoœci z przek¹tnej do macierzy wynikowej
	return D;
}
macierzkwadratowa macierzkwadratowa::zrobU() // wykonanie macierzy L z macierzy kwadratowej (górnotrójk¹tna bez elem na przek¹tnej)
{
	macierzkwadratowa U(lwierszy);
	for (int i = 0; i < lwierszy.wartosc; i++)
		for (int j = 0; j < lkolumn.wartosc; j++)
			if (i < j)
				U[i][j] = (*this)[i][j];  //przepisanie wartoœci powyzej przek¹tnej do macierzy wynikowej
	return U;
}
macierzkwadratowa macierzkwadratowa::zrobLU() // wykonanie macierzy LU (suma L i U - macierz z 0 na g³ównej przek¹tnej)
{
	macierzkwadratowa LU(lwierszy);
	for (int i = 0; i < lwierszy.wartosc; i++)
		for (int j = 0; j < lkolumn.wartosc; j++)
			if (i != j)
				LU[i][j] = (*this)[i][j]; //przepisanie wartoœci za wyj¹tkiem przek¹tnej do macierzy wynikowej
	return LU;
}
bool macierz::dodajdomnie(const macierz &d)	//dodaje do macierzy dla ktorej wywo³ano macierz d, zwraca czy siê uda³o
{	//metoda dodaj¹ca
	if (lwierszy != d.lwierszy || lkolumn != d.lkolumn)	//dodajemy tylko gdy ten sam wymiar
		return false;
	for (int i = 0; i < lwierszy.wartosc; i++)
		for (int j = 0; j < lkolumn.wartosc; j++)
			(*this)[i][j].wartosc += d[i][j].wartosc; //dodanie do odpowiednich elementów wartoœci elementów odpowiadaj¹cych macierzy przekazanej
	return true;
}
void macierz::wpis() //wpisywanie wartoœci do liczb typu double
{
	for (int i = 0; i < lwierszy.wartosc; i++)
		for (int j = 0; j < lkolumn.wartosc; j++)
		{//wymaga _CRT_SECURE_NO_WARNINGS w def preprocesora
			char c[100] = { '\0' }; //wyczyszczenie tablic znaków
			char l1[32] = { '\0' };
			char l2[32] = { '\0' };
			strcat(c, "Nr wiersza : "); //konkatenacja stringów z liczbami przerobionymi na ciagi znakow
			_itoa(i + 1, l1, 10);
			strcat(c, l1); 
			strcat(c, " Nr kolumny : ");
			_itoa(j + 1, l2, 10);
			strcat(c, l2);
			strcat(c, "\nPodaj wartosc: ");
			pole[i][j].wpis(c);	//wpis wartoœci z odp komunikatem
		}
}
void macierz::mnozskalar(double a) //mno¿enie macierzy przez skalar typu double
{
	for (int i = 0; i < lwierszy.wartosc; i++)
		for (int j = 0; j < lkolumn.wartosc; j++)
			(*this)[i][j].wartosc *= a;	//przemno¿enie ka¿dego elementu macierzy
}
bool macierz::mnozprawo(const macierz &mn) //metoda domna¿aj¹ca do macierzy z prawej jej strony, zwraca info czy uda³o siê czy nie
{	//metoda w celu wykorzystania tej samej macierzy do przechowania wyniku i lepszej przerzystoœci dzia³ania (mno¿enie elementów w odp sposob)- optymalizacja
	if (lkolumn != mn.lwierszy)
		return false; //sprawdzenie czy mnozenie wykonalne
	liczba<double>** tmp = pole;	//przechowanie wartoœci macierzy lewej
	pole = new liczba<double>*[lwierszy.wartosc];
	for (int i = 0; i < lwierszy.wartosc; i++)
		pole[i] = new liczba<double>[mn.lkolumn.wartosc];	//ponowna alokacja miejsca w macierzy lewej
	for (int i = 0; i < lwierszy.wartosc; i++)
		for (int j = 0; j < mn.lkolumn.wartosc; j++)
			for (int k = 0; k < lkolumn.wartosc; k++)
				pole[i][j].wartosc += tmp[i][k].wartosc * mn[k][j].wartosc;	//operacja mno¿enia
	for (int i = 0; i < lwierszy.wartosc; i++)	//dealokacja poprzednich wartoœci macierzy
		delete[] tmp[i];
	delete[] tmp;
	lkolumn = mn.lkolumn;	//aktualizacja informacji o macierzy
	return true;
}
bool macierz::domnozzlewej(const macierz &mn)	//metoda domna¿aj¹ca do macierzy z lewej jej strony, zwraca info czy uda³o siê czy nie
{	//metoda w celu wykorzystania tej samej macierzy do przechowania wyniku, zwrotu inf o powodzeniu operacji i lepszej przerzystoœci dzia³ania (mno¿enie elementów w odp sposob)- optymalizacja
	if (lwierszy != mn.lkolumn)
		return false; //sprawdzenie czy mnozenie wykonalne
	liczba<double>** tmp = pole;	//przechowanie wartoœci macierzy prawej
	pole = new liczba<double>*[mn.lwierszy.wartosc];
	for (int i = 0; i < mn.lwierszy.wartosc; i++)
		pole[i] = new liczba<double>[lkolumn.wartosc];	//alokacja nowego obszaru pamiêci dla wyniku w macierzy prawej
	for (int i = 0; i < mn.lwierszy.wartosc; i++)
		for (int j = 0; j < lkolumn.wartosc; j++)
			for (int k = 0; k < mn.lkolumn.wartosc; k++)
				pole[i][j].wartosc += mn[i][k].wartosc * tmp[k][j].wartosc; //operacja mno¿enia i sumowania odp. wartoœci
	for (int i = 0; i < lwierszy.wartosc; i++)	//usuniêcie poprzednich wartoœci macierzy prawej
		delete[] tmp[i];
	delete[] tmp;
	lwierszy = mn.lwierszy;	//aktualizacja informacji o macierzy
	return true;
}
bool macierz::zamianawierszy(wektor &be) //metoda zamieniaj¹ca wiersze macierzy (cel: uzyskanie utworzenia macierzy diagonalnej odwracalnej)
{//zwraca info o powodzeniu, przekazanie przez referencjê bez const ze wzglêdu na zamianê informacji rowniez w macierzy wyrazów wolnych
	for (int i = 0; i < lwierszy.wartosc; i++)
		if ((*this)[i][i].wartosc == 0)	//jeœli na przek¹tenej wystepuje zero
		{
			for (int j = i + 1; j < lwierszy.wartosc; j++)
				if ((*this)[j][i].wartosc != 0)
				{
					for (int k = 0; k < lkolumn.wartosc; k++)
						(*this)[i][k].zamien((*this)[j][k]);
					be[i][0].zamien(be[j][0]);	//znajdz w wierszach ponizej i zamieñ elementy wiersza
					break;
				}
			if ((*this)[i][i].wartosc == 0)	//jesli nie udalo sie zamienic
				for (int j = 0; j < i; j++)	//szukaj w wierszach od pocz¹tku az do aktualnego wiersza
					if ((*this)[j][i].wartosc != 0)
					{
						for (int k = 0; k < lkolumn.wartosc; k++)
							(*this)[i][k].zamien((*this)[j][k]);
						be[i][0].zamien(be[j][0]);	//i zamieñ elementy wiersza
						break;
					}
			if ((*this)[i][i].wartosc == 0)	//jezeli i tak siê nie uda³o, to nie da siê wykonaæ
			{
				std::cout << "Blad. Nie mozna wykonac." << std::endl;
				return false;
			}
		}
	return true;
}
bool macierz::robtrapezowa(int it)	//uzyskanie pojedynczych wierszy to postaci trapezowej
{
	for (int j = it + 1; j < lwierszy.wartosc; j++) //przeszukaj nastêpne wiersze w celu znalezienia kandydata do zamiany
		if ((*this)[j][it].wartosc != 0)	//je¿eli istnieje zale¿noœæ z dan¹ zmienn¹
		{
			for (int k = 0; k < lkolumn.wartosc; k++)
				(*this)[it][k].zamien((*this)[j][k]);	//zamiana wszystkich liczb wierszy
			break;
		}
	if ((*this)[it][it].wartosc == 0)	//jezeli nie uda³o siê zamieniæ, zwróæ b³¹d
	{
		std::cout << "Blad. Nie mozna wykonac." << std::endl;
		return false;
	}
	return true;
}
liczba<double>* macierz::operator[](int i) //operator indeksacji macierzy
{
	return pole[i];	//zwraca wiersz(wskaŸnik na elementy typu liczba) z którego mo¿emy otrzymaæ pojedyncze liczby
}
const liczba<double>* macierz::operator[](int i) const //operator indeksacji dla elementów typu const (przy przekazanych referencjach do obiektów funkcji)
{
	return pole[i]; //zwraca wiersz(wskaŸnik na elementy typu liczba) z którego mo¿emy odczytywaæ liczby
}
macierz & macierz::operator=(const macierz &p) //operator przypisania macierzy musi zwracaæ referencjê do elementu dla którego wykonano
{
	if (this == &p)
		return *this; //sprawdzenie warunku a=a
	for (int i = 0; i < lwierszy.wartosc; i++)
		delete[] pole[i];
	delete[] pole;	//usuniêcie poprzednich wartoœci macierzy
	lwierszy = p.lwierszy;	//uaktualnienie informacji o macierzy
	lkolumn = p.lkolumn;
	pole = new liczba<double>*[lwierszy.wartosc];
	for (int i = 0; i < lwierszy.wartosc; i++)
		pole[i] = new liczba<double>[lkolumn.wartosc];	//realokacja pola (nowy wymiar)
	for (int i = 0; i < lwierszy.wartosc; i++)
		for (int j = 0; j < lkolumn.wartosc; j++)
			pole[i][j] = p[i][j];	//przepisanie wartoœci
	return *this;
}
void macierz::wypisz() //metoda wypisuj¹ca macierz wierszami i kolumnami
{
	for (int i = 0; i < lwierszy.wartosc; i++)
	{
		for (int j = 0; j < lkolumn.wartosc; j++)
			std::cout << pole[i][j] << " ";		//wypis wartoœci
		std::cout << std::endl;
	}
}
bool macierzkwadratowa::odwrocD() //metoda odwracaj¹ca macierz diagonaln¹, zwraca info o powodzeniu operacji
{
	for (int i = 0; i < lwierszy.wartosc; i++)
		if (!pole[i][i].odwrotnosc())	//sprawdza czy da siê odwróciæ liczby na g³ównej przek¹tnej
			return false;
	return true;
}
bool macierzkwadratowa::dominacja(wektor& be) //metoda do ustalania czy macierz jest przek¹tniowo dominuj¹ca (doprowadza do dobrego ustawienia gdy tak)
{	//zwraca info czy tak jest, zgodnie z definicj¹ sprawdzamy dominacjê siln¹ dla wierszy
	double p = 0;	//pomocnicza do dodawania wartoœci pozosta³ych w wierszu
	double* tabpom = new double[lkolumn.wartosc];	//pomocnicza tablica do ustalania dominacji
	int* tabdom = new int[lwierszy.wartosc];	//pomocnicza tablica do sprawdzania dla jakiej kolumny dominacja
	for (int i = 0; i < lwierszy.wartosc; i++)	//ustalenie pocz¹tkowe na wartoœæ niemo¿liw¹ wiersza
		tabdom[i] = -1;
	for (int i = 0; i < lwierszy.wartosc; i++)	//dla wszystkich wierszy
	{
		for (int j = 0; j < lkolumn.wartosc; j++)	//dla kazdej wartosci w wierszu
		{
			p = 0;
			for (int k = 0; k < lkolumn.wartosc; k++)
			{
				if (j == k)
					continue;
				p += abs((*this)[i][k].wartosc);	//ustal sume modu³ów pozosta³ych elementów
			}
			tabpom[j] = p;	//wpisz wartoœci do pomocniczej tablicy
		}
		for (int j = 0; j < lkolumn.wartosc; j++)
			if (tabpom[j] < (*this)[i][i].wartosc)	//ustal gdzie zachodzi dominacja
			{
				tabdom[i] = j;	//mo¿e zajœæ tylko dla jednego lub zadnego elementu
				break;
			}
	}
	for (int j = 0; j < lwierszy.wartosc; j++)
		if (tabdom[j] == -1)	//jezeli sa wiersze gdzie nie ma dominacji to znaczy ze nie ma dominacji w macierzy
			return false;
	for (int j = 0; j < lwierszy.wartosc; j++)	//jezeli wszêdzie dominacje
		if (tabdom[j] != j)
		{
			for (int k = 0; k < lkolumn.wartosc; k++)
				(*this)[tabdom[j]][k].zamien((*this)[j][k]);
			be[tabdom[j]][0].zamien(be[j][0]);	//wykonaj odpowiednie zamiany elementów, ³¹cznie z wyrazami wolnymi
		}
	return true;
}
bool macierzkwadratowa::Jackobi(const wektor & b, wektor & wynikowa) // metoda obliczaj¹ca wynik iteracyjn¹ metod¹ Jackobiego
{ //przyjmuje wektor wyrazów wolnych i macierz w której wpisany bêdzie wynik (przekazany przez referencjê bez const ze wzglêdu na utworzenie go z zerami w programie g³ównym i edycjê w metodzie)
	liczba<int> li; //odczyt rz¹danej liczby iteracji
	do {
		li.wpis("Podaj liczbe iteracji (calkowita wieksza od 0): ");
	} while (li.niedodatnia());
	macierzkwadratowa tmp = *this;	//przepisanie wartoœci obu podanych macierzy do pomocniczych - mog¹ byæ potrzebne póŸniej w programie
	wektor tmpb = b;
	if (!tmp.dominacja(tmpb))	//jezeli nie jest dominujaca to wysw komunikat - wynik nie musi byc dobry
		std::cout << "Uwaga! Macierz kwadratowa nie jest przekatniowo dominujaca." << std::endl;
	if (!tmp.zamianawierszy(tmpb))
		return false;	//Czy uda³o siê utworzyæ postaci obu macierzy pozwalaj¹ce na odwracanie diagonalnej?
	macierzkwadratowa LU = tmp.zrobLU();	//wykonanie macierzy LU (L+U) i D z tymczasowej (z ewentualnie zamienionymi wierszami)
	macierzkwadratowa D = tmp.zrobD();
	if (!D.odwrocD())
		return false;	//Jeœli nie uda³o siê odwróciæ diagonalnej nie da siê wykonaæ, generalnie powinno byæ za³atwione przez zamiane wierszy
	if (!LU.domnozzlewej(D))	//domna¿amy do macierzy ju¿ istniej¹cych w celu oszczêdzenia miejsca, kazde mnozenie maciezy sprawdzamy pod k¹tem wykonywalnoœci
		return false;// macierz D^(-1)*(L+U)
	LU.mnozskalar(-1); //macierz -D^(-1)*(L+U)
	if (!D.mnozprawo(tmpb))
		return false; // macierz D^(-1)*b
	for (int i = 0; i < li.wartosc; i++) //wykonujemy rz¹dan¹ liczbê iteracji
	{
		wynikowa.domnozzlewej(LU);	//wynikowa(n+1)=-D^(-1)*(L+U)*wynikowa+D^(-1)*b
		wynikowa.dodajdomnie(D);
	}
	return true;
}
bool macierzkwadratowa::GaussSeidel(const wektor & b, wektor & wynikowa) // metoda obliczaj¹ca wynik iteracyjn¹ metod¹ Gaussa-Seidela
{ //przyjmuje wektor wyrazów wolnych i macierz w której wpisany bêdzie wynik (przekazany przez referencjê bez const ze wzglêdu na utworzenie go z zerami w programie g³ównym i edycjê w metodzie)
	liczba<int> li; //odczyt rz¹danej liczby iteracji
	do {
		li.wpis("Podaj liczbe iteracji (calkowita wieksza od 0): ");
	} while (li.niedodatnia());
	macierzkwadratowa tmp = *this;	//przepisanie wartoœci obu podanych macierzy do pomocniczych - mog¹ byæ potrzebne póŸniej w programie
	wektor tmpb = b;
	if (!tmp.dominacja(tmpb))	//jezeli nie jest dominujaca to wysw komunikat - wynik nie musi byc dobry
		std::cout << "Uwaga! Macierz kwadratowa nie jest przekatniowo dominujaca." << std::endl;
	if (!tmp.zamianawierszy(tmpb)) //zamiana wierszy w celu uzyskania macierzy diagonalnej odwracalnej
		return false;
	macierzkwadratowa L = tmp.zrobL(); //wykonanie macierzy L, D i U
	macierzkwadratowa D = tmp.zrobD();
	macierzkwadratowa U = tmp.zrobU();
	if (!D.odwrocD())	//Jeœli nie uda³o siê odwróciæ diagonalnej nie da siê wykonaæ, generalnie powinno byæ za³atwione przez zamiane wierszy
		return false;
	if (!tmpb.domnozzlewej(D))	//operacje mnozenia z kontrola poprawnosci
		return false;		//D^(-1)*b
	if (!L.domnozzlewej(D))	//D^(-1)*L
		return false;
	if (!U.domnozzlewej(D)) //D^(-1)*U
		return false;
	for (int i = 0; i < li.wartosc; i++)	//powtorzenie okreslona ilosc iteracji
		for (int j = 0; j < lwierszy.wartosc; j++) //wynikowa(n+1) = D^(-1)*b -D^(-1)*L*wynikowa(n+1) -  D^(-1)*U*wynikowa(n)
		{
			wynikowa[j][0] = tmpb[j][0]; //poczatkowe przyblizenie to odpowiadajacy wyraz wolny
			for (int k = 0; k < j; k++) //jezeli zmienna ma nizszy indeks niz aktualna to bierzemy z aktualnej iteracji, jeœli nie to z poprzedniej
				wynikowa[j][0].wartosc -= L[j][k].wartosc * wynikowa[k][0].wartosc; //nizsze indekszy
			for (int k = j + 1; k < lwierszy.wartosc; k++)
				wynikowa[j][0].wartosc -= U[j][k].wartosc * wynikowa[k][0].wartosc; //wyzsze indeksy
		}
	return true;
}
bool macierzkwadratowa::metGauss(const wektor & b, wektor & wyn) // metoda obliczaj¹ca wynik ogóln¹ metod¹ Gaussa
{//przyjmuje wektor wyrazów wolnych i macierz w której wpisany bêdzie wynik (przekazany przez referencjê bez const ze wzglêdu na utworzenie go z zerami w programie g³ównym i edycjê w metodzie)
	system("cls"); //odœwiezenie ekranu
	macierz wynikowa(lwierszy, lkolumn + 1); //utworzenie wynikowej macierzy [A|b]
	for (int i = 0; i < lwierszy.wartosc; i++)
	{
		for (int j = 0; j < lkolumn.wartosc; j++)
			wynikowa[i][j] = (*this)[i][j];
		wynikowa[i][(*this).lkolumn.wartosc] = b[i][0];	//przepisanie wartoœci A i b
	}
	double pom;	//zmienna pomocnicza do okreœlania wartoœci ju¿ okreœlonych zmiennych
	for (int i = 0; i < (*this).lkolumn.wartosc - 1; i++)	//sprawdzenie wierszy w celu utworzenia postaci trapezowej
	{
		if (wynikowa[i][i].wartosc == 0)
		{
			if (!wynikowa.robtrapezowa(i))	//zamiana wiersza gdy wspó³czynnik równy 0
				return false;
		}
		for (int j = i + 1; j < lwierszy.wartosc; j++)	//odjêcie wierszy przemno¿onych przez odpowiedni¹ sta³¹
		{
			pom = wynikowa[j][i].wartosc / wynikowa[i][i].wartosc;
			for (int k = 0; k < (*this).lkolumn.wartosc + 1; k++)
				wynikowa[j][k].wartosc -= wynikowa[i][k].wartosc * pom;
		}
	}
	pom = 0; //wykorzystanie ponowne do obliczeñ wartoœci dla zmiennych wczeœniejszych
	for (int i = lwierszy.wartosc - 1; i > -1; i--)
	{	//sprawdzenie czy na g³ównej przek¹tnej A nie ma 0
		if (wynikowa[i][i].wartosc == 0)
		{
			if (wynikowa[i][(*this).lkolumn.wartosc].wartosc - pom == 0)
				std::cout << "Uk³ad nieoznaczony." << std::endl; // przypadek 0 = 0
			else
				std::cout << "Uk³ad sprzeczny." << std::endl;	//sprzecznoœæ typu 0 = 3
			return false;
		}
		wyn[i][0].wartosc = (wynikowa[i][(*this).lkolumn.wartosc].wartosc - pom) / wynikowa[i][i].wartosc;	//ustalenie wartoœci wyniku
		pom = 0;
		if (i)
			for (int j = 1; j < lwierszy.wartosc - i + 1; j++)
				pom += wyn[lwierszy.wartosc - j][0].wartosc * wynikowa[i - 1][(*this).lkolumn.wartosc - j].wartosc;	//dodanie wsp. przemno¿onych przez wartoœci zmiennych
	}
	return true;
}
wektor::wektor() :macierz() {} //dla lkolumn i lwierszy = 0 macierz to równie¿ wektor, dlatego mo¿emy skorzystaæ z bezargumentowego konstruktora macierzy
wektor::wektor(const liczba<int>& wymiar):macierz()	//stworzymy macierz pust¹ a nastêpnie j¹ zmodyfikujemy
{
	lwierszy = wymiar;	//wektor ma tyle wierszy ile elementów
	++lkolumn;	//liczba kolumn to zawsze 1 co uzyskamy poprzez ++0
	pole = new liczba<double>*[lwierszy.wartosc];
	for (int i = 0; i < lwierszy.wartosc; i++)
		pole[i] = new liczba<double>[lkolumn.wartosc];	//alokacja pola i wpisanie liczb 0
}
wektor::wektor(const macierz &wk):macierz(wk){}	//kopiowanie zawsze przebiega tak samo wiêc musimy jedynie dobrze okreœliæ argument konstruktora
wektor::~wektor() {} //zostanie wywo³any konstruktoj klasy bazowej macierz który wykona potrzebne operacje