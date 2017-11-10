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
	friend ostream& operator<<(ostream &os,
		Box     &b);
	friend bool operator<(const Box &l,
		const Box &r);
	double&         operator[](int n);
	double operator[](int n) const;
	double volume() const;
	friend bool inside(Box const& b, Box const& outer);
	void init();
	void next();
	void prev();
	~Box();
};