#include "store.h"

Store::Box::Box(vector<double>x) {
	for (int i = 0; i < N; ++i) len[i] = x[i];
}

istream& operator>>(istream &is, Store::Box &b) {
	double tmp;

	for (int i = 0; i < Store::N; ++i) {
		is >> tmp;
		b.len[i] = tmp;
	}
	return is;
}

bool Store::check() {
	for (int dim = 0; dim < N; ++dim) {}
	return true;
}

Store::Store()
	: n(0)
{}

void Store::read(const string &filename) {
	ifstream fin(filename);

	fin >> *this;
}

istream& operator>>(istream &is, Store &s) {
	is >> s.st;
	Store::Box tmp;
	while (is >> tmp) s.boxes.push_back(tmp), ++s.n;
	return is;
}

bool Store::fits() {
	return check();
}
