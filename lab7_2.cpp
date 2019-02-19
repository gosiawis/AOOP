#include "stdafx.h"
#include <iostream>
#include <algorithm>
#include <numeric>
#include <vector>
#include <random>
#include <functional>
#include <iterator> 
#include <cmath>

using namespace std;

class generatorLiczb {
	static default_random_engine rng;
	normal_distribution<double> dist;
public:
	generatorLiczb(double mi = 0.0, double sigma = 1.0) :dist(mi, sigma) {};
	double operator ()(){ return dist(rng); }
};

default_random_engine generatorLiczb::rng;

class generatorVectora {
private:
	int size;
public:
	generatorVectora(int n) :size(n) {};
	vector<double> operator()()
	{
		vector<double> punkt(size);
		generatorLiczb gen(5.0, 10.0);
		generate(punkt.begin(), punkt.end(), gen); //zape³nianie wektorów punktów (wspolrzedne)
		return punkt;
	}
};

class addVectors { //funktor do dodawanie wektorów do siebie - zwraca sumê pierwszegop z pierwszym, drug z drug itd...
private:
	vector<double>& centroid;
public:
	addVectors(vector<double> &centr) : centroid(centr) {};
	vector<double> operator()(vector<double> &centroid, const vector<double> &element) const {
		transform(element.begin(), element.end(), centroid.begin(), centroid.begin(), plus<double>());
		return centroid;
	}
};

class divideValue {
private:
	double divider;
public:
	divideValue(const double& value) :divider(value) {};
	void operator() (double& elem) const
	{
		elem /= divider;
	}
};

double multiplie2(double n)
{
	return n *2;
}

class minusVectors {
private:
	vector<double> centroid;
public:
	minusVectors(vector<double> &centr) :centroid(centr) {};
	vector<double> operator()(vector<double> &element, vector<double> &centroid) const {
		transform(centroid.begin(), centroid.end(), element.begin(), element.begin(), minus<double>());
		return element;
	}
};

double diffPower2(double ele1, double ele2)
{
	return pow((ele1 - ele2) , 2.0);
}

class eukli {
private:
	vector<double> centroid;
public:
	eukli(vector<double> &centr) :centroid(centr){};
	double operator() (const vector<double> &wektor)
	{
		double odleglosc = inner_product(wektor.begin(), wektor.end(), centroid.begin(), 0.0, plus<double>(), diffPower2);
		return odleglosc;
	}
};
class mniejsze{
private:
	double maks;
public:
	mniejsze(double m = 0) :maks(m){};
	bool operator()(double& val){
		return val < maks;
	}
};

class wieksze{
private:
	double maks;
public:
	wieksze(double m = 0) :maks(m){};
	bool operator()(double& val){
		return val > maks;
	}
};

int main()
{
	cout << "Ile przestrzeni?       ";
	int n;
	cin >> n;

	vector<vector<double>> A(100); //chmura A - 100 pkt w n wym przestrzeni
	generatorVectora vec(n); //obiekt funkcyjny
	generate(A.begin(), A.end(), vec); //zape³nianie chmury

	//obliczanie centroidu
	vector<double> centroidA(n); //wektor ze wsp centroidu chmury A
	centroidA.assign(n, 0.0);
	addVectors adv(centroidA);
	centroidA=accumulate(A.begin(), A.end(), centroidA, adv); //powinien dodawaæ po kolei wektory do centroidu
	for_each(centroidA.begin(), centroidA.end(), divideValue(100.0));

	cout << "Centroid A: ";
	copy(centroidA.begin(), centroidA.end(), ostream_iterator<double>(cout, " "));
	cout << endl;

	//symetria srodkowa w chmurze A'=B
	vector<vector<double>> B(100);
	vector<double> centroid2(n);
	transform(centroidA.begin(), centroidA.end(), centroid2.begin(), multiplie2);
	
	cout << "Centroid 2: ";
	copy(centroid2.begin(), centroid2.end(), ostream_iterator<double>(cout, " "));
	cout << endl;

	minusVectors mvec(centroid2);
	transform(A.begin(), A.end(), B.begin(), B.begin(), mvec);

	vector<double> centroidB(n);
	centroidB.assign(n, 0.0);
	addVectors advb(centroidB);
	centroidB=accumulate(B.begin(), B.end(), centroidB, advb);
	for_each(centroidB.begin(), centroidB.end(), divideValue(100.0));

	cout << "Centroid B: ";
	copy(centroidB.begin(), centroidB.end(), ostream_iterator<double>(cout, " "));
	cout << endl;

	//						2 poziom

	vector<double> odleglosc(100); //wektor odl euklidesowych (punktów od centroidu)

	eukli odl(centroidA);
	transform(A.begin(), A.end(), odleglosc.begin(), odl);

	cout << "odleglosc: ";
	copy(odleglosc.begin(), odleglosc.end(), ostream_iterator<double>(cout, " "));
	cout << endl;

	stable_sort(odleglosc.begin(), odleglosc.end());
	double odl_maks=odleglosc[0] /2.0;

	cout << endl;
	cout << odl_maks;
	cout << endl;

	mniejsze m(odl_maks);
	wieksze w(odl_maks);

	int mniej = count_if(odleglosc.begin(), odleglosc.end(), m);
	int wiecej = count_if(odleglosc.begin(), odleglosc.end(), w);

	cout << mniej << " " << wiecej << endl;

	vector<double> odlegloscB(100); //wektor odl euklidesowych (punktów od centroidu)

	eukli odlB(centroidB);
	transform(B.begin(), B.end(), odlegloscB.begin(), odlB);

	cout << "odleglosc: ";
	copy(odlegloscB.begin(), odlegloscB.end(), ostream_iterator<double>(cout, " "));
	cout << endl;

	stable_sort(odlegloscB.begin(), odlegloscB.end());
	double odl_maks_B = odlegloscB[0] / 2.0;

	cout << endl;
	cout << odl_maks_B;
	cout << endl;

	mniejsze mB(odl_maks_B);
	wieksze wB(odl_maks_B);

	int mniejB = count_if(odlegloscB.begin(), odlegloscB.end(), mB);
	int wiecejB = count_if(odlegloscB.begin(), odlegloscB.end(), wB);

	cout << mniejB << " " << wiecejB << endl;
	return 0;
}

