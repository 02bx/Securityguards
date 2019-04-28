#pragma once
#include "stdafx.h"
#include "resource.h"
#include "afxcmn.h"
#include "TlHelp32.h"
// ThreadDialogbox �Ի���

class ThreadDialogbox : public CDialogEx
{
	DECLARE_DYNAMIC(ThreadDialogbox)

public:
	ThreadDialogbox(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~ThreadDialogbox();

// �Ի�������
	enum { IDD = IDD_Thread_Info };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_Listctr;
	virtual BOOL OnInitDialog();

// ���нӿ�
public:
	void GetThreadInfos(){ this->GetThreadInfo(); }
	// ���游���̵�ID
	DWORD m_ownperProcess = NULL;

// ˽�з���
private:
	// ��ȡ��ǰѡ�е�Listѡ�е�Pid
	unsigned long GetThreadPid();
	// ��ȡ��ť״̬
	int value = 0;
	// ��ȡ�߳���Ϣ
	BOOL GetThreadInfo();
	// ��ʾ��ȡ��Ϣ
	void ShowThreadList(const THREADENTRY32 t_32, const int nSel);
	// ������ʱת���ַ���
	TCHAR buf[MAX_PATH] = {};
public:
	afx_msg void OnLvnItemchangedList1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnRclickList1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void HungThread();
	afx_msg void RestoretheThread();
	afx_msg void CloseThread();
//	afx_msg void GetHeapInfoss();
};
