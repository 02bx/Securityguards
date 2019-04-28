#pragma once
#include "stdafx.h"
#include "resource.h"
#include "afxcmn.h"

// ModuleInfoDialogBox �Ի���

class ModuleInfoDialogBox : public CDialogEx
{
	DECLARE_DYNAMIC(ModuleInfoDialogBox)

public:
	ModuleInfoDialogBox(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~ModuleInfoDialogBox();
	// ���游��ID
	DWORD m_ownerPid = 0;
	// ��ȡ����ģ��
	void GetProcessModule(const DWORD idProcess);

// �Ի�������
	enum { IDD = IDD_MODULE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_ListCtr;
	virtual BOOL OnInitDialog();
};
