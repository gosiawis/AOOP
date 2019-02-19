#include "stdafx.h"
#include <iostream>
#include <cassert>
#include <cmath>
#include <ctime>

using namespace std;

#ifndef KONTEN_H
#define KONTEN_h

template<typename T>
class Konten
{
	enum { ssize = 100 };
	T stack[ssize];
	int top;
public:
	Konten() : top(0) {}
	void push(T i) {
		assert(top < ssize);  
		stack[top++] = i;
	};
	T pop() {
		assert(top > 0);  
		return stack[--top];
	};
	int rozmiar() { return top; };

	class iterator {
		Konten& s;
		int index;
	public:
		iterator(Konten& is) : s(is), index(0) {};
		iterator(Konten& is, bool) : s(is), index(s.top) {};

		T operator++() { // Prefix
			assert(index < s.top);
			return s.stack[++index];
		};

		T operator++(int) { // Postfix
			assert(index < s.top);
			return s.stack[index++];
		};

		T& operator*() const { return s.stack[index]; };

		iterator& operator=(const iterator& rv) {
			s = rv.s;
			index = rv.index;
			return *this;
		}

		bool operator!=(const iterator&rv) const
		{
			return index != rv.index;
		}
	};
	iterator begin() { return iterator(*this); };
	iterator end() { return iterator(*this, true); };

	friend class iterator;
};

double randdouble(){ return (rand() / (double(RAND_MAX) + 1))*10; }

//funkcja roznicuj

template<typename T>
void roznicuj(T &i1, T &i2, T &i3)
{
	while (i1 != i2) //sprawdzenie czy to nie koniec kontenera
	{
		*i1 = *i1 - *i3;
		i1++;
		i3++;
	}
};

//funkcja do kwadratu

template<typename T>
void kwadrat(T &i1, T &i2)
{
	while (i1 != i2)
	{
		*i1 = *i1*(*i1);
		i1++;
	}
}

//funkcja sumuj

template<typename T1, typename T2>
void sumuj(T1 &i1, T1 &i2, T2 &a) //a przekazane przez referencje a=0
{
	while (i1 != i2)
	{
		a += *i1;
		i1++;
	}
}

//funkcja wypisz

template<typename T>
void wypisz(T &i1, T &i2)
{
	while (i1 != i2)
	{
		cout << *i1 << endl;
		i1++;
	}
}

int main()
{

	Konten<double> p;
	Konten<double> q;

	const int size = 10;
	srand(time(NULL));

	for (int i = 0; i < size; i++)
		p.push(randdouble());
	wypisz<Konten<double>::iterator>(p.begin(), p.end());
	cout << endl;
	for (int i = 0; i < size; i++)
		q.push(randdouble());
	wypisz<Konten<double>::iterator>(q.begin(), q.end());
	cout << endl;

	roznicuj<Konten<double>::iterator>(p.begin(), p.end(), q.begin());
	wypisz<Konten<double>::iterator>(p.begin(), p.end());
	cout << endl;

	kwadrat<Konten<double>::iterator>(p.begin(), p.end());
	wypisz<Konten<double>::iterator>(p.begin(), p.end());
	cout << endl;
	
	double a = 0; //do zapisu wyniku dodawania
	sumuj<Konten<double>::iterator, double>(p.begin(), p.end(), a);

	a = sqrt(a);
	cout << "Wektor = " << a << endl;

	return 0;
}

#endif