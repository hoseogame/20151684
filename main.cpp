

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
	int	nIsAttack;         // ��ġ ���� 
	clock_t	StartTime;     // Ÿ�� ���°� ���۵� �ð�
	clock_t	DelayTime;     // Ÿ�� ������ ���� �ð�
	int	nIndex;            // ��ǥ �迭�� �����ϱ� ���� �ε���
	int	nStayX, nStayY;    // ��� ������ �� ��ǥ	
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

	clock_t   StayTime;     // Note: ���� �� ��� �ð�
	clock_t	OutPutTime;     // Note: ������ �� ��� �ð�
	clock_t	OldTime;    // Note: ���� �ð�		
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
int			g_nGrade = 0; // ���� 
int			g_nStageCount = 1;
int			g_nDudagiCount = 0;
clock_t		g_GameStartTime, g_UpdateOldTime, g_RemainTime;
int			g_nTotalGrade = 0; // ����

							   //FMOD_SYSTEM *g_System;
							   //FMOD_SOUND *g_Sound[7];
							   //FMOD_CHANNEL *g_Channel[7];
							   // ����� �Ǵ� �ݺ���     // ȿ���� 
char *g_strSoundFile[7] = { "title.wav", "fail.wav", "ready.wav", "output.wav", "ubs.WAV", "WHOOSH1.WAV", "success.wav" };


void Draw::Mangchi(int x, int y)
{
	ScreenPrint(x - 4, y - 1, "�٦�����");
	ScreenPrint(x - 4, y, "�����Φ�������");
	ScreenPrint(x - 4, y + 1, "�٦�����");
}

void Draw::MangchiReady(int x, int y)
{
	ScreenPrint(x - 4, y - 2, "    ��");
	ScreenPrint(x - 4, y - 1, "  ������");
	ScreenPrint(x - 4, y, "  ��  ��");
	ScreenPrint(x - 4, y + 1, "  ������");
	ScreenPrint(x - 4, y + 2, "    ��");
	ScreenPrint(x - 4, y + 3, "    ��");
	ScreenPrint(x - 4, y + 4, "    ��");
	ScreenPrint(x - 4, y + 5, "    ��");
}

void Draw::InitScreen()
{
	ScreenPrint(0, 0, "��������������������������������������������");
	ScreenPrint(0, 1, "��                                        ��");
	ScreenPrint(0, 2, "��                                        ��");
	ScreenPrint(0, 3, "��                                        ��");
	ScreenPrint(0, 4, "��                                        ��");
	ScreenPrint(0, 5, "��                                        ��");
	ScreenPrint(0, 6, "��                                        ��");
	ScreenPrint(0, 7, "��                                        ��");
	ScreenPrint(0, 8, "��             ////////                   ��");
	ScreenPrint(0, 9, "��             ���� /�� ����/             ��");
	ScreenPrint(0, 10, "��             ����������������           ��");
	ScreenPrint(0, 11, "��             ����������������           ��");
	ScreenPrint(0, 12, "��                                        ��");
	ScreenPrint(0, 13, "��                                        ��");
	ScreenPrint(0, 14, "��                                        ��");
	ScreenPrint(0, 15, "��             �δ��� ��� ����           ��");
	ScreenPrint(0, 16, "��                                        ��");
	ScreenPrint(0, 17, "��          space Ű�� �����ּ���         ��");
	ScreenPrint(0, 18, "��                                        ��");
	ScreenPrint(0, 19, "��                                        ��");
	ScreenPrint(0, 20, "��                                        ��");
	ScreenPrint(0, 21, "��                                        ��");
	ScreenPrint(0, 22, "��                                        ��");
	ScreenPrint(0, 23, "��������������������������������������������");
}

void Draw::ReadyScreen()
{
	ScreenPrint(0, 0, "��������������������������������������������");
	ScreenPrint(0, 1, "����������������������᦭");
	ScreenPrint(0, 2, "����������������������᦭");
	ScreenPrint(0, 3, "����������������������᦭");
	ScreenPrint(0, 4, "����������������������᦭");
	ScreenPrint(0, 5, "����������������������᦭");
	ScreenPrint(0, 6, "����������������������᦭");
	ScreenPrint(0, 7, "����������������������᦭");
	ScreenPrint(0, 8, "����������������������᦭");
	ScreenPrint(0, 9, "����������������������᦭");
	ScreenPrint(0, 10, "��������                    �����᦭");
	ScreenPrint(0, 11, "��������        ��������    �����᦭");
	ScreenPrint(0, 12, "��������                    �����᦭");
	ScreenPrint(0, 13, "����������������������᦭");
	ScreenPrint(0, 14, "����������������������᦭");
	ScreenPrint(0, 15, "����������������������᦭");
	ScreenPrint(0, 16, "����������������������᦭");
	ScreenPrint(0, 17, "����������������������᦭");
	ScreenPrint(0, 18, "����������������������᦭");
	ScreenPrint(0, 19, "����������������������᦭");
	ScreenPrint(0, 20, "����������������������᦭");
	ScreenPrint(0, 21, "����������������������᦭");
	ScreenPrint(0, 22, "����������������������᦭");
	ScreenPrint(0, 23, "��������������������������������������������");
}

