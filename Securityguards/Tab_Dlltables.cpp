// Tab_Dlltables.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Tab_Dlltables.h"
#include "afxdialogex.h"
#include "RVAtoFOA.h"

// Tab_Dlltables �Ի���

IMPLEMENT_DYNAMIC(Tab_Dlltables, CDialogEx)

Tab_Dlltables::Tab_Dlltables(CWnd* pParent /*=NULL*/)
	: CDialogEx(Tab_Dlltables::IDD, pParent)
{

}

Tab_Dlltables::~Tab_Dlltables()
{
}

void Tab_Dlltables::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST2, m_ListCtr);
}


BEGIN_MESSAGE_MAP(Tab_Dlltables, CDialogEx)
END_MESSAGE_MAP()


// Tab_Dlltables ��Ϣ�������


BOOL Tab_Dlltables::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	// ��ȡ���
	DWORD dwOldStyle;
	dwOldStyle = m_ListCtr.GetExtendedStyle();
	m_ListCtr.SetExtendedStyle(dwOldStyle | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	CRect rc;
	m_ListCtr.GetClientRect(rc);
	int nWidth = rc.Width();
	// ������
	m_ListCtr.InsertColumn(0, L"DLL����", LVCFMT_CENTER, nWidth / 5);
	m_ListCtr.InsertColumn(1, L"Module(RVA)", LVCFMT_CENTER, nWidth / 5);
	m_ListCtr.InsertColumn(2, L"�ӳ�����IAT(RVA)", LVCFMT_CENTER, nWidth / 5);
	m_ListCtr.InsertColumn(3, L"�ӳ�����RVA��INT��", LVCFMT_CENTER, nWidth / 5);
	m_ListCtr.InsertColumn(4, L"��IAT��RVA��", LVCFMT_CENTER, nWidth / 5);
	GetdllLoadofShow();

	return TRUE;
}

void Tab_Dlltables::GetdllLoadofShow()
{
	CString str;
	RVAtoFOA foa;
	// 1. ��ȡDLL��
	PIMAGE_DOS_HEADER pDos = (PIMAGE_DOS_HEADER)m_lpBase;
	PIMAGE_NT_HEADERS pNt = (PIMAGE_NT_HEADERS)(pDos->e_lfarlc + m_lpBase);
	PIMAGE_DATA_DIRECTORY pData = (PIMAGE_DATA_DIRECTORY)&pNt->OptionalHeader.DataDirectory[13];
	PIMAGE_DELAYLOAD_DESCRIPTOR pDll = (PIMAGE_DELAYLOAD_DESCRIPTOR)(foa.RVAofFOAs(pData->VirtualAddress) + m_lpBase);

	// 2. ����RVA
	str.Format(L"%08x", pDll->DllNameRVA);
	m_ListCtr.InsertItem(0, str);
	// 3. Module RVA
	str.Format(L"%08X", pDll->ModuleHandleRVA);
	m_ListCtr.SetItemText(0, 1, str);
	// 4. �ӳ�����RVA
	str.Format(L"%08X", pDll->ImportAddressTableRVA);
	m_ListCtr.SetItemText(0, 2, str);
	// 5. �ӳ�����INT
	str.Format(L"%08X", pDll->ImportNameTableRVA);
	m_ListCtr.SetItemText(0, 3, str);
	// 6. ��IAT��RVA
	str.Format(L"%08X", pDll->BoundImportAddressTableRVA);
	m_ListCtr.SetItemText(0, 4, str);
}