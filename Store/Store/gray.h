#pragma once
#include <vector>
#include "diff.h"

using namespace std;

template<int N>
class Gray {
	vector<int> g;
	vector<int> asc;
	int n;
	int pos;
	int cnt;

public:

	Gray();
	int  operator[](int n) const;
	int  size() const;
	Diff next();
	~Gray();
};

template<int N>
Gray<N>::Gray()
	: g(vector<int>(1, 0))
	, asc(vector<int>(1, 1))
	, n(1)
	, pos(0)
	, cnt(0)
{}

template<int N>
int Gray<N>::operator[](int n) const {
	return g[n];
}

template<int N>
int Gray<N>::size() const {
	return n;
}

template<int N>
Diff Gray<N>::next() {
	if ((++cnt) % N) {
		g[0] += asc[0];
		return Diff(0, asc[0] == 1);
	}
	cnt %= N;
	int p;
	for (p = 0; p < n && (g[p] + asc[p] < 0 || g[p] + asc[p] == N); ++p) {
		asc[p] *= -1;
	}
	if (p == n) {
		g.push_back(1);
		asc.push_back(1);
		++n;
		return Diff(p, true);
	}
	g[p] += asc[p];
	return Diff(p, asc[p] == 1);

	// To be finished
}

template<int N>
Gray<N>::~Gray() {}

