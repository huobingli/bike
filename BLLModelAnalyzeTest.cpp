#include "stdafx.h"
#include "BLLModelAnalyzeTest.h"
#include"FrameDAL.h"

CBLLModelAnalyzeTest::CBLLModelAnalyzeTest(int iStationNum)
{
	m_iTotalStationNum = iStationNum;
	m_iTotalSurvivalNum = 0;

	m_pHeadListRelationSet = new CListRelationSet();
	m_pTimeSliceCountArray = NULL;
	m_pMaxMinTestArray = NULL;

	m_pModelEntityRelationArray = NULL;

	m_pModelEntityStationArray = NULL;
}

CBLLModelAnalyzeTest::~CBLLModelAnalyzeTest()
{
	delete m_pHeadListRelationSet;
	m_pHeadListRelationSet = NULL;
}

void CBLLModelAnalyzeTest::initMaxMinArray(){

	m_pMaxMinTestArray = new CBLLModelEntityMaxMinTestArray[m_iTotalStationNum];
	//初始化记录数组
	for (int iCount = 0; iCount < m_iTotalStationNum; iCount++){
		m_pMaxMinTestArray[iCount].setMaxStationRelation(0);
		m_pMaxMinTestArray[iCount].setMinStationRelation(0);
	}
}

void CBLLModelAnalyzeTest::releaseMaxMinArray(){
	delete[]m_pMaxMinTestArray;
}

//初始化数组
void CBLLModelAnalyzeTest::initArray(){
	m_pTimeSliceCountArray = new CBLLModelEntityTimeSliceCountArray*[m_iTotalStationNum];
	for (int iCount = 0; iCount < m_iTotalStationNum; iCount++){
		m_pTimeSliceCountArray[iCount] = new CBLLModelEntityTimeSliceCountArray[m_iTotalStationNum];
	}

	//初始化二维数组
	for (int iCount = 0; iCount < m_iTotalStationNum; iCount++){
		for (int jCount = 0; jCount < m_iTotalStationNum; jCount++)
		{
			m_pTimeSliceCountArray[iCount][jCount].setMaxTime(0);
			m_pTimeSliceCountArray[iCount][jCount].setMinTime(0);
			m_pTimeSliceCountArray[iCount][jCount].setOperateTimes(0);
		}
	}
}

void CBLLModelAnalyzeTest::setRelationSet(CListRelationNode *&pListRelationNode) {
	double *pTempArray = NULL;
	pTempArray = new double[m_iTotalStationNum];
	int iTempTotalOperNum;
	for (int iCount = 0; iCount < m_iTotalStationNum; iCount++)
	{
		pTempArray[iCount] = 0;
	}
	for (int iCount = 0; iCount < m_iTotalStationNum; iCount++)
	{
		iTempTotalOperNum = 0;
		for (int jCount = 0; jCount < m_iTotalStationNum; jCount++)
		{
			iTempTotalOperNum = iTempTotalOperNum + m_pTimeSliceCountArray[iCount][jCount].getOperateTimes();
		}
		pTempArray[iCount] = iTempTotalOperNum;
	}
	double iRelation;
	for (int iCount = 0; iCount < m_iTotalStationNum; iCount++)
	{
		for (int jCount = 0; jCount < m_iTotalStationNum; jCount++)
		{
			if (pTempArray[iCount] != 0)
			{
				iRelation = (m_pTimeSliceCountArray[iCount][jCount].getOperateTimes() * 100) / (pTempArray[iCount]);
				if (iRelation != 0)
					pListRelationNode->getEntityRelationSet()->insertStationRelation(iCount, jCount, iRelation);
			}
		}
	}
}

//释放数组
void CBLLModelAnalyzeTest::releaseArray(){
	for (int iCount = 0; iCount < m_iTotalStationNum; iCount++){
		delete[] m_pTimeSliceCountArray[iCount];
		m_pTimeSliceCountArray[iCount] = NULL;
	}
	delete[]m_pTimeSliceCountArray;
}


void CBLLModelAnalyzeTest::initRelationArray(){

	m_pModelEntityRelationArray = new CBLLModelEntityRelationArray[5000];
	//初始化记录数组
	for (int iCount = 0; iCount < 5000; iCount++){
		m_pModelEntityRelationArray[iCount].setTargetStation(0);
		m_pModelEntityRelationArray[iCount].setRelationStation(0);
		m_pModelEntityRelationArray[iCount].setStationRelation(0);
		m_pModelEntityRelationArray[iCount].setflag(0);
	}
}

void CBLLModelAnalyzeTest::releaseRelationArray(){
	delete[]m_pModelEntityRelationArray;
}


void CBLLModelAnalyzeTest::initStationArray(){

	m_pModelEntityStationArray = new CBLLModelEntityStationArray[300];
	//初始化记录数组
	for (int iCount = 0; iCount < 300; iCount++){
		m_pModelEntityStationArray[iCount].setStationID(iCount);
		m_pModelEntityStationArray[iCount].setFlag(0);
	}
}

void CBLLModelAnalyzeTest::releaseStationArray(){
	delete[]m_pModelEntityStationArray;
}

