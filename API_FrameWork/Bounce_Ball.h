#pragma once
#include "Obj.h"
class CBounce_Ball :
	public CObj
{
public:
	CBounce_Ball();
	virtual ~CBounce_Ball();
public:
	// CObj을(를) 통해 상속됨
	virtual void Initialize();
	virtual int Update();
	virtual void Late_Update();
	virtual void Render(HDC _DC);
	virtual void Release();

public:
	void Set_Dir(BULLET::DIR _eDir) { m_eDir = _eDir; }

private:
	BULLET::DIR		m_eDir;
	int m_iTime=0;
};

