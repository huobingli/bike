#include"stdafx.h"
#include "EntityRelationSet.h"

CEntityRelationSet::CEntityRelationSet(){
	m_iStationNum = 0;
	m_iTimeID = 0;
	m_RelationSet = NULL;
}

/**
˵���������ϵ���ݼ���ʵ�壬���첢��ʼ����ά��������Ź�ϵ����
������վ�����
�����ߣ���*/
CEntityRelationSet::CEntityRelationSet(int iStationNum, int iTimeID){
	m_iStationNum = iStationNum;
	m_iTimeID = iTimeID;
	this->initRelationSet();
}

CEntityRelationSet::~CEntityRelationSet(void){

	//ɾ���ڶ�ά
	for (int iCount = 0; iCount < m_iStationNum; iCount++){
		delete[] m_RelationSet[iCount];
		m_RelationSet[iCount] = NULL;
	}
	delete[] m_RelationSet;
	m_RelationSet = NULL;
}

/**
˵��������վ�����
������վ�����
�����ߣ���*/
void CEntityRelationSet::setStationNum(int iStationNum){
	m_iStationNum = iStationNum;
}

/**
˵�����õ�վ�����
����ֵ��վ�����
�����ߣ���*/
int CEntityRelationSet::getStationNum(){
	return m_iStationNum;
}

/**
˵������ʼ����ϵ��ά���飬�Խ���Ϊ1������������
�����ߣ���*/
void CEntityRelationSet::initRelationSet(){
	//������ά��ϵ���ݼ�������
	//��ʼ����һά
	m_RelationSet = new double*[m_iStationNum];
	//��ʼ���ڶ�ά
	for (int iCount = 0; iCount < m_iStationNum; iCount++){
		m_RelationSet[iCount] = new double[m_iStationNum];
	}

	//��ʼ����ά����
	for (int iCount = 0; iCount < m_iStationNum; iCount++){
		for (int jCount = 0; jCount < m_iStationNum; jCount++)
		{
			//��ͬվ����1����ͬվ����0
			if (iCount == jCount)
				m_RelationSet[iCount][jCount] = 100;
			else
				m_RelationSet[iCount][jCount] = 0;
		}
	}

	/*m_RelationSet = new CEntityRelation[m_iStationNum];

	for(int iCount = 0; iCount < m_iStationNum; iCount++)
	{
	m_RelationSet[iCount].setTargetStationID(0);
	m_RelationSet[iCount].setRelationStationID(0);
	m_RelationSet[iCount].setStationRelation(0);
	}*/
}

/**
˵�����������ݹ�ϵ����
��������ʼվ���ϵ��Ŀ��վ���ϵ��վ�����ֵ
����ֵ���Ƿ����ɹ�
�����ߣ���*/
void CEntityRelationSet::insertStationRelation(int iTargetStationID, int iRelationStationID, double iStationRelation){
	m_RelationSet[iTargetStationID][iRelationStationID] = iStationRelation;
}

/**
˵�����������ݹ�ϵ����
��������ʼվ���ϵ��Ŀ��վ���ϵ��վ�����ֵ
����ֵ���Ƿ����ɹ�
�����ߣ���*/
void CEntityRelationSet::insertRelationSet(int iTargetStationID, int iRelationStationID, double iStationRelation){
	m_RelationSet[iTargetStationID][iRelationStationID] = iStationRelation;
}

/**
˵����ĳ��ʱ��Ƭ�еõ�����վ���ϵ
������Ŀ��վ�㣬����վ��
����ֵ��վ���ϵ
�����ߣ���*/
double CEntityRelationSet::getStationRelation(int iTargetStationID, int iRelationStationID){
	return m_RelationSet[iTargetStationID][iRelationStationID];
}

/**
˵�����õ�վ�����
����ֵ��վ�����
�����ߣ���*/
int CEntityRelationSet::getEntityNum(){
	return m_iStationNum;
}


/**
˵�����õ�����ʱ��ƬID
����ֵ��ʱ��ƬID
�����ߣ���*/
int CEntityRelationSet::getTimeID(){
	return m_iTimeID;
}

/**
˵�������ü���ʱ��ƬID
���룺ʱ��ƬID
�����ߣ���*/
void CEntityRelationSet::setTimeID(int iTimeID){
	m_iTimeID = iTimeID;
}