//开始分析
bool CBLLModelAnalyzeTest::startAnalyze(CEntityTimeSliceCountSet *pEntityTimeSliceCountSet, CListWriteRelationSet *&pListWriteRelationSet){

	int iTime = 0;
	if (pEntityTimeSliceCountSet->getHeadTimeSliceCountNode()->getTimeSliceCount()->getTimeID() != 6795 &&
		pEntityTimeSliceCountSet->getHeadTimeSliceCountNode()->getTimeSliceCount()->getTimeID() != 6796)
		return false;
	/*if (pEntityTimeSliceCountSet->getHeadTimeSliceCountNode()->getTimeSliceCount()->getTimeID() == 3650)
		return false;*/
	//判断传入
	if (pEntityTimeSliceCountSet == NULL)
	{
		AfxMessageBox(_T("传入不能为空"));
		return false;
	}
	//传入不为空
	else
	{
		CEntityTimeSliceCountNode *tempTimeSliceCountNode;

		//获取第一个节点， 其实每次进来也就一个数据
		tempTimeSliceCountNode = pEntityTimeSliceCountSet->getHeadTimeSliceCountNode();

		while (tempTimeSliceCountNode != NULL)
		{
			//初始化model中内存结构数组
			initArray();
			//将数据读入model中的内存结构中
			copyEntityTimeSliceCountNode(tempTimeSliceCountNode);
			//如果model中主链表为空，插入第一个矩阵，对角线为0，其余为100
			if (m_pHeadListRelationSet->getNextRelationNode() == NULL)
			{
				//获得节点参数
				int iTimeSliceID = tempTimeSliceCountNode->getTimeSliceCount()->getTimeID();
				int iStationCount = tempTimeSliceCountNode->getTimeSliceCount()->getStationCount()->getRentArraySize();
				int iSurvivalNum = getSurvivalNum(tempTimeSliceCountNode->getTimeSliceCount()->getSurvivalTime());

				//创建关系数据节点
				CListRelationNode *pListRelationNode = new CListRelationNode();
				//设置关系数据参数
				pListRelationNode->getEntityRelationSet()->setTimeID(iTimeSliceID);
				pListRelationNode->getEntityRelationSet()->setStationNum(m_iTotalStationNum);
				pListRelationNode->setSurvivalTime(iSurvivalNum);
				pListRelationNode->getEntityRelationSet()->initRelationSet();

				//设置第一个数组参数
				for (int iCount = 0; iCount < m_iTotalStationNum; iCount++)
				{
					for (int jCount = 0; jCount < m_iTotalStationNum; jCount++)
					{
						if (iCount == jCount)
							pListRelationNode->getEntityRelationSet()->insertStationRelation(iCount, jCount, 100);
						else
							pListRelationNode->getEntityRelationSet()->insertStationRelation(iCount, jCount, 0);
					}
				}

				//setRelationSet(pListRelationNode);

				//插入节点
				m_pHeadListRelationSet->insertRelationNode(pListRelationNode);

				//下个准备处理节点
				tempTimeSliceCountNode = tempTimeSliceCountNode->getNextTimeSliceCountNode();

				//检测输出
				/*CFrameDAL *pDAL = new CFrameDAL();
				string strTimeSliceCountSet = changeToStringstream();
				char* cstr = (char*)strTimeSliceCountSet.c_str();
				pDAL->writeStdFile(cstr);*/

				//检测输出
				/*CFrameDAL *pDAL = new CFrameDAL();
				string strTimeSliceCountSet = m_pHeadListRelationSet->changeToStringstream();
				char* cstr = (char*)strTimeSliceCountSet.c_str();
				pDAL->writeStdFile(cstr);*/

				m_iTotalSurvivalNum++;
				releaseArray();
				continue;
			}
			else
			{
				//创建写入节点
				CListRelationNode *pListRelationNode = new CListRelationNode();
				iTime = 0;
				//处理集合

				//记录每次测试max、min值
				initMaxMinArray();

				double iMaxRelation = 0;
				double iMinRelation = 0;

				//迭代iTime次
				while (iTime < 20)
				{
					iTime++;
					//第一次计算
					if (iTime == 1)
					{
						//初始化最大最小
						iMinRelation = 100;
						iMaxRelation = 0;
						getRelation(tempTimeSliceCountNode, pListRelationNode, iMaxRelation, iMinRelation);
						m_pMaxMinTestArray[iTime - 1].setMaxStationRelation(iMaxRelation);
						m_pMaxMinTestArray[iTime - 1].setMinStationRelation(iMinRelation);
					}
					//不是第一次，进行迭代计算
					else
					{
						iMinRelation = 100;
						iMaxRelation = 0;
						iteratorGetRelation(pListRelationNode, iMaxRelation, iMinRelation);
						m_pMaxMinTestArray[iTime - 1].setMaxStationRelation(iMaxRelation);
						m_pMaxMinTestArray[iTime - 1].setMinStationRelation(iMinRelation);
					}
				
				//检测输出相似度关系
				//CFrameDAL *pDAL = new CFrameDAL();
				////输出checkFile
				//string strTimeSliceCountSet = pListRelationNode->getEntityRelationSet()->changeToStringstream();
				//char* cstr = (char*)strTimeSliceCountSet.c_str();
				//pDAL->writeStdFile(cstr);
				}
				CFrameDAL *pDAL = new CFrameDAL();
				//输出checkFile
				string strTimeSliceCountSet = pListRelationNode->getEntityRelationSet()->changeToStringstream();
				char* cstr = (char*)strTimeSliceCountSet.c_str();
				pDAL->writeStdFile(cstr);

				//输出MaxMinArray最大最小数组
				/*CFrameDAL *pDAL = new CFrameDAL();
				string strMaxMinArray = printMaxMinArray();
				char* cstr1 = (char*)strMaxMinArray.c_str();
				pDAL->writeMaxMinStdFile(cstr1);*/

				//输出TimeSLiceArray
				/*CFrameDAL *pDAL = new CFrameDAL();
				string strMaxMinArray = printArray();
				char* cstr1 = (char*)strMaxMinArray.c_str();
				pDAL->writeMaxMinStdFile(cstr1);*/
					
				releaseMaxMinArray();

				//收集大于某个关系数值的数据
				initRelationArray();

				//获得大于指标线的数据
				for (int iCount = 70; iCount > -1; iCount = iCount - 10)
					double number = getRelationOver60(pListRelationNode, iCount);

				//初始化
				initStationArray();
				//得到聚类集合
				getCluster();
				//输出聚类集合
				//CFrameDAL *pDAL = new CFrameDAL();
				string strClusterSet = printClusterArray();
				char* cstr2 = (char*)strClusterSet.c_str();
				pDAL->writeClusterStdFile(cstr2);
				//释放
				releaseStationArray();

				//得到邻接矩阵
				//getRelationMatrix();

				//CFrameDAL *pDAL = new CFrameDAL();
				//输出checkFile
				string strTimeSliceCountSet2 = printRelationArray();
				char* cstr3 = (char*)strTimeSliceCountSet2.c_str();
				pDAL->writeRelationStdFile(cstr3);
				//释放数组
				releaseRelationArray();


				//将关系矩阵插入数据库
				//insertMatrixIntoMysql(pListRelationNode);

				//调整生存周期
				int iFirstTime = tempTimeSliceCountNode->getTimeSliceCount()->getTimeID();
				int iSecondTime = m_pHeadListRelationSet->getNextRelationNode()->getNextRelationNode()->getEntityRelationSet()->getTimeID();
				//完成生存周期调整
				m_iTotalSurvivalNum = m_iTotalSurvivalNum + iFirstTime - iSecondTime;

				//检测输出
				/*CFrameDAL *pDAL = new CFrameDAL();
				string strTimeSliceCountSet = m_pHeadListRelationSet->changeToStringstream();
				char* cstr = (char*)strTimeSliceCountSet.c_str();
				pDAL->writeStdFile(cstr);*/

				//下个准备处理节点
				tempTimeSliceCountNode = tempTimeSliceCountNode->getNextTimeSliceCountNode();
				releaseArray();
				continue;
			}
			//处理一个就将总体生存周期进行自增
			//m_iTotalSurvivalTime++;

		}
		//judgeSurvivalTime(pListWriteRelationSet);
		//清空临时变量
		delete tempTimeSliceCountNode;
		tempTimeSliceCountNode = NULL;
		return true;
	}
}

