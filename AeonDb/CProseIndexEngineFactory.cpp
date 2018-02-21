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
//	* CFullwidthAsciiFilter
//	* CPunctuationFilter
//	
//	Uses CSpaceTokenizer as the tokenizer.
//	Does not use any postprocessing classes.

#include "stdafx.h"

CProseIndexEngineFactory::CProseIndexEngineFactory (void)

//	CProseIndexEngineFactory constructor

	{

	//	Intentionally blank

	}

CProseIndexEngineFactory::CProseIndexEngineFactory (const CProseIndexEngineFactory &Factory)

//	CProseIndexEngineFactory copy constructor

	{

	//	Intentionally blank

	}

CProseIndexEngineFactory::~CProseIndexEngineFactory (void)

//	CProseIndexEngineFactory destructor

	{

	//	Intentionally blank

	}

CProseIndexEngineFactory &CProseIndexEngineFactory::operator= (const CProseIndexEngineFactory &Factory)

//	CProseIndexEngineFactory copy assignment operator

	{
	return *this;
	}

IIndexEngineFactory* CProseIndexEngineFactory::Clone (void)

//	Clone
//
//	Polymorphic method to decouple abstraction from implementation.

	{
	return new CProseIndexEngineFactory();
	}

CIndexEngine CProseIndexEngineFactory::Create (void)

//	Create
//
//	Factory method for CIndexEngine.

	{

	//	Insert the preprocessing classes listed in the class description. Order matters.

	CPreprocessor *pPreprocessor = new CPreprocessor();
	pPreprocessor->Append(new CToLowercase());
	pPreprocessor->Append(new CExtendedLatinFilter());
	pPreprocessor->Append(new CFullwidthAsciiFilter());
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