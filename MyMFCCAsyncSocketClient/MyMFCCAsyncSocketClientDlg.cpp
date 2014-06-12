
// MyMFCCAsyncSocketClientDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "MyMFCCAsyncSocketClient.h"
#include "MyMFCCAsyncSocketClientDlg.h"
#include "afxdialogex.h"
#include <iostream>
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMyMFCCAsyncSocketClientDlg 对话框



CMyMFCCAsyncSocketClientDlg::CMyMFCCAsyncSocketClientDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMyMFCCAsyncSocketClientDlg::IDD, pParent)
	, m_recv(_T(""))
	, m_send(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMyMFCCAsyncSocketClientDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_RECV_EDIT, m_recv);
	DDX_Text(pDX, IDC_SEND_EDIT, m_send);
}

BEGIN_MESSAGE_MAP(CMyMFCCAsyncSocketClientDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_SEND_BTN, &CMyMFCCAsyncSocketClientDlg::OnBnClickedSendBtn)
	ON_BN_CLICKED(IDC_CONNECT_BTN, &CMyMFCCAsyncSocketClientDlg::OnBnClickedConnectBtn)
END_MESSAGE_MAP()


// CMyMFCCAsyncSocketClientDlg 消息处理程序

BOOL CMyMFCCAsyncSocketClientDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	m_socketConnect.SetParent(this);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CMyMFCCAsyncSocketClientDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMyMFCCAsyncSocketClientDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CMyMFCCAsyncSocketClientDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CMyMFCCAsyncSocketClientDlg::OnConnect()
{
	UpdateData(TRUE);
	m_recv+=CString("连接成功！\r\n");

	UpdateData(FALSE);
}

void CMyMFCCAsyncSocketClientDlg::OnReceive()
{
	BYTE byBuf[1024]={0};
	int nrecvLen = 0;
	nrecvLen =	m_socketConnect.Receive(byBuf,sizeof(byBuf));
	CString tmp;
	if(nrecvLen>0)
	{
		UpdateData(TRUE);
		tmp.Format(_T("%s\r\n"),byBuf);
		m_recv+=tmp;
		UpdateData(FALSE);
	}
	else
	{
		AfxMessageBox(_T("收于是的数据有问题"));
	}
}
void CMyMFCCAsyncSocketClientDlg::OnClose()
{
	m_socketConnect.Close();
}

void CMyMFCCAsyncSocketClientDlg::OnBnClickedSendBtn()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	int nSendLen=m_socketConnect.Send(m_send.GetBuffer(0),m_send.GetLength()*2);

	if(nSendLen > 0)
	{
		AfxMessageBox(_T("发送成功!"));
	}
	else
	{
		AfxMessageBox(_T("发送失败!"));
	}
}


void CMyMFCCAsyncSocketClientDlg::OnBnClickedConnectBtn()
{
	// TODO: 在此添加控件通知处理程序代码
	//CString lpIp=_T("192.168.112.59");
	CString lpIp=_T("127.0.0.1");
	m_socketConnect.Create();
	m_socketConnect.Connect(lpIp,10000);
	
	int error = m_socketConnect.GetLastError();
	std::cout<<error<<std::endl;
	if(!error)
	{
		AfxMessageBox(_T("连接失败!"));
	}
}

void CMyMFCCAsyncSocketClientDlg::OnOK()
{	
	if(GetDlgItem(IDOK)==GetFocus())  
	{  
	    CDialog::OnOK();      
	}  
}