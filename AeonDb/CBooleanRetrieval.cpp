#include "stdafx.h"

CBooleanRetrieval::~CBooleanRetrieval(void) {}
bool CBooleanRetrieval::Find(const CString &sQuery, CQueryResults *retResults) { return false; }
IRetrievalModel* CBooleanRetrieval::Clone(void)
	{
	return new CBooleanRetrieval();
	}