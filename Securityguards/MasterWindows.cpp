// MasterWindows.cpp : ʵ���ļ�
//
#pragma once
#include "stdafx.h"
#include "MasterWindows.h"
#include "afxdialogex.h"
#include "Tab_CleanruDialogbox.h"
#include "Tab_MemoryDialogbox.h"
#include "Tab_NetworktoolDialogbox.h"
#include "Tab_PEfileanalDialogbox.h"
#include "Tab_ProcessmangDialogbox.h"
#include "Tab_SoftwarmangDialogbox.h"
#include "Tab_LDCS.h"
#include "PowrProf.h"

// MasterWindows �Ի���

IMPLEMENT_DYNAMIC(MasterWindows, CDialogEx)

// ��ʼ��TabName
const TCHAR MasterWindows::tab_Name[7][12] = { _T("�ڴ��Ż�"), _T("���̹���"), _T("PE�ļ�����"), _T("�����������"), _T("��������"), _T("���繥��"), _T("��Ȳ�ɱ") };

MasterWindows::MasterWindows(CWnd* pParent /*=NULL*/)
	: CDialogEx(MasterWindows::IDD, pParent)
{

}

MasterWindows::~MasterWindows()
{

}

void MasterWindows::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TAB1, m_Tab_control);
	DDX_Control(pDX, IDC_Wolf, m_PictrueWolf);
}


BEGIN_MESSAGE_MAP(MasterWindows, CDialogEx)

	ON_COMMAND(ID_40021, &MasterWindows::On40021)
	ON_COMMAND(ID_40022, &MasterWindows::Reboot)
	ON_COMMAND(ID_40024, &MasterWindows::Lockscreen)
	ON_COMMAND(ID_40032, &MasterWindows::Cancellation)
	ON_COMMAND(ID_40035, &MasterWindows::BOOSKEY)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()

// MasterWindows ��Ϣ�������
BOOL MasterWindows::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	m_bush.CreateSolidBrush(RGB(255, 255, 255));
	// 1.��ʼ��Tab����
	this->SetdwCount(7);
	m_Tab_control.InitData(m_dwCount, tab_Name[0], tab_Name[1], tab_Name[2], tab_Name[3], tab_Name[4], tab_Name[5], tab_Name[6]);
	// 2.��Ӵ�����Դ
	m_Tab_control.AddData(m_dwCount,
		IDD_Memory_optimization, new Tab_MemoryDialogbox,
		IDD_Process_management, new Tab_ProcessmangDialogbox,
		IDD_PE_Fille_analysis, new Tab_PEfileanalDialogbox,
		IDD_Softwar_management, new Tab_SoftwarmangDialogbox,
		IDD_Clean_rubbish, new Tab_CleanruDialogbox,
		IDD_Network_tool, new Tab_NetworktoolDialogbox,
		IDD_TABLDCS, new Tab_LDCS
		);
	// 3.���ô���LogСͼ��
	SetIcon(LoadIcon(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDI_WinSmall)), FALSE);
	// 4.���������ڽ���ͼƬ
	CBitmap* p = new CBitmap();
	p->LoadBitmapW(IDB_BITMAP1);
	m_PictrueWolf.SetBitmap((HBITMAP)p->m_hObject);
	return TRUE;
}

// ��ȡϵͳȨ��
void MasterWindows::GetSystempermissions()
{
	HANDLE hToken = NULL;
	// ��ȡα��������̣߳�
	HANDLE hProcess = GetCurrentProcess();
	OpenProcessToken(hProcess, TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken);
	TOKEN_PRIVILEGES tp = { 0 };
	LookupPrivilegeValue(0, SE_SHUTDOWN_NAME, &tp.Privileges[0].Luid);
	// ��Ȩ����
	tp.PrivilegeCount = 1;
	tp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
	AdjustTokenPrivileges(hToken, FALSE, &tp, sizeof(tp), NULL, NULL);
}

/*-----------------��ϵͳ������--------------------------*/

// 1. �ػ�
void MasterWindows::On40021()
{
	if (IDOK == MessageBox(L"Whether to turn it off", L"Warning", MB_ICONQUESTION | MB_OKCANCEL))
	{
		GetSystempermissions();
		ExitWindowsEx(EWX_POWEROFF | EWX_FORCE, 0);
	}
}

// 2. ����
void MasterWindows::Reboot()
{
	if (IDOK == MessageBox(L"Whether to restart", L"Warning", MB_ICONQUESTION | MB_OKCANCEL))
	{
		GetSystempermissions();
		ExitWindowsEx(EWX_REBOOT | EWX_FORCE, 0);
	}
}

// 3. ����
//void MasterWindows::Dormancy()
//{
//	if (IDOK == MessageBox(L"Whether to restart", L"Warning", MB_ICONQUESTION | MB_OKCANCEL))
//	{
//		GetSystempermissions();
//		SetSuspendState(TRUE, FALSE, FALSE);
//	}
//}

// 4. ����
void MasterWindows::Lockscreen()
{
	if (IDOK == MessageBox(L"Whether to restart", L"Warning", MB_ICONQUESTION | MB_OKCANCEL))
	{
		GetSystempermissions();
		LockWorkStation();
	}
}

// 5. ע��
void MasterWindows::Cancellation()
{
	if (IDOK == MessageBox(L"Whether to restart", L"Warning", MB_ICONQUESTION | MB_OKCANCEL))
	{
		GetSystempermissions();
		ExitWindowsEx(EWX_LOGOFF | EWX_FORCE, 0);
	}
}

// 6. �ϰ��
void MasterWindows::BOOSKEY()
{
	// ע��һ����ݼ� Ctrl + shift + H(��ĸ��д)
	::RegisterHotKey(this->m_hWnd, 0x1234, MOD_CONTROL | MOD_SHIFT, 'H');
}

//  ��Ӧ��ݼ���Ϣ���ϰ����
BOOL MasterWindows::PreTranslateMessage(MSG* pMsg)
{
	// TODO:  �ڴ����ר�ô����/����û���

	if ((pMsg->message == WM_HOTKEY) && (pMsg->wParam == 0x1234))
	{
		if (::IsWindowVisible(m_hWnd) == TRUE)
			ShowWindow(SW_HIDE);
		else
			ShowWindow(SW_SHOW);
	}
	return CDialogEx::PreTranslateMessage(pMsg);
}

HBRUSH MasterWindows::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  �ڴ˸��� DC ���κ�����
	if (nCtlColor == CTLCOLOR_DLG)
	{
		return  m_bush;
	}

	// TODO:  ���Ĭ�ϵĲ������軭�ʣ��򷵻���һ������
	return hbr;
}
