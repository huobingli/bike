#include"stdafx.h"
#include "EntityRelationSet.h"

CEntityRelationSet::CEntityRelationSet(){
	m_iStationNum = 0;
	m_iTimeID = 0;
	m_RelationSet = NULL;
}

/**
说明：构造关系数据集合实体，构造并初始化二维数组来存放关系数据
参数：站点个数
创建者：霍*/
CEntityRelationSet::CEntityRelationSet(int iStationNum, int iTimeID){
	m_iStationNum = iStationNum;
	m_iTimeID = iTimeID;
	this->initRelationSet();
}

CEntityRelationSet::~CEntityRelationSet(void){

	//删除第二维
	for (int iCount = 0; iCount < m_iStationNum; iCount++){
		delete[] m_RelationSet[iCount];
		m_RelationSet[iCount] = NULL;
	}
	delete[] m_RelationSet;
	m_RelationSet = NULL;
}

/**
说明：设置站点个数
参数：站点个数
创建者：霍*/
void CEntityRelationSet::setStationNum(int iStationNum){
	m_iStationNum = iStationNum;
}

/**
说明：得到站点个数
返回值：站点个数
创建者：霍*/
int CEntityRelationSet::getStationNum(){
	return m_iStationNum;
}

/**
说明：初始化关系二维数组，对角线为1，其余数据置
创建者：霍*/
void CEntityRelationSet::initRelationSet(){
	//构建二维关系数据集合数组
	//初始化第一维
	m_RelationSet = new double*[m_iStationNum];
	//初始化第二维
	for (int iCount = 0; iCount < m_iStationNum; iCount++){
		m_RelationSet[iCount] = new double[m_iStationNum];
	}

	//初始化二维数组
	for (int iCount = 0; iCount < m_iStationNum; iCount++){
		for (int jCount = 0; jCount < m_iStationNum; jCount++)
		{
			//相同站点置1，不同站点置0
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
说明：插入数据关系集合
参数：起始站点关系，目标站点关系，站点关联值
返回值：是否插入成功
创建者：霍*/
void CEntityRelationSet::insertStationRelation(int iTargetStationID, int iRelationStationID, double iStationRelation){
	m_RelationSet[iTargetStationID][iRelationStationID] = iStationRelation;
}

/**
说明：插入数据关系集合
参数：起始站点关系，目标站点关系，站点关联值
返回值：是否插入成功
创建者：霍*/
void CEntityRelationSet::insertRelationSet(int iTargetStationID, int iRelationStationID, double iStationRelation){
	m_RelationSet[iTargetStationID][iRelationStationID] = iStationRelation;
}

/**
说明：某个时间片中得到两个站点关系
参数：目标站点，关联站点
返回值：站点关系
创建者：霍*/
double CEntityRelationSet::getStationRelation(int iTargetStationID, int iRelationStationID){
	return m_RelationSet[iTargetStationID][iRelationStationID];
}

/**
说明：得到站点个数
返回值：站点个数
创建者：霍*/
int CEntityRelationSet::getEntityNum(){
	return m_iStationNum;
}


/**
说明：得到集合时间片ID
返回值：时间片ID
创建者：霍*/
int CEntityRelationSet::getTimeID(){
	return m_iTimeID;
}

/**
说明：设置集合时间片ID
输入：时间片ID
创建者：霍*/
void CEntityRelationSet::setTimeID(int iTimeID){
	m_iTimeID = iTimeID;
}

/********************************************************************************************
名称：getBinary
说明：获取本对象转成的二进制数据
返回值：二进制数据集合
创建者：蔡
更新时间：2015/10/10*/
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

	//数据总量转二进制
	isSuccessed = this->IntegerIntoBinary(iTotalNum, chTempNum);
	memcpy(chBinary, chTempNum, 4);
	memset(chTempNum, 0, 4);

	//时间片ID转二进制
	isSuccessed = this->IntegerIntoBinary(m_iTimeID, chTempNum);
	memcpy(chBinary + 4, chTempNum, 4);
	memset(chTempNum, 0, 4);

	//站点个数转二进制
	isSuccessed = this->IntegerIntoBinary(m_iStationNum, chTempNum);
	memcpy(chBinary + 8, chTempNum, 4);
	memset(chTempNum, 0, 4);

	//关系数据转二进制
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

	//添加末尾校验符
	memset(chBinary + iTotalNum - 1, '\0', 1);

	free(chTempNum);
	chTempNum = NULL;
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
int CEntityRelationSet::getBinaryLength(){
	if (m_iTimeID == 0){
		return 4 + 4 + 4 + 1;
	}
	return 4 + 4 + 4 + 1 + m_iStationNum * m_iStationNum * 4;
}

/**
名称：update
说明：使用字节数据更新
参数：更新二进制数组
返回值：是否更新成功
创建者：蔡
更新时间：2015/10/9*/
bool CEntityRelationSet::update(const unsigned char *chBuffer){

	if (chBuffer == NULL){
		return false;
	}

	int iAllLength = 0;
	unsigned char *pTempInt = (unsigned char *)malloc(4);
	memset(pTempInt, 0, 4);

	//转数据总量
	memcpy(pTempInt, chBuffer, 4);
	iAllLength = BinaryIntoInteger(pTempInt);
	memset(pTempInt, 0, 4);

	//转时间片ID
	memcpy(pTempInt, chBuffer + 4, 4);
	m_iTimeID = BinaryIntoInteger(pTempInt);
	memset(pTempInt, 0, 4);

	//转时间片内站点个数
	memcpy(pTempInt, chBuffer + 8, 4);
	m_iStationNum = BinaryIntoInteger(pTempInt);
	memset(pTempInt, 0, 4);

	//初始化二维关系数组
	if (m_iStationNum != 0){
		this->initRelationSet();

		//memcpy (m_RelationSet, chBuffer+12, m_iStationNum*m_iStationNum*4);

		//转关联数据
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
说明：将传入的整型变量转成二进制类型
输入：待转整型变量，接收转换后的二进制类型数据的字符串变量(在内部分配内存)
返回值：是否转化成功
创建者：蔡
更新时间：2015/10/21*/
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
说明：将传入的二进制类型转成整型变量
输入：二进制类型数据的字符串变量(在内部分配内存)
返回值：转化成功的整型变量
创建者：蔡
更新时间：2015/10/21*/
int CEntityRelationSet::BinaryIntoInteger(const unsigned char *chBinaryIn){
	int iNum = 0;
	long int *iNumNew = new long int();

	memcpy((unsigned char *)iNumNew, chBinaryIn, 4);
	iNum = *iNumNew;

	delete iNumNew;
	iNumNew = NULL;
	return iNum;
}