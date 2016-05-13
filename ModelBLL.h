#pragma once
#include"EntityTimeSliceCountSet.h"
#include"ListRelationSet.h"
#include"ListWriteRelationSet.h"
#include"BufferPoolBLL.h"
#include"BLLModelEntityTimeSliceCountArray.h"
class CBLLModelAnalyze
{
public:
	/**
	 * 功能：
	 * 传入：
	 * 传出：
	 * 调用条件：
	 */
	CBLLModelAnalyze(int iStationNum)
	{
		m_iTotalSurvivalTime = 3000;
		m_iTotalStationNum = iStationNum;
		//新建头结点
		m_pHeadListRelationSet = new CListRelationSet();
		_CrtDumpMemoryLeaks();
		m_pBufferPool = new CBufferPoolBLL();
		_CrtDumpMemoryLeaks();
		//创建一个二维数组存放数据
		m_pTimeSliceCountArray = NULL;
		//初始化数组
		initArray();
		_CrtDumpMemoryLeaks();
		/*releaseArray();
		_CrtDumpMemoryLeaks();*/
	}

	~CBLLModelAnalyze()
	{
		delete m_pHeadListRelationSet;
		delete m_pBufferPool;
		//delete m_pTimeSliceCountArray;
		//_CrtDumpMemoryLeaks();
		releaseArray();
		//_CrtDumpMemoryLeaks();
	}

	void initArray()
	{
		m_pTimeSliceCountArray = new CBLLModelEntityTimeSliceCountArray*[m_iTotalStationNum];
		for(int iCount = 0;iCount < m_iTotalStationNum; iCount++){
			m_pTimeSliceCountArray[iCount] = new CBLLModelEntityTimeSliceCountArray[m_iTotalStationNum];
		}
		
		//初始化二维数组
		for(int iCount = 0; iCount < m_iTotalStationNum; iCount++){
			for(int jCount = 0; jCount < m_iTotalStationNum; jCount++)
			{
				m_pTimeSliceCountArray[iCount][jCount].setMaxTime(0);
				m_pTimeSliceCountArray[iCount][jCount].setMinTime(0);
				m_pTimeSliceCountArray[iCount][jCount].setOperateTimes(0);
			}
		}
	}