//拷贝时间片关系到模型内部数组
bool CBLLModelAnalyzeTest::copyEntityTimeSliceCountNode(CEntityTimeSliceCountNode *pEntityTimeSliceCountNode){
	//写入站点数目
	int iArrayNum = pEntityTimeSliceCountNode->getTimeSliceCount()->getArraySize();
	int iRentArraySize = 0;//pEntityTimeSliceCountNode->getTimeSliceCount()->getStationCount()->getRentArraySize();
	int iReturnArraySize = 0;//pEntityTimeSliceCountNode->getTimeSliceCount()->getStationCount()->getReturnArraySize();

	int iTargetStationID = 0;
	int iRelationStationID = 0;

	CEntityStationCount *tempEntityStationCount = NULL;
	CEntityCount *tempEntityCount = NULL;

	//外层循环是EntityTimeSliceCount数组的有效个数
	for (int iCount = 0; iCount < iArrayNum; iCount++)
	{
		//获取统计集合内站点统计对象指针
		tempEntityStationCount = pEntityTimeSliceCountNode->getTimeSliceCount()->getStationCount();
		iRentArraySize = tempEntityStationCount[iCount].getRentArraySize();
		iReturnArraySize = tempEntityStationCount[iCount].getReturnArraySize();

		iTargetStationID = tempEntityStationCount[iCount].getStationID();
		//内层循环是EntityStationCount数组的有效个数
		//for(int jCount = 0; jCount < iRentArraySize; jCount++)
		//{
		//	//获取统计集合内站点统计对象内的借车对象数组指针
		//	tempEntityCount = tempEntityStationCount[iCount].getRentCount();
		//	iRelationStationID = tempEntityCount[jCount].getRelatedStationID();
		//		
		//	m_pTimeSliceCountArray[iTargetStationID - 1][iRelationStationID - 1].setMaxTime(tempEntityCount[jCount].getMaxCostTime());
		//	m_pTimeSliceCountArray[iTargetStationID - 1][iRelationStationID - 1].setMinTime(tempEntityCount[jCount].getMinCostTime());
		//	m_pTimeSliceCountArray[iTargetStationID - 1][iRelationStationID - 1].setOperateTimes(tempEntityCount[jCount].getOperatedTimes());
		//}

		//还车部分
		for (int jCount = 0; jCount < iReturnArraySize; jCount++)
		{
			//获取统计集合内站点统计对象内的还车对象数组指针
			tempEntityCount = tempEntityStationCount[iCount].getReturnCount();
			iRelationStationID = tempEntityCount[jCount].getRelatedStationID();

			m_pTimeSliceCountArray[iTargetStationID][iRelationStationID].setMaxTime((tempEntityCount[jCount].getMaxCostTime()) / 120 + 6795);
			m_pTimeSliceCountArray[iTargetStationID][iRelationStationID].setMinTime((tempEntityCount[jCount].getMinCostTime()) / 120 + 6795);
			m_pTimeSliceCountArray[iTargetStationID][iRelationStationID].setOperateTimes(tempEntityCount[jCount].getOperatedTimes());
		}
	}
	/*delete tempEntityStationCount;
	delete tempEntityCount;*/
	return true;
}

