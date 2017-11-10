#include "store.h"

bool Store::check() {
	Grid grid(space);
	vector<Box> coordinates(n);
	for (int i = 0; i < n; ++i) {
		if (!grid.place(boxes[i], coordinates[i])) return false;
	}

	print(coordinates);

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

bool Store::volumeCheck() {
	double spaceVolume = space.volume();

	double sum = 0;
	for (auto b : boxes)
		sum += b.volume();

	return ((sum <= spaceVolume) ? true : false);
}

bool Store::lenghtCheck() {
	for (auto b : boxes)
		if (!inside(b, space))
			return false;
	return true;
}

void Store::print(vector<Box> &coordinates) {
	cout << "Store lenghts: " << space << '\n';

	for (int i = 0; i < n; ++i) {
		cout << "Box lenghts: " << boxes[i];
		cout << "\tCoordinates: " << coordinates[i];
		cout << '\n';
	}
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
	if (boxes.empty()) return "The store is empty";

	if (!volumeCheck()) return false;

	init();
	Gray<6> gray;

	// Rotational examintaion
	do {
		if (lenghtCheck()) {
			// Permutational examintaion
			do {
				if (check()) return true;
			} while (next_permutation(boxes.begin(), boxes.end()));
		}
	} while (next(gray));
	return false;
}

int Store::size() const {
	return n;
}

Store::~Store() {}
