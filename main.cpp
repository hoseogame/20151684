

#include <iostream>
#include <conio.h>
#include <windows.h>
#include <time.h>
//#include <fmod.h>
#include "Screen.h"

using namespace std;

class Game {
public:

};

class Draw :public Game {
public:
void RunningScreen();
void FailureScreen();
void ResultScreen();
void Render();
void Mangchi(int x, int y);
void MangchiReady(int x, int y);
void InitScreen();
void ReadyScreen();
void SuccessScreen();
};

class Supervise :public Draw {
public:

	void SoundInit();

	void Init();

	void Update();

	void Release();

	void Render();

	//int main(void);

};


class MANGCHI :public Game
{
public:
	int	nIsAttack;         // 망치 상태 
	clock_t	StartTime;     // 타격 상태가 시작된 시각
	clock_t	DelayTime;     // 타격 상태의 지연 시각
	int	nIndex;            // 좌표 배열에 접근하기 위한 인덱스
	int	nStayX, nStayY;    // 대기 상태일 때 좌표	
};
//namespace GAME_STATE

typedef	enum { INIT, READY, RUNNING, STOP, SUCCESS, FAILED, RESULT }
GAME_STATE;
//using namespace GAME_STATE;

namespace _DUDAGI_STATE
{
	enum { SETUP, UP, DOWN };
} using namespace _DUDAGI_STATE;



class DUDAGI :public Game
{
public:

	clock_t   StayTime;     // Note: 들어갔을 때 대기 시간
	clock_t	OutPutTime;     // Note: 나왔을 때 대기 시간
	clock_t	OldTime;    // Note: 이전 시각		
	clock_t nState;
};


typedef struct _XY
{
	int nX, nY;
} XY;

XY	g_Point[9] = { { 10, 15 },{ 20, 15 },{ 30, 15 },
{ 10, 10 },{ 20, 10 },{ 30, 10 },
{ 10, 5 },{ 20, 5 },{ 30, 5 }
};

typedef struct _STAGE_INFO
{
	int nCatchDudagi;
	clock_t LimitTime;
	clock_t UpLimitTime;
	clock_t DownLimitTime;
} STAGE_INFO;


STAGE_INFO g_StageInfo[3] = { { 2, 1000 * 10, 6000, 4000 },{ 5, 1000 * 10, 2000, 2000 },
{ 50, 1000 * 120, 1000, 1000 } };


GAME_STATE g_nGameState = INIT;
//clock_t		g_GameStartTime;
int         g_nIsSuccess = 0;

DUDAGI	g_Dudagi[9];
MANGCHI	g_Mangchi;

int			g_nStage = -1;
int			g_nGrade = 0; // 점수 
int			g_nStageCount = 1;
int			g_nDudagiCount = 0;
clock_t		g_GameStartTime, g_UpdateOldTime, g_RemainTime;
int			g_nTotalGrade = 0; // 총점

							   //FMOD_SYSTEM *g_System;
							   //FMOD_SOUND *g_Sound[7];
							   //FMOD_CHANNEL *g_Channel[7];
							   // 배경음 또는 반복음     // 효과음 
char *g_strSoundFile[7] = { "title.wav", "fail.wav", "ready.wav", "output.wav", "ubs.WAV", "WHOOSH1.WAV", "success.wav" };


void Draw::Mangchi(int x, int y)
{
	ScreenPrint(x - 4, y - 1, "☆┏━┓");
	ScreenPrint(x - 4, y, "⊂┃꽝┃〓〓⊂⊃");
	ScreenPrint(x - 4, y + 1, "☆┗━┛");
}

void Draw::MangchiReady(int x, int y)
{
	ScreenPrint(x - 4, y - 2, "    ∩");
	ScreenPrint(x - 4, y - 1, "  ┏━┓");
	ScreenPrint(x - 4, y, "  ┃  ┃");
	ScreenPrint(x - 4, y + 1, "  ┗━┛");
	ScreenPrint(x - 4, y + 2, "    ∥");
	ScreenPrint(x - 4, y + 3, "    ∥");
	ScreenPrint(x - 4, y + 4, "    ∩");
	ScreenPrint(x - 4, y + 5, "    ∪");
}

void Draw::InitScreen()
{
	ScreenPrint(0, 0, "┏━━━━━━━━━━━━━━━━━━━━┓");
	ScreenPrint(0, 1, "┃                                        ┃");
	ScreenPrint(0, 2, "┃                                        ┃");
	ScreenPrint(0, 3, "┃                                        ┃");
	ScreenPrint(0, 4, "┃                                        ┃");
	ScreenPrint(0, 5, "┃                                        ┃");
	ScreenPrint(0, 6, "┃                                        ┃");
	ScreenPrint(0, 7, "┃                                        ┃");
	ScreenPrint(0, 8, "┃             ////////                   ┃");
	ScreenPrint(0, 9, "┃             ┃＼ /┃ ＼│/             ┃");
	ScreenPrint(0, 10, "┃             ┃··┃┏┳┳┓           ┃");
	ScreenPrint(0, 11, "┃             ┗┓┏┛┗┓┏┛           ┃");
	ScreenPrint(0, 12, "┃                                        ┃");
	ScreenPrint(0, 13, "┃                                        ┃");
	ScreenPrint(0, 14, "┃                                        ┃");
	ScreenPrint(0, 15, "┃             두더지 잡기 게임           ┃");
	ScreenPrint(0, 16, "┃                                        ┃");
	ScreenPrint(0, 17, "┃          space 키를 눌러주세요         ┃");
	ScreenPrint(0, 18, "┃                                        ┃");
	ScreenPrint(0, 19, "┃                                        ┃");
	ScreenPrint(0, 20, "┃                                        ┃");
	ScreenPrint(0, 21, "┃                                        ┃");
	ScreenPrint(0, 22, "┃                                        ┃");
	ScreenPrint(0, 23, "┗━━━━━━━━━━━━━━━━━━━━┛");
}

void Draw::ReadyScreen()
{
	ScreenPrint(0, 0, "┏━━━━━━━━━━━━━━━━━━━━┓");
	ScreenPrint(0, 1, "┃■■■■■■■■■■■■■■■■■■■■┃");
	ScreenPrint(0, 2, "┃■■■■■■■■■■■■■■■■■■■■┃");
	ScreenPrint(0, 3, "┃■■■■■■■■■■■■■■■■■■■■┃");
	ScreenPrint(0, 4, "┃■■■■■■■■■■■■■■■■■■■■┃");
	ScreenPrint(0, 5, "┃■■■■■■■■■■■■■■■■■■■■┃");
	ScreenPrint(0, 6, "┃■■■■■■■■■■■■■■■■■■■■┃");
	ScreenPrint(0, 7, "┃■■■■■■■■■■■■■■■■■■■■┃");
	ScreenPrint(0, 8, "┃■■■■■■■■■■■■■■■■■■■■┃");
	ScreenPrint(0, 9, "┃■■■■■■■■■■■■■■■■■■■■┃");
	ScreenPrint(0, 10, "┃■■■■■                    ■■■■■┃");
	ScreenPrint(0, 11, "┃■■■■■        스테이지    ■■■■■┃");
	ScreenPrint(0, 12, "┃■■■■■                    ■■■■■┃");
	ScreenPrint(0, 13, "┃■■■■■■■■■■■■■■■■■■■■┃");
	ScreenPrint(0, 14, "┃■■■■■■■■■■■■■■■■■■■■┃");
	ScreenPrint(0, 15, "┃■■■■■■■■■■■■■■■■■■■■┃");
	ScreenPrint(0, 16, "┃■■■■■■■■■■■■■■■■■■■■┃");
	ScreenPrint(0, 17, "┃■■■■■■■■■■■■■■■■■■■■┃");
	ScreenPrint(0, 18, "┃■■■■■■■■■■■■■■■■■■■■┃");
	ScreenPrint(0, 19, "┃■■■■■■■■■■■■■■■■■■■■┃");
	ScreenPrint(0, 20, "┃■■■■■■■■■■■■■■■■■■■■┃");
	ScreenPrint(0, 21, "┃■■■■■■■■■■■■■■■■■■■■┃");
	ScreenPrint(0, 22, "┃■■■■■■■■■■■■■■■■■■■■┃");
	ScreenPrint(0, 23, "┗━━━━━━━━━━━━━━━━━━━━┛");
}