//得到关系节点
bool CBLLModelAnalyzeTest::getRelation(CEntityTimeSliceCountNode *pEntityTimeSliceCountNode, CListRelationNode *&pListRelationNode, double &dMaxRelation, double &dMinRelation){
	//double iMaxRelation = 0;
	//得到时间片长度
	int iTimeSliceID = pEntityTimeSliceCountNode->getTimeSliceCount()->getTimeID();
	//得到该时间片数据中包含站点个数（这里的站点并不是全部存在）
	//得到借数组长度
	int iStationCount = pEntityTimeSliceCountNode->getTimeSliceCount()->getStationCount()->getReturnArraySize();
	//得到该时间片数据中节点生存周期
	int iSurvivalNum = getSurvivalNum(pEntityTimeSliceCountNode->getTimeSliceCount()->getSurvivalTime());

	//CListRelationNode *pListRelationNode = new CListRelationNode();
	//设置关系数据二位数组参数
	pListRelationNode->getEntityRelationSet()->setTimeID(iTimeSliceID);
	pListRelationNode->getEntityRelationSet()->setStationNum(m_iTotalStationNum);
	pListRelationNode->setSurvivalTime(iSurvivalNum);

	//初始化关系数据二维数组
	pListRelationNode->getEntityRelationSet()->initRelationSet();

	//以第一个站点为基准记录最大关系记录
	//double dMaxStationRelation[200];
	//int iMaxStationRelationNum = 0;
	////初始化最大关系记录
	//for (int iCount = 0; iCount < m_iTotalStationNum; iCount++)
	//	dMaxStationRelation[iCount] = 0;

	//得到各个站点相似度关系
	double iStationRelation = 0;
	//第一个站点
	for (int iCount = 0; iCount < m_iTotalStationNum; iCount++)
	{
		//第二个站点
		for (int jCount = 0; jCount < m_iTotalStationNum; jCount++)
		{
			//第一个节点iCount 第二个节点jCount
			if (iCount == jCount)
			{
				//pListRelationNode->getEntityRelationSet()->insertStationRelation(iCount, jCount, 1);
				continue;
			}
			//若两个站点不为同一站点
			else
			{
				//计算iCount和jCount两个节点之间的相似度
				iStationRelation = calculateRelation(iCount, jCount);
				if (iStationRelation > dMaxRelation)
				{
					dMaxRelation = iStationRelation;
				}
				if (iStationRelation < dMinRelation)
				{
					dMinRelation = iStationRelation;
				}
				pListRelationNode->getEntityRelationSet()->insertStationRelation(iCount, jCount, iStationRelation);
				iStationRelation = 0;
			}
		}
	}
	CEntityRelationSet *pEntityRelationSet = pListRelationNode->getEntityRelationSet();
	//归一化
	//NormalizeMatrix(pEntityRelationSet, dMaxRelation);
	//delete pEntityRelationSet;
	//计算完成，插入主链
	//m_pHeadListRelationSet->insertRelationNode(pListRelationNode);
	return true;
}

//计算两个站点关联关系
double CBLLModelAnalyzeTest::calculateRelation(int iFirstStation, int iSecondStation){
	double dStationRelation = 0;
	//int iMaxTime = 0;
	//int iMinTime = 0;
	//iEveryCoupleRelationSum用于保存一次两个站点的关系站点之间的关系和
	double dEveryCoupleRelationSum = 0;
	//iPlusCount用于保存累加次数，在最后返回两个站点之间关系值得时候作为除数
	//double iPlusCount = 0;
	//double dFirstStationOperateNum = 0;
	//double dSecondStationOperateNum = 0;
	
	//第一个站点时间片的差值
	//double iFirstStationTimeD_value = 0;
	//关联站点之间的时间片重叠差值
	//double iStationOverLapTimeD_value = 0;
	//第一个站点在的数据占在该站点换车的比例;
	//double dRateOfStationCount = 0;
	double dFirstStationRelationNum = 0;
	double dBaseMaxRelation = 0;
	//以第一个站点为基准记录最大关系记录
	double dMaxStationRelation[700];
	int iRelationNum = 0;
	//初始化最大关系记录
	for (int iCount = 0; iCount < m_iTotalStationNum; iCount++)
		dMaxStationRelation[iCount] = 0;

	//以第一个站点为基准，将与第一站点的所有关联站点的关系的最大值获取，放入dMaxStationRelation
	for (int iCount = 0; iCount < m_iTotalStationNum; iCount++)
	{
		//如果第一个站点的关系站点的操作数为0，表示该关系站点不需要考虑
		if (m_pTimeSliceCountArray[iFirstStation][iCount].getOperateTimes() == 0)
		{
			continue;
		}
		//关系站点需要考虑，得到第一个站点关系站点的一些数据，C和第一个站点的区间差值
		else
		{
			dFirstStationRelationNum++;
			//dFirstStationOperateNum = dFirstStationOperateNum + m_pTimeSliceCountArray[iFirstStation][iCount].getOperateTimes();
			//获取第一个时间片最大最小区间的差值
			/*iFirstStationTimeD_value = m_pTimeSliceCountArray[iFirstStation][iCount].getMaxTime()
				- m_pTimeSliceCountArray[iFirstStation][iCount].getMinTime() + 1;*/

			//获取C的值
			//for (int kCount = 0; kCount < m_iTotalStationNum; kCount++)
			//{
			//	dRateOfStationCount = dRateOfStationCount + m_pTimeSliceCountArray[iFirstStation][kCount].getOperateTimes();
			//}
			////得到C
			//dRateOfStationCount = ((double)m_pTimeSliceCountArray[iFirstStation][iCount].getOperateTimes()) / dRateOfStationCount;

			//得到比较站点的数据
			for (int jCount = 0; jCount < m_iTotalStationNum; jCount++)
			{
				//若比较站点的操作数为0，不予比较
				if (m_pTimeSliceCountArray[iSecondStation][jCount].getOperateTimes() == 0)
					continue;

				//如果操作次数不为0，就获取两个的重叠时间片，说明需要计算
				else
				{
					//dSecondStationOperateNum = dSecondStationOperateNum + m_pTimeSliceCountArray[iSecondStation][jCount].getOperateTimes();
					//获取第一个站点关系站点和第二个站点关系站点重叠时间片
					/*getOverLapTimes(m_pTimeSliceCountArray[iFirstStation][iCount],
						m_pTimeSliceCountArray[iSecondStation][jCount], iMaxTime, iMinTime);*/

					/*if (iMaxTime != iMinTime)
					{*/
					//两个关联站点之间重叠时间片差值
					//iStationOverLapTimeD_value = iMinTime - iMaxTime + 1;
					//iEveryCoupleRelationSum用于保存一次两个站点的关系站点之间的关系和
					//iPlusCount用于保存累加次数，在最后返回两个站点之间关系值得时候作为除数
					//计算当前重叠时间片中的重叠时间站点关系和
					/*for (int lCount = iMaxTime; lCount <= iMinTime; lCount++)
						{*/
					//获取没两个站点之间的关系
					dEveryCoupleRelationSum = getStationRelationOfNode(6795, iCount, jCount);
					//比较得到最大的站点关系，保存在dMaxStationRelation
					if (dEveryCoupleRelationSum > dBaseMaxRelation)
					{
						dBaseMaxRelation = dEveryCoupleRelationSum;
					}
					/*iStationOverLapTimeD_value / iFirstStationTimeD_value*/
					//iPlusCount = 1;
						//}
					//}
					//将每次的增加的数据清零
					//iEveryCoupleRelationSum = 0;
				}
			}	
			if (dBaseMaxRelation != 0)
			{
				dMaxStationRelation[iRelationNum] = dBaseMaxRelation;
				iRelationNum++;
			}
			dBaseMaxRelation = 0;
		}
		
		//C值清零
		//dRateOfStationCount = 0;
	}
	if (iRelationNum == 0 || dFirstStationRelationNum == 0)
		return 0;
	else{
		double iTotalStationRelation = 0;
		for (int iCount = 0; iCount < iRelationNum; iCount++)
		{
			iTotalStationRelation = iTotalStationRelation + dMaxStationRelation[iCount];
		}
		dStationRelation = iTotalStationRelation * 0.6/ dFirstStationRelationNum;
		return dStationRelation;
	}
}

