#pragma once
#include"BLLEntityTimeSliceMemory.h"

//时间片内存节点
class CEntityTimeSliceMemoryNode
{
private:
	CBLLEntityTimeSliceMemory* m_pTimeSliceMemory;
	CEntityTimeSliceMemoryNode* m_pNextTimeSliceMemoryNode;

public:
	CEntityTimeSliceMemoryNode(CBLLEntityTimeSliceMemory* pTimeSliceMemory)
	{
		m_pTimeSliceMemory = pTimeSliceMemory;
		m_pNextTimeSliceMemoryNode = NULL;
	}

	~CEntityTimeSliceMemoryNode()
	{
		delete m_pTimeSliceMemory;
		m_pTimeSliceMemory = NULL;
	}
	//函数名称：getNextTimeSliceMemoryNode
	//参数：无
	//返回值：时间片内存节点
	//描述：获取下一个时间片内存节点
	CEntityTimeSliceMemoryNode* getNextTimeSliceMemoryNode()
	{
		return m_pNextTimeSliceMemoryNode;
	}

	//函数名称：setNextTimeSliceMemoryNode
	//参数：时间片内存节点
	//返回值：无
	//描述：设置下一个时间片内存节点
	void setNextTimeSliceMemoryNode(CEntityTimeSliceMemoryNode* pNextTimeSliceMemoryNode)
	{
		m_pNextTimeSliceMemoryNode = pNextTimeSliceMemoryNode;
	}

	//函数名称：getTimeSliceMemory
	//参数：无
	//返回值：时间片内存对象
	//描述：获取时间片内存对象
	CBLLEntityTimeSliceMemory* getTimeSliceMemory()
	{
		return m_pTimeSliceMemory;
	}

	bool operator ==(CEntityTimeSliceMemoryNode* &pNode)
	{
		if(this->getTimeSliceMemory()->getTimeSliceID() == pNode->getTimeSliceMemory()->getTimeSliceID())
		{
			return true;
		}
		return false;
	}
	bool operator >(CEntityTimeSliceMemoryNode* &pNode)
	{
		if(this->getTimeSliceMemory()->getTimeSliceID() > pNode->getTimeSliceMemory()->getTimeSliceID())
		{
			return true;
		}
		return false;
	}

};
class CBLLEntityTimeSliceMemorySet
{
private:
	CEntityTimeSliceMemoryNode* m_pHeadTimeSliceMemoryNode;	//头节点
	int m_iNodeNum;											//链表元素个数


public:
	CBLLEntityTimeSliceMemorySet()
	{
		m_pHeadTimeSliceMemoryNode = NULL;
		m_iNodeNum = 0;
	}
	~CBLLEntityTimeSliceMemorySet()
	{
		if(m_pHeadTimeSliceMemoryNode!=NULL)
		{
			getLastTimeSliceMemoryNode(m_pHeadTimeSliceMemoryNode);
		}
	}
private:

	CEntityTimeSliceMemoryNode* sort(CEntityTimeSliceMemoryNode* &pHeadNode)
	{
		if(pHeadNode==NULL||pHeadNode->getNextTimeSliceMemoryNode()==NULL)
		{
			return pHeadNode;
		}

		CEntityTimeSliceMemoryNode* r = pHeadNode->getNextTimeSliceMemoryNode();
		CEntityTimeSliceMemoryNode* temp;
		pHeadNode->setNextTimeSliceMemoryNode(NULL);

		while(r!=NULL)
		{
			if(r->getTimeSliceMemory()->getTimeSliceID()<pHeadNode->getTimeSliceMemory()->getTimeSliceID())
			{
				temp = r->getNextTimeSliceMemoryNode();
				r->setNextTimeSliceMemoryNode(pHeadNode);
				pHeadNode = r;
				r = temp;
			}
			else
			{
				CEntityTimeSliceMemoryNode* p = pHeadNode;
				while(p->getNextTimeSliceMemoryNode()!=NULL)
				{
					if(r==NULL)
					{
						break;
					}
					if(r->getTimeSliceMemory()->getTimeSliceID()<p->getNextTimeSliceMemoryNode()->getTimeSliceMemory()->getTimeSliceID())
					{
						temp = r->getNextTimeSliceMemoryNode();
						r->setNextTimeSliceMemoryNode(p->getNextTimeSliceMemoryNode());
						p->setNextTimeSliceMemoryNode(r);
						r  = temp;
						continue;
					}
					else
					{
						p = p->getNextTimeSliceMemoryNode();
					}
				}
				if(p->getNextTimeSliceMemoryNode()==NULL)
				{
					temp = r->getNextTimeSliceMemoryNode();
					r->setNextTimeSliceMemoryNode(NULL);
					p->setNextTimeSliceMemoryNode(r);
					r = temp;
				}
			}
		}

		return pHeadNode;
	}
	bool getLastTimeSliceMemoryNode(CEntityTimeSliceMemoryNode* pHeadNode)
	{
		if(pHeadNode->getNextTimeSliceMemoryNode()==NULL)
		{}
		else
		{
			getLastTimeSliceMemoryNode(pHeadNode->getNextTimeSliceMemoryNode());
		}
		delete pHeadNode;
		return true;
	}
public:

