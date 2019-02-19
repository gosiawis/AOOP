#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <list>
#include <queue>
#include <set>
#include <string>


using namespace std;

template <typename T>
struct compare_words {
	bool operator() (const T& x, const T& y) const {
		return x > y;
	}
	typedef T first_argument_type;
	typedef T second_argument_type;
	typedef bool result_type;
};

template<>
struct compare_words <string> {
	bool operator() (const string& x, const string& y) const {
		return x.length() > y.length();
	}
};

using String_queue = priority_queue<string, vector<string>, compare_words<string> >;
using String_set = set<string>;

template <typename T>
struct compare {
	bool operator() (const T& x, const T& y) const {
		return x > y;
	}
	typedef T first_argument_type;
	typedef T second_argument_type;
	typedef bool result_type;
};

template<>
struct compare <String_queue> {
	bool operator() (const String_queue& x, const String_queue& y) const
	{
		return x.size() < y.size();
	}
};

template<>
struct compare <String_set> {
	bool operator() (const String_set& x, const String_set& y) const
	{
		return x.size() > y.size();
	}
};

class Mikser : public list<String_queue>
{
public:
	Mikser() {};
	Mikser(const char* filename) { open(filename); };
	~Mikser();
	void open(const char* filename);
	void execute();
	void write(const char* filename);
};

Mikser::~Mikser(){
	for (iterator i = this->begin(); i != this->end(); i++)
	{
		while (!i->empty())
			i->pop();
	}
}

void Mikser::open(const char* filename){
	
	ifstream in (filename);

	string line;
	while (!in.eof())
	{
		getline(in, line);
		if (line.empty())
			continue;
		String_queue new_queue;

		istringstream stringstream(line);
		do
		{
			string word;
			stringstream >> word;
	
			if (word.length() == 0)
				continue;
	
			new_queue.push(word);
		
		} while (stringstream);

		this->push_back(new_queue);
	}
	
	in.close();
}

void Mikser::execute(){
	this->sort(compare<String_queue>());
}

ostream& operator<< (ostream& os, String_queue& queue)
{
	os << queue.size() << ": ";
	while (!queue.empty())
	{
		os << queue.top() << " ";
		queue.pop();
	}
	os << endl;
	return os;
}

void Mikser::write(const char* filename) {
	ofstream out(filename);
	for (iterator i = this->begin(); i != this->end(); i++)
		out << *i << endl;
}



class Mikser2 : public list<String_set>
{
public:
	Mikser2() {};
	Mikser2(const char* filename) { open(filename); };
	~Mikser2();
	void open(const char* filename);
	void execute();
	void write(const char* filename);
};

Mikser2::~Mikser2(){
	this->clear();
}

void Mikser2::open(const char* filename){

	ifstream in(filename);

	string line;
	while (!in.eof())
	{
		getline(in, line);
		if (line.empty())
			continue;
		String_set new_set;

		istringstream stringstream(line);
		do
		{
			string word;
			stringstream >> word;

			if (word.length() == 0)
				continue;

			new_set.insert(word);

		} while (stringstream);

		this->push_back(new_set);
	}

	in.close();
}

void Mikser2::execute(){
	this->sort(compare<String_set>());
}

void Mikser2::write(const char* filename) {
	ofstream out(filename);
	for (iterator i = this->begin(); i != this->end(); i++)
	{
		String_set set = *i;
		for (String_set::iterator is = set.begin(); is !=set.end(); is++)
		{
			out << *is << " ";
		}
		out << endl;
	}
}

ostream& operator<<(ostream& out, String_set& set)
{
	out << set.size() << ": ";
	while (!set.empty())
	{
		for (String_set::iterator i = set.begin(); i != set.end(); i++)
			out << *i << " ";
		set.clear();
	}
	out << endl;
	return out;
}

template <class T>
class domieszka_write : public T {
public:
	domieszka_write() : T() {};
	void write(const char* filename) {
		ofstream out(filename);
		list<String_set> pom = *this;
		for (list<String_set>::iterator i = pom.begin(); i != pom.end(); ++i)
		{
			out << *i << endl;
		}
	}
};


int main()
{
	Mikser miks;
	miks.open("mistrz.txt");
	miks.execute();

	ofstream os;
	os.open("output.txt");
	miks.write("output.txt");
	os.close();

	Mikser2 miks2;
	miks2.open("quovadis.txt");
	miks2.execute();

	ofstream out;
	out.open("output2.txt");
	miks2.write("output2.txt");
	out.close();

	domieszka_write<Mikser2> miks3;
	miks3.open("quovadis.txt");
	miks3.execute();

	ofstream outt;
	outt.open("output3.txt");
	miks3.write("output3.txt");
	outt.close();
}




