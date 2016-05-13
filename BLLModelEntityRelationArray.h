#pragma once

//��¼���ݾ����й����ȴ���ĳ��ֵ�����ݲ���
class CBLLModelEntityRelationArray
{
public:
	CBLLModelEntityRelationArray()
	{
		m_iTargetStation = 0;
		m_iRelationStation = 0;
		m_dStationRelation = 0;
		m_iflag = 0;
	}
	~CBLLModelEntityRelationArray()
	{
	
	}

	int getTargetStation()
	{
		return m_iTargetStation;
	}

	void setTargetStation(int iTargetStation)
	{
		m_iTargetStation = iTargetStation;
	}

	int getRelationStation()
	{
		return m_iRelationStation;
	}

	void setRelationStation(int iRelationStation)
	{
		m_iRelationStation = iRelationStation;
	}

	double getStationRelation()
	{
		return m_dStationRelation;
	}

	void setStationRelation(double dStationRelation)
	{
		m_dStationRelation = dStationRelation;
	}

	void setflag(int iflag)
	{
		m_iflag = iflag;
	}

	int getflag()
	{
		return m_iflag;
	}
private:
	//Ŀ��վ��
	int m_iTargetStation;
	//��ϵվ��
	int m_iRelationStation;
	//վ���ϵ
	double m_dStationRelation;

	int m_iflag;
};



class CBLLModelEntityStationArray{
public:
	void setStationID(int iStationID)
	{
		m_iStationID = iStationID;
	}

	int getStationID()
	{
		return m_iStationID;
	}

	void setFlag(int iFlag)
	{
		m_iFlag = iFlag;
	}

	int getFlag()
	{
		return m_iFlag;
	}

private:
	//վ��ID
	int m_iStationID;
	//վ���־
	int m_iFlag;

};