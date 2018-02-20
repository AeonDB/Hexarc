//	CIndexEngine.cpp
//
//	CIndexEngine class
//
//	CIndexEngine is a collection of modules (CPreprocessor, ITokenizer, CPostprocessor)
//	that modifies and atomizes strings into meaningful substrings and stores them
//	(IIndexStorage, IFuzzyGraphStorage).
//
//	This object should be instantiated by a concrete instance of IIndexEngineFactory.

#include "stdafx.h"

CIndexEngine::CIndexEngine (CPreprocessor *pPreprocessor, ITokenizer *pTokenizer, CPostprocessor *pPostprocessor, IIndexStorage *pIndexStorage, IFuzzyGraphStorage *pFuzzyStorage)

//	CIndexEngine constructor

	{
	m_pPreprocessor = pPreprocessor;
	m_pTokenizer = pTokenizer;
	m_pPostprocessor = pPostprocessor;
	m_pIndexStorage = pIndexStorage;
	m_pFuzzyStorage = pFuzzyStorage;
	}

CIndexEngine::CIndexEngine (const CIndexEngine &Engine)

//	CIndexEngine copy constructor

	{
	m_pPreprocessor = new CPreprocessor(*Engine.m_pPreprocessor);
	m_pTokenizer = Engine.m_pTokenizer->Clone();
	m_pPostprocessor = new CPostprocessor(*Engine.m_pPostprocessor);
	m_pIndexStorage = Engine.m_pIndexStorage->Clone();
	m_pFuzzyStorage = Engine.m_pFuzzyStorage->Clone();
	}

CIndexEngine::~CIndexEngine (void)

//	CIndexEngine destructor

	{
	delete m_pPreprocessor;
	delete m_pTokenizer;
	delete m_pPostprocessor;
	delete m_pIndexStorage;
	delete m_pFuzzyStorage;
	}

CIndexEngine &CIndexEngine::operator= (const CIndexEngine &Engine)

//	CIndexEngine copy assignment operator

	{

	//	Delete pointers.

	delete m_pPreprocessor;
	delete m_pTokenizer;
	delete m_pPostprocessor;
	delete m_pIndexStorage;
	delete m_pFuzzyStorage;

	//	Deep copy.

	m_pPreprocessor = new CPreprocessor(*Engine.m_pPreprocessor);
	m_pTokenizer = Engine.m_pTokenizer->Clone();
	m_pPostprocessor = new CPostprocessor(*Engine.m_pPostprocessor);
	m_pIndexStorage = Engine.m_pIndexStorage->Clone();
	m_pFuzzyStorage = Engine.m_pFuzzyStorage->Clone();

	return *this;
	}

bool CIndexEngine::GetLastIndexed (SEQUENCENUMBER *retRowId)

//	GetLastIndexed
//
//	Gets the ID of the row last indexed. Returns false if fails.

	{

	//	Pass the call to a concrete IIndexStorage class.

	return m_pIndexStorage->GetLastIndexed(retRowId);
	}

bool CIndexEngine::IndexRow (const CRowKey &RowKey, SEQUENCENUMBER RowId, const CDatum &dValue)

//	IndexRow
//
//	Indexes a row and updates the fuzzy word graph. Returns false if fails.

	{

	//	Data needs to be in a string.

	CString sData = dValue.AsString();

	//	Pass the string to the preprocessor.

	m_pPreprocessor->Run(sData);

	//	Pass the modified string to the tokenizer and return term-position pairs.

	CTermOccurenceStream TermOccurences = m_pTokenizer->Operation(sData);

	//	The term-position pairs get passed to the postprocessor, which modifies them in place.

	m_pPostprocessor->Run(TermOccurences);

	//	Organize the term-position pairs into a one-to-many structure.

	STermOccurence *Occurence;
	CRowIndex IndexedRow;
	while (TermOccurences.HasNext())
		{
		Occurence = TermOccurences.Next();
		IndexedRow.Add(Occurence->sTerm, Occurence->iPosition);
		}

	//	Update an existing or insert a new mapping into the index.

	bool bSuccess = false;
	if (m_pIndexStorage->HasRow(RowKey))
		{
		bSuccess = m_pIndexStorage->UpdateRow(RowKey, IndexedRow);
		}
	else
		{
		bSuccess = m_pIndexStorage->InsertRow(RowKey, IndexedRow);
		}

	//	If there are any new terms, add them to the fuzzy word graph.

	CString sTerm;
	IndexedRow.Reset();
	while (IndexedRow.HasNext())
		{
		IndexedRow.Next();
		sTerm = IndexedRow.PeekTerm();
		if (!m_pFuzzyStorage->HasTerm(sTerm)) { bSuccess = bSuccess && m_pFuzzyStorage->AddTerm(sTerm); }
		}

	//	Return false if either the index or fuzzy word graph fails to update.

	return bSuccess;
	}

bool CIndexEngine::Open (void)

//	Open
//
//	Creates the index if it doesn't already exist and then loads it. Returns false if it fails.

	{

	//	Default state is failure.

	bool bIndex = false;
	bool bFuzzy = false;

	//	Tries opening index. If opening fails, then clean up. If cleaning up
	//	successful, then try creating. If deletion or creation fails, then function fails.

	bIndex = m_pIndexStorage->Open();
	if (!bIndex)
		{
		bIndex = m_pIndexStorage->Delete();
		if (bIndex)
			{
			bIndex = m_pIndexStorage->Create();
			}
		}

	//	Same for fuzzy map.

	bFuzzy = m_pFuzzyStorage->Open();
	if (!bFuzzy)
		{
		bFuzzy = m_pFuzzyStorage->Delete();
		if (bFuzzy)
			{
			bFuzzy = m_pFuzzyStorage->Create();
			}
		}

	//	Both index and fuzzy map must be openable.

	return bIndex && bFuzzy;
	}

bool CIndexEngine::SetLastIndexed (SEQUENCENUMBER RowId)

//	SetLastIndexed
//
//	Updates the counter that keeps track of the last row that has been indexed. Returns false if fails.

	{

	//	Pass the call to a concrete IIndexStorage class.

	return m_pIndexStorage->SetLastIndexed(RowId);
	}
