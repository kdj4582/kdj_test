
// Connect6Dlg.cpp : ���� ����
//

/*
������ ����Ű�°� �߸��Ȱ����� AI������ �߸��Ȱ����� AI�������ϸ�
���� ���ļ� �����ϰ� ����� ã�������ϰ� ���з� ����ä�� ����
�ٸ��о��� �����ϱ�����
2015.3.4
12:39
*/

#include "stdafx.h"
#include "Connect6.h"
#include "Connect6Dlg.h"
#include "afxdialogex.h"
#include "MaxCore.h"
#include <queue>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

/*
��,���,��,���� ����
�¸������Լ��� �־����� �ٸ��Լ�������
�ʿ���ϰԵǼ� �������� �ȱ�
2015.3.3
11:22
*/
const int NearCheck[4][2] = { { 1, 0 }, { 0, 1 }, { 1, 1 }, { 1, -1 } };

// ���� ���α׷� ������ ���Ǵ� CAboutDlg ��ȭ �����Դϴ�.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

// �����Դϴ�.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CConnect6Dlg ��ȭ ����



CConnect6Dlg::CConnect6Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CConnect6Dlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CConnect6Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CConnect6Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_LBUTTONDOWN()
//	ON_BN_CLICKED(IDOK, &CConnect6Dlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CConnect6Dlg �޽��� ó����

BOOL CConnect6Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	
	// �ý��� �޴��� "����..." �޴� �׸��� �߰��մϴ�.

	// IDM_ABOUTBOX�� �ý��� ��� ������ �־�� �մϴ�.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// �� ��ȭ ������ �������� �����մϴ�.  ���� ���α׷��� �� â�� ��ȭ ���ڰ� �ƴ� ��쿡��
	//  �����ӿ�ũ�� �� �۾��� �ڵ����� �����մϴ�.
	SetIcon(m_hIcon, TRUE);			// ū �������� �����մϴ�.
	SetIcon(m_hIcon, FALSE);		// ���� �������� �����մϴ�.

	// TODO: ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.

	/*
	�ٵ�ĭ �ʱ�ȭ ȣ��
	2015.2.17
	2:42
	*/
	InitBoard();
	return TRUE;  // ��Ŀ���� ��Ʈ�ѿ� �������� ������ TRUE�� ��ȯ�մϴ�.
}

void CConnect6Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// ��ȭ ���ڿ� �ּ�ȭ ���߸� �߰��� ��� �������� �׸�����
//  �Ʒ� �ڵ尡 �ʿ��մϴ�.  ����/�� ���� ����ϴ� MFC ���� ���α׷��� ��쿡��
//  �����ӿ�ũ���� �� �۾��� �ڵ����� �����մϴ�.

void CConnect6Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // �׸��⸦ ���� ����̽� ���ؽ�Ʈ�Դϴ�.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Ŭ���̾�Ʈ �簢������ �������� ����� ����ϴ�.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// �������� �׸��ϴ�.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
	/* �ٵ����� ����� �׸��ϴ�.
	�߾ӿ� ����� ���� �ִ»����� ������ ��
	�ٵϾ��߾ӿ��� ����ϳ��׸��ϴ�.
	2015.2.17
	3:08
	*/
	DrawBack();
	DrawStone();
}

// ����ڰ� �ּ�ȭ�� â�� ���� ���ȿ� Ŀ���� ǥ�õǵ��� �ý��ۿ���
//  �� �Լ��� ȣ���մϴ�.
HCURSOR CConnect6Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CConnect6Dlg::DrawBack(){
	CClientDC Edit(this);

	CPen BrownPen(PS_SOLID, 0, RGB(206, 103, 0));

	Edit.SelectObject(&BrownPen);

	CBrush BrownBrush(RGB(206, 103, 0));
	Edit.SelectObject(&BrownBrush);
	
	/*
	�ٵ��� ��� ����
	3,4��° ������ �������� 20*19����
	2015.2.23
	20:37
	*/
	Edit.Rectangle(10, 10, 10 + 21 * 19, 10 + 21 * 19);

	CPen LinePen(PS_SOLID, 1, RGB(0, 0, 0));
	Edit.SelectObject(&LinePen);
	
	/*
	�ٵ��� �ܰ��� �׸���
	2015.2.23
	22:13
	*/
	Edit.Rectangle(10, 10, 10 + 21 * 19, 10 + 21 * 19);

	/*
	�� 2for������ 30���ڵ��� ������ 10�̿����� ������ �����ϸ鼭 �ٲ�
	2015.2.23
	20:43
	*/
	//y�� (������ �׸���)
	for (int X = 0; X < 19; X++)
	{
		Edit.MoveTo(30 + 20 * X, 30);
		Edit.LineTo(30 + 20 * X, 10 + 20 * 19);
		
	}

	//x�� (������ �׸���)
	for (int Y = 0; Y < 19; Y++){
		Edit.MoveTo(30 , 30 + 20 *Y);
		Edit.LineTo(10 + 20 * 19, 30 + 20 * Y);
	}

}

