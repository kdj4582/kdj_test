
// Connect6Dlg.h : 헤더 파일
//
#include"Core.h"
#include"stdafx.h"
#include"resource.h"
#pragma once




// CConnect6Dlg 대화 상자

class CConnect6Dlg : public CDialogEx
{


private:
	/*
	바둑 칸마다 배열로 저장
	2015.2.17
	2:38
	*/
	/* Board의 값을 수정할 경우 InitBoard와 DrawStone의 for문내의 X,Y값도 변경해야
	무리없이 출력된다.
	ex)Board값만 수정하였다가 엉뚱한 부분에 흰돌이 튀어나왔음
	2015.2.17
	4:11
	*/	
	CCore Board[19][19];
	int Player = 1; // 디버깅을위해 잠깐 바꿀경우 원래는 1이 맞음 2015.2.17 12:31
	//원레 1이였지만 AI를위해 0으로 바꿈 2015.3.3 11:14
	int TurnCounter=0;
	

// 생성입니다.
public:
	CConnect6Dlg(CWnd* pParent = NULL);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
	enum { IDD = IDD_CONNECT6_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.

	
// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

public:
	/*
	배경을 그려주는 함수
	2015.2.17 2:28
	*/
	void DrawBack();
	
	/*
	바둑칸 초기화
	2015.2.17 2:39
	*/
	void InitBoard();

	/*
	바둑알 그리기
	2015.2.17.3:00
	*/
	void DrawStone(void);
	
	/*
	승리 체크
	2015.2.17 10:01
	*/
	bool CheckWin(int x, int y, CCore &CPlayer);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	
	void AIsearch();
	void Capacity(CCore &Map, int way);

//	afx_msg void OnBnClickedOk();
};
