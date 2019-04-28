// Tab_PEfileanalDialogbox.cpp : ʵ���ļ�
//
#include "stdafx.h"
#include "Tab_PEfileanalDialogbox.h"
#include "afxdialogex.h"
#include "Tab_FilePosition.h"
#include "Tab_SectionView.h"
#include "Tab_DirectoryTables.h"
#include "RVAtoFOA.h"
#include "FileInfo.h"
#include "windows.h"
#


// Tab_PEfileanalDialogbox �Ի���

IMPLEMENT_DYNAMIC(Tab_PEfileanalDialogbox, CDialogEx)

Tab_PEfileanalDialogbox::Tab_PEfileanalDialogbox(CWnd* pParent /*=NULL*/)
	: CDialogEx(Tab_PEfileanalDialogbox::IDD, pParent)
	, m_entryPoint(_T(""))
	, m_baseAddres(_T(""))
	, m_codeStart(_T(""))
	, m_fileSize(_T(""))
	, m_fileAli(_T(""))
	, m_messageFlag(_T(""))
	, m_fileTime(_T(""))
	, m_textPath(_T(""))
	, m_blocks(_T(""))
	, m_childsystems(_T(""))
	, m_dataStarts(_T(""))
	, m_rvaNames(_T(""))
{

}

Tab_PEfileanalDialogbox::~Tab_PEfileanalDialogbox()
{
}

void Tab_PEfileanalDialogbox::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_START, m_entryPoint);
	DDX_Text(pDX, IDC_BASEADDRESS, m_baseAddres);
	DDX_Text(pDX, IDC_CODESTART, m_codeStart);
	DDX_Text(pDX, IDC_FILESIZE, m_fileSize);
	DDX_Control(pDX, IDC_DATASTART, m_dataStart);
	DDX_Control(pDX, IDC_BLOCK, m_block);
	DDX_Control(pDX, IDC_CHILDSYSTEM, m_childSystem);
	DDX_Control(pDX, IDC_FLAG, m_flag);
	DDX_Text(pDX, IDC_FILEALI, m_fileAli);
	DDX_Control(pDX, IDC_RVANAME, m_rvaName);
	DDX_Text(pDX, IDC_MESSAGEFLAG, m_messageFlag);
	DDX_Text(pDX, IDC_FILETIME, m_fileTime);
	DDX_Text(pDX, IDC_EXEPATH, m_textPath);
	DDX_Text(pDX, IDC_BLOCK, m_blocks);
	DDX_Text(pDX, IDC_CHILDSYSTEM, m_childsystems);
	DDX_Text(pDX, IDC_DATASTART, m_dataStarts);
	DDX_Text(pDX, IDC_RVANAME, m_rvaNames);
}

BEGIN_MESSAGE_MAP(Tab_PEfileanalDialogbox, CDialogEx)
	ON_WM_DROPFILES()
	ON_BN_CLICKED(IDC_BUTTON15, &Tab_PEfileanalDialogbox::OnBnClickedButton15)
	ON_BN_CLICKED(IDC_BUTTON19, &Tab_PEfileanalDialogbox::OnBnClickedButton19)
	ON_BN_CLICKED(IDC_BUTTON14, &Tab_PEfileanalDialogbox::OnBnClickedButton14)
	ON_BN_CLICKED(IDC_BUTTON18, &Tab_PEfileanalDialogbox::OnBnClickedButton18)
END_MESSAGE_MAP()

// Tab_PEfileanalDialogbox ��Ϣ�������

BOOL Tab_PEfileanalDialogbox::OnInitDialog()
{
	CDialogEx::OnInitDialog();


	return TRUE;
}

// ��Ӧ��קPE��Ϣ
void Tab_PEfileanalDialogbox::OnDropFiles(HDROP hDropInfo)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	// 1.�����ק��Ŀ
	int DropCount = DragQueryFile(hDropInfo, -1, NULL, 0);
	// 2.�����ȡ��·����Ϣ
	char wcStr[MAX_PATH] = {};
	for (int i = 0; i < DropCount; i++)
	{
		// 3.�ǵ�����ַ���
		wcStr[0] = 0;
		// 4.��ȡ·����
		DragQueryFileA(hDropInfo, i, wcStr, MAX_PATH);
		m_textPath = wcStr;
	}
	// 5.���ļ����ص��ڴ�
	m_lpBase = FileLoadMemory(wcStr);
	if (!m_lpBase)
	{
		AfxMessageBox(L"FileLoadMemory() faulier!");
		return;
	}
	if (!IsPEfile(m_lpBase))
	{
		AfxMessageBox(L"file not`s PE");
		return;
	}
	// 6.�������µ�����
	ShowHeaderInfo(m_lpBase);
	// 7.���µ�������
	UpdateData(FALSE);
	// 8.�ͷ��ڴ�
	DragFinish(hDropInfo);
	// 
	// SetBkColor();
	CDialogEx::OnDropFiles(hDropInfo);
}