//获得iTImeSlice时间片节点中某组关系值
double CBLLModelAnalyzeTest::getStationRelationOfNode(int iTimeSlice, int iTargetStationID, int iRelationStationID){
	//获取时间片站关系数据时，若主链表中没有数据时，或者数据输入错误
	if (m_pHeadListRelationSet->getNextRelationNode() == NULL ||
		m_pHeadListRelationSet->getNextRelationNode()->getEntityRelationSet()->getTimeID() < iTimeSlice)
		return 0;
	//获取数据
	else
	{
		CListRelationNode *tempListRelationNode = m_pHeadListRelationSet->getNextRelationNode();
		while (tempListRelationNode != NULL)
		{
			//循环匹配符合的时间片
			if (tempListRelationNode->getEntityRelationSet()->getTimeID() == iTimeSlice)
				return tempListRelationNode->getEntityRelationSet()->getStationRelation(iTargetStationID, iRelationStationID);
			else
				tempListRelationNode = tempListRelationNode->getNextRelationNode();
		}
		return 0;
	}
}

//获取重叠时间片
void CBLLModelAnalyzeTest::getOverLapTimes(CBLLModelEntityTimeSliceCountArray iFirstCount, CBLLModelEntityTimeSliceCountArray iSecondCount, int &iMinTime, int &iMaxTime){
	//如果两个站点均没有值,这个判断要需要再次修改
	if (iFirstCount.getMaxTime() == 0 && iSecondCount.getMaxTime() == 0)
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
		if (iFirstCount.getMaxTime() > iSecondCount.getMaxTime())
			iMaxTime = iSecondCount.getMaxTime();
		else
			iMaxTime = iFirstCount.getMaxTime();
		//若第一个站点的最大比第二个站点最大小
		if (iFirstCount.getMinTime() < iSecondCount.getMinTime())
			iMinTime = iSecondCount.getMinTime();
		else
			iMinTime = iFirstCount.getMinTime();
	}
}

//判断生存周期
bool CBLLModelAnalyzeTest::judgeSurvivalTime(CListWriteRelationSet *&pListWriteRelationSet){
	//记录提取节点个数
	int iStationCount = 0;
	//新建一个关系集合指针，并赋初值为空
	CListRelationNode *pHeadListRelationNode = NULL;
	//若链表中有数据
	if (m_pHeadListRelationSet->getNodeNum() >= 0)
	{
		//将第一个节点赋值给新建的关系集合指针
		pHeadListRelationNode = m_pHeadListRelationSet->getNextRelationNode();

		//通过这个循环得到两种情况
		//1、整个链表都遍历，while不通过if跳出，所有生存周期都比当前生存周期小，所以链表都进行写入
		//2、部分链表，while通过if跳出
		while (pHeadListRelationNode != NULL)
		{
			//若节点中的生存周期大于当前生存周期
			if (pHeadListRelationNode->getSurvivalTime() > m_iTotalSurvivalNum)
			{
				//跳出循环
				//pHeadListRelationNode = pHeadListRelationNode->getNextRelationNode();
				break;
			}
			else {
				//将指针向下移位,并将提取节点数累加
				pHeadListRelationNode = pHeadListRelationNode->getNextRelationNode();
				iStationCount++;
			}
		}
	}
	else {
		AfxMessageBox(_T("主链表中节点个数不能为负值"));
		return false;
	}
	//_CrtDumpMemoryLeaks();
	//_CrtDumpMemoryLeaks();
	//判断写入链表完成，进行链表格式转换
	if (iStationCount == 0)
		return true;
	else
	{
		turnToListWriteRelationSet(iStationCount, pListWriteRelationSet);
		return true;
	}
	//_CrtDumpMemoryLeaks();
	//释放内存
	//delete pHeadListRelationNode;
}