void Draw::SuccessScreen()
{
	ScreenPrint(0, 0, "┏━━━━━━━━━━━━━━━━━━━━┓");
	ScreenPrint(0, 1, "┃                                        ┃");
	ScreenPrint(0, 2, "┃                                        ┃");
	ScreenPrint(0, 3, "┃                                        ┃");
	ScreenPrint(0, 4, "┃             // / // ＼＼＼             ┃");
	ScreenPrint(0, 5, "┃             │/＼    /＼│♬           ┃");
	ScreenPrint(0, 6, "┃             │≡  ▽  ≡│○           ┃");
	ScreenPrint(0, 7, "┃              ＼_________///            ┃");
	ScreenPrint(0, 8, "┃                                        ┃");
	ScreenPrint(0, 9, "┃                                        ┃");
	ScreenPrint(0, 10, "┃                                        ┃");
	ScreenPrint(0, 11, "┃                       스테이지         ┃");
	ScreenPrint(0, 12, "┃                                        ┃");
	ScreenPrint(0, 13, "┃                   미션 성공 !!!!       ┃");
	ScreenPrint(0, 14, "┃                                        ┃");
	ScreenPrint(0, 15, "┃                                        ┃");
	ScreenPrint(0, 16, "┃                                        ┃");
	ScreenPrint(0, 17, "┃     잡은 두더지 :                      ┃");
	ScreenPrint(0, 18, "┃                                        ┃");
	ScreenPrint(0, 19, "┃     총점 :                             ┃");
	ScreenPrint(0, 20, "┃                                        ┃");
	ScreenPrint(0, 21, "┃                                        ┃");
	ScreenPrint(0, 22, "┃                                        ┃");
	ScreenPrint(0, 23, "┗━━━━━━━━━━━━━━━━━━━━┛");
}

void Draw::RunningScreen()
{
	ScreenPrint(0, 0, "┏━━━━━━━━━━━━━━━━━━━━┓");
	ScreenPrint(0, 1, "┃                                        ┃");
	ScreenPrint(0, 2, "┃                                        ┃");
	ScreenPrint(0, 3, "┃                                        ┃");
	ScreenPrint(0, 4, "┃                                        ┃");
	ScreenPrint(0, 5, "┃                                        ┃");
	ScreenPrint(0, 6, "┃                                        ┃");
	ScreenPrint(0, 7, "┃                                        ┃");
	ScreenPrint(0, 8, "┃                                        ┃");
	ScreenPrint(0, 9, "┃                                        ┃");
	ScreenPrint(0, 10, "┃                                        ┃");
	ScreenPrint(0, 11, "┃                                        ┃");
	ScreenPrint(0, 12, "┃                                        ┃");
	ScreenPrint(0, 13, "┃                                        ┃");
	ScreenPrint(0, 14, "┃                                        ┃");
	ScreenPrint(0, 15, "┃                                        ┃");
	ScreenPrint(0, 16, "┃                                        ┃");
	ScreenPrint(0, 17, "┃                                        ┃");
	ScreenPrint(0, 18, "┃                                        ┃");
	ScreenPrint(0, 19, "┃                            ○    ●    ┃");
	ScreenPrint(0, 20, "┃                          ┏■┛┏□┛  ┃");
	ScreenPrint(0, 21, "┃                            ┛┓  ┛┓  ┃");
	ScreenPrint(0, 22, "┃                                        ┃");
	ScreenPrint(0, 23, "┗━━━━━━━━━━━━━━━━━━━━┛");
}

void Draw::FailureScreen()
{
	ScreenPrint(0, 0, "┏━━━━━━━━━━━━━━━━━━━━┓");
	ScreenPrint(0, 1, "┃                                        ┃");
	ScreenPrint(0, 2, "┃                                        ┃");
	ScreenPrint(0, 3, "┃                                        ┃");
	ScreenPrint(0, 4, "┃                                        ┃");
	ScreenPrint(0, 5, "┃                                        ┃");
	ScreenPrint(0, 6, "┃             ┎-━━-┒                 ┃");
	ScreenPrint(0, 7, "┃             d ご,.ご b                 ┃");
	ScreenPrint(0, 8, "┃             ┃┭─┮┃                 ┃");
	ScreenPrint(0, 9, "┃             ┖┦│┞┚                 ┃");
	ScreenPrint(0, 10, "┃               ┕┷┙                   ┃");
	ScreenPrint(0, 11, "┃                    스테이지            ┃");
	ScreenPrint(0, 12, "┃                                        ┃");
	ScreenPrint(0, 13, "┃            미션 실패 !!!!              ┃");
	ScreenPrint(0, 14, "┃                                        ┃");
	ScreenPrint(0, 15, "┃                                        ┃");
	ScreenPrint(0, 16, "┃                                        ┃");
	ScreenPrint(0, 17, "┃      다시 하시겠습니까? ( y/n )        ┃");
	ScreenPrint(0, 18, "┃                                        ┃");
	ScreenPrint(0, 19, "┃                                        ┃");
	ScreenPrint(0, 20, "┃                                        ┃");
	ScreenPrint(0, 21, "┃                                        ┃");
	ScreenPrint(0, 22, "┃                                        ┃");
	ScreenPrint(0, 23, "┗━━━━━━━━━━━━━━━━━━━━┛");
}

// Note: 실패 했을 경우에 출력되면서 다시 할것인지를 묻는 화면이다.

void Draw::ResultScreen()
{
	ScreenPrint(0, 0, "┏━━━━━━━━━━━━━━━━━━━━┓");
	ScreenPrint(0, 1, "┃                                        ┃");
	ScreenPrint(0, 2, "┃                                        ┃");
	ScreenPrint(0, 3, "┃                                        ┃");
	ScreenPrint(0, 4, "┃                                        ┃");
	ScreenPrint(0, 5, "┃                                        ┃");
	ScreenPrint(0, 6, "┃                                        ┃");
	ScreenPrint(0, 7, "┃  (((    두더지 잡기 게임 Score  ))))   ┃");
	ScreenPrint(0, 8, "┃                                        ┃");
	ScreenPrint(0, 9, "┃                                        ┃");
	ScreenPrint(0, 10, "┃                                        ┃");
	ScreenPrint(0, 11, "┃           총 점수  :                   ┃");
	ScreenPrint(0, 12, "┃                                        ┃");
	ScreenPrint(0, 13, "┃                                        ┃");
	ScreenPrint(0, 14, "┃                                        ┃");
	ScreenPrint(0, 15, "┃                                        ┃");
	ScreenPrint(0, 16, "┃                                        ┃");
	ScreenPrint(0, 17, "┃                                        ┃");
	ScreenPrint(0, 18, "┃                                        ┃");
	ScreenPrint(0, 19, "┃                                        ┃");
	ScreenPrint(0, 20, "┃                                        ┃");
	ScreenPrint(0, 21, "┃                                        ┃");
	ScreenPrint(0, 22, "┃                                        ┃");
	ScreenPrint(0, 23, "┗━━━━━━━━━━━━━━━━━━━━┛");
}