/********************************************************************************************
���ƣ�getBinary
˵������ȡ������ת�ɵĶ���������
����ֵ�����������ݼ���
�����ߣ���
����ʱ�䣺2015/10/10*/
unsigned char *CEntityRelationSet::getBinary(){

	bool isSuccessed = false;
	int iTotalNum = 0;
	unsigned char *chTempNum = NULL;
	unsigned char *chBinary = NULL;
	iTotalNum = 4 + 4 + 4 + 1 + m_iStationNum * m_iStationNum * 4;
	chBinary = (unsigned char *)malloc(iTotalNum);
	chTempNum = (unsigned char *)malloc(4);
	memset(chBinary, 0, iTotalNum);
	memset(chTempNum, 0, 4);

	//��������ת������
	isSuccessed = this->IntegerIntoBinary(iTotalNum, chTempNum);
	memcpy(chBinary, chTempNum, 4);
	memset(chTempNum, 0, 4);

	//ʱ��ƬIDת������
	isSuccessed = this->IntegerIntoBinary(m_iTimeID, chTempNum);
	memcpy(chBinary + 4, chTempNum, 4);
	memset(chTempNum, 0, 4);

	//վ�����ת������
	isSuccessed = this->IntegerIntoBinary(m_iStationNum, chTempNum);
	memcpy(chBinary + 8, chTempNum, 4);
	memset(chTempNum, 0, 4);

	//��ϵ����ת������
	for (int i = 0; i<m_iStationNum; i++){
		for (int j = 0; j<m_iStationNum; j++){
			isSuccessed = this->IntegerIntoBinary(m_RelationSet[i][j], chTempNum);
			memcpy(chBinary + 12 + (m_iStationNum*i + j) * 4, chTempNum, 4);
			memset(chTempNum, 0, 4);
		}

	}

	for (int i = 0; i<m_iStationNum; i++){
		for (int j = 0; j<m_iStationNum; j++){
			memcpy(chTempNum, chBinary + 12 + (m_iStationNum*i + j) * 4, 4);
			isSuccessed = this->IntegerIntoBinary(m_RelationSet[i][j], chTempNum);
			memset(chTempNum, 0, 4);
		}

	}

	//memcpy (chBinary+12, this->m_RelationSet, m_iStationNum*m_iStationNum*4);

	//���ĩβУ���
	memset(chBinary + iTotalNum - 1, '\0', 1);

	free(chTempNum);
	chTempNum = NULL;
	if (isSuccessed){
		return chBinary;
	}
	return NULL;
}

/**
���ƣ�getBinaryLength
˵������ȡ������ת�ɵĶ��������ݵĳ���
����ֵ�����������ݳ���
�����ߣ���
����ʱ�䣺2015/10/9*/
int CEntityRelationSet::getBinaryLength(){
	if (m_iTimeID == 0){
		return 4 + 4 + 4 + 1;
	}
	return 4 + 4 + 4 + 1 + m_iStationNum * m_iStationNum * 4;
}

/**
���ƣ�update
˵����ʹ���ֽ����ݸ���
���������¶���������
����ֵ���Ƿ���³ɹ�
�����ߣ���
����ʱ�䣺2015/10/9*/
bool CEntityRelationSet::update(const unsigned char *chBuffer){

	if (chBuffer == NULL){
		return false;
	}

	int iAllLength = 0;
	unsigned char *pTempInt = (unsigned char *)malloc(4);
	memset(pTempInt, 0, 4);

	//ת��������
	memcpy(pTempInt, chBuffer, 4);
	iAllLength = BinaryIntoInteger(pTempInt);
	memset(pTempInt, 0, 4);

	//תʱ��ƬID
	memcpy(pTempInt, chBuffer + 4, 4);
	m_iTimeID = BinaryIntoInteger(pTempInt);
	memset(pTempInt, 0, 4);

	//תʱ��Ƭ��վ�����
	memcpy(pTempInt, chBuffer + 8, 4);
	m_iStationNum = BinaryIntoInteger(pTempInt);
	memset(pTempInt, 0, 4);

	//��ʼ����ά��ϵ����
	if (m_iStationNum != 0){
		this->initRelationSet();

		//memcpy (m_RelationSet, chBuffer+12, m_iStationNum*m_iStationNum*4);

		//ת��������
		for (int i = 0; i<m_iStationNum; i++){
			for (int j = 0; j<m_iStationNum; j++){
				memcpy(pTempInt, chBuffer + 12 + (m_iStationNum*i + j) * 4, 4);
				m_RelationSet[i][j] = this->BinaryIntoInteger(pTempInt);
				memset(pTempInt, 0, 4);
			}
		}
	}

	free(pTempInt);
	return true;
}

/**
˵��������������ͱ���ת�ɶ���������
���룺��ת���ͱ���������ת����Ķ������������ݵ��ַ�������(���ڲ������ڴ�)
����ֵ���Ƿ�ת���ɹ�
�����ߣ���
����ʱ�䣺2015/10/21*/
bool CEntityRelationSet::IntegerIntoBinary(const int iNumIn, unsigned char *chBinaryOut){
	long int *iNum = new long int(iNumIn);

	memcpy(chBinaryOut, (unsigned char *)iNum, 1);
	memcpy(chBinaryOut + 1, (unsigned char *)iNum + 1, 1);
	memcpy(chBinaryOut + 2, (unsigned char *)iNum + 2, 1);
	memcpy(chBinaryOut + 3, (unsigned char *)iNum + 3, 1);

	delete iNum;
	iNum = NULL;
	if (chBinaryOut != 0){
		return true;
	}
	return false;
}

/**
˵����������Ķ���������ת�����ͱ���
���룺�������������ݵ��ַ�������(���ڲ������ڴ�)
����ֵ��ת���ɹ������ͱ���
�����ߣ���
����ʱ�䣺2015/10/21*/
int CEntityRelationSet::BinaryIntoInteger(const unsigned char *chBinaryIn){
	int iNum = 0;
	long int *iNumNew = new long int();

	memcpy((unsigned char *)iNumNew, chBinaryIn, 4);
	iNum = *iNumNew;

	delete iNumNew;
	iNumNew = NULL;
	return iNum;
}