//转化为写入链表
bool CBLLModelAnalyzeTest::turnToListWriteRelationSet(int iNodeNum, CListWriteRelationSet *&pListWriteRelationSet){
	//检测输入
	//_CrtDumpMemoryLeaks();
	CListRelationNode *pListRelationNode = m_pHeadListRelationSet->getNextRelationNode();
	for (int iCount = 0; iCount < iNodeNum; iCount++)
	{
		//CListWriteRelationNode *pListWriteRelationNode = m_objBufferPool->getWriteRelationNode();
		//m_pBufferPool->mallocWriteRelationNode();
		CListWriteRelationNode *pListWriteRelationNode = new CListWriteRelationNode();//m_pBufferPool->getWriteRelationNode();

		//设置关系集合,并进行关系集合初始化
		pListWriteRelationNode->getEntityRelationSet()->setTimeID(pListRelationNode->getEntityRelationSet()->getTimeID());
		pListWriteRelationNode->getEntityRelationSet()->setStationNum(m_iTotalStationNum);
		pListWriteRelationNode->getEntityRelationSet()->initRelationSet();
		//_CrtDumpMemoryLeaks();
		//设置时间片ID

		//设置关系集合
		pListWriteRelationNode->setEntityRelationSet(pListRelationNode->getEntityRelationSet());

		//_CrtDumpMemoryLeaks();
		//插入到传入DAL层链表
		pListWriteRelationSet->insertRelationSet(pListWriteRelationNode);
		//推到下一个内存关系对象
		pListRelationNode = pListRelationNode->getNextRelationNode();

	}
	//检测输出
	//_CrtDumpMemoryLeaks();
	//减去写入DAL层的节点个数，重新保存节点数
	m_pHeadListRelationSet->setNodeNum(m_pHeadListRelationSet->getNodeNum() - iNodeNum);

	//_CrtDumpMemoryLeaks();
	//用来存放
	pListRelationNode = m_pHeadListRelationSet->getNextRelationNode();

	CListRelationNode *pListRelationLinkNode = NULL;
	//修正关系主链表
	if (iNodeNum == 1)
	{
		pListRelationLinkNode = pListRelationNode->getNextRelationNode();
		pListRelationNode->setNextRelationNode(NULL);
		delete pListRelationNode;
	}
	else
	{
		int iNodeCount = iNodeNum;
		CListRelationSet *pListRelationDeleteSet = new CListRelationSet();
		pListRelationDeleteSet->setFirstListRelationNode(pListRelationNode);
		/*CListRelationNode *pListRelationLinkNode = pTempRelationNode->getNextRelationNode();*/
		while (iNodeCount > 1)
		{

			pListRelationNode = pListRelationNode->getNextRelationNode();
			iNodeCount--;
		}
		pListRelationLinkNode = pListRelationNode->getNextRelationNode();
		pListRelationNode->setNextRelationNode(NULL);

		//_CrtDumpMemoryLeaks();
		pListRelationDeleteSet->releaseNode();

	}
	//检测释放
	//_CrtDumpMemoryLeaks();

	//设置主链表上的第一个数据节点
	//若主链表数据个数不为0则设置下个节点
	//否则设置为NULL
	if (m_pHeadListRelationSet->getNodeNum() != 0)
	{
		m_pHeadListRelationSet->setFirstListRelationNode(pListRelationLinkNode);
	}
	else
	{
		m_pHeadListRelationSet->setFirstListRelationNode(NULL);
	}
	return true;
}

//获取剩余模型内集合关系链表
bool CBLLModelAnalyzeTest::getRestRelationSet(CListWriteRelationSet *&pListWriteRelationSet){
	turnToListWriteRelationSet(m_pHeadListRelationSet->getNodeNum(), pListWriteRelationSet);
	return true;
}

//字符串输出
string CBLLModelAnalyzeTest::changeToStringstream(){
	stringstream strstreamCount;
	char* cLeft = "(";
	char* cBlank = ",";
	char* cRight = ")";
	/*将各个属性放进字符串*/
	strstreamCount << cLeft;
	for (int iCount = 0; iCount < m_iTotalStationNum; iCount++)
	{
		strstreamCount << cLeft;
		for (int jCount = 0; jCount < m_iTotalStationNum; jCount++)
		{
			strstreamCount << m_pTimeSliceCountArray[iCount][jCount].changeToStringstream() << cBlank;
		}
		strstreamCount << cRight;
	}

	strstreamCount << cRight;
	/*将stringstream转换成string*/
	string strCount(strstreamCount.str());

	return strCount;
}

//计算生存周期
int CBLLModelAnalyzeTest::getSurvivalNum(int iSurvivalTime){
	return (iSurvivalTime / 20 + 1);
}

//获得模型内集合关系链表
CListRelationSet* CBLLModelAnalyzeTest::getListRelationSet(){
	return m_pHeadListRelationSet;
}

//矩阵归100化
void CBLLModelAnalyzeTest::NormalizeMatrix(CEntityRelationSet *&pEntityRelationSet, double dNormalizeParameter){
	double iGetRelation = 0;
	double iWriteRelation = 0;
	dNormalizeParameter = dNormalizeParameter / 100;

	for (int iCount = 0; iCount < m_iTotalStationNum; iCount++)
	{
		for (int jCount = 0; jCount < m_iTotalStationNum; jCount++)
		{
			if (iCount == jCount)
				continue;
			else
			{
				iGetRelation = pEntityRelationSet->getStationRelation(iCount, jCount);
				iWriteRelation = iGetRelation / dNormalizeParameter;
				pEntityRelationSet->insertStationRelation(iCount, jCount, iWriteRelation);
			}
		}
	}
}


//迭代计算，pListRelationNode源于上一次计算，并在200次计算后输出到文件
void CBLLModelAnalyzeTest::iteratorGetRelation(CListRelationNode *&pListRelationNode, double &dMaxRelation, double &dMinRelation)
{
	//创建临时数据节点，并初始化
	CListRelationNode *tempListRelationNode = new CListRelationNode();

	//复制输入节点数据，后续并更新到输入节点，不修改临时节点数据，一次迭代完成，清空临时数据节点
	tempListRelationNode->copyListRelationNode(pListRelationNode);

	//double iMaxRelation = 0;
	double iStationRelation = 0;
	for (int iCount = 0; iCount < m_iTotalStationNum; iCount++)
	{
		for (int jCount = 0; jCount < m_iTotalStationNum; jCount++)
		{
			if (iCount == jCount)
			{
				//pListRelationNode->getEntityRelationSet()->insertStationRelation(iCount, jCount, 1);
				continue;
			}
			//若两个站点不为同一站点
			else
			{
				//计算iCount和jCount两个节点之间的相似度
				iStationRelation = calculateRelation(iCount, jCount, tempListRelationNode);
				if (iStationRelation > dMaxRelation)
				{
					dMaxRelation = iStationRelation;
				}
				if (iStationRelation < dMinRelation)
				{
					dMinRelation = iStationRelation;
				}
				pListRelationNode->getEntityRelationSet()->insertStationRelation(iCount, jCount, iStationRelation);
				iStationRelation = 0;
			}
		}
	}
	CEntityRelationSet *pEntityRelationSet = pListRelationNode->getEntityRelationSet();
	//归一化
	//NormalizeMatrix(pEntityRelationSet, dMaxRelation);

	//清空数据内存空间
	//delete pEntityRelationSet;
	delete tempListRelationNode;
}