void Supervise::SoundInit()
{
	int i;

	/*FMOD_System_Create(&g_System);
	FMOD_System_Init( g_System, 32, FMOD_INIT_NORMAL, NULL);

	for( i = 0 ; i < 2 ; i++ )
	FMOD_System_CreateSound(g_System, g_strSoundFile[i], FMOD_LOOP_NORMAL , 0, &g_Sound[i]);

	for( i = 2 ; i < 7 ; i++ )
	FMOD_System_CreateSound(g_System, g_strSoundFile[i], FMOD_HARDWARE , 0, &g_Sound[i]);*/
}

void Supervise::Init()
{
	int i;

	if (g_nStage == -1) // 1번만 초기화가 되는 부분에 대한 처리 사항
	{
		SoundInit();
		g_nStage = 0;
		//FMOD_System_PlaySound( g_System, FMOD_CHANNEL_FREE, g_Sound[0], 0, &g_Channel[0] );
	}

	g_nDudagiCount = 0; // 잡은 두더지 개수	
	g_nGrade = 0;

	// Note: 망치 셋업
	g_Mangchi.nIsAttack = 0;
	g_Mangchi.nIndex = 0;
	g_Mangchi.nStayX = 38;
	g_Mangchi.nStayY = 10;
	g_Mangchi.StartTime = g_GameStartTime;
	g_Mangchi.DelayTime = 300;

	for (i = 0; i < 9; i++)
	{
		g_Dudagi[i].StayTime = rand() % g_StageInfo[g_nStage].DownLimitTime + 10; // Note: 최소 10은 된다.
		g_Dudagi[i].OldTime = clock();
		g_Dudagi[i].nState = SETUP;
		g_Dudagi[i].OutPutTime = rand() % g_StageInfo[g_nStage].UpLimitTime + 10; //최소 10은 된다.
	}
}

void Supervise::Update()
{
	int i;
	clock_t CurTime = clock();

	switch (g_nGameState)
	{
	case READY:
		if (CurTime - g_UpdateOldTime > 2000)  // 2초
		{
			g_nGameState = RUNNING;
			g_GameStartTime = CurTime;
		}
		break;
	case RUNNING:
		if ((CurTime - g_GameStartTime) > g_StageInfo[g_nStage].LimitTime)
		{
			g_nGameState = STOP;
			return;
		}
		else {
			// 두더지 업데이트	
			for (i = 0; i < 9; i++)
			{
				switch (g_Dudagi[i].nState)
				{
				case SETUP:
					g_Dudagi[i].OldTime = CurTime;
					g_Dudagi[i].OutPutTime = rand() % (int)g_StageInfo[g_nStage].UpLimitTime + 10;
					g_Dudagi[i].StayTime = rand() % (int)g_StageInfo[g_nStage].DownLimitTime + 10;
					g_Dudagi[i].nState = UP;
					//FMOD_System_PlaySound( g_System, FMOD_CHANNEL_FREE, g_Sound[3], 0, &g_Channel[3] ); // 나올때만 출력
					break;
				case UP:
					if (CurTime - g_Dudagi[i].OldTime > g_Dudagi[i].OutPutTime)
					{
						g_Dudagi[i].OldTime = CurTime;
						g_Dudagi[i].nState = DOWN;
					}
					break;
				case DOWN:
					if (CurTime - g_Dudagi[i].OldTime > g_Dudagi[i].StayTime)
						g_Dudagi[i].nState = SETUP;
					break;
				}
			}

			// 망치 업데이트 
			if (g_Mangchi.nIsAttack)
			{
				// 충돌 테스트 망치는 오직 하나의 두더지만 잡을 수 있기에 하나만 잡았으면 충돌 체크를 빠져 나온다.
				for (i = 0; i < 9; i++)
				{
					if (g_Dudagi[i].nState == UP && i == g_Mangchi.nIndex)
					{
						g_nGrade += 10;
						g_nDudagiCount++;
						g_Dudagi[i].nState = DOWN; // 죽었으면 다운 상태로 바로 전환을 하도록 한다.															
												   //FMOD_System_PlaySound( g_System, FMOD_CHANNEL_FREE, g_Sound[4], 0, &g_Channel[4] );								
						break;
					}
				}

				// Note: 망치의 상태를 변경해주는 부분 망치로 쳤을 때에 일정한 시간 동안 머물도록 하기 위한 부분
				if (CurTime - g_Mangchi.StartTime > g_Mangchi.DelayTime)
				{
					g_Mangchi.nIsAttack = 0;
				}
			}

			g_RemainTime = (g_StageInfo[g_nStage].LimitTime - (CurTime - g_GameStartTime)) / 1000; // 게임 진행 남은 시간
		}
		break;
	case STOP:
		// 성공이냐 실패를 판단해주어서 출력을 해주는 부분이 와야 한다.
		if (g_nDudagiCount >= g_StageInfo[g_nStage].nCatchDudagi)
		{
			g_UpdateOldTime = CurTime;
			g_nGameState = SUCCESS;
			g_nTotalGrade += g_nGrade;
			//FMOD_System_PlaySound( g_System, FMOD_CHANNEL_FREE, g_Sound[6], 0, &g_Channel[6] ); // 미션 성공 사운드
		}
		else {
			g_nGameState = FAILED;
			//FMOD_System_PlaySound( g_System, FMOD_CHANNEL_FREE, g_Sound[1], 0, &g_Channel[1] ); // 미션 실패 사운드
		}
		break;
	case SUCCESS:
		if (CurTime - g_UpdateOldTime > 3000)
		{
			g_UpdateOldTime = CurTime;
			g_nGrade = 0;
			++g_nStage;
			Init();
			g_nGameState = READY;
			//FMOD_Channel_Stop( g_Channel[6] );  // 미션 성공 사운드 출력 중지					
			//FMOD_System_PlaySound( g_System, FMOD_CHANNEL_FREE, g_Sound[2], 0, &g_Channel[2]); // READY 사운드 출력
		}
		break;
	}
}

void Draw::Render()
{
	int i;
	char string[100];

	ScreenClear();

	switch (g_nGameState)
	{
	case INIT:
		if (g_nStage == 0)
			InitScreen();
		break;

	case READY:
		ReadyScreen();
		sprintf(string, "%d", g_nStage + 1);
		ScreenPrint(16, 11, string);
		break;

	case RUNNING:
		RunningScreen();

		sprintf(string, "목표 두더지 : %d  잡은 두더지 : %d", g_StageInfo[g_nStage].nCatchDudagi, g_nDudagiCount);
		ScreenPrint(2, 1, string);
		sprintf(string, "스테이지 : %d 점수 : %d 남은 시간 : %d ", g_nStage + 1, g_nGrade, g_RemainTime);
		ScreenPrint(2, 2, string);

		for (i = 0; i < 9; i++)
		{
			if (g_Dudagi[i].nState == UP)
				ScreenPrint(g_Point[i].nX, g_Point[i].nY, "●");

			ScreenPrint(g_Point[i].nX, g_Point[i].nY + 1, "♨");
		}

		if (g_Mangchi.nIsAttack)
			Mangchi(g_Point[g_Mangchi.nIndex].nX, g_Point[g_Mangchi.nIndex].nY);
		else
			MangchiReady(g_Mangchi.nStayX, g_Mangchi.nStayY);
		break;

	case SUCCESS:
		SuccessScreen();
		sprintf(string, "%d", g_nStage + 1);
		ScreenPrint(20, 11, string);
		sprintf(string, "%d", g_nDudagiCount);
		ScreenPrint(21, 17, string);
		sprintf(string, "%d", g_nTotalGrade);
		ScreenPrint(14, 19, string);
		break;

	case FAILED:
		FailureScreen();
		sprintf(string, "%d", g_nStage + 1);
		ScreenPrint(16, 11, string);
		break;

	case RESULT:
		ResultScreen();
		sprintf(string, "%d", g_nTotalGrade);
		ScreenPrint(25, 11, string);
		break;
	}
	ScreenFlipping();
}

