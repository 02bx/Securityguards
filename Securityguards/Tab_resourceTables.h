#pragma once
#include "stdafx.h"
#include "resource.h"
#include "afxcmn.h"

// Tab_resourceTables �Ի���

class Tab_resourceTables : public CDialogEx
{
	DECLARE_DYNAMIC(Tab_resourceTables)

public:
	Tab_resourceTables(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~Tab_resourceTables();

// �Ի�������
	enum { IDD = IDD_RESOURCE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	//virtual BOOL OnInitDialog();
	afx_msg void OnTvnSelchangedTree1(NMHDR *pNMHDR, LRESULT *pResult);
public:
	// ����lpBase;
	char* m_lpBase = 0;
	virtual BOOL OnInitDialog();
	// ��ȡ��ʾ��Դ��
	void ShowResourInfo();
	CTreeCtrl m_TreeFile;
};
