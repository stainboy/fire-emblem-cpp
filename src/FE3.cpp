// FE3.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "FE3.h"
#include "FE3Dlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFE3App

BEGIN_MESSAGE_MAP(CFE3App, CWinApp)
	//{{AFX_MSG_MAP(CFE3App)
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFE3App construction

CFE3App::CFE3App()
{
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CFE3App object

CFE3App theApp;

/////////////////////////////////////////////////////////////////////////////
// CFE3App initialization

BOOL CFE3App::InitInstance()
{
	// Standard initialization

	CFE3Dlg dlg;
	m_pMainWnd = &dlg;
	int nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
	}
	else if (nResponse == IDCANCEL)
	{
	}

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}