/**
 * 功能：计算获得每两个站点之间的关联关系
 * 传入：第一站点，第二站点，迭代
 * 传出：
 */
double CBLLModelAnalyzeTest::calculateRelation(int iFirstStation, int iSecondStation, CListRelationNode *pListRelationNode)
{
	double dStationRelation = 0;
	//iEveryCoupleRelationSum用于保存一次两个站点的关系站点之间的关系和
	double dEveryCoupleRelationSum = 0;

	double dFirstStationRelationNum = 0;
	double dBaseMaxRelation = 0;
	//以第一个站点为基准记录最大关系记录
	double dMaxStationRelation[700];
	
	int iRelationNum = 0;
	//初始化最大关系记录
	for (int iCount = 0; iCount < m_iTotalStationNum; iCount++)
		dMaxStationRelation[iCount] = 0;

	//以第一个站点为基准，将与第一站点的所有关联站点的关系的最大值获取，放入dMaxStationRelation
	for (int iCount = 0; iCount < m_iTotalStationNum; iCount++)
	{
		//如果第一个站点的关系站点的操作数为0，表示该关系站点不需要考虑
		if (m_pTimeSliceCountArray[iFirstStation][iCount].getOperateTimes() == 0)
		{
			continue;
		}
		//关系站点需要考虑，得到第一个站点关系站点的一些数据，C和第一个站点的区间差值
		else
		{
			//用来控制除数，即第一个站点的出度
			dFirstStationRelationNum++;
			for (int jCount = 0; jCount < m_iTotalStationNum; jCount++)
			{
				//若比较站点的操作数为0，不予比较
				if (m_pTimeSliceCountArray[iSecondStation][jCount].getOperateTimes() == 0)
					continue;

				//否则就获取两个的重叠时间片
				else
				{
					dEveryCoupleRelationSum = pListRelationNode->getEntityRelationSet()->getStationRelation(iCount, jCount);
					//获得最大值
					if (dEveryCoupleRelationSum > dBaseMaxRelation)
					{
						dBaseMaxRelation = dEveryCoupleRelationSum;
					}
				}
			}
			if (dBaseMaxRelation != 0)
			{
				dMaxStationRelation[iRelationNum] = dBaseMaxRelation;
				iRelationNum++;
			}
			dBaseMaxRelation = 0;
		}	
	}
	if (iRelationNum == 0 || dFirstStationRelationNum == 0)
		return 0;
	else{
		double iTotalStationRelation = 0;
		for (int iCount = 0; iCount < iRelationNum; iCount++)
		{
			iTotalStationRelation = iTotalStationRelation + dMaxStationRelation[iCount];
		}
		dStationRelation = iTotalStationRelation * 0.6 / dFirstStationRelationNum;
		return dStationRelation;
	}
}


void CBLLModelAnalyzeTest::insertMatrixIntoMysql(CListRelationNode *pListRelationNode)
{
	CEntityRelationSet *tempEntityRelationSet = pListRelationNode->getEntityRelationSet();
	MYSQL *mysql;
	mysql = mysql_init(NULL);
	bool a = mysql_real_connect(mysql, "localhost", "root", "", "bicycledatasystem", 3306, NULL, 0);

	for (int iCount = 0; iCount < m_iTotalStationNum;iCount++)
	{
		for (int jCount = 0; jCount < m_iTotalStationNum; jCount++)
		{
			char sql[200];
			sprintf(sql, "insert into stationrelation(id, timesliceid, targetstation, relationstation, relation) values (%d, %d, %d, %d, %.3f)",
				iCount * 200 + jCount + 1, tempEntityRelationSet->getTimeID(), iCount + 1, jCount + 1, tempEntityRelationSet->getStationRelation(iCount,jCount));
			if (mysql_query(mysql, sql) != 0)
			{
				mysql_error(mysql);
			}
		}
	}
	mysql_close(mysql);
}


double CBLLModelAnalyzeTest::getRelationOver60(CListRelationNode *pListRelationNode, double iOverNum)
{
	CEntityRelationSet *tempEntityRelationSet = pListRelationNode->getEntityRelationSet();

	double lCount = 0;
	double dStationRelation = 0;
	for (int iCount = 0; iCount < m_iTotalStationNum; iCount++)
	{
		for (int jCount = 0; jCount < m_iTotalStationNum; jCount++)
		{
			if (iCount == jCount)
				continue;

			dStationRelation = tempEntityRelationSet->getStationRelation(iCount, jCount);
			//计算个数
			if (dStationRelation > iOverNum)
			{
				//用于输出
				/*m_pModelEntityRelationArray[lCount].setTargetStation(iCount);
				m_pModelEntityRelationArray[lCount].setRelationStation(jCount);
				m_pModelEntityRelationArray[lCount].setStationRelation(dStationRelation);*/
				lCount++;
			}
		}
	}
	return lCount;
}

