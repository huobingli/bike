#include"stdafx.h"
#include "FrameDAL.h"

CFrameDAL::CFrameDAL ()
:
m_objSourceFile(0),
m_objTargetFile(0),
m_objRelationFile(0),
m_objPreControl(0),
m_objAlgorithmControl(0){
    init();
}

CFrameDAL::~CFrameDAL (){

    if (m_objSourceFile != 0 && m_objTargetFile != 0 &&
        m_objRelationFile != 0 && m_objAlgorithmControl != 0 &&
        m_objPreControl != 0){
    delete m_objSourceFile;
    delete m_objTargetFile;
    delete m_objRelationFile;
    delete m_objAlgorithmControl;
    delete m_objPreControl;
    m_objSourceFile = NULL;
    m_objTargetFile = NULL;
    m_objRelationFile = NULL;
    m_objAlgorithmControl = NULL;
    m_objPreControl = NULL;
    }
}

/**
说明：初始化数据访问层框架
更新时间：2015/10/5*/
bool CFrameDAL::init (){
    m_objSourceFile = new CDALOriginalFile("Divvy_Trips_2013.csv", "ios::app");
    m_objTargetFile = new CDALFile("TargetFile.txt", "a+");
    m_objRelationFile = new CDALFile("RelationFile.txt", "a+");

    //判断文件对象是否初始化成功
    if (m_objSourceFile==0 || m_objTargetFile==0|| m_objRelationFile ==0||
        m_objAlgorithmControl==0 || m_objPreControl==0){
        return false;
    }
    return true;
}


/**
入口参数：开始位置，借还数据集合对象地址, 单次读取的量
返回值 ：是否读取成功
更新时间：2015/10/5*/
bool CFrameDAL::getUseRecord (CEntityTripDataSet *&pBorrowDataOut, int iNumIn, int iPosIn){

    if (iPosIn ==-1){
        return m_objPreControl->readSourceData(pBorrowDataOut, iNumIn);
    }
}
	
/** 
入口参数：开始位置，统计数据集合对象地址
返回值：是否写入成功
更新时间：2015/10/8*/
bool CFrameDAL::putPreprocessedData ( CEntityTimeSliceCountSet *pStatisticalDataRecordSetIn, int iPosIn){

    bool isSuccesed = false;

    //将对象转化成二进制流形式
    unsigned char *strBuf = pStatisticalDataRecordSetIn->getBinary();

    //获取二进制流数据长度
    int iDataLength = pStatisticalDataRecordSetIn->getBinaryLength();

    //将二进制流对象写入目标文件
    isSuccesed = m_objPreControl->writeTimeSliceStatisticalBinaryObject(strBuf, iPosIn);
    if (isSuccesed){
        return true;
    }else{
        return false;
    }
}

/**
参数：开始位置，统计数据集合对象地址（这个对象是在业务逻辑层中分配好内存的，并在业务逻辑层中释放），记录数
返回值 ：是否读取成功
更新时间：2015/9/30*/
bool CFrameDAL::getPreprocessedData (CEntityTimeSliceCountSet *&pStatisticalDataRecordSetOut, int iPos, int iNumIn){

    //创建二进制字节数组
    unsigned char *chBuffer = NULL;

    //调用算法处理控制对象的读取方法，将读取的数据存储在二进制字节数组中
    m_objAlgorithmControl->readTimeSliceStatisticalBinaryObject(chBuffer, iNumIn);
    if (chBuffer == NULL){
        return false;
    }else{
        //将二进制字节数据转换成时间片关联数据集合对象
        pStatisticalDataRecordSetOut->update(chBuffer);
        if (pStatisticalDataRecordSetOut == 0){
            free (chBuffer);//销毁二进制字节数组
            chBuffer = NULL;
            return false;
        }else{
            free (chBuffer); //销毁二进制字节数组
            chBuffer = NULL;
            return true;
        }
    }
}

/**
参数：开始位置，关联数据集合对象指针（这个对象是在业务逻辑层中分配好内存的，并在业务逻辑层中释放）
返回值 ：是否写入成功
更新时间：2015/9/30*/
bool CFrameDAL::putRelatedData (CListWriteRelationSet *pRelatedDataRecordSetIn, int iPosIn){
    bool isSuccesed = false;
    //将对象转化成二进制流形式
    unsigned char *strBuf = pRelatedDataRecordSetIn->getBinary();

    //获取二进制流数据长度
    int iDataLength = pRelatedDataRecordSetIn->getBinaryLength();

    //将二进制流对象写入目标文件
    isSuccesed = m_objAlgorithmControl->writeTimeSliceRelatedBinaryObject(strBuf, iPosIn);
	free(strBuf);
	strBuf = NULL;
    if (isSuccesed){
        return true;
    }else{
        return false;
    }
}

