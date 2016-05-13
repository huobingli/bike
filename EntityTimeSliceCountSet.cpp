#include"stdafx.h"
#include<iostream>
#include"EntityTimeSliceCountSet.h"
using namespace std;

CEntityTimeSliceCountNode::CEntityTimeSliceCountNode()
{
    m_pTimeSliceCount = new CEntityTimeSliceCount();
    m_pNextTimeSliceCountNode = NULL;	
}

CEntityTimeSliceCountNode::~CEntityTimeSliceCountNode()
{
	delete m_pTimeSliceCount;
	m_pTimeSliceCount = NULL;
}

CEntityTimeSliceCountNode* CEntityTimeSliceCountNode::getNextTimeSliceCountNode()
{
	return m_pNextTimeSliceCountNode;
}


CEntityTimeSliceCount *CEntityTimeSliceCountNode::getTimeSliceCount(){
    return m_pTimeSliceCount;
}

void CEntityTimeSliceCountNode::setTimeSliceCount(CEntityTimeSliceCount *pTimeSliceCount){
    m_pTimeSliceCount = pTimeSliceCount;
}

void CEntityTimeSliceCountNode::setNextTimeSliceCountNode(CEntityTimeSliceCountNode *pNextTimeSliceCountNode){
    m_pNextTimeSliceCountNode = pNextTimeSliceCountNode;
}

CEntityTimeSliceCountSet::CEntityTimeSliceCountSet()
{
	m_pHeadTimeSliceCountNode = NULL;
	m_iNodeNum = 0;
}
CEntityTimeSliceCountSet::~CEntityTimeSliceCountSet()
{
	if(m_pHeadTimeSliceCountNode!=NULL)
	{
		getLastTimeSliceCountNode(m_pHeadTimeSliceCountNode);
	}
}

bool CEntityTimeSliceCountSet::getLastTimeSliceCountNode(CEntityTimeSliceCountNode* pHeadNode)
{
	if(pHeadNode->getNextTimeSliceCountNode()==NULL)
	{
	}else{
		getLastTimeSliceCountNode(pHeadNode->getNextTimeSliceCountNode());
	}
	delete pHeadNode;
	return true;
}

bool CEntityTimeSliceCountSet::insertTimeSliceCount(CEntityTimeSliceCountNode* pTimeSliceCountNode)
{
	CEntityTimeSliceCountNode *temp = NULL;
	if(m_pHeadTimeSliceCountNode == NULL)
		m_pHeadTimeSliceCountNode = pTimeSliceCountNode;
	else
	{
		temp = m_pHeadTimeSliceCountNode;
		m_pHeadTimeSliceCountNode = pTimeSliceCountNode;
		pTimeSliceCountNode->setNextTimeSliceCountNode(temp);	
	}
	/*if(m_pHeadTimeSliceCountNode == NULL)
	{
		memcpy(m_pHeadTimeSliceCountNode,pTimeSliceCountNode,sizeof(CEntityTimeSliceCountNode));
	}
	else
	{
		temp = m_pHeadTimeSliceCountNode;
		memcpy(temp,pTimeSliceCountNode,sizeof(CEntityTimeSliceCountNode));
		pTimeSliceCountNode->setNextTimeSliceCountNode(temp);
	}*/
	m_iNodeNum++;
	return true;	
}

int CEntityTimeSliceCountSet::getNodeNum()
{
	return m_iNodeNum;
}

CEntityTimeSliceCountNode* CEntityTimeSliceCountSet::getHeadTimeSliceCountNode()
{
	return m_pHeadTimeSliceCountNode;
}


unsigned char* CEntityTimeSliceCountSet::getBinary()
{

    unsigned char *chBinary;
    bool isSuccessed = false;
    int iTotalLength = 8;
    int iDataLength = 8;

    //获取总数据量
    CEntityTimeSliceCountNode* pNode;
    pNode = m_pHeadTimeSliceCountNode;
    while (pNode != NULL){
        iTotalLength += pNode->getTimeSliceCount()->getBinaryLength();
        pNode = pNode->getNextTimeSliceCountNode();
    }
    iTotalLength += 1;
    chBinary = (unsigned char *)malloc (iTotalLength);
    memset (chBinary, '0', iTotalLength);

    //将私有属性转化成二进制类型
    //头部添加总数据量
    isSuccessed = IntegerIntoBinary(iTotalLength, chBinary);
    //链表元素个数转二进制
    isSuccessed = IntegerIntoBinary(m_iNodeNum, chBinary+4);

    //元素 时间片统计对象集合转二进制
    unsigned char *pBuf;
    pNode = m_pHeadTimeSliceCountNode;
    while (pNode != NULL){
        pBuf = pNode->getTimeSliceCount()->getBinary();
        memcpy (chBinary+iDataLength, pBuf, pNode->getTimeSliceCount()->getBinaryLength());
        iDataLength += pNode->getTimeSliceCount()->getBinaryLength();
        pNode = pNode->getNextTimeSliceCountNode();
        //free (pBuf);
        pBuf = NULL;
    }
    
    //末尾添加一个结束字符
    memset (chBinary+iTotalLength-1, '\0', 1);

    if (isSuccessed){
        return chBinary;
    }
    return NULL;
}

