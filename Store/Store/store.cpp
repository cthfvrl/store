#include "store.h"

bool Store::check() {
	Grid grid(space);
	for (auto b : boxes)
		if (!grid.place(b)) return false;

	return true;
}

void Store::init() {
	for (int i = 0; i < n; ++i) boxes[i].init();
	std::sort(boxes.begin(), boxes.end());
}

bool Store::next(Gray<6> &gray) {
	Diff d = gray.next();

	if (d.pos >= n) return false;

	if (d.next) boxes[d.pos].next();
	else boxes[d.pos].prev();
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
	s.space.num = -1;
	Box tmp;
	while (is >> tmp) {
		tmp.num = s.n;
		s.boxes.push_back(tmp),
		++s.n;
	}
	return is;
}

bool Store::fits() {
	init();
	Gray<6> gray;

	// Rotational examintaion
	do {
		// Permutational examintaion
		do {
			if (check()) return true;
		} while (next_permutation(boxes.begin(), boxes.end()));
	} while (next(gray));
	return false;
}

Store::~Store() {}
