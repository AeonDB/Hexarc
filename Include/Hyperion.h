//	Hyperion.h
//
//	Hyperion Engine Implementation
//	Copyright (c) 2011 by George Moromisato. All Rights Reserved.
//
//	STANDARD PERMISSIONS
//
//	Arc.admin:				User has administrator access to the arcology. A
//							user with this permission has all other permissions.
//
//	Arc.developer:			User may add and modify sandboxed services in the arcology.
//							Implies Arc.user.
//
//	Arc.maintenance:		User may maintain the arcology. Implies Arc.user.
//
//	Arc.user:				User may use appropriate services in the arcology.
//							It is up to each service to decide the level of access
//							Based on its own permissions.
//
//	Connect.local:			User has a local connection to arcology (implies
//							that user has physical access to one of the machines
//							in the arcology).
//
//	Connect.remote:			User is connected via remote connection.

#pragma once

#include "Hexe.h"

#define LOG_HTTP_SESSION

#ifdef DEBUG
//#define DEBUG_FILES
#endif

class CHyperionEngine;
class CAI1Service;
class CHTTPService;

//	Users

class CUserInfo
	{
	public:
		inline void DeleteRight (const CString &sRight) { m_Rights.Delete(sRight); }
		inline const CString &GetUsername (void) const { return m_sUsername; }
		inline bool HasRight (const CString &sRight) const { return m_Rights.HasAttribute(sRight); }
		bool HasRights (const CAttributeList &Rights) const;
		inline void InsertRight (const CString &sRight) { m_Rights.Insert(sRight); }
		inline bool IsAnonymous (void) const { return m_sUsername.IsEmpty(); }
		inline void SetAnonymous (void) { m_sUsername = NULL_STR; m_Rights.DeleteAll(); }
		inline void SetRights (CDatum dRights) { dRights.AsAttributeList(&m_Rights); }
		inline void SetUsername (const CString &sUsername) { m_sUsername = sUsername; }

	private:
		CString m_sUsername;					//	Username
		CAttributeList m_Rights;				//	User rights
	};

class CConnectionInfo
	{
	private:
		CString m_sClientType;					//	Type of client
		CString m_sClient;						//	Name of client (same as user-agent)
		CAttributeList m_Attribs;				//	COnnection attributes
	};

//	Sessions -------------------------------------------------------------------

class CHyperionSession : public ISessionHandler
	{
	public:
		CHyperionSession (CHyperionEngine *pEngine, const CString &sListener, CDatum dSocket, const CString &sNetAddress);

		void DebugLog (const CString &sLog);
		virtual CString GetDebugInfo (void) const;
		inline CHyperionEngine *GetEngine (void) const { return m_pEngine; }
		inline CHexeSecurityCtx &GetSecurityCtx (void) { return m_SecurityCtx; }
		inline void SetServiceSecurity (const CHexeSecurityCtx &SecurityCtx) { m_SecurityCtx.SetServiceSecurity(SecurityCtx); }

	protected:

		//	ISessionHandler virtuals

		//	NOTE: Subclasses must call CHyperionSession::OnMark if they override OnMark.
		//	LATER: We should fix this by making the subclasses override a different
		//	method.

		virtual void OnGetStatusReport (CComplexStruct *pStatus) const;
		virtual void OnMark (void) { m_dSocket.Mark(); }

		//	CHyperionSession virtuals

		virtual void OnGetHyperionStatusResport (CComplexStruct *pStatus) const { }

		CHyperionEngine *m_pEngine;
		CString m_sListener;				//	Request came through this listener
		CDatum m_dSocket;					//	Request came on this socket
		CString m_sNetAddress;				//	IP address of client making request (including port)
		CHexeSecurityCtx m_SecurityCtx;		//	Service and user security context.
	};

//	Services -------------------------------------------------------------------

