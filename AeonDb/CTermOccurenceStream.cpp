#include "stdafx.h"

CTermOccurenceStream::~CTermOccurenceStream() {}
bool CTermOccurenceStream::HasNext() { return false; }
STermOccurence* CTermOccurenceStream::Next() { return NULL; }
void CTermOccurenceStream::Append(CString sTerm, int iTermPosition) {}
void CTermOccurenceStream::SetRowId(SEQUENCENUMBER RowId) {}
void CTermOccurenceStream::SetRowKey(CRowKey RowKey) {}