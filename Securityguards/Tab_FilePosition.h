#pragma once
#include "stdafx.h"
#include "resource.h"
// Tab_FilePosition �Ի���

class Tab_FilePosition : public CDialogEx
{
	DECLARE_DYNAMIC(Tab_FilePosition)

public:
	Tab_FilePosition(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~Tab_FilePosition();

// �Ի�������
	enum { IDD = IDD_POSIT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	DWORD m_ImageBase;
	DWORD m_vritualAddress;
	DWORD m_offsetS;
	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();
	CString m_editupdate;
};
