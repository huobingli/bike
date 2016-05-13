#include "StdAfx.h"

#include"EntityTripData.h"

/**
�����ߣ�Ҧ*/
CEntityTripData::CEntityTripData(){
	m_iStartStationTime = 1501010000;    //Ĭ��ʱ��Ϊ1501010000��2015��1��1��0��0��
	m_iStopStationTime = 1501010000;
	m_iStartStationID = -1;
	m_iStopStationID = -1;
	m_iCostTime = 0;                     //Ĭ�ϳ�ʼ����ʱ��Ϊ0s
}

/**
˵�������½軹����
�����������軹������ַ���
����ֵ���Ƿ���³ɹ�
�����ߣ���*/
bool CEntityTripData::update(string csStationData){
	/*��֤�ַ�����Ч��*/
	if (csStationData == ""){
		return false;
	}

	/*�ų�������Ϣģ��*/
	string strResult;                         //������ʱ�ָ��������ϢƬ��
	/*���ַָ�����*/
	int iLast = 0;
	int iIndex = 0;

	/*�ų�������Ϣģ��*/
	iIndex = csStationData.find_first_of(',', iLast);
	strResult = csStationData.substr(iLast, iIndex - iLast);
	if (atoi(strResult.c_str()) == 0){
		return false;
	}
	translateRecordData(csStationData);  //��Ч��Ϣ�ַ�������ת������
	return true;
}

/**
˵�������ַ�������¼���Էָ�
��ڲ�����������Ч�ļ�¼��Ϣ�ַ���
����ֵ���Ƿ���³ɹ�
�����ߣ���
����ʱ�䣺2015/10/13*/
bool CEntityTripData::translateRecordData(string csRecordData){
	/*��������ģ��*/
	string strTemp = csRecordData;
	string strResult;//������ʱ�ָ��������ϢƬ��
	int iFalge = 0;//��Ϣ��λ��־
	/*���ַָ�����*/
	int iLast = 0;
	int iIndex = 0;

	/*�ָ��ַ���ģ��*/
	iIndex = strTemp.find_first_of(',', iLast);
	iFalge++;
	while (iIndex != std::string::npos){
		strResult = strTemp.substr(iLast, iIndex - iLast);
		iLast = iIndex + 1;

		/*��string����ת��ģ��*/
		if (iFalge == 3){ setStartStationTime(strResult); }
		else if (iFalge == 7){ setStopStationTime(strResult); }
		//else if (iFalge == 11){setCostTime(strResult);}
		else if (iFalge == 4){ setStartStationID(strResult); }
		else if (iFalge == 8){ setStopStationID(strResult); }

		iIndex = strTemp.find_first_of(',', iLast);
		iFalge++;
	}
	iIndex = strTemp.find_first_of(',', iLast);
	strResult = strTemp.substr(iLast, iIndex - iLast);
	if (iFalge == 11){ setCostTime(strResult); }
	return true;
}

