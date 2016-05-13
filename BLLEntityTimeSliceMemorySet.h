#pragma once
#include"BLLEntityTimeSliceMemory.h"

//ʱ��Ƭ�ڴ�ڵ�
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
	//�������ƣ�getNextTimeSliceMemoryNode
	//��������
	//����ֵ��ʱ��Ƭ�ڴ�ڵ�
	//��������ȡ��һ��ʱ��Ƭ�ڴ�ڵ�
	CEntityTimeSliceMemoryNode* getNextTimeSliceMemoryNode()
	{
		return m_pNextTimeSliceMemoryNode;
	}

	//�������ƣ�setNextTimeSliceMemoryNode
	//������ʱ��Ƭ�ڴ�ڵ�
	//����ֵ����
	//������������һ��ʱ��Ƭ�ڴ�ڵ�
	void setNextTimeSliceMemoryNode(CEntityTimeSliceMemoryNode* pNextTimeSliceMemoryNode)
	{
		m_pNextTimeSliceMemoryNode = pNextTimeSliceMemoryNode;
	}

	//�������ƣ�getTimeSliceMemory
	//��������
	//����ֵ��ʱ��Ƭ�ڴ����
	//��������ȡʱ��Ƭ�ڴ����
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
	CEntityTimeSliceMemoryNode* m_pHeadTimeSliceMemoryNode;	//ͷ�ڵ�
	int m_iNodeNum;											//����Ԫ�ظ���


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

	//�������ƣ�insertingTimeSliceMemory
	//����������Ԫ��
	//����ֵ��bool�ͣ���ʾ�����Ƿ�ɹ�
	//��������ͷ�巨����
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
			/*��С��������*/
			sort(m_pHeadTimeSliceMemoryNode);
		}
		return true;
	}

	//�������ƣ�getNodeNum
	//��������
	//����ֵ���������
	//��������ȡ�������
	int getNodeNum()
	{
		return m_iNodeNum;
	}

	//�������ƣ�getHeadNode
	//��������
	//����ֵ��ͷ�ڵ�
	//��������ȡͷ�ڵ�
	CEntityTimeSliceMemoryNode* getHeadNode()
	{
		return m_pHeadTimeSliceMemoryNode;
	}

	//�������ƣ�locatingTimeSliceMemory
	//������ʱ��Ƭ���
	//����ֵ��bool�ͣ���ʾ��Ӧʱ��Ƭ�����Ƿ����
	//���������Ҷ�Ӧʱ��Ƭ�ڴ�����Ƿ����
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

	//�������ƣ�updatingTimeSliceMemoryNode
	//������ʱ��Ƭ�ڴ����
	//����ֵ��bool�� ��ʾ�����Ƿ�ɹ�
	//��������ȡָ��ʱ��Ƭ�ڴ�ڵ㲢����ʱ��Ƭ�ڴ�ڵ�
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

	//�������ƣ�updatingHeadNode
	//��������
	//����ֵ��bool��,��ʾ�����Ƿ�ɹ�
	//����������ͷ�ڵ�
	bool updatingHeadNode()
	{
		CEntityTimeSliceMemoryNode* temp = m_pHeadTimeSliceMemoryNode->getNextTimeSliceMemoryNode();
		delete m_pHeadTimeSliceMemoryNode;
		m_pHeadTimeSliceMemoryNode = temp;
		m_iNodeNum--;

		return true;
	}

	//�������ƣ�getNode
	//������ʱ��Ƭ���
	//����ֵ��ʱ��Ƭ�ڴ����ڵ�
	//��������ȡʱ��Ƭ�ڴ����ڵ�
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

	//�������ƣ�getMinTimeSliceIDNode
	//������ͷ�ڵ�
	//����ֵ��ʱ��Ƭ�ڴ����ڵ�
	//��������ȡ��Сʱ��Ƭ��ŵ�ʱ��Ƭ�ڴ����ڵ�
	CEntityTimeSliceMemoryNode* getMinTimeSliceIDNode(CEntityTimeSliceMemoryNode* pHeadNode)
	{
		CEntityTimeSliceMemoryNode* temp = pHeadNode;
		while(temp->getNextTimeSliceMemoryNode()!=NULL)
		{
			temp = temp->getNextTimeSliceMemoryNode();
		}
		return temp;
	}

	//�������ƣ�getFirstTimeSliceMemoryNode
	//������ͷ�ڵ㣬��ǰʱ��Ƭ���
	//����ֵ����һ����Ҫ�洢��Ԫ��
	//��������ȡȥ��һ����Ҫ�洢��Ԫ��
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