void Draw::SuccessScreen()
{
	ScreenPrint(0, 0, "��������������������������������������������");
	ScreenPrint(0, 1, "��                                        ��");
	ScreenPrint(0, 2, "��                                        ��");
	ScreenPrint(0, 3, "��                                        ��");
	ScreenPrint(0, 4, "��             // / // ������             ��");
	ScreenPrint(0, 5, "��             ��/��    /������           ��");
	ScreenPrint(0, 6, "��             ����  ��  �զ���           ��");
	ScreenPrint(0, 7, "��              ��_________///            ��");
	ScreenPrint(0, 8, "��                                        ��");
	ScreenPrint(0, 9, "��                                        ��");
	ScreenPrint(0, 10, "��                                        ��");
	ScreenPrint(0, 11, "��                       ��������         ��");
	ScreenPrint(0, 12, "��                                        ��");
	ScreenPrint(0, 13, "��                   �̼� ���� !!!!       ��");
	ScreenPrint(0, 14, "��                                        ��");
	ScreenPrint(0, 15, "��                                        ��");
	ScreenPrint(0, 16, "��                                        ��");
	ScreenPrint(0, 17, "��     ���� �δ��� :                      ��");
	ScreenPrint(0, 18, "��                                        ��");
	ScreenPrint(0, 19, "��     ���� :                             ��");
	ScreenPrint(0, 20, "��                                        ��");
	ScreenPrint(0, 21, "��                                        ��");
	ScreenPrint(0, 22, "��                                        ��");
	ScreenPrint(0, 23, "��������������������������������������������");
}

void Draw::RunningScreen()
{
	ScreenPrint(0, 0, "��������������������������������������������");
	ScreenPrint(0, 1, "��                                        ��");
	ScreenPrint(0, 2, "��                                        ��");
	ScreenPrint(0, 3, "��                                        ��");
	ScreenPrint(0, 4, "��                                        ��");
	ScreenPrint(0, 5, "��                                        ��");
	ScreenPrint(0, 6, "��                                        ��");
	ScreenPrint(0, 7, "��                                        ��");
	ScreenPrint(0, 8, "��                                        ��");
	ScreenPrint(0, 9, "��                                        ��");
	ScreenPrint(0, 10, "��                                        ��");
	ScreenPrint(0, 11, "��                                        ��");
	ScreenPrint(0, 12, "��                                        ��");
	ScreenPrint(0, 13, "��                                        ��");
	ScreenPrint(0, 14, "��                                        ��");
	ScreenPrint(0, 15, "��                                        ��");
	ScreenPrint(0, 16, "��                                        ��");
	ScreenPrint(0, 17, "��                                        ��");
	ScreenPrint(0, 18, "��                                        ��");
	ScreenPrint(0, 19, "��                            ��    ��    ��");
	ScreenPrint(0, 20, "��                          ���ᦰ���র  ��");
	ScreenPrint(0, 21, "��                            ����  ����  ��");
	ScreenPrint(0, 22, "��                                        ��");
	ScreenPrint(0, 23, "��������������������������������������������");
}

void Draw::FailureScreen()
{
	ScreenPrint(0, 0, "��������������������������������������������");
	ScreenPrint(0, 1, "��                                        ��");
	ScreenPrint(0, 2, "��                                        ��");
	ScreenPrint(0, 3, "��                                        ��");
	ScreenPrint(0, 4, "��                                        ��");
	ScreenPrint(0, 5, "��                                        ��");
	ScreenPrint(0, 6, "��             ��-����-��                 ��");
	ScreenPrint(0, 7, "��             d ��,.�� b                 ��");
	ScreenPrint(0, 8, "��             ���Ѧ��Ҧ�                 ��");
	ScreenPrint(0, 9, "��             �Ŧͦ��ɦ�                 ��");
	ScreenPrint(0, 10, "��               �Ʀ���                   ��");
	ScreenPrint(0, 11, "��                    ��������            ��");
	ScreenPrint(0, 12, "��                                        ��");
	ScreenPrint(0, 13, "��            �̼� ���� !!!!              ��");
	ScreenPrint(0, 14, "��                                        ��");
	ScreenPrint(0, 15, "��                                        ��");
	ScreenPrint(0, 16, "��                                        ��");
	ScreenPrint(0, 17, "��      �ٽ� �Ͻðڽ��ϱ�? ( y/n )        ��");
	ScreenPrint(0, 18, "��                                        ��");
	ScreenPrint(0, 19, "��                                        ��");
	ScreenPrint(0, 20, "��                                        ��");
	ScreenPrint(0, 21, "��                                        ��");
	ScreenPrint(0, 22, "��                                        ��");
	ScreenPrint(0, 23, "��������������������������������������������");
}

// Note: ���� ���� ��쿡 ��µǸ鼭 �ٽ� �Ұ������� ���� ȭ���̴�.

