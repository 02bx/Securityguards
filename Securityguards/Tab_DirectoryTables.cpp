// Tab_DirectoryTables.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Tab_DirectoryTables.h"
#include "afxdialogex.h"
#include "Tab_ExportTable.h"
#include "Tab_ImportTable.h"
#include "Tab_RELOCATION.h"
#include "Tab_resourceTables.h"
#include "Tab_TlsTables.h"
#include "Tab_Dlltables.h"


// Tab_DirectoryTables �Ի���

IMPLEMENT_DYNAMIC(Tab_DirectoryTables, CDialogEx)

Tab_DirectoryTables::Tab_DirectoryTables(CWnd* pParent /*=NULL*/)
	: CDialogEx(Tab_DirectoryTables::IDD, pParent)
	, m_indexexport(_T(""))
	, m_indexexports(_T(""))
	, m_imports(_T(""))
	, m_import(_T(""))
	, m_indexSource(_T(""))
	, m_indexSources(_T(""))
	, m_Exect(_T(""))
	, m_Exects(_T(""))
	, m_Security(_T(""))
	, m_Securitys(_T(""))
	, m_Reactions(_T(""))
	, m_RELOCATION(_T(""))
	, m_Debug(_T(""))
	, m_Debugs(_T(""))
	, m_Copyright(_T(""))
	, m_Copyrights(_T(""))
	, m_Global(_T(""))
	, m_Globals(_T(""))
	, m_ThreadStorag(_T(""))
	, m_ThreadStorags(_T(""))
	, m_Load(_T(""))
	, m_Loads(_T(""))
	, m_Importaddress(_T(""))
	, m_importaddresses(_T(""))
	, m_BindDirectory(_T(""))
	, m_BindDirectorys(_T(""))
	, m_Delay(_T(""))
	, m_Delays(_T(""))
	, m_Com(_T(""))
	, m_Coms(_T(""))
	, m_Keeps(_T(""))
	, m_Keep(_T(""))
{

}

Tab_DirectoryTables::~Tab_DirectoryTables()
{
}

void Tab_DirectoryTables::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//  DDX_Text(pDX, IDC_STATICexport, m_indexexport);
	//  DDX_Text(pDX, IDC_STATICexports, m_indexexports);
	DDX_Text(pDX, IDC_STATICexport, m_indexexport);
	DDX_Text(pDX, IDC_STATICexports, m_indexexports);
	DDX_Text(pDX, IDC_STATICimport, m_imports);
	DDX_Text(pDX, IDC_STATICimports, m_import);
	DDX_Text(pDX, IDC_STATICsourc, m_indexSource);
	DDX_Text(pDX, IDC_STATICsourcs, m_indexSources);
	//  DDX_Control(pDX, IDC_Exect, m_Exect);
	//  DDX_Control(pDX, IDC_Exects, m_Exects);
	DDX_Text(pDX, IDC_Exect, m_Exect);
	DDX_Text(pDX, IDC_Exects, m_Exects);
	DDX_Text(pDX, IDC_SECURITY, m_Security);
	DDX_Text(pDX, IDC_SECURITYS, m_Securitys);
	DDX_Control(pDX, IDC_RELOCATION, m_Relocation);
	DDX_Text(pDX, IDC_RELOCATIONS, m_Reactions);
	DDX_Text(pDX, IDC_RELOCATION, m_RELOCATION);
	DDX_Text(pDX, IDC_DEBUG, m_Debug);
	DDX_Text(pDX, IDC_DEBUGS, m_Debugs);
	DDX_Text(pDX, IDC_COPYRIGHT, m_Copyright);
	DDX_Text(pDX, IDC_COPYRIGHTS, m_Copyrights);
	DDX_Text(pDX, IDC_GLOABLE, m_Global);
	DDX_Text(pDX, IDC_GLOABLES, m_Globals);
	DDX_Text(pDX, IDC_ThreadStorag, m_ThreadStorag);
	DDX_Text(pDX, IDC_ThreadStorags, m_ThreadStorags);
	DDX_Text(pDX, IDC_LOAD, m_Load);
	DDX_Text(pDX, IDC_LOADSS, m_Loads);
	DDX_Text(pDX, IDC_IMPORTADDRESS, m_Importaddress);
	DDX_Text(pDX, IDC_IMPORTADDRESSES, m_importaddresses);
	DDX_Text(pDX, IDC_BINDDIRECTORY, m_BindDirectory);
	DDX_Text(pDX, IDC_BINDDIRECTORYS, m_BindDirectorys);
	DDX_Text(pDX, IDC_DELAY, m_Delay);
	DDX_Text(pDX, IDC_DELAYS, m_Delays);
	DDX_Text(pDX, IDC_COM, m_Com);
	DDX_Text(pDX, IDC_COMS, m_Coms);
	DDX_Text(pDX, IDC_KEEP, m_Keeps);
	DDX_Text(pDX, IDC_KEEPS, m_Keep);
}

BEGIN_MESSAGE_MAP(Tab_DirectoryTables, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON11, &Tab_DirectoryTables::OnBnClickedButton11)
	ON_BN_CLICKED(IDC_BUTTON13, &Tab_DirectoryTables::OnBnClickedButton13)
	ON_BN_CLICKED(IDC_BUTTON16, &Tab_DirectoryTables::OnBnClickedButton16)
	ON_BN_CLICKED(IDC_BUTTON15, &Tab_DirectoryTables::OnBnClickedButton15)
	ON_BN_CLICKED(IDC_BUTTON12, &Tab_DirectoryTables::OnBnClickedButton12)
	ON_BN_CLICKED(IDC_BUTTON20, &Tab_DirectoryTables::OnBnClickedButton20)
