// MyAddIn.cpp : Implementation of CMyAddIn

#include "stdafx.h"
#include "MyAddIn.h"

// CMyAddIn
#pragma region ISolidEdgeAddIn

STDMETHODIMP CMyAddIn::raw_OnConnection(IDispatch *pAppDispatch, SolidEdgeFramework::SeConnectMode ConnectMode, SolidEdgeFramework::AddIn* pAddIn)
{
	HRESULT hr = S_OK;

	m_pAddInEx = pAddIn;

	hr = CEdgeBarControllerObj::CreateInstance(&m_pEdgeBarController);

	if (SUCCEEDED(hr))
	{
		m_pEdgeBarController->AddRef();
		hr = m_pEdgeBarController->SetAddInEx(m_pAddInEx);
	}

	return S_OK;
}

STDMETHODIMP CMyAddIn::raw_OnConnectToEnvironment(BSTR EnvironmentCatid, LPDISPATCH pEnvironment, VARIANT_BOOL bFirstTime)
{
	return S_OK;
}

STDMETHODIMP CMyAddIn::raw_OnDisconnection(SolidEdgeFramework::SeDisconnectMode DisconnectMode)
{
	HRESULT hr = S_OK;

	if (m_pEdgeBarController != NULL)
	{
		hr = m_pEdgeBarController->SetAddInEx(NULL);
		m_pEdgeBarController->Release();
		m_pEdgeBarController = NULL;
	}

	return S_OK;
}

#pragma endregion

