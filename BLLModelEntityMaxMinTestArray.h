#pragma once
class CBLLModelEntityMaxMinTestArray
{
public:
	CBLLModelEntityMaxMinTestArray()
	{
		m_dMaxStationRelation = 0;
		m_dMinStationRelation = 0;

	}
	~CBLLModelEntityMaxMinTestArray()
	{

	}

	double getMaxStationRelation()
	{
		return m_dMaxStationRelation;
	}
	double getMinStationRelation()
	{
		return m_dMinStationRelation;
	}

	void setMaxStationRelation(double dMaxStationRelation)
	{
		m_dMaxStationRelation = dMaxStationRelation;
	}

	void setMinStationRelation(double dMinStationRelation)
	{
		m_dMinStationRelation = dMinStationRelation;
	}

private:
	double m_dMaxStationRelation;
	double m_dMinStationRelation;
};

