
// MyMFCCAsyncSocketServerDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MyMFCCAsyncSocketServer.h"
#include "MyMFCCAsyncSocketServerDlg.h"
#include "afxdialogex.h"

#include<iostream>
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


// CMyMFCCAsyncSocketServerDlg �Ի���



CMyMFCCAsyncSocketServerDlg::CMyMFCCAsyncSocketServerDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMyMFCCAsyncSocketServerDlg::IDD, pParent)
	, m_recv(_T(""))
	, m_send(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMyMFCCAsyncSocketServerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_RECV_EDIT, m_recv);
	DDX_Text(pDX, IDC_SEND_EDIT, m_send);
}

BEGIN_MESSAGE_MAP(CMyMFCCAsyncSocketServerDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_START_BTN, &CMyMFCCAsyncSocketServerDlg::OnBnClickedStartBtn)
	ON_BN_CLICKED(IDC_SEND_BTN, &CMyMFCCAsyncSocketServerDlg::OnBnClickedSendBtn)
	ON_BN_CLICKED(IDC_CANCEL_BTN, &CMyMFCCAsyncSocketServerDlg::OnBnClickedCancelBtn)
END_MESSAGE_MAP()


// CMyMFCCAsyncSocketServerDlg ��Ϣ�������

BOOL CMyMFCCAsyncSocketServerDlg::OnInitDialog()
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
	m_sockListen.SetParent(this);
	m_socketServer.SetParent(this);


	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CMyMFCCAsyncSocketServerDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CMyMFCCAsyncSocketServerDlg::OnPaint()
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
HCURSOR CMyMFCCAsyncSocketServerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMyMFCCAsyncSocketServerDlg::OnBnClickedStartBtn()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//m_sockListen.Create(10000);
	m_sockListen.Create(10000,SOCK_STREAM,FD_READ | FD_WRITE | FD_OOB | FD_ACCEPT | FD_CONNECT | FD_CLOSE);
	if(!m_sockListen.Listen())
	{
		AfxMessageBox(_T("����ʧ�ܣ�"));
	}
	int error = m_sockListen.GetLastError();
	std::cout<<error<<std::endl;
}


void CMyMFCCAsyncSocketServerDlg::OnAccept()
{
	SOCKADDR sockAddr;
	int nSockAdrLen=sizeof(SOCKADDR);
	CString tmp;

	if(m_sockListen.Accept(m_socketServer,&sockAddr,&nSockAdrLen))
	{
		tmp.Format(_T("�пͻ�����,����%d.%d.%d.%d\r\n"),(UCHAR)sockAddr.sa_data[2],(UCHAR)sockAddr.sa_data[3],(UCHAR)sockAddr.sa_data[4],(UCHAR)sockAddr.sa_data[5]);
		m_recv+=tmp;

		//MFC��ͬ���Ϳؼ���������ֵ����
		//UpdateData(TRUE);���ؼ��е�ֵ��������
		//UpdateData(FALSE);��������ֵд��ؼ��� 
		UpdateData(FALSE);
	}
	else
	{
		AfxMessageBox(_T("����������Accept"));
	}
}

void CMyMFCCAsyncSocketServerDlg::OnReceive()
{
	BYTE byBuf[4096]={0};
	memset(byBuf,0,sizeof(byBuf));
	int nRecvLen = 0;

	nRecvLen = m_socketServer.Receive(byBuf,sizeof(byBuf));
	
	CString tmp;

	if(nRecvLen > 0)
	{
		UpdateData(TRUE);
		tmp.Format(_T("%s\r\n"),byBuf);
		m_recv+=tmp;
		UpdateData(FALSE);
	}
	else
	{
		AfxMessageBox(_T("�յ������������⣡"));
	}
}



void CMyMFCCAsyncSocketServerDlg::OnBnClickedSendBtn()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	int nSendLen = m_socketServer.Send(m_send.GetBuffer(0),m_send.GetLength()*2);
	if(nSendLen > 0)
	{
		AfxMessageBox(_T("�������ݳɹ���"));
	}
	else
	{
		AfxMessageBox(_T("��������ʧ�ܣ�"));
	}
}

void CMyMFCCAsyncSocketServerDlg::OnClose()
{
	m_socketServer.Close();
}

void CMyMFCCAsyncSocketServerDlg::OnBnClickedCancelBtn()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//CDialog::OnCancel();
}

void CMyMFCCAsyncSocketServerDlg::OnOK()
{
	if(GetDlgItem(IDOK)==GetFocus())  
    {  
        CDialog::OnOK();      
    }  

}