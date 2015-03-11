#ifndef MAXCORE
#define MAXCORE

#include "MaxCheck.h"
#include "Core.h"
/*
바둑판의 선택이 최우선 될 정보를 담기 위한 클래스
헤더
*/
class CMaxCore{
private:
	int m_Player;
	int m_EnemyPlayer;
	// -1의 경우 잘못 생성
	int m_x;
	// -1의 경우 잘못 생성
	int m_y;
	CCalCounter m_Max;
public:
	CMaxCore();
	CMaxCore(CCore CopyCore,int Direction);
	
	int GetEnemyPlayer();
	//연결 가능성 얻는 카운터
	int GetCounter();
	int GetDirectionX();
	int GetDirectionY();
	int GetX();
	int GetY();
	
};

#endif MAXCORE