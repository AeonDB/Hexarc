#include "stdafx.h"

CSpaceTokenizer::~CSpaceTokenizer() {}
CTermOccurenceStream CSpaceTokenizer::Operation(CString &sData) { return CTermOccurenceStream(); }
ITokenizer* CSpaceTokenizer::Clone(void)
	{
	return new CSpaceTokenizer();
	}