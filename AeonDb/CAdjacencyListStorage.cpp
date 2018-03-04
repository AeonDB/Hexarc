#include "stdafx.h"

CAdjacencyListStorage::CAdjacencyListStorage (CAeonTable *pTable, CAeonEngine *pEngine) { }
CAdjacencyListStorage::CAdjacencyListStorage (const CAdjacencyListStorage &Other) { }
CAdjacencyListStorage::~CAdjacencyListStorage (void) { }

CAdjacencyListStorage &CAdjacencyListStorage::operator= (const CAdjacencyListStorage &Other) { return *this; }
IFuzzyGraphStorage *CAdjacencyListStorage::Clone()
	{
	return new CAdjacencyListStorage(m_pTable, m_pEngine);
	}
bool CAdjacencyListStorage::AddTerm(const CString &sTerm) { return true; }
bool CAdjacencyListStorage::Create(void) { return true; }
bool CAdjacencyListStorage::Delete(void) { return true; }
bool CAdjacencyListStorage::HasTerm(const CString &sTerm) { return true; }
bool CAdjacencyListStorage::Open(void) { return true; }
bool CAdjacencyListStorage::Rebuild(void) { return true; }
bool CAdjacencyListStorage::FindTerm (const CString &sTerm, TArray<CString> *retResults) { return true; }