void Draw::ResultScreen()
{
	ScreenPrint(0, 0, "��������������������������������������������");
	ScreenPrint(0, 1, "��                                        ��");
	ScreenPrint(0, 2, "��                                        ��");
	ScreenPrint(0, 3, "��                                        ��");
	ScreenPrint(0, 4, "��                                        ��");
	ScreenPrint(0, 5, "��                                        ��");
	ScreenPrint(0, 6, "��                                        ��");
	ScreenPrint(0, 7, "��  (((    �δ��� ��� ���� Score  ))))   ��");
	ScreenPrint(0, 8, "��                                        ��");
	ScreenPrint(0, 9, "��                                        ��");
	ScreenPrint(0, 10, "��                                        ��");
	ScreenPrint(0, 11, "��           �� ����  :                   ��");
	ScreenPrint(0, 12, "��                                        ��");
	ScreenPrint(0, 13, "��                                        ��");
	ScreenPrint(0, 14, "��                                        ��");
	ScreenPrint(0, 15, "��                                        ��");
	ScreenPrint(0, 16, "��                                        ��");
	ScreenPrint(0, 17, "��                                        ��");
	ScreenPrint(0, 18, "��                                        ��");
	ScreenPrint(0, 19, "��                                        ��");
	ScreenPrint(0, 20, "��                                        ��");
	ScreenPrint(0, 21, "��                                        ��");
	ScreenPrint(0, 22, "��                                        ��");
	ScreenPrint(0, 23, "��������������������������������������������");
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

	if (g_nStage == -1) // 1���� �ʱ�ȭ�� �Ǵ� �κп� ���� ó�� ����
	{
		SoundInit();
		g_nStage = 0;
		//FMOD_System_PlaySound( g_System, FMOD_CHANNEL_FREE, g_Sound[0], 0, &g_Channel[0] );
	}

	g_nDudagiCount = 0; // ���� �δ��� ����	
	g_nGrade = 0;

	// Note: ��ġ �¾�
	g_Mangchi.nIsAttack = 0;
	g_Mangchi.nIndex = 0;
	g_Mangchi.nStayX = 38;
	g_Mangchi.nStayY = 10;
	g_Mangchi.StartTime = g_GameStartTime;
	g_Mangchi.DelayTime = 300;

	for (i = 0; i < 9; i++)
	{
		g_Dudagi[i].StayTime = rand() % g_StageInfo[g_nStage].DownLimitTime + 10; // Note: �ּ� 10�� �ȴ�.
		g_Dudagi[i].OldTime = clock();
		g_Dudagi[i].nState = SETUP;
		g_Dudagi[i].OutPutTime = rand() % g_StageInfo[g_nStage].UpLimitTime + 10; //�ּ� 10�� �ȴ�.
	}
}

