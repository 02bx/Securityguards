#pragma once
#include "stdafx.h"
#include "resource.h"
#include "afxcmn.h"

// Tab_ExportTable �Ի���

class Tab_ExportTable : public CDialogEx
{
	DECLARE_DYNAMIC(Tab_ExportTable)

public:
	Tab_ExportTable(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~Tab_ExportTable();

// �Ի�������
	enum { IDD = IDD_EXPORT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()


public:
	virtual BOOL OnInitDialog();
	// ����VA��ַ
	char* m_lpBases;

private:
	// ��ȡ������
	void GetExportInfo(char* lpbase);
public:
	CString m_OutOffset;
	CString m_VAULES;
	CString m_exBase;
	CString m_exName;
	CString m_exStr;
	CString m_exFunnumber;
	CString m_exFun;
	CString m_exFunaddress;
	CString m_exNameaddress;
	CString m_exNumbers;
	CListCtrl m_exListCtr;
};
