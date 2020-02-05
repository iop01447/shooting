#include "stdafx.h"
#include "Bullet.h"


CBullet::CBullet()
	: m_eDir(BULLET::END)
{
}


CBullet::~CBullet()
{
	Release();
}

void CBullet::Initialize()
{
	m_tInfo.iCX = 20;
	m_tInfo.iCY = 20;

	m_fSpeed = 5.f;
}

int CBullet::Update()
{
	if (m_bDead)
		return OBJ_DEAD;

	m_tInfo.fY -= m_fSpeed;

	Update_Rect();

	return OBJ_NOEVENT;
}

void CBullet::Late_Update()
{
	if (25 >= m_tRect.top || 25 >= m_tRect.left
		|| WINCX - 25 <= m_tRect.right || WINCY - 25 <= m_tRect.bottom)
		m_bDead = true;
}

void CBullet::Render(HDC _DC)
{
	Ellipse(_DC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
}

void CBullet::Release()
{
}
