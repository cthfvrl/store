#ifndef DIFF_H
#define DIFF_H

struct Diff {
	int  pos;
	bool next;

	Diff(int  p = 0,
	     bool n = true);
	~Diff();
};

#endif // ifndef DIFF_H
