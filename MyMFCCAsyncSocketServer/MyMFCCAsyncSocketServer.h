
// MyMFCCAsyncSocketServer.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CMyMFCCAsyncSocketServerApp:
// �йش����ʵ�֣������ MyMFCCAsyncSocketServer.cpp
//

class CMyMFCCAsyncSocketServerApp : public CWinApp
{
public:
	CMyMFCCAsyncSocketServerApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CMyMFCCAsyncSocketServerApp theApp;