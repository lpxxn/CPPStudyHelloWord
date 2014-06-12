// MySocket.cpp : 实现文件
//

#include "stdafx.h"
#include "MyMFCCAsyncSocketClient.h"
#include "MyMFCCAsyncSocketClientDlg.h"
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



void CMySocket::OnConnect(int nErrorCode)
{
	if(nErrorCode==0)
	{
		((CMyMFCCAsyncSocketClientDlg *)m_pDlg)->OnConnect();
	}
	else
	{

	}
}

void CMySocket::OnReceive(int nErrorCode)
{
	((CMyMFCCAsyncSocketClientDlg *)m_pDlg)->OnReceive();
}

void CMySocket::OnClose(int nERRORCode)
{
	((CMyMFCCAsyncSocketClientDlg *)m_pDlg)->OnClose();
}

// CMySocket 成员函数
