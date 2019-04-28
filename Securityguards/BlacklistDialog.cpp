// BlacklistDialog.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "BlacklistDialog.h"
#include "afxdialogex.h"


// BlacklistDialog �Ի���

vector<CString> BlacklistDialog::nBlackList = {};

IMPLEMENT_DYNAMIC(BlacklistDialog, CDialogEx)

BlacklistDialog::BlacklistDialog(CWnd* pParent /*=NULL*/)
	: CDialogEx(BlacklistDialog::IDD, pParent)
	, m_BlackList(_T(""))
{

}

BlacklistDialog::~BlacklistDialog()
{
}

void BlacklistDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_blacklsit);
	DDX_Text(pDX, IDC_EDIT1, m_BlackList);
}


BEGIN_MESSAGE_MAP(BlacklistDialog, CDialogEx)
	ON_WM_DROPFILES()
	ON_BN_CLICKED(IDOK, &BlacklistDialog::OnBnClickedOk)
	ON_BN_CLICKED(IDC_DELETE_BUTTON, &BlacklistDialog::OnBnClickedCancel)
END_MESSAGE_MAP()


// BlacklistDialog ��Ϣ�������


BOOL BlacklistDialog::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	// 1.��ȡ���
	CRect rc;
	this->GetClientRect(rc);
	int nWidth = rc.Width();
	// 2.��ȡ/���÷��
	DWORD dwOldStyle;
	dwOldStyle = m_blacklsit.GetExtendedStyle();
	m_blacklsit.SetExtendedStyle(dwOldStyle | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_blacklsit.InsertColumn(0, L"����������ɱ��", 0, nWidth / 1);
	UpdateList();
	return TRUE;
}

// ��Ӧ��ק��Ϣ
void BlacklistDialog::OnDropFiles(HDROP hDropInfo)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	CString str;
	// 1. ��ȡ�ļ���ק��Ŀ ����ڶ�������Ϊ-1�򷵻�һ�������ļ�ɾ��
	int DropCount = DragQueryFile(hDropInfo, -1, NULL, 0);
	// 2. ѭ����ȡ��ÿһ���ļ�
	for (int i = 0; i < DropCount; ++i)
	{
		WCHAR wcStr[MAX_PATH] = { 0 };
		// 3. ��ȡ��ק��i���ļ���
		DragQueryFile(hDropInfo, i, wcStr, MAX_PATH);
		if (find(nBlackList.begin(), nBlackList.end(), wcStr) == nBlackList.end())
			nBlackList.push_back(wcStr);
		m_BlackList.Append(wcStr);
	}
	UpdateData(FALSE);
	// 4. �ͷ��ڴ�
	DragFinish(hDropInfo);
	CDialogEx::OnDropFiles(hDropInfo);
}

// ���º������б�
void BlacklistDialog::OnBnClickedOk()
{
	UpdateData(TRUE);
	UpdateList();
	m_BlackList = " ";
	UpdateData(FALSE);
	// CDialogEx::OnOK();
}

// ɾ���������б�
void BlacklistDialog::OnBnClickedCancel()
{
	CString strName;
	int index = m_blacklsit.GetSelectionMark();
	strName = m_blacklsit.GetItemText(index, 0);
	auto nDelete = find(nBlackList.begin(), nBlackList.end(), strName);
	nBlackList.erase(nDelete);
	// ɾ����֮������б�
	UpdateList();
	// CDialogEx::OnCancel();
}

// ��װ
void BlacklistDialog::UpdateList()
{
	for (size_t i = 0; i < nBlackList.size(); ++i)
	{
		m_blacklsit.InsertItem(i, nBlackList[i].GetBuffer(0));
	}
}
