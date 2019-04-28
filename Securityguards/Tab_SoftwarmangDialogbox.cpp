// Tab_SoftwarmangDialogbox.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Tab_SoftwarmangDialogbox.h"
#include "afxdialogex.h"


// Tab_SoftwarmangDialogbox �Ի���

IMPLEMENT_DYNAMIC(Tab_SoftwarmangDialogbox, CDialogEx)

Tab_SoftwarmangDialogbox::Tab_SoftwarmangDialogbox(CWnd* pParent /*=NULL*/)
	: CDialogEx(Tab_SoftwarmangDialogbox::IDD, pParent)
{

}

Tab_SoftwarmangDialogbox::~Tab_SoftwarmangDialogbox()
{
}

void Tab_SoftwarmangDialogbox::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_ServicesoList);
	DDX_Control(pDX, IDC_LIST2, m_ServerInfo);
}

BEGIN_MESSAGE_MAP(Tab_SoftwarmangDialogbox, CDialogEx)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST1, &Tab_SoftwarmangDialogbox::OnLvnItemchangedList1)
	ON_NOTIFY(NM_CLICK, IDC_LIST1, &Tab_SoftwarmangDialogbox::OnClickList1)
	ON_NOTIFY(NM_RCLICK, IDC_LIST1, &Tab_SoftwarmangDialogbox::OnRclickList1)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST2, &Tab_SoftwarmangDialogbox::OnLvnItemchangedList2)
	ON_NOTIFY(NM_RCLICK, IDC_LIST2, &Tab_SoftwarmangDialogbox::OnRclickList2)
	ON_COMMAND(ID_40036, &Tab_SoftwarmangDialogbox::StartService)
	ON_COMMAND(ID_40037, &Tab_SoftwarmangDialogbox::StopService)
	ON_COMMAND(ID_40038, &Tab_SoftwarmangDialogbox::SofwUninstall)
	ON_BN_CLICKED(IDC_BUTTON1, &Tab_SoftwarmangDialogbox::OnBnClickedButton1)
	ON_WM_HOTKEY()
END_MESSAGE_MAP()

// Tab_SoftwarmangDialogbox ��Ϣ�������

BOOL Tab_SoftwarmangDialogbox::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	CRect rc;
	m_ServicesoList.GetClientRect(rc);
	int nWidth = rc.Width();
	DWORD dwOldStyle;
	dwOldStyle = m_ServicesoList.GetExtendedStyle();
	m_ServicesoList.SetExtendedStyle(dwOldStyle | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_ServicesoList.InsertColumn(0, L"ȫ�����", LVCFMT_CENTER, nWidth);
	m_ServicesoList.InsertItem(0, L"ȫ�����");
	m_ServicesoList.InsertItem(1, L"�����װ");
	m_ServicesoList.InsertItem(2, L"���������");
	m_ServicesoList.InsertItem(3, L"ϵͳ����");
	/*====================================================================================*/
	// ��ʼ��������
	ListStyleFuns();
	return TRUE;
}

// ����List1
void Tab_SoftwarmangDialogbox::OnLvnItemchangedList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;
}

// ��Ӧ���Listѡ����Ϣ
void Tab_SoftwarmangDialogbox::OnClickList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	CString str;
	// 1. ��ȡѡ���ı�С
	int index = m_ServicesoList.GetSelectionMark();
	str = m_ServicesoList.GetItemText(index, 0);
	// 1.1 ȫ�����
	if ("ȫ�����" == str)
	{
		m_ServerInfo.DeleteAllItems();
		this->pGetofShowAllSofwInfo();
		return;
	}
	//// 1.2 �����װ
	//else if ("�����װ" == str)
	//{
	//	this->pGetofShowZJSofwInfo();
	//	return;
	//}
	//// 1.3 ���������
	//else if ("���������" == str)
	//{
	//	this->pGetofShowBCYSofwInfo();
	//	return;
	//}
	// 1.4 ϵͳ����
	else if ("ϵͳ����" == str)
	{
		m_ServerInfo.DeleteAllItems();
		this->pGetofShowSystemService();
		return;
	}
	else
		AfxMessageBox(L"����ô��ѡ�У�");
	*pResult = 0;
}