void Supervise::Release()
{
	/*	int i;
	for( i = 0 ; i < 7 ; i++ )
	FMOD_Sound_Release( g_Sound[i] );

	FMOD_System_Close( g_System );
	FMOD_System_Release( g_System );*/
}

void Supervise::Render()
{
	int i;
	char string[100];

	ScreenClear();

	switch ( g_nGameState )
	{
	case INIT:
		if ( g_nStage == 0 )
			InitScreen();
		break;

	case READY:
		ReadyScreen();
		sprintf( string, "%d", g_nStage + 1 );
		ScreenPrint( 16, 11, string );
		break;

	case RUNNING:
		RunningScreen();

		sprintf( string, "목표 두더지 : %d  잡은 두더지 : %d", g_StageInfo[g_nStage].nCatchDudagi, g_nDudagiCount );
		ScreenPrint( 2, 1, string );
		sprintf( string, "스테이지 : %d 점수 : %d 남은 시간 : %d ", g_nStage + 1, g_nGrade, g_RemainTime );
		ScreenPrint( 2, 2, string );

		for ( i = 0; i < 9; i++ )
		{
			if ( g_Dudagi[i].nState == UP )
				ScreenPrint( g_Point[i].nX, g_Point[i].nY, "●" );

			ScreenPrint( g_Point[i].nX, g_Point[i].nY + 1, "♨" );
		}

		if ( g_Mangchi.nIsAttack )
			Mangchi( g_Point[g_Mangchi.nIndex].nX, g_Point[g_Mangchi.nIndex].nY );
		else
			MangchiReady( g_Mangchi.nStayX, g_Mangchi.nStayY );
		break;

	case SUCCESS:
		SuccessScreen();
		sprintf( string, "%d", g_nStage + 1 );
		ScreenPrint( 20, 11, string );
		sprintf( string, "%d", g_nDudagiCount );
		ScreenPrint( 21, 17, string );
		sprintf( string, "%d", g_nTotalGrade );
		ScreenPrint( 14, 19, string );
		break;

	case FAILED:
		FailureScreen();
		sprintf( string, "%d", g_nStage + 1 );
		ScreenPrint( 16, 11, string );
		break;

	case RESULT:
		ResultScreen();
		sprintf( string, "%d", g_nTotalGrade );
		ScreenPrint( 25, 11, string );
		break;
	}
	ScreenFlipping();
}


///////////////////////블럭실행

typedef enum { INIT2, READY2, RUNNING2, SUCCESS2, FAILED2, STOP2, RESULT2 } GAME_STATE2;
typedef enum _DIRECT2 { TOP, LEFT_TOP, LEFT_DOWN, DOWN2, RIGHT_DOWN, RIGHT_TOP } DIRECT2;

typedef struct _STAGE_INFO2
{
	int      nBlockCount; // 벽돌 개수
	clock_t  LimitTime;  // 제한 시간
} STAGE_INFO2;

typedef struct _BALL
{
	int		 nReady;     // 1 이면 준비 상태, 0이면 이동 상태
	int		 nHP;        // 생명
	int		 nX, nY;     // 좌표
	int   nDirect;    // 이동 방향
	clock_t  MoveTime;   // 이동 시간 간격
	clock_t  OldTime;	 // 이전 이동 시각
} BALL;

GAME_STATE2	g_nGameState2 = INIT2;


class Game2 {
public:
};

class B_Draw : public Game2 {
public:

	void InitScreen();

	void ReadyScreen();

	void SuccessScreen();

	void FailureScreen();

	void RunningScreen();

	void ResultScreen();

	void Render();

};

class Block : public Game2 {
public:

	void SoundInit();

	void SoundRelease();

	int Search(int nEnd, int nX, int nY);

	void SetBlock(int nBlockCount);

	int Collision(int nX, int nY);

	void Init();

	void Update();

	void Release();

};
typedef struct _BLOCK
{
	int  nLife;
	int  nX, nY;
} BLOCK;

typedef struct _BAR
{
	int nX[3];
	int nY;
	clock_t OldTime;
	clock_t MoveTime;
} BAR;

BAR  g_sBar;

BALL g_sBall;
int g_StateTable[4][6] = { // 벽과 충돌하게 되면 방향 상태
	{ 3,  2, -1, -1, -1,  4 },
	{ -1,  5,  4, -1, -1, -1 },
	{ -1, -1,  1,  0,  5, -1 },
	{ -1, -1, -1, -1,  2,  1 }
};

int g_BlockState[6] = { 3, 2, 1, 0, 5, 4 };
BLOCK g_sBlock[200];
//FMOD_SYSTEM     *g_System;
//FMOD_SOUND		*g_Sound[8];
//FMOD_CHANNEL	*g_Channel[8];


int         g_nIsSuccess2 = 0;
int			g_nStage2 = -1;
int			g_nGrade2 = 0; // 점수 
int			g_nStageCount2 = 1;
clock_t		g_GameStartTime2, g_UpdateOldTime2, g_RemainTime2;
int			g_nTotalGrade2 = 0; // 총점
STAGE_INFO2  g_StageInfo2[3] = { { 30, 60 * 1000 },{ 50, 2 * 60 * 1000 },{ 100, 3 * 60 * 1000 } };

int			g_nBlockCount = 0;   // 맞춘 벽돌


void B_Draw::InitScreen() // 게임 소개 화면
{
	ScreenPrint(0, 0, "┏━━━━━━━━━━━━━━━━━━━━┓");
	ScreenPrint(0, 1, "┃                                        ┃");
	ScreenPrint(0, 2, "┃    ■■■■■■■■■■■■■■■■    ┃");
	ScreenPrint(0, 3, "┃      ■■■■■■■■■■■■■■      ┃");
	ScreenPrint(0, 4, "┃        ■■■■■■■■■■■■        ┃");
	ScreenPrint(0, 5, "┃          ■■■■■■■■■■          ┃");
	ScreenPrint(0, 6, "┃          ┏━━━━━━━━┓          ┃");
	ScreenPrint(0, 7, "┃          ┃★ 벽돌 깨기  ★┃          ┃");
	ScreenPrint(0, 8, "┃          ┗━━━━━┳━━┛          ┃");
	ScreenPrint(0, 9, "┃              /)/)    ┃ ☆             ┃");
	ScreenPrint(0, 10, "┃           ★(*'')/                     ┃");
	ScreenPrint(0, 11, "┃          ■■■■■■■■■■          ┃");
	ScreenPrint(0, 12, "┃        ■■■■■■■■■■■■        ┃");
	ScreenPrint(0, 13, "┃      ■■■■■■■■■■■■■■      ┃");
	ScreenPrint(0, 14, "┃    ■■■■■■■■■■■■■■■■    ┃");
	ScreenPrint(0, 15, "┃                                        ┃");
	ScreenPrint(0, 16, "┃                                        ┃");
	ScreenPrint(0, 17, "┃    ★ 스페이스키를 눌러주세요!! ★     ┃");
	ScreenPrint(0, 18, "┃                                        ┃");
	ScreenPrint(0, 19, "┃     J:좌  L:우 K: 공발사 I: 공잡기     ┃");
	ScreenPrint(0, 20, "┃     ( 공 발사 방향 )                   ┃");
	ScreenPrint(0, 21, "┃       1: 왼족 2: 위쪽 3: 오른쪽        ┃");
	ScreenPrint(0, 22, "┃                                        ┃");
	ScreenPrint(0, 23, "┗━━━━━━━━━━━━━━━━━━━━┛");
}

