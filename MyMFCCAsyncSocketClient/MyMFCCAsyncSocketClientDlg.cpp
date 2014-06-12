
// MyMFCCAsyncSocketClientDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MyMFCCAsyncSocketClient.h"
#include "MyMFCCAsyncSocketClientDlg.h"
#include "afxdialogex.h"
#include <iostream>
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CMyMFCCAsyncSocketClientDlg �Ի���



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


// CMyMFCCAsyncSocketClientDlg ��Ϣ�������

BOOL CMyMFCCAsyncSocketClientDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	m_socketConnect.SetParent(this);

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CMyMFCCAsyncSocketClientDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CMyMFCCAsyncSocketClientDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CMyMFCCAsyncSocketClientDlg::OnConnect()
{
	UpdateData(TRUE);
	m_recv+=CString("���ӳɹ���\r\n");

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
		AfxMessageBox(_T("�����ǵ�����������"));
	}
}
void CMyMFCCAsyncSocketClientDlg::OnClose()
{
	m_socketConnect.Close();
}

void CMyMFCCAsyncSocketClientDlg::OnBnClickedSendBtn()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	int nSendLen=m_socketConnect.Send(m_send.GetBuffer(0),m_send.GetLength()*2);

	if(nSendLen > 0)
	{
		AfxMessageBox(_T("���ͳɹ�!"));
	}
	else
	{
		AfxMessageBox(_T("����ʧ��!"));
	}
}


void CMyMFCCAsyncSocketClientDlg::OnBnClickedConnectBtn()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//CString lpIp=_T("192.168.112.59");
	CString lpIp=_T("127.0.0.1");
	m_socketConnect.Create();
	m_socketConnect.Connect(lpIp,10000);
	
	int error = m_socketConnect.GetLastError();
	std::cout<<error<<std::endl;
	if(!error)
	{
		AfxMessageBox(_T("����ʧ��!"));
	}
}

void CMyMFCCAsyncSocketClientDlg::OnOK()
{	
	if(GetDlgItem(IDOK)==GetFocus())  
	{  
	    CDialog::OnOK();      
	}  
}