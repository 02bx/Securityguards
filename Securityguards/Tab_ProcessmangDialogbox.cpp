// Tab_ProcessmangDialogbox.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Tab_ProcessmangDialogbox.h"
#include "afxdialogex.h"
#include "ThreadDialogbox.h"
#include "HeapInfoDialogBox.h"
#include "ModuleInfoDialogBox.h"
#include "FileInfo.h"




TCHAR Tab_ProcessmangDialogbox::buff[MAX_PATH] = { 0 };
TCHAR Tab_ProcessmangDialogbox::buff1[MAX_PATH] = { 0 };
int Tab_ProcessmangDialogbox::count = 0;
CImageList* Tab_ProcessmangDialogbox::Icon = NULL;

// ���ڻ�ȡ�Ļص�����
BOOL CALLBACK Tab_ProcessmangDialogbox::EnumWinProc(HWND hwnd, LPARAM lParam)
{
	// ���������ÿؼ�����
	Tab_ProcessmangDialogbox* p = (Tab_ProcessmangDialogbox *)lParam;
	// ��ȡ��������
	::GetWindowText(hwnd, buff, 200);
	// ����Ϊ�� �Ҵ�С��Ϊ0 ����
	if ((::IsWindowVisible(hwnd) == TRUE) && (wcslen(buff) != 0))
	{
		// ��ȡ����id
		DWORD wPid;
		GetWindowThreadProcessId(hwnd, &wPid);
		// �򿪽��̻�ȡ���  ALL
		HANDLE handle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, wPid);
		// ��ȡ�ļ�·��
		TCHAR Path[MAX_PATH] = {};
		GetModuleFileNameEx(handle, NULL, Path, MAX_PATH);
		// ��ȡ��Ϣ
		SHFILEINFOW shfileinfo;
		SHGetFileInfo(Path, 0, &shfileinfo, sizeof(SHFILEINFOW), SHGFI_ICON);
		// ��ʼ����ϢList�б�
		INT index = Icon->Add(shfileinfo.hIcon);
		p->m_ListCtrApp.SetImageList(Icon, LVSIL_SMALL);
		p->m_ListCtrApp.InsertItem(count, buff, index);
		p->m_ListCtrApp.SetItemText(count, 1, L"��������");
		++count;
	}
	return 1;
}

IMPLEMENT_DYNAMIC(Tab_ProcessmangDialogbox, CDialogEx)

const TCHAR Tab_ProcessmangDialogbox::m_ListNameArr[g_MaxName][g_MaxName] = { L"ID", L"ӳ������", L"������ID", L"�������ȼ�", L"�߳���", L"·��" };

Tab_ProcessmangDialogbox::Tab_ProcessmangDialogbox(CWnd* pParent /*=NULL*/)
	: CDialogEx(Tab_ProcessmangDialogbox::IDD, pParent)
{

}

Tab_ProcessmangDialogbox::~Tab_ProcessmangDialogbox()
{
}

void Tab_ProcessmangDialogbox::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST2, m_ListCtr);
	DDX_Control(pDX, IDC_LIST1, m_ListCtrApp);
}


BEGIN_MESSAGE_MAP(Tab_ProcessmangDialogbox, CDialogEx)
	ON_NOTIFY(NM_RCLICK, IDC_LIST2, &Tab_ProcessmangDialogbox::OnRclickList2)
