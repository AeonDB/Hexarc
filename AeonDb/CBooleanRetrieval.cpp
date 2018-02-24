#include "stdafx.h"

CBooleanRetrieval::CBooleanRetrieval (void) { }
CBooleanRetrieval::CBooleanRetrieval (const CBooleanRetrieval &Other) { }
CBooleanRetrieval::~CBooleanRetrieval (void) { }

CBooleanRetrieval &CBooleanRetrieval::operator= (const CBooleanRetrieval &Other) { return *this; }
bool CBooleanRetrieval::Find(const CString &sQuery, CQueryResults *retResults) { return false; }
IRetrievalModel *CBooleanRetrieval::Clone(void)
	{
	return new CBooleanRetrieval();
	}