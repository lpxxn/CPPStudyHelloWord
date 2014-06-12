
// MyMFCCAsyncSocketClientDlg.h : 头文件
//

#pragma once

#include "MySocket.h"

// CMyMFCCAsyncSocketClientDlg 对话框
class CMyMFCCAsyncSocketClientDlg : public CDialogEx
{
// 构造
public:
	CMyMFCCAsyncSocketClientDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_MYMFCCASYNCSOCKETCLIENT_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持

public:
	void OnClose();
	void OnReceive();
	void OnConnect();
	void OnOK();
private:
	CMySocket m_socketConnect;
// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
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
