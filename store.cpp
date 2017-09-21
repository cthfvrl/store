#include "store.h"

Store::Box::Box() {}

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

bool operator<(const Store::Box &l, const Store::Box &r) {
	return l.num < r.num;
}

double& Store::Box::operator[](int n) {
	return len[n];
}

double Store::Box::operator[](int n) const {
	return len[n];
}

void Store::Box::init() {
	sort(len, len + N);
}

void Store::Box::next() {
	next_permutation(len, len + N);
}

void Store::Box::prev() {
	prev_permutation(len, len + N);
}

Store::Box::~Box() {}

bool Store::check() {
	// To be written
	return true;
}

void Store::init() {
	for (int i = 0; i < N; ++i) boxes[i].init();
	std::sort(boxes.begin(), boxes.end());
}

void Store::next() {
	Diff d = gray.next();

	if (d.next) boxes[d.pos].next();
	else boxes[d.pos].prev();
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
	while (is >> tmp) {
		tmp.num = s.n;
		s.boxes.push_back(tmp),
		++s.n;
	}
	return is;
}

bool Store::fits() {
	init();
	for (; gray.size() < n; next()) {
		do {
			if (check()) return true;
		} while (next_permutation(boxes.begin(), boxes.end()));
	}
	return false;
}

Store::~Store() {}
