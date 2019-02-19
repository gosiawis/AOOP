#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <list>
#include <queue>
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


template <typename T>
struct compare_queues {
	bool operator() (const T& x, const T& y) const {
		return x > y;
	}
	typedef T first_argument_type;
	typedef T second_argument_type;
	typedef bool result_type;
};

template<>
struct compare_queues <String_queue> {
	bool operator() (const String_queue& x, const String_queue& y) const
	{
		return x.size() < y.size();
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
	this->sort(compare_queues<String_queue>());
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

int main()
{
	Mikser miks;
	miks.open("mistrz.txt");
	miks.execute();

	ofstream os;
	os.open("output.txt");
	miks.write("output.txt");
	os.close();
}




