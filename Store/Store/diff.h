#pragma once

struct Diff {
	int  pos;
	bool next;

	Diff(int  p = 0,
	     bool n = true);
	~Diff();
};
