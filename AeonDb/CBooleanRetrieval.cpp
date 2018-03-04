//	CBooleanRetrieval.cpp
//
//	CBooleanRetrieval class

#include "stdafx.h"

CBooleanRetrieval::CBooleanRetrieval (void)

//	CBooleanRetrieval constructor

	{

	//	Intentionally blank.

	}

CBooleanRetrieval::CBooleanRetrieval (const CBooleanRetrieval &Other)

//	CBooleanRetrieval copy constructor

	{

	//	Intentionally blank.

	}

CBooleanRetrieval::~CBooleanRetrieval (void)

//	CBooleanRetrieval destructor

	{

	//	Intentionally blank.

	}

CBooleanRetrieval &CBooleanRetrieval::operator= (const CBooleanRetrieval &Other)

//	CBooleanRetrieval copy assignment operator

	{
	return *this;
	}

IRetrievalModel *CBooleanRetrieval::Clone (void)

//	Clone
//
//	Helper function to decouple abstraction from implementation.

	{
	return new CBooleanRetrieval();
	}

bool CBooleanRetrieval::Find (CString sQuery, bool bFuzzy, CQueryResults *retResults)

//	Find
//
//	Finds search terms using the Boolean text retrieval model.

	{
	return false;
	}
