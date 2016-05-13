#pragma once
#include <string.h>
#include <stdlib.h>
#include "DALConfiguration.h"
/**
名称：CDALBLock
说明：封装了单块数据，包括对象集合转二进制数据模块
     以及二进制数据转对象集合模块 
更新时间：2015/7/20*/
class CDALBlock{
    unsigned char* m_pchBinaryArrary;   //二进制数据块
    int m_iBinaryLength;                //二进制数据长度

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
public:
    /**
    名称：构造*/
    CDALBlock();
    CDALBlock(CDALBlock *&p);
    
    /**
    名称：构造*/
    ~CDALBlock();

    /**
    说明：初始化block对象
    返回值：是否初始化成功
    更新时间：2015/7/20*/
    bool init();

    /**
    说明：获取有效数据
    参数:二进制数据地址,有效数据量
    返回值：是否截取成功
    更新时间：2015/10/8*/
    bool getValidData(unsigned char*& pchBinary, int &iLength);

    /**
    说明：获取所有数据
    参数:二进制数据地址,有效数据量
    返回值：是否截取成功
    更新时间：2015/10/8*/
    bool getBlockData(unsigned char*& pchBinary, int &iLength);

    /*
    说明：获取有效数据长度
    返回值：有效数据长度
    更新时间：2015/10/9*/
    int getVailDataLength();

    /**
    参数：要放入的有效数据，要放入的有效数据量
    说明：将数据放入有效数据字段
    返回值：是否放置成功
    更新时间：2015/10/8*/
    bool putValidData(unsigned char* pchBinary,  int iLength);

    /**
    参数：要放入的数据，要放入的数据量
    说明：将数据放入有效数据字段
    返回值：是否放置成功
    更新时间：2015/10/25*/
    bool putBlockData(unsigned char* pchBinary,  int iLength);

    /**
    说明：将block中数据重置
    返回值：是否重置成功
    更新时间：2015/10/8*/
    bool resetBlock();
};
