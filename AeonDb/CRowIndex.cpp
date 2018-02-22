//	CRowIndex.cpp
//
//	CRowIndexIterator class
//
//	Iterator for CRowIndex. It starts at index -1 for convenience. Next() must
//	be called before peeking.
//
//	CRowIndex class
//
//	This is a data structure class that represents an inverted index for a single
//	row. ITokenizer produces CTermOccurenceStream, a list of term-position pairs.
//	CIndexEngine feeds those pairs into this class, organizing them into a format
//	that is closer to the final index.

#include "stdafx.h"

CRowIndexIterator::CRowIndexIterator (TSortMap<CString, CIntArray> &Map) : m_Map(Map)

//	CRowIndexIterator constructor

	{
	iCounter = -1;
	}

CRowIndexIterator::CRowIndexIterator (const CRowIndexIterator &Other) : m_Map(Other.m_Map)

//	CRowIndexIterator copy constructor

	{
	iCounter = Other.iCounter;
	}

CRowIndexIterator::~CRowIndexIterator (void)

//	CRowIndexIterator destructor

	{
	}

CRowIndexIterator &CRowIndexIterator::operator= (const CRowIndexIterator &Other)

//	CRowIndexIterator copy assignment operator

	{
	return *this;
	}

bool CRowIndexIterator::HasNext (void)

//	HasNext
//
//	Returns true if there are more elements after the current element.

	{
	return iCounter < m_Map.GetCount() - 1;
	}

void CRowIndexIterator::Next (void)

//	Next
//
//	Iterates to the next element. Can iterate beyond its range.

	{
	iCounter++;
	}

CIntArray &CRowIndexIterator::PeekPos (void)

//	PeekPos
//
//	Returns a reference to a list of index term positions.

	{
	return m_Map.GetValue(iCounter);
	}

const CString &CRowIndexIterator::PeekTerm (void)

//	PeekTerm
//
//	Returns a reference to the current index term.

	{
	return m_Map.GetKey(iCounter);
	}

void CRowIndexIterator::Reset (void)

//	Reset
//
//	Sets the internal counter to index -1.

	{
	iCounter = -1;
	}

CRowIndex::CRowIndex (SEQUENCENUMBER RowId)

//	CRowIndex constructor

	{
	m_RowId = RowId;
	}

CRowIndex::CRowIndex (const CRowIndex &Other) : m_Map(Other.m_Map)

//	CRowIndex copy constructor

	{
	m_RowId = Other.m_RowId;
	}

CRowIndex::~CRowIndex (void)

//	CRowIndex destructor

	{
	}

CRowIndex &CRowIndex::operator= (const CRowIndex &Other)

//	CRowIndex copy assignment operator

	{
	m_Map = Other.m_Map;
	m_RowId = Other.m_RowId;
	}

void CRowIndex::Add (const CString &sTerm, int iTermPosition)

//	Add
//
//	Insert the index term and its position into the row index.

	{

	//	If the index term already exists, get its position list and insert a new position.

	int iPos;
	if (m_Map.FindPos(sTerm, &iPos))
		{
		m_Map.GetValue(iPos).Insert(iTermPosition);
		}

	//	If it doesn't exist, create a list, insert the position, and insert the key-value pair.

	else
		{
		CIntArray Positions;
		Positions.Insert(iTermPosition);
		m_Map.Insert(sTerm, Positions);
		}
	}

SEQUENCENUMBER CRowIndex::GetRowId (void)

//	GetRowId
//
//	Get the ID of the row this object represents.

	{
	return m_RowId;
	}

CRowIndexIterator CRowIndex::Iterator (void)

//	Iterator
//
//	Returns an iterator over the elements in this list in proper sequence.

	{
	return CRowIndexIterator(m_Map);
	}