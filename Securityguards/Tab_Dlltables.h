#pragma once
#include "stdafx.h"
#include "resource.h"
#include "afxcmn.h"

// Tab_Dlltables �Ի���

class Tab_Dlltables : public CDialogEx
{
	DECLARE_DYNAMIC(Tab_Dlltables)

public:
	Tab_Dlltables(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~Tab_Dlltables();

// �Ի�������
	enum { IDD = IDD_DLLTABLES };
public:
	// �����ļ�����(VA)
	char* m_lpBase = 0;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_ListCtr;
	virtual BOOL OnInitDialog();

public:
	// ��ȡ��ʾ����
	void GetdllLoadofShow();
};
