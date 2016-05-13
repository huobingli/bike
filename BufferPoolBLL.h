#pragma once
#include"ListRelationSet.h"
#include"ListWriteRelationSet.h"

#define BuffNum 5

class CBufferPoolBLL
{
public:
	CBufferPoolBLL(void)
	{
		
		m_pBuffPoolRelationNode = NULL;
		m_pBuffPoolWriteRelationNode = NULL;

		m_iBuffCount = -1;
	}
	~CBufferPoolBLL(void)
	{

	}

	/**
	 * ���ܣ��½�BuffNum������ڵ㣬����ģ�͵���
	 * ���룺
	 * ������
	 * ����������
	 *
	 */
	void mallocRelationNode()
	{
		m_pBuffPoolRelationNode = new CListRelationNode[BuffNum];
		return;
	}

	/**
	 * ���ܣ����սڵ㣬�ͷſռ�
	 * ���룺
	 * ������
	 * ����������
	 *
	 */
	void freeRelationNode()
	{
		delete []m_pBuffPoolRelationNode;
	}

	/**
	 * ���ܣ��½�BuffNum������ڵ㣬����ģ�͵���
	 * ���룺
	 * ������
	 * ����������
	 *
	 */
	void mallocWriteRelationNode()
	{
		m_pBuffPoolWriteRelationNode = new CListWriteRelationNode();	
	}

	CListWriteRelationNode *getWriteRelationNode()
	{
		return m_pBuffPoolWriteRelationNode;
	}

	/**
	 * ���ܣ����սڵ㣬�ͷſռ�
	 * ���룺
	 * ������
	 * ����������
	 *
	 */
	void freeListWriteRelationNode()
	{
		delete m_pBuffPoolWriteRelationNode;
	}
private:
	CListRelationNode *m_pBuffPoolRelationNode;
	CListWriteRelationNode *m_pBuffPoolWriteRelationNode;

	int m_iBuffCount;
};

