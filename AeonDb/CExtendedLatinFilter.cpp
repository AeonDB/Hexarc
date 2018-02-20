#include "stdafx.h"

CExtendedLatinFilter::~CExtendedLatinFilter() {}
void CExtendedLatinFilter::Operation(CString &sData) {}
IPreprocess* CExtendedLatinFilter::Clone(void)
	{
	return new CExtendedLatinFilter();
	}