//	CTermOccurenceStream.cpp
//
//	CTermOccurenceStreamIterator class
//
//	Iterator class for CTermOccurenceStream.
//
//	CTermOccurenceStream class
//
//	A list of index terms and substring positions pairs.
//
//	ITokenizer produces this class and IPostprocessor uses this class.
//	CIndexEngine creates a CRowIndex object from this class.

#include "stdafx.h"

CTermOccurenceStreamIterator::CTermOccurenceStreamIterator (CStringArray Terms, CIntArray Positions) :
		m_Terms(Terms),
		m_Positions(Positions),
		m_iCounter(-1)

//	CTermOccurenceStreamIterator constructor

	{

	//	Intentionally blank.

	}

CTermOccurenceStreamIterator::CTermOccurenceStreamIterator (const CTermOccurenceStreamIterator &Other) :
		m_Terms(Other.m_Terms),
		m_Positions(Other.m_Positions),
		m_iCounter(Other.m_iCounter)

//	CTermOccurenceStreamIterator copy constructor

	{

	//	Intentionally blank.

	}

CTermOccurenceStreamIterator::~CTermOccurenceStreamIterator (void)

//	CTermOccurenceStreamIterator destructor

	{

	//	Intentionally blank.

	}

CTermOccurenceStreamIterator &CTermOccurenceStreamIterator::operator= (const CTermOccurenceStreamIterator &Other)

//	CTermOccurenceStreamIterator copy assignment operator

	{
	return *this;
	}

bool CTermOccurenceStreamIterator::HasNext (void)

//	HasNext
//
//	Returns true if there are more elements.

	{
	return m_iCounter < m_Terms.GetCount() - 1;
	}

void CTermOccurenceStreamIterator::Next (void)

//	Next
//
//	Iterates to the next element. Can iterate beyond the last element.

	{
	m_iCounter++;
	}

int CTermOccurenceStreamIterator::PeekPos (void)

//	PeekPos
//
//	Get the index term's substring position.

	{
	return m_Positions.GetAt(m_iCounter);
	}

CString CTermOccurenceStreamIterator::PeekTerm (void)

//	PeekTerm
//
//	Get the index term.

	{
	return m_Terms.GetAt(m_iCounter);
	}

CTermOccurenceStream::CTermOccurenceStream ()

//	CTermOccurenceStream constructor

	{

	//	Intentionally blank.

	}

CTermOccurenceStream::CTermOccurenceStream (const CTermOccurenceStream &Other) :
		m_Terms(Other.m_Terms),
		m_Positions(Other.m_Positions)

//	CTermOccurenceStream copy constructor

	{

	//	Intentionally blank.

	}

CTermOccurenceStream::~CTermOccurenceStream (void)

//	CTermOccurenceStream destructor

	{

	//	Intentionally blank.

	}

CTermOccurenceStream &CTermOccurenceStream::operator= (const CTermOccurenceStream &Other)

//	CTermOccurenceStream copy assignment operator

	{
	m_Terms = Other.m_Terms;
	m_Positions = Other.m_Positions;
	return *this;
	}

void CTermOccurenceStream::Append (CString sTerm, int iWordPosition)

//	Append
//
//	Add an index term and its substring position to the end of this list.

	{
	m_Terms.Insert(sTerm);
	m_Positions.Insert(iWordPosition);
	}

CTermOccurenceStreamIterator CTermOccurenceStream::Iterator (void)

//	Iterator
//
//	Get an iterator for this collection.
	
	{
	return CTermOccurenceStreamIterator(m_Terms, m_Positions);
	}
