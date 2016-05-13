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
	 * 功能：新建BuffNum个链表节点，用于模型调用
	 * 传入：
	 * 传出：
	 * 调用条件：
	 *
	 */
	void mallocRelationNode()
	{
		m_pBuffPoolRelationNode = new CListRelationNode[BuffNum];
		return;
	}

	/**
	 * 功能：回收节点，释放空间
	 * 传入：
	 * 传出：
	 * 调用条件：
	 *
	 */
	void freeRelationNode()
	{
		delete []m_pBuffPoolRelationNode;
	}

	/**
	 * 功能：新建BuffNum个链表节点，用于模型调用
	 * 传入：
	 * 传出：
	 * 调用条件：
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
	 * 功能：回收节点，释放空间
	 * 传入：
	 * 传出：
	 * 调用条件：
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

