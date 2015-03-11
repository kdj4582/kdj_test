
// Connect6Dlg.cpp : 구현 파일
//

/*
방향을 가리키는게 잘못된것인지 AI로직이 잘못된것인지 AI를적용하면
돌도 겹쳐서 생성하고 제대로 찾지도못하고 실패로 남긴채로 종료
다른학업에 집중하기위해
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
상,우상,우,우하 정보
승리판정함수에 있었지만 다른함수에서도
필요로하게되서 이쪽으로 옴김
2015.3.3
11:22
*/
const int NearCheck[4][2] = { { 1, 0 }, { 0, 1 }, { 1, 1 }, { 1, -1 } };

// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
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


// CConnect6Dlg 대화 상자



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


// CConnect6Dlg 메시지 처리기

BOOL CConnect6Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	
	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
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

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.

	/*
	바둑칸 초기화 호출
	2015.2.17
	2:42
	*/
	InitBoard();
	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
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

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CConnect6Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
	/* 바둑판의 배경을 그립니다.
	중앙에 흑색이 먼저 있는상태의 시작이 룰
	바둑알중앙에도 흑색하나그립니다.
	2015.2.17
	3:08
	*/
	DrawBack();
	DrawStone();
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
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
	바둑판 모양 수정
	3,4번째 변수가 기존에는 20*19였음
	2015.2.23
	20:37
	*/
	Edit.Rectangle(10, 10, 10 + 21 * 19, 10 + 21 * 19);

	CPen LinePen(PS_SOLID, 1, RGB(0, 0, 0));
	Edit.SelectObject(&LinePen);
	
	/*
	바둑판 외곽선 그리기
	2015.2.23
	22:13
	*/
	Edit.Rectangle(10, 10, 10 + 21 * 19, 10 + 21 * 19);

	/*
	밑 2for문내의 30숫자들은 기존에 10이였으나 디자인 변경하면서 바꿈
	2015.2.23
	20:43
	*/
	//y축 (세로줄 그리기)
	for (int X = 0; X < 19; X++)
	{
		Edit.MoveTo(30 + 20 * X, 30);
		Edit.LineTo(30 + 20 * X, 10 + 20 * 19);
		
	}

	//x축 (가로줄 그리기)
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
	//육목의 시작은 흑돌이 중앙에 놓고 백돌부터 시작한다.
	Board[9][9].SetPlayer(2);
}

