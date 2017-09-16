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

double& Store::Box::operator[](int n) {
	return len[n];
}

Store::Box::~Box() {}

bool Store::check() {
	for (int dim = 0; dim < N; ++dim) {
		double tmp = 0;
		for (int i = 0; i < n; ++i) tmp += boxes[i][dim];
		if (tmp > space[dim]) return false;
	}
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
	is >> s.space;
	Store::Box tmp;
	while (is >> tmp) s.boxes.push_back(tmp), ++s.n;
	return is;
}

bool Store::fits() {
	return check();
}

Store::~Store() {}
