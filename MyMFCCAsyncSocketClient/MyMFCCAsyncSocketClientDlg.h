
// MyMFCCAsyncSocketClientDlg.h : ͷ�ļ�
//

#pragma once

#include "MySocket.h"

// CMyMFCCAsyncSocketClientDlg �Ի���
class CMyMFCCAsyncSocketClientDlg : public CDialogEx
{
// ����
public:
	CMyMFCCAsyncSocketClientDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_MYMFCCASYNCSOCKETCLIENT_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��

public:
	void OnClose();
	void OnReceive();
	void OnConnect();
	void OnOK();
private:
	CMySocket m_socketConnect;
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
	afx_msg void OnBnClickedSendBtn();
	afx_msg void OnBnClickedConnectBtn();
};