	void releaseArray()
	{
		for(int iCount = 0;iCount < m_iTotalStationNum; iCount++){
			delete [] m_pTimeSliceCountArray[iCount];
		}

		delete [] m_pTimeSliceCountArray;
	}
	/**
	 * 功能：model中主要分析方法，每次传入一个统计集合链表，经过处理返回需要写入的关系集合链表
	 * 传入：统计集合链表（链表形式）， （引用传入）写入集合链表（链表形式）
	 * 传出：（引用传出）写入集合链表（链表形式）
	 * 调用条件：
	 */
	bool startAnalyze(CEntityTimeSliceCountSet *pEntityTimeSliceCountSet, CListWriteRelationSet *&pListWriteRelationSet)
	{
		CEntityTimeSliceCountNode *tempTimeSliceCountNode;
		//判断传入
		if(pEntityTimeSliceCountSet == NULL)
		{
			AfxMessageBox(_T("传入不能为空"));
			return false;
		}
		//传入不为空
		else
		{
			//获取第一个节点
			tempTimeSliceCountNode = pEntityTimeSliceCountSet->getHeadTimeSliceCountNode();
			
			//测试代码，测试用例667时间片
			//tempTimeSliceCountNode = tempTimeSliceCountNode->getNextTimeSliceCountNode()->
			//	getNextTimeSliceCountNode()->getNextTimeSliceCountNode();
			//if(tempTimeSliceCountNode->getTimeSliceCount()->getTimeID() == 667)
			//{
			//	initArray();
			//	copyEntityTimeSliceCountNode(tempTimeSliceCountNode);
			//	getRelation(tempTimeSliceCountNode);
			//}

			while(tempTimeSliceCountNode != NULL)
			{
				//初始化model中内存结构数组
				initArray();
				//将数据读入model中的内存结构中
				copyEntityTimeSliceCountNode(tempTimeSliceCountNode);

				//如果model中主链表为空，插入第一个矩阵，对角线为0，其余为100
				if(m_pHeadListRelationSet->getNextRelationNode() == NULL)
				{
					//处理集合并插入主链表
					//getRelation(tempTimeSliceCountNode);      /***************/
			
					//得到时间片长度
					int iTimeSliceID = tempTimeSliceCountNode->getTimeSliceCount()->getTimeID();
					int iStationCount = tempTimeSliceCountNode->getTimeSliceCount()->getStationCount()->getRentArraySize();
					int iSurvivalTime = tempTimeSliceCountNode->getTimeSliceCount()->getSurvivalTime();
	
					CListRelationNode *pListRelationNode = new CListRelationNode();
					//设置关系数据二位数组参数
					pListRelationNode->getEntityRelationSet()->setTimeID(iTimeSliceID);
					pListRelationNode->getEntityRelationSet()->setStationNum(m_iTotalStationNum);
					pListRelationNode->setSurvivalTime(iSurvivalTime);
					pListRelationNode->getEntityRelationSet()->initRelationSet();
					for(int iCount = 0; iCount < m_iTotalStationNum; iCount++)
					{
						for(int jCount = 0; jCount < m_iTotalStationNum; jCount++)
						{
							if(iCount == jCount)
								pListRelationNode->getEntityRelationSet()->insertStationRelation(iCount, jCount, 0);
							else
								pListRelationNode->getEntityRelationSet()->insertStationRelation(iCount, jCount, 100);
						}
					}
					m_pHeadListRelationSet->insertRelationNode(pListRelationNode);

					//下个准备处理节点
					tempTimeSliceCountNode = tempTimeSliceCountNode->getNextTimeSliceCountNode();

					m_iTotalSurvivalTime++;
					continue;
				}
				//如果插入节点和主链表中的头节点的序号不连续
				//插入一个空的关系对象
				else if(tempTimeSliceCountNode->getTimeSliceCount()->getTimeID() 
					- m_pHeadListRelationSet->getNextRelationNode()->getEntityRelationSet()->getTimeID() > 1)
				{
					//添加数据，处理
					int iTimeSliceID = m_pHeadListRelationSet->getNextRelationNode()->getEntityRelationSet()->getTimeID() + 1;
					//创建新的关系对象
					CListRelationNode *pListRelationNode = new CListRelationNode();
					//设置关系数据二位数组参数
					pListRelationNode->getEntityRelationSet()->setTimeID(iTimeSliceID);
					pListRelationNode->getEntityRelationSet()->setStationNum(m_iTotalStationNum);
					//初始化关系数据二维数组
					pListRelationNode->getEntityRelationSet()->initRelationSet();

					//没有的时间片集合，直接将初始化的数据存入主链表
					//getRelation(tempTimeSliceCountNode); 

					//插入到主链表中
					m_pHeadListRelationSet->insertRelationNode(pListRelationNode);

					
					m_iTotalSurvivalTime++;
					continue;
				}
				else
				{
					//处理集合
					getRelation(tempTimeSliceCountNode);      /***************/
			
					//下个准备处理节点
					tempTimeSliceCountNode = tempTimeSliceCountNode->getNextTimeSliceCountNode();

					
					m_iTotalSurvivalTime++;
					continue;
				}
				//处理一个就将总体生存周期进行自增
				//m_iTotalSurvivalTime++;

			}
		
			judgeSurvivalTime(pListWriteRelationSet);
			
			//释放
			delete tempTimeSliceCountNode;
			return true;
		}
	}


