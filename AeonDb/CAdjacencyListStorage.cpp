#include "stdafx.h"

CAdjacencyListStorage::~CAdjacencyListStorage(void) { }
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