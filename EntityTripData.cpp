#include "StdAfx.h"

#include"EntityTripData.h"

/**
创建者：姚*/
CEntityTripData::CEntityTripData(){
	m_iStartStationTime = 1501010000;    //默认时间为1501010000即2015年1月1日0点0分
	m_iStopStationTime = 1501010000;
	m_iStartStationID = -1;
	m_iStopStationID = -1;
	m_iCostTime = 0;                     //默认初始花费时间为0s
}

/**
说明：更新借还对象
参数：包含借还对象的字符串
返回值：是否更新成功
创建者：蔡*/
bool CEntityTripData::update(string csStationData){
	/*验证字符串有效性*/
	if (csStationData == ""){
		return false;
	}

	/*排除无用信息模块*/
	string strResult;                         //保存临时分割出来的信息片段
	/*区分分割区间*/
	int iLast = 0;
	int iIndex = 0;

	/*排除无用信息模块*/
	iIndex = csStationData.find_first_of(',', iLast);
	strResult = csStationData.substr(iLast, iIndex - iLast);
	if (atoi(strResult.c_str()) == 0){
		return false;
	}
	translateRecordData(csStationData);  //有效信息字符串进入转换过程
	return true;
}

/**
说明：将字符串按记录属性分割
入口参数：包含有效的记录信息字符串
返回值：是否更新成功
创建者：蔡
更新时间：2015/10/13*/
bool CEntityTripData::translateRecordData(string csRecordData){
	/*变量定义模块*/
	string strTemp = csRecordData;
	string strResult;//保存临时分割出来的信息片段
	int iFalge = 0;//信息归位标志
	/*区分分割区间*/
	int iLast = 0;
	int iIndex = 0;

	/*分割字符串模块*/
	iIndex = strTemp.find_first_of(',', iLast);
	iFalge++;
	while (iIndex != std::string::npos){
		strResult = strTemp.substr(iLast, iIndex - iLast);
		iLast = iIndex + 1;

		/*将string类型转化模块*/
		if (iFalge == 3){ setStartStationTime(strResult); }
		else if (iFalge == 7){ setStopStationTime(strResult); }
		//else if (iFalge == 11){setCostTime(strResult);}
		else if (iFalge == 4){ setStartStationID(strResult); }
		else if (iFalge == 8){ setStopStationID(strResult); }

		iIndex = strTemp.find_first_of(',', iLast);
		iFalge++;
	}
	iIndex = strTemp.find_first_of(',', iLast);
	strResult = strTemp.substr(iLast, iIndex - iLast);
	if (iFalge == 11){ setCostTime(strResult); }
	return true;
}

void CEntityTripData::setStartStationTime(string strStartStationTime){
	/*变量定义模块*/
	string strTemp = strStartStationTime;
	string strResult;//保存临时分割出来的信息片段
	string strTime;   //截取的有效时间
	char *chTemp = (char *)malloc(3);
	memset(chTemp, 0, 2);
	int iFalge = 0;//信息归位标志
	/*区分分割区间*/
	int iLast = 0;
	int iIndex = 0;

	/*获取年份月份模块*/
	iIndex = strTemp.find_first_of('/', iLast);
	iFalge++;
	while (iIndex != std::string::npos){
		strResult = strTemp.substr(iLast, iIndex - iLast);
		iLast = iIndex + 1;

		/*将string类型转化模块*/
		if (iFalge == 1){
			strncpy(chTemp, strResult.c_str() + 2, 2);
			chTemp[2] = '\0';
			strResult = chTemp;
			strTime += strResult;
		}
		else if (iFalge == 2 || iFalge == 3){
			if (strlen(strResult.c_str()) == 1){
				strTime += '0';
				strTime += strResult;
			}
			else{
				strTime += strResult;
			}
		}

		iIndex = strTemp.find_first_of('/', iLast);
		iFalge++;
	}

	/*获取日期*/
	strTemp = strTemp.substr(iLast, iIndex - iLast);
	iFalge = 0;//信息归位标志
	iLast = 0;//分割上下界重置
	iIndex = 0;

	/*获取年份月份模块*/
	iIndex = strTemp.find_first_of(' ', iLast);
	iFalge++;
	while (iIndex != std::string::npos){
		strResult = strTemp.substr(iLast, iIndex - iLast);
		iLast = iIndex + 1;

		/*将string类型转化模块*/
		if (iFalge == 1){
			if (strlen(strResult.c_str()) == 1){
				strTime += '0';
				strTime += strResult;
			}
			else{
				strTime += strResult;
			}
		}

		iIndex = strTemp.find_first_of('/', iLast);
		iFalge++;
	}

	/*获取小时*/
	strTemp = strTemp.substr(iLast, iIndex - iLast);
	iFalge = 0;//信息归位标志
	iLast = 0;//分割上下界重置
	iIndex = 0;

	/*获取年份月份模块*/
	iIndex = strTemp.find_first_of(':', iLast);
	iFalge++;
	while (iIndex != std::string::npos){
		strResult = strTemp.substr(iLast, iIndex - iLast);
		iLast = iIndex + 1;

		/*将string类型转化模块*/
		if (iFalge == 1){
			if (strlen(strResult.c_str()) == 1){
				strTime += '0';
				strTime += strResult;
			}
			else{
				strTime += strResult;
			}
		}

		iIndex = strTemp.find_first_of('：', iLast);
		iFalge++;
	}

	/*获取分钟*/
	strTemp = strTemp.substr(iLast, iIndex - iLast);
	strTime += strTemp;

	m_iStartStationTime = atoi(strTime.c_str());

	free(chTemp);
	chTemp = NULL;
}

