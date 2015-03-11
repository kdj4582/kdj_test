#ifndef MAXCORE
#define MAXCORE

#include "MaxCheck.h"
#include "Core.h"
/*
�ٵ����� ������ �ֿ켱 �� ������ ��� ���� Ŭ����
���
*/
class CMaxCore{
private:
	int m_Player;
	int m_EnemyPlayer;
	// -1�� ��� �߸� ����
	int m_x;
	// -1�� ��� �߸� ����
	int m_y;
	CCalCounter m_Max;
public:
	CMaxCore();
	CMaxCore(CCore CopyCore,int Direction);
	
	int GetEnemyPlayer();
	//���� ���ɼ� ��� ī����
	int GetCounter();
	int GetDirectionX();
	int GetDirectionY();
	int GetX();
	int GetY();
	
};

#endif MAXCORE