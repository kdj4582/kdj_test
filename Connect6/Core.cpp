#include"Core.h"
#include"MaxCore.h"
#define TRUE 1;
#define FALSE 0;
CCore::CCore(){
	CCore::CCore(-1, -1);
}

/*
플레이어는 클래스 포인터로 만들어서 조작하고
에너미플레이어도 마찬가지
맥스카운터와 디렉션은 함수를 만들거임
2015.2.23
23:34
*/

CCore::CCore(int y, int x){
	m_Player = 0;
	m_EnemyPlayer = 0;
	m_x = x;
	m_y = y;
}

void CCore::SetX(int x){
	this->m_x = x;
}

void CCore::SetY(int y){
	this->m_y = y;
}

int CCore::GetX(){
	return this->m_x;
}

int CCore::GetY(){
	return this->m_y;
}

void CCore::SetPlayer(int Player){
	this->m_Player = Player;
	if (Player == 1){
		this->m_EnemyPlayer = 2;
	}
	else if (Player == 2)
	{
		this->m_EnemyPlayer = 1;
	}

}

int CCore::GetPlayer(){
	return m_Player;
}

int CCore::GetEnemyPlayer(){
	return m_EnemyPlayer;
}

void CCore::SetMaxDirector(int arr, int y, int x){
	m_Max[arr].SetDirection(y, x);
}

void CCore::AddCounter(int arr){
	m_Max[arr].AddCounter();
}

void CCore::CounterInit(int arr){
	m_Max[arr].CounterInit();

}

int CCore::GetCounter(int arr){
	return m_Max[arr].GetCounter();
}

void CCore::AddDirectionCounter(int num){
	m_Max[num].AddDirectionCounter();
}
void CCore::InitDirectionCounter(int num){
	m_Max[num].InitDirectionCounter();
}

int CCore::CoreDirectionX(int num){
	return m_Max[num].GetDirectionX();
}
int CCore::CoreDirectionY(int num){
	return m_Max[num].GetDirectionY();
}

CCalCounter CCore::GetCCalCounter(int num){
	return m_Max[num];
}

CCalCounter::CCalCounter(){
	//2015.2.25 19:06 Counter를 0으로 썼었다가 잘못써서 1로 수정
	m_Counter = 1;
	m_DirectionX = 0;
	m_DirectionY = 0;
}

void CCalCounter::SetDirection(int y, int x){
	this->m_DirectionY = y;
	this->m_DirectionX = x;
}

void CCalCounter::AddCounter(){
	m_Counter++;
}

void CCalCounter::CounterInit(){
	//2015.2.25 19:06 Counter를 0으로 썼었다가 잘못써서 1로 수정
	m_Counter = 1;
}

int CCalCounter::GetCounter(){
	return m_Counter;
}

void CCalCounter::InitDirectionCounter(){
	m_DirectionCounter = 1;
};
void CCalCounter::AddDirectionCounter(){
	m_DirectionCounter++;
};
int CCalCounter::GetDirectionCounter(){
	return m_DirectionCounter;
}

int CCalCounter::GetDirectionX(){
	return m_DirectionX;
}

int CCalCounter::GetDirectionY(){
	return m_DirectionY;
}

CMaxCore::CMaxCore(){
	m_Player = 0;
	m_x = -1;
	m_y = -1;
}

CMaxCore::CMaxCore(CCore CopyCore, int Direction){
	m_Player = CopyCore.GetPlayer();
	m_EnemyPlayer = CopyCore.GetEnemyPlayer();
	m_x = CopyCore.GetX();
	m_y = CopyCore.GetY();
	m_Max = CopyCore.GetCCalCounter(Direction);
}

int CMaxCore::GetCounter(){
	return m_Max.GetDirectionCounter();
}

int CMaxCore::GetX(){
	return m_x;
}

int CMaxCore::GetY(){
	return m_y;
}

int CMaxCore::GetDirectionX(){
	return m_Max.GetDirectionX();
}

int CMaxCore::GetDirectionY(){
	return m_Max.GetDirectionY();
}

int CMaxCore::GetEnemyPlayer(){
	return m_EnemyPlayer;
}