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
    ˵��������Ҫ���������ڵ�ʱ��������������һ���ڵ�
    ��������һ���ڵ�ָ��
    ����ֵ��
    ����ʱ�䣺*/
	void setNextRelationNode(CListRelationNode *pNextRelationNode)
	{
		m_pNextRelationNode = pNextRelationNode;
	}

	/**
    ˵�������������һ���ڵ�
    ������
    ����ֵ����һ���ڵ�ָ��
    ����ʱ�䣺*/
	CListRelationNode *getNextRelationNode()
	{
		return m_pNextRelationNode;
	}

	/**
    ˵�������ýڵ��б����ʱ��Ƭ����
    ������ʱ��Ƭ����ָ��
    ����ֵ��
    ����ʱ�䣺*/
	void setEntityRelationSet(CEntityRelationSet *pEntityRelationSet)
	{
		m_pEntityRelationSet = pEntityRelationSet;
	}

	/**
    ˵�����õ���ǰָ�뱣���ʱ��Ƭ��ϵ����ָ��
    ������
    ����ֵ����ǰʱ��Ƭָ���ϵ����
    ����ʱ�䣺*/
	CEntityRelationSet *getEntityRelationSet()
	{
		return m_pEntityRelationSet;
	}

	/**
    ˵����������������
    ��������������
    ����ֵ��
    ����ʱ�䣺*/
	void setSurvivalTime(int iSurvivalTime)
	{
		m_iSurvivalTime = iSurvivalTime;
	}

	/**
    ˵���������������
    ������
    ����ֵ����������
    ����ʱ�䣺*/
	int getSurvivalTime()
	{
		return m_iSurvivalTime;
	}

	/**
    ˵�����������վ��֮��Ĺ�ϵ
    ������
    ����ֵ������վ��֮��Ĺ�ϵֵ
    ����ʱ�䣺*/
	int getStationRelation(int iTargetStation, int iRelationStation)
	{
		m_pEntityRelationSet->getStationRelation(iTargetStation, iRelationStation);
	}

	/**
	 * ���ܣ�copyListRelationNode�ڵ�����,������ListRelationNode,����������ͬ�ڵ�֮��Ŀ���
	 * ���룺��Ҫcopy��ListRelationNode�½��ڵ㣬����Ҫ���г�ʼ��
	 * ������
	 */
	void copyListRelationNode(CListRelationNode* pListRelationNode)
	{
		//��ȡ��Ҫ�����ڵ��վ�����
		int iStationNum = pListRelationNode->getEntityRelationSet()->getStationNum();
		//��ȡ��������
		int iSurvivalTime = pListRelationNode->getSurvivalTime();
		//������������
		this->setSurvivalTime(iSurvivalTime);
		//����վ�����
		this->getEntityRelationSet()->setStationNum(iStationNum);
		//��ʼ����ϵ��������
		this->getEntityRelationSet()->initRelationSet();

		//��ϵ����copy
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
	//��һ����ϵ���Ͻڵ�
	CListRelationNode *m_pNextRelationNode;
	//��ǰ�ڵ��Ӧ��ϵ���ݼ���
	CEntityRelationSet *m_pEntityRelationSet;
	//��������
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
		//��ͷ�ڵ�Ϊ�գ�ֱ�Ӳ���
		if(m_pFirstListRelationNode == NULL)
			m_pFirstListRelationNode = pListRelationNode;
		//ͷ�ڵ㲻Ϊ�գ�����ͷ�巨
		else
		{
			//����ͷ�����һ���ڵ�ָ��
			CListRelationNode *tempListRelationNode = m_pFirstListRelationNode;
			//���뵽ͷ��������
			m_pFirstListRelationNode = pListRelationNode;
			//��ԭ���ڵ����õ��²���ڵ�֮��
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
		/*����ϵ���ݷ����ַ�����*/
		/*�������Ϊ�գ��ͷ���()*/
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
	//ָ���һ������ڵ�
	CListRelationNode *m_pFirstListRelationNode;
	//����ڵ�����
	int m_iNodeNum;
};

