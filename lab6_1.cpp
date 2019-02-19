#include "stdafx.h"
#include <iostream>
#include <algorithm>
#include <vector>
#include <ctime>
#include <cmath>
#include <numeric>

using namespace std;

template<class T>
class wartosc_oczekiwana {
private:
	T sum;
	T div;
public:
	wartosc_oczekiwana(const T& value) : sum(value), div(1.0) {};
	void operator() (T elem){
		sum += elem;
		div++;
	}
	T get_avg() { return sum / div; };
};

template<class T>
class roznica {
private:
	T wo;
public:
	roznica<T>(const T& value) : wo(value) {};
	T operator() (T elem){
		return wo - elem;
	}
};

double kwadrat(double elem) { return pow(elem, 2); };

int main()
{
	srand(time(NULL));

	vector<double> seria(10);
	fill(seria.begin(), seria.end(), (double)((rand() % 100))/10);

	wartosc_oczekiwana<double> WO(1);
	WO = for_each(seria.begin(), seria.end(), WO);

	cout << "Srednia : " << WO.get_avg() << endl;

	vector<double> roznice(seria.size());
	roznica<double> r(WO.get_avg());
	transform(seria.begin(), seria.end(), roznice.begin(), r);

	vector<double> kwadraty(roznice.size());
	transform(roznice.begin(), roznice.end(), kwadraty.begin(), kwadrat);

	double sum = accumulate(kwadraty.begin(), kwadraty.end(), 0.0);

	cout << "Wariancja : " << sum / (double)(seria.size()-1) << endl;

	return 0;
}

