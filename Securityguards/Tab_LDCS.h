#pragma once
#include "stdafx.h"
#include "resource.h"
#include "afxcmn.h"
#include "afxwin.h"
#include "MFCsockclass.h"
#include "afxeditbrowsectrl.h"
#include "vector"

using std::vector;

// Tab_LDCS �Ի���

class Tab_LDCS : public CDialogEx
{
	DECLARE_DYNAMIC(Tab_LDCS)

public:
	Tab_LDCS(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~Tab_LDCS();

// �Ի�������
	enum { IDD = IDD_TABLDCS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CListCtrl m_PathListCtr;
	CListCtrl m_ListMessageInfo;
	afx_msg void OnBnClickedOk();
	int m_buttQP;
	CButton m_ButtCX;
	afx_msg void OnBnClickedRadio1();
	afx_msg void OnBnClickedRadio2();
	afx_msg void OnBnClickedRadio3();
	afx_msg void OnRadio2();
	afx_msg void OnRadio3();
public:
	// ��Ӧ��������������Ϣ
	void OnReceives(WPARAM wParam, LPARAM lParam);
	// �����ļ���ɱ
	void FindFile(CString Path, CString MD5);
	static CString strFindNamPathp[5];
	// ���ʲô����ɱ ��ֹ�����ļ���ק
	static int Flag;
	static int nCounts;
	int GetDriveStringName();
	// ��ʱ����MD5ֵ
	char SaveMd5[MAX_PATH][36] = {};
	// �ϴ�������
	BOOL Md5PutValues();
	char IsEm = 0;				// ������������
	int nCOunt = 0;
	// �Ʋ�ɱ���ضԱ�
	BOOL Md5Recver(CString PathName, CString md5valse);
	static int nCountList;		// �ؼ�����ȫ�ֱ���


private:
	// ����MD5��������
	vector<CString> SaveMd5Values;
	// �������
	CRect rc;
	DWORD dwOldStyle;
	// ��¼�����ļ�����(��ѭ������List�������к�)
	int nI = 0, nK = 0, nCountFileNumber = 0;
	// ��ȡ�̷�����
	int nDriverCount = 0;
	// ��������ļ�
	vector<CString> SaveSuspectedFile;
	// Socket����
	MFCsockclass pSocket;
	// ���÷���ɱ·��
	void SetStylePathList();
	// ���ÿ����ļ����
	void SetSaveSuspectedFileList();
	// ���ز�ɱ���ֱ�־
	BOOL ConnentFlag = FALSE;
	// �ص��������
	HANDLE hThread;
public:
	afx_msg void OnDropFiles(HDROP hDropInfo);
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton4();
	CString m_NetworkStatus;
	CMFCEditBrowseCtrl m_CMFeditBriwse;
	afx_msg void OnBnClickedButton6();
	CString m_Editvalues;
	afx_msg void OnLvnItemchangedList5(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnRclickList5(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void On40043();
	CString m_MDEditValse;
	static CString m_MDEValues;
	// CProgressCtrl m_ProgressBar;
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton5();
	afx_msg void OnEnChangeMfceditbrowse1();
	afx_msg void OnBnClickedButton7();
	afx_msg void OnBnClickedButton8();
	afx_msg void On40042();
	afx_msg void OnStnClickedValuestat();
};
