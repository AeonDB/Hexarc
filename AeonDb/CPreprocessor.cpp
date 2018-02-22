//	CPreprocessor.cpp
//
//	CPreprocessor class
//
//	CPreprocessor is a container for preprocessing techniques for generating
//	meaningful indexing terms. This class follows a mix and match style giving
//	the indexing engine great flexibility to adjust to the numerous combinations
//	of writing systems, grammar, whitespace structures, etc present in textual
//	data. This allows which subset of indexing techniques to be selected at runtime,
//	allowing end users to write configuration files or change in real time.
//
//	WARNING: The order in which concrete subclasses of IPreprocess is inserted is important.
//
//	CIndexEngine uses this class.

#include "stdafx.h"

CPreprocessor::CPreprocessor (void)

//	CPreprocessor constructor

	{

	//	Intentionally blank.

	}

CPreprocessor::CPreprocessor (const CPreprocessor &Other) : m_Processes(Other.m_Processes)

//	CPreprocessor copy constructor

	{

	//	Intentionally blank.

	}

CPreprocessor::~CPreprocessor (void)

//	CPreprocessor destructor

	{
	m_Processes.DeleteAllAndFreeValues();
	}

CPreprocessor &CPreprocessor::operator= (const CPreprocessor &Other)

//	CPreprocessor copy assignment operator

	{
	m_Processes = Other.m_Processes;
	return *this;
	}

void CPreprocessor::Append (IPreprocess *pProc)

//	Append
//
//	Inserts a preprocessing technique to the end. Insertion order is important.

	{
	m_Processes.Insert(pProc);
	}

void CPreprocessor::Run (CString &sData)

//	Run
//
//	Processes the data using the selected preprocessing techniques in place.

	{
	for (int i = 0; i < m_Processes.GetCount(); i++)
		{
		m_Processes.GetAt(i)->Operation(sData);
		}
	}
