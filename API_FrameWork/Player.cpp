#include "stdafx.h"
#include "Player.h"
#include "Bullet.h"


CPlayer::CPlayer()
	:m_iBulletCreateTime(100), m_OldTime(GetTickCount()), m_hp(5)
{
	ZeroMemory(&m_Points, sizeof(m_Points));
}


CPlayer::~CPlayer()
{
	Release();
}

void CPlayer::Initialize()
{
	m_tInfo.fX = WINCX / 2;
	m_tInfo.fY = WINCY - 100;
	m_tInfo.iCX = 30;
	m_tInfo.iCY = 15;

	m_fDis = 100.f;
	m_fSpeed = 5.f;

	m_fAngle = 90.f;

	Set_Color(55, 52, 235);
	Set_Pen_UnVisible();

	m_StarPos[0] = { 101, 0 };
	m_StarPos[1] = { 77, 77 };
	m_StarPos[2] = { 0, 77 };
	m_StarPos[3] = { 62, 125 };
	m_StarPos[4] = { 39, 201 };
	m_StarPos[5] = { 101, 153 };
	m_StarPos[6] = { 163, 201 };
	m_StarPos[7] = { 138, 125 };
	m_StarPos[8] = { 201, 77 };
	m_StarPos[9] = { 124, 77 };
	m_StarPos[10] = { 101, 0 };
	for (int i = 0; i < 11; ++i) {
		m_StarPos[i].x *= 0.1;
		m_StarPos[i].y *= 0.1;
	}
}

int CPlayer::Update()
{
	if (m_bDead)
		return OBJ_DEAD;

	// �̵�
	if (GetAsyncKeyState(VK_LEFT))
	{
		if (GetAsyncKeyState(VK_UP))
		{
			m_tInfo.fX -= m_fSpeed / sqrtf(2.f);
			m_tInfo.fY -= m_fSpeed / sqrtf(2.f);
		}
		else if (GetAsyncKeyState(VK_DOWN))
		{
			m_tInfo.fX -= m_fSpeed / sqrtf(2.f);
			m_tInfo.fY += m_fSpeed / sqrtf(2.f);
		}
		else
			m_tInfo.fX -= m_fSpeed;
	}
	else if (GetAsyncKeyState(VK_RIGHT))
	{
		if (GetAsyncKeyState(VK_UP))
		{
			m_tInfo.fX += m_fSpeed / sqrtf(2.f);
			m_tInfo.fY -= m_fSpeed / sqrtf(2.f);
		}
		else if (GetAsyncKeyState(VK_DOWN))
		{
			m_tInfo.fX += m_fSpeed / sqrtf(2.f);
			m_tInfo.fY += m_fSpeed / sqrtf(2.f);
		}
		else
			m_tInfo.fX += m_fSpeed;
	}
	else if (GetAsyncKeyState(VK_UP))
		m_tInfo.fY -= m_fSpeed;
	else if (GetAsyncKeyState(VK_DOWN))
		m_tInfo.fY += m_fSpeed;

	// �Ѿ� ���
	int size = 7;
	BULLET::SHAPE shape = BULLET::SHAPE::ELLIPSE;
	if (GetAsyncKeyState(VK_SPACE) && (GetTickCount() - m_OldTime) > m_iBulletCreateTime) {
		m_OldTime = GetTickCount();
		m_pBullet->emplace_back(Create_Bullet(m_tInfo.fX-size, m_tInfo.fY-3*size-10, shape));
		m_pBullet->emplace_back(Create_Bullet(m_tInfo.fX+size, m_tInfo.fY-3*size-10, shape));
		m_pBullet->emplace_back(Create_Bullet(m_tInfo.fX-2*size, m_tInfo.fY-10, shape));
		m_pBullet->emplace_back(Create_Bullet(m_tInfo.fX+2*size, m_tInfo.fY-10, shape));
	}

	// ��ų
	if (GetAsyncKeyState('Q'))
	{
		Skill_1();
	}

	Update_Rect();
	Update_Polygon();

	return OBJ_NOEVENT;
}

void CPlayer::Late_Update()
{
}

void CPlayer::Render(HDC _DC)
{
	// �����
	SelectObject(_DC, Set_Color(55, 52, 235));
	Polygon(_DC, m_Points, 4); 
	//Rectangle(_DC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);

	// ���
	SelectObject(_DC, Set_Color(255, 0, 0));
	for (int i = 0; i < m_hp; ++i) {
		Draw_Star(_DC, 50 + i*25, 45);
	}
}

void CPlayer::Release()
{
}

CObj* CPlayer::Create_Bullet()
{
	CObj* pObj = CAbstractFactory<CBullet>::Create(m_tInfo.fX, m_tInfo.fY, m_fAngle);

	return pObj;
}

CObj* CPlayer::Create_Bullet(BULLET::DIR _eDIr)
{
	CObj* pObj = CAbstractFactory<CBullet>::Create(m_tInfo.fX, m_tInfo.fY);
	dynamic_cast<CBullet*>(pObj)->Set_Dir(_eDIr);

	return pObj;
}

CObj * CPlayer::Create_Bullet(float x, float y, BULLET::SHAPE _eShape)
{
	CObj* pObj = CAbstractFactory<CBullet>::Create(x, y, m_fAngle);
	dynamic_cast<CBullet*>(pObj)->Set_Shape(_eShape);
	pObj->Set_Color(52, 137, 235);
	pObj->Set_Pen_UnVisible();

	return pObj;
}

void CPlayer::Update_Polygon()
{
	m_Points[0].x = (LONG)m_tInfo.fX - 30;
	m_Points[0].y = (LONG)m_tInfo.fY + 20;
	m_Points[1].x = (LONG)m_tInfo.fX;
	m_Points[1].y = (LONG)m_tInfo.fY - 10;
	m_Points[2].x = (LONG)m_tInfo.fX + 30;
	m_Points[2].y = (LONG)m_tInfo.fY + 20;
	m_Points[3].x = (LONG)m_tInfo.fX;
	m_Points[3].y = (LONG)m_tInfo.fY + 10;
}

void CPlayer::Draw_Star(HDC _DC, int _x, int _y)
{
	POINT pos[11];
	for (int i = 0; i < 11; ++i) {
		pos[i].x = m_StarPos[i].x + _x;
		pos[i].y = m_StarPos[i].y + _y;
	}

	Polygon(_DC, pos, 11);
}

void CPlayer::Skill_1()
{
	m_pBullet->emplace_back(Create_Bullet());
}
