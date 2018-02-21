//	CToLowercase.cpp
//
//	CToLowercase class
//
//	A concrete implementation of IPostprocess. This postprocessing technique changes
//	all uppercase ASCII letters to their lowercase equivalents. This prevents the
//	index from being fragmented, but some words may lose their meaning such as in
//	"The Who" and programming languages lose their case sensitivity.

#include "stdafx.h"

CToLowercase::CToLowercase (void)

//	CToLowercase constructor

	{

	//	Intentionally blank.

	}

CToLowercase::CToLowercase (const CToLowercase &Other)

//	CToLowercase copy constructor

	{

	//	Intentionally blank.

	}

CToLowercase::~CToLowercase (void)

//	CToLowercase destructor

	{

	//	Intentionally blank.

	}

CToLowercase &CToLowercase::operator= (const CToLowercase &Other)

//	CToLowercase copy assignment operator

	{
	return *this;
	}

IPostprocess* CToLowercase::Clone (void)

//	Clone
//
//	Polymorphic method to decouple abstraction from implementation.

	{
	return new CToLowercase();
	}

void CToLowercase::Operation (CTermOccurenceStream &Data)

//	Operation
//
//	Decorator method for postprocessing text. This converts all uppercase ASCII letters into lowercase letters.

	{

	//	Iterate through CTermOccurenceStream
	//	Lowercase each term.

	}