#pragma once
#include "stdafx.h"
#include "resource.h"
#include "afxcmn.h"
#include <vector>

using std::vector;

// Tab_SoftwarmangDialogbox �Ի���

class Tab_SoftwarmangDialogbox : public CDialogEx
{
	DECLARE_DYNAMIC(Tab_SoftwarmangDialogbox)

public:
	Tab_SoftwarmangDialogbox(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~Tab_SoftwarmangDialogbox();

	// �Ի�������
	enum { IDD = IDD_Softwar_management };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_ServicesoList;
	CListCtrl m_ServerInfo;
	virtual BOOL OnInitDialog();
	afx_msg void OnLvnItemchangedList1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnClickList1(NMHDR *pNMHDR, LRESULT *pResult);

	// ���нӿ�
public:
	void pGetofShowAllSofwInfo() { this->GetofShowAllSofwInfo(); };
	//void pGetofShowZJSofwInfo() { this->GetofShowZJSofwInfo(); };
	//void pGetofShowBCYSofwInfo() { this->GetofShowBCYSofwInfo(); };
	void pGetofShowSystemService() { this->GetofShowSystemService(); };
	// 1. �Զ���ṹ��
	typedef struct _SOFTINFO
	{
		WCHAR szSoftName[50];				// ������� 
		WCHAR szSoftVer[50];				// ����汾��
		WCHAR szSoftDate[20];				// �����װ����
		WCHAR szSoftSize[MAX_PATH];			// �����С
		WCHAR strSoftInsPath[MAX_PATH];		// �����װ·��
		WCHAR strSoftUniPath[MAX_PATH];		// ���ж��·��
		WCHAR strSoftVenRel[50];			// �����������
		WCHAR strSoftIco[MAX_PATH];			// ���ͼ��·��
	}SOFTINFO, *PSOFTINFO;

	// ˽�з���
private:
	// 1. ��ȡ��ʾȫ����� 
	BOOL GetofShowAllSofwInfo();
	//// 2. ��ȡ��ʾ�����װ���
	//BOOL GetofShowZJSofwInfo();
	//// 3. ��ȡ��ʾ���������
	//BOOL GetofShowBCYSofwInfo();
	// 4. ��ȡ��ʾϵͳ����
	BOOL GetofShowSystemService();
	// ������������Ϣ
	vector<SOFTINFO> m_vecSofInfo;
	// ����
	HKEY RootKey = HKEY_LOCAL_MACHINE;
	// �Ӽ�
	LPCTSTR lpSubKey = L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Uninstall";
	// ���ռ����򿪵ļ��ľ��
	HKEY hkResult = 0;
	// List����װ��ϵͳ��
	void ListStyleFun();
	// List����װ�������
	void ListStyleFuns();
public:
	afx_msg void OnRclickList1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnLvnItemchangedList2(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnRclickList2(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void StartService();
	afx_msg void StopService();
	afx_msg void SofwUninstall();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnHotKey(UINT nHotKeyId, UINT nKey1, UINT nKey2);
};