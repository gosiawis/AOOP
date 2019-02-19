#include "stdafx.h"
#include<iostream>
#include<fstream>
#include<string>
#include<limits>
#include<exception>
#include<iomanip>

using namespace std;

bool czy_jest_2_do_n(const double& i){
	double r = i;
	if (r < 1)
		return false; //wartość musi być większa od 1 ponieważ 2^0=1
	else if (r == 1)
		return true; //n=0
	else {
		r /= 2.0;
		return czy_jest_2_do_n(r); //sprawdzamy rekurencyjnie czy wszystkie dzielniki liczby to 2
	}
	return false;
}

class Bazowe_Cechy {
public:
	static const bool _jest_liczba = false;
	static const bool _nalezy_do_przedzialu = false;
	static const bool _jest_liczba_calkowita = false;
	static const int _dolna_granica_przedzialu = 0;
	static const int _gorna_granica_przedzialu = 0;

	static const int _precision = 0;
	static const bool _jest_polowkowa = false;
	static const bool _jest_2_do_n = false;
	static const bool _jest_jedno_miejsce_po_przecinku = false;
};

template<typename T>
class Cechy : public Bazowe_Cechy {
public:
	static const double dolna_granica_przedzialu() { return 0; };
	static const double gorna_granica_przedzialu() { return 0; };
};

class temperatura_wody {
	double t;
public:
	temperatura_wody(double temp = 50) : t(temp) {};
	double operator()() { return t; };
	temperatura_wody& operator=(double temp) { t = temp; return *this; };
};

template<>
class Cechy<temperatura_wody> : public Bazowe_Cechy{
public:
	static const bool _jest_liczba = true;
	static const bool _nalezy_do_przedzialu = true;
	static const double dolna_granica_przedzialu() { return 0; };
	static const double gorna_granica_przedzialu() { return 100; };
};

class kostka_do_gry {
	int n;
public:
	kostka_do_gry(int num = 1) : n(num) {};
	int operator()() { return n; };
	kostka_do_gry& operator=(int num) { n = num; return *this; };
};

template<>
class Cechy<kostka_do_gry> : public Bazowe_Cechy{
public:
	static const bool _jest_liczba = true;
	static const bool _nalezy_do_przedzialu = true;
	static const bool _jest_liczba_calkowita = true;
	static const int _dolna_granica_przedzialu = 1;
	static const int _gorna_granica_przedzialu = 6;
};

class srednica_opon {
	int s;
public:
	srednica_opon(int srednica = 10) :s(srednica) {};
	int operator()() { return s; };
	srednica_opon& operator=(int srednica) { s = srednica; return *this; };
	friend ostream& operator<<(ostream& value, const srednica_opon& srednica);
};

template<>
class Cechy<srednica_opon> : public Bazowe_Cechy{
public:
	static const bool _jest_liczba = true;
	static const bool _nalezy_do_przedzialu = true;
	static const bool _jest_liczba_calkowita = true;
	static const int _dolna_granica_przedzialu = 10;
	static const int _gorna_granica_przedzialu = 24;
	static const double dolna_granica_przedzialu() { return 10; };
	static const double gorna_granica_przedzialu() { return 24; };
};

ostream& operator<<(ostream& value, const srednica_opon& srednica){
	setprecision(Cechy<srednica_opon>::_precision);
	return value << srednica.s << endl;
}

class UKF {
	double u;
public:
	UKF(double ukf = 87.5) :u(ukf) {};
	double operator()() { return u; };
	UKF& operator=(double ukf) { u = ukf; return *this; };
	friend ostream& operator<<(ostream& value, const UKF& ukf);
};

template<>
class Cechy<UKF> : public Bazowe_Cechy{
public:
	static const bool _jest_liczba = true;
	static const bool _nalezy_do_przedzialu = true;
	static const double dolna_granica_przedzialu() { return 87.5; };
	static const double gorna_granica_przedzialu() { return 108.0; };

	static const int _precision = 1;
	static const bool _jest_jedno_miejsce_po_przecinku = true;
};

ostream& operator<<(ostream& value, const UKF& ukf){
	setprecision(Cechy<UKF>::_precision);
	return value << ukf.u << endl;
}

class rozmiar_buta {
	double b;
public:
	rozmiar_buta(double but = 1) : b(but) {};
	double operator()() { return b; };
	rozmiar_buta& operator=(double but) { b = but; return *this; };
	friend ostream& operator<<(ostream& value, const rozmiar_buta& but);
};

