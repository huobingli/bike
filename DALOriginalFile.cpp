#include"stdafx.h"

#include "DALOriginalFile.h"

CDALOriginalFile::CDALOriginalFile(const char *chFileName, const char *chFlag)
:
m_fReadAreadyPos(0),
m_chFileName(0),
m_WriteReadFlag(0){

    //初始化
    m_WriteReadFlag = (struct BitFied *) malloc (sizeof (struct BitFied));
    memset (m_WriteReadFlag, 0, sizeof (struct BitFied));
    m_chFileName = (char *)malloc (20);

    strcpy (m_chFileName, chFileName);   //拷贝文件名
}

CDALOriginalFile::~CDALOriginalFile(){
    free (m_chFileName);
    m_chFileName = NULL;
}

/**
说明：从txt文件中读取相应的数据
参数：当前已读取的数据量，临时读取的数据保存位置
返回值：是否读取成功 
更新时间：2015/10/16*/
bool CDALOriginalFile::readTripRecord(CEntityTripDataSet *&pRecordSetOut, int iNumIn){
    /*初始化变量模块*/
    string temp;
    int iLineAready = 0;//本次打开已读取的数据量（按行计），确定分块读取的数据量

    /*未正确读取文件*/
    if (!m_inputFile){
        return false;
    }

    /*填补表头空缺*/
    if (m_fReadAreadyPos == 0){
        iNumIn += 1;
    }

    /*循环读取数据模块*/ 
    /*说明：
    单次读取数据量为EACH_TIME_READ*/
    m_inputFile.seekg(m_fReadAreadyPos);//还原上次读取的位置

    while (iLineAready < iNumIn){
        getline(m_inputFile,temp);
        /*读取文件到末尾*/
        if (m_inputFile.eof()){
            return false;
        }
        iLineAready ++;
	
        /*说明*/
        /*调用站点集合的biggerStationSet()函数扩充数组*/
        if (pRecordSetOut->isEnd()){
            pRecordSetOut->biggerRecordSet();
        }
        /*说明*/
        /*通过linkRecord()函数直接获取记录集合数组首地址，再通过CEntityTripData->getSize()确定当前存储位置下标，最后通过调用当前存储位置
        单个记录对应的updatteRecord（）函数，将字符串类型记录信息更新至相对应的单个站点的私有属性值*/
        if (pRecordSetOut->linkRecord()[pRecordSetOut->gettingSize()].update(temp)){
            (pRecordSetOut->gettingSize()) ++;//站点集合存储位置下移
            cout << temp << endl;
        }
    }

    m_fReadAreadyPos = m_inputFile.tellg();//保存本次读取的位置信息

    return true;
}

/**
说明：打开文件
返回值：是否打开成功
更新时间：2015/10/16*/
bool CDALOriginalFile::openFile(int iFlag){

    m_WriteReadFlag->chFlag = iFlag;

    if (m_WriteReadFlag->chFlag != ORIGIN_FILE_OPEN_MODE_OUT){
        m_inputFile.open(m_chFileName,ios::app);
    }else{
        m_outputFile.open(m_chFileName,ios::out);
    }
    return true;
}


/**
说明：关闭文件
返回值：是否关闭成功
更新时间：2015/10/16*/
bool CDALOriginalFile::closeFile(){

    if (m_WriteReadFlag->chFlag != ORIGIN_FILE_OPEN_MODE_OUT){
        m_inputFile.close();
    }else{
        m_outputFile.close();
    }
    return true;
}

/**
说明：将数据写入文件 
参数：要写入的字符串
返回值：是否写入成功
更新时间：2015/11/5*/
bool CDALOriginalFile::writeStdCheck (char *chTest){
    
    m_outputFile << chTest;
    return true;
}
