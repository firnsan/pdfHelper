// �Ķ�����Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "�Ķ�����.h"
#include "�Ķ�����Dlg.h"
#include <atlimage.h>
#include "MyDialog.h"

#define WM_SHOWTASK (WM_USER +1)
#define ID_CLOSEME 3001

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyDlg dialog

CMyDlg::CMyDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMyDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMyDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32

    m_rectTracker.m_nStyle=CRectTracker::resizeInside|CRectTracker::solidLine;
	m_rectTracker.m_rect.SetRect(-1,-1,-1,-1);
    m_bDraw=FALSE;
	m_bFirstDraw=FALSE;
	m_bQuit=FALSE;
    m_startPt=0;
	m_xScreen=GetSystemMetrics(SM_CXSCREEN);
	m_yScreen=GetSystemMetrics(SM_CYSCREEN);

	//CRect rect(0,0,m_xScreen,m_yScreen);
	//m_pBitmap=CBitmap::FromHandle(CopyScreenToBitmap(&rect));
	m_pBitmap=CBitmap::FromHandle(CopyScreenToBitmap(CRect(0,0,m_xScreen,m_yScreen)));

	m_rgn.CreateRectRgn(0,0,50,50);
	
    m_hCursor=AfxGetApp()->LoadCursor(IDC_CURSOR1);


///////////////////////////////////////////////////////////////////////////
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMyDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMyDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CMyDlg, CDialog)
	//{{AFX_MSG_MAP(CMyDlg)
 ON_MESSAGE(WM_HOTKEY,OnHotKey)
 ON_MESSAGE(WM_SHOWTASK,OnShowTask)
// ON_COMMAND(ID_CLOSEME,0nCloseMe)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_RBUTTONDOWN()
	ON_WM_ERASEBKGND()
	ON_WM_SETCURSOR()
	//}}AFX_MSG_MAP
    
	ON_WM_SYSCOMMAND()
	ON_WM_CLOSE()
	ON_COMMAND(ID_CLOSEIT, &CMyDlg::OnCloseit)
	ON_COMMAND(ID_ABOUTIT, &CMyDlg::OnAboutit)
	ON_COMMAND(ID_HELP, &CMyDlg::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyDlg message handlers

BOOL CMyDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	
	RegisterHotKey(m_hWnd,1000,MOD_SHIFT,VK_F1);

	SetWindowPos(&wndTopMost,0,0,m_xScreen,m_yScreen,SWP_SHOWWINDOW);
	ShowWindow(SW_MINIMIZE );

	((CMyApp *)AfxGetApp())->m_hwndDlg=m_hWnd;

	ToTray();

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMyDlg::OnPaint() 
{
	//PaintWindow();

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
 
		//DrawMessage();//�����������˸
		if(m_bFirstDraw)
		{
		   CPaintDC dc(this);
			m_rectTracker.Draw(&dc);
		   DrawMessage();

		}
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CMyDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CMyDlg::OnCancel() 
{
	// TODO: Add extra cleanup here
	
	if(m_bFirstDraw)
	{
		m_bFirstDraw=FALSE;
		m_bDraw=FALSE;
		m_rectTracker.m_rect.SetRect(-1,-1,-1,-1);
		//PaintWindow();
		Invalidate();
	}
	else
	{
      
		ShowWindow(SW_MINIMIZE );    
	 //else  CDialog::OnCancel();
	}
}

void CMyDlg::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	//PaintWindow();
  
	int nHitTest;
	nHitTest=m_rectTracker.HitTest(point);
	Invalidate();
	if(nHitTest<0)
	{
		if(!m_bFirstDraw)
		{
			m_startPt=point;
			m_bDraw=TRUE;
			Invalidate();
		}
	}
	else
	{
		m_rectTracker.Track(this,point,TRUE);
		SendMessage(WM_LBUTTONUP,NULL,NULL);
	   Invalidate();
	}
	CDialog::OnLButtonDown(nFlags, point);
}

void CMyDlg::OnLButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	m_bDraw=FALSE;

	Invalidate();
	CDialog::OnLButtonUp(nFlags, point);
}

void CMyDlg::OnMouseMove(UINT nFlags, CPoint point) 
{

	// TODO: Add your message handler code here and/or call default
   
	Invalidate();//ˢ��,����onpaint()������ʾ
	if(m_bDraw)
	   {
		m_rectTracker.m_rect.SetRect(m_startPt.x+1,m_startPt.y+1,point.x,point.y);
		m_bFirstDraw=TRUE;
		
	   }
	CDialog::OnMouseMove(nFlags, point);
}

void CMyDlg::OnLButtonDblClk(UINT nFlags, CPoint point) 
{
Invalidate();
	// TODO: Add your message handler code here and/or call default
	int nHitTest;
	nHitTest=m_rectTracker.HitTest(point);
	
	if(nHitTest==8)
	{
		CopyScreenToBitmap(m_rectTracker.m_rect,TRUE);
        MyDialog dlg;
        
        m_rectTracker.m_rect.SetRect(-1,-1,-1,-1);
               Invalidate();
        m_bFirstDraw=FALSE;
	    dlg.DoModal();
		ShowWindow(SW_MINIMIZE );
		//PostQuitMessage(0);

	}
	CDialog::OnLButtonDblClk(nFlags, point);
}

void CMyDlg::OnRButtonDown(UINT nFlags, CPoint point) 
{

	Invalidate();
	// TODO: Add your message handler code here and/or call default
	if(m_bFirstDraw)
	{
		//����Ѿ���ȡ���������ȡ����
		m_bFirstDraw=FALSE;
		m_rectTracker.m_rect.SetRect(-1,-1,-1,-1);
		Invalidate();
	}
	else
	{
		
		//ShowWindow(SW_MINIMIZE );
 ShowWindow(SW_MINIMIZE );
		//PostQuitMessage(0);
	}
	CDialog::OnRButtonDown(nFlags, point);
}

BOOL CMyDlg::OnEraseBkgnd(CDC* pDC) 
{
	// TODO: Add your message handler code here and/or call default


	BITMAP bmp;
	m_pBitmap->GetBitmap(&bmp);

	CDC dcCompatible;
	dcCompatible.CreateCompatibleDC(pDC);
	dcCompatible.SelectObject(m_pBitmap);

	CRect rect;
	GetClientRect(&rect);


	pDC->BitBlt(0,0,rect.Width(),rect.Height(),&dcCompatible,0,0,SRCCOPY);
	/*
	COLORREF pix;
		BYTE r,g,b,rgb;
		for(int x=0;x<=rect.Width();x++)
		{
			for(int y=0;y<=rect.Height();y++)
			{
				pix=pDC->GetPixel(x,y);
				r=GetRValue(pix);
				g=GetGValue(pix);
				b=GetBValue(pix);
	           rgb=max(r,max(g,b));
	           pDC->SetPixel(x,y,RGB(rgb,rgb,rgb));
			}
		}
	*/

	if(!m_bFirstDraw)DrawMessage();
	return TRUE;
	//return CDialog::OnEraseBkgnd(pDC);
}


HBITMAP CMyDlg::CopyScreenToBitmap(LPRECT lpRect,BOOL bSave)
	//lpRect ����ѡ������
{
	HDC hScrDC, hMemDC;      
	// ��Ļ���ڴ��豸������
	HBITMAP hBitmap, hOldBitmap;   
	// λͼ���
	int nX, nY, nX2, nY2;      
	// ѡ����������
	int nWidth, nHeight;
	
	// ȷ��ѡ������Ϊ�վ���
	if (IsRectEmpty(lpRect))
		return NULL;
	//Ϊ��Ļ�����豸������
	hScrDC = CreateDC("DISPLAY", NULL, NULL, NULL);
	
	//Ϊ��Ļ�豸�����������ݵ��ڴ��豸������
	hMemDC = CreateCompatibleDC(hScrDC);
	// ���ѡ����������
	nX = lpRect->left;
	nY = lpRect->top;
	nX2 = lpRect->right;
	nY2 = lpRect->bottom;
	
	//ȷ��ѡ�������ǿɼ���
	if (nX < 0)
		nX = 0;
	if (nY < 0)
		nY = 0;
	if (nX2 > m_xScreen)
		nX2 = m_xScreen;
	if (nY2 > m_yScreen)
		nY2 = m_yScreen;
	nWidth = nX2 - nX;
	nHeight = nY2 - nY;
	// ����һ������Ļ�豸��������ݵ�λͼ
	hBitmap = CreateCompatibleBitmap
		(hScrDC, nWidth, nHeight);
	// ����λͼѡ���ڴ��豸��������
	hOldBitmap = (HBITMAP)SelectObject(hMemDC, hBitmap);
	// ����Ļ�豸�����������ڴ��豸��������
	if(bSave)
	{
		CDC dcCompatible;
		dcCompatible.CreateCompatibleDC(CDC::FromHandle(hMemDC));
		dcCompatible.SelectObject(m_pBitmap);
        
		BitBlt(hMemDC, 0, 0, nWidth, nHeight,
			dcCompatible, nX, nY, SRCCOPY);
		
	}
	else
	{
		BitBlt(hMemDC, 0, 0, nWidth, nHeight,
			hScrDC, nX, nY, SRCCOPY);
	}
	
	hBitmap = (HBITMAP)SelectObject(hMemDC, hOldBitmap);
	//�õ���Ļλͼ�ľ��
	//��� 
	DeleteDC(hScrDC);
	DeleteDC(hMemDC);
	// ����λͼ���
	if(bSave)
	{		
		CImage img;
		img.Attach(hBitmap);
		img.Save("data\\temp.jpg");
		STARTUPINFO   startupInfo;
		memset(&startupInfo,0,sizeof(STARTUPINFO));
		startupInfo.cb = sizeof(STARTUPINFO);

		startupInfo.dwFlags |= STARTF_USESHOWWINDOW;
		startupInfo.wShowWindow = SW_SHOWMAXIMIZED;

		//����ocr���, ʶ��սص�ͼ
		PROCESS_INFORMATION ProcessInfo;
		BOOL bCreate = CreateProcess
			(
			"data\\th.exe",
			"data\\th.exe data\\temp.jpg",
			NULL,
			NULL,
			FALSE,
			0,
			NULL,
			NULL,
			&startupInfo,
			&ProcessInfo); 

		if(!bCreate)
			{AfxMessageBox("run ocr error");exit(0);}
	
	}
	return hBitmap;
}


