//	CPostprocessor.cpp
//
//	CPostprocessor class
//
//	CPostprocessor is a container for postprocessing techniques for generating
//	meaningful indexing terms. This class follows a mix and match style giving
//	the indexing engine great flexibility to adjust to the numerous combinations
//	of writing systems, grammar, whitespace structures, etc present in textual
//	data. This allows which subset of indexing techniques to be selected at runtime,
//	allowing end users to write configuration files or change in real time.
//
//	WARNING: The order in which concrete subclasses of IPostprocess is inserted is important.
//
//	CIndexEngine uses this class.

#include "stdafx.h"

CPostprocessor::CPostprocessor (void)
	
//	CPostprocessor constructor

	{

	//	Intentionally blank.

	}

CPostprocessor::CPostprocessor (const CPostprocessor &Other) : m_Processes(Other.m_Processes)

//	CPostprocessor copy constructor

	{

	//	Intentionally blank.

	}

CPostprocessor::~CPostprocessor (void)
	
//	CPostprocessor destructor

	{
	m_Processes.DeleteAllAndFreeValues();
	}

CPostprocessor &CPostprocessor::operator= (const CPostprocessor &Other)

//	CPostprocessor copy assignment operator

	{
	m_Processes = Other.m_Processes;
	return *this;
	}

void CPostprocessor::Append (IPostprocess *pProc)

//	Append
//
//	Inserts a postprocessing technique to the end. Insertion order is important.

	{
	m_Processes.Insert(pProc);
	}

void CPostprocessor::Run (CTermOccurenceStream &Data)

//	Run
//
//	Processes the data using the selected postprocessing techniques in place.

	{
	for (int i = 0; i < m_Processes.GetCount(); i++)
		{
		m_Processes.GetAt(i)->Operation(Data);
		}
	}