class IHyperionService
	{
	public:
		struct SListenerDesc
			{
			CString sProtocol;
			CString sPort;
			};

		virtual ~IHyperionService (void) { }

		static bool CreateService (const CString &sName,
								   CDatum dServiceDef, 
								   const CHexeDocument &Package, 
								   const CString &sPackageName,
								   IHyperionService **retpService, 
								   CString *retsError);

		inline CHyperionSession *CreateSessionObject (CHyperionEngine *pEngine, const CString &sListener, const CString &sSocket, const CString &sNetAddress) { return OnCreateSessionObject(pEngine, sListener, sSocket, sNetAddress); }
		inline void DeleteSession (CHyperionSession *pSession) { CSmartLock Lock(m_cs); m_Sessions.DeleteValue(pSession); }
		inline CString GetFileRoot (void) const { return OnGetFileRoot(); }
		inline const CString &GetName (void) const { return m_sName; }
		inline const CString &GetPackageName (void) const { return m_sPackageName; }
		inline const CString &GetPort (void) const { return m_sPort; }
		inline void GetListeners (TArray<SListenerDesc> &Listeners) const { return OnGetListeners(Listeners); }
		inline const CString &GetProtocol (void) const { return m_sProtocol; }
		inline const CHexeSecurityCtx &GetSecurityCtx (void) const { return m_SecurityCtx; }
		inline int GetSessionCount (void) const { CSmartLock Lock(m_cs); return m_Sessions.GetCount(); }
		inline void InitProcess (CHexeProcess &Process) { OnInitProcess(Process); }
		inline void InsertSession (CHyperionSession *pSession) { CSmartLock Lock(m_cs); m_Sessions.Insert(pSession); }
		bool IsAccessible (const CString &sName);
		inline bool IsListener (void) const { return OnIsListener(); }
		inline bool IsSandboxed (void) { return !m_SecurityCtx.GetSandbox().IsEmpty(); }
		inline void Mark (void) { OnMark(); }

		static bool ParseObjectName (const CString &sName, CString *retsSandbox, CString *retsLocalName);
		static bool ValidatePort (const CString &sPort);

	protected:
		//	IHyperionService
		virtual CHyperionSession *OnCreateSessionObject (CHyperionEngine *pEngine, const CString &sListener, const CString &sSocket, const CString &sNetAddress) { return NULL; }
		virtual CString OnGetFileRoot (void) const { return NULL_STR; }
		virtual void OnGetListeners (TArray<SListenerDesc> &Listeners) const;
		virtual bool OnInit (CDatum dServiceDef, const CHexeDocument &Package, CString *retsError) { return true; }
		virtual void OnInitProcess (CHexeProcess &Process) { }
		virtual bool OnIsListener (void) const { return false; }
		virtual void OnMark (void) { }

	private:
		CCriticalSection m_cs;

		CString m_sPackageName;
		CString m_sName;
		CString m_sProtocol;
		CString m_sPort;

		CHexeSecurityCtx m_SecurityCtx;		//	Service security (excluding user info)

		TArray<CHyperionSession *> m_Sessions;		//	We keep track of the sessions that are
													//	using this service.
	};

class CHyperionCommandSet
	{
	public:
		struct SCommandInfo
			{
			CDatum dDesc;

			CString sName;
			CDatum dHelp;
			CAttributeList Attribs;
			bool bPublic;

			CDatum dCode;
			};

		~CHyperionCommandSet (void);

		bool AddCommand (const CString &sName, CDatum dDesc, SCommandInfo **retpEntry, CString *retsError);
		void DeleteAll (void);
		bool FindCommand (const CString &sAttrib, const CString &sName, SCommandInfo *retCommand);
		void GetCommands (const CString &sAttrib, TArray<CHyperionCommandSet::SCommandInfo> *retList);
		void Mark (void);

	private:
		typedef TSortMap<CString, SCommandInfo *> CCommandIndex;

		TArray<SCommandInfo *> m_AllCommands;
		TSortMap<CString, CCommandIndex> m_ByAttrib;
	};

