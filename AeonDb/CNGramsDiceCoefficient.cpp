#include "stdafx.h"

CNGramsDiceCoefficient::CNGramsDiceCoefficient (void) { }
CNGramsDiceCoefficient::CNGramsDiceCoefficient (const CNGramsDiceCoefficient &Other) { }
CNGramsDiceCoefficient::~CNGramsDiceCoefficient (void) { }

CNGramsDiceCoefficient &CNGramsDiceCoefficient::operator= (const CNGramsDiceCoefficient &Other) { return *this; }

double CNGramsDiceCoefficient::Compare(const CString &sA, const CString &sB) { return 0.0; }

IStringSimilarity* CNGramsDiceCoefficient::Clone(void)
	{
	return new CNGramsDiceCoefficient();
	}