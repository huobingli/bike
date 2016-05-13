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
说明：设置下一个节点
参数：下一个节点指针
创建者:霍*/
void CListWriteRelationNode::setNextRelationNode(CListWriteRelationNode *pListWriteRelationNode){
    m_pNextRelationNode = pListWriteRelationNode;
}

/**
说明：得到下一个节点
返回值：下一个节点
创建者：霍*/
CListWriteRelationNode *CListWriteRelationNode::getNextRelationNode(){
    return m_pNextRelationNode;
}

/**
说明：得到当前节点关系集合
返回值：节点关系集合指针
创建者：霍*/
CEntityRelationSet *CListWriteRelationNode::getEntityRelationSet(){
    return m_pEntityRelationSet;
}

/**
说明：设置当前节点关系集合
参数：节点关系集合
创建者：霍*/
void CListWriteRelationNode::setEntityRelationSet(CEntityRelationSet *pEntityRelationSet){
    int iStationNum = pEntityRelationSet->getStationNum();//得到站点个数
    //m_pEntityRelationSet->setTimeID(pEntityRelationSet->getTimeID());//设置时间ID
    //m_pEntityRelationSet->setStationNum(iStationNum);//设置站点个数
    //m_pEntityRelationSet->initRelationSet();//初始化数组

    for(int iCount = 0; iCount < iStationNum; iCount++){
        for(int jCount = 0; jCount < iStationNum; jCount++){
			m_pEntityRelationSet->insertStationRelation(iCount, jCount, pEntityRelationSet->getStationRelation(iCount, jCount));
        }
    }
}

CListWriteRelationSet::CListWriteRelationSet(){
    m_pFirstListRelationNode = NULL;     //next节点初始化
    m_iNodeNum = 0;                      //链表节点个数初始化为0
}

/**
说明：测试专用
参数：关系对象
创建者：蔡
更新时间：2015.10.23*/
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
说明：将传入的整型变量转成二进制类型
输入：待转整型变量，接收转换后的二进制类型数据的字符串变量
返回值：是否转化成功
创建者：蔡
更新时间：2015/10/21*/
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
说明：将传入的二进制类型转成整型变量
输入：二进制类型数据的字符串变量(在内部分配内存)
返回值：转化成功的整型变量
创建者：蔡
更新时间：2015/10/21*/
int CListWriteRelationSet::BinaryIntoInteger(const unsigned char *chBinaryIn){
    int iNum = 0;
    long int *iNumNew = new long int();

    memcpy ((unsigned char *)iNumNew, chBinaryIn, 4);
    iNum = *iNumNew;

    delete iNumNew;
    return iNum;
}

/**
说明：在链表尾部插入一个关系集合节点（尾差法存入）
参数：插入节点
返回值：是否插入成功
创建者：霍*/
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
说明：获取节点数目
返回值：节点数目
创建者：霍*/
int CListWriteRelationSet::getNodeNum(){
	return m_iNodeNum;
}

/**
说明：获取头结点
返回值：头结点
创建者：霍*/
CListWriteRelationNode *CListWriteRelationSet::getListWriteRelationHeadNode(){
    return m_pFirstListRelationNode;
}

/**
名称：getBinary
说明：获取本对象转成的二进制数据
返回值：二进制数据集合
创建者：蔡
更新时间：2015/10/9*/
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

    //数据总量转二进制
    isSuccessed = this->IntegerIntoBinary(iTotalNum, chTempNum);
    memcpy (chBinary, chTempNum, 4);
    memset (chTempNum, 0, 4);

    //节点个数转二进制
    isSuccessed = this->IntegerIntoBinary(m_iNodeNum, chTempNum);
    memcpy (chBinary+4, chTempNum, 4);
    memset (chTempNum, 0, 4);

    //各节点转二进制
    pTempNode = m_pFirstListRelationNode;
    for (int i=0; i<m_iNodeNum; i++){
        chTempBinary = pTempNode->getEntityRelationSet()->getBinary();
        memcpy (chBinary+iDataLength, chTempBinary, pTempNode->getEntityRelationSet()->getBinaryLength());
        iDataLength += pTempNode->getEntityRelationSet()->getBinaryLength();
        pTempNode = pTempNode->getNextRelationNode();
		free (chTempBinary);
		chTempBinary = NULL;
    }

    //添加末尾校验符
    memset (chBinary+iTotalNum-1, '\0', 1);

    free (chTempNum);
    if (isSuccessed){
        return chBinary;
    }
    return NULL;
}

/**
名称：getBinaryLength
说明：获取本对象转成的二进制数据的长度
返回值：二进制数据长度
创建者：蔡
更新时间：2015/10/9*/
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
名称：update
说明：更新二进制数组
参数：包含更新信息的二进制数据
返回值：bool型，表示更新是否成功
创建者：蔡
更新时间:2015/10/25*/
bool CListWriteRelationSet::update(const unsigned char* chBuffer){
    int iAllLength = 0;
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

    /*转多个时间片*/
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
            //获取段长度
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

