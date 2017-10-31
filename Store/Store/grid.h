#pragma once
#include "box.h"
#include <map>

using namespace std;

class Grid {
	map<double, map<double, map<double, bool> > > grid;

public:
	Grid(Box const& b);
	bool place(Box const& b);
	~Grid();
};