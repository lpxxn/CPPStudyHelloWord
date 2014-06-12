// MySocket.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MyMFCCAsyncSocketServer.h"
#include "MyMFCCAsyncSocketServerDlg.h"
#include "MySocket.h"


// CMySocket

CMySocket::CMySocket()
{
}

CMySocket::~CMySocket()
{
}

void CMySocket::SetParent(CDialog * pDlg)
{
	m_pDlg=pDlg;
}

void CMySocket::OnAccept(int nErrorCode)
{
	if(nErrorCode==0)
	{
		((CMyMFCCAsyncSocketServerDlg *)m_pDlg)->OnAccept();
	}
	else
	{
		AfxMessageBox(_T("MySocket��Accept"));
	}
}



void CMySocket::OnReceive(int nErrorCode)
{
	((CMyMFCCAsyncSocketServerDlg *)m_pDlg)->OnReceive();
}

void CMySocket::OnClose(int nERRORCode)
{
	((CMyMFCCAsyncSocketServerDlg *)m_pDlg)->OnClose();
}

// CMySocket ��Ա����
