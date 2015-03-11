#ifndef CORE
#define CORE

#include "MaxCheck.h"
//���� ������
#define BoardMin 0
//���� �ִ밪
#define BoardMax 19
/*
�ٵ����� ������ ��� ���� Ŭ������ �����ϱ� ����
���
*/

/*
�ٵ��ǿ����� ������ ����ִ�
���� ���� �÷��� �ִ���=m_player

���� x��ǥ = m_x
���� y��ǥ = m_y
2015.2.23
23:28
*/
class CCore{
private:
	int m_Player;
	int m_EnemyPlayer;
	// -1�� ��� �߸� ����
	int m_x;
	// -1�� ��� �߸� ����
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
	//����Ȱ� 1�� ���ϱ�
	void AddCounter(int arr);
	//����Ȱ� 1�� �ʱ�ȭ�ϱ�
	void CounterInit(int arr);
	//����Ȱ� ���
	int GetCounter(int arr);
	//���������� �ִ��̾��� ����
	CCalCounter GetCCalCounter(int num);
	void AddDirectionCounter(int num);
	void InitDirectionCounter(int num);
	int CoreDirectionX(int num);
	int CoreDirectionY(int num);

	void CalMaxCounter(int y, int x, int Player);
};

#endif CORE