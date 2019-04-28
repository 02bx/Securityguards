#pragma once


// MasterTabCtrl

class MasterTabCtrl : public CTabCtrl
{
	DECLARE_DYNAMIC(MasterTabCtrl)

public:
	MasterTabCtrl();
	virtual ~MasterTabCtrl();

// �����ӿ�
public:
	// ��ʼ��Tab
	BOOL InitData(DWORD dwCount, ...);
	// ���Ӵ���
	BOOL AddData(DWORD dwCount, ...);
	// ����
	BOOL SetSelAndShow(int nSel);
// ˽�нӿ�
private:
	// ����
	CDialogEx* m_pDlg[10];
	DWORD m_dwCount = 0;

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnTcnSelchange(NMHDR *pNMHDR, LRESULT *pResult);
};


