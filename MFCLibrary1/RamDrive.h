// RamDrive.h: interface for the QRamDrive class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(RAMDRIVE_H)
#define RAMDRIVE_H

//��д��:������  ����:2004-11-8
//����: ��������ʵʱ���ݵĲɼ�������ʵʱ���ݿ�֮��Ľ���

//�����ڴ�����ĸ���Ŀ
//1. ����������
//2. ʵʱ������
//3. �ṹ������

#include <stdio.h>

#define		MAX_DATA_SIZE			2000	//ʵʱ�������Ļ����С����
#define		MAX_STRUCT_NUM			25		//���нṹ�����Ļ����С����
#define		MAX_STRUCT_NUM_DOWN		20		//���нṹ�����Ļ����С����

#define  SHM_SIZE   25000					//�����ڴ����Ĵ�С

//size 21224
struct StructDrive
{
	int iVersion;					//�������İ汾
	char  chExistGetCmd;			//�Ƿ�����´�����  0 ������  1 ����
	char  chGetCmd[200];			//���������
	int     iValue[MAX_DATA_SIZE];		//ʵʱ������
	int iStructNum;			//�ϴ��ı��ṹ���ݸ���  ��û��ʱΪ0 ������ʱΪ�������Ŀ
	char chStruct[MAX_STRUCT_NUM][200];  //�ϴ��ı��ṹ����

	int iStructNumDown;		//�´��ı��ṹ���ݸ���  ��û��ʱΪ0 ������ʱΪ�������Ŀ
	char chStructDown[MAX_STRUCT_NUM_DOWN][200];  //�´��ı��ṹ����
};

class QRamDrive
{
public:
	QRamDrive();
	virtual ~QRamDrive();

	bool CreateRam(int ramid);
	bool bRam;
	int iRamid;


	HANDLE hMapFile;
	LPVOID  lpMapAddress;

	StructDrive    * drive;
	void SetExit();   //send exit cmd
	void SetCmd(char * chCmd);
	void GetCmd(char * chCmd);
	bool GetExistCmd() {			//�ж��������Ƿ��������
		if (drive == NULL)
			return false;
		else
			return   (drive->chExistGetCmd != 0);
	}

	void SetValue(int id, int iValue) {	//����������ֵ
		if (drive == NULL) return;
		drive->iValue[id] = iValue;
	}
	int GetValue(int id) {					//ȡ������ֵ
		if (drive == NULL) return 0;
		return  drive->iValue[id];
	}

	void SetStructNum(int iStructNum) { //�������нṹ��������
		if (drive == NULL) return;
		drive->iStructNum = iStructNum;
	}

	int GetStructNum() {	//ȡ���нṹ��������
		if (drive == NULL) return 0;
		return drive->iStructNum;
	}

	void SetStruct(int iNum, char * chMsg);// �������нṹ����

	char * GetStruct(int iNum) { return *(drive->chStruct + iNum); }//ȡ���нṹ����

	int GetStructNumDown() { return drive->iStructNumDown; }//ȡ���нṹ��������
	void SetStructNumDown(int iNum) { drive->iStructNumDown = iNum; }//�������нṹ��������

	char * GetStructDown(int iNum) { return *(drive->chStructDown + iNum); }	//ȡ���нṹ����
	void SetStructDown(int iNum, char * chMsgDown)	//�������нṹ����
	{
		strcpy_s(*(drive->chStructDown + iNum), chMsgDown);
	}

	void ClearCmdMark() {		//��������־
		if (drive == NULL)
			return;
		else
			drive->chExistGetCmd = 0;
	}

	char * GetCmdWithoutClearMark() { return drive->chGetCmd; }

};
#endif //