/**
名称：getRelatedData
入口参数：开始位置，统计数据集合对象地址（这个对象是在业务逻辑层中分配好内存的，并在业务逻辑层中释放），记录数
返回值：是否读取成功
更新时间：2015/11/6*/
bool CFrameDAL::getRelatedData(CListWriteRelationSet *&pRelatedDataRecordSetOut, int iPos, int iNumIn){

    //创建二进制字节数组
    unsigned char *chBuffer = NULL;

    //调用算法处理控制对象的读取方法，将读取的数据存储在二进制字节数组中
    m_objAlgorithmControl->readTimeSliceRelatedBinaryObject(chBuffer, iNumIn);
    if (chBuffer == NULL){
        return false;
    }else{
        //将二进制字节数据转换成时间片关联数据集合对象
        pRelatedDataRecordSetOut->update(chBuffer);
        if (pRelatedDataRecordSetOut == 0){
            free (chBuffer);//销毁二进制字节数组
            chBuffer = NULL;
            return false;
        }else{
            free (chBuffer); //销毁二进制字节数组
            chBuffer = NULL;
            return true;
        }
    }
}

/**
参数：源文件名称和目标文件名称
返回值 ：是否预初始化成功
更新时间：2015/10/8*/
bool CFrameDAL::initPreProcessControl (){

    //打开原文件
    if (!m_objSourceFile->openFile(ORIGIN_FILE_OPEN_MODE_APP)){
        return false;
    }

    //打开目标文件
    if (!m_objTargetFile->openFile()){
        return false;
    }
    
    //动态创建预处理控制对象
    m_objPreControl = new CControlPre(m_objSourceFile, m_objTargetFile);
    if (m_objPreControl == 0){
        return false;
    }

    return true;
}

/**
说明：预处理善后
返回值 ：是否预处理善后成功
更新时间：2015/10/8*/
bool CFrameDAL::doPreprocessRehabilitation (){

    //关闭原文件
    if (!m_objSourceFile->closeFile()){
        return false;
    }

    //关闭目标文件
    if (!m_objTargetFile->closeFile()){
        return false;
    }

    //销毁与处理控制对象
    if (m_objPreControl != 0){
        delete m_objPreControl;
        m_objPreControl = NULL;
        return true;
    }else{
        return false;
    }
}

/**
参数：源文件名称和目标文件名称
返回值 ：是否算法初始化成功
更新时间：2015/10/8*/
bool CFrameDAL::initAlgorithmControl (){

    //打开目标文件
    if (!m_objTargetFile->openFile()){
        return false;
    }

    //打开关联文件
    if (!m_objRelationFile->openFile()){
        return false;
    }
    
    //动态创建算法处理控制对象
    m_objAlgorithmControl = new CControlAlgorithm(m_objTargetFile, m_objRelationFile);
    if (m_objAlgorithmControl == 0){
        return false;
    }

    return true;
}

/**
说明：算法善后
返回值 ：是否算法处理善后成功
更新时间：2015/10/8*/
bool CFrameDAL::doAlgorithmRehabilitation (){

    //关闭目标文件
    if (!m_objTargetFile->closeFile()){
        return false;
    }

    //关闭关联文件
    if (!m_objRelationFile->closeFile()){
        return false;
    }

    //销毁算法控制对象
    if (m_objAlgorithmControl != 0){
        delete m_objAlgorithmControl;
        m_objAlgorithmControl = NULL;
        return true;
    }else{
        return false;
    }
}

/**
名称:writeStdFile
说明：文件不存在就创建，文件存在就清空内容
入口参数：要写入的字符串
返回值：是否写入成功
更新时间：2015/11/5*/
bool CFrameDAL::writeStdFile(char *chTest){ 

    if (chTest == NULL){
        return false;
    }

    CDALOriginalFile *objFile = new CDALOriginalFile ("checkFile.txt", "ios::out");
    objFile->openFile(ORIGIN_FILE_OPEN_MODE_OUT);
    objFile->writeStdCheck(chTest);
    objFile->closeFile();

    return true;
}

/**
名称:writemaxMinStdFile
说明：文件不存在就创建，文件存在就清空内容
入口参数：要写入的字符串
返回值：是否写入成功
更新时间：2015/1/15*/
bool CFrameDAL::writeMaxMinStdFile(char *chTest){

	if (chTest == NULL){
		return false;
	}

	CDALOriginalFile *objFile = new CDALOriginalFile("checkMaxMinFile.txt", "ios::out");
	objFile->openFile(ORIGIN_FILE_OPEN_MODE_OUT);
	objFile->writeStdCheck(chTest);
	objFile->closeFile();

	return true;
}

/**
名称:writeRelationStdFile
说明：文件不存在就创建，文件存在就清空内容
入口参数：要写入的字符串
返回值：是否写入成功
更新时间：2015/1/26*/
bool CFrameDAL::writeRelationStdFile(char *chTest){

	if (chTest == NULL){
		return false;
	}

	CDALOriginalFile *objFile = new CDALOriginalFile("checkRelationArray.txt", "ios::out");
	objFile->openFile(ORIGIN_FILE_OPEN_MODE_OUT);
	objFile->writeStdCheck(chTest);
	objFile->closeFile();

	return true;
}

bool CFrameDAL::writeClusterStdFile(char *chTest)
{
	if (chTest == NULL)
	{
		return false;
	}

	CDALOriginalFile *objFile = new CDALOriginalFile("checkClusterArray.txt", "ios::out");
	objFile->openFile(ORIGIN_FILE_OPEN_MODE_OUT);
	objFile->writeStdCheck(chTest);
	objFile->closeFile();
	return true;
}