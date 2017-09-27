#include "diff.h"

Diff::Diff(int  p,
           bool n)
	: pos(p)
	, next(n)
{}

Diff::~Diff() {}