template<>
class Cechy<rozmiar_buta> : public Bazowe_Cechy{
public:
	static const bool _jest_liczba = true;
	static const bool _nalezy_do_przedzialu = true;
	static const int _dolna_granica_przedzialu = 1;
	static const int _gorna_granica_przedzialu = 70;
	static const double dolna_granica_przedzialu() { return 1; };
	static const double gorna_granica_przedzialu() { return 70; };

	static const int _precision = 1;
	static const bool _jest_polowkowa = true;
};

ostream& operator<<(ostream& value, const rozmiar_buta& but) {
	setprecision(Cechy<rozmiar_buta>::_precision);
	return value << but.b << endl;
}

class micro_sd {
	int m;
public:
	micro_sd(int micro = 2) :m(micro) {};
	int operator()() { return m; };
	micro_sd& operator=(int micro) { m = micro; return *this; };
	friend ostream& operator<<(ostream& value, const micro_sd& micro);
};

template<>
class Cechy<micro_sd> : public Bazowe_Cechy{
public:
	static const bool _jest_liczba = true;
	static const bool _nalezy_do_przedzialu = true;
	static const bool _jest_liczba_calkowita = true;
	static const int _dolna_granica_przedzialu = 2;
	static const int _gorna_granica_przedzialu = 128;
	static const double dolna_granica_przedzialu() { return 2; };
	static const double gorna_granica_przedzialu() { return 128; };

	static const bool _jest_2_do_n = true;
};

ostream& operator<<(ostream& value, const micro_sd& micro) {
	setprecision(Cechy<micro_sd>::_precision);
	return value << micro.m << endl;
}

class Przepelnienie : public exception {
	char opis[100];
public:
	Przepelnienie(const char* o) { strcpy_s(opis, o); }
	const char* what() const throw() { return opis; };
};
class BrakDanych : public exception {
	char opis[100];
public:
	BrakDanych(const char* o) { strcpy_s(opis, o); }
	const char* what() const throw() { return opis; };
};


template<typename T, int rozmiar, class _Cechy = Cechy<T>>
class SzablonStosu{
	T stos[rozmiar];
	int top;
public:
	int zajetosc() { return top; };
	SzablonStosu() : top(0) {}
	void push(const T& i) {
		if (top == rozmiar)
			throw Przepelnienie(typeid(i).name());
		stos[top++] = i;
	}
	void push(int i) {  //nalezy rozszerzyc o cechy dla calkowitych -
		if (top == rozmiar)
			throw Przepelnienie(typeid(i).name());

		// walidacja warto�ci przekazanej do zapisu
		if (Cechy<T>::_jest_liczba) {
			if (Cechy<T>::_jest_2_do_n && !czy_jest_2_do_n(i)) //sprawdzenie czy rozmiar karty sd jest 2^n
				return;
			if (Cechy<T>::_nalezy_do_przedzialu) {
				if ((Cechy<T>::_dolna_granica_przedzialu <= i) && (i <= Cechy<T>::_gorna_granica_przedzialu))
				{
					cout << i << endl;;
					stos[top++] = i;
				}
			}
			else
				stos[top++] = i;
		}
	}
	void push(double i) {
		if (top == rozmiar)
			throw Przepelnienie(typeid(i).name());

		// walidacja warto�ci przekazanej do zapisu
		if (Cechy<T>::_jest_liczba && !Cechy<T>::_jest_liczba_calkowita) {
			if (Cechy<T>::_jest_polowkowa && ((int)(i*10.0)) % 5 != 0)
				return;
			if (Cechy<T>::_jest_jedno_miejsce_po_przecinku && ((int)(i * 100.0)) % 10 != 0)
				return;
			if (Cechy<T>::_nalezy_do_przedzialu) {
				if ((Cechy<T>::dolna_granica_przedzialu() <= i) && (i <= Cechy<T>::gorna_granica_przedzialu()) || (abs(Cechy<T>::dolna_granica_przedzialu() - i)<0.001 || abs(Cechy<T>::gorna_granica_przedzialu() - i)<0.001))
				{
					cout << i << endl;;
					stos[top++] = i;
				}
			}
			else
				stos[top++] = i;
		}
	}
	T pop() {
		if (top == 0)
			throw BrakDanych(typeid(stos[0]).name());
		return stos[--top];
	}
};

class Stos2{
	static const int rozmiar = 10;
protected:
	double stos[rozmiar];
	int top;
public:
	int zajetosc() { return top; };
	Stos2() : top(0) {}
	virtual void push(const double& i) {
		if (top == rozmiar)
			throw Przepelnienie(typeid(i).name());
		stos[top++] = i;
	}
	virtual double pop() {
		if (top == 0)
			throw BrakDanych(typeid(stos[0]).name());
		return stos[--top];
	}
};

