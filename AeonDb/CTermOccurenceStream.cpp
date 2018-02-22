#include "stdafx.h"

CTermOccurenceStream::CTermOccurenceStream (void) { }
CTermOccurenceStream::CTermOccurenceStream (const CTermOccurenceStream &Other) { }
CTermOccurenceStream::~CTermOccurenceStream (void) { }

CTermOccurenceStream &CTermOccurenceStream::operator= (const CTermOccurenceStream &Other) { return *this; }
bool CTermOccurenceStream::HasNext() { return false; }
STermOccurence* CTermOccurenceStream::Next() { return NULL; }
void CTermOccurenceStream::Append(CString sTerm, int iTermPosition) {}
void CTermOccurenceStream::SetRowId(SEQUENCENUMBER RowId) {}
void CTermOccurenceStream::SetRowKey(CRowKey RowKey) {}