void B_Draw::ReadyScreen()
{
	ScreenPrint(0, 0, "┏━━━━━━━━━━━━━━━━━━━━┓");
	ScreenPrint(0, 1, "┃                                        ┃");
	ScreenPrint(0, 2, "┃                                        ┃");
	ScreenPrint(0, 3, "┃                                        ┃");
	ScreenPrint(0, 4, "┃                                        ┃");
	ScreenPrint(0, 5, "┃                                        ┃");
	ScreenPrint(0, 6, "┃                                        ┃");
	ScreenPrint(0, 7, "┃              S t a g e                 ┃");
	ScreenPrint(0, 8, "┃                            ●          ┃");
	ScreenPrint(0, 9, "┃                      ☜〓━┃          ┃");
	ScreenPrint(0, 10, "┃                        ☜〓┛          ┃");
	ScreenPrint(0, 11, "┃                          ┏┻┓        ┃");
	ScreenPrint(0, 12, "┃                                        ┃");
	ScreenPrint(0, 13, "┃                                        ┃");
	ScreenPrint(0, 14, "┃                                        ┃");
	ScreenPrint(0, 15, "┃                                        ┃");
	ScreenPrint(0, 16, "┃                                        ┃");
	ScreenPrint(0, 17, "┃                                        ┃");
	ScreenPrint(0, 18, "┃                                        ┃");
	ScreenPrint(0, 19, "┃                                        ┃");
	ScreenPrint(0, 20, "┃                                        ┃");
	ScreenPrint(0, 21, "┃                                        ┃");
	ScreenPrint(0, 22, "┃                                        ┃");
	ScreenPrint(0, 23, "┗━━━━━━━━━━━━━━━━━━━━┛");
}

void B_Draw::SuccessScreen()
{
	ScreenPrint(0, 0, "┏━━━━━━━━━━━━━━━━━━━━┓");
	ScreenPrint(0, 1, "┃      *.                                ┃");
	ScreenPrint(0, 2, "┃              .*            .*          ┃");
	ScreenPrint(0, 3, "┃     *.                        .*       ┃");
	ScreenPrint(0, 4, "┃       *.             .*                ┃");
	ScreenPrint(0, 5, "┃           *.                           ┃");
	ScreenPrint(0, 6, "┃            *.             .*           ┃");
	ScreenPrint(0, 7, "┃     *.      *.┏┓┏┓.*대    .*       ┃");
	ScreenPrint(0, 8, "┃             ┏┻┫┣┻┓단             ┃");
	ScreenPrint(0, 9, "┃     *.      ┃━┫┣━┃해      .*     ┃");
	ScreenPrint(0, 10, "┃             ┃━┫┣━┃요~            ┃");
	ScreenPrint(0, 11, "┃        *.   ┗━┛┗━┛               ┃");
	ScreenPrint(0, 12, "┃                                        ┃");
	ScreenPrint(0, 13, "┃                          .*            ┃");
	ScreenPrint(0, 14, "┃  *.           You Win!!          *.    ┃");
	ScreenPrint(0, 15, "┃                                        ┃");
	ScreenPrint(0, 16, "┃                                        ┃");
	ScreenPrint(0, 17, "┃                       *.               ┃");
	ScreenPrint(0, 18, "┃    *.         *.                       ┃");
	ScreenPrint(0, 19, "┃                                 *.     ┃");
	ScreenPrint(0, 20, "┃                      *.                ┃");
	ScreenPrint(0, 21, "┃  *.                             *.     ┃");
	ScreenPrint(0, 22, "┃                                        ┃");
	ScreenPrint(0, 23, "┗━━━━━━━━━━━━━━━━━━━━┛");
}

void B_Draw::FailureScreen()
{
	ScreenPrint(0, 0, "┏━━━━━━━━━━━━━━━━━━━━┓");
	ScreenPrint(0, 1, "┃  ■■■■■■■■■■■■■■■■■■  ┃");
	ScreenPrint(0, 2, "┃  ■■■■■■■■■■■■■■■■■■  ┃");
	ScreenPrint(0, 3, "┃                                        ┃");
	ScreenPrint(0, 4, "┃                                        ┃");
	ScreenPrint(0, 5, "┃                                        ┃");
	ScreenPrint(0, 6, "┃                                        ┃");
	ScreenPrint(0, 7, "┃             *┭┮  ┭┮*               ┃");
	ScreenPrint(0, 8, "┃          *.  ㅣㅣ▽ㅣㅣ   .*           ┃");
	ScreenPrint(0, 9, "┃   ┏ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ┓     ┃");
	ScreenPrint(0, 10, "┃   ┃다음 번 기회를 이용해 주세요┃     ┃");
	ScreenPrint(0, 11, "┃   ┗ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ┛     ┃");
	ScreenPrint(0, 12, "┃                                        ┃");
	ScreenPrint(0, 13, "┃                                        ┃");
	ScreenPrint(0, 14, "┃    (*⌒⌒*)                            ┃");
	ScreenPrint(0, 15, "┃   ┏O━━━O━━━━━━━━━━┓     ┃");
	ScreenPrint(0, 16, "┃   ┃계속하시겠습니까? <y/n>     ┃     ┃");
	ScreenPrint(0, 17, "┃   ┗━━━━━━━━━━━━━━┛     ┃");
	ScreenPrint(0, 18, "┃                                        ┃");
	ScreenPrint(0, 19, "┃                                        ┃");
	ScreenPrint(0, 20, "┃                                        ┃");
	ScreenPrint(0, 21, "┃  ■■■■■■■■■■■■■■■■■■  ┃");
	ScreenPrint(0, 22, "┃  ■■■■■■■■■■■■■■■■■■  ┃");
	ScreenPrint(0, 23, "┗━━━━━━━━━━━━━━━━━━━━┛");
}

void B_Draw::RunningScreen()
{
	ScreenPrint(0, 0, "┏━━━━━━━━━━━━━━━━━━━━┓");
	ScreenPrint(0, 1, "┃                                        ┃");
	ScreenPrint(0, 2, "┃                                        ┃");
	ScreenPrint(0, 3, "┃                                        ┃");
	ScreenPrint(0, 4, "┃                                        ┃");
	ScreenPrint(0, 5, "┃                                        ┃");
	ScreenPrint(0, 6, "┃                                        ┃");
	ScreenPrint(0, 7, "┃                                        ┃");
	ScreenPrint(0, 8, "┃                                        ┃");
	ScreenPrint(0, 9, "┃                                        ┃");
	ScreenPrint(0, 10, "┃                                        ┃");
	ScreenPrint(0, 11, "┃                                        ┃");
	ScreenPrint(0, 12, "┃                                        ┃");
	ScreenPrint(0, 13, "┃                                        ┃");
	ScreenPrint(0, 14, "┃                                        ┃");
	ScreenPrint(0, 15, "┃                                        ┃");
	ScreenPrint(0, 16, "┃                                        ┃");
	ScreenPrint(0, 17, "┃                                        ┃");
	ScreenPrint(0, 18, "┃                                        ┃");
	ScreenPrint(0, 19, "┃                                        ┃");
	ScreenPrint(0, 20, "┃                                        ┃");
	ScreenPrint(0, 21, "┃                                        ┃");
	ScreenPrint(0, 22, "┃                                        ┃");
	ScreenPrint(0, 23, "┗━━━━━━━━━━━━━━━━━━━━┛");
}

