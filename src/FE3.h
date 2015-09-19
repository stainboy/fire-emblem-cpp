// FE3.h : main header file for the FE3 application
//

#if !defined(AFX_FE3_H__793EA536_910E_4499_86E8_3E255E21A9E8__INCLUDED_)
#define AFX_FE3_H__793EA536_910E_4499_86E8_3E255E21A9E8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CFE3App:
// See FE3.cpp for the implementation of this class
//

class CFE3App : public CWinApp
{
public:
	CFE3App();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFE3App)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CFE3App)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FE3_H__793EA536_910E_4499_86E8_3E255E21A9E8__INCLUDED_)
