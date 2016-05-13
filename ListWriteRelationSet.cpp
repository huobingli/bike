#include"stdafx.h"
#include "ListWriteRelationSet.h"

CListWriteRelationNode::CListWriteRelationNode(){
    m_pNextRelationNode = NULL;
    m_pEntityRelationSet = new CEntityRelationSet();
}

CListWriteRelationNode::~CListWriteRelationNode(){
	delete m_pEntityRelationSet;
	m_pNextRelationNode = NULL;
}

/**
˵����������һ���ڵ�
��������һ���ڵ�ָ��
������:��*/
void CListWriteRelationNode::setNextRelationNode(CListWriteRelationNode *pListWriteRelationNode){
    m_pNextRelationNode = pListWriteRelationNode;
}

/**
˵�����õ���һ���ڵ�
����ֵ����һ���ڵ�
�����ߣ���*/
CListWriteRelationNode *CListWriteRelationNode::getNextRelationNode(){
    return m_pNextRelationNode;
}

/**
˵�����õ���ǰ�ڵ��ϵ����
����ֵ���ڵ��ϵ����ָ��
�����ߣ���*/
CEntityRelationSet *CListWriteRelationNode::getEntityRelationSet(){
    return m_pEntityRelationSet;
}

/**
˵�������õ�ǰ�ڵ��ϵ����
�������ڵ��ϵ����
�����ߣ���*/
void CListWriteRelationNode::setEntityRelationSet(CEntityRelationSet *pEntityRelationSet){
    int iStationNum = pEntityRelationSet->getStationNum();//�õ�վ�����
    //m_pEntityRelationSet->setTimeID(pEntityRelationSet->getTimeID());//����ʱ��ID
    //m_pEntityRelationSet->setStationNum(iStationNum);//����վ�����
    //m_pEntityRelationSet->initRelationSet();//��ʼ������

    for(int iCount = 0; iCount < iStationNum; iCount++){
        for(int jCount = 0; jCount < iStationNum; jCount++){
			m_pEntityRelationSet->insertStationRelation(iCount, jCount, pEntityRelationSet->getStationRelation(iCount, jCount));
        }
    }
}

CListWriteRelationSet::CListWriteRelationSet(){
    m_pFirstListRelationNode = NULL;     //next�ڵ��ʼ��
    m_iNodeNum = 0;                      //����ڵ������ʼ��Ϊ0
}

/**
˵��������ר��
��������ϵ����
�����ߣ���
����ʱ�䣺2015.10.23*/
//CListWriteRelationSet::CListWriteRelationSet(CEntityRelationSet *pEntityRelationSet){
//    m_pFirstListRelationNode = new CListWriteRelationNode();
//    m_iNodeNum = 1;
//    CListWriteRelationNode *pListWriteRelationNode = new CListWriteRelationNode();
//}

CListWriteRelationSet::~CListWriteRelationSet(){
	//while(m_iNodeNum--)
	//{
	//	CListWriteRelationNode *tempReleaseNode = m_pFirstListRelationNode;
	//	m_pFirstListRelationNode = tempReleaseNode->getNextRelationNode();
	//	//_CrtDumpMemoryLeaks();
	//	delete tempReleaseNode;
	//	//_CrtDumpMemoryLeaks();
	//}
	getLastTimeSliceCountNode(m_pFirstListRelationNode);
}