	/**

	 * 功能：拷贝统计集合，将原先统计集合放入内存模型
	 * 传入：统计集合
	 * 传出：
	 * 调用条件：
	 */
	bool copyEntityTimeSliceCountNode(CEntityTimeSliceCountNode *pEntityTimeSliceCountNode)
	{
		//写入站点数目
		int iArrayNum = pEntityTimeSliceCountNode->getTimeSliceCount()->getArraySize();
		int iRentArraySize = 0;//pEntityTimeSliceCountNode->getTimeSliceCount()->getStationCount()->getRentArraySize();
		int iReturnArraySize = 0;//pEntityTimeSliceCountNode->getTimeSliceCount()->getStationCount()->getReturnArraySize();

		int iTargetStationID = 0;
		int iRelationStationID = 0;

		CEntityStationCount *tempEntityStationCount = NULL;
		CEntityCount *tempEntityCount = NULL;

		//外层循环是EntityTimeSliceCount数组的有效个数
		for(int iCount = 0; iCount < iArrayNum; iCount++)
		{
			//获取统计集合内站点统计对象指针
			tempEntityStationCount = pEntityTimeSliceCountNode->getTimeSliceCount()->getStationCount();
			iRentArraySize = tempEntityStationCount[iCount].getRentArraySize();
			//iReturnArraySize = tempEntityStationCount[iCount].getReturnArraySize();

			iTargetStationID = tempEntityStationCount[iCount].getStationID();
			//内层循环是EntityStationCount数组的有效个数
			for(int jCount = 0; jCount < iRentArraySize; jCount++)
			{
				//获取统计集合内站点统计对象内的借车对象数组指针
				tempEntityCount = tempEntityStationCount[iCount].getRentCount();
				iRelationStationID = tempEntityCount[jCount].getRelatedStationID();
				
				m_pTimeSliceCountArray[iTargetStationID - 1][iRelationStationID - 1].setMaxTime(tempEntityCount[jCount].getMaxCostTime());
				m_pTimeSliceCountArray[iTargetStationID - 1][iRelationStationID - 1].setMinTime(tempEntityCount[jCount].getMinCostTime());
				m_pTimeSliceCountArray[iTargetStationID - 1][iRelationStationID - 1].setOperateTimes(tempEntityCount[jCount].getOperatedTimes());
			}

			//还车部分
			//for(int jCount = 0; jCount < iReturnArraySize; jCount++)
			//{
			//	//获取统计集合内站点统计对象内的还车对象数组指针
			//	tempEntityCount = tempEntityStationCount[iCount].getReturnCount();
			//	iRelationStationID = tempEntityCount[jCount].getRelatedStationID();
			//	
			//	m_pTimeSliceCountArray[iTargetStationID - 1][iRelationStationID - 1].setMaxTime(tempEntityCount[jCount].getMaxCostTime());
			//	m_pTimeSliceCountArray[iTargetStationID - 1][iRelationStationID - 1].setMinTime(tempEntityCount[jCount].getMinCostTime());
			//	m_pTimeSliceCountArray[iTargetStationID - 1][iRelationStationID - 1].setOperateTimes(tempEntityCount[jCount].getOperatedTimes());
			//}
		}

		/*delete tempEntityStationCount;
		delete tempEntityCount;*/
		return true;
	}

	/**
	 * 功能：将时间片统计集合进行计算，得出当前时间片对象的关系集合
	 * 传入：时间片统计集合（链表形式）,写入DAL层关系统计集合（链表形式）
	 * 传出：引用传出
	 * 调用条件：
	 */
	bool getRelation(CEntityTimeSliceCountNode *pEntityTimeSliceCountNode)
	{
		//得到时间片长度
		int iTimeSliceID = pEntityTimeSliceCountNode->getTimeSliceCount()->getTimeID();
		//得到该时间片数据中包含站点个数（这里的站点并不是全部存在）
		//得到借数组长度
		int iStationCount = pEntityTimeSliceCountNode->getTimeSliceCount()->getStationCount()->getRentArraySize();
		//得到该时间片数据中节点生存周期
		int iSurvivalTime = pEntityTimeSliceCountNode->getTimeSliceCount()->getSurvivalTime();
	
		CListRelationNode *pListRelationNode = new CListRelationNode();
		//设置关系数据二位数组参数
		pListRelationNode->getEntityRelationSet()->setTimeID(iTimeSliceID);
		pListRelationNode->getEntityRelationSet()->setStationNum(m_iTotalStationNum);
		pListRelationNode->setSurvivalTime(iSurvivalTime);

		//初始化关系数据二维数组
		pListRelationNode->getEntityRelationSet()->initRelationSet();

		//计算结果放入
		/*****************************这个计算应该没这么简单***********************************/
		//for(int iCount = 0; iCount < iStationCount; iCount++)
		//{
		//	//pEntityTimeSliceCountNode->getTimeSliceCount()->getStationCount()->getStationID();
		//	pListRelationNode->getEntityRelationSet()->insertStationRelation(iCount,);
		//	
		//}
		int iStationRelation = 0;
		//第一个站点
		for(int iCount = 0;iCount < m_iTotalStationNum; iCount++)
		 {
			 //第二个站点
			 for(int jCount = 0; jCount < m_iTotalStationNum; jCount++)
			 {
				 //第一个节点iCount 第二个节点jCount
				 if(iCount == jCount)
					//pListRelationNode->getEntityRelationSet()->insertStationRelation(iCount, jCount, 1);
					continue;
				 //若两个站点不为同一站点
				 else
				 {
					 /*if((iCount == 24 || iCount == 37 || iCount == 44 || iCount == 51 || iCount == 90)
						 && (jCount == 24 || jCount == 37 || jCount == 44 || jCount == 51 || jCount == 99))*/
					 //计算iCount和jCount两个节点之间的相似度
					 iStationRelation = calculateRelation(iCount, jCount);
					 pListRelationNode->getEntityRelationSet()->insertStationRelation(iCount, jCount, iStationRelation);
					 iStationRelation = 0;
				 }
				 //if(m_pTimesliceCountArray[iCount][jCount].getOperateTimes() == 0)
				 //calculateRelation(iCount, jCount);

				 //pListRelationNode->getEntityRelationSet()->insertStationRelation();
			 }
		 }

		//计算完成，插入主链
		m_pHeadListRelationSet->insertRelationNode(pListRelationNode);
		return true;
	}

