#pragma once

#include "DALFile.h"

/**
说明：算法控制
更新时间：2015/9/30*/
class CControlAlgorithm{
    CDALFile *m_objTargetFile;      //目标文件对象(框架拷贝)接收容器
    CDALFile *m_objRelationFile;   //关联文件对象(框架拷贝)接收容器

private:
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
    说明：获取所有数据量
    参数：二进制集合
    返回值：数据量
    更新时间：2015/10/23*/
    int getTotalNum(const unsigned char *chBufferIn);

    /**
    说明：获取所需可分组数
    入口参数：二进制集合
    返回值：可分组数
    更新时间：2015/10/8*/
    int getGroupNum(const unsigned char *chBufferIn);

public:
    CControlAlgorithm(const CDALFile *objTargetFileIn, const CDALFile *objRelationFileIn);
    ~CControlAlgorithm();

    /**
    说明：读取时间片统计数据对象
    入口参数：时间片统计二进制对象和开始位置
    返回值：是否成功
    更新时间：2015/10/8*/
    bool readTimeSliceStatisticalBinaryObject(unsigned char *&chBufferOut, int iPosStartIn);
    
    /**
    说明：写入时间片关联对象数据对象
    入口参数：时间片关联对象二进制对象和开始位置
    返回值：是否成功
    更新时间：2015/10/8*/
    bool writeTimeSliceRelatedBinaryObject(const unsigned char *chBufferIn, int iPosStartIn);

    /**
    说明：读取时间片关联数据对象
    入口参数：时间片关联二进制对象和开始位置
    返回值：是否成功
    更新时间：2015/10/8*/
    bool readTimeSliceRelatedBinaryObject(unsigned char *&chBufferOut, int iPosStartIn);
};
