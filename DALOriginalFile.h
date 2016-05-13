#pragma once

#include <iostream>
#include <fstream>
#include <string.h>
#include <strstream>
#include "EntityTripDataSet.h"
#include "DALConfiguration.h"

using namespace std;

struct BitFied{
    unsigned char chFlag:1;
};

/**
说明：原数据读取
更新时间:2015/10/16*/
class CDALOriginalFile{
    char *m_chFileName;                //源文件名
    float m_fReadAreadyPos;            //文件当前读取位置
    struct BitFied *m_WriteReadFlag;   //文件读写标志
    ifstream m_inputFile;              //输出流 
    ofstream m_outputFile;             //输入流 

public:
    CDALOriginalFile(const char *chFileName, const char *chFlag);
    ~CDALOriginalFile();
public:
    /**
    说明：读取借还记录对象
    参数：借还对象集合，本次读取记录量
    返回值：是否读取成功
    更新时间：2015/10/16*/
    bool readTripRecord(CEntityTripDataSet *&pcsStationSetOut, int iNumIn);

    /**
    说明：打开文件
    返回值：是否打开成功
    更新时间：2015/10/16*/
    bool openFile(int iFlag);

    /**
    说明：关闭文件
    返回值：是否关闭成功
    更新时间：2015/10/16*/
    bool closeFile();

    /**
    说明：将数据写入文件 
    参数：要写入的字符串
    返回值：是否写入成功
    更新时间：2015/11/5*/
    bool writeStdCheck (char *chTest);
};
