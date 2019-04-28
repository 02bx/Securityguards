#include "RVAtoFOA.h"

char* RVAtoFOA::g_NamelpBase = 0;

RVAtoFOA::RVAtoFOA()
{

}

RVAtoFOA::~RVAtoFOA()
{

}

// RVA --> offset
DWORD RVAtoFOA::RVAofFOAs(const DWORD dwRVA)
{
	// 1.��ȡDOSͷ
	PIMAGE_DOS_HEADER pDos = (PIMAGE_DOS_HEADER)g_NamelpBase;
	// 2.��ȡPEͷ
	PIMAGE_NT_HEADERS pNt = (PIMAGE_NT_HEADERS)(pDos->e_lfanew + g_NamelpBase);
	// 3.��ȡ��ͷ
	PIMAGE_SECTION_HEADER pSection = IMAGE_FIRST_SECTION(pNt);
	// 4.��ȡ��������
	DWORD dwCount = pNt->FileHeader.NumberOfSections;
	// 5.ѭ���ж��������Ǹ�����
	for (DWORD i = 0; i < dwCount; ++i)
	{
		// 6.�ڸ�����
		if ((dwRVA >= pSection->VirtualAddress) && (dwRVA < (pSection->VirtualAddress + pSection->SizeOfRawData))){
			// 7.���� RVA��ת�� - RVA������+ offset(��) 
			return dwRVA - pSection->VirtualAddress + pSection->PointerToRawData;
		}
		++pSection;
	}
	return 0;
}

_SAVERVAOFOFFSET RVAtoFOA::GetRvaofFOA(const DWORD dwRVA)
{
	_SAVERVAOFOFFSET sa = { 0 };
	// 1.��ȡDOSͷ
	PIMAGE_DOS_HEADER pDos = (PIMAGE_DOS_HEADER)g_NamelpBase;
	// 2.��ȡPEͷ
	PIMAGE_NT_HEADERS pNt = (PIMAGE_NT_HEADERS)(pDos->e_lfanew + g_NamelpBase);
	// 3.��ȡ��ͷ
	PIMAGE_SECTION_HEADER pSection = IMAGE_FIRST_SECTION(pNt);
	// 4.��ȡ��������
	DWORD dwCount = pNt->FileHeader.NumberOfSections;
	// 5.ѭ���ж��������Ǹ�����
	for (DWORD i = 0; i < dwCount; ++i)
	{
		// 6.�ڸ�����
		if ((dwRVA >= pSection->VirtualAddress) && (dwRVA < (pSection->VirtualAddress + pSection->SizeOfRawData))){
			// 7.���� RVA��ת�� - RVA������+ offset(��) 
			sa.Rva = pSection->VirtualAddress;
			sa.offset =  pSection->PointerToRawData;
			return sa;
		}
		++pSection;
	}
	return sa;
}