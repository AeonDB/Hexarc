//	CNGramsDiceCoefficient.cpp
//
//	CNGramsDiceCoefficient class
//
//	n-grams are overlapping substrings of length n.
//	Bigrams and trigrams are the most common.
//
//	"statistics"
//	Unigrams:	s, t, a, t, i, s, t, i, c, s
//	Bigrams:	st, ta, at, ti, is, st, ti, ic, cs
//	Trigrams:	sta, tat, ati, tis, ist, sti, tic, ics
//
//	Dice's Coefficient is 
//	(2 * C) / (A + B)
//	where
//	C = number of shared unique n-grams
//	A = number of unique n-grams in one string
//	B = number of unique n-grams in the other string
//
//	"statistics"
//	st, ta, at, ti, is, st, ti, ic, cs
//	st, ta, at, ti, is,         ic, cs
//
//	"statistical"
//	st, ta, at, ti, is, st, ti, ic, ca, al
//	st, ta, at, ti, is,         ic, ca, al
//
//	Shared
//	st, ta, at, ti, is, ic
//
//	(2 * 6) / (7 + 8) = 0.8

#include "stdafx.h"

CNGramsDiceCoefficient::CNGramsDiceCoefficient (int iLength) : m_iLength(iLength)

//	CNGramsDiceCoefficient constructor

	{
	
	//	Intentionally blank.

	}

CNGramsDiceCoefficient::CNGramsDiceCoefficient (const CNGramsDiceCoefficient &Other) : m_iLength(Other.m_iLength)
	
//	CNGramsDiceCoefficient copy constructor

	{

	//	Intentionally blank.

	}

CNGramsDiceCoefficient::~CNGramsDiceCoefficient (void)

//	CNGramsDiceCoefficient destructor

	{

	//	Intentionally blank.

	}

CNGramsDiceCoefficient &CNGramsDiceCoefficient::operator= (const CNGramsDiceCoefficient &Other)
	
//	CNGramsDiceCoefficient copy assignment operator
	
	{
	m_iLength = Other.m_iLength;
	return *this;
	}

IStringSimilarity *CNGramsDiceCoefficient::Clone (void)

//	Clone
//
//	Helper function to decouple abstraction from implementation.

	{
	return new CNGramsDiceCoefficient(*this);
	}

double CNGramsDiceCoefficient::Compare (const CString &sA, const CString &sB)

//	Compare
//
//	Compares the similarity between 2 strings.
//	Outputs a number between 0 and 1.
//	A perfect match is 1.

	{
	TSortSet<CString> Ngrams1 = UniqueNgrams(sA, m_iLength);
	double rA = Ngrams1.Size();

	TSortSet<CString> Ngrams2 = UniqueNgrams(sB, m_iLength);
	double rB = Ngrams2.Size();

	Ngrams1.RetainAll(Ngrams2);
	double rC = Ngrams1.Size();

	return (2.0 * rC) / (rA + rB);
	}

TSortSet<CString> UniqueNgrams (const CString &sString, int iLength)

//	UniqueNgrams
//
//	Splits a string into n-grams.

	{

	//	If the length of the substring is longer than the string, return the string.

	TSortSet<CString> Set;
	if (sString.GetLength() <= iLength)
		{
		Set.Add(sString);
		return Set;
		}

	//	Calculate number of n-grams.

	int iCount = sString.GetLength() - iLength + 1;

	//	Create substrings of length n

	for (int i = 0; i <= iCount; i++)
		{
		Set.Add(strSubString(sString, i, iLength));
		}
	return Set;
	}