ON_COMMAND(ID_40014, &Tab_ProcessmangDialogbox::CloseProcess)
ON_COMMAND(ID__40018, &Tab_ProcessmangDialogbox::Filelocation)
ON_COMMAND(ID_40015, &Tab_ProcessmangDialogbox::GetThreadInfo)
ON_COMMAND(ID__40019, &Tab_ProcessmangDialogbox::GetHeapInfoss)
ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST1, &Tab_ProcessmangDialogbox::OnLvnItemchangedList1)
ON_BN_CLICKED(IDC_BUTTON1, &Tab_ProcessmangDialogbox::OnBnClickedButton1)
ON_COMMAND(ID__40020, &Tab_ProcessmangDialogbox::GetModule)
ON_NOTIFY(NM_RCLICK, IDC_LIST1, &Tab_ProcessmangDialogbox::OnRclickList1)
ON_COMMAND(ID_40031, &Tab_ProcessmangDialogbox::AppList)
ON_COMMAND(ID_ATTRES, &Tab_ProcessmangDialogbox::OnAttres)
END_MESSAGE_MAP()


// Tab_ProcessmangDialogbox ��Ϣ�������

BOOL Tab_ProcessmangDialogbox::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	// 1.��ȡ���
	CRect rc;
	this->GetClientRect(rc);
	int nWidth = rc.Width();
	// 2.��ȡ/���÷��
	DWORD dwOldStyle;
	dwOldStyle = m_ListCtr.GetExtendedStyle();
	m_ListCtr.SetExtendedStyle(dwOldStyle | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	// 3.���ó�ʼ������
	for (int i = 0; i < g_MaxName; i++)
	{
		m_ListCtr.InsertColumn(i, m_ListNameArr[i], LVCFMT_CENTER, nWidth / g_MaxName);
	}
	// 4.��ȡ������Ϣ
	this->GetProcessInfo();
	/*���ؽ��̲˵���Ϣ*/
	men.LoadMenuW(IDR_MENU2);
	/*==========================================================*/
	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	dwOldStyle = m_ListCtrApp.GetExtendedStyle();
	m_ListCtrApp.SetExtendedStyle(dwOldStyle | LVS_EX_FULLROWSELECT | LVS_EX_REGIONAL);
	m_ListCtrApp.GetClientRect(&rc);
	nWidth = rc.Width();
	m_ListCtrApp.InsertColumn(0, L"����", 0, nWidth / 2);
	m_ListCtrApp.InsertColumn(1, L"״̬", 0, nWidth / 2);
	// ��̬����ȫ�� Ȼ����thisָ��
	// ��λ�ȡӦ�ô���Сͼ�ꣿ
	// ��ʼ������ͼƬ��С
	Icon = new CImageList;
	Icon->Create(25, 25, ILC_COLOR32, 0, 4);
	// ���ûص�����
	EnumWindows(EnumWinProc, (LPARAM)this);
	return TRUE;
}

// ��ȡ����
BOOL Tab_ProcessmangDialogbox::GetProcessInfo()
{
	m_ListCtr.DeleteAllItems();
	// ��ʼ����Ч�ľ��ֵ
	HANDLE hprocess = INVALID_HANDLE_VALUE;
	PROCESSENTRY32W p_32 = { 0 };
	// 1.�������̿���
	hprocess = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (INVALID_HANDLE_VALUE != hprocess)
	{
		p_32.dwSize = sizeof(PROCESSENTRY32W);
		// ���㵱ǰѭ������
		int count = 0;
		// ��ʼ��������
		if (!Process32First(hprocess, &p_32))
		{
			AfxMessageBox(L"Process32First falure!");
			CloseHandle(hprocess);
			return FALSE;
		}
		do
		{
			/*
			if (0 >= GetProcessImageFileName(hprocess, buf, MAX_PATH))
				AfxMessageBox(L"GetProcessImageFileName() failure!");
				*/
			GetProcessImageFileName(hprocess, buf, MAX_PATH);
			this->SetProcessInfo(&p_32, count, buf);
		} while (Process32Next(hprocess, &p_32));
	}
	else
	{
		AfxMessageBox(L"CreateToolhelp32Snapshot failure!");
		return FALSE;
	}
	return TRUE;
}

