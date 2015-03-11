#ifndef CORE
#define CORE

#include "MaxCheck.h"
//맵의 최저값
#define BoardMin 0
//맵의 최대값
#define BoardMax 19
/*
바둑판의 정보를 담기 위한 클래스를 관리하기 위한
헤더
*/

/*
바둑판에대한 정보가 담겨있다
무슨 돌이 올려져 있는지=m_player

현재 x좌표 = m_x
현재 y좌표 = m_y
2015.2.23
23:28
*/
class CCore{
private:
	int m_Player;
	int m_EnemyPlayer;
	// -1의 경우 잘못 생성
	int m_x;
	// -1의 경우 잘못 생성
	int m_y;
	
	CCalCounter m_Max[4];
public:
	CCore();
	CCore(int y, int x);

	void SetX(int x);
	void SetY(int y);
	int GetX();
	int GetY();
	void SetPlayer(int Player);
	int GetPlayer();
	int GetEnemyPlayer();
	void SetMaxDirector(int arr, int y, int x);
	//연결된값 1씩 더하기
	void AddCounter(int arr);
	//연결된값 1로 초기화하기
	void CounterInit(int arr);
	//연결된값 얻기
	int GetCounter(int arr);
	//방향정보와 최대이어짐 정보
	CCalCounter GetCCalCounter(int num);
	void AddDirectionCounter(int num);
	void InitDirectionCounter(int num);
	int CoreDirectionX(int num);
	int CoreDirectionY(int num);

	void CalMaxCounter(int y, int x, int Player);
};

#endif CORE