void CConnect6Dlg::InitBoard(){
	for (int Y = 0; Y < 19; Y++){
		for (int X = 0; X < 19; X++){
			Board[Y][X].SetPlayer(0);
			for (int dir = 0; dir < 4; dir++){
				Board[Y][X].SetMaxDirector(dir, NearCheck[dir][0], NearCheck[dir][1]);
			}
		}
	}
	//������ ������ �浹�� �߾ӿ� ���� �鵹���� �����Ѵ�.
	Board[9][9].SetPlayer(2);
}

void CConnect6Dlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	int MouseX = 0, MouseY = 0;
	/*
	player���� ��ī������ ��쿡 ���� �ٲ�⶧���� ���� Ŭ������ ����� �÷��̾� ������ ��Ƶα� ����
	checkPlayer�� ����
	2015.2.23
	20:17

	int checkPlayer = Player;
	*/
	/*
	ĭ�ȿ� �ٵϾ��� �������� �ڿ���������ġ�� ����x�� y�� -10�� ����
	2015.2.17
	4:00

	���� ��ġ�� x�� y�� 20�� �� �ȱ�� ����
	������ ĭ �ȿ� �ٵϾ��� ǥ��������
	�� ���� �ٵϾ��� ǥ���ϱ� ���� -10 ����
	-20���� ����
	2015.2.23
	22:07
	*/
	MouseX = (point.x - 20) / 20;
	MouseY = (point.y - 20) / 20;

	if (MouseX < 0 || MouseX >= 19 || MouseY < 0 || MouseY >= 19){
		return;
	}

	if (Board[MouseY][MouseX].GetPlayer() != 0){
		return;
	}
	Board[MouseY][MouseX].SetX(MouseX);
	Board[MouseY][MouseX].SetY(MouseY);
	/*
	Ŭ�������� ���÷��̾ �鵹�̸�
	�Ʒ��� ������ ��� ����
	���� �Լ����Ǹ�系��
	*/
	if (Player == 1 || Board[MouseY][MouseX].GetEnemyPlayer() != 2){
		Board[MouseY][MouseX].SetPlayer(Player);
	/*
		���⿡ �޼����ڽ� ��� if���� ���� ��� ����
		�׷����� �ʰ� ����Ǵ� ���ڿ������򶧹���
		������ �ε����ϰ� �߾ӿ� ����
		2015.2.17
		13:30

		�̺κ��� �����ؼ� ��ǻ�Ͱ� �����ϰ�
		���� �������� ������ �����̴�
		2015.2.27
		12:01

		AI���ֱ����� ������ ���Ŭ������� �ּ�ó��
		2015.3.3
		22:37

		if (Player == 1){
		Board[MouseY][MouseX].SetPlayer(Player);
		if (TurnCounter == 2){
		TurnCounter = 1;
		Player = 2;
		}
		else{
		TurnCounter++;
		}
		}
		else if (Player == 2){
		AIsearch();
		Board[MouseY][MouseX].SetPlayer(Player);
		if (TurnCounter == 2){
		TurnCounter = 1;
		Player = 1;
		}
		else{
		TurnCounter++;
		}
		}
		*/
	//bool EndCheck = CheckWin(MouseY, MouseX, Board[MouseY][MouseX]);
	DrawStone();

	/*
	if���� �Լ������͸� �Ű������� �޾Ƽ�
	�Լ��� ���� Ȱ���� �� ���� ������?
	2015/2/26
	23:58
	*/
	/*if (EndCheck)
	{
		CString Winner;
		if (Board[MouseY][MouseX].GetPlayer() == 2)
		{
			Winner = _T("�浹�� �̰���ϴ�");
		}
		else if (Board[MouseY][MouseX].GetPlayer() == 1)
		{
			Winner = _T("�鵹�� �̰���ϴ�");
		}
		MessageBox(Winner);
		CConnect6Dlg::OnOK();
	}*/
	TurnCounter++;
	if (TurnCounter == 2){
		Player = 2;
		TurnCounter = 0;
	}
	
	
	//�浹 ����
	while (Player == 2){
		AIsearch();
		//bool EndCheck = CheckWin(MouseY, MouseX, Board[MouseY][MouseX]);
		DrawStone();
	/*	if (EndCheck)
		{
			CString Winner;
			if (Board[MouseY][MouseX].GetPlayer() == 2)
			{
				Winner = _T("�浹�� �̰���ϴ�");
			}
			else if (Board[MouseY][MouseX].GetPlayer() == 1)
			{
				Winner = _T("�鵹�� �̰���ϴ�");
			}
			MessageBox(Winner);
			CConnect6Dlg::OnOK();
		}*/
		TurnCounter++;
		if (TurnCounter == 2){
			Player = 1;
			TurnCounter = 0;
			break;
		}
	}
}
	
	
	CDialogEx::OnLButtonDown(nFlags, point);
}