	/**
	 * 功能：计算两个站点之间的相似度（两个站点不为同一个站点）
	 * 传入：第一个站点，第二个站点
	 * 传出：两个站点相似度
	 * 调用条件：
	 */
	int calculateRelation(int iFirstStation, int iSecondStation)
	{
		double iStationRelation = 0;
		int iMaxTime = 0;
		int iMinTime = 0;
		//iEveryCoupleRelationSum用于保存一次两个站点的关系站点之间的关系和
		double iEveryCoupleRelationSum = 0;
		//iPlusCount用于保存累加次数，在最后返回两个站点之间关系值得时候作为除数
		int iPlusCount = 0;

		//第一个站点时间片的差值
		int iFirstStationTimeD_value = 0;
		//关联站点之间的时间片重叠差值
		int iStationOverLapTimeD_value = 0;
		//第一个站点在的数据占在该站点换车的比例;
		double dRateOfStationCount = 0;

		//
		for(int iCount = 0; iCount < m_iTotalStationNum; iCount++)
		{
			//如果第一个站点的关系站点的操作数为0，表示该关系站点不需要考虑
			if(m_pTimeSliceCountArray[iFirstStation][iCount].getOperateTimes() == 0)
			{
				continue;
			}
			//关系站点需要考虑，得到第一个站点关系站点的一些数据，C和第一个站点的区间差值
			else
			{
				//获取第一个时间片最大最小区间的差值
				iFirstStationTimeD_value = m_pTimeSliceCountArray[iFirstStation][iCount].getMaxTime()
					- m_pTimeSliceCountArray[iFirstStation][iCount].getMinTime() + 1;
			
				//获取C的值
				for(int kCount = 0; kCount < m_iTotalStationNum; kCount++)
				{
					dRateOfStationCount = dRateOfStationCount + m_pTimeSliceCountArray[iFirstStation][kCount].getOperateTimes();
				}
				//得到C
				dRateOfStationCount = m_pTimeSliceCountArray[iFirstStation][iCount].getOperateTimes() / dRateOfStationCount;

			}

			//得到比较站点的数据
			for(int jCount = 0; jCount < m_iTotalStationNum; jCount++)
			{
				//若比较站点的操作数为0，不予比较
				if(m_pTimeSliceCountArray[iSecondStation][jCount].getOperateTimes() == 0)
					continue;

				//否则就获取两个的重叠时间片
				else
				{
					//获取第一个站点关系站点和第二个站点关系站点重叠时间片
					getOverLapTimes(m_pTimeSliceCountArray[iFirstStation][iCount], 
					m_pTimeSliceCountArray[iSecondStation][jCount], iMaxTime, iMinTime);

					if(iMaxTime != iMinTime)
					{
						//两个关联站点之间重叠时间片差值
						iStationOverLapTimeD_value = iMinTime - iMaxTime + 1;
					
						//iEveryCoupleRelationSum用于保存一次两个站点的关系站点之间的关系和
						//iPlusCount用于保存累加次数，在最后返回两个站点之间关系值得时候作为除数
						//计算当前重叠时间片中的重叠时间站点关系和
						for(int lCount = iMaxTime; lCount <= iMinTime; lCount++)
						{
							iEveryCoupleRelationSum = iEveryCoupleRelationSum + 
								getStationRelationOfNode(lCount, iFirstStation, iSecondStation) *
								iStationOverLapTimeD_value / iFirstStationTimeD_value * dRateOfStationCount;
							iPlusCount++;
						}
					}
					iStationRelation = iStationRelation + iEveryCoupleRelationSum;
					iEveryCoupleRelationSum = 0;
				}
			}

			dRateOfStationCount = 0;
		}
		if(iPlusCount == 0)
			return 0;
		else
			return (int)(iStationRelation / iPlusCount);
	}
	
