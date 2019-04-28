#pragma once
#include "stdafx.h"
#include "resource.h"
#include "afxcmn.h"

// HeapInfoDialogBox �Ի���

class HeapInfoDialogBox : public CDialogEx
{
	DECLARE_DYNAMIC(HeapInfoDialogBox)

public:
	HeapInfoDialogBox(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~HeapInfoDialogBox();

// �Ի�������
	enum { IDD = IDD_HeapInfo };
	// ���ո�������ID
	DWORD m_ownerPid = 0;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��


	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CListCtrl m_ListCtr;
	afx_msg void OnLvnItemchangedList1(NMHDR *pNMHDR, LRESULT *pResult);

public:
	// ��ȡ����Ϣ����
	BOOL GetHeapInfo(DWORD pid);
	// ������ʱ�ַ���
	TCHAR buf[MAX_PATH] = {};

	afx_msg void OnRclickList1(NMHDR *pNMHDR, LRESULT *pResult);
};