// ��ȡ��ʾȫ�������Ϣ
BOOL Tab_SoftwarmangDialogbox::GetofShowAllSofwInfo()
{
	ListStyleFuns();
	SOFTINFO SoftInfo = { 0 };
	FILETIME ftLastWriteTimeA;					// last write time 
	// 1. ��һ���Ѵ��ڵ�ע����
	LONG LReturn = RegOpenKeyEx(RootKey, lpSubKey, 0, KEY_ENUMERATE_SUB_KEYS | KEY_WOW64_32KEY | KEY_QUERY_VALUE, &hkResult);
	// 2. �����Сע���
	// TCHAR    achKey[MAX_PATH] = {};			// buffer for subkey name
	DWORD    cbName = 0;						// size of name string 
	TCHAR    achClass[MAX_PATH] = TEXT("");		// buffer for class name 
	DWORD    cchClassName = MAX_PATH;			// size of class string 
	DWORD    cSubKeys = 0;						// number of subkeys 
	DWORD    cbMaxSubKey;						// longest subkey size 
	DWORD    cchMaxClass;						// longest class string 
	DWORD    cValues;							// number of values for key 
	DWORD    cchMaxValue;						// longest value name 
	DWORD    cbMaxValueData;					// longest value data 
	DWORD    cbSecurityDescriptor;				// size of security descriptor 
	FILETIME ftLastWriteTime;					// last write time 
	DWORD	retCode;
	// TCHAR  achValue[MAX_PATH] = {};
	DWORD cchValue = MAX_PATH;
	// Get the class name and the value count. 
	retCode = RegQueryInfoKey(
		hkResult,                // key handle 
		achClass,                // buffer for class name 
		&cchClassName,           // size of class string 
		NULL,                    // reserved 
		&cSubKeys,               // number of subkeys 
		&cbMaxSubKey,            // longest subkey size 
		&cchMaxClass,            // longest class string 
		&cValues,                // number of values for this key 
		&cchMaxValue,            // longest value name 
		&cbMaxValueData,         // longest value data 
		&cbSecurityDescriptor,   // security descriptor 
		&ftLastWriteTime);       // last write time 
	// 3. ѭ������UninstallĿ¼�µ��ӽ�
	int nCount = 1;
	DWORD dwIndex = 0;
	DWORD dwKeyLen = 255;
	DWORD dwType = 0;
	WCHAR szNewKeyName[MAX_PATH] = {};		// ע�������
	WCHAR strMidReg[MAX_PATH] = {};
	DWORD dwNamLen = 255;					// ��ȡ��ֵ
	HKEY hkValueKey = 0;
	LONG lRrturn = ERROR_SUCCESS;
	for (SIZE_T i = 0; i < cSubKeys; i++)
	{
		dwKeyLen = MAX_PATH;
		lRrturn = RegEnumKeyEx(hkResult, dwIndex, szNewKeyName, &dwKeyLen, 0, NULL, NULL, &ftLastWriteTimeA);
		// 2.1 ͨ���õ��ӽ�������������ϳ��µ��ӽ�·��
		swprintf_s(strMidReg, L"%s%s%s", lpSubKey, L"\\", szNewKeyName);
		// 2.2 ���µ��ӽ�, ��ȡ����
		RegOpenKeyEx(RootKey, strMidReg, 0, KEY_QUERY_VALUE, &hkValueKey);
		// ����
		dwNamLen = 255;
		RegQueryValueEx(hkValueKey, L"DisplayName", 0, &dwType, (LPBYTE)SoftInfo.szSoftName, &dwNamLen);
		m_ServerInfo.InsertItem(nCount, SoftInfo.szSoftName);
		// �汾��
		dwNamLen = 255;
		RegQueryValueEx(hkValueKey, L"VersionNumber", 0, &dwType, (LPBYTE)SoftInfo.szSoftVer, &dwNamLen);
		m_ServerInfo.SetItemText(nCount, 3, SoftInfo.szSoftVer);
		// ��װʱ��
		dwNamLen = 255;
		RegQueryValueEx(hkValueKey, L"Time", 0, &dwType, (LPBYTE)SoftInfo.szSoftDate, &dwNamLen);
		m_ServerInfo.SetItemText(nCount, 2, SoftInfo.szSoftDate);
		// ��С
		dwNamLen = 255;
		RegQueryValueEx(hkValueKey, L"Sizeof", 0, &dwType, (LPBYTE)SoftInfo.szSoftSize, &dwNamLen);
		m_ServerInfo.SetItemText(nCount, 4, SoftInfo.szSoftSize);
		// ������
		dwNamLen = 255;
		RegQueryValueEx(hkValueKey, L"Sizeof", 0, &dwType, (LPBYTE)SoftInfo.strSoftVenRel, &dwNamLen); 
		// ж��·��
		dwNamLen = 255;
		RegQueryValueEx(hkValueKey, L"UninstallString", 0, &dwType, (LPBYTE)SoftInfo.strSoftUniPath, &dwNamLen);
		m_ServerInfo.SetItemText(nCount, 5, SoftInfo.strSoftUniPath);
		dwNamLen = 255;
		++dwIndex;
	}
	return TRUE;
}