// �ڴ�����ļ�
char* Tab_PEfileanalDialogbox::FileLoadMemory(char* lpFilePath)
{
	// ��ȡ�ļ����
	HANDLE hFile = CreateFileA(lpFilePath, GENERIC_READ, FALSE, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hFile == INVALID_HANDLE_VALUE)
	{
		AfxMessageBox(L"CreateFileA() failuer!");
		exit(EXIT_FAILURE);
	}
	// ��ȡ�ļ���С
	DWORD dwSize = GetFileSize(hFile, NULL);
	m_fileSize.Format(L"%d", dwSize);
	// ������
	m_lpBase = new char[dwSize]{};
	// ���ļ�
	DWORD dwCount = 1;
	BOOL  bRet = ReadFile(hFile, m_lpBase, dwSize, &dwCount, NULL);
	if (bRet){
		// ��ֵ��ȫ�ֱ���
		RVAtoFOA::g_NamelpBase = this->m_lpBase;
		return m_lpBase;
	}
	CloseHandle(hFile);
	delete m_lpBase;
	return 0;

}

// PE�ļ��ж�
BOOL Tab_PEfileanalDialogbox::IsPEfile(char* lpBase)
{
	// 1.��ȡMZУ��(e_magic)
	PIMAGE_DOS_HEADER pDos = (PIMAGE_DOS_HEADER)this->m_lpBase;
	if (pDos->e_magic != IMAGE_DOS_SIGNATURE)
		return FALSE;
	// 2.��ȡPEУ��(signature)
	PIMAGE_NT_HEADERS pNt = (PIMAGE_NT_HEADERS)(pDos->e_lfanew + m_lpBase);
	if (pNt->Signature != IMAGE_NT_SIGNATURE)
		return FALSE;

	return TRUE;
}

// ��ʾPEͷ����Ϣ
void Tab_PEfileanalDialogbox::ShowHeaderInfo(char* lpBase)
{
	DWORD swap;
	WORD swaps;
	PIMAGE_DOS_HEADER pDos = (PIMAGE_DOS_HEADER)lpBase;
	PIMAGE_NT_HEADERS pNt = (PIMAGE_NT_HEADERS)(pDos->e_lfanew + lpBase);
	// ��ڵ�
	swap = pNt->OptionalHeader.AddressOfEntryPoint + pNt->OptionalHeader.ImageBase;
	m_entryPoint.Format(L"%08X", swap);
	// ����ַs
	swap = pNt->OptionalHeader.ImageBase;
	e_addrssbase = swap;
	m_baseAddres.Format(L"%08X", swap);
	// ���θ���
	swap = pNt->FileHeader.NumberOfSections;
	// ������ʼ
	swap = pNt->FileHeader.TimeDateStamp;
	m_fileTime.Format(L"%d", swap);
	// �ļ���С
	swap = pNt->OptionalHeader.SizeOfCode;
	m_fileTime.Format(L"%d", swap);
	// �ļ�����
	swap = pNt->OptionalHeader.FileAlignment;
	m_fileAli.Format(L"%X", swap);
	// �����
	swap = pNt->OptionalHeader.SectionAlignment;
	m_blocks.Format(L"%X", swap);
	// ��ϵͳ
	swaps = pNt->OptionalHeader.Subsystem;
	m_childsystems.Format(L"%d", swaps);
	// ��Ϣ��־
	swaps = pNt->OptionalHeader.Magic;
	m_messageFlag.Format(L"%X", swaps);
	// ����Ŀ¼
	swap = pNt->FileHeader.NumberOfSections;
	m_codeStart.Format(L"%d", swap);
	// ������ʼ
	swap = pNt->OptionalHeader.BaseOfData;
	m_dataStarts.Format(L"%08X", swap);
	// ����Ŀ¼����
	swap = pNt->OptionalHeader.NumberOfRvaAndSizes;
	m_rvaNames.Format(L"%d", swap);
}

// Ŀ¼����Ϣ
void Tab_PEfileanalDialogbox::OnBnClickedButton15()
{
	// ����Ŀ¼����Ϣ
	Tab_DirectoryTables direct;
	direct.m_lpBases = m_lpBase;
	direct.DoModal();
}

// λ�ü�����(BUG�޸�)
void Tab_PEfileanalDialogbox::OnBnClickedButton19()
{
	if (0 == m_lpBase)
	{
		AfxMessageBox(L"������ק�ļ�");
		return;
	}
	PIMAGE_DOS_HEADER pDos = (PIMAGE_DOS_HEADER)m_lpBase;
	PIMAGE_NT_HEADERS pNt = (PIMAGE_NT_HEADERS)(pDos->e_lfanew + m_lpBase);
	// ��ʽ  RVA(ת) - RVA(����) + OFFSET(����) = OFFSET(�ļ�)
	// 1.��������
	Tab_FilePosition tab_FOA;
	// 2.VR���ػ�ַ = OEP + ImaBase
	tab_FOA.m_ImageBase = pNt->OptionalHeader.ImageBase + pNt->OptionalHeader.AddressOfEntryPoint;
	tab_FOA.DoModal();
}

// ���α�鿴
void Tab_PEfileanalDialogbox::OnBnClickedButton14()
{
	// �����´���
	Tab_SectionView section;
	section.SetlpBase(m_lpBase);
	section.DoModal();
}

// �ļ���Ϣ����
void Tab_PEfileanalDialogbox::OnBnClickedButton18()
{
	UpdateData(TRUE);
	FileInfo getFileInfo;
	getFileInfo.cFilePath = m_textPath;
	getFileInfo.DoModal();
}