	/**
	 * 功能：获取主链表中的关系集合内部的站点关系值
	 * 传入：时间片ID，目标站点，关联站点
	 * 传出：站点关系值
	 * 调用条件：
	 */
	int getStationRelationOfNode(int iTimeSlice, int iTargetStationID, int iRelationStationID)
	{
		//获取时间片站关系数据时，若主链表中没有数据时，或者数据输入错误
		if(m_pHeadListRelationSet->getNextRelationNode() == NULL || 
			m_pHeadListRelationSet->getNextRelationNode()->getEntityRelationSet()->getTimeID() < iTimeSlice)
			return 0;
		//获取数据
		else
		{
			CListRelationNode *tempListRelationNode = m_pHeadListRelationSet->getNextRelationNode();
			while(tempListRelationNode != NULL)
			{
				if(tempListRelationNode->getEntityRelationSet()->getTimeID() == iTimeSlice)
					return tempListRelationNode->getEntityRelationSet()->getStationRelation(	iTargetStationID, iRelationStationID);	
				else
					tempListRelationNode = tempListRelationNode->getNextRelationNode();
			}
			return 0;
		}
	}


	/**
	 * 功能：得到重叠时间片
	 * 传入：第一个站点，第二个站点，最小时间编号，最大时间编号
	 * 传出：引用传出最小时间编号，引用传出最大时间编号
	 * 调用条件：
	 */
	void getOverLapTimes(CBLLModelEntityTimeSliceCountArray iFirstCount, CBLLModelEntityTimeSliceCountArray iSecondCount, int &iMinTime, int &iMaxTime)
	{
		//如果两个站点均没有值,这个判断要需要再次修改
		if(iFirstCount.getMaxTime() == 0 && iSecondCount.getMaxTime() == 0)
		{
			iMinTime = 0;
			iMaxTime = 0;
		}
		//若第一个站点的最小时间大于第二个站点的最大时间，或者第一个最大时间小于第一个站点最小时间
		else if (iFirstCount.getMaxTime() < iSecondCount.getMinTime() || iFirstCount.getMinTime() > iSecondCount.getMaxTime())
		{
			iMinTime = 0;
			iMaxTime = 0;
		}
		//有效数据
		else 
		{
			//若第一个站点的最小比第二个站点最小大
			if(iFirstCount.getMaxTime() > iSecondCount.getMaxTime())
				iMaxTime = iSecondCount.getMaxTime();
			else
				iMaxTime = iFirstCount.getMaxTime();
			//若第一个站点的最大比第二个站点最大小
			if(iFirstCount.getMinTime() < iSecondCount.getMinTime())
				iMinTime = iSecondCount.getMinTime();
			else
				iMinTime = iFirstCount.getMinTime();
		}
	}
	
