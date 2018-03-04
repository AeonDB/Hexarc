//
//
//

#include "stdafx.h"

DECLARE_CONST_STRING(INDEX_KEY_INDEX,			"index")
DECLARE_CONST_STRING(INDEX_KEY_POSITIONS,		"positions")
DECLARE_CONST_STRING(INDEX_KEY_ROWKEY_ROWID,	"rowKeyRowId")
DECLARE_CONST_STRING(INDEX_KEY_LATEST_ROWID,	"latestRowId")
DECLARE_CONST_STRING(INDEX_MAIN_KEY,			"indexKey")

//	Helper functions

CTableDimensions GetTableDimensions1 (void)

//
//
//

	{
	CTableDimensions Dims;
	Dims.Insert({EKeyTypes::keyUTF8, ESortOptions::AscendingSort});
	return Dims;
	}

CDatum GetTableDimensions2 (void)

//
//
//

	{
	CDatum dDim(CDatum::typeStruct);
	dDim.SetElement("keyType", CDatum("utf8"));
	dDim.SetElement("keySort", CDatum("ascending"));
	return dDim;
	}

bool StrToRowKey (CString sKey, CRowKey *retRowKey)

//
//
//

	{
	CString sError;
	CDatum dKey(sKey);
	return CRowKey::ParseKeyForCreate(GetTableDimensions1(), dKey, retRowKey, &sError);
	}

bool GetDataFromTable (CAeonTable *pTable, CDatum *retdData)

//
//
//

	{
	CRowKey RowKey;
	if (!StrToRowKey(INDEX_MAIN_KEY, &RowKey))
		{
		printf("GetDataFromTable failed. Bad key.\n");
		return false;
		}

	CString sError;
	SEQUENCENUMBER RowId;

	if (!pTable->GetData(CAeonTable::DEFAULT_VIEW, RowKey, retdData, &RowId, &sError))
		{
		printf(sError + " : GetDataFromTable failed. Could not get row data.\n");
		return false;
		}

	return true;
	}

bool SetDataToTable (CAeonTable *pTable, CDatum &dData)

//
//
//

	{
	CRowKey RowKey;
	if (!StrToRowKey(INDEX_MAIN_KEY, &RowKey))
		{
		printf("SetDataToTable failed. Bad key.\n");
		return false;
		}

	CString sError;

	bool bSuccess = pTable->Insert(RowKey, dData, &sError);

	if (!bSuccess)
		{
		printf(sError + " : SetDataToTable failed. Bad insertion.\n");
		return false;
		}

	return true;
	}

CDatum AsDatum2 (CIntArray Array)

//
//
//

	{
	CDatum dArray(CDatum::typeArray);
	for (int i = 0; i < Array.GetCount(); i++)
		{
		dArray.Append(Array.GetAt(i));
		}
	return dArray;
	}

CDatum AsDatum2 (TArray<SEQUENCENUMBER> Array)

//
//
//

	{
	CDatum dArray(CDatum::typeArray);
	for (int i = 0; i < Array.GetCount(); i++)
		{
		dArray.Append(Array.GetAt(i));
		}
	return dArray;
	}

CDatum AsDatum2 (TSortMap<CString, CIntArray> Map)

//
//
//

	{
	CDatum dMap(CDatum::typeStruct);
	for (int i = 0; i < Map.GetCount(); i++)
		{
		dMap.SetElement(Map.GetKey(i), AsDatum2(Map.GetValue(i)));
		}
	return dMap;
	}

CDatum AsDatum2 (TSortMap<CString, TArray<SEQUENCENUMBER>> Map)

//
//
//

	{
	CDatum dMap(CDatum::typeStruct);
	for (int i = 0; i < Map.GetCount(); i++)
		{
		dMap.SetElement(Map.GetKey(i), AsDatum2(Map.GetValue(i)));
		}
	return dMap;
	}

CDatum AsDatum2 (TSortMap<SEQUENCENUMBER, TSortMap<CString, CIntArray>> Map)

//
//
//

	{
	CDatum dMap(CDatum::typeStruct);
	for (int i = 0; i < Map.GetCount(); i++)
		{
		CString sKey = strFromInt(Map.GetKey(i), false);
		dMap.SetElement(sKey, AsDatum2(Map.GetValue(i)));
		}
	return dMap;
	}

