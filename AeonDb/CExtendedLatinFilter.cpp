//	CExtendedLatinFilter.cpp
//
//	CExtendedLatinFilter class
//
//	A concrete implementation of IPostprocess. This postprocessing technique changes
//	Unicode characters in the range of U+00C0 to U+00FF to their ASCII character
//	equivalents. These characters are known as extended ASCII. In an 8-bit byte,
//	ASCII takes the first 0-127 and these characters form 128-255. These are also
//	known as Latin-1 Supplement. This conversion allows easier indexing and searching.
//	This does not change other Latin characters from U+0100 onwards.
//
//	http://unicode.org/charts/PDF/U0000.pdf
//	http://unicode.org/charts/PDF/U0080.pdf
//
//	The following conversions are made (numbers are in hexidecimal Unicode):
//
//	ASCII	EXTENDED RANGE
//	0041	00C0-00C6
//	TODO ASCII conversion table

#include "stdafx.h"

CExtendedLatinFilter::CExtendedLatinFilter (void)

//	CExtendedLatinFilter constructor

	{

	//	Intentionally blank.

	}

CExtendedLatinFilter::CExtendedLatinFilter (const CExtendedLatinFilter &Other)

//	CExtendedLatinFilter copy constructor

	{

	//	Intentionally blank.

	}

CExtendedLatinFilter::~CExtendedLatinFilter (void)

//	CExtendedLatinFilter destructor

	{

	//	Intentionally blank.

	}

CExtendedLatinFilter &CExtendedLatinFilter::operator= (const CExtendedLatinFilter &Other)

//	CExtendedLatinFilter copy assignment operator

	{
	return *this;
	}

IPostprocess *CExtendedLatinFilter::Clone (void)

//	Clone
//
//	Polymorphic method to decouple abstraction from implementation.

	{
	return new CExtendedLatinFilter();
	}

void CExtendedLatinFilter::Operation (CTermOccurenceStream &Data)

//	Operation
//
//	Decorator method for postprocessing text. This converts Latin-1 Supplement characters to ASCII equivalents.

	{

	//	Iterate through each character in the string.
	//	TODO

	}
