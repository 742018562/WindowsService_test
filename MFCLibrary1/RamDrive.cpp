// RamDrive.cpp: implementation of the QRamDrive class.
//
//////////////////////////////////////////////////////////////////////
#include "pch.h"
#include "ramdrive.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
QRamDrive::QRamDrive()
{

	int isize;
	isize = sizeof(StructDrive);
	drive = NULL;
	bRam = false;
	lpMapAddress = NULL;
	hMapFile = NULL;

}

QRamDrive::~QRamDrive()
{

	if (lpMapAddress)  UnmapViewOfFile(lpMapAddress);
	if (hMapFile) CloseHandle(hMapFile);

}

//��ָ���ı�Ŵ��������ڴ���
bool QRamDrive::CreateRam(int ramid)
{
	char chRamName[30];
	sprintf_s(chRamName, "RAM%03d", ramid);
	CString strRam;
	strRam.Format(_T("RAM%03d"), ramid);

	if (lpMapAddress)  UnmapViewOfFile(lpMapAddress);
	if (hMapFile) CloseHandle(hMapFile);

	HANDLE hFile = (HANDLE)0xFFFFFFFF;

	hMapFile = CreateFileMapping(hFile, NULL, PAGE_READWRITE, 0, SHM_SIZE, strRam);
	if (hMapFile == NULL) {
		//TRACE( _T("���������ڴ����\r\n") );
		char chMsg[100];
		strcpy_s(chMsg, "�����ڴ���������������Ӧ����ϵ");
		::MessageBox(NULL, (LPCTSTR)chMsg, NULL, MB_OK);
		lpMapAddress = NULL;
		bRam = false;
		return false;
	}
	lpMapAddress = MapViewOfFile(hMapFile, FILE_MAP_ALL_ACCESS, 0, 0, 0);
	drive = (StructDrive *)lpMapAddress;

	bRam = true;
	drive->iVersion = 1;
	iRamid = ramid;
	return true;
}

// ���������������
// char * chCmd ���͵����
void QRamDrive::SetCmd(char * chCmd)
{
	strcpy_s(drive->chGetCmd, chCmd);
	drive->chExistGetCmd = 1;
}

//ȡ�����ڴ��������
//char * chCmd ��ȡ�������ݵĻ�����
void QRamDrive::GetCmd(char * chCmd)
{
	strcpy_s(chCmd, 200, drive->chGetCmd);
	drive->chExistGetCmd = 0;
}

//�����ϴ��Ľṹ����
//int iNum  �ṹ�������   char * chMsg  �ṹ��������
void QRamDrive::SetStruct(int iNum, char * chMsg)
{
	if (drive == NULL) return;
	strcpy_s(drive->chStruct[iNum], chMsg);
}

//��������������������ΪEXIT
void QRamDrive::SetExit()
{
	strcpy_s(drive->chGetCmd, "EXIT");
	drive->chExistGetCmd = 1;
}


/*
ʹ�÷���

QRamDrive  ram  ;		//���������ڴ������
ram.CreateRam( 0 );		//����0�Ź����ڴ�
ram.SetValue( 1, 100 ) ;	//��1��ʵʱ������ֵ100

int iValue ;
iValue = ram.GetValue( 1 ) ;  //ȡ1��ʵʱ����,  ӦΪ100

ram.SetCmd(  "control 1 1 " ) ;����������������

char chCmd[200];
if( ram.GetExistCmd(  ) )	//�����������
	ram.GetCmd( chCmd );	//ȡ���������뻺����

ram.SetStruct( 0, "soe 2006 5 15 08 09  30  6 0  1 " );// ����0�����нṹ����
ram.SetStructNum( 1 );  //�������нṹ������ĿΪ1 , ��λ������ݴ�1ȡ��

*/