// ��ȡ��ʾϵͳ������Ϣ
BOOL Tab_SoftwarmangDialogbox::GetofShowSystemService()
{
	ListStyleFun();
	// 1. ��Զ�̼�������������ƹ�����
	SC_HANDLE hSCMs = OpenSCManagerW(NULL, NULL, SC_MANAGER_ALL_ACCESS);
	// 2. ��һ�ε��ã���Ҫ��ȡ�ڴ��С
	DWORD dwServiceNum = 0;
	DWORD dwSize = 0;
	EnumServicesStatusEx(hSCMs, SC_ENUM_PROCESS_INFO, SERVICE_WIN32, SERVICE_STATE_ALL, NULL, 0, &dwSize, &dwServiceNum, NULL, NULL);
	// 3. ������Ҫ���ڴ棬 �ڶ��ε���
	LPENUM_SERVICE_STATUS_PROCESS pEnumService = (LPENUM_SERVICE_STATUS_PROCESS)new char[dwSize];
	// 4. �ڶ���ö��
	BOOL bStatus = FALSE;
	bStatus = EnumServicesStatusEx(hSCMs, SC_ENUM_PROCESS_INFO, SERVICE_WIN32, SERVICE_STATE_ALL, (PBYTE)pEnumService, dwSize, &dwSize, &dwServiceNum, NULL, NULL);
	// 5. ������Ϣ
	for (DWORD i = 0; i < dwServiceNum; ++i)
	{
		// 5.1 ����
		m_ServerInfo.InsertItem(i, pEnumService[i].lpServiceName);
		// 5.2 ״̬
		switch (pEnumService[i].ServiceStatusProcess.dwCurrentState)
		{
			// ֹͣ-->Ϊ��
		case SERVICE_STOPPED:
			m_ServerInfo.SetItemText(i, 2, L" ");
			break;
			// ������
		case SERVICE_RUNNING:
			m_ServerInfo.SetItemText(i, 2, L"������");
			break;
			// ��ͣ
		case SERVICE_PAUSED:
			m_ServerInfo.SetItemText(i, 2, L"��ͣ");
			break;
		}
		// ��ȡ�������ϸ��Ϣ
		SC_HANDLE hServices = OpenService(hSCMs, pEnumService[i].lpServiceName, SERVICE_QUERY_CONFIG);
		// ��һ�ε��û�������С
		QueryServiceConfig(hServices, NULL, 0, &dwSize);
		// �����ڴ�
		LPQUERY_SERVICE_CONFIG pServiceConfig = (LPQUERY_SERVICE_CONFIG)new char[dwSize];
		// �ڶ��ε��ã� ��ȡ��Ϣ
		QueryServiceConfig(hServices, pServiceConfig, dwSize, &dwSize);
		// 5.3 �豸���ͣ�������Ϣ��
		DWORD sType = pServiceConfig->dwServiceType;
		switch (sType)
		{
			// �ļ�ϵͳ��������
		case SERVICE_FILE_SYSTEM_DRIVER:
			m_ServerInfo.SetItemText(i, 1, L"�ļ�ϵͳ��������");
			break;
			// �����������
		case SERVICE_KERNEL_DRIVER:
			m_ServerInfo.SetItemText(i, 1, L"�����������");
			break;
			// �����̷���
		case SERVICE_WIN32_OWN_PROCESS:
			m_ServerInfo.SetItemText(i, 1, L"�����̷���");
			break;
			// 0x0000020����
		case SERVICE_WIN32_SHARE_PROCESS:
			m_ServerInfo.SetItemText(i, 1, L"0x0000020 ����");
			break;
		}
		// 5.4 ��������
		DWORD startType = pServiceConfig->dwStartType;
		switch (startType)
		{
			// �Զ�
		case SERVICE_AUTO_START:
			m_ServerInfo.SetItemText(i, 3, L"�Զ�");
			break;
			// �Զ�(�ӳ�����)
		case SERVICE_BOOT_START:
			m_ServerInfo.SetItemText(i, 3, L"�Զ�(�ӳ�����)");
			break;
			// 
		case SERVICE_DEMAND_START:
			m_ServerInfo.SetItemText(i, 3, L"�ֶ�");
			break;
			// ����
		case SERVICE_DISABLED:
			m_ServerInfo.SetItemText(i, 3, L"����");
			break;
		default:
			break;
		}
		// 5.5 ��ȡ·����Ϣ
		m_ServerInfo.SetItemText(i, 5, pServiceConfig->lpBinaryPathName);
		// 5.6 ��¼Ϊ
		m_ServerInfo.SetItemText(i, 4, pServiceConfig->lpServiceStartName);
	}
	return FALSE;
}

