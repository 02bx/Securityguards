// dllmain.cpp : ���� DLL Ӧ�ó������ڵ㡣
#include "stdafx.h"

HANDLE WINAPI MyOpenProcess(DWORD dwDesiredAccess,	BOOL bInheritHandle, DWORD dwProcessId);
DWORD Pid;
void InstallHOOK();
void UninstallHOOK();
// ����ԭ������
BYTE g_oldFun[5];
BYTE g_NewFun[5] = { 0xE9 };


BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
					 )
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
	{
		MessageBox(NULL, L"X64���������", L"ע��", NULL);
		InstallHOOK();
	}
	break;
	// case DLL_THREAD_ATTACH:
	// case DLL_THREAD_DETACH:
		// �Ͽ�
	case DLL_PROCESS_DETACH:
		UninstallHOOK();
		break;
	}
	return TRUE;
}


HANDLE WINAPI MyOpenProcess(DWORD dwDesiredAccess,
	BOOL bInheritHandle, DWORD dwProcessId)
{
	if (dwProcessId == Pid)
	{
		::MessageBox(NULL, L"��Ȩ�ر��ػ�����", L"����", NULL);
		return NULL;
	}
	else
	{
		UninstallHOOK();
		HANDLE hProc = OpenProcess(dwDesiredAccess, bInheritHandle, dwProcessId);
		InstallHOOK();
		return hProc;
	}
}

// ��װHOOK
void InstallHOOK()
{
	HANDLE hMap = OpenFileMapping(FILE_MAP_ALL_ACCESS,FALSE,L"Pid");
	LPVOID hAddr = MapViewOfFile(hMap, FILE_MAP_ALL_ACCESS,0,0,0x10);
	Pid = *(DWORD*)hAddr;

	// 1. ����ԭ����OPcpde
	memcpy(g_oldFun, OpenProcess, 5);
	// 2. ����ƫ��
	DWORD dwOffset = (DWORD)MyOpenProcess - (DWORD)OpenProcess - 5;
	// 3. 
	*(DWORD *)(g_NewFun + 1) = dwOffset;
	DWORD dwOldAttrubet = 0;
	// 4. �����ڴ�ռ�
	VirtualProtect(OpenProcess, 5, PAGE_EXECUTE_READWRITE, &dwOldAttrubet);
	// 5. �޸�diamante
	memcpy(OpenProcess, g_NewFun, 5);
	// 6. �ָ�ԭ�����ڴ�����
	VirtualProtect(OpenProcess, 5, dwOldAttrubet, &dwOldAttrubet);


}

// ж��HOOK
void UninstallHOOK()
{
	DWORD dwoldAttrubet;
	// ��ȡ����
	VirtualProtect(OpenProcess, 5, PAGE_EXECUTE_READWRITE, &dwoldAttrubet);

	memcpy(OpenProcess, g_oldFun, 5);
	
	VirtualProtect(OpenProcess, 5, dwoldAttrubet, &dwoldAttrubet);

}

