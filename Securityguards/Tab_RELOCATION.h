#pragma once
#include "stdafx.h"
#include "resource.h"
#include "afxcmn.h"

// Tab_RELOCATION �Ի���

class Tab_RELOCATION : public CDialogEx
{
	DECLARE_DYNAMIC(Tab_RELOCATION)

public:
	Tab_RELOCATION(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~Tab_RELOCATION();
	char* m_lpBaseReLoc;

// �Ի�������
	enum { IDD = IDD_RELOCATION };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnLvnItemchangedRelist1(NMHDR *pNMHDR, LRESULT *pResult);
	CListCtrl m_ReListCtr;
	CListCtrl m_ReListCtrs;
	// ��ȡ�������Ƽ����εĻ�ַ
	DWORD GetSection(PIMAGE_NT_HEADERS const pNt, DWORD const dwRVA);
	// ������������
	CString strName;
private:
	// �������Խ��� analysis
	void SectionAnal();
	// ����Ŀ���Խ���
	void BloackAnal();
};
