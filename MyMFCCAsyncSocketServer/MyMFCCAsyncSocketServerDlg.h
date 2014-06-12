
// MyMFCCAsyncSocketServerDlg.h : ͷ�ļ�
//

#pragma once

#include "MySocket.h"

// CMyMFCCAsyncSocketServerDlg �Ի���
class CMyMFCCAsyncSocketServerDlg : public CDialogEx
{
// ����
public:
	CMyMFCCAsyncSocketServerDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_MYMFCCASYNCSOCKETSERVER_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��

public:
	virtual void OnClose();
	virtual void OnReceive();
	virtual void OnAccept();
	virtual void OnOK();
private:
private:
	CMySocket m_sockListen;
	CMySocket m_socketServer;
// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CString m_recv;
	CString m_send;
	afx_msg void OnBnClickedStartBtn();
	afx_msg void OnBnClickedSendBtn();
	afx_msg void OnBnClickedCancelBtn();
};
