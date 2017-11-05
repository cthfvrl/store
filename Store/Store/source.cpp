#include "store.h"
#include <iostream>
#include <fstream>

int main() {
	ios_base::sync_with_stdio(0);
	cout.tie(0);
	cin.tie(0);

	Store store;

	store.read("input.txt");

	ofstream fout("out.txt");
	fout << store.fits() << '\n';

	return 0;
}