	/**
	 * 功能：将模型内部的时间片关系集合链表进行判断，若链表中存在生存周期小于model总体生存周期的，返回上层BLL控制类
	 * 传入：
	 * 传出：
	 * 调用条件：
	 */
	bool judgeSurvivalTime(CListWriteRelationSet *&pListWriteRelationSet)
	{
		//记录提取节点个数
		int iStationCount = 0;
		//新建一个关系集合指针，并赋初值为空
		CListRelationNode *pHeadListRelationNode = NULL;
		//若链表中有数据
		if(m_pHeadListRelationSet->getNodeNum() >= 0)
		{
			//将第一个节点赋值给新建的关系集合指针
			pHeadListRelationNode = m_pHeadListRelationSet->getNextRelationNode();

			//通过这个循环得到两种情况
			//1、整个链表都遍历，while不通过if跳出，所有生存周期都比当前生存周期小，所以链表都进行写入
			//2、部分链表，while通过if跳出
			while(pHeadListRelationNode != NULL)
			{
				//若节点中的生存周期大于当前生存周期
				if(pHeadListRelationNode->getSurvivalTime() > m_iTotalSurvivalTime)
				{
					//跳出循环
					//pHeadListRelationNode = pHeadListRelationNode->getNextRelationNode();
					break;
				} else {
					//将指针向下移位,并将提取节点数累加
					pHeadListRelationNode = pHeadListRelationNode->getNextRelationNode();
					iStationCount++;
				}
			}
		} else {
			AfxMessageBox(_T("主链表中节点个数不能为负值"));
		}

		//判断写入链表完成，进行链表格式转换
		turnToListWriteRelationSet(iStationCount, pListWriteRelationSet);

		//释放内存
		delete pHeadListRelationNode;
		return true;
	}

	/**
	 * 功能：将内存模型中的链表形式转换成可以传入DAL层的链表形式（即将ListRelationSet 转换成ListWriteRelationSet）
	 * 传入：内存模型中链表读取个数（int），（引用传入）传入DAL层链表（链表形式）
	 * 传出：（引用传出）传入DAL层链表（链表形式）
	 * 调用条件：
	 */
	bool turnToListWriteRelationSet(int iNodeNum, CListWriteRelationSet *&pListWriteRelationSet)
	{
	
		//m_objBufferPool->mallocWriteRelationNode();
		//这里需要缓冲池         
		/*******************************缓冲池*************************************/
		
		//CListWriteRelationNode *pListWriteRelationNode = new CListWriteRelationNode();
		
		CListRelationNode *pListRelationNode = m_pHeadListRelationSet->getNextRelationNode();
		for(int iCount = 0; iCount < iNodeNum; iCount++)
		{
			//CListWriteRelationNode *pListWriteRelationNode = m_objBufferPool->getWriteRelationNode();
			m_pBufferPool->mallocWriteRelationNode();
			CListWriteRelationNode *pListWriteRelationNode = m_pBufferPool->getWriteRelationNode();
			//设置关系集合,并进行关系集合初始化
			pListWriteRelationNode->getEntityRelationSet()->setStationNum(m_iTotalStationNum);
			pListWriteRelationNode->getEntityRelationSet()->initRelationSet();
			//设置时间片ID
			pListWriteRelationNode->getEntityRelationSet()->setTimeID(pListRelationNode->getEntityRelationSet()->getTimeID());
			//设置关系集合
			pListWriteRelationNode->setEntityRelationSet(pListRelationNode->getEntityRelationSet());
			

			//插入到传入DAL层链表
			pListWriteRelationSet->insertRelationSet(pListWriteRelationNode);
			//推到下一个内存关系对象
			pListRelationNode = pListRelationNode->getNextRelationNode();
		}
		//减去写入DAL层的节点个数，重新保存节点数
		m_pHeadListRelationSet->setNodeNum(m_pHeadListRelationSet->getNodeNum() - iNodeNum);

		CListRelationNode *pTempRelationNode = m_pHeadListRelationSet->getNextRelationNode();
		while(iNodeNum > 0)
		{
			pTempRelationNode = pTempRelationNode->getNextRelationNode();
			iNodeNum--;
		}
		m_pHeadListRelationSet->setFirstListRelationNode(pTempRelationNode);
		return true;
	}

private:
	//总体生存周期
	int m_iTotalSurvivalTime;
	//模型内部时间片关系集合链表
	CListRelationSet *m_pHeadListRelationSet;
	//缓冲池对象
	CBufferPoolBLL *m_pBufferPool;
	//总站点个数
	int m_iTotalStationNum;
	////结构体二维数组
	//structSet **m_pStructSet;
	CBLLModelEntityTimeSliceCountArray **m_pTimeSliceCountArray;
};

