#include "stdafx.h"

CToLowercase::~CToLowercase() {}
void CToLowercase::Operation(CString &sData) {}
IPreprocess* CToLowercase::Clone(void)
	{
	return new CToLowercase();
	}