void CEntityTripData::setStartStationTime(string strStartStationTime){
	/*��������ģ��*/
	string strTemp = strStartStationTime;
	string strResult;//������ʱ�ָ��������ϢƬ��
	string strTime;   //��ȡ����Чʱ��
	char *chTemp = (char *)malloc(3);
	memset(chTemp, 0, 2);
	int iFalge = 0;//��Ϣ��λ��־
	/*���ַָ�����*/
	int iLast = 0;
	int iIndex = 0;

	/*��ȡ����·�ģ��*/
	iIndex = strTemp.find_first_of('/', iLast);
	iFalge++;
	while (iIndex != std::string::npos){
		strResult = strTemp.substr(iLast, iIndex - iLast);
		iLast = iIndex + 1;

		/*��string����ת��ģ��*/
		if (iFalge == 1){
			strncpy(chTemp, strResult.c_str() + 2, 2);
			chTemp[2] = '\0';
			strResult = chTemp;
			strTime += strResult;
		}
		else if (iFalge == 2 || iFalge == 3){
			if (strlen(strResult.c_str()) == 1){
				strTime += '0';
				strTime += strResult;
			}
			else{
				strTime += strResult;
			}
		}

		iIndex = strTemp.find_first_of('/', iLast);
		iFalge++;
	}

	/*��ȡ����*/
	strTemp = strTemp.substr(iLast, iIndex - iLast);
	iFalge = 0;//��Ϣ��λ��־
	iLast = 0;//�ָ����½�����
	iIndex = 0;

	/*��ȡ����·�ģ��*/
	iIndex = strTemp.find_first_of(' ', iLast);
	iFalge++;
	while (iIndex != std::string::npos){
		strResult = strTemp.substr(iLast, iIndex - iLast);
		iLast = iIndex + 1;

		/*��string����ת��ģ��*/
		if (iFalge == 1){
			if (strlen(strResult.c_str()) == 1){
				strTime += '0';
				strTime += strResult;
			}
			else{
				strTime += strResult;
			}
		}

		iIndex = strTemp.find_first_of('/', iLast);
		iFalge++;
	}

	/*��ȡСʱ*/
	strTemp = strTemp.substr(iLast, iIndex - iLast);
	iFalge = 0;//��Ϣ��λ��־
	iLast = 0;//�ָ����½�����
	iIndex = 0;

	/*��ȡ����·�ģ��*/
	iIndex = strTemp.find_first_of(':', iLast);
	iFalge++;
	while (iIndex != std::string::npos){
		strResult = strTemp.substr(iLast, iIndex - iLast);
		iLast = iIndex + 1;

		/*��string����ת��ģ��*/
		if (iFalge == 1){
			if (strlen(strResult.c_str()) == 1){
				strTime += '0';
				strTime += strResult;
			}
			else{
				strTime += strResult;
			}
		}

		iIndex = strTemp.find_first_of('��', iLast);
		iFalge++;
	}

	/*��ȡ����*/
	strTemp = strTemp.substr(iLast, iIndex - iLast);
	strTime += strTemp;

	m_iStartStationTime = atoi(strTime.c_str());

	free(chTemp);
	chTemp = NULL;
}

void CEntityTripData::setStopStationTime(string strStopStationTime){
	/*��������ģ��*/
	string strTemp = strStopStationTime;
	string strResult;//������ʱ�ָ��������ϢƬ��
	string strTime;   //��ȡ����Чʱ��
	char *chTemp = (char *)malloc(3);
	memset(chTemp, 0, 2);
	int iFalge = 0;//��Ϣ��λ��־
	/*���ַָ�����*/
	int iLast = 0;
	int iIndex = 0;

	/*��ȡ����·�ģ��*/
	iIndex = strTemp.find_first_of('/', iLast);
	iFalge++;
	while (iIndex != std::string::npos){
		strResult = strTemp.substr(iLast, iIndex - iLast);
		iLast = iIndex + 1;

		/*��string����ת��ģ��*/
		if (iFalge == 1){
			strncpy(chTemp, strResult.c_str() + 2, 2);
			chTemp[2] = '\0';
			strResult = chTemp;
			strTime += strResult;
		}
		else if (iFalge == 2 || iFalge == 3){
			if (strlen(strResult.c_str()) == 1){
				strTime += '0';
				strTime += strResult;
			}
			else{
				strTime += strResult;
			}
		}

		iIndex = strTemp.find_first_of('/', iLast);
		iFalge++;
	}

	/*��ȡ����*/
	strTemp = strTemp.substr(iLast, iIndex - iLast);
	iFalge = 0;//��Ϣ��λ��־
	iLast = 0;//�ָ����½�����
	iIndex = 0;

	/*��ȡ����·�ģ��*/
	iIndex = strTemp.find_first_of(' ', iLast);
	iFalge++;
	while (iIndex != std::string::npos){
		strResult = strTemp.substr(iLast, iIndex - iLast);
		iLast = iIndex + 1;

		/*��string����ת��ģ��*/
		if (iFalge == 1){
			if (strlen(strResult.c_str()) == 1){
				strTime += '0';
				strTime += strResult;
			}
			else{
				strTime += strResult;
			}
		}

		iIndex = strTemp.find_first_of('/', iLast);
		iFalge++;
	}

	/*��ȡСʱ*/
	strTemp = strTemp.substr(iLast, iIndex - iLast);
	iFalge = 0;//��Ϣ��λ��־
	iLast = 0;//�ָ����½�����
	iIndex = 0;

	/*��ȡ����·�ģ��*/
	iIndex = strTemp.find_first_of(':', iLast);
	iFalge++;
	while (iIndex != std::string::npos){
		strResult = strTemp.substr(iLast, iIndex - iLast);
		iLast = iIndex + 1;

		/*��string����ת��ģ��*/
		if (iFalge == 1){
			if (strlen(strResult.c_str()) == 1){
				strTime += '0';
				strTime += strResult;
			}
			else{
				strTime += strResult;
			}
		}

		iIndex = strTemp.find_first_of('��', iLast);
		iFalge++;
	}

	/*��ȡ����*/
	strTemp = strTemp.substr(iLast, iIndex - iLast);
	strTime += strTemp;

	m_iStopStationTime = atoi(strTime.c_str());

	free(chTemp);
	chTemp = NULL;
}

