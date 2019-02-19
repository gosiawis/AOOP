// lab01_1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <cstdio>
#include "Wyklad13b.h"

using namespace std;

struct Dane {
	int id;
	char nazwa[10];
	double temp;
	double pojemn;
	Dane &operator +=(const Dane &x)
	{
		temp += x.temp;
		pojemn += x.pojemn;
		return *this;
	}
};

fstream &operator<<(fstream &a, const Dane &b)
{
	a << "|";
	a.width(6);
	a.fill('0');
	a << right << b.id << "|";
	a.fill(' ');
	a.width(10);
	a << left << b.nazwa << "|";
	a.width(7);
	a << right << b.temp << "|";
	a.width(6);
	int i = 10, j=1;
	while (b.pojemn > i)
	{
		i *= 10;
		j++;
	}
	a.precision(j);
	a.unsetf(ios::showpoint);
	a << right << b.pojemn << "|";
	return a;
}

void zapis_do_pliku(Tablica<Dane, 10> &Obiekt, char nazwa_pliku[40], int tryb_pliku);

int main()
{
	Tablica<Dane, 10> Obiekt;
	for (int i = 0; i < 10; i++)
	{
		Obiekt[i].id = i;
		strcpy(Obiekt[i].nazwa, "nazwa");
		Obiekt[i].temp = i + 2;
		Obiekt[i].pojemn = i * 20.54;
	}

	cout << "Podaj nazwe pliku: ";
	char nazwa[40];
	cin >> nazwa;

	zapis_do_pliku(Obiekt, nazwa, ios::out);

	return 0;
}

void zapis_do_pliku(Tablica<Dane, 10> &Obiekt, char nazwa_pliku[40], int tryb_pliku)
{
	if (tryb_pliku != 2)
	{
		cout << "Zly tryb otwarcia pliku" << endl;
		exit(EXIT_FAILURE);
	}

	fstream raport;
	strcat(nazwa_pliku, ".txt");
	raport.open(nazwa_pliku, tryb_pliku);
	
	if (!raport.is_open())
	{
		cout << "Otwarcie pliku sie nie powiodlo." << endl;
		exit(EXIT_FAILURE);
	}

	raport.width(35);

	time_t czas; //zmiennna typu time_t przechowuje czas
	time(&czas); //zwracana jest obecna data i czas i zapisywana w zmiennej typu time_t
	char* rezultat = ctime(&czas); //zwracany jest wskaŸnik do ci¹gu znaków reprezentuj¹cych czas (wczeœniej pobranych 
									//w funkcji time i zapisanych w zmiennej typu time_t)
	if (rezultat)   //sprawdzamy, czy wykonanie ctime odbylo sie poprawnie, je¿eli odby³oby siê nie poprawnie wykona³oby siê 0
		raport << right << rezultat; //zapisanie do raportu wartoœci zapisanej do rezultat przy pomocy ctime(&wskaznik)
	else
		cout << "Blad funkcji ctime()";

	raport << endl << left << getenv("COMPUTERNAME") << endl; //funkcja getenv pobiera string "systemowy"

	Dane help;
	help.id = 0;
	strcpy(help.nazwa, "");
	help.temp = 0;
	help.pojemn = 0;

	raport << "+------+----------+-------+------+" << endl;
	raport << "|  ID  | nazwa    | temp. |pojemn|" << endl;
	raport << "+------+----------+-------+------+" << endl;
	//wpisanie do raportu
	for (int i = 0; i < 10; i++)
	{
		raport << Obiekt[i] << endl;
		help += Obiekt[i];
	}
	raport << "+------+----------+-------+------+" << endl; 
	//suma raportu
	raport << help << endl;
	raport << "+------+----------+-------+------+" << endl;

	raport.close();
	
}