void CEntityTripData::setStopStationTime(string strStopStationTime){
	/*变量定义模块*/
	string strTemp = strStopStationTime;
	string strResult;//保存临时分割出来的信息片段
	string strTime;   //截取的有效时间
	char *chTemp = (char *)malloc(3);
	memset(chTemp, 0, 2);
	int iFalge = 0;//信息归位标志
	/*区分分割区间*/
	int iLast = 0;
	int iIndex = 0;

	/*获取年份月份模块*/
	iIndex = strTemp.find_first_of('/', iLast);
	iFalge++;
	while (iIndex != std::string::npos){
		strResult = strTemp.substr(iLast, iIndex - iLast);
		iLast = iIndex + 1;

		/*将string类型转化模块*/
		if (iFalge == 1){
			strncpy(chTemp, strResult.c_str() + 2, 2);
			chTemp[2] = '\0';
			strResult = chTemp;
			strTime += strResult;
		}
		else if (iFalge == 2 || iFalge == 3){
			if (strlen(strResult.c_str()) == 1){
				strTime += '0';
				strTime += strResult;
			}
			else{
				strTime += strResult;
			}
		}

		iIndex = strTemp.find_first_of('/', iLast);
		iFalge++;
	}

	/*获取日期*/
	strTemp = strTemp.substr(iLast, iIndex - iLast);
	iFalge = 0;//信息归位标志
	iLast = 0;//分割上下界重置
	iIndex = 0;

	/*获取年份月份模块*/
	iIndex = strTemp.find_first_of(' ', iLast);
	iFalge++;
	while (iIndex != std::string::npos){
		strResult = strTemp.substr(iLast, iIndex - iLast);
		iLast = iIndex + 1;

		/*将string类型转化模块*/
		if (iFalge == 1){
			if (strlen(strResult.c_str()) == 1){
				strTime += '0';
				strTime += strResult;
			}
			else{
				strTime += strResult;
			}
		}

		iIndex = strTemp.find_first_of('/', iLast);
		iFalge++;
	}

	/*获取小时*/
	strTemp = strTemp.substr(iLast, iIndex - iLast);
	iFalge = 0;//信息归位标志
	iLast = 0;//分割上下界重置
	iIndex = 0;

	/*获取年份月份模块*/
	iIndex = strTemp.find_first_of(':', iLast);
	iFalge++;
	while (iIndex != std::string::npos){
		strResult = strTemp.substr(iLast, iIndex - iLast);
		iLast = iIndex + 1;

		/*将string类型转化模块*/
		if (iFalge == 1){
			if (strlen(strResult.c_str()) == 1){
				strTime += '0';
				strTime += strResult;
			}
			else{
				strTime += strResult;
			}
		}

		iIndex = strTemp.find_first_of('：', iLast);
		iFalge++;
	}

	/*获取分钟*/
	strTemp = strTemp.substr(iLast, iIndex - iLast);
	strTime += strTemp;

	m_iStopStationTime = atoi(strTime.c_str());

	free(chTemp);
	chTemp = NULL;
}

