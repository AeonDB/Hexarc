#include "stdafx.h"

CPunctuationFilter::~CPunctuationFilter() {}
void CPunctuationFilter::Operation(CString &sData) {}
IPreprocess* CPunctuationFilter::Clone(void)
	{
	return new CPunctuationFilter();
	}