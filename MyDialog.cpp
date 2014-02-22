// MyDialog.cpp : 实现文件
//

#include "stdafx.h"
#include "阅读助手.h"
#include "MyDialog.h"


// MyDialog 对话框

IMPLEMENT_DYNAMIC(MyDialog, CDialog)

MyDialog::MyDialog(CWnd* pParent /*=NULL*/)
	: CDialog(MyDialog::IDD, pParent)
	, m_text(_T(""))
{
	CString strFileTitle="data\\temp.txt";		//ocr软件识别出来的文本
	CFileFind finder;
	int i=1;
	while(!finder.FindFile(strFileTitle))
	{   if (i>5) 
			{AfxMessageBox("Temp file not found");exit(0);}
		i++;
		Sleep(500);
	}
	CStdioFile myFile;
	myFile.Open("data\\temp.txt",CFile::typeText|CFile::modeRead);
	CString strRead;
	while(myFile.ReadString(strRead))
	{
		m_text+=strRead;
		m_text+="\r\n";
	}
	myFile.Close();
	//UpdateData(FALSE);

}

MyDialog::~MyDialog()
{
	CString strFileTitle="data\\temp.txt";
	CFileFind finder;
	CStdioFile myFile;
	if(!finder.FindFile(strFileTitle))
		return;
	DeleteFile("data\\temp.txt");	//删除本次的临时文本

}

void MyDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Text(pDX,IDC_EDIT1,m_text);
}


BEGIN_MESSAGE_MAP(MyDialog, CDialog)
	
	ON_BN_CLICKED(IDC_BUTTON1, &MyDialog::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_SAVE, &MyDialog::OnBnClickedSave)
	ON_BN_CLICKED(IDC_OPEN, &MyDialog::OnBnClickedOpen)
END_MESSAGE_MAP()


// MyDialog 消息处理程序



void MyDialog::OnBnClickedButton1()		//复制文本框的内容到剪切板
{
	UpdateData();
	if (OpenClipboard()) 
	{

		HGLOBAL hmem=GlobalAlloc(GHND,strlen(m_text)+1);
		CString *pmem=(CString *)GlobalLock(hmem);

		EmptyClipboard();
		memcpy(pmem,m_text,strlen(m_text)+1);
		//GlobalUnlock(hmem);

		SetClipboardData(CF_TEXT,hmem);
		CloseClipboard();
		GlobalFree(hmem); 
	}
	CDialog::OnCancel();
}

void MyDialog::OnBnClickedSave() 
{
	// TODO: 在此添加控件通知处理程序代码
	CString name,newpath,totalpath,cmd;
	
	//获取系统时间
	CTime tm;
	tm=CTime::GetCurrentTime();
	name=tm.Format("%Y%m%d%X");
	name.Remove('\:');
	name+=".jpg";
	
	newpath="picture\\";
	newpath+=name;

	CreateDirectory("picture", NULL);
	CopyFile("data\\temp.jpg",newpath, FALSE);

}

void MyDialog::OnBnClickedOpen()	//打开图片目录
{
	// TODO: 在此添加控件通知处理程序代码
	CString totalpath;

    TCHAR strExePath[MAX_PATH]; GetCurrentDirectory(MAX_PATH, strExePath);

	totalpath=strExePath;
	totalpath+="\\picture\\";
	
	ShellExecute(NULL, "open", "explorer.exe", totalpath, NULL, SW_SHOWNORMAL);
	CDialog::OnCancel();
}
