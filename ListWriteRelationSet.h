#pragma once
#include"EntityRelationSet.h"

//链表节点
class CListWriteRelationNode{
    CListWriteRelationNode *m_pNextRelationNode; //下一个关系对象节点
    CEntityRelationSet *m_pEntityRelationSet;    //每个节点中各个站点关系对象指针
public:
    CListWriteRelationNode();

    /**
    说明：设置下一个节点
    参数：下一个节点指针
    创建者:霍*/
    void setNextRelationNode(CListWriteRelationNode *pListWriteRelationNode);

    ~CListWriteRelationNode();

    /**
    说明：得到下一个节点
    返回值：下一个节点
    创建者：霍*/
    CListWriteRelationNode *getNextRelationNode();

    /**
    说明：得到当前节点关系集合
    返回值：节点关系集合指针
    创建者：霍*/
    CEntityRelationSet *getEntityRelationSet();

    /**
    说明：设置当前节点关系集合
    参数：节点关系集合
    创建者：霍*/
    void setEntityRelationSet(CEntityRelationSet *pEntityRelationSet);
};

//链表
class CListWriteRelationSet{
    CListWriteRelationNode *m_pFirstListRelationNode;//链表头结点指针
    int m_iNodeNum;                                  //节点个数

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
	void getLastTimeSliceCountNode(CListWriteRelationNode * pHeadNode);
    CListWriteRelationSet();

    /**
    说明：测试专用
    参数：关系对象
    创建者：蔡
    更新时间：2015.10.23*/
    CListWriteRelationSet(CEntityRelationSet *pEntityRelationSet);

    ~CListWriteRelationSet(void);

    /**
    说明：在链表尾部插入一个关系集合节点（尾差法存入）
    参数：插入节点
    返回值：是否插入成功
    创建者：霍*/
    bool insertRelationSet(CListWriteRelationNode *pListWriteRelationNode);

    /**
    说明：获取节点数目
    返回值：节点数目
    创建者：霍*/
    int getNodeNum();
	void setNodeNum(int iNodeNum)
	{
		m_iNodeNum = iNodeNum;
	}
	void releaseNode()
	{
		getLastTimeSliceCountNode(m_pFirstListRelationNode);
	}
    /**
    说明：获取头结点
    返回值：头结点
    创建者：霍*/
    CListWriteRelationNode *getListWriteRelationHeadNode();

    /**
    名称：getBinary
    说明：获取本对象转成的二进制数据
    返回值：二进制数据集合
    创建者：蔡
    更新时间：2015/10/9*/
    unsigned char * getBinary();

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
    返回值：bool型，表示更新是否成功()
    创建者：蔡
    更新时间:2015/10/25*/
    bool update(const unsigned char* chBuffer);

	/*char *getString()
	{
		char cString[300];
		CListWriteRelationNode *temp = m_pFirstListRelationNode;
		strcat(cString, temp->getEntityRelationSet()->getString());
		while(m_iNodeNum--)
		{
			strcat(cString, temp->getEntityRelationSet()->getString());
			temp = temp->getNextRelationNode();
		}
		return cString;
	}*/
};
