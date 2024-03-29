#include "stdafx.h"
#include "Monster.h"
#include "Bullet.h"
#include "Rect.h"
#include "MinAoe.h"
#include "Item.h"

CMonster::CMonster()
{
}


CMonster::~CMonster()
{
}

void CMonster::Initialize()
{
	m_tInfo.fX = float(WINCX/2);
	m_tInfo.fY = 1.f;
	m_tInfo.iCX = 60;
	m_tInfo.iCY = 60;

	m_iHp = 10;       //몬스터 최대 체력
	m_fSpeed = 3.25f;

	Set_Color(160, 60, 160);
}

int CMonster::Update()
{
	if (m_bDead) {
		m_pItem->emplace_back(CAbstractFactory<CItem>::Create(m_tInfo.fX, m_tInfo.fY));
		return OBJ_DEAD;
	}
	int iTime = rand();

	Monster_move(250);


	float fX = 0.f, fY = 0.f, fDis = 0.f;
	fX = m_pTarget->Get_Info().fX - m_tInfo.fX;
	fY = m_pTarget->Get_Info().fY - m_tInfo.fY;
	fDis = sqrtf(fX * fX + fY * fY);
	m_fAngle = acosf(fX / fDis) * 180.f / PI;

	if (m_tInfo.fY < m_pTarget->Get_Info().fY)
		m_fAngle *= -1.f;

	//////////////총알발사 --> 하드코딩 수정필요
	if (iTime % 1300 >= 11 && iTime % 1300 <= 13) // 12갈래총알
	{
		m_pMonsterBullet->emplace_back(Create_Bullet<CBullet>());
		m_pMonsterBullet->emplace_back(Create_Bullet<CBullet>(m_fAngle + 30.f));
		m_pMonsterBullet->emplace_back(Create_Bullet<CBullet>(m_fAngle + 60.f));
		m_pMonsterBullet->emplace_back(Create_Bullet<CBullet>(m_fAngle + 90.f));
		m_pMonsterBullet->emplace_back(Create_Bullet<CBullet>(m_fAngle + 120.f));
		m_pMonsterBullet->emplace_back(Create_Bullet<CBullet>(m_fAngle + 150.f));
		m_pMonsterBullet->emplace_back(Create_Bullet<CBullet>(m_fAngle - 180.f));
		m_pMonsterBullet->emplace_back(Create_Bullet<CBullet>(m_fAngle - 30.f));
		m_pMonsterBullet->emplace_back(Create_Bullet<CBullet>(m_fAngle - 60.f));
		m_pMonsterBullet->emplace_back(Create_Bullet<CBullet>(m_fAngle - 90.f));
		m_pMonsterBullet->emplace_back(Create_Bullet<CBullet>(m_fAngle - 120.f));
		m_pMonsterBullet->emplace_back(Create_Bullet<CBullet>(m_fAngle - 150.f));
	}
	else if (iTime % 1300 >= 14 && iTime % 1300 <= 19) //6갈래총알
	{
		m_pMonsterBullet->emplace_back(Create_Bullet<CMinAoe>());
		m_pMonsterBullet->emplace_back(Create_Bullet<CMinAoe>(m_fAngle + 60.f));
		m_pMonsterBullet->emplace_back(Create_Bullet<CMinAoe>(m_fAngle + 120.f));
		m_pMonsterBullet->emplace_back(Create_Bullet<CMinAoe>(m_fAngle + 180.f));
		m_pMonsterBullet->emplace_back(Create_Bullet<CMinAoe>(m_fAngle + 240.f));
		m_pMonsterBullet->emplace_back(Create_Bullet<CMinAoe>(m_fAngle + 300.f));

	}
	else if (iTime % 1300 >= 20 && iTime % 1300 <= 30) // 4갈래총알
	{
		m_pMonsterBullet->emplace_back(Create_Bullet<CRect>(90.f));
		m_pMonsterBullet->emplace_back(Create_Bullet<CRect>(180.f));
		m_pMonsterBullet->emplace_back(Create_Bullet<CRect>(270.f));
		m_pMonsterBullet->emplace_back(Create_Bullet<CRect>(360.f));


	}
	else if (iTime % 1300 >= 31 && iTime % 1300 <= 60) // 일반공격
	{
		m_pMonsterBullet->emplace_back(Create_Bullet<CBullet>());
	}

	Update_Rect();
	return OBJ_NOEVENT;
}

void CMonster::Late_Update()
{
	if (0 >= m_iHp)
		m_bDead = true;
}

void CMonster::Render(HDC _DC)
{
	Ellipse(_DC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
}

void CMonster::Release()
{
}