// Tab_NetworktoolDialogbox.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Tab_NetworktoolDialogbox.h"
#include "afxdialogex.h"


// Tab_NetworktoolDialogbox �Ի���

IMPLEMENT_DYNAMIC(Tab_NetworktoolDialogbox, CDialogEx)


Tab_NetworktoolDialogbox::Tab_NetworktoolDialogbox(CWnd* pParent /*=NULL*/)
	: CDialogEx(Tab_NetworktoolDialogbox::IDD, pParent)
{

}

Tab_NetworktoolDialogbox::~Tab_NetworktoolDialogbox()
{
}

void Tab_NetworktoolDialogbox::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(Tab_NetworktoolDialogbox, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON4, &Tab_NetworktoolDialogbox::OnBnClickedButton4)
END_MESSAGE_MAP()


// Tab_NetworktoolDialogbox ��Ϣ�������

// ������HOOK�ػ�
void Tab_NetworktoolDialogbox::OnBnClickedButton4()
{

	char* WindowsDlgNmae = "Windows ���������";
	char* WindowsClassName = "#32770 (�Ի���)";
	//InjectDLL.dll
	char IngPath[MAX_PATH] = "E:\\VS��Ŀ\\Securityguards\\Debug\\DllInjer.dll";
	//char IngPath[MAX_PATH] = "E:\\InjectDLL.dll";



	// ��ȡ������������� �õ����������PID
	HWND hWind = ::FindWindowA(NULL, WindowsDlgNmae);
	GetWindowThreadProcessId(hWind, &m_TPid);

	m_SPid = GetCurrentProcessId();
	HANDLE hMap = CreateFileMapping(INVALID_HANDLE_VALUE,NULL,PAGE_READWRITE, 0, 0x10,L"Pid");
	LPVOID hP = MapViewOfFile(hMap,FILE_MAP_ALL_ACCESS,0,0,0);
	memcpy_s(hP, 0x10, &m_SPid, sizeof(DWORD));

	
	// 1. ��ȡ���̾��
	HANDLE hprocess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, m_TPid);
	if (NULL == hprocess)
	{
		AfxMessageBox(L"OpenProcess() failure");
		return;
	}
	DWORD dwSize = strlen(IngPath) + 1;
	// 2. ���������ڴ�
	LPVOID lpBuf = VirtualAllocEx(hprocess, NULL, dwSize, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
	sizeof(&lpBuf);
	if (NULL == lpBuf)
	{
		AfxMessageBox(L"VirtualAllEx() failure");
		return;
	}

	// 3. ·��д������������ڴ�
	INT ErrorCode = WriteProcessMemory(hprocess, lpBuf, IngPath, dwSize, &dwSize);
	if (0 >= ErrorCode)
	{
		AfxMessageBox(L"WriteProcessMemory() failuer!");
		VirtualFreeEx(hprocess, lpBuf, dwSize, MEM_RELEASE);
		CloseHandle(hprocess);
		return;
	}
	//// ����Ȩ�޲���
	//// HANDLE hpr = GetCurrentProcess();
	//HANDLE hToken;
	//// ��ȡ���̵ķ�������
	//OpenProcessToken(hprocess, TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken);
	//TOKEN_PRIVILEGES to32 = { 0 };
	//// ��ȡ��LUID
	//LookupPrivilegeValue(NULL, SE_SHUTDOWN_NAME, &to32.Privileges[0].Luid);
	//// ��Ȩ����
	//to32.PrivilegeCount = 1;
	//to32.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
	//AdjustTokenPrivileges(hToken, FALSE, &to32, sizeof(to32), NULL, NULL);
	// 4. ����Զ���߳�

	PVOID pRemoteProcess = CreateRemoteThreadEx(hprocess, NULL, NULL, (LPTHREAD_START_ROUTINE)LoadLibraryA, lpBuf, NULL, NULL, NULL);
	if (NULL == pRemoteProcess)
	{
		AfxMessageBox(L"CreateRemoteThreadEx() failuer");
		VirtualFreeEx(hprocess, lpBuf, dwSize, MEM_RELEASE);
		CloseHandle(hprocess);
		return;
	}

	// 5. �ȴ�Զ���߳�
	WaitForSingleObject(pRemoteProcess, INFINITE);

	// 6. �ͷż�����ر�
	VirtualFreeEx(hprocess, lpBuf, dwSize, MEM_RELEASE);
	CloseHandle(pRemoteProcess);
	CloseHandle(hprocess);
}


