// WhiteDialogBox.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "WhiteDialogBox.h"
#include "afxdialogex.h"


// WhiteDialogBox �Ի���

vector<CString> WhiteDialogBox::WhiteName = { };

IMPLEMENT_DYNAMIC(WhiteDialogBox, CDialogEx)

WhiteDialogBox::WhiteDialogBox(CWnd* pParent /*=NULL*/)
	: CDialogEx(WhiteDialogBox::IDD, pParent)
	, m_WhiteEdit(_T(""))
{

}

WhiteDialogBox::~WhiteDialogBox()
{
}

void WhiteDialogBox::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_WhiteEdit);
	DDX_Control(pDX, IDC_LIST1, m_ListArr);
}

BEGIN_MESSAGE_MAP(WhiteDialogBox, CDialogEx)
	ON_BN_CLICKED(IDOK, &WhiteDialogBox::OnBnClickedOk)
	ON_BN_CLICKED(IDC_WHITEBUUT, &WhiteDialogBox::OnBnClickedCancel)
	ON_WM_DROPFILES()
END_MESSAGE_MAP()


// WhiteDialogBox ��Ϣ�������

BOOL WhiteDialogBox::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	// 1.��ȡ���
	CRect rc;
	this->GetClientRect(rc);
	int nWidth = rc.Width();
	// 2.��ȡ/���÷��
	DWORD dwOldStyle;
	dwOldStyle = m_ListArr.GetExtendedStyle();
	m_ListArr.SetExtendedStyle(dwOldStyle | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_ListArr.InsertColumn(0, L"����������ɱ��", 0, nWidth / 1);
	UpdateListName();
	return TRUE;
}

// ����List
void WhiteDialogBox::UpdateListName()
{
	m_ListArr.DeleteAllItems();
	for (SIZE_T i = 0; i < WhiteName.size(); ++i)
	{
		m_ListArr.InsertItem(i, WhiteName[i].GetBuffer(0));
	}
}

// ��Ӹ���
void WhiteDialogBox::OnBnClickedOk()
{
	UpdateData(TRUE);
	UpdateListName();
	m_WhiteEdit = " ";
	UpdateData(FALSE);

	// CDialogEx::OnOK();
}

// ɾ����ť
void WhiteDialogBox::OnBnClickedCancel()
{
	int index = m_ListArr.GetSelectionMark();
	CString strName = m_ListArr.GetItemText(index, 0);
	auto nDelete = find(WhiteName.begin(), WhiteName.end(), strName);
	if (nDelete != WhiteName.end())
		WhiteName.erase(nDelete);
	UpdateListName();
	// CDialogEx::OnCancel();
}

// ��Ӧ�ļ���ק
void WhiteDialogBox::OnDropFiles(HDROP hDropInfo)
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
		// 4. �������ظ�����ļ�
		if (find(WhiteName.begin(), WhiteName.end(), wcStr) == WhiteName.end())
			WhiteName.push_back(wcStr);
		m_WhiteEdit.Append(wcStr);
	}
	UpdateData(FALSE);
	// 4. �ͷ��ڴ�
	DragFinish(hDropInfo);
	CDialogEx::OnDropFiles(hDropInfo);
}