void B_Draw::ResultScreen()
{
	ScreenPrint(0, 0, "┏━━━━━━━━━━━━━━━━━━━━┓");
	ScreenPrint(0, 1, "┃                                        ┃");
	ScreenPrint(0, 2, "┃                                        ┃");
	ScreenPrint(0, 3, "┃                                        ┃");
	ScreenPrint(0, 4, "┃                                        ┃");
	ScreenPrint(0, 5, "┃                                        ┃");
	ScreenPrint(0, 6, "┃                                        ┃");
	ScreenPrint(0, 7, "┃   (((    벽돌 깨기  게임 Score  ))))   ┃");
	ScreenPrint(0, 8, "┃                                        ┃");
	ScreenPrint(0, 9, "┃                                        ┃");
	ScreenPrint(0, 10, "┃                                        ┃");
	ScreenPrint(0, 11, "┃           총 점수  :                   ┃");
	ScreenPrint(0, 12, "┃                                        ┃");
	ScreenPrint(0, 13, "┃                                        ┃");
	ScreenPrint(0, 14, "┃                                        ┃");
	ScreenPrint(0, 15, "┃                                        ┃");
	ScreenPrint(0, 16, "┃                                        ┃");
	ScreenPrint(0, 17, "┃                                        ┃");
	ScreenPrint(0, 18, "┃                                        ┃");
	ScreenPrint(0, 19, "┃                                        ┃");
	ScreenPrint(0, 20, "┃                                        ┃");
	ScreenPrint(0, 21, "┃                                        ┃");
	ScreenPrint(0, 22, "┃                                        ┃");
	ScreenPrint(0, 23, "┗━━━━━━━━━━━━━━━━━━━━┛");
}

void Block::SoundInit()
{
	//// 시스템 오브젝트 생성과 초기화
	//FMOD_System_Create(&g_System);
	//FMOD_System_Init( g_System, 32, FMOD_INIT_NORMAL, NULL);

	//// 반복 사운드
	//FMOD_System_CreateSound( g_System, "title.wav", FMOD_DEFAULT | FMOD_LOOP_NORMAL , 0, &g_Sound[0]);
	//FMOD_System_CreateSound( g_System, "run.wav",   FMOD_DEFAULT | FMOD_LOOP_NORMAL, 0, &g_Sound[1]);
	//FMOD_System_CreateSound( g_System, "fail.wav",  FMOD_DEFAULT | FMOD_LOOP_NORMAL, 0, &g_Sound[2]); // 적군이 이겼을 때	

	//// 효과 사운드
	//FMOD_System_CreateSound( g_System, "stage.wav", FMOD_DEFAULT, 0, &g_Sound[3]); // 스테이지 출력시 
	//FMOD_System_CreateSound( g_System, "ball_bar_wall_collision.wav", FMOD_DEFAULT , 0, &g_Sound[4]); // 경계 영역과 공이 부딪힐 때
	//FMOD_System_CreateSound( g_System, "block_collision.wav", FMOD_DEFAULT , 0, &g_Sound[5]); // 벽돌과 공이 부딫힐 때
	//FMOD_System_CreateSound( g_System, "fire.wav", FMOD_DEFAULT , 0, &g_Sound[6]); // 공 발사
	//FMOD_System_CreateSound( g_System, "success.wav", FMOD_DEFAULT , 0, &g_Sound[7]); // 공 발사
}



void Block::SoundRelease()
{
	int i;

	//for( i = 0 ; i < 8 ; i++ )
	//	FMOD_Sound_Release(g_Sound[i]);	

	//FMOD_System_Close( g_System );
	//FMOD_System_Release( g_System );
}

int  Block::Search(int nEnd, int nX, int nY)
{
	int i;
	for (i = 0; i < nEnd; i++)
	{
		if (g_sBlock[i].nY == nY)
		{
			if (g_sBlock[i].nX == nX || (g_sBlock[i].nX + 1) == nX ||
				g_sBlock[i].nX == nX + 1 || (g_sBlock[i].nX + 1) == nX + 1)
				return 1; // 같은 것이 있으면
		}
	}
	return 0; // 같은 것이 없으면 
}

void  Block::SetBlock(int nBlockCount)
{
	int nX, nY, i;

	srand((unsigned int)time(NULL));
	for (i = 0; i < nBlockCount; i++)
	{
		g_sBlock[i].nLife = 1;

		while (1)
		{
			nX = rand() % 39 + 2; // 2 ~ 40 범위 안에서
			nY = rand() % 10 + 1; // 1 ~ 10 까지의 범위

			if (Search(i, nX, nY) == 0)
			{
				g_sBlock[i].nX = nX;
				g_sBlock[i].nY = nY;
				break;
			}
		}
	}
}


int Block::Collision(int nX, int nY)
{
	int i, nCount = 0; // 충돌 개수

					   // 공과 벽돌의 충돌
	for (i = 0; i < g_StageInfo2[g_nStage2].nBlockCount; i++)
	{
		if (g_sBlock[i].nLife == 1)
		{
			if (g_sBlock[i].nY == nY)
			{
				if ((g_sBlock[i].nX == nX || (g_sBlock[i].nX + 1) == nX) ||
					(g_sBlock[i].nX == (nX + 1) || (g_sBlock[i].nX + 1) == (nX + 1)))
				{
					g_sBall.nDirect = g_BlockState[g_sBall.nDirect];
					g_sBlock[i].nLife = 0;
					g_nBlockCount++;
					nCount++;
				}
			}
		}
	}

	// 충돌 체크 
	if (nCount != 0)
	{
		//FMOD_System_PlaySound( g_System, FMOD_CHANNEL_FREE, g_Sound[5], 0, &g_Channel[5]); // 공과 벽돌 충돌
		return 1;
	}

	// 공과 막대기 충돌
	for (i = 0; i < 3; i++)
	{
		if (nY == g_sBar.nY)
		{
			if ((nX >= g_sBar.nX[0] && nX <= (g_sBar.nX[2] + 1)) || ((nX + 1) >= g_sBar.nX[0] && (nX + 1) <= (g_sBar.nX[2] + 1)))
			{
				g_sBall.nDirect = g_BlockState[g_sBall.nDirect];
				//FMOD_System_PlaySound( g_System, FMOD_CHANNEL_FREE, g_Sound[4], 0, &g_Channel[4]); // READY 사운드 출력
				return 1;
			}
		}
	}

	// Note: 위쪽  
	if (nY < 1)
	{
		g_sBall.nDirect = g_StateTable[0][g_sBall.nDirect];
		return 1;
	}

	// Note: 오른쪽
	if (nX > 39)
	{
		g_sBall.nDirect = g_StateTable[1][g_sBall.nDirect];
		return 1;
	}

	// Note: 공의 초기화 및 생명 감소
	if (nY > 22)
	{
		g_sBall.nHP--;

		if (g_sBall.nHP == 0)
		{	// 게임 판정으로 
			g_nGameState2 = STOP2;
		}
		else {
			g_sBall.nX = g_sBar.nX[1];
			g_sBall.nY = g_sBar.nY - 1;
			g_sBall.nReady = 1;
		}

		return 1;
	}

	if (nX < 2)
	{
		g_sBall.nDirect == g_StateTable[3][g_sBall.nDirect];
		return 1;
	}

	return 0;
}

