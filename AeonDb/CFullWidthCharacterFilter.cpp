#include "stdafx.h"

CFullWidthCharacterFilter::~CFullWidthCharacterFilter(void) {}
void CFullWidthCharacterFilter::Operation(CString &sData) {}
IPreprocess* CFullWidthCharacterFilter::Clone(void)
	{
	return new CFullWidthCharacterFilter();
	}