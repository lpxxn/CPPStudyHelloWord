
// MyMFCCAsyncSocketClient.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CMyMFCCAsyncSocketClientApp:
// �йش����ʵ�֣������ MyMFCCAsyncSocketClient.cpp
//

class CMyMFCCAsyncSocketClientApp : public CWinApp
{
public:
	CMyMFCCAsyncSocketClientApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CMyMFCCAsyncSocketClientApp theApp;