/**
˵��������������ͱ���ת�ɶ���������
���룺��ת���ͱ���������ת����Ķ������������ݵ��ַ�������
����ֵ���Ƿ�ת���ɹ�
�����ߣ���
����ʱ�䣺2015/10/21*/
bool CListWriteRelationSet::IntegerIntoBinary(const int iNumIn, unsigned char *chBinaryOut){
    long int *iNum = new long int(iNumIn);

    memcpy (chBinaryOut, (unsigned char *)iNum, 1);
    memcpy (chBinaryOut+1, (unsigned char *)iNum+1, 1);
    memcpy (chBinaryOut+2, (unsigned char *)iNum+2, 1);
    memcpy (chBinaryOut+3, (unsigned char *)iNum+3, 1);

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
int CListWriteRelationSet::BinaryIntoInteger(const unsigned char *chBinaryIn){
    int iNum = 0;
    long int *iNumNew = new long int();

    memcpy ((unsigned char *)iNumNew, chBinaryIn, 4);
    iNum = *iNumNew;

    delete iNumNew;
    return iNum;
}

/**
˵����������β������һ����ϵ���Ͻڵ㣨β����룩
����������ڵ�
����ֵ���Ƿ����ɹ�
�����ߣ���*/
bool CListWriteRelationSet::insertRelationSet(CListWriteRelationNode *pListWriteRelationNode){
    if(m_pFirstListRelationNode == NULL){
        m_pFirstListRelationNode = pListWriteRelationNode;
    }else{
        CListWriteRelationNode *tempListWriteRelationNode = m_pFirstListRelationNode;
        m_pFirstListRelationNode = pListWriteRelationNode;
        pListWriteRelationNode->setNextRelationNode(tempListWriteRelationNode);

    }
    m_iNodeNum++;
    return true;	
}

/**
˵������ȡ�ڵ���Ŀ
����ֵ���ڵ���Ŀ
�����ߣ���*/
int CListWriteRelationSet::getNodeNum(){
	return m_iNodeNum;
}

/**
˵������ȡͷ���
����ֵ��ͷ���
�����ߣ���*/
CListWriteRelationNode *CListWriteRelationSet::getListWriteRelationHeadNode(){
    return m_pFirstListRelationNode;
}

/**
���ƣ�getBinary
˵������ȡ������ת�ɵĶ���������
����ֵ�����������ݼ���
�����ߣ���
����ʱ�䣺2015/10/9*/
unsigned char *CListWriteRelationSet::getBinary(){
        
    bool isSuccessed = false;
    int iTotalNum = 13;
    int iDataLength = 8;
    unsigned char *chTempNum = NULL;
    unsigned char *chBinary = NULL;
	unsigned char *chTempBinary = NULL;
    CListWriteRelationNode *pTempNode;

    pTempNode = m_pFirstListRelationNode;
    for (int i=0; i<m_iNodeNum; i++){
        iTotalNum += pTempNode->getEntityRelationSet()->getBinaryLength();
        pTempNode = pTempNode->getNextRelationNode();
    }
    chBinary = (unsigned char *)malloc (iTotalNum);
    chTempNum = (unsigned char *)malloc (4);
    memset (chBinary, 0, iTotalNum);
    memset (chTempNum, 0, 4);

    //��������ת������
    isSuccessed = this->IntegerIntoBinary(iTotalNum, chTempNum);
    memcpy (chBinary, chTempNum, 4);
    memset (chTempNum, 0, 4);

    //�ڵ����ת������
    isSuccessed = this->IntegerIntoBinary(m_iNodeNum, chTempNum);
    memcpy (chBinary+4, chTempNum, 4);
    memset (chTempNum, 0, 4);

    //���ڵ�ת������
    pTempNode = m_pFirstListRelationNode;
    for (int i=0; i<m_iNodeNum; i++){
        chTempBinary = pTempNode->getEntityRelationSet()->getBinary();
        memcpy (chBinary+iDataLength, chTempBinary, pTempNode->getEntityRelationSet()->getBinaryLength());
        iDataLength += pTempNode->getEntityRelationSet()->getBinaryLength();
        pTempNode = pTempNode->getNextRelationNode();
		free (chTempBinary);
		chTempBinary = NULL;
    }

    //���ĩβУ���
    memset (chBinary+iTotalNum-1, '\0', 1);

    free (chTempNum);
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
int CListWriteRelationSet::getBinaryLength(){
    int iTotalNum = 13;
    CListWriteRelationNode *pTempNode;

    pTempNode = m_pFirstListRelationNode;
    for (int i=0; i<m_iNodeNum; i++){
        iTotalNum += pTempNode->getEntityRelationSet()->getBinaryLength();
        pTempNode = pTempNode->getNextRelationNode();
    }

    return iTotalNum;
}

/**
���ƣ�update
˵�������¶���������
����������������Ϣ�Ķ���������
����ֵ��bool�ͣ���ʾ�����Ƿ�ɹ�
�����ߣ���
����ʱ��:2015/10/25*/
bool CListWriteRelationSet::update(const unsigned char* chBuffer){
    int iAllLength = 0;
    unsigned char *pTempInt = (unsigned char *)malloc (4);
    memset (pTempInt, 0, 4);

    //ת��������
    memcpy (pTempInt, chBuffer, 4);
    iAllLength = BinaryIntoInteger(pTempInt);
    memset (pTempInt, 0, 4);

    //ת����Ԫ�ظ���
    memcpy (pTempInt, chBuffer+4, 4);
    int iNodeNum = BinaryIntoInteger(pTempInt);
    memset (pTempInt, 0, 4);

    /*ת���ʱ��Ƭ*/
    int iSectionLength = 0;
    int iTempLength = 8;
    unsigned char *chSectionLength = (unsigned char *)malloc (4);
    memset (chSectionLength, 0, 4);
    unsigned char *pTempBuf;

    if (iNodeNum != 0){
        CListWriteRelationNode *pNode;
        for (int i=0; i<iNodeNum; i++){

          /*  if (i == 0){
                pNode = m_pFirstListRelationNode = new CListWriteRelationNode();
            }else{
                pNode = new CListWriteRelationNode();
            }*/

			CListWriteRelationNode *pNode = new CListWriteRelationNode();
			this->insertRelationSet(pNode);
            //��ȡ�γ���
            memset (chSectionLength, 0, 4);
            memcpy (chSectionLength, chBuffer+iTempLength, 4);
            iSectionLength = this->BinaryIntoInteger(chSectionLength);

            pTempBuf = (unsigned char *)malloc (iSectionLength);
            memset (pTempBuf, 0, iSectionLength);
            memcpy (pTempBuf, chBuffer+iTempLength, iSectionLength);

            pNode->getEntityRelationSet()->update(pTempBuf);
            //pNode = pNode->getNextRelationNode();
            iTempLength += iSectionLength;
            free (pTempBuf);
            pTempBuf = NULL;
        }
    }

    free (chSectionLength);
    free (pTempInt);
    pTempInt = NULL;
    return true;
}

void CListWriteRelationSet::getLastTimeSliceCountNode(CListWriteRelationNode * pHeadNode)
{
	
	if(pHeadNode->getNextRelationNode()==NULL)
	{
		
	}else{
		getLastTimeSliceCountNode(pHeadNode->getNextRelationNode());
	}
	delete pHeadNode;
}

