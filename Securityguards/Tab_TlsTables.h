#pragma once
#include "stdafx.h"
#include "resource.h"
#include "afxwin.h"

// Tab_TlsTables �Ի���

class Tab_TlsTables : public CDialogEx
{
	DECLARE_DYNAMIC(Tab_TlsTables)

public:
	Tab_TlsTables(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~Tab_TlsTables();

// �Ի�������
	enum { IDD = IDD_TLSTABLES };

public:
	char* m_lpBase = 0;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CEdit m_EditText;
	CString outputstr;
	virtual BOOL OnInitDialog();
};
