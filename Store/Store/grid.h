#pragma once
#include "box.h"
#include <map>

using namespace std;

class Grid {
public:
	Grid(Box const& space);
	bool place(Box const& b);
	~Grid();

private:
	map<double, map<double, map<double, bool> > > grid;

	bool place(Box const&b, double xStart, double yStart, double zStart);
};