// FE3Dlg.h : header file
//

#if !defined(AFX_FE3DLG_H__B67EBB1A_52E3_4441_9609_5AA8F87EFAEA__INCLUDED_)
#define AFX_FE3DLG_H__B67EBB1A_52E3_4441_9609_5AA8F87EFAEA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CFE3Dlg dialog
#include "gamestart.h"
#include "boom.h"
class CFE3Dlg : public CDialog
{
// Construction
public:
	CFE3Dlg(CWnd* pParent = NULL);	// standard constructor
	chapter f;
	boom boom;
	int count;
	int stage;
	int ms;//max stage
// Dialog Data
	//{{AFX_DATA(CFE3Dlg)
	enum { IDD = IDD_FE3_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFE3Dlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CFE3Dlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FE3DLG_H__B67EBB1A_52E3_4441_9609_5AA8F87EFAEA__INCLUDED_)
