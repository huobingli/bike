#pragma once
#include"EntityRelationSet.h"

//����ڵ�
class CListWriteRelationNode{
    CListWriteRelationNode *m_pNextRelationNode; //��һ����ϵ����ڵ�
    CEntityRelationSet *m_pEntityRelationSet;    //ÿ���ڵ��и���վ���ϵ����ָ��
public:
    CListWriteRelationNode();

    /**
    ˵����������һ���ڵ�
    ��������һ���ڵ�ָ��
    ������:��*/
    void setNextRelationNode(CListWriteRelationNode *pListWriteRelationNode);

    ~CListWriteRelationNode();

    /**
    ˵�����õ���һ���ڵ�
    ����ֵ����һ���ڵ�
    �����ߣ���*/
    CListWriteRelationNode *getNextRelationNode();

    /**
    ˵�����õ���ǰ�ڵ��ϵ����
    ����ֵ���ڵ��ϵ����ָ��
    �����ߣ���*/
    CEntityRelationSet *getEntityRelationSet();

    /**
    ˵�������õ�ǰ�ڵ��ϵ����
    �������ڵ��ϵ����
    �����ߣ���*/
    void setEntityRelationSet(CEntityRelationSet *pEntityRelationSet);
};

//����
class CListWriteRelationSet{
    CListWriteRelationNode *m_pFirstListRelationNode;//����ͷ���ָ��
    int m_iNodeNum;                                  //�ڵ����

    /**
    ˵��������������ͱ���ת�ɶ���������
    ���룺��ת���ͱ���������ת����Ķ������������ݵ��ַ�������
    ����ֵ���Ƿ�ת���ɹ�
    �����ߣ���
    ����ʱ�䣺2015/10/21*/
    bool IntegerIntoBinary(const int iNumIn, unsigned char *chBinaryOut);

    /**
    ˵����������Ķ���������ת�����ͱ���
    ���룺�������������ݵ��ַ�������(���ڲ������ڴ�)
    ����ֵ��ת���ɹ������ͱ���
    �����ߣ���
    ����ʱ�䣺2015/10/21*/
    int BinaryIntoInteger(const unsigned char *chBinaryIn);

public:
	void getLastTimeSliceCountNode(CListWriteRelationNode * pHeadNode);
    CListWriteRelationSet();

    /**
    ˵��������ר��
    ��������ϵ����
    �����ߣ���
    ����ʱ�䣺2015.10.23*/
    CListWriteRelationSet(CEntityRelationSet *pEntityRelationSet);

    ~CListWriteRelationSet(void);

    /**
    ˵����������β������һ����ϵ���Ͻڵ㣨β����룩
    ����������ڵ�
    ����ֵ���Ƿ����ɹ�
    �����ߣ���*/
    bool insertRelationSet(CListWriteRelationNode *pListWriteRelationNode);

    /**
    ˵������ȡ�ڵ���Ŀ
    ����ֵ���ڵ���Ŀ
    �����ߣ���*/
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
    ˵������ȡͷ���
    ����ֵ��ͷ���
    �����ߣ���*/
    CListWriteRelationNode *getListWriteRelationHeadNode();

    /**
    ���ƣ�getBinary
    ˵������ȡ������ת�ɵĶ���������
    ����ֵ�����������ݼ���
    �����ߣ���
    ����ʱ�䣺2015/10/9*/
    unsigned char * getBinary();

    /**
    ���ƣ�getBinaryLength
    ˵������ȡ������ת�ɵĶ��������ݵĳ���
    ����ֵ�����������ݳ���
    �����ߣ���
    ����ʱ�䣺2015/10/9*/
    int getBinaryLength();

    /**
    ���ƣ�update
    ˵�������¶���������
    ����������������Ϣ�Ķ���������
    ����ֵ��bool�ͣ���ʾ�����Ƿ�ɹ�()
    �����ߣ���
    ����ʱ��:2015/10/25*/
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
