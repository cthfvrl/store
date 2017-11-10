#include "store.h"
#include <iostream>
#include <fstream>

int main() {
	ios_base::sync_with_stdio(0);
	cout.tie(0);
	cin.tie(0);

	Store store;

	store.read("input.txt");

	const string fit = (store.size() > 1) ? "Boxes fit into the store" : "Box fits into the store";
	const string dontfit = (store.size() > 1) ? "Boxes don't fit into the store" : "Box doesn't fit into the store";

	if (!store.fits())
		cout << dontfit << '\n';

	return 0;
}
