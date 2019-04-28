// Tab_MemoryDialogbox.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Tab_MemoryDialogbox.h"
#include "afxdialogex.h"
#include "Psapi.h"

// Tab_MemoryDialogbox �Ի���

// �̻߳ص������CPU���ٵ�����
DWORD WINAPI ThreadProc(LPVOID lparameter)
{
	Tab_MemoryDialogbox *pDlg = (Tab_MemoryDialogbox*)lparameter;
	pDlg->GetCpuUsage();
	return 0;
}

IMPLEMENT_DYNAMIC(Tab_MemoryDialogbox, CDialogEx)

Tab_MemoryDialogbox::Tab_MemoryDialogbox(CWnd* pParent /*=NULL*/)
	: CDialogEx(Tab_MemoryDialogbox::IDD, pParent)
	, m_Cpusyl(_T(""))
	, m_MemoryBFB(_T(""))
	, m_Pymemory(_T(""))
	, m_Pagesize(_T(""))
	, m_Memorysize(_T(""))
	, m_Kymemorysize(_T(""))
{

}

Tab_MemoryDialogbox::~Tab_MemoryDialogbox()
{
}

void Tab_MemoryDialogbox::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_ListCtr);
	DDX_Text(pDX, IDC_CPUSYL, m_Cpusyl);
	DDX_Text(pDX, IDC_MEMORYBFB, m_MemoryBFB);
	DDX_Text(pDX, IDC_PHMEMORY, m_Pymemory);
	DDX_Text(pDX, IDC_PAGESIZE, m_Pagesize);
	DDX_Text(pDX, IDC_MEMORYSIZE, m_Memorysize);
	DDX_Text(pDX, IDC_KYMEMORYSIZE, m_Kymemorysize);
}


BEGIN_MESSAGE_MAP(Tab_MemoryDialogbox, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON8, &Tab_MemoryDialogbox::OnBnClickedButton8)
	ON_WM_TIMER()
END_MESSAGE_MAP()


// Tab_MemoryDialogbox ��Ϣ�������

BOOL Tab_MemoryDialogbox::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	CRect rc;
	m_ListCtr.GetClientRect(rc);
	int nWidth = rc.Width();
	DWORD dwOldsytle;
	dwOldsytle = m_ListCtr.GetExtendedStyle();
	m_ListCtr.SetExtendedStyle(dwOldsytle | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

	m_ListCtr.InsertColumn(0, L"״̬	", LVCFMT_CENTER, nWidth / 5);
	m_ListCtr.InsertColumn(1, L"BLOCK RVA", LVCFMT_CENTER, nWidth / 5);
	m_ListCtr.InsertColumn(2, L"�ڴ�����", LVCFMT_CENTER, nWidth / 5);
	m_ListCtr.InsertColumn(3, L"�ڴ��ҳ����", LVCFMT_CENTER, nWidth / 5);
	m_ListCtr.InsertColumn(4, L"���С", LVCFMT_CENTER, nWidth / 5);
	// ��ʾ�����ڴ���Ϣ
	queryViryualMemoryStatue(GetCurrentProcess());
	// ��ʾCPUʹ����
	GetCpuUsage();
	// ��ʾ�����ڴ���Ϣ
	GetMemoryInfo();
	// ���±������ؼ�
	UpdateData(FALSE);
	// Settimer
	SetTimer(1, 1000, NULL);
	return TRUE; 
}

// ʱ��ת��
double Tab_MemoryDialogbox::FILETIMEDouble(const _FILETIME & filetime)
{
	return double(filetime.dwHighDateTime * 4.294967296e9) + double(filetime.dwLowDateTime);
}

// ��ȡCPU��ռ����
void Tab_MemoryDialogbox::GetCpuUsage()
{
	// ��ȡ����ʱ�� �ں� �û�
	_FILETIME idleTime, kernelTime, userTime;
	GetSystemTimes(&idleTime, &kernelTime, &userTime);
	// Creates or opens a named or unnamed event object.
	// �������һ�������Ļ��������¼�����
	// failure 0  | sucess handle
	HANDLE hEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
	// �ȴ�1000���룬�ں˶�������ȷ
	WaitForSingleObject(hEvent, 1000);
	// ��ȡ�µ�ʱ��
	_FILETIME newidleTime, newkernelTime, newuserTime;
	GetSystemTimes(&newidleTime, &newkernelTime, &newuserTime);
	// ת��ʱ��
	double	doldidleTime = FILETIMEDouble(idleTime);
	double	doldkernelTime = FILETIMEDouble(kernelTime);
	double	dolduserTime = FILETIMEDouble(userTime);
	double	dnewidleTime = FILETIMEDouble(newidleTime);
	double	dnewkernelTime = FILETIMEDouble(newkernelTime);
	double	dnewuserTime = FILETIMEDouble(newuserTime);
	double	Times = dnewidleTime - doldidleTime;
	double	Kerneltime = dnewkernelTime - doldkernelTime;
	double	usertime = dnewuserTime - dolduserTime;
	// ����ʹ����
	double Cpurate = (100.0 - Times / (Kerneltime + usertime) * 100.0);
	m_Cpusyl.Format(L"%0.2lf", Cpurate);
	m_Cpusyl += "%";
}

