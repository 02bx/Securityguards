#pragma once

// MFCsockclass ����Ŀ��

class MFCsockclass : public CSocket
{
public:
	MFCsockclass();
	virtual ~MFCsockclass();
	virtual void OnReceive(int nErrorCode);

public:
	// ���� ��Ӧthisָ��
	static LPVOID Thisptr;

private:
	const int m_port = 1234;
};