class CHyperionPackageList
	{
	public:
		struct SPackageFileInfo
			{
			CString sFilePath;
			DWORD dwVersion;
			};

		struct SPackageInfo
			{
			CString sName;
			CString sFilePath;
			CString sVersion;
			CString sModifiedBy;
			CDateTime ModifiedOn;
			};

		struct SServiceInfo
			{
			CString sName;
			IHyperionService *pService;
			};

		struct STableInfo
			{
			CString sName;
			CDatum dDesc;
			};

		struct STaskInfo
			{
			CString sName;
			int iInterval;
			CDatum dCode;
			};

		CHyperionPackageList (void);
		~CHyperionPackageList (void);

		bool AddPackage (IArchonProcessCtx *pProcess, CDatum dFileDesc, CHexeProcess &Process, CHexeDocument &Doc, CString *retsName, CString *retsError);
		bool AddPackage (IArchonProcessCtx *pProcess, CDatum dFileDesc, IByteStream &Stream, CString *retsName, CString *retsError);
		bool AddPackage (IArchonProcessCtx *pProcess, const CString &sResName, CString *retsError);
		bool FindCommand (const CString &sAttrib, const CString &sCommand, CHyperionCommandSet::SCommandInfo *retInfo);
		bool FindCommand (const CString &sPackage, const CString &sAttrib, const CString &sCommand, CHyperionCommandSet::SCommandInfo *retInfo);
		void GetCommands (const CString &sAttrib, TArray<CHyperionCommandSet::SCommandInfo> *retList);
		void GetPackageList (TArray<SPackageInfo> *retPackages);
		void GetPackageTables (const CString &sName, TArray<CDatum> *retTables);
		void GetScheduledTasks (IArchonProcessCtx *pProcess, TArray<STaskInfo> *retList);
		void GetServices (TArray<SServiceInfo> *retList);
		void SetPackages (const TArray<SPackageFileInfo> &List, TArray<CString> *retNeeded);
		void Mark (void);

		static CString ComputePackageName (const CString &sFilePath);

	private:
		struct SPackage
			{
			CString sName;							//	Name of package

			CString sFilePath;						//	Filepath of package
			CString sVersion;						//	Version string in package file
			DWORD dwVersion;						//	Version of package files
			CString sModifiedBy;					//	Username of person who uploaded this package version
			CDateTime ModifiedOn;					//	Date time when package was uploaded
			TArray<CString> Developers;				//	List of usernames allowed to overwrite package
			CHexeSecurityCtx PackageSecurity;		//	Rights requested by package

			TArray<SServiceInfo> Services;			//	List of services in this package. This structure
													//	owns the service pointer.

			TArray<STableInfo> Tables;				//	List of table definitions for this package.

			CHyperionCommandSet CommandSet;			//	List of commands (entry points)

			bool bBuiltIn;							//	TRUE if package came with EXE
			bool bDelete;							//	Temporary used during package config
			};

		void CleanUpPackage (SPackage *pEntry);
		void CollectGarbage (void);
		bool FindPackage (const CString &sFilePath, int *retiIndex = NULL);
		bool FindPackageByName (const CString &sName, int *retiIndex = NULL);
		bool InitPackage (SPackage *pPackage, CDatum dPackageDef, CString *retsError);
		bool LoadPackageDoc (IArchonProcessCtx *pProcess, SPackage *pPackage, CHexeProcess &Process, CHexeDocument &PackageDoc, CString *retsError);
		bool LoadPackageDoc (IArchonProcessCtx *pProcess, SPackage *pPackage, IByteStream &Stream, CString *retsError);
		void MarkPackage (SPackage *pEntry);
		bool ValidateServiceName (SPackage *pPackage, const CString &sSandboxPrefix, const CString &sServiceName, CString *retsError);

		CCriticalSection m_cs;
		TArray<SPackage> m_Packages;

		TArray<IHyperionService *> m_Deleted;
	};