// ��ʾ����
void Tab_ProcessmangDialogbox::SetProcessInfo(const LPPROCESSENTRY32W P_32, const int count, const TCHAR* buf)
{
	TCHAR bufs[MAX_PATH] = {};
	// ����ID
	_stprintf_s(bufs, MAX_PATH, L"%d", P_32->th32ProcessID);
	m_ListCtr.InsertItem(count, bufs);
	// ������
	m_ListCtr.SetItemText(count, 1, P_32->szExeFile);
	// ������ID
	_stprintf_s(bufs, MAX_PATH, L"%d", P_32->th32ParentProcessID);
	m_ListCtr.SetItemText(count, 2, bufs);
	// �������ȼ�
	if (P_32->pcPriClassBase == 31)
		m_ListCtr.SetItemText(count, 3, L"ʵʱ(real-time)");
	else if (P_32->pcPriClassBase >= 15)
		m_ListCtr.SetItemText(count, 3, L"��(High)");
	else if (P_32->pcPriClassBase >= 11)
		m_ListCtr.SetItemText(count, 3, L"���ڱ�׼(above normal)");
	else if (P_32->pcPriClassBase >= 8)
		m_ListCtr.SetItemText(count, 3, L"��׼(normal)");
	else if (P_32->pcPriClassBase >= 5)
		m_ListCtr.SetItemText(count, 3, L"���ڱ�׼(below Normal)");
	else if (P_32->pcPriClassBase >= 0)
		m_ListCtr.SetItemText(count, 3, L"���(idle)");
	// �߳���
	_stprintf_s(bufs, MAX_PATH, L"%d", P_32->cntThreads);
	m_ListCtr.SetItemText(count, 4, bufs);
	// ·��
	m_ListCtr.SetItemText(count, 5, buf);
}

// �һ������˵�
void Tab_ProcessmangDialogbox::OnRclickList2(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// �˵���ҪPopģʽ��ע������˵�����������������GetSubMenu�Ƿ��ز��˲˵����������Ϊ0;
	// 1.��ȡh_Menu��������ص��Ĳ˵������
	p = men.GetSubMenu(0);
	// 2.��ȡ��ǰ�һ�λ��
	GetCursorPos(&point);
	// 3.��ʾһ�������˵�
	p->TrackPopupMenu(TPM_LEFTBUTTON, point.x, point.y, this);
}

// ��������
void Tab_ProcessmangDialogbox::CloseProcess()
{
	if (MessageBox(L"ȷ����������?", L"��ʾ", MB_OKCANCEL | MB_ICONQUESTION))
	{
		// 1.��ȡ��ǰѡ������
		int index = m_ListCtr.GetSelectionMark();
		// 2.��ȡ����ID
		CString str = m_ListCtr.GetItemText(index, 0);
		// 3.��ȡ���̾��
		int process_id = _ttol(str);
		HANDLE hprocess = OpenProcess(PROCESS_TERMINATE, FALSE, process_id);
		TerminateProcess(hprocess, 0);
		CloseHandle(hprocess);
	}
	else;
}

// ���ļ�λ��
void Tab_ProcessmangDialogbox::Filelocation()
{
	// 1.��ȡ����ID
	int index = m_ListCtr.GetSelectionMark();
	CString str = m_ListCtr.GetItemText(index, 0);
	// 2.��ȡ���̾��
}

// ��ȡ�߳�
void Tab_ProcessmangDialogbox::GetThreadInfo()
{
	// ���ô���
	ThreadDialogbox threadobj;
	int index = m_ListCtr.GetSelectionMark();
	CString str = m_ListCtr.GetItemText(index, 0);
	threadobj.m_ownperProcess = _ttol(str);
	threadobj.DoModal();
}

// ��ȡ��
void Tab_ProcessmangDialogbox::GetHeapInfoss()
{
	// TODO:  �ڴ���������������
	HeapInfoDialogBox heapObj;
	int index = m_ListCtr.GetSelectionMark();
	CString str = m_ListCtr.GetItemText(index, 0);
	heapObj.m_ownerPid = _ttol(str);
	heapObj.DoModal();
}