CIntArray ToIntArray (CDatum dArray)

//
//
//

	{
	CIntArray Array;
	for (int i = 0; i < dArray.GetArrayCount(); i++)
		{
		Array.Insert(dArray.GetArrayElement(i));
		}
	return Array;
	}

TArray<SEQUENCENUMBER> ToSeqArray (CDatum dArray)

//
//
//

	{
	TArray<SEQUENCENUMBER> Array;
	for (int i = 0; i < dArray.GetArrayCount(); i++)
		{
		Array.Insert(dArray.GetArrayElement(i));
		}
	return Array;
	}

TSortMap<CString, CIntArray> ToStringIntArrayMap (CDatum dMap)

//
//
//

	{
	TSortMap<CString, CIntArray> Map;
	for (int i = 0; i < dMap.GetCount(); i++)
		{
		Map.Insert(dMap.GetKey(i), ToIntArray(dMap.GetElement(i)));
		}
	return Map;
	}

TSortMap<CString, TArray<SEQUENCENUMBER>> ToStringSeqArrayMap (CDatum dMap)

//
//
//

	{
	TSortMap<CString, TArray<SEQUENCENUMBER>> Map;
	for (int i = 0; i < dMap.GetCount(); i++)
		{
		Map.Insert(dMap.GetKey(i), ToSeqArray(dMap.GetElement(i)));
		}
	return Map;
	}

TSortMap<SEQUENCENUMBER, TSortMap<CString, CIntArray>> ToSeqStringIntArrayMapMap (CDatum dMap)

//
//
//

	{
	TSortMap<SEQUENCENUMBER, TSortMap<CString, CIntArray>> Map;
	for (int i = 0; i < dMap.GetCount(); i++)
		{
		SEQUENCENUMBER RowId = strParseInt(dMap.GetKey(i));
		Map.Insert(RowId, ToStringIntArrayMap(dMap.GetElement(i)));
		}
	return Map;
	}

CIndexStructure::CIndexStructure (CDatum &Src)
	{
	m_Latest = Src.GetElement(INDEX_KEY_LATEST_ROWID);
	m_Index = ToStringSeqArrayMap(Src.GetElement(INDEX_KEY_INDEX));
	m_Positions = ToSeqStringIntArrayMapMap(Src.GetElement(INDEX_KEY_POSITIONS));
	}

CIndexStructure::~CIndexStructure (void)
	{
	}

void CIndexStructure::Update (SEQUENCENUMBER RowId, CString sTerm)
	{
	if (!m_Index.Find(sTerm))
		m_Index.Insert(sTerm, TArray<SEQUENCENUMBER>());
	m_Index.GetAt(sTerm)->Insert(RowId);
	}

void CIndexStructure::Update2 (SEQUENCENUMBER RowId, TSortMap<CString, CIntArray> TermPositions)
	{
	m_Positions.DeleteAt(RowId);
	m_Positions.Insert(RowId, TermPositions);
	}

SEQUENCENUMBER CIndexStructure::GetLatestRowId (void)
	{
	return m_Latest;
	}

void CIndexStructure::SetLatestRowId (SEQUENCENUMBER RowId)
	{
	m_Latest = RowId;
	}

CDatum CIndexStructure::AsDatum (void)
	{
	CDatum dData;
	dData.SetElement(INDEX_KEY_LATEST_ROWID, m_Latest);
	dData.SetElement(INDEX_KEY_INDEX, AsDatum2(m_Index));
	dData.SetElement(INDEX_KEY_POSITIONS, AsDatum2(m_Positions));
	return dData;
	}

CIndexStorageA::CIndexStorageA (CAeonTable *pTable, CAeonEngine *pEngine) :
		m_pTable(pTable),
		m_pIndexTable(NULL),
		m_pEngine(pEngine),
		m_pIndexStructure(NULL)

//

	{
	}

CIndexStorageA::CIndexStorageA (const CIndexStorageA &Other)

//

	{
	}

CIndexStorageA::~CIndexStorageA (void)

//

	{
	Save();
	delete m_pIndexStructure;
	}

CIndexStorageA &CIndexStorageA::operator= (const CIndexStorageA &Other)

//

	{
	return *this;
	}

IIndexStorage *CIndexStorageA::Clone (void)