void CConnect6Dlg::DrawStone(){
	CClientDC Edit(this);
	int X, Y; 

	for (Y = 0; Y < 19; Y++)
	{
		for (X = 0; X < 19; X++)
		{
			/*
			���� ��ġ�� x�� y�� 20�� �� �ȱ�� ����
			ellipse�� ���� 22,38�κ��� ������ 2,18���� ���Ѱ���
			2015.2.23
			22:09
			*/
			if (Board[Y][X].GetPlayer() == 1)
			{
				Edit.SelectObject(GetStockObject(WHITE_BRUSH));
				Edit.Ellipse((22 + 20 * X), (22 + 20 * Y), (38 + 20 * X), (38 + 20 * Y));
			}
			else if (Board[Y][X].GetPlayer() == 2){
				Edit.SelectObject(GetStockObject(BLACK_BRUSH));
				Edit.Ellipse((22 + 20 * X), (22 + 20 * Y), (38 + 20 * X), (38 + 20 * Y));
			}
		}
	}
}

bool CConnect6Dlg::CheckWin(int y, int x, CCore &CPlayer){

	const int WinPoint = 5;
	int NearX, NearY;
	//Ŭ����ȭ�ϸ鼭 �ʿ������ 2015.2.25 19:07 int CheckPoint;
	// �߰��� ��������쿡�� ������ �� �ʿ䰡 ��� �������ִ��� üũ�ϱ� ���� ����
	bool PlusLink, MinusLink; 

		for (int yDot = 0; yDot < 4; yDot++){
			//CheckPoint = 1;
			PlusLink = MinusLink = TRUE;

			/*
			���⸶�� maxcounter����� ���� �������� ����
			2015.2.24
			10:38
			*/
			CPlayer.SetMaxDirector(yDot, NearCheck[yDot][0], NearCheck[yDot][1]);
			/*
			�θ������� �ٽ� ���°Ŵϱ� �ʱ�ȭ���ִ°�
				2015.2.24
				13:53
			*/
				CPlayer.CounterInit(yDot);

			for (int Point = 0; Point <= WinPoint; Point++){
				NearX = NearCheck[yDot][0] * (Point + 1);
				NearY = NearCheck[yDot][1] * (Point + 1);

				if (y + NearY < BoardMax && x + NearX < BoardMax && PlusLink)
				{
					if (Board[y + NearY][x + NearX].GetPlayer() == CPlayer.GetPlayer())
					{
						//CheckPoint++; Ŭ����ȭ�ϸ鼭 �Ʒ��� ��ü 2015.2.25
						CPlayer.AddCounter(yDot);
					}
					else
					{
						PlusLink = FALSE;
					}
				}
				else
				{
					PlusLink = FALSE;
				}
				
				if (y - NearY > BoardMin && x - NearX > BoardMin&&MinusLink)
				{
					if (Board[y - NearY][x - NearX].GetPlayer() == CPlayer.GetPlayer())
					{
						//CheckPoint++; Ŭ����ȭ�ϸ鼭 �Ʒ��� ��ü 2015.2.25
						CPlayer.AddCounter(yDot);
					}
					else
					{
						MinusLink = FALSE;
					}
				}
				else
				{
					MinusLink = FALSE;
				}
			}
			/*
			������ CheckPoint>WinPoint������ Ŭ����ȭ�ϸ鼭 ����
			2015.2.25
			19:07
			*/
			if (CPlayer.GetCounter(yDot) > WinPoint)
			{
				return true;
			}
	}
		return false;

}


