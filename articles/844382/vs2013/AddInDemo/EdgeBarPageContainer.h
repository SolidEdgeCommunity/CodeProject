#pragma once


// CEdgeBarPageContainer

class CEdgeBarPageContainer : public CWnd
{
	DECLARE_DYNAMIC(CEdgeBarPageContainer)

public:
	CEdgeBarPageContainer();
	virtual ~CEdgeBarPageContainer();

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
};


