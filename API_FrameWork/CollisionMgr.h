#pragma once

#ifndef __COLLISIONMGR_H__
#define __COLLISIONMGR_H__



class CCollisionMgr
{
public:
	CCollisionMgr();
	~CCollisionMgr();

public:
	// 객체를 생성하지 않고도 스코프 연산자를 통해 호출이 가능하다!
	// 인자로 list를 받는 이유는 충돌 객체가 하나라고 확답할 수 없다!
	// -> 다 대 다 충돌 처리를 검사하기 위해 list를 넘겨준다.
	static void Collision_Rect(list<CObj*>& _Dst, list<CObj*>& _Src);
	static void Collision_Rect(list<CObj*>& _Dst, list<CObj*>& _Src, OBJID::ID _DstId, OBJID::ID _SrcId);
//	void Collision_Shield_Rect(list<CObj*>& _Dst, list<CObj*>& _Src);
	static void Collision_Sphere(list<CObj*>& _Dst, list<CObj*>& _Src);
	static bool Check_Sphere(CObj* _Dst, CObj* _Src);
};


#endif // !__COLLISIONMGR_H__
