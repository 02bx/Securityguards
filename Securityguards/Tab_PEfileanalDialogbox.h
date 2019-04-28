#pragma once
#include "stdafx.h"
#include "resource.h"
#include "afxwin.h"

// Tab_PEfileanalDialogbox �Ի���

class Tab_PEfileanalDialogbox : public CDialogEx
{
	DECLARE_DYNAMIC(Tab_PEfileanalDialogbox)

public:
	Tab_PEfileanalDialogbox(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~Tab_PEfileanalDialogbox();

// �Ի�������
	enum { IDD = IDD_PE_Fille_analysis };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CString m_entryPoint;
	CString m_baseAddres;
	CString m_codeStart;
	CString m_fileSize;
	CStatic m_dataStart;
	CStatic m_block;
	CStatic m_childSystem;
	CStatic m_flag;
	CString m_fileAli;
	CStatic m_rvaName;
	CString m_messageFlag;
	CString m_fileTime;
	DWORD	e_addrssbase;
// ���ýӿ�
public:
	// �ж��Ƿ�PE�ļ�
	BOOL IsPEfile(char* lpBase);
	// ��ʾPEͷ����Ϣ
	void ShowHeaderInfo(char* lpBase);
	// �ļ����ؽӿ�
	void FileLoadMemorys(char* lpFilePtah){ this->FileLoadMemory(lpFilePtah); }

// ˽�з���
private:
	// �����ļ����ڴ�
	char* FileLoadMemory(char* lpFilePath);
	// ��ʱ����������
	char* m_lpBase = 0;

public:
	CString m_textPath;
	// ��Ӧ��ק��Ϣ
	afx_msg void OnDropFiles(HDROP hDropInfo);
	CString m_blocks;
	CString m_childsystems;
	CString m_dataStarts;
	CString m_rvaNames;
	afx_msg void OnBnClickedButton15();
	afx_msg void OnBnClickedButton19();
	afx_msg void OnBnClickedButton14();
	afx_msg void OnBnClickedButton18();
};
