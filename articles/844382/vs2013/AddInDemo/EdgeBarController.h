#pragma once
#include "AddInDemo_i.h"
#include "XEventHandler.h"
#include "EdgeBarDocument.h"

// {AC9C8327-445B-4C98-81ED-D96E60A0F7E2}
DEFINE_GUID(CLSID_EdgeBarController, 0xac9c8327, 0x445b, 0x4c98, 0x81, 0xed, 0xd9, 0x6e, 0x60, 0xa0, 0xf7, 0xe2);

// {52BB414E-E570-40F0-8148-6FCD43201F00}
DEFINE_GUID(CLSID_XAddInEdgeBarEvents, 0x52bb414e, 0xe570, 0x40f0, 0x81, 0x48, 0x6f, 0xcd, 0x43, 0x20, 0x1f, 0x0);

// Define a mapping from a Solid Edge document dispatch pointer to my add-in document.
typedef CTypedPtrMap<CMapPtrToPtr, SolidEdgeDocument*, CComObject<CEdgeBarDocument>*> CMapDocumentToEdgeBarPage;

// Local COM class that handles adding\removing EdgeBar pages.
class CEdgeBarController :
	public CComObjectRoot,
	public CComCoClass<CEdgeBarController, &CLSID_EdgeBarController>
{
public:
	CEdgeBarController();
	~CEdgeBarController();

	HRESULT SetAddInEx(ISEAddInEx* pAddInEx);

	BEGIN_COM_MAP(CEdgeBarController)
	END_COM_MAP()
	DECLARE_NOT_AGGREGATABLE(CEdgeBarController)

protected:
	CMapDocumentToEdgeBarPage m_pMap;
	ISEAddInExPtr m_pAddInEx;

	HRESULT AddEdgeBarPage(SolidEdgeDocument* pDocument);
	HRESULT RemoveEdgeBarPage(SolidEdgeDocument* pDocument);

protected:
	// Nested COM class that handles ISEAddInEdgeBarEvents.
	class XAddInEdgeBarEvents : public XEventHandler < ISEAddInEdgeBarEvents,
		&__uuidof(ISEAddInEdgeBarEvents),
		&LIBID_AddInDemoLib,
		XAddInEdgeBarEvents,
		&CLSID_XAddInEdgeBarEvents >
	{
	public:
		// ISEAddInEvents methods
		STDMETHOD(raw_AddPage) (LPDISPATCH theDocument);
		STDMETHOD(raw_RemovePage) (LPDISPATCH theDocument);
		STDMETHOD(raw_IsPageDisplayable) (LPDISPATCH theDocument, BSTR EnvironmentCatID, VARIANT_BOOL * vbIsPageDisplayable);

		CEdgeBarController* m_pController;
	};

	typedef CComObject<XAddInEdgeBarEvents> XAddInEdgeBarEventsObj;
	XAddInEdgeBarEventsObj* m_pAddInEdgeBarEventsObj;
};

typedef CComObject<CEdgeBarController> CEdgeBarControllerObj;