int CEntityTimeSliceCountSet::getBinaryLength()
{
    int iTotalLength = 8;

    //获取总数据量
    CEntityTimeSliceCountNode* pNode;
    pNode = m_pHeadTimeSliceCountNode;
    while (pNode != NULL){
        iTotalLength += pNode->getTimeSliceCount()->getBinaryLength();
        pNode = pNode->getNextTimeSliceCountNode();
    }
    iTotalLength += 1;

    return iTotalLength;
}

bool CEntityTimeSliceCountSet::update(const unsigned char *chBuffer){

    int iAllLength = 0;
    int iDataLength = 8;
    unsigned char *pTempInt = (unsigned char *)malloc (4);
    memset (pTempInt, 0, 4);

    //转总数据量
    memcpy (pTempInt, chBuffer, 4);
    iAllLength = BinaryIntoInteger(pTempInt);
    memset (pTempInt, 0, 4);

    //转链表元素个数
    memcpy (pTempInt, chBuffer+4, 4);
    int iNodeNum = BinaryIntoInteger(pTempInt);
    memset (pTempInt, 0, 4);

    /*转站点统计对象数组*/
        int iSectionLength = 0;
        int iTempLength = 8;
        unsigned char *chSectionLength = (unsigned char *)malloc (4);
        memset (chSectionLength, 0, 4);
        unsigned char *pTempBuf;

        if (iNodeNum != 0){
            for (int i=0; i<iNodeNum; i++){
                
                CEntityTimeSliceCountNode *pNode = new CEntityTimeSliceCountNode();
                this->insertTimeSliceCount(pNode);

                //获取段长度
                memset (chSectionLength, 0, 4);
                memcpy (chSectionLength, chBuffer+iTempLength, 4);
                iSectionLength = this->BinaryIntoInteger(chSectionLength);

                pTempBuf = (unsigned char *)malloc (iSectionLength);
                memset (pTempBuf, 0, iSectionLength);
                memcpy (pTempBuf, chBuffer+iTempLength, iSectionLength);

                pNode->getTimeSliceCount()->update(pTempBuf);
                //pNode = pNode->getNextTimeSliceCountNode();
                iTempLength += iSectionLength;
                free (pTempBuf);
                pTempBuf = NULL;
            }
        }

    free (chSectionLength);
    free (pTempInt);
    pTempInt = NULL;
    chSectionLength = NULL;
    return true;
}

/**
说明：将传入的整型变量转成二进制类型
输入：待转整型变量，接收转换后的二进制类型数据的字符串变量(在内部分配内存)
返回值：是否转化成功
更新时间：2015/10/21*/
bool CEntityTimeSliceCountSet::IntegerIntoBinary(const int iNumIn, unsigned char *chBinaryOut){
    long int *iNum = new long int(iNumIn);

    memcpy (chBinaryOut, (unsigned char *)iNum, 1);
    memcpy (chBinaryOut+1, (unsigned char *)iNum+1, 1);
    memcpy (chBinaryOut+2, (unsigned char *)iNum+2, 1);
    memcpy (chBinaryOut+3, (unsigned char *)iNum+3, 1);

    delete iNum;
    iNum = NULL;
    if (chBinaryOut != 0){
        return true;
    }
    return false;
}

/**
说明：将传入的二进制类型转成整型变量
输入：二进制类型数据的字符串变量(在内部分配内存)
返回值：转化成功的整型变量 
更新时间：2015/10/21*/
int CEntityTimeSliceCountSet::BinaryIntoInteger(const unsigned char *chBinaryIn){
    int iNum = 0;
    long int *iNumNew = new long int();

    memcpy ((unsigned char *)iNumNew, chBinaryIn, 4);
    iNum = *iNumNew;

    delete iNumNew;
    return iNum;
}

char* CEntityTimeSliceCountSet::changeToChar()
{
	int charLength;
	char* cTimeSliceCountSet = new char();
	char* cLeft = "(";
	char* cRight = ")";
	CEntityTimeSliceCountNode* temp =m_pHeadTimeSliceCountNode;

	/*将时间片统计记录拼接到时间片统计链表字符串中*/
	/*如果时间片统计链表为空，就返回()*/
	if(m_iNodeNum==0)
	{
		strcat(cTimeSliceCountSet,cLeft);
		strcat(cTimeSliceCountSet,cRight);
	}
	else
	{
		while(temp!=NULL)
		{
			strcat(cTimeSliceCountSet,temp->getTimeSliceCount()->changeToChar());
			charLength = strlen(cTimeSliceCountSet);
			cout<<charLength<<endl;
			temp = temp->getNextTimeSliceCountNode();
		}
	}

	return cTimeSliceCountSet;
}

string CEntityTimeSliceCountSet::changeToStringstream()
{
	stringstream strstreamTimeSliceCountSet;
	char* cLeft = "(";
	char* cRight = ")";	
	CEntityTimeSliceCountNode* temp =m_pHeadTimeSliceCountNode;
	/*将时间片统计记录放入统计链表字符串中*/
	/*如果时间片统计链表为空，就返回()*/
	if(m_iNodeNum==0)
	{
		strstreamTimeSliceCountSet<<cLeft;
		strstreamTimeSliceCountSet>>cRight;
	}
	else
	{
		while(temp!=NULL)
		{
			strstreamTimeSliceCountSet<<temp->getTimeSliceCount()->changeToStringstream();
			temp = temp->getNextTimeSliceCountNode();
		}
	}
	string strTimeSliceCountSet(strstreamTimeSliceCountSet.str());
	return strTimeSliceCountSet;
}