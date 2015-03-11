#ifndef MAXCHECK
#define MAXCHECK
/*
승리할 수 있는 가능성이 있는지,
돌이 몇개 이어져있는지 = m_MaxCounter
어떤방향으로 이어져 있는지 = m_DirectorX,m_DirecotY
*/
class CCalCounter{
private:
	
	int m_Counter;
	int m_DirectionX;
	int m_DirectionY;
	// -1의 경우 승리할 가능성이 없음을나타냄
	int m_DirectionCounter;

public:
	CCalCounter();
	//연결된값 1씩 더하기
	void AddCounter();
	//연결된값 1로 초기화하기
	void CounterInit();
	void SetDirection(int y, int x);
	int GetDirectionX();
	int GetDirectionY();
	// 연결되어있는 값 얻기
	int GetCounter();
	void InitDirectionCounter();
	void AddDirectionCounter();
	// 승리할가능성있는지의 값 얻기
	int GetDirectionCounter();
};
#endif MAXCHECK