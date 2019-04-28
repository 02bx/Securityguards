#pragma once
#include "stdafx.h"
#include "resource.h"
#include "afxwin.h"

// FileInfo �Ի���

class FileInfo : public CDialogEx
{
	DECLARE_DYNAMIC(FileInfo)

public:
	FileInfo(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~FileInfo();

// �Ի�������
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CString m_seFileType;
	CString m_seFileWZ;
	CString m_seFileSizeof;
	CString m_seFileCreate;
	CString m_seFileModify;
	CString m_seFileAccess;
	CString m_seEditFileName;
	CString m_seEditMD5;
	virtual BOOL OnInitDialog();
	// �����ļ�·��(����)
	CString cFilePath;
	static CImageList* Icon;
	CBrush m_bush;
private:
	// ��ȡ�ļ�·��
	void GetFileInfo(CString str);
public:
	CStatic m_ICon;
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};
