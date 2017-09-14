#ifndef STORE
#define STORE
#include <fstream>
#include <string>
#include <vector>

using namespace std;

class Store {
	static const int N = 3;
	struct Box {
		double len[N];

		Box(vector<double>x = vector<double>(N, 0));
		friend istream& operator>>(istream &is,
		                           Box     &b);
	};

	friend istream& operator>>(istream &is,
	                           Box     &b);
	int n;
	Box st;
	vector<Box> boxes;

	bool check();

public:

	Store();
	void            read(const string &filename = "");
	friend istream& operator>>(istream &is,
	                           Store   &s);
	bool            fits();
};

#endif // ifndef STORE