// ��ȡģ��
void Tab_ProcessmangDialogbox::GetModule()
{
	ModuleInfoDialogBox moduleObj;
	int index = m_ListCtr.GetSelectionMark();
	CString str = m_ListCtr.GetItemText(index, 0);
	moduleObj.m_ownerPid = _ttol(str);
	moduleObj.DoModal();
}

// lISTAPPCtrol
void Tab_ProcessmangDialogbox::OnLvnItemchangedList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;
}

// ˢ��ȫ����ť
void Tab_ProcessmangDialogbox::OnBnClickedButton1()
{
	// -----------****���´���APP***------------------
	count = 0;
	m_ListCtrApp.DeleteAllItems();
	EnumWindows(EnumWinProc, (LPARAM)this);

	// -----------****����APP***------------------
	GetProcessInfo();
}

// APP�һ������˵�
void Tab_ProcessmangDialogbox::OnRclickList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	CMenu PopMen;
	PopMen.LoadMenuW(IDR_MENU4);
	POINT point;
	GetCursorPos(&point);
	CMenu *p = PopMen.GetSubMenu(0);
	p->TrackPopupMenu(TPM_LEFTBUTTON, point.x, point.y, this);
	*pResult = 0;
}

// ��ӦApp���������ת
void Tab_ProcessmangDialogbox::AppList()
{
	CString str;
	DWORD nPid = 0;
	// 1. ��ȡ��ǰ������
	int index = m_ListCtrApp.GetSelectionMark();
	str = m_ListCtrApp.GetItemText(index, 0);
	int k = m_ListCtrApp.GetSelectionMark();
	m_ListCtr.SetItemState(k, 0, LVIS_SELECTED | LVIS_FOCUSED);

	// 2.��ȡ��ǰ���̵ľ��
	CWnd *pwnd = FindWindow(NULL, str);
	HWND hApp = pwnd->GetSafeHwnd();
	GetWindowThreadProcessId(hApp, &nPid);

	// 3.ѭ������mList��PID  �ҵ�����Ϲ�����õ�����
	int nCount = m_ListCtr.GetItemCount();
	for (int i = 0; i < nCount; ++i)
	{
		str = m_ListCtr.GetItemText(i, 0);
		DWORD ProccessPid = wcstol(str, NULL, 10);
		if (ProccessPid == nPid)
		{
			LVITEMINDEX aaaa = { i, 0 };
			// ��ȡ��ѡ����һ��
			m_ListCtrApp.SetItemState(index, 0, LVIS_SELECTED | LVIS_FOCUSED);
			// ���ù�굽����
			m_ListCtr.SetFocus();
			m_ListCtr.SetItemState(i, LVIS_SELECTED | LVIS_FOCUSED, LVIS_SELECTED | LVIS_FOCUSED);
			return;
		}
	}
}

// ��Ӧ�ļ�����
void Tab_ProcessmangDialogbox::OnAttres()
{
	DWORD nPid = 0;
	CString str;
	// 1. ��ȡ��ǰ����
	int index = m_ListCtrApp.GetSelectionMark();
	str = m_ListCtrApp.GetItemText(index, 0);
	// 2.��ȡ��ǰ���̵ľ��
	CWnd *pwnd = FindWindow(NULL, str);
	HWND hApp = pwnd->GetSafeHwnd();
	GetWindowThreadProcessId(hApp, &nPid);
	// 3. �򿪽��̻�ȡ���  ALL
	HANDLE handle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, nPid);
	// 4. ��ȡ�ļ�·��
	TCHAR Path[MAX_PATH] = {};
	GetModuleFileNameEx(handle, NULL, Path, MAX_PATH);
	// 5. ��ȡ�ļ�·��
	FileInfo file;
	str = Path;
	file.cFilePath = str;
	file.DoModal();
}