// ��ȡ�����ڴ���Ϣ
void Tab_MemoryDialogbox::GetMemoryInfo()
{
	// �����ṹ����� ��ȡ�ڴ���Ϣ����
	MEMORYSTATUS memStatus;
	GlobalMemoryStatus(&memStatus);
	// ��ǰռ���� Occupancy rate
	m_MemoryBFB.Format(L"%u", memStatus.dwMemoryLoad);
	m_MemoryBFB += "%";
	// ��ʹ�������ڴ��С Physical memory size
	size_t memPhysize = memStatus.dwTotalPhys - memStatus.dwAvailPhys;
	m_Pymemory.Format(L"%u", (memPhysize / 1024 / 1024 / 8));
	m_Pymemory += " MB";
	// �ļ�������С Size of the file exchange
	m_Pagesize.Format(L"%u", (memStatus.dwAvailPageFile / 1024 / 1024 / 8));
	m_Pagesize += " MB";
	// �����ڴ��С Virtual memory size
	m_Memorysize.Format(L"%u", (memStatus.dwTotalVirtual / 1024 / 1024 / 8));
	m_Memorysize += " MB";
	// ���������ڴ��С Available virtual memory size
	m_Kymemorysize.Format(L"%d", (memStatus.dwAvailVirtual / 1024 / 1024 / 8));
	m_Kymemorysize += " MB";
}

// һ���Ż��ڴ�
void Tab_MemoryDialogbox::OnBnClickedButton8()
{
	CString str, str1;
	str = "һ�����ٳɹ��� ��ʡ�˿ռ䣺  ";
	// 1. ��ȡ��ǰ���������ڴ�״̬
	MEMORYSTATUSEX stcMemStatusEx = { 0 };
	stcMemStatusEx.dwLength = sizeof(stcMemStatusEx);
	GlobalMemoryStatusEx(&stcMemStatusEx);
	DWORDLONG preUsedMem = stcMemStatusEx.ullTotalPhys - stcMemStatusEx.ullAvailPhys;
	// 2. �����ڴ�
	DWORD dwPIDList[1000] = { 0 };
	DWORD bufSize = sizeof(dwPIDList);
	DWORD dwNeedSize = 0;
	EnumProcesses(dwPIDList, bufSize, &dwNeedSize);
	for (DWORD i = 0; i < dwNeedSize / sizeof(DWORD); ++i)
	{
		HANDLE hProccess = OpenProcess(PROCESS_SET_QUOTA, false, dwPIDList[i]);
		SetProcessWorkingSetSize(hProccess, -1, -1);
	}
	// 3. ��ȡ�������ڴ�״̬
	GlobalMemoryStatusEx(&stcMemStatusEx);
	DWORDLONG afterCleanUserdMem = stcMemStatusEx.ullTotalPhys - stcMemStatusEx.ullAvailPhys;
	// 4. ���㲢��������ɹ�
	DWORDLONG CleanofSuccess = preUsedMem - afterCleanUserdMem;
	str1.Format(L"%d", (CleanofSuccess / 1024 / 1024 / 8));
	str = str + str1 + " MB";
	if (CleanofSuccess > 0)
		::MessageBox(NULL, str, L"���ٳɹ��y�z�|�}�� ", 0);
}