// ϵͳ���
void Tab_SoftwarmangDialogbox::ListStyleFun()
{
	int count = m_ServerInfo.GetHeaderCtrl()->GetItemCount();
	for (int i = 0; i < count; ++i)
	{
		m_ServerInfo.DeleteColumn(0);
	}
	CRect rc;
	CString str;
	// DWORD dwOldStyle;
	// m_ServerInfo.SetExtendedStyle(dwOldStyle | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_ServerInfo.GetClientRect(rc);
	int nWidth = rc.Width();
	m_ServerInfo.InsertColumn(0, L"����", 0, nWidth / 6);
	m_ServerInfo.InsertColumn(1, L"����", 0, nWidth / 6);
	m_ServerInfo.InsertColumn(2, L"״̬", 0, nWidth / 6);
	m_ServerInfo.InsertColumn(3, L"��������", 0, nWidth / 6);
	m_ServerInfo.InsertColumn(4, L"��¼Ϊ", 0, nWidth / 6);
	m_ServerInfo.InsertColumn(5, L"·��", 0, nWidth / 6);
}

// �����
void Tab_SoftwarmangDialogbox::ListStyleFuns()
{
	int count = m_ServerInfo.GetHeaderCtrl()->GetItemCount();
	for (int i = 0; i < count; ++i)
	{
		m_ServerInfo.DeleteColumn(0);
	}
	CRect rc;
	m_ServerInfo.GetClientRect(rc);
	int nWidth = rc.Width();
	m_ServerInfo.InsertColumn(0, L"�������", LVCFMT_CENTER, nWidth / 6);
	m_ServerInfo.InsertColumn(1, L"������", LVCFMT_CENTER, nWidth / 6);
	m_ServerInfo.InsertColumn(2, L"��װʱ��", LVCFMT_CENTER, nWidth / 6);
	m_ServerInfo.InsertColumn(3, L"��С", LVCFMT_CENTER, nWidth / 6);
	m_ServerInfo.InsertColumn(4, L"�汾", LVCFMT_CENTER, nWidth / 6);
	m_ServerInfo.InsertColumn(5, L"ж��·��", LVCFMT_CENTER, nWidth / 6);
}

// �һ���Ӧ(ȫ�����)
void Tab_SoftwarmangDialogbox::OnRclickList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	AfxMessageBox(L"���һ���ûɶ�ã�");
	*pResult = 0;
}

void Tab_SoftwarmangDialogbox::OnLvnItemchangedList2(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;
}

// �һ���Ӧ����ж�ز˵�
void Tab_SoftwarmangDialogbox::OnRclickList2(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	CMenu PopMen;
	PopMen.LoadMenuW(IDR_MENU5);
	POINT point;
	GetCursorPos(&point);
	CMenu *p = PopMen.GetSubMenu(0);
	p->TrackPopupMenu(TPM_LEFTBUTTON, point.x, point.y, this);
	*pResult = 0;
}

