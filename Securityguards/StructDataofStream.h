/*����Ϊȫ��Ψһ*/
#pragma once
#include "windows.h"

// ö�ٽṹ���¼��Ϣ����
enum SockEnum
{
	MD5MEEAGE = 2,		// MD5�ϴ�
	MD5SELECT = 3		// MD5��ѯ
};

// MD5��Ӧ��Ϣ
typedef struct _MESSAGECONTENT
{
	LONG ulFileSize;
	char sMD5[36];
}MESSAGECONTENT, *PMESSAGECONTENT;

// �ͻ��˷������ݰ���������
typedef struct _SOCKETSEND
{
	HANDLE hWnd;				// ���ھ��
	SockEnum eEnum;				// ��Ϣ����
	union _SENDMESSAGE
	{
		MESSAGECONTENT	m_Md5;	// md5�ṹ��
	}u1;
	char PathName[100];			// �洢����
}SOCKETSEND, *PSOCKETSEND;

// ��Ӧ���������������ݰ�
typedef struct _SERVERSTRUCT
{
	HANDLE hWnd;
	SockEnum eEnum;
	INT OpenCode;				// �ɹ�(1)��ʧ��(2)����ֵ
	union _SENDMESSAGE
	{
		MESSAGECONTENT	m_Md5;	// md5�ṹ��
		SOCKETSEND		se;		// ���շ������˷�����Ϣ iii data(SOCKETSEND����)
	}u1;
	char PathName[100];		// �洢����
}SERVERSTRUCT, *PSERVERSTRUCT;