void Supervise::Update()
{
	int i;
	clock_t CurTime = clock();

	switch (g_nGameState)
	{
	case READY:
		if (CurTime - g_UpdateOldTime > 2000)  // 2��
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
			// �δ��� ������Ʈ	
			for (i = 0; i < 9; i++)
			{
				switch (g_Dudagi[i].nState)
				{
				case SETUP:
					g_Dudagi[i].OldTime = CurTime;
					g_Dudagi[i].OutPutTime = rand() % (int)g_StageInfo[g_nStage].UpLimitTime + 10;
					g_Dudagi[i].StayTime = rand() % (int)g_StageInfo[g_nStage].DownLimitTime + 10;
					g_Dudagi[i].nState = UP;
					//FMOD_System_PlaySound( g_System, FMOD_CHANNEL_FREE, g_Sound[3], 0, &g_Channel[3] ); // ���ö��� ���
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

			// ��ġ ������Ʈ 
			if (g_Mangchi.nIsAttack)
			{
				// �浹 �׽�Ʈ ��ġ�� ���� �ϳ��� �δ����� ���� �� �ֱ⿡ �ϳ��� ������� �浹 üũ�� ���� ���´�.
				for (i = 0; i < 9; i++)
				{
					if (g_Dudagi[i].nState == UP && i == g_Mangchi.nIndex)
					{
						g_nGrade += 10;
						g_nDudagiCount++;
						g_Dudagi[i].nState = DOWN; // �׾����� �ٿ� ���·� �ٷ� ��ȯ�� �ϵ��� �Ѵ�.															
												   //FMOD_System_PlaySound( g_System, FMOD_CHANNEL_FREE, g_Sound[4], 0, &g_Channel[4] );								
						break;
					}
				}

				// Note: ��ġ�� ���¸� �������ִ� �κ� ��ġ�� ���� ���� ������ �ð� ���� �ӹ����� �ϱ� ���� �κ�
				if (CurTime - g_Mangchi.StartTime > g_Mangchi.DelayTime)
				{
					g_Mangchi.nIsAttack = 0;
				}
			}

			g_RemainTime = (g_StageInfo[g_nStage].LimitTime - (CurTime - g_GameStartTime)) / 1000; // ���� ���� ���� �ð�
		}
		break;
	case STOP:
		// �����̳� ���и� �Ǵ����־ ����� ���ִ� �κ��� �;� �Ѵ�.
		if (g_nDudagiCount >= g_StageInfo[g_nStage].nCatchDudagi)
		{
			g_UpdateOldTime = CurTime;
			g_nGameState = SUCCESS;
			g_nTotalGrade += g_nGrade;
			//FMOD_System_PlaySound( g_System, FMOD_CHANNEL_FREE, g_Sound[6], 0, &g_Channel[6] ); // �̼� ���� ����
		}
		else {
			g_nGameState = FAILED;
			//FMOD_System_PlaySound( g_System, FMOD_CHANNEL_FREE, g_Sound[1], 0, &g_Channel[1] ); // �̼� ���� ����
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
			//FMOD_Channel_Stop( g_Channel[6] );  // �̼� ���� ���� ��� ����					
			//FMOD_System_PlaySound( g_System, FMOD_CHANNEL_FREE, g_Sound[2], 0, &g_Channel[2]); // READY ���� ���
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

		sprintf(string, "��ǥ �δ��� : %d  ���� �δ��� : %d", g_StageInfo[g_nStage].nCatchDudagi, g_nDudagiCount);
		ScreenPrint(2, 1, string);
		sprintf(string, "�������� : %d ���� : %d ���� �ð� : %d ", g_nStage + 1, g_nGrade, g_RemainTime);
		ScreenPrint(2, 2, string);

		for (i = 0; i < 9; i++)
		{
			if (g_Dudagi[i].nState == UP)
				ScreenPrint(g_Point[i].nX, g_Point[i].nY, "��");

			ScreenPrint(g_Point[i].nX, g_Point[i].nY + 1, "��");
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

		sprintf( string, "��ǥ �δ��� : %d  ���� �δ��� : %d", g_StageInfo[g_nStage].nCatchDudagi, g_nDudagiCount );
		ScreenPrint( 2, 1, string );
		sprintf( string, "�������� : %d ���� : %d ���� �ð� : %d ", g_nStage + 1, g_nGrade, g_RemainTime );
		ScreenPrint( 2, 2, string );

		for ( i = 0; i < 9; i++ )
		{
			if ( g_Dudagi[i].nState == UP )
				ScreenPrint( g_Point[i].nX, g_Point[i].nY, "��" );

			ScreenPrint( g_Point[i].nX, g_Point[i].nY + 1, "��" );
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


///////////////////////������

typedef enum { INIT2, READY2, RUNNING2, SUCCESS2, FAILED2, STOP2, RESULT2 } GAME_STATE2;
typedef enum _DIRECT2 { TOP, LEFT_TOP, LEFT_DOWN, DOWN2, RIGHT_DOWN, RIGHT_TOP } DIRECT2;

typedef struct _STAGE_INFO2
{
	int      nBlockCount; // ���� ����
	clock_t  LimitTime;  // ���� �ð�
} STAGE_INFO2;

typedef struct _BALL
{
	int		 nReady;     // 1 �̸� �غ� ����, 0�̸� �̵� ����
	int		 nHP;        // ����
	int		 nX, nY;     // ��ǥ
	int   nDirect;    // �̵� ����
	clock_t  MoveTime;   // �̵� �ð� ����
	clock_t  OldTime;	 // ���� �̵� �ð�
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
int g_StateTable[4][6] = { // ���� �浹�ϰ� �Ǹ� ���� ����
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
int			g_nGrade2 = 0; // ���� 
int			g_nStageCount2 = 1;
clock_t		g_GameStartTime2, g_UpdateOldTime2, g_RemainTime2;
int			g_nTotalGrade2 = 0; // ����
STAGE_INFO2  g_StageInfo2[3] = { { 30, 60 * 1000 },{ 50, 2 * 60 * 1000 },{ 100, 3 * 60 * 1000 } };

int			g_nBlockCount = 0;   // ���� ����


void B_Draw::InitScreen() // ���� �Ұ� ȭ��
{
	ScreenPrint(0, 0, "��������������������������������������������");
	ScreenPrint(0, 1, "��                                        ��");
	ScreenPrint(0, 2, "��    �����������������    ��");
	ScreenPrint(0, 3, "��      ���������������      ��");
	ScreenPrint(0, 4, "��        �������������        ��");
	ScreenPrint(0, 5, "��          �����������          ��");
	ScreenPrint(0, 6, "��          ��������������������          ��");
	ScreenPrint(0, 7, "��          ���� ���� ����  �ڦ�          ��");
	ScreenPrint(0, 8, "��          ��������������������          ��");
	ScreenPrint(0, 9, "��              /)/)    �� ��             ��");
	ScreenPrint(0, 10, "��           ��(*'')/                     ��");
	ScreenPrint(0, 11, "��          �����������          ��");
	ScreenPrint(0, 12, "��        �������������        ��");
	ScreenPrint(0, 13, "��      ���������������      ��");
	ScreenPrint(0, 14, "��    �����������������    ��");
	ScreenPrint(0, 15, "��                                        ��");
	ScreenPrint(0, 16, "��                                        ��");
	ScreenPrint(0, 17, "��    �� �����̽�Ű�� �����ּ���!! ��     ��");
	ScreenPrint(0, 18, "��                                        ��");
	ScreenPrint(0, 19, "��     J:��  L:�� K: ���߻� I: �����     ��");
	ScreenPrint(0, 20, "��     ( �� �߻� ���� )                   ��");
	ScreenPrint(0, 21, "��       1: ���� 2: ���� 3: ������        ��");
	ScreenPrint(0, 22, "��                                        ��");
	ScreenPrint(0, 23, "��������������������������������������������");
}

void B_Draw::ReadyScreen()
{
	ScreenPrint(0, 0, "��������������������������������������������");
	ScreenPrint(0, 1, "��                                        ��");
	ScreenPrint(0, 2, "��                                        ��");
	ScreenPrint(0, 3, "��                                        ��");
	ScreenPrint(0, 4, "��                                        ��");
	ScreenPrint(0, 5, "��                                        ��");
	ScreenPrint(0, 6, "��                                        ��");
	ScreenPrint(0, 7, "��              S t a g e                 ��");
	ScreenPrint(0, 8, "��                            ��          ��");
	ScreenPrint(0, 9, "��                      �С리��          ��");
	ScreenPrint(0, 10, "��                        �С린          ��");
	ScreenPrint(0, 11, "��                          ������        ��");
	ScreenPrint(0, 12, "��                                        ��");
	ScreenPrint(0, 13, "��                                        ��");
	ScreenPrint(0, 14, "��                                        ��");
	ScreenPrint(0, 15, "��                                        ��");
	ScreenPrint(0, 16, "��                                        ��");
	ScreenPrint(0, 17, "��                                        ��");
	ScreenPrint(0, 18, "��                                        ��");
	ScreenPrint(0, 19, "��                                        ��");
	ScreenPrint(0, 20, "��                                        ��");
	ScreenPrint(0, 21, "��                                        ��");
	ScreenPrint(0, 22, "��                                        ��");
	ScreenPrint(0, 23, "��������������������������������������������");
}

void B_Draw::SuccessScreen()
{
	ScreenPrint(0, 0, "��������������������������������������������");
	ScreenPrint(0, 1, "��      *.                                ��");
	ScreenPrint(0, 2, "��              .*            .*          ��");
	ScreenPrint(0, 3, "��     *.                        .*       ��");
	ScreenPrint(0, 4, "��       *.             .*                ��");
	ScreenPrint(0, 5, "��           *.                           ��");
	ScreenPrint(0, 6, "��            *.             .*           ��");
	ScreenPrint(0, 7, "��     *.      *.��������.*��    .*       ��");
	ScreenPrint(0, 8, "��             ��������������             ��");
	ScreenPrint(0, 9, "��     *.      ��������������      .*     ��");
	ScreenPrint(0, 10, "��             ��������������~            ��");
	ScreenPrint(0, 11, "��        *.   ������������               ��");
	ScreenPrint(0, 12, "��                                        ��");
	ScreenPrint(0, 13, "��                          .*            ��");
	ScreenPrint(0, 14, "��  *.           You Win!!          *.    ��");
	ScreenPrint(0, 15, "��                                        ��");
	ScreenPrint(0, 16, "��                                        ��");
	ScreenPrint(0, 17, "��                       *.               ��");
	ScreenPrint(0, 18, "��    *.         *.                       ��");
	ScreenPrint(0, 19, "��                                 *.     ��");
	ScreenPrint(0, 20, "��                      *.                ��");
	ScreenPrint(0, 21, "��  *.                             *.     ��");
	ScreenPrint(0, 22, "��                                        ��");
	ScreenPrint(0, 23, "��������������������������������������������");
}

void B_Draw::FailureScreen()
{
	ScreenPrint(0, 0, "��������������������������������������������");
	ScreenPrint(0, 1, "��  �������������������  ��");
	ScreenPrint(0, 2, "��  �������������������  ��");
	ScreenPrint(0, 3, "��                                        ��");
	ScreenPrint(0, 4, "��                                        ��");
	ScreenPrint(0, 5, "��                                        ��");
	ScreenPrint(0, 6, "��                                        ��");
	ScreenPrint(0, 7, "��             *�Ѧ�  �Ѧ�*               ��");
	ScreenPrint(0, 8, "��          *.  �Ӥӡ�Ӥ�   .*           ��");
	ScreenPrint(0, 9, "��   ���ѤѤѤѤѤѤѤѤѤѤѤѤѤѦ�     ��");
	ScreenPrint(0, 10, "��   ������ �� ��ȸ�� �̿��� �ּ��䦭     ��");
	ScreenPrint(0, 11, "��   ���ѤѤѤѤѤѤѤѤѤѤѤѤѤѦ�     ��");
	ScreenPrint(0, 12, "��                                        ��");
	ScreenPrint(0, 13, "��                                        ��");
	ScreenPrint(0, 14, "��    (*�ҡ�*)                            ��");
	ScreenPrint(0, 15, "��   ��O������O����������������������     ��");
	ScreenPrint(0, 16, "��   ������Ͻðڽ��ϱ�? <y/n>     ��     ��");
	ScreenPrint(0, 17, "��   ��������������������������������     ��");
	ScreenPrint(0, 18, "��                                        ��");
	ScreenPrint(0, 19, "��                                        ��");
	ScreenPrint(0, 20, "��                                        ��");
	ScreenPrint(0, 21, "��  �������������������  ��");
	ScreenPrint(0, 22, "��  �������������������  ��");
	ScreenPrint(0, 23, "��������������������������������������������");
}

void B_Draw::RunningScreen()
{
	ScreenPrint(0, 0, "��������������������������������������������");
	ScreenPrint(0, 1, "��                                        ��");
	ScreenPrint(0, 2, "��                                        ��");
	ScreenPrint(0, 3, "��                                        ��");
	ScreenPrint(0, 4, "��                                        ��");
	ScreenPrint(0, 5, "��                                        ��");
	ScreenPrint(0, 6, "��                                        ��");
	ScreenPrint(0, 7, "��                                        ��");
	ScreenPrint(0, 8, "��                                        ��");
	ScreenPrint(0, 9, "��                                        ��");
	ScreenPrint(0, 10, "��                                        ��");
	ScreenPrint(0, 11, "��                                        ��");
	ScreenPrint(0, 12, "��                                        ��");
	ScreenPrint(0, 13, "��                                        ��");
	ScreenPrint(0, 14, "��                                        ��");
	ScreenPrint(0, 15, "��                                        ��");
	ScreenPrint(0, 16, "��                                        ��");
	ScreenPrint(0, 17, "��                                        ��");
	ScreenPrint(0, 18, "��                                        ��");
	ScreenPrint(0, 19, "��                                        ��");
	ScreenPrint(0, 20, "��                                        ��");
	ScreenPrint(0, 21, "��                                        ��");
	ScreenPrint(0, 22, "��                                        ��");
	ScreenPrint(0, 23, "��������������������������������������������");
}

void B_Draw::ResultScreen()
{
	ScreenPrint(0, 0, "��������������������������������������������");
	ScreenPrint(0, 1, "��                                        ��");
	ScreenPrint(0, 2, "��                                        ��");
	ScreenPrint(0, 3, "��                                        ��");
	ScreenPrint(0, 4, "��                                        ��");
	ScreenPrint(0, 5, "��                                        ��");
	ScreenPrint(0, 6, "��                                        ��");
	ScreenPrint(0, 7, "��   (((    ���� ����  ���� Score  ))))   ��");
	ScreenPrint(0, 8, "��                                        ��");
	ScreenPrint(0, 9, "��                                        ��");
	ScreenPrint(0, 10, "��                                        ��");
	ScreenPrint(0, 11, "��           �� ����  :                   ��");
	ScreenPrint(0, 12, "��                                        ��");
	ScreenPrint(0, 13, "��                                        ��");
	ScreenPrint(0, 14, "��                                        ��");
	ScreenPrint(0, 15, "��                                        ��");
	ScreenPrint(0, 16, "��                                        ��");
	ScreenPrint(0, 17, "��                                        ��");
	ScreenPrint(0, 18, "��                                        ��");
	ScreenPrint(0, 19, "��                                        ��");
	ScreenPrint(0, 20, "��                                        ��");
	ScreenPrint(0, 21, "��                                        ��");
	ScreenPrint(0, 22, "��                                        ��");
	ScreenPrint(0, 23, "��������������������������������������������");
}

void Block::SoundInit()
{
	//// �ý��� ������Ʈ ������ �ʱ�ȭ
	//FMOD_System_Create(&g_System);
	//FMOD_System_Init( g_System, 32, FMOD_INIT_NORMAL, NULL);

	//// �ݺ� ����
	//FMOD_System_CreateSound( g_System, "title.wav", FMOD_DEFAULT | FMOD_LOOP_NORMAL , 0, &g_Sound[0]);
	//FMOD_System_CreateSound( g_System, "run.wav",   FMOD_DEFAULT | FMOD_LOOP_NORMAL, 0, &g_Sound[1]);
	//FMOD_System_CreateSound( g_System, "fail.wav",  FMOD_DEFAULT | FMOD_LOOP_NORMAL, 0, &g_Sound[2]); // ������ �̰��� ��	

	//// ȿ�� ����
	//FMOD_System_CreateSound( g_System, "stage.wav", FMOD_DEFAULT, 0, &g_Sound[3]); // �������� ��½� 
	//FMOD_System_CreateSound( g_System, "ball_bar_wall_collision.wav", FMOD_DEFAULT , 0, &g_Sound[4]); // ��� ������ ���� �ε��� ��
	//FMOD_System_CreateSound( g_System, "block_collision.wav", FMOD_DEFAULT , 0, &g_Sound[5]); // ������ ���� �΋H�� ��
	//FMOD_System_CreateSound( g_System, "fire.wav", FMOD_DEFAULT , 0, &g_Sound[6]); // �� �߻�
	//FMOD_System_CreateSound( g_System, "success.wav", FMOD_DEFAULT , 0, &g_Sound[7]); // �� �߻�
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
				return 1; // ���� ���� ������
		}
	}
	return 0; // ���� ���� ������ 
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
			nX = rand() % 39 + 2; // 2 ~ 40 ���� �ȿ���
			nY = rand() % 10 + 1; // 1 ~ 10 ������ ����

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
	int i, nCount = 0; // �浹 ����

					   // ���� ������ �浹
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

	// �浹 üũ 
	if (nCount != 0)
	{
		//FMOD_System_PlaySound( g_System, FMOD_CHANNEL_FREE, g_Sound[5], 0, &g_Channel[5]); // ���� ���� �浹
		return 1;
	}

	// ���� ����� �浹
	for (i = 0; i < 3; i++)
	{
		if (nY == g_sBar.nY)
		{
			if ((nX >= g_sBar.nX[0] && nX <= (g_sBar.nX[2] + 1)) || ((nX + 1) >= g_sBar.nX[0] && (nX + 1) <= (g_sBar.nX[2] + 1)))
			{
				g_sBall.nDirect = g_BlockState[g_sBall.nDirect];
				//FMOD_System_PlaySound( g_System, FMOD_CHANNEL_FREE, g_Sound[4], 0, &g_Channel[4]); // READY ���� ���
				return 1;
			}
		}
	}

	// Note: ����  
	if (nY < 1)
	{
		g_sBall.nDirect = g_StateTable[0][g_sBall.nDirect];
		return 1;
	}

	// Note: ������
	if (nX > 39)
	{
		g_sBall.nDirect = g_StateTable[1][g_sBall.nDirect];
		return 1;
	}

	// Note: ���� �ʱ�ȭ �� ���� ����
	if (nY > 22)
	{
		g_sBall.nHP--;

		if (g_sBall.nHP == 0)
		{	// ���� �������� 
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
	if (g_nStage2 == -1) // 1���� �ʱ�ȭ�� �Ǵ� �κп� ���� ó�� ����
	{
		SoundInit();
		g_nStage2 = 0;
		//FMOD_System_PlaySound( g_System, FMOD_CHANNEL_FREE, g_Sound[0], 0, &g_Channel[0] );
	}

	g_nGrade = 0;
	SetBlock(g_StageInfo2[g_nStage2].nBlockCount);

	// Note: �� �ʱ�ȭ
	g_sBall.nX = 19;
	g_sBall.nHP = 3;
	g_sBall.nY = 20;
	g_sBall.nDirect = TOP;
	g_sBall.OldTime = clock();
	g_sBall.nReady = 1;
	g_sBall.MoveTime = 50;

	// Note: ����� �ʱ�ȭ
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
		if (CurTime - g_UpdateOldTime > 3000)  // 2��
		{
			g_nGameState2 = RUNNING2;
			g_GameStartTime2 = CurTime;

			//FMOD_System_PlaySound( g_System, FMOD_CHANNEL_FREE, g_Sound[1], 0, &g_Channel[1] ); // ���� ���� ����
		}
		break;

	case RUNNING2:
		g_RemainTime2 = (g_StageInfo2[g_nStage2].LimitTime - (CurTime - g_GameStartTime)) / 1000; // ���� ���� ���� �ð�

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
		// �����̳� ���и� �Ǵ����־ ����� ���ִ� �κ��� �;� �Ѵ�.  
		if (g_nBlockCount == g_StageInfo2[g_nStage2].nBlockCount && g_sBall.nHP > 0 && g_RemainTime2 > 0)
		{
			g_UpdateOldTime2 = CurTime;
			g_nGameState2 = SUCCESS2;
			g_nTotalGrade2 += g_nBlockCount * 10;
			//FMOD_Channel_Stop( g_Channel[1] ); // ����� ����
			//FMOD_System_PlaySound( g_System, FMOD_CHANNEL_FREE, g_Sound[7], 0, &g_Channel[7] ); // �̼� ���� ����
		}
		else {
			g_nGameState2 = FAILED2;
			//FMOD_Channel_Stop( g_Channel[1] ); // ����� ����
			//FMOD_System_PlaySound( g_System, FMOD_CHANNEL_FREE, g_Sound[2], 0, &g_Channel[2] ); // �̼� ���� ����
		}
		break;
	case SUCCESS2:
		if (CurTime - g_UpdateOldTime2 > 3000)
		{
			g_UpdateOldTime2 = CurTime;
			++g_nStage;
			Init();
			g_nGameState2 = READY2;
			//FMOD_Channel_Stop( g_Channel[7] );  // �̼� ���� ���� ��� ����					
			//FMOD_System_PlaySound( g_System, FMOD_CHANNEL_FREE, g_Sound[3], 0, &g_Channel[3]); // READY ���� ���
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

		sprintf(string, "�������� : %d", g_nStage2 + 1);
		ScreenPrint(45, 2, string);

		sprintf(string, "���� : %d ", g_sBall.nHP);
		ScreenPrint(45, 4, string);

		sprintf(string, "���� : %d ", g_nGrade2);
		ScreenPrint(45, 6, string);

		sprintf(string, "���� �ð� : %d �� %d ��", g_RemainTime2 / 60, g_RemainTime2 % 60);
		ScreenPrint(45, 8, string);


		for (i = 0; i < g_StageInfo2[g_nStage2].nBlockCount; i++)
		{
			if (g_sBlock[i].nLife == 1)
				ScreenPrint(g_sBlock[i].nX, g_sBlock[i].nY, "��");
		}

		for (i = 0; i < 3; i++)
		{
			ScreenPrint(g_sBar.nX[i], g_sBar.nY, "��");
		}

		ScreenPrint(g_sBall.nX, g_sBall.nY, "��");
		break;
	case SUCCESS2:
		SuccessScreen();
		sprintf(string, "%d Stage", g_nStage2 + 1);
		ScreenPrint(19, 12, string);
		sprintf(string, "����: %d", g_nTotalGrade2);
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
	cout << "1��)�δ���   2��)������" << endl;
	cin >> choice;

	if (choice == 1) {
		int nKey;

		ScreenInit();
		blank.Init();       // �ʱ�ȭ

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
						//FMOD_Channel_Stop( g_Channel[0] ); // ����� ����
						//FMOD_System_PlaySound( g_System, FMOD_CHANNEL_FREE, g_Sound[2], 0, &g_Channel[2]); // READY ���� ���
						g_UpdateOldTime = clock();  // ready�� �����ð� ������ �ֱ� ���� 							
					}
					break;
				case '1':  // ��ġ Ű �Է� 1 ~ 9����
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
						//FMOD_Channel_Stop( g_Channel[1] );  // �̼� ���� ���� ��� ���� 
						//FMOD_System_PlaySound( g_System, FMOD_CHANNEL_FREE, g_Sound[2], 0, &g_Channel[2]); // READY ���� ���
						g_nGrade = 0;
						g_UpdateOldTime = clock();
					}
					break;
				case 'n':
				case 'N':
					if (g_nGameState == FAILED)
					{
						g_nGameState = RESULT;
						//FMOD_Channel_Stop( g_Channel[1] );  // �̼� ���� ���� ��� ����							
					}
					break;
				}
			}

			blank.Update();    // ������ ����
			blank.Render();    // ȭ�� ���
						 //FMOD_System_Update( g_System );
		}

		blank.Release();   // ����
		ScreenRelease();
	}

	

//////////////////////////////////////////���ڵ�

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
						//FMOD_Channel_Stop( g_Channel[0] ); // ����� ����
						//FMOD_System_PlaySound( g_System, FMOD_CHANNEL_FREE, g_Sound[3], 0, &g_Channel[3]); // �������� ���
						g_UpdateOldTime2 = clock();  // ready�� �����ð� ������ �ֱ� ���� 							
					}
					break;

				case 'k': //�� �߻�
					if (g_nGameState2 == RUNNING2 && g_sBall.nReady == 1)
					{
						g_sBall.nReady = 0;  // �̵� ����
						g_sBall.OldTime = clock();
						//FMOD_System_PlaySound( g_System, FMOD_CHANNEL_FREE, g_Sound[6], 0, &g_Channel[6]); // �� �߻�
					}
					break;

				case 'j':
					if (g_nGameState2 == RUNNING2)
					{

						CurTime = clock();
						if (CurTime - g_sBar.OldTime > g_sBar.MoveTime)
						{
							g_sBar.OldTime = CurTime;
							if (g_sBar.nX[0] > 2) // ��� ���� �浹 üũ
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
							if (g_sBar.nX[2] < 40)  // ��� ���� üũ
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

				case 'i': // �� ���
						  //������ �� �浹
					if (g_nGameState2 == RUNNING2 && g_sBall.nReady == 0)
					{
						nX = g_sBall.nX;
						nY = g_sBall.nY;

						for (i = 0; i < 3; i++)
						{
							if (nY == (g_sBar.nY - 1)) // ���� ����Ⱑ ���� ���
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

				case '1': // ���� ����� �� 1, 2, 3 ���� ���ð���	
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
						//FMOD_Channel_Stop( g_Channel[2] );  // �̼� ���� ���� ��� ���� 
						//FMOD_System_PlaySound( g_System, FMOD_CHANNEL_FREE, g_Sound[3], 0, &g_Channel[3]); // READY ���� ���
						g_UpdateOldTime2 = clock();
					}
					break;
				case 'n':
				case 'N':
					if (g_nGameState2 == FAILED2)
					{
						g_nGameState2 = RESULT2;
						//FMOD_Channel_Stop( g_Channel[2] );  // �̼� ���� ���� ��� ����							
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


