#pragma once
#include "stdafx.h"
#include "resource.h"
#include "afxwin.h"
#include <vector>
#include "afxcmn.h"
// Tab_CleanruDialogbox �Ի���

using namespace std;

class Tab_CleanruDialogbox : public CDialogEx
{
	DECLARE_DYNAMIC(Tab_CleanruDialogbox)

public:
	Tab_CleanruDialogbox(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~Tab_CleanruDialogbox();

// �Ի�������
	enum { IDD = IDD_Clean_rubbish };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CComboBox m_TypeSelect;
	afx_msg void OnCbnSelchangeCombo1();
	CString m_EditText;
	CEdit m_EditTexts;
	CButton m_GetEditText;
	afx_msg void OnDropFiles(HDROP hDropInfo);
private:
	static int FileNumbersFlag;		// ��¼��ǰ�ļ�·��һ��ռ�ü���
	int Flag = 0;					// ���������׺	
	vector<CString> PathString;		// ����·��������
	static CString ExtendString;	// VS�����׺·��
	static CString UserExtendString;// �Զ��������׺·��
	vector<CString> DeletString;	// Ҫɾ�����ļ�
	INT FileCount, DestCount;		// ���ļ�����
	LARGE_INTEGER CountSize;		// �ļ��ܴ�С
	INT DeleteCount;				// ��ɾ�����ļ�����
	LARGE_INTEGER DestSize;			// ��ɾ���ļ��Ĵ�С
	TCHAR buf[MAX_PATH] = { };		// �����Զ����ļ���Ϣ������
	CString strPath;				// �����������ϵͳ��������·��
	void GetDeleteFileList(vector<CString> PathStrings);	// ��ȡ��ɾ���б�
	void FindFile(CString Path);	// ���ұ����ļ�
public:
	CString m_cleaFilenumber;
	CString m_cleaFileSizeof;
	CStatic m_cleaDeleFileCount;
	CString m_cleaDeleFileCounts;
	afx_msg void OnBnClickedOk();
	CListCtrl m_cleaDeleteInfoList;
	CListCtrl m_cleaFileInfoList;
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton3();
	CEdit m_SuffixFileName;
	afx_msg void OnBnClickedButton2();
	CButton m_Suffix;
	CString m_SuffixFileNameValues;
};
