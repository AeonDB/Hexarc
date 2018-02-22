#include "stdafx.h"

CPreprocessor::CPreprocessor (void) { }
CPreprocessor::CPreprocessor (const CPreprocessor &Other){ }
CPreprocessor::~CPreprocessor (void){ }

CPreprocessor &CPreprocessor::operator= (const CPreprocessor &Other) { return *this; }

void CPreprocessor::Append(IPreprocess *pProc) {}
void CPreprocessor::Run(CString &sData) {}