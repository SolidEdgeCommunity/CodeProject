#pragma once
#include "stdafx.h"

template <class IEvents, const IID* piidEvents, const GUID* plibid, class XEvents, const CLSID* pClsidEvents>
class XEventHandler :
	public CComDualImpl<IEvents, piidEvents, plibid>,
	public CComObjectRoot,
	public CComCoClass<XEvents, pClsidEvents>
{
public:
	BEGIN_COM_MAP(XEvents)
		COM_INTERFACE_ENTRY_IID(*piidEvents, IEvents)
	END_COM_MAP()
	DECLARE_NOT_AGGREGATABLE(XEvents)
	HRESULT Connect(IUnknown* pUnk)
	{
		HRESULT hr; VERIFY(SUCCEEDED(hr = AtlAdvise(pUnk, this, *piidEvents, &m_dwAdvise))); return hr;
	}
	HRESULT Disconnect(IUnknown* pUnk)
	{
		HRESULT hr; VERIFY(SUCCEEDED(hr = AtlUnadvise(pUnk, *piidEvents, m_dwAdvise))); return hr;
	}

	// Store a back pointer to the embedding command object (makes life easy).
	// Do not delete! Its merely a back pointer to the object that controls the
	// lifetime of your event handlers. Use this pointer in the event handling methods 
	// based on this object template to communicate to the embedding class (CCommands).

	//CCommands* m_pCommands;

protected:
	DWORD m_dwAdvise;
};