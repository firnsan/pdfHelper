#pragma once
#include "afxwin.h"


// MyDialog �Ի���

class MyDialog : public CDialog
{
	DECLARE_DYNAMIC(MyDialog)

public:
	MyDialog(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~MyDialog();

// �Ի�������
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:

CString m_text;
	
	
afx_msg void OnBnClickedButton1();
afx_msg void OnBnClickedSave();
afx_msg void OnBnClickedOpen();
};
