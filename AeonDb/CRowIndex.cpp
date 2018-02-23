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

CRowIndexIterator::CRowIndexIterator (TSortMap<CString, CIntArray> &Map) :
		m_Map(Map),
		m_iCounter(-1)

//	CRowIndexIterator constructor

	{

	//	Intentionally blank.

	}

CRowIndexIterator::CRowIndexIterator (const CRowIndexIterator &Other) :
		m_Map(Other.m_Map),
		m_iCounter(Other.m_iCounter)

//	CRowIndexIterator copy constructor

	{

	//	Intentionally blank.

	}

CRowIndexIterator::~CRowIndexIterator (void)

//	CRowIndexIterator destructor

	{

	//	Intentionally blank.

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
	return m_iCounter < m_Map.GetCount() - 1;
	}

void CRowIndexIterator::Next (void)

//	Next
//
//	Iterates to the next element. Can iterate beyond its range.

	{
	m_iCounter++;
	}

CIntArray &CRowIndexIterator::PeekPos (void)

//	PeekPos
//
//	Returns a reference to a list of index term positions.

	{
	return m_Map.GetValue(m_iCounter);
	}

const CString &CRowIndexIterator::PeekTerm (void)

//	PeekTerm
//
//	Returns a reference to the current index term.

	{
	return m_Map.GetKey(m_iCounter);
	}

void CRowIndexIterator::Reset (void)

//	Reset
//
//	Sets the internal counter to index -1.

	{
	m_iCounter = -1;
	}

CRowIndex::CRowIndex (const CRowKey &RowKey, SEQUENCENUMBER RowId) :
		m_RowKey(RowKey),
		m_RowId(RowId)

//	CRowIndex constructor

	{

	//	Intentionally blank.

	}

CRowIndex::CRowIndex (const CRowIndex &Other) :
		m_Map(Other.m_Map),
		m_RowKey(Other.m_RowKey),
		m_RowId(Other.m_RowId)

//	CRowIndex copy constructor

	{

	//	Intentionally blank.

	}

CRowIndex::~CRowIndex (void)

//	CRowIndex destructor

	{

	//	Intentionally blank.

	}

CRowIndex &CRowIndex::operator= (const CRowIndex &Other)

//	CRowIndex copy assignment operator

	{
	m_Map = Other.m_Map;
	m_RowId = Other.m_RowId;
	m_RowKey = Other.m_RowKey;
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

CRowKey CRowIndex::GetRowKey (void)

//	GetRowKey
//
//	Get the key of the row this object represents.

	{
	return m_RowKey;
	}

CRowIndexIterator CRowIndex::Iterator (void)

//	Iterator
//
//	Returns an iterator over the elements in this list in proper sequence.

	{
	return CRowIndexIterator(m_Map);
	}
