#pragma once
#include <string>
#include<sstream>
#include"iostream"
using namespace std;

class CEntityRelationSet{
	//数组内站点个数
    int m_iStationNum;   
	//时间片ID
    int m_iTimeID;  
	//关系二维数组
    double **m_RelationSet;     
	//byte **m_RelationSet;
    /**
    说明：将传入的整型变量转成二进制类型
    输入：待转整型变量，接收转换后的二进制类型数据的字符串变量
    返回值：是否转化成功
    创建者：蔡
    更新时间：2015/10/21*/
    bool IntegerIntoBinary(const int iNumIn, unsigned char *chBinaryOut);

    /**
    说明：将传入的二进制类型转成整型变量
    输入：二进制类型数据的字符串变量(在内部分配内存)
    返回值：转化成功的整型变量 
    创建者：蔡
    更新时间：2015/10/21*/
    int BinaryIntoInteger(const unsigned char *chBinaryIn);
public:
	
    /**
    说明：构造关系数据集合实体，构造并初始化二维数组来存放关系数据
    参数：站点个数
    创建者：霍*/
    CEntityRelationSet(int iStationNum, int iTimeID);

    CEntityRelationSet();

    ~CEntityRelationSet(void);

    /**
    说明：设置站点个数
    参数：站点个数
    创建者：霍*/
    void setStationNum(int iStationNum);

    /**
    说明：得到站点个数
    返回值：站点个数
    创建者：霍*/
    int getStationNum();

	//CEntityRelation *getRelationSet()
	//{
	//	return m_RelationSet;
	//}
    /**
    说明：初始化关系二维数组，对角线为1，其余数据置
    创建者：霍*/
	void initRelationSet();

    /**
    说明：插入数据关系集合
    参数：起始站点关系，目标站点关系，站点关联值
    返回值：是否插入成功
    创建者：霍*/
    void insertRelationSet(int iTargetStationID, int iRelationStationID, double iStationRelation);

    /**
    说明：插入数据关系集合
    参数：起始站点关系，目标站点关系，站点关联值
    返回值：是否插入成功
    创建者：霍*/
	void insertStationRelation(int iTargetStationID, int iRelationStationID, double iStationRelation);

    /**
    说明：某个时间片中得到两个站点关系
    参数：目标站点，关联站点
    返回值：站点关系
    创建者：霍*/
    double getStationRelation(int iSourceStationID, int iTargetStationID);

    /**
    说明：得到站点个数
    返回值：站点个数
    创建者：霍*/
    int getEntityNum();

    /**
    说明：得到集合时间片ID
    返回值：时间片ID
    创建者：霍*/
    int getTimeID();

    /**
    说明：设置集合时间片ID
    输入：时间片ID
    创建者：霍*/
    void setTimeID(int iTimeID);

    /**
    名称：getBinary
    说明：获取本对象转成的二进制数据
    返回值：二进制数据集合
    创建者：蔡
    更新时间：2015/10/9*/
    unsigned char *getBinary();

    /**
    名称：getBinaryLength
    说明：获取本对象转成的二进制数据的长度
    返回值：二进制数据长度
    创建者：蔡
    更新时间：2015/10/9*/
    int getBinaryLength();

    /**
    名称：update
    说明：更新二进制数组
    参数：包含更新信息的二进制数据
    返回值：bool型，表示更新是否成功
    创建者：蔡
    更新时间:2015/10/25*/
    bool update(const unsigned char* chBuffer);

	char *getString()
	{
		char cString [20000];
		itoa(m_iTimeID,cString, 10);
		strcat(cString, "   ");
		
		char cStringStationNum[10];
		itoa(m_iStationNum, cStringStationNum, 10);
		strcat(cStringStationNum, "   ");

		strcat(cString,cStringStationNum);
		
		for(int iCount = 0; iCount < m_iStationNum; iCount++)
		{
			for (int jCount = 0; jCount < m_iStationNum; jCount++)
			{
				char *a = (char *)malloc (5);
				memset(a, 0, 5);
				itoa(m_RelationSet[iCount][jCount], a, 10);
				strcat(cString, a);
			}
		}
		return cString;
	}

	string changeToStringstream()
	{
		stringstream strstreamCount;
		char* cLeft = "(";
		char* cBlank = ",";
		char* cRight = ")";
		/*将各个属性放进字符串*/
		strstreamCount<<cLeft;
		for(int iCount = 0; iCount < m_iStationNum; iCount++)
		{
			strstreamCount<<cLeft;
			for(int jCount = 0; jCount < m_iStationNum; jCount++)
			{
				strstreamCount<<m_RelationSet[iCount][jCount]<<cBlank;
			}
			strstreamCount<<cRight<<"\n";
		}
		
		strstreamCount<<cRight;

		/*将stringstream转换成string*/
		string strCount(strstreamCount.str());


		return strCount;
	}
};
