#pragma once

// CMySocket ÃüÁîÄ¿±ê

class CMySocket : public CAsyncSocket
{
public:
	CMySocket();
	virtual ~CMySocket();

	void SetParent(CDialog * pDlg);
protected:
	virtual void OnClose(int nERRORCode);
	virtual void OnReceive(int nErrorCode);				   
	
	virtual void OnAccept(int nErrorCode);
private:
	CDialog * m_pDlg;
};


