#pragma once
#include "stdafx.h"
#include "resource.h"
#include "afxcmn.h"
#include "list"

using std::list;

// Tab_MemoryDialogbox �Ի���

class Tab_MemoryDialogbox : public CDialogEx
{
	DECLARE_DYNAMIC(Tab_MemoryDialogbox)

public:
	Tab_MemoryDialogbox(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~Tab_MemoryDialogbox();

// �Ի�������
	enum { IDD = IDD_Memory_optimization };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	// ��ȡCPU��ռ����
	void GetCpuUsage();

private:
	// Ȩ��
	enum MEMORYSTATE {
		e_stat_free = MEM_FREE,
		e_stat_reserve = MEM_RESERVE,
		e_stat_commit = MEM_COMMIT
	};
	// �����ڴ��ҳ����
	enum MEMORYTYPE {
		e_type_image = MEM_IMAGE,
		e_type_mapped = MEM_MAPPED,
		e_type_private = MEM_PRIVATE,
	};
	// �ṹ��
	typedef struct VMINFO {
		DWORD		address;
		DWORD		size;
		MEMORYSTATE state;
	}VMINFO;
	// ����List�ṹ��
	list<VMINFO> vmlist;

private:
	// ��ȡ�����ڴ����Ϣ
	void GetMemoryInfo();
	// ���ڴ����
	void queryViryualMemoryStatue(HANDLE hProccess);
	// ʱ��ת��
	double FILETIMEDouble(const _FILETIME & filetime);
public:
	afx_msg void OnBnClickedButton8();
	CListCtrl m_ListCtr;
	CString m_Cpusyl;
	CString m_MemoryBFB;
	CString m_Pymemory;
	CString m_Pagesize;
	CString m_Memorysize;
	CString m_Kymemorysize;
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};