/*
AISearch ������� ����� �ϼ�
2015.3.3
11:07
*/
//AI�� ���� ��� ������ �˻��ϴ� �Լ�
void CConnect6Dlg::AIsearch(){

	int y, x;
	int direction;
	int Maxconnet=0;
	//������ �׸��� ���� �ھ�
	CMaxCore LastCore;
	//queue��front ���� �ھ�
	CMaxCore MatchCore;
	std::queue<CMaxCore> Choose;
	for (y = 0; y < 19; y++){
		for (x = 0; x < 19; x++){
			for (direction = 0; direction < 4; direction++){
				/*
				�̱氡�ɼ� ī������� Direction�� map�־
				2015.3.2
				13:51
				*/
				//�̱氡�ɼ� üũ�ؼ� 6���� ū�ֵ� �����ǵ�,
				Capacity(Board[y][x], direction);
				//���ᰪ �����ϴº��� �ϳ����� ��� ���ؼ� ����ū�� ���ϰ�
				if (Board[y][x].GetCounter(direction)>Maxconnet){
					Maxconnet = Board[y][x].GetCounter(direction);
				}
			}
		}
	}

	// �̱氡�ɼ�counter ���� ���� ū�ֵ��� ���� �Ѱ��� ����Ű��
	// �ʿ��� maxcounter�� ���� board�� counter(direction)�� ���� CMaxCore����
	// CMaxcore�־ �ϼ� ��
	// �̱氡�ɼ������� ���ؼ� �̱氡�ɼ� �����Ÿ� �׸�
	for (y = 0; y < 19; y++){
		for (x = 0; x < 19; x++){
			for (direction = 0; direction < 4; direction++){
				if (Board[y][x].GetCounter(direction) == Maxconnet){
					CMaxCore Core(Board[y][x], direction);
					Choose.push(Core);
				}
			}
		}
	}
	// �׸��� �������� �ϳ�����
	while (!Choose.empty()){
		MatchCore = Choose.front();
		if (MatchCore.GetCounter() >= 6){
			if (LastCore.GetCounter() < MatchCore.GetCounter()){
				LastCore = MatchCore;
			}
		}
		Choose.pop();
	}
	// ���ڸ��� ������ ���Ѱ��� �׸���Ǵ°ž�!
	int temp = Board[LastCore.GetY() + LastCore.GetDirectionY()][LastCore.GetX() + LastCore.GetDirectionX()].GetPlayer();
	if (temp != LastCore.GetEnemyPlayer()){
	//if (Board[LastCore.GetY() + LastCore.GetDirectionY()][LastCore.GetX() + LastCore.GetDirectionX()].GetPlayer() != LastCore.GetEnemyPlayer()){
		Board[LastCore.GetY() + LastCore.GetDirectionY()][LastCore.GetX() + LastCore.GetDirectionX()].SetPlayer(2);
		Board[LastCore.GetY() + LastCore.GetDirectionY()][LastCore.GetX() + LastCore.GetDirectionX()].SetY(LastCore.GetY() + LastCore.GetDirectionY());
		Board[LastCore.GetY() + LastCore.GetDirectionY()][LastCore.GetX() + LastCore.GetDirectionX()].SetX(LastCore.GetX() + LastCore.GetDirectionX());
	}
}


//�� for������ int x�ǰ��� way�� �޾ƿ���� 2015.3.2 16:50
//�� �������� 6ĭ�� �ϼ���ų �� �ִ��� ���θ� �˻�


/* 
�ʿ� ��ǥ���� ���⸸ŭ ������ ��������ؼ� �������� ��ĭ���� Ȯ���ؼ� ���ɼ��� üũ
6�̳Ѿ�� ���ɼ����ְ� ������ ����
*/
/*
enemyplayer�� ���⼭ ����Ϸ��������� �����غ��� �ʿ����
2015.3.3
11:46
*/
void CConnect6Dlg::Capacity(CCore &Map, int way){
	Map.InitDirectionCounter(way);
	int Plusy, Plusx;
	int Minusy, Minusx;
	bool PlusLink=TRUE, MinusLink=TRUE;
	for (auto i = 0; i < 3; i++){
		Plusy = ((Map.GetY()) + Map.CoreDirectionY(way)*i);
		Plusx = ((Map.GetX()) + Map.CoreDirectionX(way)*i);
		Minusy = ((Map.GetY()) - Map.CoreDirectionY(way)*i);
		Minusx = ((Map.GetX()) - Map.CoreDirectionX(way)*i);
		
		if (Plusy < BoardMax && Plusx < BoardMax && PlusLink){
			if ((Board[Plusy][Plusx].GetPlayer() == Map.GetPlayer()) || (Board[Plusy][Plusx].GetPlayer() == 0)){
				Map.AddDirectionCounter(way);
			}
			else{
				PlusLink = false;
				/*
				���� ���������� ���ᰡ�ɼ��� ���� ����,
				�Լ��ۿ������� 6������ ������ Ȯ�����ٰ� �Ǵ�
				2015.3.2 16:52
				*/
			}
			if (Minusy > BoardMin && Minusx > BoardMin && MinusLink){
				if (Board[Minusy][Minusx].GetPlayer() == Map.GetPlayer() || (Board[Minusy][Minusx].GetPlayer() == 0)){
					Map.AddDirectionCounter(way);
				}
				else{
					MinusLink = false;
				}
			}
		}
	}
}

