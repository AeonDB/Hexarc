#include "stdafx.h"

CNGramsDiceCoefficient::~CNGramsDiceCoefficient(void) {}
double CNGramsDiceCoefficient::Compare(const CString &sA, const CString &sB) { return 0.0; }

IStringSimilarity* CNGramsDiceCoefficient::Clone(void)
	{
	return new CNGramsDiceCoefficient();
	}