class CHyperionScheduler
	{
	public:
		enum EResults
			{
			resultOK,
			resultError,

			resultRunning,
			};

		CDatum GetTaskList (void);
		void GetTasksToRun (TArray<CString> *retTasks);
		bool IsSignalStop (const CString &sTask, CString *retsMessage);
		void Mark (void);
		void SetRunComplete (const CString &sTask);
		EResults SetRunning (const CString &sTask, CDatum *retdCode);
		bool SetSignalStop (const CString &sTask, CString *retsError);
		void SetTaskList (const TArray<CHyperionPackageList::STaskInfo> &Tasks);
		bool SetTaskRunOn (const CString &sTask, const CDateTime &RunOn, CString *retsError);

	private:
		struct STask
			{
			CString sName;							//	Task name (globally unique)
			int iInterval;							//	Interval between runs (in seconds)

			CDatum dCode;

			CDateTime LastRun;						//	Last time we ran
			CDateTime NextRun;						//	Next time we're scheduled to run

			bool bRunning;							//	TRUE if we're running now
			bool bDelete;							//	TRUE if we need to delete this task when it's done
			bool bMarked;							//	Temp
			bool bSignalStop;						//	TRUE if we need to stop running
			};

		CCriticalSection m_cs;
		TSortMap<CString, STask> m_Tasks;
	};

class CHyperionCache
	{
	public:
		bool FindEntry (const CString &sID, CDatum *retdEntry = NULL) const;
		void Mark (void);
		void SetEntry (const CString &sID, CDatum dEntry);

	private:
		struct SEntry
			{
			CDatum dEntry;
			mutable DWORDLONG dwLastAccess;
			};

		CCriticalSection m_cs;
		TSortMap<CString, SEntry> m_Cache;
	};

//	CHyperionEngine ------------------------------------------------------------

