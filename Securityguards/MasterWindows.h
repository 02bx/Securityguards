#pragma once
#include "stdafx.h"
#include "resource.h"
#include "MasterTabCtrl.h"
#include "afxwin.h"

// MasterWindows �Ի���

class MasterWindows : public CDialogEx
{
	DECLARE_DYNAMIC(MasterWindows)

public:
	MasterWindows(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~MasterWindows();

// �Ի�������
	enum { IDD = IDD_MasterWindow };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()

public:
	virtual BOOL OnInitDialog();
	void SetdwCount(const int dwCount){ this->m_dwCount = dwCount; }
private:
	// 4. ��ȡϵͳȨ��
	void GetSystempermissions();
	MasterTabCtrl m_Tab_control;						// Tab����
	int m_dwCount = 0;									// ���ڸ���
	static const TCHAR tab_Name[7][12];					// ��������
	CBrush m_bush;
public:
	CStatic m_PictrueWolf;
	afx_msg void On40021();
	afx_msg void Reboot();
	afx_msg void Lockscreen();
	afx_msg void Cancellation();
	afx_msg void BOOSKEY();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};
