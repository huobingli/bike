#pragma once
#include "DALFile.h"
#include "DALOriginalFile.h"
#include "DALControlAlgorithm.h"
#include "DALControlPre.h"
#include "EntityTripDataSet.h"
#include "ListWriteRelationSet.h"
#include "EntityTimeSliceCountSet.h"
#include <string>
using namespace std;

/**
说明：数据访问层，提供写入读取接口
更新时间：2015/9/30*/
class CFrameDAL{
    CDALOriginalFile *m_objSourceFile;       //源文件对象
    CDALFile *m_objTargetFile;               //目标文件对象
    CDALFile *m_objRelationFile;             //关联文件对象
    CControlPre *m_objPreControl;            //预处理控制对象
    CControlAlgorithm *m_objAlgorithmControl; //算法处理控制对象

    /**
    名称：init 
    说明：初始化数据访问层框架
    更新时间：2015/9/30*/
    bool init();
public:
    CFrameDAL();
    ~CFrameDAL();

    /**
    名称：getUseRecord
    入口参数：开始位置，借还数据集合对象地址，单次读取的量
    返回值 ：是否读取成功
    更新时间：2015/10/8*/
    bool getUseRecord(CEntityTripDataSet *&pBorrowDataOut, int iNumIn, int iPos=-1);

    /**
    名称：putPreprocessedData 
    入口参数：开始位置，统计数据集合对象地址
    返回值 ：是否写入成功
    更新时间：2015/9/30*/
    bool putPreprocessedData(CEntityTimeSliceCountSet *pStatisticalDataRecordSetIn, int iPosIn=-1);

    /**
    名称：getPreprocessedData
    入口参数：开始位置，统计数据集合对象地址（这个对象是在业务逻辑层中分配好内存的，并在业务逻辑层中释放），记录数
    返回值：是否读取成功
    更新时间：2015/9/30*/
    bool getPreprocessedData(CEntityTimeSliceCountSet *&pStatisticalDataRecordSetOut, int iPos=-1, int iNumIn=-1);

    /**
    名称：putRelatedData 
    入口参数：开始位置，关联数据集合对象指针（这个对象是在业务逻辑层中分配好内存的，并在业务逻辑层中释放）
    返回值 ：是否写入成功
    更新时间：2015/9/30*/
    bool putRelatedData(CListWriteRelationSet *pRelatedDataRecordSetIn, int iPosIn=-1);

    /**
    名称：getRelatedData
    入口参数：开始位置，统计数据集合对象地址（这个对象是在业务逻辑层中分配好内存的，并在业务逻辑层中释放），记录数
    返回值：是否读取成功
    更新时间：2015/11/6*/
    bool getRelatedData(CListWriteRelationSet *&pRelatedDataRecordSetOut, int iPos=-1, int iNumIn=-1);

    /**
    名称：initPreProcessControl
    入口参数：源文件名称和目标文件名称/无
    返回值 ：是否预初始化成功
    更新时间：2015/9/30*/
    bool initPreProcessControl();

    /**
    名称：doPreprocessRehabilitation
    入口参数：无
    返回值 ：是否预处理善后成功
    更新时间：2015/9/30*/
    bool doPreprocessRehabilitation();

    /**
    名称：initPreProcessControl
    入口参数：源文件名称和目标文件名称
    返回值 ：是否算法初始化成功
    更新时间：2015/9/30*/
    //bool initAlgorithmControl(char *sSourceFileNameIn, char *sTargetFileNameIn);
    bool initAlgorithmControl();

    /**
    名称：doAlgorithmRehabilitation
    入口参数：无
    返回值 ：是否算法处理善后成功
    更新时间：2015/9/30*/
    bool doAlgorithmRehabilitation();

    /**
    名称:writeStdFile
    入口参数：要写入的字符串
    返回值：是否写入成功
    更新时间：2015/11/5*/
    bool writeStdFile(char *chTest);

	/**
	名称:writemaxMinStdFile
	说明：文件不存在就创建，文件存在就清空内容
	入口参数：要写入的字符串
	返回值：是否写入成功
	更新时间：2015/11/5*/
	bool writeMaxMinStdFile(char *chTest);

	bool writeRelationStdFile(char *chTest);

	bool writeClusterStdFile(char *chTest);
}; 