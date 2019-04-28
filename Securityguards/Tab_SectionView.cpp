// Tab_SectionView.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Tab_SectionView.h"
#include "afxdialogex.h"
#include <tchar.h>


// Tab_SectionView �Ի���

const TCHAR Tab_SectionView::strName[6][20] = { L"����", L"��ʼRVA", L"���δ�С(���غ�)", L"�ļ�ƫ��", L"���δ�С(�ļ���)", L"��������" };

IMPLEMENT_DYNAMIC(Tab_SectionView, CDialogEx)

Tab_SectionView::Tab_SectionView(CWnd* pParent /*=NULL*/)
	: CDialogEx(Tab_SectionView::IDD, pParent)
{

}

Tab_SectionView::~Tab_SectionView()
{
}

void Tab_SectionView::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_listCtr);
}


BEGIN_MESSAGE_MAP(Tab_SectionView, CDialogEx)
END_MESSAGE_MAP()


// Tab_SectionView ��Ϣ�������

BOOL Tab_SectionView::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 1.��ʼ�����
	CRect rc;
	m_listCtr.GetClientRect(rc);
	int nWdith = rc.Width();
	DWORD dwOldStyle;
	dwOldStyle = m_listCtr.GetExtendedStyle();
	m_listCtr.SetExtendedStyle(dwOldStyle | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	// 2.��ʼ���б�
	for (int i = 0; i < 6; ++i)
	{
		m_listCtr.InsertColumn(i, strName[i], LVCFMT_CENTER, nWdith / 6);
	}
	// 3.��ʾ���α�����
	ShowDateInfo();
	return TRUE; 
}

// ��ʾ���α�����
void Tab_SectionView::ShowDateInfo()
{

	// 1.��ȡDosHeader
	PIMAGE_DOS_HEADER pDos = (PIMAGE_DOS_HEADER)m_lpBase;
	// 2.��ȡNTHeadrs
	PIMAGE_NT_HEADERS pNt = (PIMAGE_NT_HEADERS)(pDos->e_lfanew + m_lpBase);
	// 3.��ȡSectionheads
	PIMAGE_SECTION_HEADER pSection = IMAGE_FIRST_SECTION(pNt);
	// 4.��ȡ���εĸ���
	DWORD dwCount = pNt->FileHeader.NumberOfSections;
	// 5.ѭ���������Σ��м������Σ�
	for (DWORD i = 0; i < dwCount; ++i)
	{
		auto strName = (char *)pSection->Name;
		CString str = strName;
		m_listCtr.InsertItem(i, str);
		buf[0] = 0;
		_stprintf_s(buf, MAX_PATH, L"%08X", pSection->VirtualAddress);
		m_listCtr.SetItemText(i, 1, buf);
		buf[0] = 0;
		_stprintf_s(buf, MAX_PATH, L"%08X", pSection->SizeOfRawData);
		m_listCtr.SetItemText(i, 2, buf);
		buf[0] = 0;
		_stprintf_s(buf, MAX_PATH, L"%08X", pSection->PointerToRawData);
		m_listCtr.SetItemText(i, 3, buf);
		buf[0] = 0;
		_stprintf_s(buf, MAX_PATH, L"%08X", pSection->Misc.VirtualSize);
		m_listCtr.SetItemText(i, 4, buf);
		buf[0] = 0;
		_stprintf_s(buf, MAX_PATH, L"%08X", pSection->Characteristics);
		m_listCtr.SetItemText(i, 5, buf);
		buf[0] = 0;
		++pSection;
	} 
}