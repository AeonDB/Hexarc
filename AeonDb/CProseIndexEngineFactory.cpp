//	CProseIndexEngineFactory.cpp
//
//	CProseIndexEngineFactory class
//
//	A concrete implementation of the decorator abstract factory IIndexEngineFactory.
//	This implementation combines various preprocessing techniques that are effective
//	for English literature as opposed to programming languages, mathematics,
//	records, etc.
//
//	Uses the following preprocessing classes:
//	* CToLowercase
//	* CExtendedLatinFilter
//	* CFullWidthCharacterFilter
//	* CPunctuationFilter
//	
//	Uses CSpaceTokenizer as the tokenizer.
//	Does not use any postprocessing classes.

#include "stdafx.h"

CIndexEngine CProseIndexEngineFactory::Create (void)

//	Create
//
//	Factory method for CIndexEngine.

	{

	//	Insert the preprocessing classes listed in the class description. Order matters.

	CPreprocessor *pPreprocessor = new CPreprocessor();
	pPreprocessor->Append(new CToLowercase());
	pPreprocessor->Append(new CExtendedLatinFilter());
	pPreprocessor->Append(new CFullWidthCharacterFilter());
	pPreprocessor->Append(new CPunctuationFilter());

	//	Tokenizer

	ITokenizer *pTokenizer = new CSpaceTokenizer();

	//	Empty postprocessor

	CPostprocessor *pPostprocessor = new CPostprocessor();

	//	Storage classes are interchangeable.

	IIndexStorage *pIndexStorage = new CIndexStorageA();
	IFuzzyGraphStorage *pFuzzyStorage = new CAdjacencyListStorage();

	//	Return the complete indexing engine.

	return CIndexEngine(pPreprocessor, pTokenizer, pPostprocessor, pIndexStorage, pFuzzyStorage);
	}