#ifndef STORE_H
#define STORE_H
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include "gray.h"

using namespace std;

class Store {
	static const int N = 3;
	struct Box {
		int    num;
		double len[N];

		Box();
		Box(vector<double>x);
		friend istream& operator>>(istream &is,
		                           Box     &b);
		friend bool     operator<(const Box &l,
		                          const Box &r);
		double&         operator[](int n);
		double          operator[](int n) const;
		void init();
		void next();
		void prev();
		~Box();
	};

	friend istream& operator>>(istream &is,
	                           Box     &b);
	friend bool     operator<(const Box &l,
	                          const Box &r);

	int n;
	Box space;
	vector<Box> boxes;
	Gray<6> gray;

	bool check();
	void init();
	void next();

public:

	Store();
	void            read(const string &filename);
	friend istream& operator>>(istream &is,
	                           Store   &s);
	bool            fits();
	~Store();
};

#endif // ifndef STORE_H
