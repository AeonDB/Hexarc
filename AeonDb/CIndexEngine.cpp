#include "stdafx.h"

CIndexEngine::~CIndexEngine(void) {}
void CIndexEngine::SetPreprocessor(CPreprocessor *pProc) {}
void CIndexEngine::SetTokenizer(ITokenizer *pTokenizer) {}
void CIndexEngine::SetPostprocessor(CPostprocessor *pProc) {}
void CIndexEngine::SetIndexStorage(IIndexStorage *pStorage) {}
void CIndexEngine::SetFuzzyMapStorage(IFuzzyMapStorage *pStorage) {}
bool CIndexEngine::GetLastIndexed(SEQUENCENUMBER *retRowId) { return false; }
bool CIndexEngine::IndexRow(const CRowKey &RowKey, SEQUENCENUMBER RowId, const CDatum &dValue) { return false; }
bool CIndexEngine::Open(void) { return false; }
bool CIndexEngine::SetLastIndexed(SEQUENCENUMBER RowId) { return false; }