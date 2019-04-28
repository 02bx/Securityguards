// Tab_RELOCATION.cpp : ʵ���ļ�
//
#pragma once
#include "stdafx.h"
#include "Tab_RELOCATION.h"
#include "afxdialogex.h"
#include "RVAtoFOA.h"


// Tab_RELOCATION �Ի���

IMPLEMENT_DYNAMIC(Tab_RELOCATION, CDialogEx)

Tab_RELOCATION::Tab_RELOCATION(CWnd* pParent /*=NULL*/)
	: CDialogEx(Tab_RELOCATION::IDD, pParent)
{

}

Tab_RELOCATION::~Tab_RELOCATION()
{
}

void Tab_RELOCATION::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_RELIST1, m_ReListCtr);
	DDX_Control(pDX, IDC_RELIST2, m_ReListCtrs);
}

BEGIN_MESSAGE_MAP(Tab_RELOCATION, CDialogEx)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_RELIST1, &Tab_RELOCATION::OnLvnItemchangedRelist1)
END_MESSAGE_MAP()

// Tab_RELOCATION ��Ϣ�������

BOOL Tab_RELOCATION::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	// ==================����ȡList=========================/
	CRect rc;
	m_ReListCtr.GetClientRect(rc);
	int nWidth = rc.Width();
	DWORD dwOldStyle = m_ReListCtr.GetExtendedStyle();
	// ����������Ϣ
	m_ReListCtr.SetExtendedStyle(dwOldStyle | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_ReListCtr.InsertColumn(0, L"����", LVCFMT_CENTER, nWidth / 4);
	m_ReListCtr.InsertColumn(1, L"����", LVCFMT_CENTER, nWidth / 4);
	m_ReListCtr.InsertColumn(2, L"RVA", LVCFMT_CENTER, nWidth / 4);
	m_ReListCtr.InsertColumn(3, L"��Ŀ", LVCFMT_CENTER, nWidth / 4);

	// ���ÿ���Ŀ
	m_ReListCtrs.GetClientRect(rc);
	int nWidth1 = rc.Width();
	dwOldStyle = m_ReListCtrs.GetExtendedStyle();
	m_ReListCtrs.SetExtendedStyle(dwOldStyle | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_ReListCtrs.InsertColumn(0, L"����", LVCFMT_CENTER, nWidth1 / 6);
	m_ReListCtrs.InsertColumn(1, L"RVA", LVCFMT_CENTER, nWidth1 / 6);
	m_ReListCtrs.InsertColumn(2, L"ƫ��", LVCFMT_CENTER, nWidth1 / 6);
	m_ReListCtrs.InsertColumn(3, L"����", LVCFMT_CENTER, nWidth1 / 6);
	m_ReListCtrs.InsertColumn(4, L"FAR��ַ", LVCFMT_CENTER, nWidth1 / 6);
	m_ReListCtrs.InsertColumn(6, L"���ݽ���", LVCFMT_CENTER, nWidth1 / 6);
	// ��ʾ�����������
	SectionAnal();
	return TRUE;
}

// �������Խ��� analysis
void Tab_RELOCATION::SectionAnal()
{
	RVAtoFOA offset;
	// 1.����һ���ṹ�帨��
	typedef struct _OFFSET{
		WORD Offset : 12;
		WORD Type : 4;
	}Offset;
	PIMAGE_DOS_HEADER pDos = (PIMAGE_DOS_HEADER)m_lpBaseReLoc;
	PIMAGE_NT_HEADERS pNt = (PIMAGE_NT_HEADERS)(pDos->e_lfanew + m_lpBaseReLoc);
	// 2.��ȡ�����е�RVA
	PIMAGE_DATA_DIRECTORY pDir = &pNt->OptionalHeader.DataDirectory[5];
	DWORD dwResFOA = offset.RVAofFOAs(pDir->VirtualAddress);
	// 3.��ȡ�ض���ַ
	PIMAGE_BASE_RELOCATION pResHead = (PIMAGE_BASE_RELOCATION)(dwResFOA + m_lpBaseReLoc);
	// 4.ѭ��
	int nCount = 0;
	int index = 1;
	CString str;
	while (pResHead->SizeOfBlock != 0)
	{
		// ����һ����
		m_ReListCtr.InsertItem(nCount, NULL);
		Offset* pOffset = (Offset *)(pResHead + 1);
		// 5.��Ҫ�ض�λ (SizeofBlock - 8) / 2 = ��Ҫ�ض�λ�ĸ���
		DWORD dwCount = ((pResHead->SizeOfBlock - sizeof(IMAGE_BASE_RELOCATION)) / 2);
		// ============================List�ؼ�����================================
		// ��1�� ��������
		str.Format(L"%d", index);
		m_ReListCtr.SetItemText(nCount, 0, str);
		// ��2�� RVA�����Σ�
		auto rva = GetSection(pNt, pDir->VirtualAddress);
		str.Format(L"%08X", rva);
		m_ReListCtr.SetItemText(nCount, 2, str);
		// ��3�� ���������
		m_ReListCtr.SetItemText(nCount, 1, strName);
		// ��4�� ��Ҫ�ض������
		str.Format(L"%d", dwCount);
		m_ReListCtr.SetItemText(nCount, 3, str);
		// 6.ѭ��
		for (DWORD i = 0; i < dwCount; ++i)
		{
			if (pOffset->Type == 3){
				// ��1�� ��������
				m_ReListCtrs.InsertItem(i, NULL);
				str.Format(L"%d", i);
				m_ReListCtrs.SetItemText(i, 0, str);
				// 7.ƫ�Ƶ�ַ + ��������ַ(Base��RVA)
				DWORD dwDataFOA = offset.RVAofFOAs(pOffset->Offset + pResHead->VirtualAddress);
				// ��2�� ƫ�Ƶ�ַRVA
				str.Format(L"%08X", pResHead->VirtualAddress);
				m_ReListCtrs.SetItemText(i, 1, str);
				// ��3�� ƫ�Ƶ�ַoffset
				str.Format(L"%08X", pOffset->Offset);
				m_ReListCtrs.SetItemText(i, 2, str);
				// ��4�� ���� pOffset->Type
				str.Format(L"%08X", pOffset->Type);
				m_ReListCtrs.SetItemText(i, 3, str);
				// ��5�� FAR ��ַ 
				DWORD* fra = (DWORD *)(pOffset->Offset + m_lpBaseReLoc);
				str.Format(L"08X", *fra);
				m_ReListCtrs.SetItemText(i, 4, str);
				// ��6�� ���ݽ���
				// Ԥ��
				DWORD* pData = (DWORD*)(dwDataFOA + m_lpBaseReLoc);
				// �ض�λ���ݲ���
			}
			++pOffset;
		}
		// 8.��һ���ض�λ
		pResHead = (PIMAGE_BASE_RELOCATION)(pResHead->SizeOfBlock + (DWORD)pResHead);
		++index;
		++nCount;
	}
	UpdateData(FALSE);
}
// ����Ŀ���Խ���
void Tab_RELOCATION::BloackAnal()
{
}
// ����
DWORD Tab_RELOCATION::GetSection(PIMAGE_NT_HEADERS const pNt, DWORD const dwRVA)
{
	// ���θ���
	DWORD dwCount = pNt->FileHeader.NumberOfSections;
	// ��ȡ����ͷ
	PIMAGE_SECTION_HEADER pSection = IMAGE_FIRST_SECTION(pNt);
	for (DWORD i = 0; i < dwCount; ++i)
	{
		// ���������
		if ((dwRVA >= pSection->VirtualAddress) && (dwRVA < (pSection->VirtualAddress + pSection->SizeOfRawData))){
			// ��ȡ���ε�����
			strName.Format(L"%d", i);
			strName += "  ";
			strName += (char *)pSection->Name;
			// ��ȡ���ε�RVA
			return pSection->VirtualAddress;
		}
		++pSection;
	}
	AfxMessageBox(L"��ȡ����ʧ��!");
	return 0;
}

void Tab_RELOCATION::OnLvnItemchangedRelist1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;
}
