
// Connect6Dlg.h : ��� ����
//
#include"Core.h"
#include"stdafx.h"
#include"resource.h"
#pragma once




// CConnect6Dlg ��ȭ ����

class CConnect6Dlg : public CDialogEx
{


private:
	/*
	�ٵ� ĭ���� �迭�� ����
	2015.2.17
	2:38
	*/
	/* Board�� ���� ������ ��� InitBoard�� DrawStone�� for������ X,Y���� �����ؾ�
	�������� ��µȴ�.
	ex)Board���� �����Ͽ��ٰ� ������ �κп� ���� Ƣ�����
	2015.2.17
	4:11
	*/	
	CCore Board[19][19];
	int Player = 1; // ����������� ��� �ٲܰ�� ������ 1�� ���� 2015.2.17 12:31
	//���� 1�̿����� AI������ 0���� �ٲ� 2015.3.3 11:14
	int TurnCounter=0;
	

// �����Դϴ�.
public:
	CConnect6Dlg(CWnd* pParent = NULL);	// ǥ�� �������Դϴ�.

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_CONNECT6_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �����Դϴ�.

	
// �����Դϴ�.
protected:
	HICON m_hIcon;

	// ������ �޽��� �� �Լ�
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

public:
	/*
	����� �׷��ִ� �Լ�
	2015.2.17 2:28
	*/
	void DrawBack();
	
	/*
	�ٵ�ĭ �ʱ�ȭ
	2015.2.17 2:39
	*/
	void InitBoard();

	/*
	�ٵϾ� �׸���
	2015.2.17.3:00
	*/
	void DrawStone(void);
	
	/*
	�¸� üũ
	2015.2.17 10:01
	*/
	bool CheckWin(int x, int y, CCore &CPlayer);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	
	void AIsearch();
	void Capacity(CCore &Map, int way);

//	afx_msg void OnBnClickedOk();
};
