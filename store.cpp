#include "store.h"

Store::Box::Box() {}

Store::Box::Box(vector<double> x) {
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

void Store::place2D(map<int, map<int, int> > &z, const Store::Box &b, double curX, double curY) {
	// Intersecting levels, including the botttom one
	for (auto y = z.find(curY); y != z.end() && y->first < curY + b[1]; ++y) {
		auto x = y->second.upper_bound(curX);
		--x;
		// The fuck is this??
		if ((curX < x->first) || (curX + b[0] > x->second)) throw PredicateViolation();

		// Space left to the right
		if (curX + b[0] < x->second) y->second[curX + b[0]] = x->second;

		// Space left to the left
		if (curX != x->first) x->second = curX;

		// No space left to the left
		else y->second.erase(x);
	}

	// Init top level if needed
	// Process!!!!!!!!!!!
	//  --
	// |  | --  <- new y
	// |  ||  |
	//  --  --
	if ((curY + b[1] < space[1]) && !z.count(curY + b[1])) z[curY + b[1]][0] = space[0];
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
							// Remember current x, y and z
							double curX = x->first, curY = y->first, curZ = z->first;

							// Intersecting planes, including the bottom one
							for (; z != grid.end() && z->first < curZ + b[2]; ++z)
								try {
									place2D(z->second, b, curX, curY);
								}
								catch (PredicateViolation) {
									cerr << "Predicate violation.\n";
									throw 1;
								}

							// Init top plane if needed
							if ((curZ + b[2] < space[2]) && !grid.count(curZ + b[2])) grid[curZ + b[2]][0][0] = space[0];

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
