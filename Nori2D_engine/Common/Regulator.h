#pragma once


class Regulator
{
	float m_UpdatePeriod;
	float m_Current;

public:
	Regulator(float NumUpdatesPerSecondRqd)
	{
		m_UpdatePeriod = NumUpdatesPerSecondRqd;
		m_Current = m_UpdatePeriod;
	}

	bool isReady(float dt)
	{
		m_Current -= dt;
		if (m_Current<=0.f) {
			m_Current = m_UpdatePeriod;
			return true;
		}
		return false;
	}

	bool Tick(float dt) 
	{ 
		m_Current -= dt; 
		return (m_Current<=0.f);	
	}

	void Reset() { m_Current = m_UpdatePeriod; }
};





