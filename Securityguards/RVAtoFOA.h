#pragma once
#ifndef RVATOFOA_H_
#define RVATOFOA_H_
#include <afxwin.h>
#include <windows.h>

struct _SAVERVAOFOFFSET
{
	DWORD Rva;
	DWORD offset;
};

class RVAtoFOA{
public:
	RVAtoFOA();
	~RVAtoFOA();
public:
	// ����ȫ���ļ���
	static char* g_NamelpBase;
	// ת������
	DWORD RVAofFOAs(const DWORD dwRVA);
	// ��ȡ��ǰ���ε�����
	_SAVERVAOFOFFSET GetRvaofFOA(const DWORD dwRVA);
};



#endif