//
//
//

	{
	return new CIndexStorageA (m_pTable, m_pEngine);
	}

bool CIndexStorageA::GetTermPos (SEQUENCENUMBER RowId, const CString &sTerm, CIntArray *retPositions)

//
//
//

	{
	return false;
	}

bool CIndexStorageA::FindTerm (const CString &sTerm, TSortSet<SEQUENCENUMBER> *retResults)

//
//
//

	{
	printf("FindTerm\n");
	return false;
	}

bool CIndexStorageA::RemoveRow (const CRowKey &Key)

//
//
//

	{
	printf("RemoveRow\n");
	return false;
	}

bool CIndexStorageA::InsertRow (const CRowKey &Key, CRowIndex &Data)

//
//
//

	{
	CRowIndexIterator Iterator = Data.Iterator();
	while (Iterator.HasNext())
		{
		Iterator.Next();
		m_pIndexStructure->Update(Data.GetRowId(), Iterator.PeekTerm());
		}

	m_pIndexStructure->Update2(Data.GetRowId(), Data.GetMap());

	printf("Inserted row.\n");
	return true;
	}

bool CIndexStorageA::UpdateRow (const CRowKey &Key, const CRowIndex &Data)

//
//
//

	{
	printf("UpdateRow\n");
	return false;
	}

bool CIndexStorageA::HasRow (const CRowKey &Key)

//
//
//

	{
	printf("HasRow\n");
	return false;
	}

bool CIndexStorageA::HasTerm (const CString &sTerm)

//
//
//

	{
	printf("HasTerm\n");
	return false;
	}

bool CIndexStorageA::GetLastIndexed (SEQUENCENUMBER *retRowId)

//
//
//

	{
	*retRowId = m_pIndexStructure->GetLatestRowId();
	return true;
	}

bool CIndexStorageA::SetLastIndexed (SEQUENCENUMBER RowID)

//
//
//

	{
	m_pIndexStructure->SetLatestRowId(RowID);
	return true;
	}

bool CIndexStorageA::Save (void)

//
//
//
//

	{
	CString sError;
	CRowKey RowKey;

	if (!StrToRowKey(INDEX_MAIN_KEY, &RowKey))
		{
		printf("Save index failed. Bad key.\n");
		return false;
		}

	if (!m_pIndexTable->Insert(RowKey, m_pIndexStructure->AsDatum(), &sError))
		{
		printf("Cannot write to index file.\n");
		printf(sError + "\n");
		return false;
		}

	return true;
	}

bool CIndexStorageA::Open (void)

//
//
//

	{
	printf("Opening index files.\n");
	if (!m_pEngine->FindTable(m_pTable->GetName() + "_index", &m_pIndexTable))
		{
		printf("Cannot find index files.\n");
		if (!Create())
			return false;
		}



	CString sError;
	CRowKey RowKey;

	if (!StrToRowKey(INDEX_MAIN_KEY, &RowKey))
		{
		printf("Open index failed. Bad key.\n");
		return false;
		}

	CDatum dWholeIndex;
	SEQUENCENUMBER Useless;

	if (!m_pIndexTable->GetData(CAeonTable::DEFAULT_VIEW, RowKey, &dWholeIndex, &Useless, &sError))
		{
		printf(sError + ": Can't load index file.\n");
		return false;
		}

	m_pIndexStructure = new CIndexStructure(dWholeIndex);

	printf("Successfully opened index file.\n");
	return true;
	}

bool CIndexStorageA::Create (void)

//
//
//

	{
	printf("Creating new index file.\n");
	CDatum dTableDesc(CDatum::typeStruct);
	dTableDesc.SetElement("name", m_pTable->GetName() + "_index");
	dTableDesc.SetElement("x", GetTableDimensions2());

	bool bExists = false;
	CString sError;

	bool bSuccess = m_pEngine->CreateTable(dTableDesc, &m_pIndexTable, &bExists, &sError);

	if (bExists)
		printf("Index file already exists.\n");

	if (bSuccess)
		printf("Created index file.\n");
	else
		printf("Failed creating index file.\n");
		printf(sError + "\n");
	
	return bSuccess;
	}

bool CIndexStorageA::Delete (void)

//
//
//

	{
	return m_pIndexTable->Delete();
	}