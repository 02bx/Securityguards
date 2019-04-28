#pragma once
#include "stdafx.h"
#include "resource.h"
#include "afxcmn.h"

// Tab_SectionView �Ի���

class Tab_SectionView : public CDialogEx
{
	DECLARE_DYNAMIC(Tab_SectionView)

public:
	Tab_SectionView(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~Tab_SectionView();

// �Ի�������
	enum { IDD = IDD_SECTIONVIEW };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_listCtr;
	virtual BOOL OnInitDialog();
	static const TCHAR strName[6][20];
	void ShowDateInfo();
	// ���ݼ��ؽӿ�
	void SetlpBase(char* lpbase){ this->m_lpBase = lpbase; }
private:
	char* m_lpBase;										// ������ص�ַ
	TCHAR buf[MAX_PATH] = {};							// ������ʱ����
};
