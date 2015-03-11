#ifndef MAXCHECK
#define MAXCHECK
/*
�¸��� �� �ִ� ���ɼ��� �ִ���,
���� � �̾����ִ��� = m_MaxCounter
��������� �̾��� �ִ��� = m_DirectorX,m_DirecotY
*/
class CCalCounter{
private:
	
	int m_Counter;
	int m_DirectionX;
	int m_DirectionY;
	// -1�� ��� �¸��� ���ɼ��� ��������Ÿ��
	int m_DirectionCounter;

public:
	CCalCounter();
	//����Ȱ� 1�� ���ϱ�
	void AddCounter();
	//����Ȱ� 1�� �ʱ�ȭ�ϱ�
	void CounterInit();
	void SetDirection(int y, int x);
	int GetDirectionX();
	int GetDirectionY();
	// ����Ǿ��ִ� �� ���
	int GetCounter();
	void InitDirectionCounter();
	void AddDirectionCounter();
	// �¸��Ұ��ɼ��ִ����� �� ���
	int GetDirectionCounter();
};
#endif MAXCHECK