// ��������
void Tab_SoftwarmangDialogbox::StartService()
{
	// 1. ��ȡ��������
	int index = m_ServerInfo.GetSelectionMark();
	CString str = m_ServerInfo.GetItemText(index, 0);
	// 2. �򿪷�����������õ���ǰ���Ʒ���
	SC_HANDLE hSC = ::OpenSCManager(NULL,
		NULL, GENERIC_EXECUTE);
	SC_HANDLE hSvc = ::OpenService(hSC, str,
		SERVICE_START | SERVICE_QUERY_STATUS | SERVICE_STOP);
	if (hSvc == NULL)
	{
		TRACE("Open www erron��");
		::CloseServiceHandle(hSC);
		return;
	}
	// 3. ��ȡ����״̬
	SERVICE_STATUS status;
	if (::QueryServiceStatus(hSvc, &status) == FALSE)
	{
		TRACE("Get Service state error��");
		::CloseServiceHandle(hSvc);
		::CloseServiceHandle(hSC);
		return;
	}
	// 4. ��������
	if (status.dwCurrentState == SERVICE_STOPPED)
	{
		if (::StartService(hSvc, NULL, NULL) == FALSE)
		{
			TRACE("�������������");
			::CloseServiceHandle(hSvc);
			::CloseServiceHandle(hSC);
			return;
		}
		// �ȴ���������
		while (::QueryServiceStatus(hSvc, &status) == TRUE)
		{
			::Sleep(status.dwWaitHint);
			if (status.dwCurrentState == SERVICE_RUNNING)
			{
				AfxMessageBox(L"��������ɹ�");
				::CloseServiceHandle(hSvc);
				::CloseServiceHandle(hSC);
				return;
			}
		}
	}
	::CloseServiceHandle(hSvc);
	::CloseServiceHandle(hSC);
}

// �رշ���
void Tab_SoftwarmangDialogbox::StopService()
{
	// 1. ��ȡ��������
	int index = m_ServerInfo.GetSelectionMark();
	CString str = m_ServerInfo.GetItemText(index, 0);
	// 2. �򿪷�����������õ���ǰ���Ʒ���
	SC_HANDLE hSC = ::OpenSCManager(NULL,
		NULL, GENERIC_EXECUTE);
	SC_HANDLE hSvc = ::OpenService(hSC, str,
		SERVICE_START | SERVICE_QUERY_STATUS | SERVICE_STOP);
	if (hSvc == NULL)
	{
		TRACE("Open www erron��");
		::CloseServiceHandle(hSC);
		return;
	}
	// 3. ��ȡ����״̬
	SERVICE_STATUS status;
	if (::QueryServiceStatus(hSvc, &status) == FALSE)
	{
		TRACE("Get Service state error��");
		::CloseServiceHandle(hSvc);
		::CloseServiceHandle(hSC);
		return;
	}
	//�������ֹͣ״̬���������񣬷���ֹͣ����
	if (status.dwCurrentState == SERVICE_RUNNING)
	{
		// ֹͣ����
		if (::ControlService(hSvc,
			SERVICE_CONTROL_STOP, &status) == FALSE)
		{
			TRACE("stop service error��");
			::CloseServiceHandle(hSvc);
			::CloseServiceHandle(hSC);
			return;
		}
		// �ȴ�����ֹͣ
		while (::QueryServiceStatus(hSvc, &status) == TRUE)
		{
			::Sleep(status.dwWaitHint);
			if (status.dwCurrentState == SERVICE_STOPPED)
			{
				AfxMessageBox(L"����رճɹ�");
				::CloseServiceHandle(hSvc);
				::CloseServiceHandle(hSC);
				return;
			}
		}
	}
	::CloseServiceHandle(hSvc);
	::CloseServiceHandle(hSC);
}

// ж�����
void Tab_SoftwarmangDialogbox::SofwUninstall()
{
	// TODO:  �ڴ���������������
	char Path[MAX_PATH] = { 0 };
	int index = m_ServerInfo.GetSelectionMark();
	CString strPath = m_ServerInfo.GetItemText(index, 5);
	WideCharToMultiByte(CP_ACP, NULL, strPath, strPath.GetLength(), Path, sizeof(Path), NULL, NULL);
	WinExec(Path, SW_SHOW);
}

// ˢ�·���
void Tab_SoftwarmangDialogbox::OnBnClickedButton1()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	GetofShowAllSofwInfo();
	GetofShowSystemService();
}


void Tab_SoftwarmangDialogbox::OnHotKey(UINT nHotKeyId, UINT nKey1, UINT nKey2)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ

	CDialogEx::OnHotKey(nHotKeyId, nKey1, nKey2);
}
