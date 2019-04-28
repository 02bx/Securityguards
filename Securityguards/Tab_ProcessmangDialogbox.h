#pragma once

#include "resource.h"
#include "afxcmn.h"
#include "TlHelp32.h"
#include "Psapi.h"
// Tab_ProcessmangDialogbox �Ի���

// ListNameArrNumber
const int g_MaxName = 6;

class Tab_ProcessmangDialogbox : public CDialogEx
{
	DECLARE_DYNAMIC(Tab_ProcessmangDialogbox)

public:
	Tab_ProcessmangDialogbox(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~Tab_ProcessmangDialogbox();

// �Ի�������
	enum { IDD = IDD_Process_management };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();

// �ӿ�
public:
	void GetProcessInfos(){ this->GetProcessInfo(); }

// ˽�з���
private:
	// 1. ��ȡ������Ϣ
	BOOL GetProcessInfo();
	// 2. ���ý�����Ϣ
	void SetProcessInfo(const LPPROCESSENTRY32W P_32, const int count, const TCHAR* buf);
	// 3. ListNameArr
	static const TCHAR m_ListNameArr[g_MaxName][g_MaxName];
	TCHAR buf[MAX_PATH] = { };

// App����
private:
	// ��ȡ��ǰ���ڽ�������
	void GetNewWindowProcessData();
	// ��ȡ������Ϣ�Ļص�����
	static BOOL CALLBACK EnumWinProc(HWND hwnd, LPARAM lParam);
	// ��װ
	void ShowWindowApp();
	static int count;
	static TCHAR buff[MAX_PATH];
	static TCHAR buff1[MAX_PATH];
	static CImageList* Icon;


public:
	/*���ò˵�����*/
	CMenu men;
	POINT point;
	CMenu *p;
	/*-----------*/
	CListCtrl m_ListCtr;
	afx_msg void OnRclickList2(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void CloseProcess();
	afx_msg void Filelocation();
	afx_msg void GetThreadInfo();
	afx_msg void GetHeapInfoss();
	CListCtrl m_ListCtrApp;
	afx_msg void OnLvnItemchangedList1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedButton1();
	afx_msg void GetModule();
	afx_msg void OnRclickList1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void AppList();
	afx_msg void OnAttres();
};
