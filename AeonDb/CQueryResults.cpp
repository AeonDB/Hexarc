//	CQueryResults.cpp
//
//	CResultsIterator class
//
//	Iterator class for CQueryResults. Obtained by calling the Iterator method
//	from a CQueryResults object.
//
//	CQueryResults class
//
//	This class holds the ordered or unordered results of a search. It contains a
//	list of row IDs and search term positions. It does not return the row itself.


#include "stdafx.h"

CResultsIterator::CResultsIterator (TArray<SEQUENCENUMBER> &RowIds, TArray<CIntArray> &Positions) :
		m_RowIds(RowIds),
		m_Positions(Positions),
		m_iCounter(-1)

//	CResultsIterator constructor

	{
	//	Intentionally blank.
	}

CResultsIterator::CResultsIterator (const CResultsIterator &Other) :
		m_RowIds(Other.m_RowIds),
		m_Positions(Other.m_Positions),
		m_iCounter(Other.m_iCounter)
	
//	CResultsIterator copy constructor
	
	{
	//	Intentionally blank.
	}

CResultsIterator::~CResultsIterator (void)

//	CResultsIterator destructor

	{
	// Intentionally blank.
	}

CResultsIterator &CResultsIterator::operator= (const CResultsIterator &Other)

//	CResultsIterator copy assignment operator

	{
	return *this;
	}

bool CResultsIterator::HasNext (void)

//	HasNext
//
//	Returns true if there is at least one more element after this current element.

{
	return m_iCounter < m_RowIds.GetCount() - 1;
}

void CResultsIterator::Next (void)

//	Next
//
//	Iterates to the next element.

	{
	m_iCounter++;
	}

SEQUENCENUMBER &CResultsIterator::PeekRowId (void)

//	PeekRowId
//
//	Returns the row ID of the current result.

	{
	return m_RowIds.GetAt(m_iCounter);
	}

CIntArray &CResultsIterator::PeekTermPositions (void)

//	PeekTermPositions
//
//	Returns the search term positions of the current result.
	
	{
	return m_Positions.GetAt(m_iCounter);
	}

CQueryResults::CQueryResults (void)

//	CQueryResults constructor

	{
	// Intentionally blank.
	}

CQueryResults::CQueryResults (const CQueryResults &Other)

//	CQueryResults copy constructor

	{
	m_RowIds = Other.m_RowIds;
	m_Positions = Other.m_Positions;
	}

CQueryResults::~CQueryResults (void)

//	CQueryResults destructor

	{
	// Intentionally blank.
	}

CQueryResults &CQueryResults::operator= (const CQueryResults &Other)

//	CQueryResults copy assignment operator

	{
	m_RowIds = Other.m_RowIds;
	m_Positions = Other.m_Positions;
	return *this;
	}

void CQueryResults::Append (SEQUENCENUMBER RowId, const CIntArray &TermPositions)

//	Append
//
//	Adds the row ID and its search term positions to the last index.

	{
	// TODO implement this.
	}

CResultsIterator CQueryResults::Iterator (void)

//	Iterator
//
//	Returns an iterator over the elements in this list in proper sequence.

	{
	return CResultsIterator(m_RowIds, m_Positions);
	}
