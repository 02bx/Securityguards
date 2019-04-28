// FileInfo.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "FileInfo.h"
#include "afxdialogex.h"
#include "Psapi.h"
#include "MD5.h"

// FileInfo �Ի���

CImageList* FileInfo::Icon = NULL;

IMPLEMENT_DYNAMIC(FileInfo, CDialogEx)

FileInfo::FileInfo(CWnd* pParent /*=NULL*/)
	: CDialogEx(FileInfo::IDD, pParent)
	, m_seFileType(_T(""))
	, m_seFileWZ(_T(""))
	, m_seFileSizeof(_T(""))
	, m_seFileCreate(_T(""))
	, m_seFileModify(_T(""))
	, m_seFileAccess(_T(""))
	, m_seEditFileName(_T(""))
	, m_seEditMD5(_T(""))
{

}

FileInfo::~FileInfo()
{
}

void FileInfo::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_SEFILETYPE, m_seFileType);
	DDX_Text(pDX, IDC_SEFILEWZ, m_seFileWZ);
	DDX_Text(pDX, IDC_SEFILESIZEOF, m_seFileSizeof);
	DDX_Text(pDX, IDC_SEFILECREATE, m_seFileCreate);
	DDX_Text(pDX, IDC_SEFILEMODIFY, m_seFileModify);
	DDX_Text(pDX, IDC_SEACCESSTIME, m_seFileAccess);
	DDX_Text(pDX, IDC_SEEDITNAME, m_seEditFileName);
	DDX_Text(pDX, IDC_EDIT2, m_seEditMD5);
}


BEGIN_MESSAGE_MAP(FileInfo, CDialogEx)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()

// FileInfo ��Ϣ�������


BOOL FileInfo::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	// ��ȡ�ļ���Ϣ
	GetFileInfo(cFilePath);
	//m_bush.CreateSolidBrush(RGB(255, 255, 255));
	return TRUE;
}

// ��ȡ�ļ���ϸ��Ϣ
void FileInfo::GetFileInfo(CString str)
{
	MD5VAL md5;
	// ��ȡ�ļ�·��
	TCHAR Path[MAX_PATH] = {};
	SYSTEMTIME System = { 0 };
	// ���ڱ�����ʱ�ַ����Ļ�����
	TCHAR TempBuffer[MAX_PATH] = { 0 };
	// VS_FIXEDFILEINFO 
	WIN32_FIND_DATA stFileData = { 0 };
	HANDLE hFile = FindFirstFile(str, &stFileData);
	if (hFile == INVALID_HANDLE_VALUE)
		return;
	// 1. ����ļ���
	m_seEditFileName = stFileData.cFileName;
	// 2. ��Ӵ���ʱ��
	FileTimeToSystemTime(&stFileData.ftCreationTime, &System);
	_stprintf(TempBuffer, TEXT("%d/%d/%d %d:%d:%d"), System.wYear,
		System.wMonth, System.wDay, System.wHour, System.wMinute, System.wSecond);
	m_seFileCreate = TempBuffer;
	// 3. ����ļ��޸�ʱ��
	FileTimeToSystemTime(&stFileData.ftLastWriteTime, &System);
	_stprintf(TempBuffer, TEXT("%d/%d/%d %d:%d:%d"), System.wYear,
		System.wMonth, System.wDay, System.wHour, System.wMinute, System.wSecond);
	m_seFileModify = TempBuffer;
	// 4. ���������
	FileTimeToSystemTime(&stFileData.ftLastAccessTime, &System);
	_stprintf(TempBuffer, TEXT("%d/%d/%d %d:%d:%d"), System.wYear,
		System.wMonth, System.wDay, System.wHour, System.wMinute, System.wSecond);
	m_seFileAccess = TempBuffer;
	TempBuffer[0] = 0;
	// 5. �ж��ǲ���Ŀ¼  
	if (stFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
		_tcscat(TempBuffer, TEXT("Ŀ¼ "));
	else
		_tcscat(TempBuffer, TEXT("�ļ� "));
	m_seFileType = TempBuffer;
	// 6. ��ʾ��ǰ�ļ��Ĵ�С
	TempBuffer[0] = 0;
	if (stFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
		_tcscat(TempBuffer, TEXT("-"));
	else
	{
		if (stFileData.nFileSizeLow > 1073741824)
			_stprintf(TempBuffer, TEXT("%.2lfGB"), stFileData.nFileSizeLow / 1024.0 / 1024.0 / 1024.0);
		else if (stFileData.nFileSizeLow > 1048576)
			_stprintf(TempBuffer, TEXT("%.2lfMB"), stFileData.nFileSizeLow / 1024.0 / 1024.0);
		else
			_stprintf(TempBuffer, TEXT("%.2lfKB"), stFileData.nFileSizeLow / 1024.0 / 1024.0);
	}
	m_seFileSizeof = TempBuffer;
	// 7. ����
	// �ж��ǲ������ص�
	if (stFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
		_tcscat(TempBuffer, TEXT("���� "));
	// �ж��ǲ���ֻ����
	if (stFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
		_tcscat(TempBuffer, TEXT("ֻ��"));
	m_seFileWZ = TempBuffer;
	GetModuleFileNameEx(hFile, NULL, Path, MAX_PATH);
	// MD5����
	char FileName[MAX_PATH] = { 0 };
	char *p = FileName;
	memset(FileName, 0, sizeof(FileName));
	// strcpy(FileName, str.GetBuffer(str.GetLength()));
	// sprintf ������
	// p = (LPSTR)(LPCSTR)str;
	// ת�ɿ��ַ�
	sprintf(FileName, "%ws", str);
	m_seEditMD5 = md5FileValue(FileName);
	// ��ȡ��Ϣ
	SHFILEINFOW shfileinfo;
	SHGetFileInfo(Path, 0, &shfileinfo, sizeof(SHFILEINFOW), SHGFI_ICON);
	//	Icon->Add(shfileinfo.hIcon);
	//	m_ICon.SetIcon((HBITMAP)Icon->);
	// ���±���
	UpdateData(FALSE);
}

HBRUSH FileInfo::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);
	if (nCtlColor == CTLCOLOR_DLG)
	{
		return  m_bush;
	}
	// TODO:  ���Ĭ�ϵĲ������軭�ʣ��򷵻���һ������
	return hbr;
}