void CConnect6Dlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	int MouseX = 0, MouseY = 0;
	/*
	player값은 턴카운터의 경우에 따라 바뀌기때문에 현재 클릭했을 당시의 플레이어 정보를 담아두기 위해
	checkPlayer를 생성
	2015.2.23
	20:17

	int checkPlayer = Player;
	*/
	/*
	칸안에 바둑알을 놓기위해 자연스러운터치를 위해x와 y에 -10씩 넣음
	2015.2.17
	4:00

	판의 위치를 x축 y축 20씩 더 옴기기 위해
	기존은 칸 안에 바둑알을 표시했으나
	선 위에 바둑알을 표시하기 위해 -10 삭제
	-20으로 수정
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
	클릭했을때 턴플레이어가 백돌이면
	아래의 내용을 모두 실행
	거의 함수내의모든내용
	*/
	if (Player == 1 || Board[MouseY][MouseX].GetEnemyPlayer() != 2){
		Board[MouseY][MouseX].SetPlayer(Player);
	/*
		여기에 메세지박스 출력 if문을 넣을 경우 돌이
		그려지지 않고 종료되는 부자연스러움때문에
		변수를 부득이하게 중앙에 선언
		2015.2.17
		13:30

		이부분을 수정해서 컴퓨터가 놓을턴과
		내가 놓을턴을 구별할 예정이다
		2015.2.27
		12:01

		AI를넣기위해 기존의 양방클릭방식은 주석처리
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
	if문을 함수포인터를 매개변수로 받아서
	함수로 만들어서 활용할 수 있지 않을까?
	2015/2/26
	23:58
	*/
	/*if (EndCheck)
	{
		CString Winner;
		if (Board[MouseY][MouseX].GetPlayer() == 2)
		{
			Winner = _T("흑돌이 이겼습니다");
		}
		else if (Board[MouseY][MouseX].GetPlayer() == 1)
		{
			Winner = _T("백돌이 이겼습니다");
		}
		MessageBox(Winner);
		CConnect6Dlg::OnOK();
	}*/
	TurnCounter++;
	if (TurnCounter == 2){
		Player = 2;
		TurnCounter = 0;
	}
	
	
	//흑돌 차례
	while (Player == 2){
		AIsearch();
		//bool EndCheck = CheckWin(MouseY, MouseX, Board[MouseY][MouseX]);
		DrawStone();
	/*	if (EndCheck)
		{
			CString Winner;
			if (Board[MouseY][MouseX].GetPlayer() == 2)
			{
				Winner = _T("흑돌이 이겼습니다");
			}
			else if (Board[MouseY][MouseX].GetPlayer() == 1)
			{
				Winner = _T("백돌이 이겼습니다");
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
			판의 위치를 x축 y축 20씩 더 옴기기 위해
			ellipse의 식의 22,38부분은 기존에 2,18에서 더한것임
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
	//클래스화하면서 필요없어짐 2015.2.25 19:07 int CheckPoint;
	// 중간에 끊어진경우에는 연산을 할 필요가 없어서 끊어져있는지 체크하기 위한 변수
	bool PlusLink, MinusLink; 

		for (int yDot = 0; yDot < 4; yDot++){
			//CheckPoint = 1;
			PlusLink = MinusLink = TRUE;

			/*
			방향마다 maxcounter재려고 방향 넣으려고 만듬
			2015.2.24
			10:38
			*/
			CPlayer.SetMaxDirector(yDot, NearCheck[yDot][0], NearCheck[yDot][1]);
			/*
			부를때마다 다시 새는거니깐 초기화해주는거
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
						//CheckPoint++; 클래스화하면서 아래로 대체 2015.2.25
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
						//CheckPoint++; 클래스화하면서 아래로 대체 2015.2.25
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
			기존에 CheckPoint>WinPoint였으나 클래스화하면서 수정
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
AISearch 생각대로 만들기 완성
2015.3.3
11:07
*/
//AI가 돌을 어디에 놓을지 검색하는 함수
void CConnect6Dlg::AIsearch(){

	int y, x;
	int direction;
	int Maxconnet=0;
	//마지막 그릴거 저장 코어
	CMaxCore LastCore;
	//queue값front 넣을 코어
	CMaxCore MatchCore;
	std::queue<CMaxCore> Choose;
	for (y = 0; y < 19; y++){
		for (x = 0; x < 19; x++){
			for (direction = 0; direction < 4; direction++){
				/*
				이길가능성 카운터재기 Direction과 map넣어서
				2015.3.2
				13:51
				*/
				//이길가능성 체크해서 6보다 큰애들 넣을건데,
				Capacity(Board[y][x], direction);
				//연결값 저장하는변수 하나만들어서 계속 비교해서 가장큰거 구하고
				if (Board[y][x].GetCounter(direction)>Maxconnet){
					Maxconnet = Board[y][x].GetCounter(direction);
				}
			}
		}
	}

	// 이길가능성counter 값이 가장 큰애들을 방향 한곳만 가리키는
	// 맵에서 maxcounter랑 같은 board의 counter(direction)을 빼서 CMaxCore만들어서
	// CMaxcore넣어서 완성 후
	// 이길가능성값끼리 비교해서 이길가능성 높은거를 그림
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
	// 그리고 마지막에 하나빼고
	while (!Choose.empty()){
		MatchCore = Choose.front();
		if (MatchCore.GetCounter() >= 6){
			if (LastCore.GetCounter() < MatchCore.GetCounter()){
				LastCore = MatchCore;
			}
		}
		Choose.pop();
	}
	// 그자리에 방향을 더한곳에 그리면되는거야!
	int temp = Board[LastCore.GetY() + LastCore.GetDirectionY()][LastCore.GetX() + LastCore.GetDirectionX()].GetPlayer();
	if (temp != LastCore.GetEnemyPlayer()){
	//if (Board[LastCore.GetY() + LastCore.GetDirectionY()][LastCore.GetX() + LastCore.GetDirectionX()].GetPlayer() != LastCore.GetEnemyPlayer()){
		Board[LastCore.GetY() + LastCore.GetDirectionY()][LastCore.GetX() + LastCore.GetDirectionX()].SetPlayer(2);
		Board[LastCore.GetY() + LastCore.GetDirectionY()][LastCore.GetX() + LastCore.GetDirectionX()].SetY(LastCore.GetY() + LastCore.GetDirectionY());
		Board[LastCore.GetY() + LastCore.GetDirectionY()][LastCore.GetX() + LastCore.GetDirectionX()].SetX(LastCore.GetX() + LastCore.GetDirectionX());
	}
}


//위 for문에서 int x의값을 way로 받아오면됨 2015.3.2 16:50
//이 지점에서 6칸을 완성시킬 수 있는지 여부를 검사


/* 
맵에 좌표에서 방향만큼 전진과 후진계산해서 적군인지 빈칸인지 확인해서 가능성을 체크
6이넘어가면 가능성이있고 없으면 없음
*/
/*
enemyplayer를 여기서 사용하려고했으나 생각해보니 필요없음
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
				더한 지점에서의 연결가능성은 세지 않음,
				함수밖에나가서 6개보다 작으면 확률없다고 판단
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

