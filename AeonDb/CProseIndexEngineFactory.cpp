#include "stdafx.h"

CIndexEngine CProseIndexEngineFactory::Create(void)
	{
	CPreprocessor *pPreprocessor;
	ITokenizer *pTokenizer;
	CPostprocessor *pPostprocessor;
	IIndexStorage *pIndexStorage;
	IFuzzyMapStorage *pFuzzyStorage;
	return CIndexEngine(pPreprocessor, pTokenizer, pPostprocessor, pIndexStorage, pFuzzyStorage);
	}