// MyAddIn.cpp : Implementation of CMyAddIn

#include "stdafx.h"
#include "MyAddIn.h"

// CMyAddIn
#pragma region ISolidEdgeAddIn

STDMETHODIMP CMyAddIn::raw_OnConnection(IDispatch *pAppDispatch, SolidEdgeFramework::SeConnectMode ConnectMode, SolidEdgeFramework::AddIn* pAddIn)
{
	HRESULT hr = S_OK;

	// Store smart pointer to addin. Note that the smart pointer is QueryInferface()'ing for ISEAddInEx.
	m_pAddInEx = pAddIn;

	// Create instance of CEdgeBarController.
	hr = CEdgeBarControllerObj::CreateInstance(&m_pEdgeBarController);

	if (SUCCEEDED(hr))
	{
		// Manually AddRef() our local CEdgeBarController COM object.
		m_pEdgeBarController->AddRef();

		// Pass the ISEAddInEx pointer to the CEdgeBarController.
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
		// Disconnect the CEdgeBarController by passing NULL.
		hr = m_pEdgeBarController->SetAddInEx(NULL);

		// Manually Release() our local CEdgeBarController COM object.
		m_pEdgeBarController->Release();

		m_pEdgeBarController = NULL;
	}

	return S_OK;
}

#pragma endregion

