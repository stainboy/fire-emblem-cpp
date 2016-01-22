// FE3Dlg.cpp : implementation file
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
// CFE3Dlg dialog

CFE3Dlg::CFE3Dlg(CWnd* pParent /*=NULL*/)
	: CDialog(CFE3Dlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CFE3Dlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CFE3Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFE3Dlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CFE3Dlg, CDialog)
	//{{AFX_MSG_MAP(CFE3Dlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_TIMER()
	ON_WM_KEYDOWN()
	ON_WM_CLOSE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFE3Dlg message handlers

BOOL CFE3Dlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	MoveWindow(0,0,518,512);
	ShowCursor(false);

	stage=1;
	count=0;
	ms=2;
	f.hwnd=this;
//	boom.init(IDR_EXE1);
	f.init();
	f.start(stage);
	SetTimer(1,200,0);
	SetTimer(2,200,0);
	SetTimer(3,20,0);
	SetTimer(4,100,0);
	SetTimer(5,800,0);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CFE3Dlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

HCURSOR CFE3Dlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CFE3Dlg::OnTimer(UINT nIDEvent) 
{
	f.timer(nIDEvent);
	if(nIDEvent == 4)
	{
		rand();
		if(f.mhead==0)
		{
			f.win();
			stage++;
			if(stage>ms)
			{
				f.fin();
				PostMessage(WM_CLOSE);
			}
			f.start(stage);
		}
		if(f.hhead==0)
			{f.loss();f.start(stage);}
	}
	if(nIDEvent == 5)count=0;
		
	CDialog::OnTimer(nIDEvent);
}

void CFE3Dlg::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	f.keyChar=nChar;
	f.keydown();
	if(nChar == VK_SPACE)
	{
		if(count == 0)count++;
		else if(count == 1)count++;
		else if(count == 2)count++;
		else if(count == 3)
		{
			count=0;
			f.win();
			stage++;
			if(stage>ms)
			{
				f.fin();
				PostMessage(WM_CLOSE);
			}
			f.start(stage);
		}
	}
	CDialog::OnKeyDown(nChar, nRepCnt, nFlags);
}
