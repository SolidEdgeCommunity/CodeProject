// EdgeBarPage.cpp : implementation file
//

#include "stdafx.h"
#include "AddInDemo.h"
#include "EdgeBarPageContainer.h"
#include "EdgeBarDialog.h"

// CEdgeBarPageContainer

IMPLEMENT_DYNAMIC(CEdgeBarPageContainer, CWnd)

CEdgeBarPageContainer::CEdgeBarPageContainer()
{

}

CEdgeBarPageContainer::~CEdgeBarPageContainer()
{
}


BEGIN_MESSAGE_MAP(CEdgeBarPageContainer, CWnd)
	ON_WM_SIZE()
END_MESSAGE_MAP()



// CEdgeBarPageContainer message handlers

void CEdgeBarPageContainer::OnSize(UINT nType, int cx, int cy)
{
	CWnd::OnSize(nType, cx, cy);

	// TODO: Add your message handler code here
	CWnd *pChild = GetWindow(GW_CHILD);

	while (pChild)
	{
		pChild->MoveWindow(0, 0, cx, cy);

		// Give the dialog a shot at reorganizing its layout.
		if (pChild->IsKindOf(RUNTIME_CLASS(CEdgeBarDialog)))
		{
			CEdgeBarDialog* pDialog = (CEdgeBarDialog*)pChild;
			pDialog->OnSize(nType, cx, cy);
		}

		pChild = pChild->GetWindow(GW_HWNDNEXT);
	}
}
