#include "ProgramStart.h"
#include "MasterWindows.h"

ProgramStatic g_WinApp;		// ����Ӧ�ó���

ProgramStatic::ProgramStatic()
{

}

ProgramStatic::~ProgramStatic()
{

}

BOOL ProgramStatic::InitInstance()
{
	// MasterWindows* obj_master = NULL;
	MasterWindows obj_master;
	m_pMainWnd = &obj_master;
	obj_master.DoModal();
	return TRUE;
}

