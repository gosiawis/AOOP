#include "stdafx.h"
#include <iostream>
#include <vector>
#include <ctime>
#include <algorithm>
#include <cstdlib>

using namespace std;

void change_combination(vector<int>& vec, int first, int second, int third){
	for (vector<int>::iterator i = vec.begin(); i != vec.end()-2; i++)
	{
		if (*i == first&&*(i + 1) == second&&*(i + 2) == third){
			*i = third;
			*(i + 2) = first;
		}
	}
}

int count_combinations(vector<int>& vec, int tab[]){
	int count = 0;
	vector<int>::iterator i=vec.begin();
	i = search(i, vec.end(), tab, tab+3);
	while (i != vec.end()){
		count++;
		i = search(i, vec.end()-2, tab, tab + 3);
		i += 2;
	}
		
	return count;
}


int generator(void){
	int losowa = rand() % 6 + 1;
	return losowa;
}


int main()
{

	srand(time(NULL));
	int liczba_rzutow = 1000;
	vector<int> rzuty(liczba_rzutow);
	generate(rzuty.begin(), rzuty.end(), generator);

	for (vector<int>::iterator i = rzuty.begin(); i != rzuty.end(); i++)
	{
		cout << *i << " ";
	}

	int n = 1;
	int tab123[] = { 1, 2, 3 };
	int tab456[] = { 4, 5, 6 };
	int tab135[] = { 1, 3, 5 };
	int tab246[] = { 2, 4, 6 };

	cout << "Przed : " << endl;
	int count123 = 0, count456 = 0, count135 = 0, count246 = 0;
	count123 = count_combinations(rzuty, tab123);
	cout << "123 : " << count123 << endl;
	count456 = count_combinations(rzuty, tab456);
	cout << "456 : " << count456 << endl;
	count135 = count_combinations(rzuty, tab135);
	cout << "135 : " << count135 << endl;
	count246 = count_combinations(rzuty, tab246);
	cout << "246 : " << count246 << endl;

	change_combination(rzuty, 1, 2, 3);
	change_combination(rzuty, 4, 5, 6);
	change_combination(rzuty, 1, 3, 5);
	change_combination(rzuty, 2, 4, 6);

	cout << "Po : " << endl;
	count123 = 0, count456 = 0, count135 = 0, count246 = 0;
	count123 = count_combinations(rzuty, tab123);
	cout << "123 : " << count123 << endl;
	count456 = count_combinations(rzuty, tab456);
	cout << "456 : " << count456 << endl;
	count135 = count_combinations(rzuty, tab135);
	cout << "135 : " << count135 << endl;
	count246 = count_combinations(rzuty, tab246);
	cout << "246 : " << count246 << endl;

	return 0;
}

