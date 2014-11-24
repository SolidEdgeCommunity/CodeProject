#include "stdafx.h"
#include "EdgeBarDocument.h"
#include "resource.h"
//#include "EdgeBarPage.h"

CEdgeBarDocument::CEdgeBarDocument()
{
	m_pDocument = NULL;
}


CEdgeBarDocument::~CEdgeBarDocument()
{
	m_pDocument = NULL;
}

HRESULT CEdgeBarDocument::CreateEdgeBarPage(ISolidEdgeBarEx* pEdgeBarEx, SolidEdgeDocument* pDocument)
{
	HWND hWndEdgeBarPage = 0;
	//CWnd* hWndEdgeBarPage = NULL;
	m_pDocument = pDocument;

	// Build path to .dll that contains the resources.
	HINSTANCE hInstance = AfxGetResourceHandle();
	TCHAR ResourceFilename[MAX_PATH];
	GetModuleFileName(hInstance, ResourceFilename, sizeof(ResourceFilename));

	CString strTooltip;
	strTooltip = L"";
	_bstr_t bstrTooltip = strTooltip;

	hWndEdgeBarPage = (HWND)pEdgeBarEx->AddPageEx(pDocument, ResourceFilename, IDB_EDGEBAR, bstrTooltip, 2);

	if (hWndEdgeBarPage)
	{
		// Get RECT of newly created EdgeBar page.
		RECT rect;
		::GetWindowRect(hWndEdgeBarPage, &rect);

		// Create a new container window and make it a child of the newly created EdgeBar page.
		m_pEdgeBarPageContainer = new CEdgeBarPageContainer();
		m_pEdgeBarPageContainer->CreateEx(0, _T("STATIC"), NULL, WS_VISIBLE | WS_CHILD, 0, 0, rect.right - rect.left, rect.bottom - rect.top, hWndEdgeBarPage, NULL, NULL);

		// Create a new dialog and make it a child of the new container window.
		m_pDialog = new CEdgeBarDialog();
		m_pDialog->Create(IDD_EDGEBARDIALOG, m_pEdgeBarPageContainer);
		m_pDialog->MoveWindow(0, 0, rect.right - rect.left, rect.bottom - rect.top);
		m_pDialog->ShowWindow(SW_SHOW);
	}

	return S_OK;
}

HRESULT CEdgeBarDocument::DeleteEdgeBarPage(ISolidEdgeBarEx* pEdgeBarEx, SolidEdgeDocument* pDocument)
{
	HRESULT hr = S_OK;
	HWND hWndEdgeBarPage = ::GetParent(m_pEdgeBarPageContainer->m_hWnd);

	hr = pEdgeBarEx->RemovePage(pDocument, (LONG)hWndEdgeBarPage, 0);

	delete m_pDialog;
	m_pDialog = NULL;

	delete m_pEdgeBarPageContainer;
	m_pEdgeBarPageContainer = NULL;

	return S_OK;
}