// ��ȡ���ڴ����
void Tab_MemoryDialogbox::queryViryualMemoryStatue(HANDLE hProccess)
{
	m_ListCtr.DeleteAllItems();
	int count = 0;
	CString str;
	MEMORY_BASIC_INFORMATION	mbi = { 0 };
	VMINFO						statue = { 0 };
	DWORD						dwAddress = 0;
	DWORD						dwSize = 0;
	BOOL						bRet = FALSE;
	while (1) {

		bRet = VirtualQueryEx(hProccess,
			(LPCVOID)dwAddress,
			&mbi,
			sizeof(MEMORY_BASIC_INFORMATION));
		if (bRet == FALSE)
			break;

		statue.address = dwAddress;
		statue.state = (MEMORYSTATE)mbi.State;
		dwSize = mbi.RegionSize;

		// ����ڴ�״̬, 
		// �ڴ�״̬�������������ڴ���û�к�����洢�����й���.
		// ���Ƿ�Ԥ��.
		// free   : ����,û��Ԥ��,û�к�����洢������
		// reserve: ����,��Ԥ��,û�к�����洢������
		// commit : �ύ,�Ѿ�������洢������
		switch (statue.state) {
		case e_stat_free:
			str.Format(L"free:          0x%08X", statue.address);
			m_ListCtr.InsertItem(count, str);
			break;
		case e_stat_reserve:
			str.Format(L"reserve:   0x%08X", statue.address);
			m_ListCtr.InsertItem(count, str);
			break;
		case e_stat_commit:
			str.Format(L"commit:   0x%08X", statue.address);
			m_ListCtr.InsertItem(count, str);
			break;
		}

		// ����ڴ��ַ�Ѿ��ύ�������ڴ�,������ύ����ÿһ���ڴ��.
		if (statue.state == e_stat_commit) {

			dwSize = 0;
			LPVOID	dwAllocationBase = mbi.AllocationBase;
			DWORD	dwBlockAddress = (DWORD)dwAddress;
			while (1) {

				bRet = VirtualQueryEx(hProccess,
					(LPCVOID)dwBlockAddress,
					&mbi,
					sizeof(MEMORY_BASIC_INFORMATION));
				if (bRet == FALSE) {
					break;
				}


				// �жϱ����������ڴ���Ƿ���ͬһ��.(�����ǵķ�����׵�ַ�Ƿ����.)
				// �������,������ѭ��.
				if (mbi.AllocationBase != dwAllocationBase)
					break;
				// ���RVA
				str.Format(L"0x%08X", dwBlockAddress);
				m_ListCtr.SetItemText(count, 1, str);

				// ����ڴ�����
				// �ڴ����ͱ�ʾ�����ڴ����Ժ��ַ�ʽ������洢�����й���
				// image  : �Ǵ�Ӱ���ļ���ӳ�����
				// mapped : �ڴ�ӳ��
				// private: ˽���ڴ�,���������޷�����.
				switch (mbi.Type) {
				case e_type_image:
					m_ListCtr.SetItemText(count, 2, L"image");
					break;
				case e_type_mapped:
					m_ListCtr.SetItemText(count, 2, L"mapped");
					break;
				case e_type_private:
					m_ListCtr.SetItemText(count, 2, L"private");
					break;
				default:
					break;
				}

				// ����ڴ��ҳ����
				// �ڴ��ҳ�������ڱ�ʾ�ڴ��ҳ�ܹ����к��ַ���,���,д,ִ��,дʱ����.
				if (mbi.Protect == 0)
					m_ListCtr.SetItemText(count, 3, L"---");
				else if (mbi.Protect & PAGE_EXECUTE)
					m_ListCtr.SetItemText(count, 3, L"E--");
				else if (mbi.Protect & PAGE_EXECUTE_READ)
					m_ListCtr.SetItemText(count, 3, L"ER-");
				else if (mbi.Protect & PAGE_EXECUTE_READWRITE)
					m_ListCtr.SetItemText(count, 3, L"ERW");
				else if (mbi.Protect & PAGE_READONLY)
					m_ListCtr.SetItemText(count, 3, L"-R-");
				else if (mbi.Protect & PAGE_READWRITE)
					m_ListCtr.SetItemText(count, 3, L"-RW");
				else if (mbi.Protect & PAGE_WRITECOPY)
					m_ListCtr.SetItemText(count, 3, L"WCOPY");
				else if (mbi.Protect & PAGE_EXECUTE_WRITECOPY)
					m_ListCtr.SetItemText(count, 3, L"EWCOPY");

				// ����ڴ��Ĵ�С.
				// printf(" ��С:0x%X\n", mbi.RegionSize);
				str.Format(L"0x%X", mbi.RegionSize);
				m_ListCtr.SetItemText(count, 4, str);
				// ��������һ���ڴ��
				dwBlockAddress += mbi.RegionSize;

				// �ۼ��ڴ��Ĵ�С
				dwSize += mbi.RegionSize;
			}
		}

		statue.size = dwSize;
		this->vmlist.push_back(statue);
		// ������һ�������ڴ�.
		dwAddress += dwSize;
		++count;
	}
}

// ÿms�����������
void Tab_MemoryDialogbox::OnTimer(UINT_PTR nIDEvent)
{
	m_ListCtr.SetRedraw(FALSE);
	// ����CPUʹ���� д���̻߳ص�
	HANDLE thProcces = CreateThread(NULL, NULL, ThreadProc, (LPVOID)this, NULL, NULL);
	// ���������ڴ�����
	GetMemoryInfo();
	// �����ڴ����
	queryViryualMemoryStatue(GetCurrentProcess());
	//��������
	UpdateData(FALSE);
	m_ListCtr.SetRedraw(TRUE);
	m_ListCtr.Invalidate();
	m_ListCtr.UpdateWindow();
	// CloseHandle(thProcces);
	CDialogEx::OnTimer(nIDEvent);
}
