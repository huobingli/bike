#pragma once

//记录数据矩阵中关联度大于某个值的数据参数
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
	//目标站点
	int m_iTargetStation;
	//关系站点
	int m_iRelationStation;
	//站点关系
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
	//站点ID
	int m_iStationID;
	//站点标志
	int m_iFlag;

};