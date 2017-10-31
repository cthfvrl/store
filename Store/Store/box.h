#pragma once
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Box {
	static const int N = 3;

	int num;
	double len[N];

	Box();
	Box(vector<double> x);
	friend istream& operator>>(istream &is,
		Box     &b);
	friend bool operator<(const Box &l,
		const Box &r);
	double&         operator[](int n);
	double operator[](int n) const;
	void init();
	void next();
	void prev();
	~Box();
};