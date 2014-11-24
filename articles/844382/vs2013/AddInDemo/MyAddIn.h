// MyAddIn.h : Declaration of the CMyAddIn

#pragma once
#include "resource.h"       // main symbols
#include "AddInDemo_i.h"
#include "EdgeBarController.h"

#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "Single-threaded COM objects are not properly supported on Windows CE platform, such as the Windows Mobile platforms that do not include full DCOM support. Define _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA to force ATL to support creating single-thread COM object's and allow use of it's single-threaded COM object implementations. The threading model in your rgs file was set to 'Free' as that is the only threading model supported in non DCOM Windows CE platforms."
#endif

using namespace ATL;

// {8C5A128C-4BA6-4840-97F9-124EBEB1410E}
DEFINE_GUID(CLSID_MyAddIn, 0x8c5a128c, 0x4ba6, 0x4840, 0x97, 0xf9, 0x12, 0x4e, 0xbe, 0xb1, 0x41, 0xe);

// CMyAddIn

class ATL_NO_VTABLE CMyAddIn :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CMyAddIn, &CLSID_MyAddIn>,
	public ISolidEdgeAddIn
	{
	public:
		CMyAddIn()
		{
		}

		DECLARE_REGISTRY_RESOURCEID(IDR_MYADDIN)

		BEGIN_COM_MAP(CMyAddIn)
			COM_INTERFACE_ENTRY(ISolidEdgeAddIn)
		END_COM_MAP()



		DECLARE_PROTECT_FINAL_CONSTRUCT()

		HRESULT FinalConstruct()
		{
			return S_OK;
		}

		void FinalRelease()
		{
		}

	public:
#pragma region ISolidEdgeAddIn

		STDMETHOD(raw_OnConnection) (LPDISPATCH Application, SolidEdgeFramework::SeConnectMode ConnectMode, SolidEdgeFramework::AddIn * AddInInstance);
		STDMETHOD(raw_OnConnectToEnvironment) (BSTR EnvCatID, LPDISPATCH pEnvironmentDispatch, VARIANT_BOOL bFirstTime);
		STDMETHOD(raw_OnDisconnection) (SolidEdgeFramework::SeDisconnectMode DisconnectMode);

#pragma endregion
	private:
		ISEAddInExPtr m_pAddInEx;
		CEdgeBarControllerObj* m_pEdgeBarController;
	};

OBJECT_ENTRY_AUTO(CLSID_MyAddIn, CMyAddIn)
