#pragma once
#include "DALConfiguration.h"
#include "DALBlock.h"
#include "stdio.h"
/**
名称：CDALFile
说明：封装block，实现数据的读写
更新时间：2015/10/8*/
class CDALFile{
    CDALBlock *m_pBlock;    //单块数据块
    FILE *m_pFP;            //文件二进制流指针
    char *m_chFileName;     //存储的文件名
    char *m_chFlag;         //文件的打开方式

    /**
    名称：moveSeek
    说明：更新当前操作指针位置
    返回值：是否移动成功
    更新时间：2015/10/11*/
    bool moveSeek(int iPosIn);

   /**
    名称：write
    说明：写入
    参数：存放地址
    返回值：本次写入量
    更新时间：2015/10/11*/
    int write(const CDALBlock *pBlockIn);

    /**
    名称：read
    说明：读取
    参数：存放地址
    返回值：本次读取量
    更新时间：2015/10/11*/
    int read(CDALBlock *&pBlock);

    /**
    说明：将传入的整型变量转成二进制类型
    参数：待转整型变量，接收转换后的二进制类型数据的字符串变量
    返回值：是否转化成功
    更新时间：2015/10/21*/
    bool IntegerIntoBinary(const int iNumIn, unsigned char *chBinaryOut);

    /**
    说明：将传入的二进制类型转成整型变量
    参数：二进制类型数据的字符串变量(在内部分配内存)
    返回值：转化成功的整型变量 
    更新时间：2015/10/21*/
    int BinaryIntoInteger(const unsigned char *chBinaryIn);

    /**
    说明：获取所有数据量-
    参数：二进制集合
    返回值：数据量
    更新时间：2015/10/23*/
    int getTotalNum(const unsigned char *chBufferIn);

    /**
    说明：获取所需可分组数
    参数：记录数
    返回值：可分组数
    更新时间：2015/10/8*/
    int getGroupNum(const unsigned char *chBufferIn);

public:
    /**
    名称：构造*/
    CDALFile(const char *chFileName, const char *chFlag);

    /**
    析构*/
    ~CDALFile();

    /**
    说明：初始化本文件对象
    返回值：是否初始化成功
    更新时间：2015/7/20*/
    bool init (char *chFileName);

    /**
    说明：打开文件
    返回值：是否打开成功
    更新时间：2015/10/8*/
    bool openFile();

    /**
    说明：关闭文件
    返回值：是否关闭成功
    更新时间：2015/10/8*/
    bool closeFile();
	
    /**
    参数:二进制数据，写入块位置
    返回值：是否写入成功
    更新时间：2015/10/8*/
    bool writeToFile(const unsigned char *pBinaryIn, int iBlockPos);

    /**
    参数:单块，读取位置
    返回值：是否读取成功
    更新时间：2015/10/8*/
    bool readFromFile(unsigned char *&pBinaryOut, int iBlockPos);
	
};
