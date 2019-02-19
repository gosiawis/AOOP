#include "stdafx.h"
#include <iostream>
#include <algorithm>
#include <numeric>
#include <vector>
#include <random>
#include <functional>
#include <iterator> 

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


	return 0;
}