END_MESSAGE_MAP()

// Tab_DirectoryTables ��Ϣ�������

BOOL Tab_DirectoryTables::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	PIMAGE_DOS_HEADER pDos = (PIMAGE_DOS_HEADER)m_lpBases;
	PIMAGE_NT_HEADERS32 pNt = (PIMAGE_NT_HEADERS32)(pDos->e_lfanew + m_lpBases);
	PIMAGE_OPTIONAL_HEADER32 pOptionalHeader = &(pNt->OptionalHeader);
	// 1.��ȡ���ݱ�
	pDataDirectory = pOptionalHeader->DataDirectory;
	// 2.��ʾÿ�����RVA�ʹ�С
	ShowDateofsize(pDataDirectory);
	return TRUE; 
}

// ��ʾ����RVA����С
void Tab_DirectoryTables::ShowDateofsize(PIMAGE_DATA_DIRECTORY pDataDirectory)
{
	// 1.�����
	m_indexexport.Format(L"%08X", pDataDirectory[0].VirtualAddress);
	m_indexexports.Format(L"%08X", pDataDirectory[0].Size);
	// 2.�����
	m_imports.Format(L"%08X", pDataDirectory[1].VirtualAddress);
	m_import.Format(L"%08X", pDataDirectory[1].Size);
	// 3.��Դ��
	m_indexSource.Format(L"%08X", pDataDirectory[2].VirtualAddress);
	m_indexSources.Format(L"%08X", pDataDirectory[2].Size);
	// 4.�쳣����
	m_Exect.Format(L"%08X", pDataDirectory[3].VirtualAddress);
	m_Exects.Format(L"%08X", pDataDirectory[3].Size);
	// 5.��ȫ�ṹ
	m_Security.Format(L"%08X", pDataDirectory[4].VirtualAddress);
	m_Securitys.Format(L"%08X", pDataDirectory[4].Size);
	// 6.�ض����
	m_RELOCATION.Format(L"%08X", pDataDirectory[5].VirtualAddress);
	m_Reactions.Format(L"%08X", pDataDirectory[5].Size);
	// 7.������Ϣ
	m_Debug.Format(L"%08X", pDataDirectory[6].VirtualAddress);
	m_Debugs.Format(L"%08X", pDataDirectory[6].Size);
	// 8.��Ȩ
	m_Copyright.Format(L"%08X", pDataDirectory[7].VirtualAddress);
	m_Copyrights.Format(L"%08X", pDataDirectory[7].Size);
	// 9.ȫ��ָ��
	m_Global.Format(L"%08X", pDataDirectory[8].VirtualAddress);
	m_Globals.Format(L"%08X", pDataDirectory[8].Size);
	// 10.�ֲ߳̾��洢
	m_ThreadStorag.Format(L"%08X", pDataDirectory[9].VirtualAddress);
	m_ThreadStorags.Format(L"%08X", pDataDirectory[9].Size);
	// 11.��������
	m_Load.Format(L"%08X", pDataDirectory[10].VirtualAddress);
	m_Loads.Format(L"%08X", pDataDirectory[10].Size);
	// 12.�����ַ��
	m_Importaddress.Format(L"%08X", pDataDirectory[11].VirtualAddress);
	m_importaddresses.Format(L"%08X", pDataDirectory[11].Size);
	// 13.������Ŀ¼��
	m_BindDirectory.Format(L"%08X", pDataDirectory[12].VirtualAddress);
	m_BindDirectorys.Format(L"%08X", pDataDirectory[12].Size);
	// 14.�ӳ���������
	m_Delay.Format(L"%08X", pDataDirectory[13].VirtualAddress);
	m_Delays.Format(L"%08X", pDataDirectory[13].Size);
	// 15.COM
	m_Com.Format(L"%08X", pDataDirectory[14].VirtualAddress);
	m_Coms.Format(L"%08X", pDataDirectory[14].Size);
	// 16.����
	m_Keeps.Format(L"%08X", pDataDirectory[15].VirtualAddress);
	m_Keep.Format(L"%08X", pDataDirectory[15].Size);
	UpdateData(FALSE);
}

// ��������ϸ����
void Tab_DirectoryTables::OnBnClickedButton11()
{
	// ��ȡpDataDuretory�ı�ͷ
	if (!pDataDirectory->VirtualAddress){
		AfxMessageBox(L"exeû�е�����");
		return;
	}
	Tab_ExportTable exports;
	exports.m_lpBases = this->m_lpBases;
	exports.DoModal();
}

// �������ϸ����
void Tab_DirectoryTables::OnBnClickedButton13()
{
	Tab_ImportTable imports;
	imports.m_ImlpBase = this->m_lpBases;
	imports.DoModal();
}

// �ض�λ����ϸ����
void Tab_DirectoryTables::OnBnClickedButton16()
{
	Tab_RELOCATION relocation;
	relocation.m_lpBaseReLoc = this->m_lpBases;
	relocation.DoModal();
}

// ��̬�ı���ʾ�ṹ���е�����(TLS��)
void Tab_DirectoryTables::OnBnClickedButton15()
{
	Tab_TlsTables tlsTable;
	tlsTable.m_lpBase = this->m_lpBases;
	tlsTable.DoModal();
}

// ��Դ��
void Tab_DirectoryTables::OnBnClickedButton12()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	Tab_resourceTables resour;
	resour.m_lpBase = this->m_lpBases;
	resour.DoModal();
}

// DLL�ӳٱ�
void Tab_DirectoryTables::OnBnClickedButton20()
{
	Tab_Dlltables dllLoad;
	dllLoad.m_lpBase = this->m_lpBases;
	dllLoad.DoModal();
}
