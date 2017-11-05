#include "grid.h"

Grid::Grid(Box const& space) {
	double x = space[0], y = space[1], z = space[2];
	grid[0][0][0] = true;
	grid[x][0][0] = false;
	grid[0][y][0] = false;
	grid[x][y][0] = false;
	grid[0][0][z] = false;
	grid[x][0][z] = false;
	grid[0][y][z] = false;
	grid[x][y][z] = false;
}

bool Grid::place(Box const& b) {
	for (auto& z : grid)
		for (auto& y : z.second)
			for (auto& x : y.second)
				if (place(b, x.first, y.first, z.first))
					return true;
	return false;
}

Grid::~Grid() {}

bool Grid::place(Box const& b, double xStart, double yStart, double zStart) {
	const double xEdge = grid[0][0].rbegin()->first;
	const double yEdge = grid[0].rbegin()->first;
	const double zEdge = grid.rbegin()->first;

	double xNew = xStart + b[0];
	double yNew = yStart + b[1];
	double zNew = zStart + b[2];

	for (auto& z : grid)
		if (z.first >= zStart && z.first < zNew)
			for (auto& y : z.second)
				if (y.first >= yStart && y.first < yNew)
					for (auto& x : y.second)
						if (x.first >= xStart && x.first < xNew)
							// Cube which partly (or entirely) lies inside 
							// the box is already occupied
							if (x.second == false)
								return false;

	// All intersecting cubes are empty
	// Make new vertices if needed
	// Check edge vertices
	if (grid[0][0].find(xNew) == grid[0][0].end())
		for (auto& z : grid)
			for (auto& y : z.second) {
				if (y.first == yEdge || z.first == zEdge) {
					y.second[xNew] = false;
					continue;
				}
				auto tmp = y.second[0];
				for (auto& x : y.second) {
					if (x.first < xNew) tmp = x.second;
					else break;
				}
				y.second[xNew] = tmp;
			}
	if (grid[0].find(yNew) == grid[0].end())
		for (auto& z : grid) {
			auto *tmp = &z.second[0];
			for (auto& y : z.second) {
				if (y.first < yNew) tmp = &y.second;
				else break;
			}
			z.second[yNew] = *tmp;
		}
	if (grid.find(zNew) == grid.end()) {
		auto *tmp = &grid[0];
		for (auto& z : grid) {
			if (z.first < zNew) tmp = &z.second;
			else break;
		}
		grid[zNew] = *tmp;
	}

	// Mark cubes occupied by new box
	for (auto& z : grid)
		if (z.first >= zStart && z.first < zNew)
			for (auto& y : z.second)
				if (y.first >= yStart && y.first < yNew)
					for (auto& x : y.second)
						if (x.first >= xStart && x.first < xNew)
							x.second = false;

	return true;
}
