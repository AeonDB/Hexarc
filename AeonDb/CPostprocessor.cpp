#include "stdafx.h"

CPostprocessor::CPostprocessor (void){ }
CPostprocessor::CPostprocessor (const CPostprocessor &Other){ }
CPostprocessor::~CPostprocessor (void){ }

CPostprocessor &CPostprocessor::operator= (const CPostprocessor &Other) { return *this; }

void CPostprocessor::Append(IPostprocess *pProc) {}

void CPostprocessor::Run(CTermOccurenceStream &Data) {}