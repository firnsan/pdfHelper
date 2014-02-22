#pragma once
#include "afxwin.h"


// MyDialog 对话框

class MyDialog : public CDialog
{
	DECLARE_DYNAMIC(MyDialog)

public:
	MyDialog(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~MyDialog();

// 对话框数据
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:

CString m_text;
	
	
afx_msg void OnBnClickedButton1();
afx_msg void OnBnClickedSave();
afx_msg void OnBnClickedOpen();
};
