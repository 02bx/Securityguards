// ThreadDialogbox.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ThreadDialogbox.h"
#include "afxdialogex.h"



// ThreadDialogbox �Ի���

IMPLEMENT_DYNAMIC(ThreadDialogbox, CDialogEx)

ThreadDialogbox::ThreadDialogbox(CWnd* pParent /*=NULL*/)
	: CDialogEx(ThreadDialogbox::IDD, pParent)
{

}

ThreadDialogbox::~ThreadDialogbox()
{
}

void ThreadDialogbox::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_Listctr);
}


BEGIN_MESSAGE_MAP(ThreadDialogbox, CDialogEx)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST1, &ThreadDialogbox::OnLvnItemchangedList1)
	ON_NOTIFY(NM_RCLICK, IDC_LIST1, &ThreadDialogbox::OnRclickList1)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST1, &ThreadDialogbox::OnLvnItemchangedList1)
	ON_NOTIFY(NM_RCLICK, IDC_LIST1, &ThreadDialogbox::OnRclickList1)
	ON_COMMAND(ID_40028, &ThreadDialogbox::HungThread)
	ON_COMMAND(ID_40029, &ThreadDialogbox::RestoretheThread)
	ON_COMMAND(ID_40030, &ThreadDialogbox::CloseThread)
//	ON_COMMAND(ID__40019, &ThreadDialogbox::GetHeapInfoss)
END_MESSAGE_MAP()


// ThreadDialogbox ��Ϣ�������


BOOL ThreadDialogbox::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	// 1.���÷��
	CRect rc;
	this->GetClientRect(rc);
	int nWidth = rc.Width();
	DWORD dwold = m_Listctr.GetExtendedStyle();
	m_Listctr.SetExtendedStyle(dwold | LVS_EX_FULLROWSELECT |LVS_EX_GRIDLINES);
	// ��ʼ��list
	m_Listctr.InsertColumn(0, L"������ID", LVCFMT_CENTER, nWidth / 3);
	m_Listctr.InsertColumn(1, L"����ID", LVCFMT_CENTER, nWidth / 3);
	m_Listctr.InsertColumn(2, L"������ȼ�", LVCFMT_CENTER, nWidth / 3);
	// ��ȡ����ѡ�еĽ���ID�������
	
	GetThreadInfo();
	return TRUE;
}

BOOL ThreadDialogbox::GetThreadInfo()
{
	HANDLE lpthread = INVALID_HANDLE_VALUE;
	THREADENTRY32 t_32 = { 0 };
	lpthread = lpthread = CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, 0);
	if (INVALID_HANDLE_VALUE == lpthread)
	{
		AfxMessageBox(L"CreateToolhelp32Snapshot() failure!");
		return FALSE;
	}
	if (ERROR_NO_MORE_FILES == Thread32First(lpthread, &t_32))
	{
		CloseHandle(lpthread);
		AfxMessageBox(L"Thread32First() failure!");
		return FALSE;
	}
	int count = 0;
	t_32.dwSize = sizeof(THREADENTRY32);
	do{
		if (t_32.th32OwnerProcessID == this->m_ownperProcess)
		{
			this->ShowThreadList(t_32, count);
			++count;
		}
	} while (Thread32Next(lpthread, &t_32));
	return TRUE;
}

// ��ʾ�߳�
void ThreadDialogbox::ShowThreadList(const THREADENTRY32 t_32,const int nSel)
{
	// ������ID
	_stprintf_s(buf, MAX_PATH, L"%u", t_32.th32OwnerProcessID);
	m_Listctr.InsertItem(nSel, buf);
	// ����ID
	_stprintf_s(buf, MAX_PATH, L"%u", t_32.th32OwnerProcessID);
	m_Listctr.SetItemText(nSel, 1, buf);
	// ���ȼ�
	_stprintf_s(buf, MAX_PATH, L"%d", t_32.tpBasePri);
	if (t_32.tpBasePri == 31)
		m_Listctr.SetItemText(nSel, 2, L"ʵʱ(real-time)");
	else if (t_32.tpBasePri >= 15)	
		m_Listctr.SetItemText(nSel, 2, L"��(High)");
	else if (t_32.tpBasePri >= 11)	
		m_Listctr.SetItemText(nSel, 2, L"���ڱ�׼(above normal)");
	else if (t_32.tpBasePri >= 8)	
		m_Listctr.SetItemText(nSel, 2, L"��׼(normal)");
	else if (t_32.tpBasePri >= 5)	
		m_Listctr.SetItemText(nSel, 2, L"���ڱ�׼(below Normal)");
	else if (t_32.tpBasePri >= 0)	
		m_Listctr.SetItemText(nSel, 2, L"���(idle)");
}


// List
void ThreadDialogbox::OnLvnItemchangedList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	
	*pResult = 0;
}

// ��Ӧ�һ��˵�
void ThreadDialogbox::OnRclickList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	CMenu men;
	men.LoadMenuW(IDR_MENU3);
	POINT point;
	GetCursorPos(&point);
	CMenu *p = men.GetSubMenu(0);
	p->TrackPopupMenu(TPM_LEFTBUTTON, point.x, point.y, this);
	*pResult = 0;
}

// �̹߳���
void ThreadDialogbox::HungThread()
{
	// TODO:  �ڴ���������������
	value = MessageBox(L"Suspends the current thread?", L"Warning!", MB_ICONQUESTION | MB_OKCANCEL);
	if (IDOK == value)
	{
		ULONG hwnd = GetThreadPid();
		SuspendThread(HANDLE(hwnd));
	}
}

// ��ȡThread Pid
unsigned long ThreadDialogbox::GetThreadPid()
{
	unsigned long index = m_Listctr.GetSelectionMark();
	CString strPid = m_Listctr.GetItemText(index, 0);
	return _ttol(strPid);
}

// �ָ��߳�
void ThreadDialogbox::RestoretheThread()
{
	// TODO:  �ڴ���������������
	value = MessageBox(L"Restore the current thread running?", L"Warning!", MB_ICONQUESTION | MB_OKCANCEL);
	if (IDOK == value)
	{
		ULONG hwnd = GetThreadPid();
		ResumeThread(HANDLE(hwnd));
	}
}

// �߳̽���
void ThreadDialogbox::CloseThread()
{
	// TODO:  �ڴ���������������
	value = MessageBox(L"End of the current thread?", L"Warning!", MB_ICONQUESTION | MB_OKCANCEL);
	if (IDOK == value)
	{
		ULONG hwnd = GetThreadPid();
		ExitProcess(0);
	}
}