class CHyperionEngine : public TSimpleEngine<CHyperionEngine>
	{
	public:
		CHyperionEngine (void);
		virtual ~CHyperionEngine (void);

		//	Used by session objects
		bool AddServicePackage (CDatum dFileDesc, CHexeProcess &Process, CHexeDocument &Doc, CString *retsName);
		void AddServicePackage (const CString &sResName);
		void Disconnect (const CString &sSocket);
		void FatalError (const SArchonMessage &Msg);
		bool FindAI1Service (const CString &sListener, const CString &sInterface, CAI1Service **retpService);
		bool FindHTTPService (const CString &sListener, const CHTTPMessage &Request, CHTTPService **retpService);
		inline bool FindServiceCommand (const CString &sAttrib, const CString &sCommand, CHyperionCommandSet::SCommandInfo *retInfo) { return m_Packages.FindCommand(sAttrib, sCommand, retInfo); }
		inline bool FindServiceCommand (const CString &sPackage, const CString &sAttrib, const CString &sCommand, CHyperionCommandSet::SCommandInfo *retInfo) { return m_Packages.FindCommand(sPackage, sAttrib, sCommand, retInfo); }
		inline CHyperionCache &GetCache (void) { return m_Cache; }
		inline void GetCommands (const CString &sAttrib, TArray<CHyperionCommandSet::SCommandInfo> *retList) { m_Packages.GetCommands(sAttrib, retList); }
		inline CCriticalSection &GetCS (void) { return m_cs; }
		inline void GetPackageTables (const CString &sPackage, TArray<CDatum> *retTableDefs) { m_Packages.GetPackageTables(sPackage, retTableDefs); }
		inline bool IsAdminNeeded (void) { return m_bAdminNeeded; }
		void LoadServices (void);
		inline void SetServicePackages (const TArray<CHyperionPackageList::SPackageFileInfo> &List, TArray<CString> *retNeeded) { m_Packages.SetPackages(List, retNeeded); }

		//	TSimpleEngine
		static SMessageHandler m_MsgHandlerList[];
		static int m_iMsgHandlerListCount;

	protected:
		virtual void OnBoot (void);
		virtual void OnMarkEx (void);
		virtual void OnStartRunning (void);
		virtual void OnStopRunning (void);

	private:
		enum EListenerStatus
			{
			statusUnknown,
			statusStopped,
			statusListening,
			statusListenRequested,
			statusStopRequested,
			};

		struct SListener
			{
			CString sName;							//	Name that we registered
			CString sProtocol;						//	Esper-defined protocol (NULL_STR == raw)
			CString sPort;							//	Port number
			DWORD dwLastTicket;						//	Ticket used for most recent request
			EListenerStatus iStatus;				//	Current status
			EListenerStatus iDesiredStatus;			//	Desired status

			TArray<IHyperionService *> Services;	//	List of services for this listener.
													//	The service object is owned by the
													//	package list (we don't own it).
			};

		struct SMsgHandler
			{
			CString sName;							//	Name that we registered (e.g., "Multiverse.msg")
			IHyperionService *pService;				//	Service (may be NULL, if inactive)
			};

		//	Messages
		void MsgAeonOnStart (const SArchonMessage &Msg, const CHexeSecurityCtx *pSecurityCtx);
		void MsgCryptosaurOnAdminNeeded (const SArchonMessage &Msg, const CHexeSecurityCtx *pSecurityCtx);
		void MsgCryptosaurOnStart (const SArchonMessage &Msg, const CHexeSecurityCtx *pSecurityCtx);
		void MsgEsperOnConnect (const SArchonMessage &Msg, const CHexeSecurityCtx *pSecurityCtx);
		void MsgEsperOnListenerStarted (const SArchonMessage &Msg, const CHexeSecurityCtx *pSecurityCtx);
		void MsgEsperOnListenerStopped (const SArchonMessage &Msg, const CHexeSecurityCtx *pSecurityCtx);
		void MsgGetPackageList (const SArchonMessage &Msg, const CHexeSecurityCtx *pSecurityCtx);
		void MsgGetSessionList (const SArchonMessage &Msg, const CHexeSecurityCtx *pSecurityCtx);
		void MsgGetTaskList (const SArchonMessage &Msg, const CHexeSecurityCtx *pSecurityCtx);
		void MsgGetStatus (const SArchonMessage &Msg, const CHexeSecurityCtx *pSecurityCtx);
		void MsgHousekeeping (const SArchonMessage &Msg, const CHexeSecurityCtx *pSecurityCtx);
		void MsgRefresh (const SArchonMessage &Msg, const CHexeSecurityCtx *pSecurityCtx);
		void MsgResizeImage (const SArchonMessage &Msg, const CHexeSecurityCtx *pSecurityCtx);
		void MsgRunTask (const SArchonMessage &Msg, const CHexeSecurityCtx *pSecurityCtx);
		void MsgServiceMsg (const SArchonMessage &Msg, const CHexeSecurityCtx *pSecurityCtx);
		void MsgSetTaskRunOn (const SArchonMessage &Msg, const CHexeSecurityCtx *pSecurityCtx);
		void MsgStopTask (const SArchonMessage &Msg, const CHexeSecurityCtx *pSecurityCtx);

		//	Listener functions
		void ActivateListeners (void);
		bool AddListener (const CString &sProtocol, const CString &sPort, IHyperionService *pService);
		bool AddListeners (IHyperionService *pService);
		bool FindListener (const CString &sName, int *retiIndex);
		inline CString MakeListenerName (const CString &sPort) { return strPattern("Hyperion-%s", sPort); }
		void SignalListener (const CString &sName, EListenerStatus iDesiredStatus);

		//	Handler functions
		bool FindHexarcMsgService (const CString &sService, IHyperionService **retpService);
		inline bool FindHandler (const CString &sName, int *retiIndex) { return m_MsgHandlers.FindPos(sName, retiIndex); }

		CCriticalSection m_cs;
		CHyperionPackageList m_Packages;
		TSortMap<CString, SListener> m_Listeners;
		TSortMap<CString, SMsgHandler> m_MsgHandlers;
		CHyperionScheduler m_Scheduler;
		CHyperionCache m_Cache;
		bool m_bAdminNeeded;						//	TRUE if we need to create an admin account
	};
