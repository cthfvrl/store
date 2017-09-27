#include "store.h"

Store::Box::Box() {}

Store::Box::Box(vector<double>x) {
	for (int i = 0; i < N; ++i) len[i] = x[i];
}

istream& operator>>(istream &is, Store::Box &b) {
	for (int i = 0; i < Store::N; ++i) is >> b.len[i];
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
	map<int, map<int, map<int, int> > > grid;
	grid[0][0][0] = space[0];
	for (auto b : boxes)
		if (!place(grid, b)) return false;

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

bool Store::place(map<int, map<int, map<int, int> > > &grid, const Store::Box &b) {
	for (map<int, map<int, map<int, int> > >::iterator z = grid.begin(),
	     prevZ = grid.end();
	     z != grid.end();
	     prevZ = z++)
		if (space[2] - z->first >= b[2]) {
			for (map<int, map<int, int> >::iterator y = z->second.begin(),
			     prevY = z->second.end();
			     y != z->second.end();
			     prevY = y++)
				if (space[1] - y->first >= b[1]) {
					for (map<int, int>::iterator x = y->second.begin(),
					     prevX = y->second.end();
					     x != y->second.end();
					     prevX = x++)
						if (x->second - x->first >= b[0]) {
							if (x->second - x->first == b[0]) y->second.erase(x);  // Not enough
							else x->second -= b[0];

							return true;
						}
						else if (prevX != y->second.end()) y->second.erase(prevX);
				}
				else if (prevY != z->second.end()) z->second.erase(prevY);
		}
		else if (prevZ != grid.end()) grid.erase(prevZ);

	return false;
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
	Gray<6> gray;
	do {
		do {
			if (check()) return true;
		} while (next_permutation(boxes.begin(), boxes.end()));
	} while (next(gray));
	return false;
}

Store::~Store() {}
