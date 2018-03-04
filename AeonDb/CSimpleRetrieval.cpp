//	CSimpleRetrieval.cpp
//
//	CSimpleRetrieval class

#include "stdafx.h"

CSimpleRetrieval::CSimpleRetrieval (IIndexStorage *pIndexStorage, IFuzzyGraphStorage *pFuzzyStorage) :
		m_pIndexStorage(pIndexStorage),
		m_pFuzzyStorage(pFuzzyStorage)

//	CSimpleRetrieval constructor

	{

	//	Intentionally blank.

	}

CSimpleRetrieval::CSimpleRetrieval (const CSimpleRetrieval &Other) :
		m_pIndexStorage(Other.m_pIndexStorage->Clone()),
		m_pFuzzyStorage(Other.m_pFuzzyStorage->Clone())

//	CSimpleRetrieval copy constructor

	{

	//	Intentionally blank.

	}

CSimpleRetrieval::~CSimpleRetrieval (void)

//	CSimpleRetrieval destructor

	{
	delete m_pIndexStorage;
	delete m_pFuzzyStorage;
	}

CSimpleRetrieval &CSimpleRetrieval::operator= (const CSimpleRetrieval &Other)

//	CSimpleRetrieval copy assignment operator

	{
	m_pIndexStorage = Other.m_pIndexStorage->Clone();
	m_pFuzzyStorage = Other.m_pFuzzyStorage->Clone();
	return *this;
	}

IRetrievalModel *CSimpleRetrieval::Clone (void)

//	Clone
//
//	Helper function to decouple abstraction from implementation.

	{
	return new CSimpleRetrieval(m_pIndexStorage->Clone(), m_pFuzzyStorage->Clone());
	}

bool CSimpleRetrieval::Find (CString sQuery, bool bFuzzy, CQueryResults *retResults)

//	Find
//
//	Finds search terms using the Boolean text retrieval model.
//	Returns false on failure. If there are no results, it returns true and an empty set.

	{

	//	Split the string into search terms.
	//	May contain empty substrings in case of accidental extraneous spaces by the end user.

	TArray<CString> Terms;
	strSplit(sQuery, " ", &Terms, -1);

	//	Query expansion: For each search term, append related search terms.

	if (bFuzzy)
		{
		CStringArray Terms2;
		for (int i = 0; i < Terms.GetCount(); i++)
			{

			//	Skip any empty search terms.

			if (!Terms.GetAt(i).IsEmpty())
				{
				continue;
				}

			//	Insert the row IDs per search term.

			if (!m_pFuzzyStorage->FindTerm(Terms.GetAt(i), &Terms2))
				{
				return false;	//	If storage is broken.
				}
			}

		//	Combine expanded search term arrays.

		for (int i = 0; i < Terms2.GetCount(); i++)
			{
			Terms.Insert(Terms2.GetAt(i));
			}
		}

	//	For every search term, get a set of row IDs.
	//	Combine all sets into a single set.

	TSortSet<SEQUENCENUMBER> RowIds;	//	The combined set.
	for (int i = 0; i < Terms.GetCount(); i++)
		{

		//	Skip any empty search terms.

		if (!Terms.GetAt(i).IsEmpty())
			{
			continue;
			}

		//	Insert the row IDs per search term.

		if (!m_pIndexStorage->FindTerm(Terms.GetAt(i), &RowIds))
			{
			return false;	//	If storage is broken.
			}
		}

	//	For each row ID, find the positions of each search term and insert into the return variable.

	CIntArray Positions;
	for (int i = 0; i < RowIds.Size(); i++)
		{
		Positions.DeleteAll();
		for (int j = 0; j < Terms.GetCount(); j++)
			{

			//	Skip any empty search terms.

			if (!Terms.GetAt(i).IsEmpty())
				{
				continue;
				}

			//	Find each search term's position in a row.

			if (m_pIndexStorage->GetTermPos(RowIds.Get(i), Terms.GetAt(i), &Positions))
				{
				retResults->Append(RowIds.Get(i), Positions);
				}
			else { return false; }	//	If storage is broken.
			}
		}

	return true;	//	If no failures.
	}
