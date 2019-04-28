// Tab_FilePosition.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Tab_FilePosition.h"
#include "afxdialogex.h"
#include "RVAtoFOA.h"

// Tab_FilePosition �Ի���

IMPLEMENT_DYNAMIC(Tab_FilePosition, CDialogEx)

Tab_FilePosition::Tab_FilePosition(CWnd* pParent /*=NULL*/)
	: CDialogEx(Tab_FilePosition::IDD, pParent)
	, m_ImageBase(0)
	, m_vritualAddress(0)
	, m_offsetS(0)
	, m_editupdate(_T(""))
{

}

Tab_FilePosition::~Tab_FilePosition()
{
}

void Tab_FilePosition::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_ImageBase);
	DDX_Text(pDX, IDC_EDIT2, m_vritualAddress);
	DDX_Text(pDX, IDC_EDIT3, m_offsetS);
	DDX_Text(pDX, IDC_SUCCESS, m_editupdate);
}


BEGIN_MESSAGE_MAP(Tab_FilePosition, CDialogEx)
	ON_BN_CLICKED(IDOK, &Tab_FilePosition::OnBnClickedOk)
END_MESSAGE_MAP()


// Tab_FilePosition ��Ϣ�������

BOOL Tab_FilePosition::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	return TRUE;
}

// ����ִ�е�ʱ��
void Tab_FilePosition::OnBnClickedOk()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	RVAtoFOA Getrva;
	_SAVERVAOFOFFSET obj = { 0 };;
	// 1.��ȡ�༭������
	UpdateData(TRUE);
	// 2.VA + RVA = ƫ����   BUG ʮ������� Ӧ����16����
	obj = Getrva.GetRvaofFOA(m_vritualAddress);
	// m_offsetS = m_ImageBase + m_vritualAddress;
	m_offsetS = obj.offset;
	m_editupdate += "�ɹ�";
	// 3.���µ��ؼ�
	UpdateData(FALSE);

	// CDialogEx::OnOK();
}

