// Tab_CleanruDialogbox.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Tab_CleanruDialogbox.h"
#include "afxdialogex.h"
#include <algorithm>

// Tab_CleanruDialogbox �Ի���

// VS�����׺
CString Tab_CleanruDialogbox::ExtendString = { _T(".obj\\.tlog\\.lastbuildstate\\.idb\\.pdb\\.pch\\.res\\.ilk\\.exe\\.sdf\\.ipch\\.log\\.db\\.suo\\") };

// �Զ�����Ϣ��׺
CString Tab_CleanruDialogbox::UserExtendString = {};

// �ݶ� ȫ��Ψһ��ʶ
int Tab_CleanruDialogbox::FileNumbersFlag = 0;

IMPLEMENT_DYNAMIC(Tab_CleanruDialogbox, CDialogEx)

Tab_CleanruDialogbox::Tab_CleanruDialogbox(CWnd* pParent /*=NULL*/)
	: CDialogEx(Tab_CleanruDialogbox::IDD, pParent)
	, m_EditText(_T(""))
	, m_cleaFilenumber(_T(""))
	, m_cleaFileSizeof(_T(""))
	, m_cleaDeleFileCounts(_T(""))
	, m_SuffixFileNameValues(_T(""))
{

}

Tab_CleanruDialogbox::~Tab_CleanruDialogbox()
{
}

void Tab_CleanruDialogbox::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, m_TypeSelect);
	DDX_Text(pDX, IDC_EDIT1, m_EditText);
	DDX_Control(pDX, IDC_EDIT1, m_EditTexts);
	DDX_Control(pDX, IDC_BUTTON1, m_GetEditText);
	DDX_Text(pDX, IDC_CLEAFILENUMBER, m_cleaFilenumber);
	DDX_Text(pDX, IDC_CLEAFILESIZEOF, m_cleaFileSizeof);
	DDX_Control(pDX, IDC_CLEADELETEFILECOUNT, m_cleaDeleFileCount);
	DDX_Text(pDX, IDC_CLEADELETEFILECOUNT, m_cleaDeleFileCounts);
	DDX_Control(pDX, IDC_LIST2, m_cleaDeleteInfoList);
	DDX_Control(pDX, IDC_LIST1, m_cleaFileInfoList);
	DDX_Control(pDX, IDC_EDIT2, m_SuffixFileName);
	DDX_Control(pDX, IDC_BUTTON2, m_Suffix);
	DDX_Text(pDX, IDC_EDIT2, m_SuffixFileNameValues);
}

BEGIN_MESSAGE_MAP(Tab_CleanruDialogbox, CDialogEx)
	ON_CBN_SELCHANGE(IDC_COMBO1, &Tab_CleanruDialogbox::OnCbnSelchangeCombo1)
	ON_WM_DROPFILES()
	ON_BN_CLICKED(IDOK, &Tab_CleanruDialogbox::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON1, &Tab_CleanruDialogbox::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON3, &Tab_CleanruDialogbox::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON2, &Tab_CleanruDialogbox::OnBnClickedButton2)
END_MESSAGE_MAP()

// Tab_CleanruDialogbox ��Ϣ�������

BOOL Tab_CleanruDialogbox::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	m_TypeSelect.AddString(L"VS����");
	m_TypeSelect.AddString(L"�Զ�������");
	m_TypeSelect.AddString(L"���������");
	m_TypeSelect.AddString(L"ϵͳ��������");
	m_TypeSelect.SetCurSel(2);
	this->Flag = 3;
	CRect rc;
	DWORD dwOldStyle = 0;
	m_cleaFileInfoList.GetClientRect(rc);
	int nWidth = rc.Width();
	dwOldStyle = m_cleaFileInfoList.GetExtendedStyle();
	m_cleaFileInfoList.SetExtendedStyle(dwOldStyle | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_cleaDeleteInfoList.SetExtendedStyle(dwOldStyle | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_cleaFileInfoList.InsertColumn(0, L"File  Info", LVCFMT_CENTER, nWidth);
	m_cleaDeleteInfoList.InsertColumn(0, L"Delete  FileInfo", LVCFMT_CENTER, nWidth);
	// ��ʼ�������ۼƴ�С
	CountSize.QuadPart = 0;
	DestSize.QuadPart = 0;
	return TRUE;
}

// ��Ӧ����ѡ��
void Tab_CleanruDialogbox::OnCbnSelchangeCombo1()
{
	m_cleaDeleteInfoList.DeleteAllItems();
	m_cleaFileInfoList.DeleteAllItems();
	/*ֻ�Կؼ����� �� ��־λ�޸�*/
	CString str;
	int nIndex = m_TypeSelect.GetCurSel();
	m_TypeSelect.GetLBText(nIndex, str);
	if ("VS����" == str)
	{	
		this->Flag = 1;
		m_SuffixFileName.ShowWindow(SW_SHOW);
		m_Suffix.ShowWindow(SW_SHOW);
		m_EditTexts.ShowWindow(SW_HIDE);
		m_SuffixFileName.SetWindowTextW(ExtendString);
	}
	else if ("�Զ�������" == str)
	{
		this->Flag = 2;
		m_SuffixFileName.ShowWindow(SW_SHOW);
		m_Suffix.ShowWindow(SW_SHOW);
		m_EditTexts.ShowWindow(SW_SHOW);
		m_GetEditText.ShowWindow(SW_SHOW);
		m_SuffixFileName.SetWindowTextW(UserExtendString);
	}
	else if ("���������" == str)
	{
		this->Flag = 3;
		m_SuffixFileName.ShowWindow(SW_SHOW);
		m_Suffix.ShowWindow(SW_HIDE);
		m_EditTexts.ShowWindow(SW_HIDE);
	}
	else if ("ϵͳ��������" == str)
	{
		this->Flag = 4;
		m_SuffixFileName.ShowWindow(SW_SHOW);
		m_Suffix.ShowWindow(SW_HIDE);
		m_EditTexts.ShowWindow(SW_HIDE);
	}
	else
		AfxMessageBox(L"ô�л�ȡ����ȷ��Ϣ���u�v��");

}

// ��Ӧ�ļ���ק
void Tab_CleanruDialogbox::OnDropFiles(HDROP hDropInfo)
{
	PathString.clear();
	CString str;
	// 1. ��ȡ�ļ���ק��Ŀ ����ڶ�������Ϊ-1�򷵻�һ�������ļ�ɾ��
	int DropCount = DragQueryFile(hDropInfo, -1, NULL, 0);
	// 2. ѭ����ȡ��ÿһ���ļ�
	for (int i = 0; i < DropCount; ++i)
	{
		WCHAR wcStr[MAX_PATH] = { 0 };
		// 3. ��ȡ��ק��i���ļ���
		DragQueryFile(hDropInfo, i, wcStr, MAX_PATH);
		if (find(PathString.begin(), PathString.end(), wcStr) == PathString.end())
		{
			if (this->Flag <= 2)
			{
				// 5. ��ӵ����浽·�����������б���
				PathString.push_back(wcStr);
				str = "�ļ�·����";
				str += wcStr;
				m_cleaFileInfoList.InsertItem(i, str);
			}
			else
				AfxMessageBox(L"ϵͳ���������������ɸ�������·��");
		}
	}
	// 6. �ͷ��ڴ�
	DragFinish(hDropInfo);
	CDialogEx::OnDropFiles(hDropInfo);
}

// ��ȡ��ɾ���ļ����б�
void Tab_CleanruDialogbox::GetDeleteFileList(vector<CString> PathStrings)
{
	DeletString.clear();
	FileCount = DestCount = 0;
	DestSize.QuadPart = DestSize.HighPart = 0;
	// 1. ��ȡɾ��·���������ļ�
	for (auto Path : PathStrings)
		FindFile(Path);
	// 2. ������ȡ�ļ���С
	CString DeleteSizeofs;
	// 3. �ļ�����   ��ɾ���ļ�����
	m_cleaFilenumber.Format(L"%-3d ��", FileCount);
	m_cleaFileSizeof.Format(L"%.2lf MB", (CountSize.QuadPart / 1024.0 / 1024.0));
	m_cleaDeleFileCounts.Format(L"%-3d ��", DestCount);
	// 4. ������ɾ���ļ��Ĵ�С
	DeleteSizeofs.Format(L"��ɾ���ļ���С�� %.2lf MB", DestSize.QuadPart / 1024.0 / 1024.0);
	UpdateData(FALSE);
	AfxMessageBox(DeleteSizeofs);
}

// ����·����ɾ����׺��
void Tab_CleanruDialogbox::FindFile(CString Path)
{
	int i = 0;
	WIN32_FIND_DATA FileData = { 0 };
	HANDLE hFile = FindFirstFile(Path + "\\*", &FileData);
	// 1. �ж�
	if (hFile != INVALID_HANDLE_VALUE)
	{
		// 2. �ݹ�ѭ��
		do
		{
			if (FileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
			{
				if (CString(".") != FileData.cFileName && CString("..") != FileData.cFileName)
					FindFile(Path + CString("\\") + FileData.cFileName);
			}
			// 3. �����ļ�������ļ���Ϣ
			else
			{
				// �ļ�����+1  �� �ļ���С
				++FileCount;
				CountSize.QuadPart += FileData.nFileSizeLow;
				// 4. �жϺ�׺��
				if ((2 >= this->Flag) && (UserExtendString.GetLength() > 0) )
				{
					// 4.1 VS��׺���� �� �Զ�������
					if (-1 != ExtendString.Find(PathFindExtension(FileData.cFileName)) && (1 == this->Flag) )
					{
						++DestCount;
						DestSize.QuadPart += FileData.nFileSizeLow;
						DeletString.push_back(Path + CString("\\") + FileData.cFileName);
						m_cleaDeleteInfoList.InsertItem(i, Path + CString("\\") + FileData.cFileName);
					}
					// 4.2 VS��׺���� �� �Զ�������
					if (-1 != UserExtendString.Find(PathFindExtension(FileData.cFileName)) && (2 == this->Flag) )
					{
						++DestCount;
						DestSize.QuadPart += FileData.nFileSizeLow;
						DeletString.push_back(Path + CString("\\") + FileData.cFileName);
						m_cleaDeleteInfoList.InsertItem(i, Path + CString("\\") + FileData.cFileName);
					}
				}
				// 5. �����ǹ̶�Ŀ¼��ϵͳ���� ��������� �����ֺ�׺
				else
				{
					++DestCount;
					DestSize.QuadPart += FileData.nFileSizeLow;
					DeletString.push_back(Path + CString("\\") + FileData.cFileName);
					m_cleaDeleteInfoList.InsertItem(i, Path + CString("\\") + FileData.cFileName);
				}
			}
			++i;
		} while (FindNextFile(hFile, &FileData));
	}
}

// ɾ���ļ���ť
void Tab_CleanruDialogbox::OnBnClickedOk()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CString str = "ȷ������·��Ϊ �� ";
	for (SIZE_T i = 0; i < PathString.size(); ++i)
	{
		str += ' ';
		str += PathString[i].GetString();
	}
	str += " �� �µ��ļ�????";
	if (IDOK == ::MessageBox(NULL, str, L"ɾ��ȷ��", MB_ICONQUESTION | MB_OKCANCEL))
	{
		// ��ʼɾ���ļ�
		DeleteCount = 0;
		for (auto File : DeletString)
		{
			if (DeleteFile(File))
				++DeleteCount;
		}
		CString Msg;
		Msg.Format(L"��ɾ���ļ� %d ��\n��ɾ���ļ� %d ��",
			DestCount, DeleteCount);
		MessageBox(Msg);
	}
	return;
	// CDialogEx::OnOK();
}

// ��ȡ��ǰ���ͼ�׼��ɾ������
void Tab_CleanruDialogbox::OnBnClickedButton1()
{
	// ���������Ϣ��
	m_cleaDeleteInfoList.DeleteAllItems();
	// 1. ��ȡ��ǰѡ�е��ı���Ϣ
	CString str;
	int nIndex = m_TypeSelect.GetCurSel();
	m_TypeSelect.GetLBText(nIndex, str);
	// 2. ��Ӧ��Ե��¼�
	if ("VS����" == str)
	{
		if (0 == PathString.size())
		{
			AfxMessageBox(L"������ק׼����ɾ���ļ���, �ٴλ�ȡ");
			return;
		}
		// 2.1 ������ק�ļ�·��
		GetDeleteFileList(PathString);
	}
	else if ("�Զ�������" == str)
	{
		UpdateData(TRUE);
		if (m_EditText.GetLength() > 0)
			PathString.push_back(str);
		else
		{
			AfxMessageBox(L"����\\��ק ɾ���ļ���Ŀ¼, �ٴλ�ȡ");
			return;
		}
		GetDeleteFileList(PathString);
	}
	else if ("���������" == str)
	{
		// �̶�·��
		this->strPath = "c:\\users\\administrator\\appdata\\roaming\\360se6\\User Data\\Default";
		PathString.push_back(strPath);
		GetDeleteFileList(PathString);
	}
	else if ("ϵͳ��������" == str)
	{
		// �̶�·��
		this->strPath = "C:\\Windows\\Temp";
		PathString.push_back(strPath);
		GetDeleteFileList(PathString);
	}
	else
		AfxMessageBox(L"ô�л�ȡ����ȷ��Ϣ���u�v��");
}

// ����VS���Զ����׺����
void Tab_CleanruDialogbox::OnBnClickedButton3()
{
	UpdateData(TRUE);
	// ���VS��׺����
	if (1 == Flag)
	{
		ExtendString = m_SuffixFileNameValues;
		return;
	}
	if (2 == Flag)
	{
		UserExtendString = m_SuffixFileNameValues;
		return;
	}
}

void Tab_CleanruDialogbox::OnBnClickedButton2()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}
