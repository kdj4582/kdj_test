#include"Core.h"
#define TRUE 1;
#define FALSE 0;
CCore::CCore(){
	CCore::CCore(-1, -1);
}

/*
�÷��̾�� Ŭ���� �����ͷ� ���� �����ϰ�
���ʹ��÷��̾ ��������
�ƽ�ī���Ϳ� �𷺼��� �Լ��� �������
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

void CCore::SetMaxDirector(int arr, int y, int x){
	m_Max[arr].SetDirection(y, x);
}

void CCore::AddCounter(int arr){
	m_Max[arr].AddMaxCounter();
	int m;
}

void CCore::CounterInit(int arr){
	m_Max[arr].CounterInit();

}

int CCore::GetCounter(int arr){
	return m_Max[arr].GetCounter();
}

CCalMax::CCalMax(){
	//2015.2.25 19:06 Counter�� 0���� ����ٰ� �߸��Ἥ 1�� ����
	m_MaxCounter = 1;
	m_DirectionX = 0;
	m_DirectionY = 0;
}

void CCalMax::SetDirection(int y, int x){
	this->m_DirectionY = y;
	this->m_DirectionX = x;
}

void CCalMax::AddMaxCounter(){
	m_MaxCounter++;
}

void CCalMax::CounterInit(){
	//2015.2.25 19:06 Counter�� 0���� ����ٰ� �߸��Ἥ 1�� ����
	m_MaxCounter = 1;
}

int CCalMax::GetCounter(){
	return m_MaxCounter;
}