void CEntityTripData::setStartStationID(string strStartStationID){

	/*��������ģ��*/
	string strTemp = strStartStationID;
	string strResult;//������ʱ�ָ��������ϢƬ��
	string strTime;   //��ȡ����Чid
	char *chTemp = (char *)malloc(3);
	memset(chTemp, 0, 2);
	int iFalge = 0;//��Ϣ��λ��־
	/*���ַָ�����*/
	int iLast = 0;
	int iIndex = 0;

	/*��ȡ����·�ģ��*/
	iIndex = strTemp.find_first_of('-', iLast);
	iFalge++;
	while (iIndex != std::string::npos){
		strResult = strTemp.substr(iLast, iIndex - iLast);
		iLast = iIndex + 1;

		strTime += strResult;

		iIndex = strTemp.find_first_of('-', iLast);
		//  iFalge ++;
	}

	strResult = strTemp.substr(iLast, iIndex - iLast);
	strTime += strResult;

	m_iStartStationID = atoi(strTime.c_str());
}

void CEntityTripData::setStopStationID(string strStopStationID){
	/*��������ģ��*/
	string strTemp = strStopStationID;
	string strResult;//������ʱ�ָ��������ϢƬ��
	string strTime;   //��ȡ����Чid
	char *chTemp = (char *)malloc(3);
	memset(chTemp, 0, 2);
	int iFalge = 0;//��Ϣ��λ��־
	/*���ַָ�����*/
	int iLast = 0;
	int iIndex = 0;

	/*��ȡ����·�ģ��*/
	iIndex = strTemp.find_first_of('-', iLast);
	iFalge++;
	while (iIndex != std::string::npos){
		strResult = strTemp.substr(iLast, iIndex - iLast);
		iLast = iIndex + 1;

		strTime += strResult;

		iIndex = strTemp.find_first_of('-', iLast);
		//  iFalge ++;
	}

	strResult = strTemp.substr(iLast, iIndex - iLast);
	strTime += strResult;

	m_iStopStationID = atoi(strTime.c_str());
}

void CEntityTripData::setCostTime(string strCostTime){

	/*��������ģ��*/
	string strTemp = strCostTime;
	string strResult;//������ʱ�ָ��������ϢƬ��
	string strTime;   //��ȡ����Чʹ��ʱ��
	int iTime = 0;
	char *chTemp = (char *)malloc(3);
	memset(chTemp, 0, 2);
	int iFalge = 0;//��Ϣ��λ��־
	/*���ַָ�����*/
	int iLast = 0;
	int iIndex = 0;

	/*��ȡ����·�ģ��*/
	iIndex = strTemp.find_first_of("С", iLast);
	iFalge++;
	while (iIndex != std::string::npos){
		strResult = strTemp.substr(iLast, iIndex - iLast);
		iLast = iIndex + 1;

		iTime += 3600 * atoi(strResult.c_str());

		iIndex = strTemp.find_first_of('-', iLast);
	}

	iIndex = strTemp.find_first_of("��", iLast);
	iFalge += 4;
	while (iIndex != std::string::npos){
		strResult = strTemp.substr(iLast + 3, iIndex - 5);
		iLast = iIndex + 1;

		iTime += 60 * atoi(strResult.c_str());

		iIndex = strTemp.find_first_of('-', iLast);
	}

	//strResult = strTemp.substr(iLast,iIndex-iLast);
	//strTime += strResult;

	m_iCostTime = iTime;
}

CEntityTripData::~CEntityTripData(){
}

/**
˵������ȡ����
�����ߣ�Ҧ*/
long int CEntityTripData::getStartStationTime(){
	return m_iStartStationTime;
}

long int CEntityTripData::getStopStationTime(){
	return m_iStopStationTime;
}

int CEntityTripData::getStartStationID(){
	return m_iStartStationID;
}

int CEntityTripData::getStopStationID(){
	return m_iStopStationID;
}

int CEntityTripData::getCostTime(){
	return m_iCostTime;
}
