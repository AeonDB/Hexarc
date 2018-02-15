#include "stdafx.h"

CIndexEngine::~CIndexEngine(void) {}
void CIndexEngine::SetPreprocessor(CPreprocessor *pProc) {}
void CIndexEngine::SetTokenizer(ITokenizer *pTokenizer) {}
void CIndexEngine::SetPostprocessor(CPostprocessor *pProc) {}
void CIndexEngine::SetIndexStorage(IIndexStorage *pStorage) {}
void CIndexEngine::SetFuzzyMapStorage(IFuzzyMapStorage *pStorage) {}
bool CIndexEngine::GetLastIndexed(SEQUENCENUMBER *retRowId) {}
bool CIndexEngine::IndexRow(const CRowKey &RowKey, SEQUENCENUMBER RowId, CDatum dValue) {}
bool CIndexEngine::Open(void) {}
bool CIndexEngine::SetLastIndexed(SEQUENCENUMBER RowId) {}