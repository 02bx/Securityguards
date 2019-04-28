// Tab_resourceTables.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Tab_resourceTables.h"
#include "afxdialogex.h"
#include "RVAtoFOA.h"


// Tab_resourceTables �Ի���

IMPLEMENT_DYNAMIC(Tab_resourceTables, CDialogEx)

Tab_resourceTables::Tab_resourceTables(CWnd* pParent /*=NULL*/)
	: CDialogEx(Tab_resourceTables::IDD, pParent)
{

}

Tab_resourceTables::~Tab_resourceTables()
{
}

void Tab_resourceTables::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TREE1, m_TreeFile);
}

BEGIN_MESSAGE_MAP(Tab_resourceTables, CDialogEx)
	ON_NOTIFY(TVN_SELCHANGED, IDC_TREE1, &Tab_resourceTables::OnTvnSelchangedTree1)
END_MESSAGE_MAP()

// Tab_resourceTables ��Ϣ�������
void Tab_resourceTables::OnTvnSelchangedTree1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;
}

void Tab_resourceTables::ShowResourInfo()
{
	// ��һ�����ڵ�
	HTREEITEM m_hRoot = nullptr;
	// �ڶ������ڵ�
	HTREEITEM m_hRoot2 = nullptr;

	// ������Ϣ����һ���ã�
	char* arryResType[] = { "", "���ָ�루Cursor��", "λͼ��Bitmap��", "ͼ�꣨Icon��", "�˵���Menu��"
		, "�Ի���Dialog��", "�ַ����б�String Table��", "����Ŀ¼��Font Directory��", "���壨Font��", "��ݼ���Accelerators��"
		, "�Ǹ�ʽ����Դ��Unformatted��", "��Ϣ�б�Message Table��", "���ָ���飨Croup Cursor��", "", "ͼ���飨Group Icon��", ""
		, "�汾��Ϣ��Version Information��" };
	// ��Դ��׼����ַ��ȡ
	CString str;
	RVAtoFOA rva;
	PIMAGE_DOS_HEADER pDos = (PIMAGE_DOS_HEADER)m_lpBase;
	PIMAGE_NT_HEADERS pNt = (PIMAGE_NT_HEADERS)(pDos->e_lfanew + m_lpBase);
	PIMAGE_DATA_DIRECTORY pData = (PIMAGE_DATA_DIRECTORY)&pNt->OptionalHeader.DataDirectory[2];
	
	// 1.��ַ
	PIMAGE_RESOURCE_DIRECTORY pResHead = (PIMAGE_RESOURCE_DIRECTORY)(rva.RVAofFOAs(pData->VirtualAddress) + m_lpBase);
	// 2.��һ����������
	WORD dwCount_1 = pResHead->NumberOfIdEntries + pResHead->NumberOfNamedEntries;
	// 2.1 ����
	str.Format(L"%08X", pResHead->Characteristics);
	GetDlgItem(IDC_EDIT1)->SetWindowTextW(str);
	// 2.2 ʱ��
	str.Format(L"%08X", pResHead->TimeDateStamp);
	GetDlgItem(IDC_EDIT7)->SetWindowTextW(str);
	// 2.3 ���汾
	str.Format(L"%08X", pResHead->MajorVersion);
	GetDlgItem(IDC_EDIT2)->SetWindowTextW(str);
	// 2.4 �ΰ汾
	str.Format(L"%08X", pResHead->MajorVersion);
	GetDlgItem(IDC_EDIT6)->SetWindowTextW(str);
	// 2.5 ���ַ�����Ϊ��Դ��ʶ����Ŀ
	str.Format(L"%08X", pResHead->NumberOfNamedEntries);
	GetDlgItem(IDC_EDIT3)->SetWindowTextW(str);
	// 2.6 ������ID��Ϊ��Դ��ʶ��Ŀ
	str.Format(L"%08X", pResHead->NumberOfNamedEntries);
	GetDlgItem(IDC_EDIT4)->SetWindowTextW(str);
	// 2.7 ��Դ����Ŀ
	str.Format(L"%08X", dwCount_1);
	GetDlgItem(IDC_EDIT5)->SetWindowTextW(str);
	// 3.���entry(��һ��)
	PIMAGE_RESOURCE_DIRECTORY_ENTRY pResourcEntry = (PIMAGE_RESOURCE_DIRECTORY_ENTRY)(pResHead + 1);
	RVAtoFOA offset;
	// 4.������
	for (DWORD i = 0; i < dwCount_1; ++i)
	{
		// �ж����λ
		if (pResourcEntry->NameIsString){
			// �������һ��Ψһ
			PIMAGE_RESOURCE_DIR_STRING_U pName = (PIMAGE_RESOURCE_DIR_STRING_U)(pResourcEntry->NameOffset + (DWORD)pResHead);
			WCHAR* wcName = new WCHAR[pName->Length + 1]{};
			memcpy(wcName, pName->NameString, pName->Length * 2);
			// ��ӵ���һ��Ŀ¼  Tree (Name)
			m_hRoot = m_TreeFile.InsertItem(wcName);
		}
		else{
			// �������Ļ�
			if ((pResourcEntry->Id <= 16) && (pResourcEntry->Id >0))
			{
				// ������ʲô  arrResType[]
				str = arryResType[pResourcEntry->Id];
				m_TreeFile.InsertItem(str);
			}
			else
			{
				str.Format(L"04X", pResourcEntry->Id);
				m_TreeFile.InsertItem(str);
			}
		}

		// �ж��Ƿ�����һ��
		if (pResourcEntry->DataIsDirectory){
			// �ڶ���
			PIMAGE_RESOURCE_DIRECTORY pResources_2 = (PIMAGE_RESOURCE_DIRECTORY)(pResourcEntry->OffsetToDirectory + (DWORD)pResHead);
			// ��ȡ��ǰ����Դ����
			DWORD dwCount_2 = pResources_2->NumberOfIdEntries + pResources_2->NumberOfNamedEntries;
			// �ҵ�Entryͷ��ַ
			PIMAGE_RESOURCE_DIRECTORY_ENTRY pEntry2 = (PIMAGE_RESOURCE_DIRECTORY_ENTRY)(pResources_2 + 1);
			// �жϸ�λ�Ƿ����ַ�����
			for (DWORD i = 0; i < dwCount_2; ++i)
			{
				// ���Ǹ��ַ���
				if (pEntry2->NameIsString){
					PIMAGE_RESOURCE_DIR_STRING_U pName = 
						(PIMAGE_RESOURCE_DIR_STRING_U)(pEntry2->NameOffset + (DWORD)pResHead);
					WCHAR* wcName = new WCHAR[pName->Length + 1]{};
					memcpy(wcName, pName->NameString, pName->Length * 2);
					m_hRoot2 = m_TreeFile.InsertItem(wcName, m_hRoot);
				}
				else{
					// �ⲻ��һ���ַ���ID
					str.Format(L"%04X", pEntry2->Id);
					m_hRoot2 = m_TreeFile.InsertItem(str, m_hRoot);
				}

				// �Ƿ�����һ��
				if (pEntry2->DataIsDirectory)
				{
					PIMAGE_RESOURCE_DIRECTORY pResourc_3 = (PIMAGE_RESOURCE_DIRECTORY)(pEntry2->OffsetToDirectory + (DWORD)pResHead);
					PIMAGE_RESOURCE_DIRECTORY_ENTRY pEntry_3 = (PIMAGE_RESOURCE_DIRECTORY_ENTRY)(pResourc_3 + 1);
					PIMAGE_RESOURCE_DATA_ENTRY PDataEntry = (PIMAGE_RESOURCE_DATA_ENTRY)(pEntry_3->OffsetToData + (DWORD)pResHead);
					
					DWORD dwDataFOA = offset.RVAofFOAs(PDataEntry->OffsetToData);
					DWORD dwDataSize = PDataEntry->Size;
					// ��������Դ�ľ���λ��ƫ���Ǽ��ϼ��ػ�ַ
					unsigned char* pData = (unsigned char*)(dwDataFOA + m_lpBase);
					for (int i = 0; i < 10; i++)
					{
						// printf("%02X ", pData[i]);
						str.Format(L"%02X", pData[i]);
						m_TreeFile.InsertItem(str, m_hRoot2);
					}
				}
				++pResources_2;
			}// �ڶ���
		}
		++pResourcEntry;
	} // ��һ�β�
}

BOOL Tab_resourceTables::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��ʼ�����ؼ���Ϣ
	m_TreeFile.ModifyStyle(NULL, TVS_HASBUTTONS | TVS_HASLINES | TVS_LINESATROOT | TVS_EDITLABELS);
	// ��ʾ��Դ��������Ϣ
	ShowResourInfo();
	return TRUE;
}