	//函数名称：insertingTimeSliceMemory
	//参数：插入元素
	//返回值：bool型，表示插入是否成功
	//描述：按头插法插入
	bool insertingTimeSliceMemory(CEntityTimeSliceMemoryNode* pTimeSliceMemoryNode)
	{
		CEntityTimeSliceMemoryNode* temp = m_pHeadTimeSliceMemoryNode;
		if(m_pHeadTimeSliceMemoryNode == NULL)
		{
			m_pHeadTimeSliceMemoryNode = pTimeSliceMemoryNode;
		}
		else
		{
			temp = m_pHeadTimeSliceMemoryNode;
			m_pHeadTimeSliceMemoryNode = pTimeSliceMemoryNode;
			pTimeSliceMemoryNode->setNextTimeSliceMemoryNode(temp);
		}
		m_iNodeNum++;
		if(m_iNodeNum>=2)
		{
			/*从小到大排序*/
			sort(m_pHeadTimeSliceMemoryNode);
		}
		return true;
	}

	//函数名称：getNodeNum
	//参数：无
	//返回值：链表个数
	//描述：获取链表个数
	int getNodeNum()
	{
		return m_iNodeNum;
	}

	//函数名称：getHeadNode
	//参数：无
	//返回值：头节点
	//描述：获取头节点
	CEntityTimeSliceMemoryNode* getHeadNode()
	{
		return m_pHeadTimeSliceMemoryNode;
	}

	//函数名称：locatingTimeSliceMemory
	//参数：时间片编号
	//返回值：bool型，表示对应时间片对象是否存在
	//描述：查找对应时间片内存对象是否存在
	bool locatingTimeSliceMemory(int iTimeSliceID)
	{
		CEntityTimeSliceMemoryNode* temp = m_pHeadTimeSliceMemoryNode;
		while(temp)
		{
			if(temp->getTimeSliceMemory()->getTimeSliceID()==iTimeSliceID)
			{
				return true;
			}
			temp = temp->getNextTimeSliceMemoryNode();
		}
		return false;
	}

	//函数名称：updatingTimeSliceMemoryNode
	//参数：时间片内存对象
	//返回值：bool型 表示更新是否成功
	//描述：获取指定时间片内存节点并更新时间片内存节点
	bool updatingTimeSliceMemoryNode(CBLLEntityTimeSliceMemory* pTimeSliceMemory)
	{
		CEntityTimeSliceMemoryNode* temp = m_pHeadTimeSliceMemoryNode;
		
		while(temp!=NULL)
		{
			CBLLEntityTimeSliceMemory* tempTimeSliceMemory = temp->getTimeSliceMemory();
			if(tempTimeSliceMemory->getTimeSliceID()==pTimeSliceMemory->getTimeSliceID())
			{
				tempTimeSliceMemory->setTimeSliceID(pTimeSliceMemory->getTimeSliceID());
				tempTimeSliceMemory->setSurvivalTime(pTimeSliceMemory->getSurvivalTime());
				tempTimeSliceMemory->setArrayLength(pTimeSliceMemory->getArrayLength());
				tempTimeSliceMemory->setArraySize(pTimeSliceMemory->getArraySize());
				memcpy(tempTimeSliceMemory->getStationCount(),pTimeSliceMemory->getStationCount(),sizeof(CEntityStationCount));
				return true;
			}
			temp = temp->getNextTimeSliceMemoryNode();
		}
		return false;
	}

	//函数名称：updatingHeadNode
	//参数：无
	//返回值：bool型,表示更新是否成功
	//描述：更新头节点
	bool updatingHeadNode()
	{
		CEntityTimeSliceMemoryNode* temp = m_pHeadTimeSliceMemoryNode->getNextTimeSliceMemoryNode();
		delete m_pHeadTimeSliceMemoryNode;
		m_pHeadTimeSliceMemoryNode = temp;
		m_iNodeNum--;

		return true;
	}

	//函数名称：getNode
	//参数：时间片编号
	//返回值：时间片内存对象节点
	//描述：获取时间片内存对象节点
	CEntityTimeSliceMemoryNode* getNode(int iTimeSliceID)
	{
		CEntityTimeSliceMemoryNode* temp = m_pHeadTimeSliceMemoryNode;
		while(temp)
		{
			if(temp->getTimeSliceMemory()->getTimeSliceID()==iTimeSliceID)
			{
				return temp;
			}
			temp = temp->getNextTimeSliceMemoryNode();
		}
		return NULL;
	}

	//函数名称：getMinTimeSliceIDNode
	//参数：头节点
	//返回值：时间片内存对象节点
	//描述：获取最小时间片编号的时间片内存对象节点
	CEntityTimeSliceMemoryNode* getMinTimeSliceIDNode(CEntityTimeSliceMemoryNode* pHeadNode)
	{
		CEntityTimeSliceMemoryNode* temp = pHeadNode;
		while(temp->getNextTimeSliceMemoryNode()!=NULL)
		{
			temp = temp->getNextTimeSliceMemoryNode();
		}
		return temp;
	}

	//函数名称：getFirstTimeSliceMemoryNode
	//参数：头节点，当前时间片编号
	//返回值：第一个需要存储的元素
	//描述：获取去第一个需要存储的元素
	CEntityTimeSliceMemoryNode* getFirstWriteTimeSliceMemoryNode(CEntityTimeSliceMemoryNode* &pHead,int iTimeSliceID)
	{
		CEntityTimeSliceMemoryNode* temp = pHead;
		while(temp!=NULL&&temp->getTimeSliceMemory()->getTimeSliceID()>=iTimeSliceID)
		{
			temp = temp->getNextTimeSliceMemoryNode();
		}
		return temp;
	}
};
