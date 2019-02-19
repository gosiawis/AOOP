#include "stdafx.h"
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <stack>

using namespace std;

void checkMath(ifstream &math);

int main()
{
	ifstream math;
	math.open("math.txt");

	if (!math.is_open())
	{
		cout << "Otwarcie pliku siê nie powiodlo." << endl;
		EXIT_FAILURE;
	}

	checkMath(math);

	math.close();
	return 0;
}

void checkMath(ifstream &math)
{
	string str; //tutaj bêdzie zapisana linia pobrana z pliku
	stringstream str_stream; //tutaj bêdzie przpisywany fragment str a¿ do odnalezienia odpowiedniego znaku/wyra¿enia
	string pom; //tutaj bêd¹ zapisywane fragmenty stringstream

	int nr_wiersza = 0;

	try
	{
		getline(math, str);
		str_stream << str;
		str_stream >> pom;

		if (pom == "<math") //sprawdzenie czy math jest poprawnie zamkniety
		{
			//getline(math, str);
			while (!math.eof())
			{
				pom = str.substr(0, 7);
				if (pom == "</math>")
					break;
				else if (pom != "</math>")
				{
					getline(math, str);
					nr_wiersza++;
					string pom1;
					string pom2;

					pom1 = str.substr(0, 4);
					pom2 = str.substr(5, 5);
					if (pom1 != "<mo>" && pom1 != "<mi>" && pom1 != "<mn>" && pom2 != "</mo>" && pom2 != "</mi>" && pom2 != "</mn>")
						throw string("BLAD - NIEDOMKNIETY TAG.");
					
				}
				getline(math, str);
				nr_wiersza++;
			}
		}

		stack <string> stos; //deklaracja stosu na którym bêd¹ zapisywane ele od <math do <\math>

		math.seekg(0, math.beg);

		nr_wiersza = 0;
		getline(math, str);
		nr_wiersza = stos.size() + 1;
		pom = str.substr(0, 6);

		if (pom != "<math ")
		{
			cout << pom << endl;
			throw string("BLAD - PIERWSZA LINIA NIEPOPRAWNA.");
		}
		else //plik poprawnie rozpoczety
		{
			getline(math, str);
			stos.push(str);
			nr_wiersza = stos.size();

			while (stos.top() != "</math>")
			{
				pom = str.substr(0, 4);

				if (pom == "<mo>")
				{
					pom = str.substr(5, 5);
					if (pom != "</mo>")
						throw string("BLAD - NIEDOMKNIETY TAG <mo>");
					else
						stos.pop();
				}
				else if (pom == "<mi>")
				{
					pom = str.substr(5, 5);
					if (pom != "</mi>")
						throw string("BLAD - NIEDOMKNIETY TAG <mi>");
					else
						stos.pop();
				}
				else if (pom == "<mn>")
				{
					pom = str.substr(5, 5);
					if (pom != "</mn>")
						throw string("BLAD - NIEDOMKNIETY TAG <mn>");
					else
						stos.pop();
				}
				else
					throw string("BLAD - NIEPOPRAWNA SK£ADNIA.");

				getline(math, str);
				stos.push(str);
				nr_wiersza++;

			}
			if (stos.top() == "</math>")
			{
				while (!stos.empty())
					stos.pop();
			}
		}

	}

	catch (string& blad)
	{
		cout << blad << endl;
		cout << "NR LINII : " << nr_wiersza << endl;
	}


}