void Block::Init()
{
	if (g_nStage2 == -1) // 1번만 초기화가 되는 부분에 대한 처리 사항
	{
		SoundInit();
		g_nStage2 = 0;
		//FMOD_System_PlaySound( g_System, FMOD_CHANNEL_FREE, g_Sound[0], 0, &g_Channel[0] );
	}

	g_nGrade = 0;
	SetBlock(g_StageInfo2[g_nStage2].nBlockCount);

	// Note: 공 초기화
	g_sBall.nX = 19;
	g_sBall.nHP = 3;
	g_sBall.nY = 20;
	g_sBall.nDirect = TOP;
	g_sBall.OldTime = clock();
	g_sBall.nReady = 1;
	g_sBall.MoveTime = 50;

	// Note: 막대기 초기화
	g_sBar.nY = g_sBall.nY + 1;
	g_sBar.nX[0] = g_sBall.nX - 2;
	g_sBar.nX[1] = g_sBall.nX;
	g_sBar.nX[2] = g_sBall.nX + 2;
	g_sBar.MoveTime = 10;
	g_sBar.OldTime = clock();

	g_nBlockCount = 0;
}

void Block::Update()
{
	clock_t CurTime = clock();

	switch (g_nGameState2)
	{
	case READY2:
		if (CurTime - g_UpdateOldTime > 3000)  // 2초
		{
			g_nGameState2 = RUNNING2;
			g_GameStartTime2 = CurTime;

			//FMOD_System_PlaySound( g_System, FMOD_CHANNEL_FREE, g_Sound[1], 0, &g_Channel[1] ); // 게임 진행 사운드
		}
		break;

	case RUNNING2:
		g_RemainTime2 = (g_StageInfo2[g_nStage2].LimitTime - (CurTime - g_GameStartTime)) / 1000; // 게임 진행 남은 시간

		if ((CurTime - g_GameStartTime) > g_StageInfo2[g_nStage2].LimitTime || g_nBlockCount == g_StageInfo2[g_nStage2].nBlockCount)
		{
			g_nGameState2 = STOP2;
			return;
		}
		else if (g_sBall.nReady == 0) {

			if (CurTime - g_sBall.OldTime > g_sBall.MoveTime)
			{
				g_sBall.OldTime = CurTime;

				switch (g_sBall.nDirect)
				{
				case TOP:
					if (Collision(g_sBall.nX, g_sBall.nY - 1) == 0)
						g_sBall.nY--;
					break;
				case LEFT_TOP:
					if (Collision(g_sBall.nX + 1, g_sBall.nY - 1) == 0)
					{
						g_sBall.nX++;
						g_sBall.nY--;
					}
					break;
				case LEFT_DOWN:
					if (Collision(g_sBall.nX + 1, g_sBall.nY + 1) == 0)
					{
						g_sBall.nX++;
						g_sBall.nY++;
					}
					break;
				case DOWN2:
					if (Collision(g_sBall.nX, g_sBall.nY + 1) == 0)
						g_sBall.nY++;
					break;
				case RIGHT_DOWN:
					if (Collision(g_sBall.nX - 1, g_sBall.nY + 1) == 0)
					{
						g_sBall.nX--;
						g_sBall.nY++;
					}
					break;
				case RIGHT_TOP:
					if (Collision(g_sBall.nX - 1, g_sBall.nY - 1) == 0)
					{
						g_sBall.nX--;
						g_sBall.nY--;
					}
					break;
				}
			}
		}
		break;
	case STOP2:
		// 성공이냐 실패를 판단해주어서 출력을 해주는 부분이 와야 한다.  
		if (g_nBlockCount == g_StageInfo2[g_nStage2].nBlockCount && g_sBall.nHP > 0 && g_RemainTime2 > 0)
		{
			g_UpdateOldTime2 = CurTime;
			g_nGameState2 = SUCCESS2;
			g_nTotalGrade2 += g_nBlockCount * 10;
			//FMOD_Channel_Stop( g_Channel[1] ); // 배경음 중지
			//FMOD_System_PlaySound( g_System, FMOD_CHANNEL_FREE, g_Sound[7], 0, &g_Channel[7] ); // 미션 성공 사운드
		}
		else {
			g_nGameState2 = FAILED2;
			//FMOD_Channel_Stop( g_Channel[1] ); // 배경음 중지
			//FMOD_System_PlaySound( g_System, FMOD_CHANNEL_FREE, g_Sound[2], 0, &g_Channel[2] ); // 미션 실패 사운드
		}
		break;
	case SUCCESS2:
		if (CurTime - g_UpdateOldTime2 > 3000)
		{
			g_UpdateOldTime2 = CurTime;
			++g_nStage;
			Init();
			g_nGameState2 = READY2;
			//FMOD_Channel_Stop( g_Channel[7] );  // 미션 성공 사운드 출력 중지					
			//FMOD_System_PlaySound( g_System, FMOD_CHANNEL_FREE, g_Sound[3], 0, &g_Channel[3]); // READY 사운드 출력
		}
		break;
	}
}


void B_Draw::Render()
{
	int i;
	char string[100];

	ScreenClear();

	switch (g_nGameState2)
	{
	case INIT2:
		if (g_nStage2 == 0)
			InitScreen();
		break;

	case READY2:
		ReadyScreen();
		sprintf(string, "%d", g_nStage2 + 1);
		ScreenPrint(13, 7, string);
		break;
	case RUNNING2:
		RunningScreen();

		sprintf(string, "스테이지 : %d", g_nStage2 + 1);
		ScreenPrint(45, 2, string);

		sprintf(string, "생명 : %d ", g_sBall.nHP);
		ScreenPrint(45, 4, string);

		sprintf(string, "점수 : %d ", g_nGrade2);
		ScreenPrint(45, 6, string);

		sprintf(string, "남은 시간 : %d 분 %d 초", g_RemainTime2 / 60, g_RemainTime2 % 60);
		ScreenPrint(45, 8, string);


		for (i = 0; i < g_StageInfo2[g_nStage2].nBlockCount; i++)
		{
			if (g_sBlock[i].nLife == 1)
				ScreenPrint(g_sBlock[i].nX, g_sBlock[i].nY, "■");
		}

		for (i = 0; i < 3; i++)
		{
			ScreenPrint(g_sBar.nX[i], g_sBar.nY, "▣");
		}

		ScreenPrint(g_sBall.nX, g_sBall.nY, "●");
		break;
	case SUCCESS2:
		SuccessScreen();
		sprintf(string, "%d Stage", g_nStage2 + 1);
		ScreenPrint(19, 12, string);
		sprintf(string, "총점: %d", g_nTotalGrade2);
		ScreenPrint(25, 16, string);
		break;
	case FAILED2:
		FailureScreen();
		sprintf(string, "%d Stage!", g_nStage2 + 1);
		ScreenPrint(16, 4, string);
		break;

	case RESULT2:
		ResultScreen();
		sprintf(string, "%d", g_nTotalGrade2);
		ScreenPrint(25, 11, string);
		break;
	}

	ScreenFlipping();
}

