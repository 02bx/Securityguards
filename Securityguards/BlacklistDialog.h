#pragma once
#include "stdafx.h"
#include "resource.h"
#include "afxcmn.h"
#include "vector"
// BlacklistDialog �Ի���

using std::vector;

class BlacklistDialog : public CDialogEx
{
	DECLARE_DYNAMIC(BlacklistDialog)

public:
	BlacklistDialog(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~BlacklistDialog();

// �Ի�������
	enum { IDD = IDD_BLACKLIST };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	// ���������·��
	static vector<CString> nBlackList;
	// ��װUpdateList
	void UpdateList();
	virtual BOOL OnInitDialog();
	afx_msg void OnDropFiles(HDROP hDropInfo);
	CListCtrl m_blacklsit;
	CString m_BlackList;
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
};
