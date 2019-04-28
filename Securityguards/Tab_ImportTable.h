#pragma once
#include "stdafx.h"
#include "resource.h"
#include "afxcmn.h"

// Tab_ImportTable �Ի���

class Tab_ImportTable : public CDialogEx
{
	DECLARE_DYNAMIC(Tab_ImportTable)

public:
	Tab_ImportTable(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~Tab_ImportTable();

// �Ի�������
	enum { IDD = IDD_IMPORTTABLE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_ImportListCtr;
	CListCtrl m_ImportListCtr1;
	virtual BOOL OnInitDialog();
	char* m_ImlpBase;
private:
	// ��ʾ�����
	void ShowImportTable();
	// �л�API����
	void APIshow();
	// ����ͷ
	PIMAGE_IMPORT_DESCRIPTOR pImport = { 0 };
public:
	afx_msg void OnLvnItemchangedList3(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnClickList3(NMHDR *pNMHDR, LRESULT *pResult);
};