void  Block::Release()
{
	int i;
	//for( i = 0 ; i < 8 ; i++ )
	//	FMOD_Sound_Release( g_Sound[i] ); 

	//   FMOD_System_Close( g_System ); 
	//   FMOD_System_Release( g_System );
}



void main()
{
	int choice;
	Supervise blank;
	cout << "1번)두더지   2번)블럭깨기" << endl;
	cin >> choice;

	if (choice == 1) {
		int nKey;

		ScreenInit();
		blank.Init();       // 초기화

		while (1)
		{
			if (_kbhit())
			{
				if (g_nGameState == RESULT)
					break;

				nKey = _getch();
				switch (nKey)
				{
				case ' ':
					if (g_nGameState == INIT && g_nStage == 0)
					{
						g_nGameState = READY;
						//FMOD_Channel_Stop( g_Channel[0] ); // 배경음 중지
						//FMOD_System_PlaySound( g_System, FMOD_CHANNEL_FREE, g_Sound[2], 0, &g_Channel[2]); // READY 사운드 출력
						g_UpdateOldTime = clock();  // ready를 일정시간 지속해 주기 위해 							
					}
					break;
				case '1':  // 망치 키 입력 1 ~ 9까지
				case '2':
				case '3':
				case '4':
				case '5':
				case '6':
				case '7':
				case '8':
				case '9':
					if (g_Mangchi.nIsAttack == 0 && g_nGameState == RUNNING)
					{
						g_Mangchi.nIndex = nKey - '1';
						g_Mangchi.StartTime = clock();
						g_Mangchi.nIsAttack = 1;
						//FMOD_System_PlaySound( g_System, FMOD_CHANNEL_FREE, g_Sound[5], 0, &g_Channel[5] );
					}
					break;

				case 'y':
				case 'Y':
					if (g_nGameState == FAILED)
					{
						blank.Init();
						g_nGameState = READY;
						//FMOD_Channel_Stop( g_Channel[1] );  // 미션 실패 사운드 출력 중지 
						//FMOD_System_PlaySound( g_System, FMOD_CHANNEL_FREE, g_Sound[2], 0, &g_Channel[2]); // READY 사운드 출력
						g_nGrade = 0;
						g_UpdateOldTime = clock();
					}
					break;
				case 'n':
				case 'N':
					if (g_nGameState == FAILED)
					{
						g_nGameState = RESULT;
						//FMOD_Channel_Stop( g_Channel[1] );  // 미션 실패 사운드 출력 중지							
					}
					break;
				}
			}

			blank.Update();    // 데이터 갱신
			blank.Render();    // 화면 출력
						 //FMOD_System_Update( g_System );
		}

		blank.Release();   // 해제
		ScreenRelease();
	}

	

//////////////////////////////////////////블럭코드

	else if (choice == 2)
	{
		int nKey, i, nX, nY;
		clock_t CurTime;

		Block blank;
		B_Draw blank2;

		ScreenInit();
		blank.Init();

		while (1)
		{
			if (_kbhit())
			{
				if (g_nGameState2 == RESULT2)
					break;

				nKey = _getch();

				switch (nKey)
				{
				case ' ':
					if (g_nGameState2 == INIT2 && g_nStage2 == 0)
					{
						g_nGameState2 = READY2;
						//FMOD_Channel_Stop( g_Channel[0] ); // 배경음 중지
						//FMOD_System_PlaySound( g_System, FMOD_CHANNEL_FREE, g_Sound[3], 0, &g_Channel[3]); // 스테이지 출력
						g_UpdateOldTime2 = clock();  // ready를 일정시간 지속해 주기 위해 							
					}
					break;

				case 'k': //공 발사
					if (g_nGameState2 == RUNNING2 && g_sBall.nReady == 1)
					{
						g_sBall.nReady = 0;  // 이동 상태
						g_sBall.OldTime = clock();
						//FMOD_System_PlaySound( g_System, FMOD_CHANNEL_FREE, g_Sound[6], 0, &g_Channel[6]); // 공 발사
					}
					break;

				case 'j':
					if (g_nGameState2 == RUNNING2)
					{

						CurTime = clock();
						if (CurTime - g_sBar.OldTime > g_sBar.MoveTime)
						{
							g_sBar.OldTime = CurTime;
							if (g_sBar.nX[0] > 2) // 경계 영역 충돌 체크
							{
								g_sBar.nX[0]--;
								g_sBar.nX[1]--;
								g_sBar.nX[2]--;

								if (g_sBall.nReady == 1)
									g_sBall.nX--;
							}
						}
					}
					break;
				case 'l':
					if (g_nGameState2 == RUNNING2)
					{
						CurTime = clock();
						if (CurTime - g_sBar.OldTime > g_sBar.MoveTime)
						{
							g_sBar.OldTime = CurTime;
							if (g_sBar.nX[2] < 40)  // 경계 영역 체크
							{
								g_sBar.nX[0]++;
								g_sBar.nX[1]++;
								g_sBar.nX[2]++;

								if (g_sBall.nReady == 1)
									g_sBall.nX++;
							}
						}
					}
					break;

				case 'i': // 공 잡기
						  //막대기와 공 충돌
					if (g_nGameState2 == RUNNING2 && g_sBall.nReady == 0)
					{
						nX = g_sBall.nX;
						nY = g_sBall.nY;

						for (i = 0; i < 3; i++)
						{
							if (nY == (g_sBar.nY - 1)) // 공과 막대기가 접한 경우
							{
								if ((nX >= g_sBar.nX[0] && nX <= (g_sBar.nX[2] + 1)) || ((nX + 1) >= g_sBar.nX[0] && (nX + 1) <= (g_sBar.nX[2] + 1)))
								{
									g_sBall.nReady = 1;
									break;
								}
							}
						}
					}
					break;

				case '1': // 공을 잡았을 때 1, 2, 3 방향 선택가능	
					if (g_nGameState2 == RUNNING2 && g_sBall.nReady == 1)
					{
						g_sBall.nDirect = RIGHT_TOP;
						g_sBall.OldTime = clock();
					}
					break;

				case '2':
					if (g_nGameState2 == RUNNING2 && g_sBall.nReady == 1)
					{
						g_sBall.nDirect = TOP;
						g_sBall.OldTime = clock();
					}
					break;

				case '3':
					if (g_nGameState2 == RUNNING2 && g_sBall.nReady == 1)
					{
						g_sBall.nDirect = LEFT_TOP;
						g_sBall.OldTime = clock();
					}
					break;
				case 'y':
				case 'Y':
					if (g_nGameState2 == FAILED2)
					{
						blank.Init();
						g_nGameState2 = READY2;
						//FMOD_Channel_Stop( g_Channel[2] );  // 미션 실패 사운드 출력 중지 
						//FMOD_System_PlaySound( g_System, FMOD_CHANNEL_FREE, g_Sound[3], 0, &g_Channel[3]); // READY 사운드 출력
						g_UpdateOldTime2 = clock();
					}
					break;
				case 'n':
				case 'N':
					if (g_nGameState2 == FAILED2)
					{
						g_nGameState2 = RESULT2;
						//FMOD_Channel_Stop( g_Channel[2] );  // 미션 실패 사운드 출력 중지							
					}
					break;
				}
			}

			blank.Update();
			blank2.Render();
			//FMOD_System_Update( g_System );	
		}

		blank.Release();
		ScreenRelease();
	}
}


