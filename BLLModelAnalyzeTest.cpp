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
	//��ʼ����¼����
	for (int iCount = 0; iCount < m_iTotalStationNum; iCount++){
		m_pMaxMinTestArray[iCount].setMaxStationRelation(0);
		m_pMaxMinTestArray[iCount].setMinStationRelation(0);
	}
}

void CBLLModelAnalyzeTest::releaseMaxMinArray(){
	delete[]m_pMaxMinTestArray;
}

//��ʼ������
void CBLLModelAnalyzeTest::initArray(){
	m_pTimeSliceCountArray = new CBLLModelEntityTimeSliceCountArray*[m_iTotalStationNum];
	for (int iCount = 0; iCount < m_iTotalStationNum; iCount++){
		m_pTimeSliceCountArray[iCount] = new CBLLModelEntityTimeSliceCountArray[m_iTotalStationNum];
	}

	//��ʼ����ά����
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

//�ͷ�����
void CBLLModelAnalyzeTest::releaseArray(){
	for (int iCount = 0; iCount < m_iTotalStationNum; iCount++){
		delete[] m_pTimeSliceCountArray[iCount];
		m_pTimeSliceCountArray[iCount] = NULL;
	}
	delete[]m_pTimeSliceCountArray;
}


void CBLLModelAnalyzeTest::initRelationArray(){

	m_pModelEntityRelationArray = new CBLLModelEntityRelationArray[5000];
	//��ʼ����¼����
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
	//��ʼ����¼����
	for (int iCount = 0; iCount < 300; iCount++){
		m_pModelEntityStationArray[iCount].setStationID(iCount);
		m_pModelEntityStationArray[iCount].setFlag(0);
	}
}

void CBLLModelAnalyzeTest::releaseStationArray(){
	delete[]m_pModelEntityStationArray;
}

//��ʼ����
bool CBLLModelAnalyzeTest::startAnalyze(CEntityTimeSliceCountSet *pEntityTimeSliceCountSet, CListWriteRelationSet *&pListWriteRelationSet){

	int iTime = 0;
	if (pEntityTimeSliceCountSet->getHeadTimeSliceCountNode()->getTimeSliceCount()->getTimeID() != 6795 &&
		pEntityTimeSliceCountSet->getHeadTimeSliceCountNode()->getTimeSliceCount()->getTimeID() != 6796)
		return false;
	/*if (pEntityTimeSliceCountSet->getHeadTimeSliceCountNode()->getTimeSliceCount()->getTimeID() == 3650)
		return false;*/
	//�жϴ���
	if (pEntityTimeSliceCountSet == NULL)
	{
		AfxMessageBox(_T("���벻��Ϊ��"));
		return false;
	}
	//���벻Ϊ��
	else
	{
		CEntityTimeSliceCountNode *tempTimeSliceCountNode;

		//��ȡ��һ���ڵ㣬 ��ʵÿ�ν���Ҳ��һ������
		tempTimeSliceCountNode = pEntityTimeSliceCountSet->getHeadTimeSliceCountNode();

		while (tempTimeSliceCountNode != NULL)
		{
			//��ʼ��model���ڴ�ṹ����
			initArray();
			//�����ݶ���model�е��ڴ�ṹ��
			copyEntityTimeSliceCountNode(tempTimeSliceCountNode);
			//���model��������Ϊ�գ������һ�����󣬶Խ���Ϊ0������Ϊ100
			if (m_pHeadListRelationSet->getNextRelationNode() == NULL)
			{
				//��ýڵ����
				int iTimeSliceID = tempTimeSliceCountNode->getTimeSliceCount()->getTimeID();
				int iStationCount = tempTimeSliceCountNode->getTimeSliceCount()->getStationCount()->getRentArraySize();
				int iSurvivalNum = getSurvivalNum(tempTimeSliceCountNode->getTimeSliceCount()->getSurvivalTime());

				//������ϵ���ݽڵ�
				CListRelationNode *pListRelationNode = new CListRelationNode();
				//���ù�ϵ���ݲ���
				pListRelationNode->getEntityRelationSet()->setTimeID(iTimeSliceID);
				pListRelationNode->getEntityRelationSet()->setStationNum(m_iTotalStationNum);
				pListRelationNode->setSurvivalTime(iSurvivalNum);
				pListRelationNode->getEntityRelationSet()->initRelationSet();

				//���õ�һ���������
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

				//����ڵ�
				m_pHeadListRelationSet->insertRelationNode(pListRelationNode);

				//�¸�׼������ڵ�
				tempTimeSliceCountNode = tempTimeSliceCountNode->getNextTimeSliceCountNode();

				//������
				/*CFrameDAL *pDAL = new CFrameDAL();
				string strTimeSliceCountSet = changeToStringstream();
				char* cstr = (char*)strTimeSliceCountSet.c_str();
				pDAL->writeStdFile(cstr);*/

				//������
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
				//����д��ڵ�
				CListRelationNode *pListRelationNode = new CListRelationNode();
				iTime = 0;
				//������

				//��¼ÿ�β���max��minֵ
				initMaxMinArray();

				double iMaxRelation = 0;
				double iMinRelation = 0;

				//����iTime��
				while (iTime < 20)
				{
					iTime++;
					//��һ�μ���
					if (iTime == 1)
					{
						//��ʼ�������С
						iMinRelation = 100;
						iMaxRelation = 0;
						getRelation(tempTimeSliceCountNode, pListRelationNode, iMaxRelation, iMinRelation);
						m_pMaxMinTestArray[iTime - 1].setMaxStationRelation(iMaxRelation);
						m_pMaxMinTestArray[iTime - 1].setMinStationRelation(iMinRelation);
					}
					//���ǵ�һ�Σ����е�������
					else
					{
						iMinRelation = 100;
						iMaxRelation = 0;
						iteratorGetRelation(pListRelationNode, iMaxRelation, iMinRelation);
						m_pMaxMinTestArray[iTime - 1].setMaxStationRelation(iMaxRelation);
						m_pMaxMinTestArray[iTime - 1].setMinStationRelation(iMinRelation);
					}
				
				//���������ƶȹ�ϵ
				//CFrameDAL *pDAL = new CFrameDAL();
				////���checkFile
				//string strTimeSliceCountSet = pListRelationNode->getEntityRelationSet()->changeToStringstream();
				//char* cstr = (char*)strTimeSliceCountSet.c_str();
				//pDAL->writeStdFile(cstr);
				}
				CFrameDAL *pDAL = new CFrameDAL();
				//���checkFile
				string strTimeSliceCountSet = pListRelationNode->getEntityRelationSet()->changeToStringstream();
				char* cstr = (char*)strTimeSliceCountSet.c_str();
				pDAL->writeStdFile(cstr);

				//���MaxMinArray�����С����
				/*CFrameDAL *pDAL = new CFrameDAL();
				string strMaxMinArray = printMaxMinArray();
				char* cstr1 = (char*)strMaxMinArray.c_str();
				pDAL->writeMaxMinStdFile(cstr1);*/

				//���TimeSLiceArray
				/*CFrameDAL *pDAL = new CFrameDAL();
				string strMaxMinArray = printArray();
				char* cstr1 = (char*)strMaxMinArray.c_str();
				pDAL->writeMaxMinStdFile(cstr1);*/
					
				releaseMaxMinArray();

				//�ռ�����ĳ����ϵ��ֵ������
				initRelationArray();

				//��ô���ָ���ߵ�����
				for (int iCount = 70; iCount > -1; iCount = iCount - 10)
					double number = getRelationOver60(pListRelationNode, iCount);

				//��ʼ��
				initStationArray();
				//�õ����༯��
				getCluster();
				//������༯��
				//CFrameDAL *pDAL = new CFrameDAL();
				string strClusterSet = printClusterArray();
				char* cstr2 = (char*)strClusterSet.c_str();
				pDAL->writeClusterStdFile(cstr2);
				//�ͷ�
				releaseStationArray();

				//�õ��ڽӾ���
				//getRelationMatrix();

				//CFrameDAL *pDAL = new CFrameDAL();
				//���checkFile
				string strTimeSliceCountSet2 = printRelationArray();
				char* cstr3 = (char*)strTimeSliceCountSet2.c_str();
				pDAL->writeRelationStdFile(cstr3);
				//�ͷ�����
				releaseRelationArray();


				//����ϵ����������ݿ�
				//insertMatrixIntoMysql(pListRelationNode);

				//������������
				int iFirstTime = tempTimeSliceCountNode->getTimeSliceCount()->getTimeID();
				int iSecondTime = m_pHeadListRelationSet->getNextRelationNode()->getNextRelationNode()->getEntityRelationSet()->getTimeID();
				//����������ڵ���
				m_iTotalSurvivalNum = m_iTotalSurvivalNum + iFirstTime - iSecondTime;

				//������
				/*CFrameDAL *pDAL = new CFrameDAL();
				string strTimeSliceCountSet = m_pHeadListRelationSet->changeToStringstream();
				char* cstr = (char*)strTimeSliceCountSet.c_str();
				pDAL->writeStdFile(cstr);*/

				//�¸�׼������ڵ�
				tempTimeSliceCountNode = tempTimeSliceCountNode->getNextTimeSliceCountNode();
				releaseArray();
				continue;
			}
			//����һ���ͽ������������ڽ�������
			//m_iTotalSurvivalTime++;

		}
		//judgeSurvivalTime(pListWriteRelationSet);
		//�����ʱ����
		delete tempTimeSliceCountNode;
		tempTimeSliceCountNode = NULL;
		return true;
	}
}

//����ʱ��Ƭ��ϵ��ģ���ڲ�����
bool CBLLModelAnalyzeTest::copyEntityTimeSliceCountNode(CEntityTimeSliceCountNode *pEntityTimeSliceCountNode){
	//д��վ����Ŀ
	int iArrayNum = pEntityTimeSliceCountNode->getTimeSliceCount()->getArraySize();
	int iRentArraySize = 0;//pEntityTimeSliceCountNode->getTimeSliceCount()->getStationCount()->getRentArraySize();
	int iReturnArraySize = 0;//pEntityTimeSliceCountNode->getTimeSliceCount()->getStationCount()->getReturnArraySize();

	int iTargetStationID = 0;
	int iRelationStationID = 0;

	CEntityStationCount *tempEntityStationCount = NULL;
	CEntityCount *tempEntityCount = NULL;

	//���ѭ����EntityTimeSliceCount�������Ч����
	for (int iCount = 0; iCount < iArrayNum; iCount++)
	{
		//��ȡͳ�Ƽ�����վ��ͳ�ƶ���ָ��
		tempEntityStationCount = pEntityTimeSliceCountNode->getTimeSliceCount()->getStationCount();
		iRentArraySize = tempEntityStationCount[iCount].getRentArraySize();
		iReturnArraySize = tempEntityStationCount[iCount].getReturnArraySize();

		iTargetStationID = tempEntityStationCount[iCount].getStationID();
		//�ڲ�ѭ����EntityStationCount�������Ч����
		//for(int jCount = 0; jCount < iRentArraySize; jCount++)
		//{
		//	//��ȡͳ�Ƽ�����վ��ͳ�ƶ����ڵĽ賵��������ָ��
		//	tempEntityCount = tempEntityStationCount[iCount].getRentCount();
		//	iRelationStationID = tempEntityCount[jCount].getRelatedStationID();
		//		
		//	m_pTimeSliceCountArray[iTargetStationID - 1][iRelationStationID - 1].setMaxTime(tempEntityCount[jCount].getMaxCostTime());
		//	m_pTimeSliceCountArray[iTargetStationID - 1][iRelationStationID - 1].setMinTime(tempEntityCount[jCount].getMinCostTime());
		//	m_pTimeSliceCountArray[iTargetStationID - 1][iRelationStationID - 1].setOperateTimes(tempEntityCount[jCount].getOperatedTimes());
		//}

		//��������
		for (int jCount = 0; jCount < iReturnArraySize; jCount++)
		{
			//��ȡͳ�Ƽ�����վ��ͳ�ƶ����ڵĻ�����������ָ��
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

//�õ���ϵ�ڵ�
bool CBLLModelAnalyzeTest::getRelation(CEntityTimeSliceCountNode *pEntityTimeSliceCountNode, CListRelationNode *&pListRelationNode, double &dMaxRelation, double &dMinRelation){
	//double iMaxRelation = 0;
	//�õ�ʱ��Ƭ����
	int iTimeSliceID = pEntityTimeSliceCountNode->getTimeSliceCount()->getTimeID();
	//�õ���ʱ��Ƭ�����а���վ������������վ�㲢����ȫ�����ڣ�
	//�õ������鳤��
	int iStationCount = pEntityTimeSliceCountNode->getTimeSliceCount()->getStationCount()->getReturnArraySize();
	//�õ���ʱ��Ƭ�����нڵ���������
	int iSurvivalNum = getSurvivalNum(pEntityTimeSliceCountNode->getTimeSliceCount()->getSurvivalTime());

	//CListRelationNode *pListRelationNode = new CListRelationNode();
	//���ù�ϵ���ݶ�λ�������
	pListRelationNode->getEntityRelationSet()->setTimeID(iTimeSliceID);
	pListRelationNode->getEntityRelationSet()->setStationNum(m_iTotalStationNum);
	pListRelationNode->setSurvivalTime(iSurvivalNum);

	//��ʼ����ϵ���ݶ�ά����
	pListRelationNode->getEntityRelationSet()->initRelationSet();

	//�Ե�һ��վ��Ϊ��׼��¼����ϵ��¼
	//double dMaxStationRelation[200];
	//int iMaxStationRelationNum = 0;
	////��ʼ������ϵ��¼
	//for (int iCount = 0; iCount < m_iTotalStationNum; iCount++)
	//	dMaxStationRelation[iCount] = 0;

	//�õ�����վ�����ƶȹ�ϵ
	double iStationRelation = 0;
	//��һ��վ��
	for (int iCount = 0; iCount < m_iTotalStationNum; iCount++)
	{
		//�ڶ���վ��
		for (int jCount = 0; jCount < m_iTotalStationNum; jCount++)
		{
			//��һ���ڵ�iCount �ڶ����ڵ�jCount
			if (iCount == jCount)
			{
				//pListRelationNode->getEntityRelationSet()->insertStationRelation(iCount, jCount, 1);
				continue;
			}
			//������վ�㲻Ϊͬһվ��
			else
			{
				//����iCount��jCount�����ڵ�֮������ƶ�
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
	//��һ��
	//NormalizeMatrix(pEntityRelationSet, dMaxRelation);
	//delete pEntityRelationSet;
	//������ɣ���������
	//m_pHeadListRelationSet->insertRelationNode(pListRelationNode);
	return true;
}

//��������վ�������ϵ
double CBLLModelAnalyzeTest::calculateRelation(int iFirstStation, int iSecondStation){
	double dStationRelation = 0;
	//int iMaxTime = 0;
	//int iMinTime = 0;
	//iEveryCoupleRelationSum���ڱ���һ������վ��Ĺ�ϵվ��֮��Ĺ�ϵ��
	double dEveryCoupleRelationSum = 0;
	//iPlusCount���ڱ����ۼӴ���������󷵻�����վ��֮���ϵֵ��ʱ����Ϊ����
	//double iPlusCount = 0;
	//double dFirstStationOperateNum = 0;
	//double dSecondStationOperateNum = 0;
	
	//��һ��վ��ʱ��Ƭ�Ĳ�ֵ
	//double iFirstStationTimeD_value = 0;
	//����վ��֮���ʱ��Ƭ�ص���ֵ
	//double iStationOverLapTimeD_value = 0;
	//��һ��վ���ڵ�����ռ�ڸ�վ�㻻���ı���;
	//double dRateOfStationCount = 0;
	double dFirstStationRelationNum = 0;
	double dBaseMaxRelation = 0;
	//�Ե�һ��վ��Ϊ��׼��¼����ϵ��¼
	double dMaxStationRelation[700];
	int iRelationNum = 0;
	//��ʼ������ϵ��¼
	for (int iCount = 0; iCount < m_iTotalStationNum; iCount++)
		dMaxStationRelation[iCount] = 0;

	//�Ե�һ��վ��Ϊ��׼�������һվ������й���վ��Ĺ�ϵ�����ֵ��ȡ������dMaxStationRelation
	for (int iCount = 0; iCount < m_iTotalStationNum; iCount++)
	{
		//�����һ��վ��Ĺ�ϵվ��Ĳ�����Ϊ0����ʾ�ù�ϵվ�㲻��Ҫ����
		if (m_pTimeSliceCountArray[iFirstStation][iCount].getOperateTimes() == 0)
		{
			continue;
		}
		//��ϵվ����Ҫ���ǣ��õ���һ��վ���ϵվ���һЩ���ݣ�C�͵�һ��վ��������ֵ
		else
		{
			dFirstStationRelationNum++;
			//dFirstStationOperateNum = dFirstStationOperateNum + m_pTimeSliceCountArray[iFirstStation][iCount].getOperateTimes();
			//��ȡ��һ��ʱ��Ƭ�����С����Ĳ�ֵ
			/*iFirstStationTimeD_value = m_pTimeSliceCountArray[iFirstStation][iCount].getMaxTime()
				- m_pTimeSliceCountArray[iFirstStation][iCount].getMinTime() + 1;*/

			//��ȡC��ֵ
			//for (int kCount = 0; kCount < m_iTotalStationNum; kCount++)
			//{
			//	dRateOfStationCount = dRateOfStationCount + m_pTimeSliceCountArray[iFirstStation][kCount].getOperateTimes();
			//}
			////�õ�C
			//dRateOfStationCount = ((double)m_pTimeSliceCountArray[iFirstStation][iCount].getOperateTimes()) / dRateOfStationCount;

			//�õ��Ƚ�վ�������
			for (int jCount = 0; jCount < m_iTotalStationNum; jCount++)
			{
				//���Ƚ�վ��Ĳ�����Ϊ0������Ƚ�
				if (m_pTimeSliceCountArray[iSecondStation][jCount].getOperateTimes() == 0)
					continue;

				//�������������Ϊ0���ͻ�ȡ�������ص�ʱ��Ƭ��˵����Ҫ����
				else
				{
					//dSecondStationOperateNum = dSecondStationOperateNum + m_pTimeSliceCountArray[iSecondStation][jCount].getOperateTimes();
					//��ȡ��һ��վ���ϵվ��͵ڶ���վ���ϵվ���ص�ʱ��Ƭ
					/*getOverLapTimes(m_pTimeSliceCountArray[iFirstStation][iCount],
						m_pTimeSliceCountArray[iSecondStation][jCount], iMaxTime, iMinTime);*/

					/*if (iMaxTime != iMinTime)
					{*/
					//��������վ��֮���ص�ʱ��Ƭ��ֵ
					//iStationOverLapTimeD_value = iMinTime - iMaxTime + 1;
					//iEveryCoupleRelationSum���ڱ���һ������վ��Ĺ�ϵվ��֮��Ĺ�ϵ��
					//iPlusCount���ڱ����ۼӴ���������󷵻�����վ��֮���ϵֵ��ʱ����Ϊ����
					//���㵱ǰ�ص�ʱ��Ƭ�е��ص�ʱ��վ���ϵ��
					/*for (int lCount = iMaxTime; lCount <= iMinTime; lCount++)
						{*/
					//��ȡû����վ��֮��Ĺ�ϵ
					dEveryCoupleRelationSum = getStationRelationOfNode(6795, iCount, jCount);
					//�Ƚϵõ�����վ���ϵ��������dMaxStationRelation
					if (dEveryCoupleRelationSum > dBaseMaxRelation)
					{
						dBaseMaxRelation = dEveryCoupleRelationSum;
					}
					/*iStationOverLapTimeD_value / iFirstStationTimeD_value*/
					//iPlusCount = 1;
						//}
					//}
					//��ÿ�ε����ӵ���������
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
		
		//Cֵ����
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

//���iTImeSliceʱ��Ƭ�ڵ���ĳ���ϵֵ
double CBLLModelAnalyzeTest::getStationRelationOfNode(int iTimeSlice, int iTargetStationID, int iRelationStationID){
	//��ȡʱ��Ƭվ��ϵ����ʱ������������û������ʱ�����������������
	if (m_pHeadListRelationSet->getNextRelationNode() == NULL ||
		m_pHeadListRelationSet->getNextRelationNode()->getEntityRelationSet()->getTimeID() < iTimeSlice)
		return 0;
	//��ȡ����
	else
	{
		CListRelationNode *tempListRelationNode = m_pHeadListRelationSet->getNextRelationNode();
		while (tempListRelationNode != NULL)
		{
			//ѭ��ƥ����ϵ�ʱ��Ƭ
			if (tempListRelationNode->getEntityRelationSet()->getTimeID() == iTimeSlice)
				return tempListRelationNode->getEntityRelationSet()->getStationRelation(iTargetStationID, iRelationStationID);
			else
				tempListRelationNode = tempListRelationNode->getNextRelationNode();
		}
		return 0;
	}
}

//��ȡ�ص�ʱ��Ƭ
void CBLLModelAnalyzeTest::getOverLapTimes(CBLLModelEntityTimeSliceCountArray iFirstCount, CBLLModelEntityTimeSliceCountArray iSecondCount, int &iMinTime, int &iMaxTime){
	//�������վ���û��ֵ,����ж�Ҫ��Ҫ�ٴ��޸�
	if (iFirstCount.getMaxTime() == 0 && iSecondCount.getMaxTime() == 0)
	{
		iMinTime = 0;
		iMaxTime = 0;
	}
	//����һ��վ�����Сʱ����ڵڶ���վ������ʱ�䣬���ߵ�һ�����ʱ��С�ڵ�һ��վ����Сʱ��
	else if (iFirstCount.getMaxTime() < iSecondCount.getMinTime() || iFirstCount.getMinTime() > iSecondCount.getMaxTime())
	{
		iMinTime = 0;
		iMaxTime = 0;
	}
	//��Ч����
	else
	{
		//����һ��վ�����С�ȵڶ���վ����С��
		if (iFirstCount.getMaxTime() > iSecondCount.getMaxTime())
			iMaxTime = iSecondCount.getMaxTime();
		else
			iMaxTime = iFirstCount.getMaxTime();
		//����һ��վ������ȵڶ���վ�����С
		if (iFirstCount.getMinTime() < iSecondCount.getMinTime())
			iMinTime = iSecondCount.getMinTime();
		else
			iMinTime = iFirstCount.getMinTime();
	}
}

//�ж���������
bool CBLLModelAnalyzeTest::judgeSurvivalTime(CListWriteRelationSet *&pListWriteRelationSet){
	//��¼��ȡ�ڵ����
	int iStationCount = 0;
	//�½�һ����ϵ����ָ�룬������ֵΪ��
	CListRelationNode *pHeadListRelationNode = NULL;
	//��������������
	if (m_pHeadListRelationSet->getNodeNum() >= 0)
	{
		//����һ���ڵ㸳ֵ���½��Ĺ�ϵ����ָ��
		pHeadListRelationNode = m_pHeadListRelationSet->getNextRelationNode();

		//ͨ�����ѭ���õ��������
		//1����������������while��ͨ��if�����������������ڶ��ȵ�ǰ��������С��������������д��
		//2����������whileͨ��if����
		while (pHeadListRelationNode != NULL)
		{
			//���ڵ��е��������ڴ��ڵ�ǰ��������
			if (pHeadListRelationNode->getSurvivalTime() > m_iTotalSurvivalNum)
			{
				//����ѭ��
				//pHeadListRelationNode = pHeadListRelationNode->getNextRelationNode();
				break;
			}
			else {
				//��ָ��������λ,������ȡ�ڵ����ۼ�
				pHeadListRelationNode = pHeadListRelationNode->getNextRelationNode();
				iStationCount++;
			}
		}
	}
	else {
		AfxMessageBox(_T("�������нڵ��������Ϊ��ֵ"));
		return false;
	}
	//_CrtDumpMemoryLeaks();
	//_CrtDumpMemoryLeaks();
	//�ж�д��������ɣ����������ʽת��
	if (iStationCount == 0)
		return true;
	else
	{
		turnToListWriteRelationSet(iStationCount, pListWriteRelationSet);
		return true;
	}
	//_CrtDumpMemoryLeaks();
	//�ͷ��ڴ�
	//delete pHeadListRelationNode;
}

//ת��Ϊд������
bool CBLLModelAnalyzeTest::turnToListWriteRelationSet(int iNodeNum, CListWriteRelationSet *&pListWriteRelationSet){
	//�������
	//_CrtDumpMemoryLeaks();
	CListRelationNode *pListRelationNode = m_pHeadListRelationSet->getNextRelationNode();
	for (int iCount = 0; iCount < iNodeNum; iCount++)
	{
		//CListWriteRelationNode *pListWriteRelationNode = m_objBufferPool->getWriteRelationNode();
		//m_pBufferPool->mallocWriteRelationNode();
		CListWriteRelationNode *pListWriteRelationNode = new CListWriteRelationNode();//m_pBufferPool->getWriteRelationNode();

		//���ù�ϵ����,�����й�ϵ���ϳ�ʼ��
		pListWriteRelationNode->getEntityRelationSet()->setTimeID(pListRelationNode->getEntityRelationSet()->getTimeID());
		pListWriteRelationNode->getEntityRelationSet()->setStationNum(m_iTotalStationNum);
		pListWriteRelationNode->getEntityRelationSet()->initRelationSet();
		//_CrtDumpMemoryLeaks();
		//����ʱ��ƬID

		//���ù�ϵ����
		pListWriteRelationNode->setEntityRelationSet(pListRelationNode->getEntityRelationSet());

		//_CrtDumpMemoryLeaks();
		//���뵽����DAL������
		pListWriteRelationSet->insertRelationSet(pListWriteRelationNode);
		//�Ƶ���һ���ڴ��ϵ����
		pListRelationNode = pListRelationNode->getNextRelationNode();

	}
	//������
	//_CrtDumpMemoryLeaks();
	//��ȥд��DAL��Ľڵ���������±���ڵ���
	m_pHeadListRelationSet->setNodeNum(m_pHeadListRelationSet->getNodeNum() - iNodeNum);

	//_CrtDumpMemoryLeaks();
	//�������
	pListRelationNode = m_pHeadListRelationSet->getNextRelationNode();

	CListRelationNode *pListRelationLinkNode = NULL;
	//������ϵ������
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
	//����ͷ�
	//_CrtDumpMemoryLeaks();

	//�����������ϵĵ�һ�����ݽڵ�
	//�����������ݸ�����Ϊ0�������¸��ڵ�
	//��������ΪNULL
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

//��ȡʣ��ģ���ڼ��Ϲ�ϵ����
bool CBLLModelAnalyzeTest::getRestRelationSet(CListWriteRelationSet *&pListWriteRelationSet){
	turnToListWriteRelationSet(m_pHeadListRelationSet->getNodeNum(), pListWriteRelationSet);
	return true;
}

//�ַ������
string CBLLModelAnalyzeTest::changeToStringstream(){
	stringstream strstreamCount;
	char* cLeft = "(";
	char* cBlank = ",";
	char* cRight = ")";
	/*���������ԷŽ��ַ���*/
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
	/*��stringstreamת����string*/
	string strCount(strstreamCount.str());

	return strCount;
}

//������������
int CBLLModelAnalyzeTest::getSurvivalNum(int iSurvivalTime){
	return (iSurvivalTime / 20 + 1);
}

//���ģ���ڼ��Ϲ�ϵ����
CListRelationSet* CBLLModelAnalyzeTest::getListRelationSet(){
	return m_pHeadListRelationSet;
}

//�����100��
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


//�������㣬pListRelationNodeԴ����һ�μ��㣬����200�μ����������ļ�
void CBLLModelAnalyzeTest::iteratorGetRelation(CListRelationNode *&pListRelationNode, double &dMaxRelation, double &dMinRelation)
{
	//������ʱ���ݽڵ㣬����ʼ��
	CListRelationNode *tempListRelationNode = new CListRelationNode();

	//��������ڵ����ݣ����������µ�����ڵ㣬���޸���ʱ�ڵ����ݣ�һ�ε�����ɣ������ʱ���ݽڵ�
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
			//������վ�㲻Ϊͬһվ��
			else
			{
				//����iCount��jCount�����ڵ�֮������ƶ�
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
	//��һ��
	//NormalizeMatrix(pEntityRelationSet, dMaxRelation);

	//��������ڴ�ռ�
	//delete pEntityRelationSet;
	delete tempListRelationNode;
}

/**
 * ���ܣ�������ÿ����վ��֮��Ĺ�����ϵ
 * ���룺��һվ�㣬�ڶ�վ�㣬����
 * ������
 */
double CBLLModelAnalyzeTest::calculateRelation(int iFirstStation, int iSecondStation, CListRelationNode *pListRelationNode)
{
	double dStationRelation = 0;
	//iEveryCoupleRelationSum���ڱ���һ������վ��Ĺ�ϵվ��֮��Ĺ�ϵ��
	double dEveryCoupleRelationSum = 0;

	double dFirstStationRelationNum = 0;
	double dBaseMaxRelation = 0;
	//�Ե�һ��վ��Ϊ��׼��¼����ϵ��¼
	double dMaxStationRelation[700];
	
	int iRelationNum = 0;
	//��ʼ������ϵ��¼
	for (int iCount = 0; iCount < m_iTotalStationNum; iCount++)
		dMaxStationRelation[iCount] = 0;

	//�Ե�һ��վ��Ϊ��׼�������һվ������й���վ��Ĺ�ϵ�����ֵ��ȡ������dMaxStationRelation
	for (int iCount = 0; iCount < m_iTotalStationNum; iCount++)
	{
		//�����һ��վ��Ĺ�ϵվ��Ĳ�����Ϊ0����ʾ�ù�ϵվ�㲻��Ҫ����
		if (m_pTimeSliceCountArray[iFirstStation][iCount].getOperateTimes() == 0)
		{
			continue;
		}
		//��ϵվ����Ҫ���ǣ��õ���һ��վ���ϵվ���һЩ���ݣ�C�͵�һ��վ��������ֵ
		else
		{
			//�������Ƴ���������һ��վ��ĳ���
			dFirstStationRelationNum++;
			for (int jCount = 0; jCount < m_iTotalStationNum; jCount++)
			{
				//���Ƚ�վ��Ĳ�����Ϊ0������Ƚ�
				if (m_pTimeSliceCountArray[iSecondStation][jCount].getOperateTimes() == 0)
					continue;

				//����ͻ�ȡ�������ص�ʱ��Ƭ
				else
				{
					dEveryCoupleRelationSum = pListRelationNode->getEntityRelationSet()->getStationRelation(iCount, jCount);
					//������ֵ
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
			//�������
			if (dStationRelation > iOverNum)
			{
				//�������
				/*m_pModelEntityRelationArray[lCount].setTargetStation(iCount);
				m_pModelEntityRelationArray[lCount].setRelationStation(jCount);
				m_pModelEntityRelationArray[lCount].setStationRelation(dStationRelation);*/
				lCount++;
			}
		}
	}
	return lCount;
}

//����m_pModelEntityRelationArrayͨ����������ȡ
/*void CBLLModelAnalyzeTest::getRelationMatrix()
{
	//int iCount = 0;
	//�õ���һ��վ��
	//while (iCount<5000){
	//	if (iStartStation != m_pModelEntityRelationArray[iCount].getTargetStation())
	//		iCount++;
	//	else if (iStartStation == m_pModelEntityRelationArray[iCount].getTargetStation())
	//	{
	//		break;
	//	}
	//	else
	//	{
	//		AfxMessageBox(_T("δ�ҵ���ʵվ��"));
	//	}
	//}
	////����ҵ�վ�㣬���Ի����iCountֵ������Ϊ���ĸ��ڵ�
	//treeNode *treeRoot;
	////д����ڵ�վ����
	//treeRoot->iStationID = m_pModelEntityRelationArray[iCount].getTargetStation();
	//treeRoot->child = NULL;
	//treeRoot->brother = NULL;
	//treeRoot->relation = 0;
	////תΪ�ڽӾ���
	////
	//createTree(treeRoot, iCount);

	//����һ���µ��ڽӾ���
	matrixArray *matrixRelationArray = NULL;
	matrixRelationArray = (matrixArray *)malloc(500 * sizeof(matrixArray));

	//��ʼ���ڽӾ���
	for (int iCount = 0; iCount < 500; iCount++)
	{
		matrixRelationArray[iCount].firstmatrixNode = NULL;
		matrixRelationArray[iCount].iStationID = 0;
	}

	//�������ձ���
	int iTargetStation = 0;
	int iRelationStation = 0;
	double dStationRelation = 0;

	int jCount = 0;
	int lCount = 0;

	bool flag = false;
	for(int iCount = 0; iCount < 300; iCount++)
	{
		//�õ�Ŀ��վ�㡢��ϵվ��
		iTargetStation = m_pModelEntityRelationArray[iCount].getTargetStation();
		iRelationStation = m_pModelEntityRelationArray[iCount].getRelationStation();
		dStationRelation = m_pModelEntityRelationArray[iCount].getStationRelation();
		if (iTargetStation == 0 && iRelationStation == 0 && dStationRelation == 0)
			break;
		
		//���ѭ����ȡ�õ�һ��0ֵ��˵�����������targetStation����Ҫ�½�
		for (lCount = 0; lCount < 500; lCount++)
		{
			if (matrixRelationArray[lCount].iStationID == iTargetStation)
			{
				flag = true;
				break;
			}
		}

		//flagΪfalse
		if (flag == false)
		{
			matrixRelationArray[jCount].iStationID = iTargetStation;
			matrixRelationArray[jCount].firstmatrixNode = (matrixNode *)malloc(sizeof(matrixNode));
			matrixRelationArray[jCount].firstmatrixNode->iRelationID = iRelationStation;
			matrixRelationArray[jCount].firstmatrixNode->iStationRelation = dStationRelation;
			matrixRelationArray[jCount].firstmatrixNode->nextRelationStation = NULL;
			jCount++;
		}
		//flagΪtrue,����������targetStation
		else
		{
			//������ʱ�ڵ�����������ж��Ƿ�Ϊд��λ���Լ����ڱ���д��λ��
			matrixNode *tempNode = matrixRelationArray[lCount].firstmatrixNode;
			
			//Ѱ�����һ���ڵ�
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

			//�ж�Ϊ��false
			flag = false;
		}
	}
}		*/



////ת��Ϊ�ڽӾ���
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


//�õ������ض���ϵ���ݵľ��༯��

//������targetStationID����relationStationID��Ҫ���뵽������
//������
void CBLLModelAnalyzeTest::getCluster()
{
	int iTargetStation;
	int iRelationStation;
	int flag;
	int littleFlag;
	//���ڿ��ƾ�����
	int lCount = 0;
	//ÿ�ζ�ȡһ�����ݽ��б��
	for (int iCount = 0; iCount < 300; iCount++)
	{
		//�õ���һ��վ���
		iTargetStation = m_pModelEntityRelationArray[iCount].getTargetStation();
		iRelationStation = m_pModelEntityRelationArray[iCount].getRelationStation();

		//���Ŀ��վ���flagΪ0��˵��δ���
		if (m_pModelEntityStationArray[iTargetStation].getFlag() == 0)
		{
			//����flag���
			m_pModelEntityStationArray[iTargetStation].setFlag(lCount + 1);//������ΪiCount
			lCount++;
			//���flag��ţ����ڹ���վ��Ϊ��ʱ��Ҫ��ֵ
			flag = m_pModelEntityStationArray[iTargetStation].getFlag();
		}
		else
		{
			//���flag
			flag = m_pModelEntityStationArray[iTargetStation].getFlag();
		}

		//�����ϵվ���flagΪ0��˵��Ϊ���
		if (m_pModelEntityStationArray[iRelationStation].getFlag() == 0)
		{
			//����flag���targetStation��flag���
			m_pModelEntityStationArray[iRelationStation].setFlag(flag);
		}

		//˵����ϵվ���Ѿ�����ǣ�����ȡ��С���Ǹ�flag���������е���������վ��
		else
		{
			if (flag > m_pModelEntityStationArray[iRelationStation].getFlag())
				//�Ȼ��ԭ���Ľ�С��flagֵ
				littleFlag = m_pModelEntityStationArray[iRelationStation].getFlag();
			else
				littleFlag = flag;
			//����С��flagֵ��ֵ����������վ��
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