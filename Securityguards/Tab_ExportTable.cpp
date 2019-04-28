// Tab_ExportTable.cpp : ʵ���ļ�
//
#pragma once
#include "stdafx.h"
#include "Tab_ExportTable.h"
#include "afxdialogex.h"
#include "RVAtoFOA.h"


// Tab_ExportTable �Ի���

IMPLEMENT_DYNAMIC(Tab_ExportTable, CDialogEx)

Tab_ExportTable::Tab_ExportTable(CWnd* pParent /*=NULL*/)
	: CDialogEx(Tab_ExportTable::IDD, pParent)
	// , m_OutOffset(_T(""))
	, m_VAULES(_T(""))
	, m_exBase(_T(""))
	, m_exName(_T(""))
	// , m_exStr(_T(""))
	, m_exFunnumber(_T(""))
	, m_exFun(_T(""))
	, m_exFunaddress(_T(""))
	, m_exNameaddress(_T(""))
	, m_exNumbers(_T(""))
{

}

Tab_ExportTable::~Tab_ExportTable()
{
}

void Tab_ExportTable::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	// DDX_Text(pDX, IDC_OUTOFFSET, m_OutOffset);
	DDX_Text(pDX, IDC_VALUES, m_VAULES);
	DDX_Text(pDX, IDC_EXBASE, m_exBase);
	DDX_Text(pDX, IDC_EXNAME, m_exName);
	// DDX_Text(pDX, IDC_EXSTR, m_exStr);
	DDX_Text(pDX, IDC_EXFUNNUMBER, m_exFunnumber);
	DDX_Text(pDX, IDC_EXFUN, m_exFun);
	DDX_Text(pDX, IDC_EXFUNADDRESS, m_exFunaddress);
	DDX_Text(pDX, IDC_EXNAMEADDRESS, m_exNameaddress);
	DDX_Text(pDX, IDC_EXNUMBERS, m_exNumbers);
	DDX_Control(pDX, IDC_EXLIST1, m_exListCtr);
}

BEGIN_MESSAGE_MAP(Tab_ExportTable, CDialogEx)
END_MESSAGE_MAP()

// Tab_ExportTable ��Ϣ�������

BOOL Tab_ExportTable::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	// ��ȡ���
	DWORD dwOldStyle;
	dwOldStyle = m_exListCtr.GetExtendedStyle();
	m_exListCtr.SetExtendedStyle(dwOldStyle | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	CRect rc;
	m_exListCtr.GetClientRect(rc);
	int nWidth = rc.Width();
	// ������
	m_exListCtr.InsertColumn(0, L"���", LVCFMT_CENTER, nWidth / 4);
	m_exListCtr.InsertColumn(1, L"RVA", LVCFMT_CENTER, nWidth / 4);
	m_exListCtr.InsertColumn(2, L"ƫ����", LVCFMT_CENTER, nWidth / 4);
	m_exListCtr.InsertColumn(3, L"������", LVCFMT_CENTER, nWidth / 4);
	GetExportInfo(m_lpBases);
	return TRUE;
}

// ��ȡ��������Ϣ
void Tab_ExportTable::GetExportInfo(char* lpBase)
{
	RVAtoFOA offset;
	PIMAGE_DOS_HEADER pDos = (PIMAGE_DOS_HEADER)lpBase;
	PIMAGE_NT_HEADERS pNt = (PIMAGE_NT_HEADERS)(pDos->e_lfanew + lpBase);
	PIMAGE_DATA_DIRECTORY pData = (PIMAGE_DATA_DIRECTORY)pNt->OptionalHeader.DataDirectory;
	// 1.RVAת����ַ
	DWORD  pExprotFOA = offset.RVAofFOAs(pData->VirtualAddress);
	// 2.�ҵ�������ַ
	PIMAGE_EXPORT_DIRECTORY pExportTable = (PIMAGE_EXPORT_DIRECTORY)(pExprotFOA + m_lpBases);
	// ����ֵ
	m_VAULES.Format(L"%08X", pExportTable->TimeDateStamp);
	// ��Ż�ַ
	m_exBase.Format(L"%08X", pExportTable->Base);
	// ����
	m_exName.Format(L"%08X", pExportTable->Name);
	// �����Ӵ�
	m_exStr;
	// ������ַ
	m_exFunaddress.Format(L"%08X", pExportTable->AddressOfFunctions);
	// �������Ƶ�ַ
	m_exNameaddress.Format(L"%08X", pExportTable->AddressOfNames);
	// ������ŵ�ַ
	m_exNumbers.Format(L"%08X", pExportTable->AddressOfNameOrdinals);
	// 3.��������
	DWORD dwFunCount = pExportTable->NumberOfFunctions;
	m_exFunnumber.Format(L"%d", dwFunCount);
	// 4.������������
	DWORD dwOrdinalCount = pExportTable->NumberOfNames;
	m_exFun.Format(L"%d", dwFunCount);
	// 5.��ַ��
	DWORD* pFunAdd = (DWORD*)(offset.RVAofFOAs(pExportTable->AddressOfFunctions) + lpBase);
	// 6.�������Ʊ�
	DWORD* pNameAddr = (DWORD*)(offset.RVAofFOAs(pExportTable->AddressOfNames) + lpBase);
	// 7.��ű�
	DWORD* pOrdinalAddr = (DWORD*)(offset.RVAofFOAs(pExportTable->AddressOfNameOrdinals) + lpBase);
	// 8.ѭ��������Ϣ
	CString str;
	_SAVERVAOFOFFSET obj = {};
	for (DWORD i = 0; i < dwFunCount; ++i)
	{
		// 9.�����0������Ч��ַ 
		if (0 == pFunAdd[i]){
			continue;
		}
		// 10.������ű��Ƿ������, ����������
		BOOL bFlag = FALSE;
		for (DWORD j = 0; j < dwOrdinalCount; ++j)
		{
			bFlag = TRUE;
			DWORD dwNameRVA = pNameAddr[j];
			// �������
			str.Format(L"%d", pOrdinalAddr[i]);
			m_exListCtr.InsertItem(i, str);
			// RVA
			str.Format(L"%08X", dwNameRVA);
			m_exListCtr.SetItemText(i, 1, str);
			// ������
			str = (char *)(offset.RVAofFOAs(dwNameRVA) + lpBase);
			m_exListCtr.SetItemText(i, 3, str);
			// offset
			obj = offset.GetRvaofFOA(dwNameRVA);
			str.Format(L"%08X", obj.offset);
			m_exListCtr.SetItemText(i, 2, str);

		}
		if (!bFlag){
			// ������NULL ������� %04X
			str.Format(L"%d", (i + pExportTable->Base));
			m_exListCtr.SetItemText(i, 0, str);
		}
	}
	UpdateData(FALSE);
}
