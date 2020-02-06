#pragma once
#include "Obj.h"
class CShotgun :
	public CObj
{
public:
	CShotgun();
	virtual ~CShotgun();

public:
	// CObj��(��) ���� ��ӵ�
	virtual void Initialize();
	virtual int Update();
	virtual void Late_Update();
	virtual void Render(HDC _DC);
	virtual void Release();

public:
	void Set_Dir(BULLET::DIR _eDir) { m_eDir = _eDir; }

private:
	BULLET::DIR		m_eDir;
};
