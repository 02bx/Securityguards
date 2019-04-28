// MFCsockclass.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MFCsockclass.h"
#include "Tab_LDCS.h"


// MFCsockclass
LPVOID MFCsockclass::Thisptr = nullptr;

MFCsockclass::MFCsockclass()
{
	// 1. ��ʼ��ģ��
	WSADATA wsaData = { 0 };
	if (NULL != WSAStartup(MAKEWORD(2, 2), &wsaData))
	{
		AfxMessageBox(L"��ʼ��WSAStartup()ʧ��");
	}
}

MFCsockclass::~MFCsockclass()
{
	// �ͷ��׽���
	this->Close();
	// ���WSA
	WSACleanup();
}

// MFCsockclass ��Ա����

// �������������������ݰ�
void MFCsockclass::OnReceive(int nErrorCode)
{
	// 1. ��Ӧ��������������Ϣ
	char* pData = NULL;
	pData = new char[1024]{0};
	this->Receive(pData, sizeof(char) * 1024, 0);

	// 2. ���ú�������
	Tab_LDCS* ldcs = (Tab_LDCS *)Thisptr;
	ldcs->OnReceives(NULL, (LPARAM)pData);

	// 3. �ͷŵ��ѿռ�
	delete pData;
	pData = NULL;
	CSocket::OnReceive(nErrorCode);
}