//根据m_pModelEntityRelationArray通过搜索来获取
/*void CBLLModelAnalyzeTest::getRelationMatrix()
{
	//int iCount = 0;
	//得到第一个站点
	//while (iCount<5000){
	//	if (iStartStation != m_pModelEntityRelationArray[iCount].getTargetStation())
	//		iCount++;
	//	else if (iStartStation == m_pModelEntityRelationArray[iCount].getTargetStation())
	//	{
	//		break;
	//	}
	//	else
	//	{
	//		AfxMessageBox(_T("未找到其实站点"));
	//	}
	//}
	////如果找到站点，可以获得其iCount值，并做为树的根节点
	//treeNode *treeRoot;
	////写入根节点站点编号
	//treeRoot->iStationID = m_pModelEntityRelationArray[iCount].getTargetStation();
	//treeRoot->child = NULL;
	//treeRoot->brother = NULL;
	//treeRoot->relation = 0;
	////转为邻接矩阵
	////
	//createTree(treeRoot, iCount);

	//创建一个新的邻接矩阵
	matrixArray *matrixRelationArray = NULL;
	matrixRelationArray = (matrixArray *)malloc(500 * sizeof(matrixArray));

	//初始化邻接矩阵
	for (int iCount = 0; iCount < 500; iCount++)
	{
		matrixRelationArray[iCount].firstmatrixNode = NULL;
		matrixRelationArray[iCount].iStationID = 0;
	}

	//创建接收变量
	int iTargetStation = 0;
	int iRelationStation = 0;
	double dStationRelation = 0;

	int jCount = 0;
	int lCount = 0;

	bool flag = false;
	for(int iCount = 0; iCount < 300; iCount++)
	{
		//得到目标站点、关系站点
		iTargetStation = m_pModelEntityRelationArray[iCount].getTargetStation();
		iRelationStation = m_pModelEntityRelationArray[iCount].getRelationStation();
		dStationRelation = m_pModelEntityRelationArray[iCount].getStationRelation();
		if (iTargetStation == 0 && iRelationStation == 0 && dStationRelation == 0)
			break;
		
		//如果循环读取得到一个0值，说明不存在这个targetStation，需要新建
		for (lCount = 0; lCount < 500; lCount++)
		{
			if (matrixRelationArray[lCount].iStationID == iTargetStation)
			{
				flag = true;
				break;
			}
		}

		//flag为false
		if (flag == false)
		{
			matrixRelationArray[jCount].iStationID = iTargetStation;
			matrixRelationArray[jCount].firstmatrixNode = (matrixNode *)malloc(sizeof(matrixNode));
			matrixRelationArray[jCount].firstmatrixNode->iRelationID = iRelationStation;
			matrixRelationArray[jCount].firstmatrixNode->iStationRelation = dStationRelation;
			matrixRelationArray[jCount].firstmatrixNode->nextRelationStation = NULL;
			jCount++;
		}
		//flag为true,如果存在这个targetStation
		else
		{
			//定义临时节点变量，用于判断是否为写入位置以及用于保存写入位置
			matrixNode *tempNode = matrixRelationArray[lCount].firstmatrixNode;
			
			//寻找最后一个节点
			while (tempNode->nextRelationStation != NULL)
			{
				tempNode = tempNode->nextRelationStation;
			}
			
			tempNode->nextRelationStation = (matrixNode *)malloc(sizeof(matrixNode));

			tempNode = tempNode->nextRelationStation;
			tempNode->iRelationID = iRelationStation;
			tempNode->iStationRelation = dStationRelation;
			tempNode->nextRelationStation = NULL;
			//jCount++;

			//判断为置false
			flag = false;
		}
	}
}		*/



////转换为邻接矩阵
//treeNode* CBLLModelAnalyzeTest::createTree(treeNode* root, int iCount)
//{
//	treeNode *treeNode;
//	iCount++;
//	while (root->iStationID == m_pModelEntityRelationArray[iCount].getTargetStation())
//	{
//		createTree(root->child, iCount);
//		createTree(root->brother, iCount);
//		iCount++;
//	}
//}


//得到大于特定关系数据的聚类集合

//无论是targetStationID还是relationStationID都要加入到聚类中
//将两个
void CBLLModelAnalyzeTest::getCluster()
{
	int iTargetStation;
	int iRelationStation;
	int flag;
	int littleFlag;
	//用于控制聚类数
	int lCount = 0;
	//每次读取一行数据进行编号
	for (int iCount = 0; iCount < 300; iCount++)
	{
		//得到第一个站点的
		iTargetStation = m_pModelEntityRelationArray[iCount].getTargetStation();
		iRelationStation = m_pModelEntityRelationArray[iCount].getRelationStation();

		//如果目标站点的flag为0，说明未标记
		if (m_pModelEntityStationArray[iTargetStation].getFlag() == 0)
		{
			//设置flag编号
			m_pModelEntityStationArray[iTargetStation].setFlag(lCount + 1);//先设置为iCount
			lCount++;
			//获得flag编号，用于关联站点为空时需要赋值
			flag = m_pModelEntityStationArray[iTargetStation].getFlag();
		}
		else
		{
			//获得flag
			flag = m_pModelEntityStationArray[iTargetStation].getFlag();
		}

		//如果关系站点的flag为0，说明为标记
		if (m_pModelEntityStationArray[iRelationStation].getFlag() == 0)
		{
			//设置flag编号targetStation的flag编号
			m_pModelEntityStationArray[iRelationStation].setFlag(flag);
		}

		//说明关系站点已经被标记，所以取较小的那个flag来更新所有的其他关联站点
		else
		{
			if (flag > m_pModelEntityStationArray[iRelationStation].getFlag())
				//先获得原来的较小的flag值
				littleFlag = m_pModelEntityStationArray[iRelationStation].getFlag();
			else
				littleFlag = flag;
			//将较小的flag值赋值给其他关联站点
			int jCount = 0;
			while (jCount < 300)
			{
				if (m_pModelEntityStationArray[jCount].getFlag() == flag)
					m_pModelEntityStationArray[jCount].setFlag(littleFlag);
				jCount++;
			}
		}
		//iCount++; 
	}
}