template<class T>
class pierwsza_domieszka : public T {
public:
	pierwsza_domieszka() : T() {};
	double pop() {
		cout << "Liczba elementow: " << top << endl; //wypisanie początkowej liczby
		return T::pop(); //wyświetlenie zdejmowanej
	}
};

template<class T>
class druga_domieszka : public T {
	double suma;
public: 
	druga_domieszka() : T() { suma = 0; };
	void push(const double& i) {
		T::push(i);
		suma+=i;
		cout << "suma = " << suma << endl;
	}
	double pop() {
		double val = T::pop();
		suma-=val;
		cout << "suma = " << suma << endl;
		return val;
	}
};

int main() {
	//SzablonStosu<string, 5> K1;
	//SzablonStosu<temperatura_wody, 10> K2;
	//SzablonStosu<kostka_do_gry, 10> K3;

	//// zape�nianie stosu
	//ifstream fi("qv-lab4.txt");
	//string s;
	//try{
	//	K1.push("Henryk");
	//	K1.push("Sienkiewicz");
	//	while (fi) {
	//		fi >> s;
	//		K1.push(s);
	//		fi.seekg(ios::beg);
	//		fi.clear();
	//		cout << '*';
	//	};
	//}
	//catch (Przepelnienie& e){
	//	cout << "K1 gotowy: " << e.what() << endl;
	//};
	//cout << "Danych na stosie K1: " << K1.zajetosc() << endl;

	//K2.push(temperatura_wody());
	//K2.push(temperatura_wody(36.6));
	//K2.push(40);
	//K2.push(71.2);
	//cout << "Danych na stosie K2: " << K2.zajetosc() << endl;

	//K3.push(kostka_do_gry(3));
	//K3.push(kostka_do_gry());
	//K3.push(4);
	//K3.push(6);
	//K3.push(10);
	//cout << "Danych na stosie K3: " << K3.zajetosc() << endl;

	SzablonStosu<srednica_opon, 6> K1;
	SzablonStosu<UKF, 6> K2;
	SzablonStosu<rozmiar_buta, 5> K3;
	SzablonStosu<micro_sd, 6> K4;

	try{
		K1.push(0);
		K1.push(2.5);
		K1.push(12);
		K1.push(28);
		K1.push(24);
		K1.push(29.5);
	}
	catch (Przepelnienie& e){
		cout << "K1 gotowy: " << K1.zajetosc() << endl;
	};
	cout << "Danych na stosie K1: " << K1.zajetosc() << endl;
	
	try{
		K2.push(-3);
		K2.push(21);
		K2.push(89.5);
		K2.push(109.5);
		K2.push(101.75);
		K2.push(110.45);
	}
	catch (Przepelnienie& e){
		cout << "K2 gotowy: " << K2.zajetosc() << endl;
	};
	cout << "Danych na stosie K2: " << K2.zajetosc() << endl;

	try{
		K3.push(21.25);
		K3.push(30);
		K3.push(-5);
		K3.push(41.5);
		K3.push(100);
	}
	catch (Przepelnienie& e){
		cout << "K3 gotowy: " << K3.zajetosc() << endl;
	};
	cout << "Danych na stosie K3: " << K3.zajetosc() << endl;

	try{
		K4.push(7);
		K4.push(2);
		K4.push(-2);
		K4.push(16);
		K4.push(140);
		K4.push(2.22);
	}
	catch (Przepelnienie& e){
		cout << "K4 gotowy: " << K4.zajetosc() << endl;
	};
	cout << "Danych na stosie K4: " << K4.zajetosc() << endl;

	// opr�nianie stosu
	try{
		while (true)
			K1.pop();
	}
	catch (BrakDanych& e) {
		cout << "K1 pusty: " << e.what() << endl;
	}
	try{
		while (true)
			K2.pop();
	}
	catch (BrakDanych& e) {
		cout << "K2 pusty: " << e.what() << endl;
	}
	try{
		while (true)
			K3.pop();
	}
	catch (BrakDanych& e) {
		cout << "K3 pusty: " << e.what() << endl;
	}
	try{
		while (true)
			K4.pop();
	}
	catch (BrakDanych& e) {
		cout << "K4 pusty: " << e.what() << endl;
	}

	druga_domieszka<pierwsza_domieszka<Stos2>> K5;

	K5.push(2.0);
	K5.push(0.1);
	K5.push(3.7);
	K5.push(0.2);

	cout << "Usuwane: " << K5.pop() << endl;
	cout << "Usuwane: " << K5.pop() << endl;
	cout << "Usuwane: " << K5.pop() << endl;
	cout << "Usuwane: " << K5.pop() << endl;

	system("pause");
	return 0;
}