BOOL CMyDlg::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message) 
{
	// TODO: Add your message handler code here and/or call default
	if (pWnd == this && m_rectTracker.SetCursor(this, nHitTest)) 
    {
		
		return TRUE; 
	}
	else
	{
		//���ò�ɫ���
		SetCursor(m_hCursor);
		return TRUE;
	}

	return CDialog::OnSetCursor(pWnd, nHitTest, message);
}

LRESULT CMyDlg::OnHotKey(WPARAM wParam,LPARAM lParam)
{
	//wParam��ע���ȼ���ID��lParam�ǹ��ڰ�������Ϣ
	if(wParam==1000)
	{  
		m_pBitmap=CBitmap::FromHandle(CopyScreenToBitmap(CRect(0,0,m_xScreen,m_yScreen)));
		ShowWindow(SW_MAXIMIZE);
  
        m_rectTracker.m_rect.SetRect(-1,-1,-1,-1);
       
	}	
		return 0;
}

void CMyDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	if(nID==SC_RESTORE)
	{
		//AfxMessageBox("aaa");
		m_pBitmap=CBitmap::FromHandle(CopyScreenToBitmap(CRect(0,0,m_xScreen,m_yScreen)));
	}
	CDialog::OnSysCommand(nID, lParam);
}


void CMyDlg::DrawMessage()
{
	const int space=3;

	//����������ɫ��С
	CClientDC DC(this);
	CPoint pt;
	CPen pen(PS_SOLID,1,RGB(147,147,147));
	DC.SetTextColor(RGB(147,147,147));
	CFont font;
	font.CreatePointFont(90,"����");
	DC.SelectObject(&font);

	//�õ������Ⱥ͸߶�
	GetCursorPos(&pt);
	DC.SetBkMode(TRANSPARENT);
	TEXTMETRIC tm;
	int charHeight;
	CSize size;
	int	lineLength;
	DC.GetTextMetrics(&tm);
	charHeight = tm.tmHeight+tm.tmExternalLeading;
	size=DC.GetTextExtent(" �����Ҽ�����/�뿪��ͼ    ",strlen(" �����Ҽ�����/�뿪��ͼ    "));
	lineLength=size.cx;

	//��ʼ������, �Ա�֤д����������
	CRect rect1(pt.x+space,pt.y-charHeight*6-space,pt.x+lineLength+space,pt.y-space);

	//�����ջ�ˢ������
	DC.SelectObject((HBRUSH)GetStockObject(NULL_BRUSH));
	DC.Rectangle(rect1);
	rect1.top+=2;
	//�ھ�������ʾ����

	CString string("    �Ķ�����(Shift+F1)  ");
	DC.TextOut(rect1.left,rect1.top,string);

	string=" ";
	DC.TextOut(rect1.left,rect1.top+charHeight,string);

	string=" ˫����ɽ�ͼ��ʶ������  ";
	DC.TextOut(rect1.left,rect1.top+charHeight*2,string);

	string=" ����'ESC'�뿪��ͼ";
	DC.TextOut(rect1.left,rect1.top+charHeight*4,string);

	string=" �����Ҽ�����/�뿪��ͼ  ";
	DC.TextOut(rect1.left,rect1.top+charHeight*3,string);

}

