#pragma once
#include "stdafx.h"
#include "resource.h"
#include "afxcmn.h"
#include <vector>

using std::vector;

// WhiteDialogBox �Ի���

class WhiteDialogBox : public CDialogEx
{
	DECLARE_DYNAMIC(WhiteDialogBox)

public:
	WhiteDialogBox(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~WhiteDialogBox();

// �Ի�������
	enum { IDD = IDD_DIALOG2 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	// ����������
	static vector<CString> WhiteName;
	// ��ʼ����װ
	void UpdateListName();
	CString m_WhiteEdit;
	CListCtrl m_ListArr;
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	virtual BOOL OnInitDialog();
	afx_msg void OnDropFiles(HDROP hDropInfo);
};
