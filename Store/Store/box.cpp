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

bool inside(Box const& b, Box const& outer) {
	vector<double> v(Box::N);
	for (int i = 0; i < Box::N; ++i)
		v[i] = b[i];
	sort(v.begin(), v.end());

	do {
		bool fits = true;
		for (int i = 0; i < Box::N; ++i)
			if (v[i] > outer[i]) {
				fits = false;
				break;;
			}
		if (fits) return true;
	} while (next_permutation(v.begin(), v.end()));
	return false;
}

double& Box::operator[](int n) {
	return len[n];
}

double Box::operator[](int n) const {
	return len[n];
}

double Box::volume() const {
	double v = 1;
	for (int i = 0; i < N; ++i)
		v *= len[i];
	return v;
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
