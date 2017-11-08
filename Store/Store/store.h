#pragma once
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <iostream>
#include "gray.h"
#include "box.h"
#include "grid.h"

using namespace std;

class Store {
protected:
	static const int N = 3;

	int n;
	Box space;
	vector<Box> boxes;

	bool check();
	void init();
	bool next(Gray<6> &gray);
	bool volumeCheck();
	bool lenghtCheck();
	
public:

	Store();
	void read(const string &filename);
	friend istream& operator>>(istream &is,
		Store   &s);
	string fits();
	~Store();
};
