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
˵�������ݷ��ʲ㣬�ṩд���ȡ�ӿ�
����ʱ�䣺2015/9/30*/
class CFrameDAL{
    CDALOriginalFile *m_objSourceFile;       //Դ�ļ�����
    CDALFile *m_objTargetFile;               //Ŀ���ļ�����
    CDALFile *m_objRelationFile;             //�����ļ�����
    CControlPre *m_objPreControl;            //Ԥ������ƶ���
    CControlAlgorithm *m_objAlgorithmControl; //�㷨������ƶ���

    /**
    ���ƣ�init 
    ˵������ʼ�����ݷ��ʲ���
    ����ʱ�䣺2015/9/30*/
    bool init();
public:
    CFrameDAL();
    ~CFrameDAL();

    /**
    ���ƣ�getUseRecord
    ��ڲ�������ʼλ�ã��軹���ݼ��϶����ַ�����ζ�ȡ����
    ����ֵ ���Ƿ��ȡ�ɹ�
    ����ʱ�䣺2015/10/8*/
    bool getUseRecord(CEntityTripDataSet *&pBorrowDataOut, int iNumIn, int iPos=-1);

    /**
    ���ƣ�putPreprocessedData 
    ��ڲ�������ʼλ�ã�ͳ�����ݼ��϶����ַ
    ����ֵ ���Ƿ�д��ɹ�
    ����ʱ�䣺2015/9/30*/
    bool putPreprocessedData(CEntityTimeSliceCountSet *pStatisticalDataRecordSetIn, int iPosIn=-1);

    /**
    ���ƣ�getPreprocessedData
    ��ڲ�������ʼλ�ã�ͳ�����ݼ��϶����ַ�������������ҵ���߼����з�����ڴ�ģ�����ҵ���߼������ͷţ�����¼��
    ����ֵ���Ƿ��ȡ�ɹ�
    ����ʱ�䣺2015/9/30*/
    bool getPreprocessedData(CEntityTimeSliceCountSet *&pStatisticalDataRecordSetOut, int iPos=-1, int iNumIn=-1);

    /**
    ���ƣ�putRelatedData 
    ��ڲ�������ʼλ�ã��������ݼ��϶���ָ�루�����������ҵ���߼����з�����ڴ�ģ�����ҵ���߼������ͷţ�
    ����ֵ ���Ƿ�д��ɹ�
    ����ʱ�䣺2015/9/30*/
    bool putRelatedData(CListWriteRelationSet *pRelatedDataRecordSetIn, int iPosIn=-1);

    /**
    ���ƣ�getRelatedData
    ��ڲ�������ʼλ�ã�ͳ�����ݼ��϶����ַ�������������ҵ���߼����з�����ڴ�ģ�����ҵ���߼������ͷţ�����¼��
    ����ֵ���Ƿ��ȡ�ɹ�
    ����ʱ�䣺2015/11/6*/
    bool getRelatedData(CListWriteRelationSet *&pRelatedDataRecordSetOut, int iPos=-1, int iNumIn=-1);

    /**
    ���ƣ�initPreProcessControl
    ��ڲ�����Դ�ļ����ƺ�Ŀ���ļ�����/��
    ����ֵ ���Ƿ�Ԥ��ʼ���ɹ�
    ����ʱ�䣺2015/9/30*/
    bool initPreProcessControl();

    /**
    ���ƣ�doPreprocessRehabilitation
    ��ڲ�������
    ����ֵ ���Ƿ�Ԥ�����ƺ�ɹ�
    ����ʱ�䣺2015/9/30*/
    bool doPreprocessRehabilitation();

    /**
    ���ƣ�initPreProcessControl
    ��ڲ�����Դ�ļ����ƺ�Ŀ���ļ�����
    ����ֵ ���Ƿ��㷨��ʼ���ɹ�
    ����ʱ�䣺2015/9/30*/
    //bool initAlgorithmControl(char *sSourceFileNameIn, char *sTargetFileNameIn);
    bool initAlgorithmControl();

    /**
    ���ƣ�doAlgorithmRehabilitation
    ��ڲ�������
    ����ֵ ���Ƿ��㷨�����ƺ�ɹ�
    ����ʱ�䣺2015/9/30*/
    bool doAlgorithmRehabilitation();

    /**
    ����:writeStdFile
    ��ڲ�����Ҫд����ַ���
    ����ֵ���Ƿ�д��ɹ�
    ����ʱ�䣺2015/11/5*/
    bool writeStdFile(char *chTest);

	/**
	����:writemaxMinStdFile
	˵�����ļ������ھʹ������ļ����ھ��������
	��ڲ�����Ҫд����ַ���
	����ֵ���Ƿ�д��ɹ�
	����ʱ�䣺2015/11/5*/
	bool writeMaxMinStdFile(char *chTest);

	bool writeRelationStdFile(char *chTest);

	bool writeClusterStdFile(char *chTest);
}; 