void CMyDlg::ToTray()
{    
	NOTIFYICONDATA nid;     
	nid.cbSize=(DWORD)sizeof(NOTIFYICONDATA);     
	nid.hWnd=this->m_hWnd;     
	nid.uID=IDR_MAINFRAME;     
	nid.uFlags=nid.uFlags=NIF_ICON|NIF_MESSAGE|NIF_TIP|NIF_INFO;
	nid.uCallbackMessage=WM_SHOWTASK;
	nid.hIcon=LoadIcon(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDR_MAINFRAME)); 
	strcpy(nid.szTip,"�Ķ�����");  //��Ϣ��ʾ��  

	strcpy(nid.szInfo,_T("�Ķ�����"));
	strcpy(nid.szInfoTitle,_T("����'Shift+F1'���Դ���Ŷ"));
	nid.dwInfoFlags=NIIF_INFO;
	nid.uTimeout=500;  

	Shell_NotifyIcon(NIM_ADD,&nid);    //�����������ͼ��     
	//ShowWindow(SW_HIDE);    //����������
}

void CMyDlg::OnCloseMe() 
{
	//AfxMessageBox("test");
	OnClose();

}



LRESULT CMyDlg::OnShowTask(WPARAM wParam,LPARAM lParam)
{     
	if(wParam!=IDR_MAINFRAME)        
		return 1; 
	switch(lParam)     
	{            
	case WM_RBUTTONUP://�Ҽ�����ʱ������ݲ˵�������ֻ��һ�����رա�       
	  { 
		LPPOINT lpoint=new tagPOINT;    
		::GetCursorPos(lpoint);		//�õ����λ��          
		CMenu menu;      
		menu.CreatePopupMenu();		//����һ������ʽ�˵�        
		 
		menu.AppendMenu(MF_STRING,ID_HELP,"����..."); 
		menu.AppendMenu(MF_STRING,ID_ABOUTIT,"����..."); 
		menu.AppendMenu(MF_SEPARATOR);
		menu.AppendMenu(MF_STRING,ID_CLOSEIT,"�˳����");
		
		//ȷ������ʽ�˵���λ��           
		menu.TrackPopupMenu(TPM_LEFTALIGN,lpoint->x,lpoint->y,this);     
		
		//��Դ����            
		HMENU hmenu=menu.Detach();      
		menu.DestroyMenu();          
		delete lpoint;     
	  }           
	  break;     
	case WM_LBUTTONDBLCLK:		//˫������Ĵ���    
		{         
			this->ShowWindow(SW_SHOW);//�򵥵���ʾ���������¶�      
			//DeleteTray();    
		}          
		break;       
	default:         
		break;   
	}    
	return 0;
} 
void CMyDlg::OnClose()
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if(MessageBox("ȷ��Ҫ�˳������","�Ķ�����" ,MB_ICONEXCLAMATION|MB_YESNO)!=IDNO)
	{
		DeleteTray();
		DestroyWindow();
	}
}

void CMyDlg::DeleteTray()
{ 
	NOTIFYICONDATA nid;  
	nid.cbSize=(DWORD)sizeof(NOTIFYICONDATA); 
	nid.hWnd=this->m_hWnd; 
	nid.uID=IDR_MAINFRAME; 
	nid.uFlags=NIF_ICON|NIF_MESSAGE|NIF_TIP ;  
	nid.uCallbackMessage=WM_SHOWTASK;//�Զ������Ϣ����  
	nid.hIcon=LoadIcon(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDR_MAINFRAME)); 
	strcpy(nid.szTip,"�Ķ�����");  
	Shell_NotifyIcon(NIM_DELETE,&nid);    //��������ɾ��ͼ�� 
	
}
void CMyDlg::OnCloseit()
{
	OnClose();
	// TODO: �ڴ���������������
}

void CMyDlg::OnAboutit()
{
	// TODO: �ڴ���������������
	MessageBox("�Ķ����� V0.01","�Ķ�����" ,MB_ICONEXCLAMATION|MB_OKCANCEL);
}

void CMyDlg::OnHelp()
{
	// TODO: �ڴ���������������
    MessageBox(" ����'Shift+F1'�򿪽�ͼ����\r\n��ͼʱ,˫�����'���'��ɽ�ͼ,�Զ�ʶ��ͼ������\r\n����'�Ҽ�'���½�ͼ���뿪��ͼ\r\n����'ESC'�뿪��ͼ","�Ķ�����" ,MB_ICONEXCLAMATION|MB_OKCANCEL);
}
