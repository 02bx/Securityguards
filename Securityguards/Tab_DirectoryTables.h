#pragma once
#include "stdafx.h"
#include "resource.h"
#include "afxwin.h"

// Tab_DirectoryTables �Ի���

class Tab_DirectoryTables : public CDialogEx
{
	DECLARE_DYNAMIC(Tab_DirectoryTables)

public:
	Tab_DirectoryTables(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~Tab_DirectoryTables();

// �Ի�������
	enum { IDD = IDD_DIRECTORY };
// ���������Ϣ
	char* m_lpBases;


protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();

public:
	// ��ʾ����RVA����С
	void ShowDateofsize(PIMAGE_DATA_DIRECTORY pDataDirectory);
	CString m_indexexport;
	CString m_indexexports;
	CString m_imports;
	CString m_import;
	afx_msg void OnBnClickedButton11();
	CString m_indexSource;
	CString m_indexSources;
	PIMAGE_DATA_DIRECTORY pDataDirectory;
	afx_msg void OnBnClickedButton13();
	afx_msg void OnBnClickedButton16();
	afx_msg void OnBnClickedButton15();
//	CStatic m_Exect;
//	CStatic m_Exects;
	CString m_Exect;
	CString m_Exects;
	CString m_Security;
	CString m_Securitys;
	CStatic m_Relocation;
	CString m_Reactions;
	CString m_RELOCATION;
	CString m_Debug;
	CString m_Debugs;
	CString m_Copyright;
	CString m_Copyrights;
	CString m_Global;
	CString m_Globals;
	CString m_ThreadStorag;
	CString m_ThreadStorags;
	CString m_Load;
	CString m_Loads;
	CString m_Importaddress;
	CString m_importaddresses;
	CString m_BindDirectory;
	CString m_BindDirectorys;
	CString m_Delay;
	CString m_Delays;
	CString m_Com;
	CString m_Coms;
	CString m_Keeps;
	CString m_Keep;
	afx_msg void OnBnClickedButton12();
	afx_msg void OnBnClickedButton20();
};
