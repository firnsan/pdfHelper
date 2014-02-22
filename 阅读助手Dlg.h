// ÔÄ¶ÁÖúÊÖDlg.h : header file
//

#if !defined(AFX_DLG_H__390E288A_AD37_4402_AE13_3BA7399D8275__INCLUDED_)
#define AFX_DLG_H__390E288A_AD37_4402_AE13_3BA7399D8275__INCLUDED_


#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CMyDlg dialog

class CMyDlg : public CDialog
{
// Construction
public:
	CMyDlg(CWnd* pParent = NULL);	// standard constructor
	int m_xScreen;
	int m_yScreen;
	
	CPoint m_startPt;
	HCURSOR m_hCursor;
	CBitmap *m_pBitmap;
    CRectTracker m_rectTracker;
	CRgn m_rgn;
	BOOL m_bFirstDraw;
	BOOL m_bDraw;
	BOOL m_bQuit;


public:
	void ToTray();
	void DeleteTray();
	HBITMAP CopyScreenToBitmap(LPRECT lpRect,BOOL bSave=FALSE);
    void DrawMessage();
	afx_msg LRESULT OnHotKey(WPARAM wParam,LPARAM lParam);

// Dialog Data
	//{{AFX_DATA(CMyDlg)
	enum { IDD = IDD_MY_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CMyDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	virtual void OnCancel();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
    afx_msg LRESULT OnShowTask(WPARAM wParam,LPARAM lParam) ;

	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnCloseMe();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnClose();
	afx_msg void OnCloseit();
	afx_msg void OnAboutit();
	afx_msg void OnHelp();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLG_H__390E288A_AD37_4402_AE13_3BA7399D8275__INCLUDED_)
