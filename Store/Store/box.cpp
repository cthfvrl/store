#include "box.h"

Box::Box() {}

Box::Box(vector<double> x) {
	for (int i = 0; i < N; ++i) len[i] = x[i];
}

istream& operator>>(istream &is, Box &b) {
	for (int i = 0; i < Box::N; ++i) is >> b.len[i];
	return is;
}

bool operator<(const Box &l, const Box &r) {
	return l.num < r.num;
}

double& Box::operator[](int n) {
	return len[n];
}

double Box::operator[](int n) const {
	return len[n];
}

void Box::init() {
	sort(len, len + N);
}

void Box::next() {
	next_permutation(len, len + N);
}

void Box::prev() {
	prev_permutation(len, len + N);
}

Box::~Box() {}
