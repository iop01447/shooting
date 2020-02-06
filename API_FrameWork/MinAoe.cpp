#include "stdafx.h"
#include "MinAoe.h"


CMinAoe::CMinAoe()
	: m_eDir(BULLET::DIR_END)
{
}


CMinAoe::~CMinAoe()
{
	Release();
}

void CMinAoe::Initialize()
{
	m_tInfo.iCX = 15;
	m_tInfo.iCY = 15;
	m_fSpeed = 10.f;

	//�Ѿ˶��°� �Ⱦ ������.
	m_fAngle = 45.f;
}

int CMinAoe::Update()
{
	if (m_bDead)
		return OBJ_DEAD;

	m_tInfo.fX += cosf(m_fAngle * PI / 180.f) * m_fSpeed;
	m_tInfo.fY -= sinf(m_fAngle * PI / 180.f) * m_fSpeed;
	m_fAngle += 60.f;
	m_fSpeed += 1.f;

	Update_Rect();

	return OBJ_NOEVENT;
}

void CMinAoe::Late_Update()
{
	if (25 >= m_tRect.top || 25 >= m_tRect.left
		|| WINCX - 25 <= m_tRect.right || WINCY - 25 <= m_tRect.bottom)
		m_bDead = true;
}

void CMinAoe::Render(HDC _DC)
{
	Ellipse(_DC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
}

void CMinAoe::Release()
{
}
