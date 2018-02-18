#include "stdafx.h"

CRowIndex::~CRowIndex(void) { }
void CRowIndex::Add(CString sTerm, int iTermPosition) { }
SEQUENCENUMBER CRowIndex::GetRowId() { return 0; }

void CRowIndex::Reset(void) { }
CString CRowIndex::PeekTerm(void) { return CString(); }
CIntArray CRowIndex::PeekPositions(void) { return CIntArray(); }
void CRowIndex::Next(void) { }
bool CRowIndex::HasNext(void) { return false; }