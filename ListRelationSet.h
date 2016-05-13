#pragma once
#include"EntityRelationSet.h"

class CListRelationNode
{
public:
	CListRelationNode()
	{
		m_pNextRelationNode = NULL;
		m_pEntityRelationSet = new CEntityRelationSet();
		m_iSurvivalTime = 0;
	}
	~CListRelationNode()
	{
		delete m_pEntityRelationSet;
		m_pNextRelationNode = NULL;
	}
public:
	/**
    说明：在需要向链表插入节点时，设置链表中下一个节点
    参数：下一个节点指针
    返回值：
    更新时间：*/
	void setNextRelationNode(CListRelationNode *pNextRelationNode)
	{
		m_pNextRelationNode = pNextRelationNode;
	}

	/**
    说明：获得链表下一个节点
    参数：
    返回值：下一个节点指针
    更新时间：*/
	CListRelationNode *getNextRelationNode()
	{
		return m_pNextRelationNode;
	}

	/**
    说明：设置节点中保存的时间片集合
    参数：时间片集合指针
    返回值：
    更新时间：*/
	void setEntityRelationSet(CEntityRelationSet *pEntityRelationSet)
	{
		m_pEntityRelationSet = pEntityRelationSet;
	}

	/**
    说明：得到当前指针保存的时间片关系集合指针
    参数：
    返回值：当前时间片指针关系集合
    更新时间：*/
	CEntityRelationSet *getEntityRelationSet()
	{
		return m_pEntityRelationSet;
	}

	/**
    说明：设置生存周期
    参数：生存周期
    返回值：
    更新时间：*/
	void setSurvivalTime(int iSurvivalTime)
	{
		m_iSurvivalTime = iSurvivalTime;
	}

	/**
    说明：获得生存周期
    参数：
    返回值：生存周期
    更新时间：*/
	int getSurvivalTime()
	{
		return m_iSurvivalTime;
	}

	/**
    说明：获得两个站点之间的关系
    参数：
    返回值：两个站点之间的关系值
    更新时间：*/
	int getStationRelation(int iTargetStation, int iRelationStation)
	{
		m_pEntityRelationSet->getStationRelation(iTargetStation, iRelationStation);
	}

	/**
	 * 功能：copyListRelationNode节点数据,到调用ListRelationNode,用于两个相同节点之间的拷贝
	 * 传入：需要copy的ListRelationNode新建节点，不需要进行初始化
	 * 传出：
	 */
	void copyListRelationNode(CListRelationNode* pListRelationNode)
	{
		//获取需要拷贝节点的站点个数
		int iStationNum = pListRelationNode->getEntityRelationSet()->getStationNum();
		//获取生存周期
		int iSurvivalTime = pListRelationNode->getSurvivalTime();
		//设置生存周期
		this->setSurvivalTime(iSurvivalTime);
		//设置站点个数
		this->getEntityRelationSet()->setStationNum(iStationNum);
		//初始化关系数据数组
		this->getEntityRelationSet()->initRelationSet();

		//关系数据copy
		for (int iCount = 0; iCount < iStationNum; iCount++)
		{
			for (int jCount = 0; jCount < iStationNum; jCount++)
			{
				this->getEntityRelationSet()->insertStationRelation(iCount, jCount, pListRelationNode->getEntityRelationSet()->getStationRelation(iCount, jCount));
			}
		}
	}

	string changeToStringstream()
	{
		stringstream strstreamTimeSliceCountSet;
		char* cLeft = "(";
		char* cRight = ")";
		strstreamTimeSliceCountSet << m_pEntityRelationSet->changeToStringstream();		
		string strTimeSliceCountSet(strstreamTimeSliceCountSet.str());
		return strTimeSliceCountSet;
	}
private:
	//下一个关系集合节点
	CListRelationNode *m_pNextRelationNode;
	//当前节点对应关系数据集合
	CEntityRelationSet *m_pEntityRelationSet;
	//生存周期
	int m_iSurvivalTime;
};

class CListRelationSet
{
public:
	void getLastTimeSliceCountNode(CListRelationNode *pHeadNode)
	{
	
		if(pHeadNode->getNextRelationNode()==NULL)
		{
		
		}else{
			getLastTimeSliceCountNode(pHeadNode->getNextRelationNode());
		}
		delete pHeadNode;
	}

	CListRelationSet(void)
	{
		m_pFirstListRelationNode = NULL;
		m_iNodeNum = 0;
	}
	~CListRelationSet(void)
	{
		while(m_iNodeNum--)
		{
			CListRelationNode *tempReleaseNode = this->getNextRelationNode();
			m_pFirstListRelationNode = tempReleaseNode->getNextRelationNode();
			
			delete tempReleaseNode;	
		}
	}
	void releaseNode()
	{
		getLastTimeSliceCountNode(m_pFirstListRelationNode);
	}


	bool insertRelationNode(CListRelationNode *pListRelationNode)
	{
		//若头节点为空，直接插入
		if(m_pFirstListRelationNode == NULL)
			m_pFirstListRelationNode = pListRelationNode;
		//头节点不为空，采用头插法
		else
		{
			//保存头结点下一个节点指针
			CListRelationNode *tempListRelationNode = m_pFirstListRelationNode;
			//插入到头结点的下面
			m_pFirstListRelationNode = pListRelationNode;
			//将原来节点设置到新插入节点之后
			pListRelationNode->setNextRelationNode(tempListRelationNode);
		}
		m_iNodeNum++;
		return true;
	}
	
	CListRelationNode *getNextRelationNode()
	{
		return m_pFirstListRelationNode;
	}

	int getNodeNum()
	{
		return m_iNodeNum;
	}
	void setNodeNum(int iNodeNum)
	{
		m_iNodeNum = iNodeNum;
	}

	void setFirstListRelationNode(CListRelationNode *pListRelationNode)
	{
		m_pFirstListRelationNode = pListRelationNode;
	}

	string changeToStringstream()
	{
		stringstream strstreamTimeSliceCountSet;
		char* cLeft = "(";
		char* cRight = ")";	
		CListRelationNode* temp =m_pFirstListRelationNode;
		/*将关系数据放入字符串中*/
		/*如果链表为空，就返回()*/
		if(m_iNodeNum==0)
		{
			strstreamTimeSliceCountSet<<cLeft;
			strstreamTimeSliceCountSet>>cRight;
		}
		else
		{
			while(temp!=NULL)
			{
				strstreamTimeSliceCountSet<<temp->getEntityRelationSet()->changeToStringstream();
				temp = temp->getNextRelationNode();
			}
		}
		string strTimeSliceCountSet(strstreamTimeSliceCountSet.str());
		return strTimeSliceCountSet;
	}
private:
	//指向第一个链表节点
	CListRelationNode *m_pFirstListRelationNode;
	//链表节点总数
	int m_iNodeNum;
};