void CEntityTripData::setStartStationID(string strStartStationID){

	/*变量定义模块*/
	string strTemp = strStartStationID;
	string strResult;//保存临时分割出来的信息片段
	string strTime;   //截取的有效id
	char *chTemp = (char *)malloc(3);
	memset(chTemp, 0, 2);
	int iFalge = 0;//信息归位标志
	/*区分分割区间*/
	int iLast = 0;
	int iIndex = 0;

	/*获取年份月份模块*/
	iIndex = strTemp.find_first_of('-', iLast);
	iFalge++;
	while (iIndex != std::string::npos){
		strResult = strTemp.substr(iLast, iIndex - iLast);
		iLast = iIndex + 1;

		strTime += strResult;

		iIndex = strTemp.find_first_of('-', iLast);
		//  iFalge ++;
	}

	strResult = strTemp.substr(iLast, iIndex - iLast);
	strTime += strResult;

	m_iStartStationID = atoi(strTime.c_str());
}

void CEntityTripData::setStopStationID(string strStopStationID){
	/*变量定义模块*/
	string strTemp = strStopStationID;
	string strResult;//保存临时分割出来的信息片段
	string strTime;   //截取的有效id
	char *chTemp = (char *)malloc(3);
	memset(chTemp, 0, 2);
	int iFalge = 0;//信息归位标志
	/*区分分割区间*/
	int iLast = 0;
	int iIndex = 0;

	/*获取年份月份模块*/
	iIndex = strTemp.find_first_of('-', iLast);
	iFalge++;
	while (iIndex != std::string::npos){
		strResult = strTemp.substr(iLast, iIndex - iLast);
		iLast = iIndex + 1;

		strTime += strResult;

		iIndex = strTemp.find_first_of('-', iLast);
		//  iFalge ++;
	}

	strResult = strTemp.substr(iLast, iIndex - iLast);
	strTime += strResult;

	m_iStopStationID = atoi(strTime.c_str());
}

void CEntityTripData::setCostTime(string strCostTime){

	/*变量定义模块*/
	string strTemp = strCostTime;
	string strResult;//保存临时分割出来的信息片段
	string strTime;   //截取的有效使用时间
	int iTime = 0;
	char *chTemp = (char *)malloc(3);
	memset(chTemp, 0, 2);
	int iFalge = 0;//信息归位标志
	/*区分分割区间*/
	int iLast = 0;
	int iIndex = 0;

	/*获取年份月份模块*/
	iIndex = strTemp.find_first_of("小", iLast);
	iFalge++;
	while (iIndex != std::string::npos){
		strResult = strTemp.substr(iLast, iIndex - iLast);
		iLast = iIndex + 1;

		iTime += 3600 * atoi(strResult.c_str());

		iIndex = strTemp.find_first_of('-', iLast);
	}

	iIndex = strTemp.find_first_of("分", iLast);
	iFalge += 4;
	while (iIndex != std::string::npos){
		strResult = strTemp.substr(iLast + 3, iIndex - 5);
		iLast = iIndex + 1;

		iTime += 60 * atoi(strResult.c_str());

		iIndex = strTemp.find_first_of('-', iLast);
	}

	//strResult = strTemp.substr(iLast,iIndex-iLast);
	//strTime += strResult;

	m_iCostTime = iTime;
}

CEntityTripData::~CEntityTripData(){
}

/**
说明：获取方法
创建者：姚*/
long int CEntityTripData::getStartStationTime(){
	return m_iStartStationTime;
}

long int CEntityTripData::getStopStationTime(){
	return m_iStopStationTime;
}

int CEntityTripData::getStartStationID(){
	return m_iStartStationID;
}

int CEntityTripData::getStopStationID(){
	return m_iStopStationID;
}

int CEntityTripData::getCostTime(){
	return m_iCostTime;
}
