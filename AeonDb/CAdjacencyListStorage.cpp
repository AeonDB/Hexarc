#include "stdafx.h"

CAdjacencyListStorage::CAdjacencyListStorage (void){ }
CAdjacencyListStorage::CAdjacencyListStorage (const CAdjacencyListStorage &Other){ }
CAdjacencyListStorage::~CAdjacencyListStorage (void){ }

CAdjacencyListStorage &CAdjacencyListStorage::operator= (const CAdjacencyListStorage &Other) { return *this; }
IFuzzyGraphStorage* CAdjacencyListStorage::Clone()
	{
	return new CAdjacencyListStorage();
	}
bool CAdjacencyListStorage::AddTerm(const CString &sTerm) { return false; }
bool CAdjacencyListStorage::Create(void) { return false; }
bool CAdjacencyListStorage::Delete(void) { return false; }
bool CAdjacencyListStorage::HasTerm(const CString &sTerm) { return false; }
bool CAdjacencyListStorage::Open(void) { return false; }
bool CAdjacencyListStorage::Rebuild(void) { return false; }