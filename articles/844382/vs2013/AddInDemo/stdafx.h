// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently

#pragma once

#define _ATL_APARTMENT_THREADED 
#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN            // Exclude rarely-used stuff from Windows headers
#endif

#include "targetver.h"

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS      // some CString constructors will be explicit

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions

#ifndef _AFX_NO_OLE_SUPPORT
#include <afxole.h>         // MFC OLE classes
#include <afxodlgs.h>       // MFC OLE dialog classes
#include <afxdisp.h>        // MFC Automation classes
#endif // _AFX_NO_OLE_SUPPORT

#ifndef _AFX_NO_DB_SUPPORT
#include <afxdb.h>                      // MFC ODBC database classes
#endif // _AFX_NO_DB_SUPPORT

#ifndef _AFX_NO_DAO_SUPPORT
#include <afxdao.h>                     // MFC DAO database classes
#endif // _AFX_NO_DAO_SUPPORT

#ifndef _AFX_NO_OLE_SUPPORT
#include <afxdtctl.h>           // MFC support for Internet Explorer 4 Common Controls
#endif
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>                     // MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT

#include <atlbase.h>
#include <atlcom.h>

//#include <atlctl.h> // Remark this line out due to ambiguous CDialogImpl error.
#include <afxcontrolbars.h> // Added by Dialog -> Add Class wizard

#pragma region Solid Edge specific

#include <atlsafe.h>
#include <initguid.h> // Necessary for secatids.h.
#include "secatids.h" // C:\Program Files\Solid Edge ST7\SDK\Advanced\include (Extract from DVD)

// SolidEdgeConstants
#import "constant.tlb"

//SolidEdgeFramework
#import "framewrk.tlb" exclude ("UINT_PTR", "LONG_PTR") rename ("GetOpenFileName", "SEGetOpenFileName")

// SolidEdgeGeometry
#import "geometry.tlb"

// SolidEdgeFrameworkSupport
#import "fwksupp.tlb"

// SolidEdgePart
#import "part.tlb"

// SolidEdgeAssembly
#import "assembly.tlb"

// SolidEdgeDraft
#import "draft.tlb"

// SEInstallDataLib
#import "SEInstallData.dll"

using namespace SolidEdgeFramework;

#define IfFailGo(x) { hr=(x); if (FAILED(hr)) goto Error; }
#define IfFailGoCheck(x, p) { hr=(x); if (FAILED(hr)) goto Error; if(!p) {hr = E_FAIL; goto Error; } }

#pragma endregion