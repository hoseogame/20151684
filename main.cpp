

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
	int	nIsAttack;         // 蜂纂 鼻鷓 
	clock_t	StartTime;     // 顫問 鼻鷓陛 衛濛脹 衛陝
	clock_t	DelayTime;     // 顫問 鼻鷓曖 雖翱 衛陝
	int	nIndex;            // 謝ル 寡翮縑 蕾斬ж晦 嬪и 檣策蝶
	int	nStayX, nStayY;    // 渠晦 鼻鷓橾 陽 謝ル	
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

	clock_t   StayTime;     // Note: 菟橫鬲擊 陽 渠晦 衛除
	clock_t	OutPutTime;     // Note: 釭諮擊 陽 渠晦 衛除
	clock_t	OldTime;    // Note: 檜瞪 衛陝		
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
int			g_nGrade = 0; // 薄熱 
int			g_nStageCount = 1;
int			g_nDudagiCount = 0;
clock_t		g_GameStartTime, g_UpdateOldTime, g_RemainTime;
int			g_nTotalGrade = 0; // 識薄

							   //FMOD_SYSTEM *g_System;
							   //FMOD_SOUND *g_Sound[7];
							   //FMOD_CHANNEL *g_Channel[7];
							   // 寡唳擠 傳朝 奩犒擠     // �膩�擠 
char *g_strSoundFile[7] = { "title.wav", "fail.wav", "ready.wav", "output.wav", "ubs.WAV", "WHOOSH1.WAV", "success.wav" };


void Draw::Mangchi(int x, int y)
{
	ScreenPrint(x - 4, y - 1, "≧旨收旬");
	ScreenPrint(x - 4, y, "↖早統早㏑㏑↖↗");
	ScreenPrint(x - 4, y + 1, "≧曲收旭");
}

void Draw::MangchiReady(int x, int y)
{
	ScreenPrint(x - 4, y - 2, "    ↘");
	ScreenPrint(x - 4, y - 1, "  旨收旬");
	ScreenPrint(x - 4, y, "  早  早");
	ScreenPrint(x - 4, y + 1, "  曲收旭");
	ScreenPrint(x - 4, y + 2, "    ‵");
	ScreenPrint(x - 4, y + 3, "    ‵");
	ScreenPrint(x - 4, y + 4, "    ↘");
	ScreenPrint(x - 4, y + 5, "    ↙");
}

void Draw::InitScreen()
{
	ScreenPrint(0, 0, "旨收收收收收收收收收收收收收收收收收收收收旬");
	ScreenPrint(0, 1, "早                                        早");
	ScreenPrint(0, 2, "早                                        早");
	ScreenPrint(0, 3, "早                                        早");
	ScreenPrint(0, 4, "早                                        早");
	ScreenPrint(0, 5, "早                                        早");
	ScreenPrint(0, 6, "早                                        早");
	ScreenPrint(0, 7, "早                                        早");
	ScreenPrint(0, 8, "早             ////////                   早");
	ScreenPrint(0, 9, "早             早′ /早 ′弛/             早");
	ScreenPrint(0, 10, "早             早﹞﹞早旨有有旬           早");
	ScreenPrint(0, 11, "早             曲旬旨旭曲旬旨旭           早");
	ScreenPrint(0, 12, "早                                        早");
	ScreenPrint(0, 13, "早                                        早");
	ScreenPrint(0, 14, "早                                        早");
	ScreenPrint(0, 15, "早             舒渦雖 濩晦 啪歜           早");
	ScreenPrint(0, 16, "早                                        早");
	ScreenPrint(0, 17, "早          space 酈蒂 揚楝輿撮蹂         早");
	ScreenPrint(0, 18, "早                                        早");
	ScreenPrint(0, 19, "早                                        早");
	ScreenPrint(0, 20, "早                                        早");
	ScreenPrint(0, 21, "早                                        早");
	ScreenPrint(0, 22, "早                                        早");
	ScreenPrint(0, 23, "曲收收收收收收收收收收收收收收收收收收收收旭");
}

void Draw::ReadyScreen()
{
	ScreenPrint(0, 0, "旨收收收收收收收收收收收收收收收收收收收收旬");
	ScreenPrint(0, 1, "早﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥早");
	ScreenPrint(0, 2, "早﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥早");
	ScreenPrint(0, 3, "早﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥早");
	ScreenPrint(0, 4, "早﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥早");
	ScreenPrint(0, 5, "早﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥早");
	ScreenPrint(0, 6, "早﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥早");
	ScreenPrint(0, 7, "早﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥早");
	ScreenPrint(0, 8, "早﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥早");
	ScreenPrint(0, 9, "早﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥早");
	ScreenPrint(0, 10, "早﹥﹥﹥﹥﹥                    ﹥﹥﹥﹥﹥早");
	ScreenPrint(0, 11, "早﹥﹥﹥﹥﹥        蝶纔檜雖    ﹥﹥﹥﹥﹥早");
	ScreenPrint(0, 12, "早﹥﹥﹥﹥﹥                    ﹥﹥﹥﹥﹥早");
	ScreenPrint(0, 13, "早﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥早");
	ScreenPrint(0, 14, "早﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥早");
	ScreenPrint(0, 15, "早﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥早");
	ScreenPrint(0, 16, "早﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥早");
	ScreenPrint(0, 17, "早﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥早");
	ScreenPrint(0, 18, "早﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥早");
	ScreenPrint(0, 19, "早﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥早");
	ScreenPrint(0, 20, "早﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥早");
	ScreenPrint(0, 21, "早﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥早");
	ScreenPrint(0, 22, "早﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥早");
	ScreenPrint(0, 23, "曲收收收收收收收收收收收收收收收收收收收收旭");
}

void Draw::SuccessScreen()
{
	ScreenPrint(0, 0, "旨收收收收收收收收收收收收收收收收收收收收旬");
	ScreenPrint(0, 1, "早                                        早");
	ScreenPrint(0, 2, "早                                        早");
	ScreenPrint(0, 3, "早                                        早");
	ScreenPrint(0, 4, "早             // / // ′′′             早");
	ScreenPrint(0, 5, "早             弛/′    /′弛Ｏ           早");
	ScreenPrint(0, 6, "早             弛＜  ∩  ＜弛∞           早");
	ScreenPrint(0, 7, "早              ′_________///            早");
	ScreenPrint(0, 8, "早                                        早");
	ScreenPrint(0, 9, "早                                        早");
	ScreenPrint(0, 10, "早                                        早");
	ScreenPrint(0, 11, "早                       蝶纔檜雖         早");
	ScreenPrint(0, 12, "早                                        早");
	ScreenPrint(0, 13, "早                   嘐暮 撩奢 !!!!       早");
	ScreenPrint(0, 14, "早                                        早");
	ScreenPrint(0, 15, "早                                        早");
	ScreenPrint(0, 16, "早                                        早");
	ScreenPrint(0, 17, "早     濩擎 舒渦雖 :                      早");
	ScreenPrint(0, 18, "早                                        早");
	ScreenPrint(0, 19, "早     識薄 :                             早");
	ScreenPrint(0, 20, "早                                        早");
	ScreenPrint(0, 21, "早                                        早");
	ScreenPrint(0, 22, "早                                        早");
	ScreenPrint(0, 23, "曲收收收收收收收收收收收收收收收收收收收收旭");
}

void Draw::RunningScreen()
{
	ScreenPrint(0, 0, "旨收收收收收收收收收收收收收收收收收收收收旬");
	ScreenPrint(0, 1, "早                                        早");
	ScreenPrint(0, 2, "早                                        早");
	ScreenPrint(0, 3, "早                                        早");
	ScreenPrint(0, 4, "早                                        早");
	ScreenPrint(0, 5, "早                                        早");
	ScreenPrint(0, 6, "早                                        早");
	ScreenPrint(0, 7, "早                                        早");
	ScreenPrint(0, 8, "早                                        早");
	ScreenPrint(0, 9, "早                                        早");
	ScreenPrint(0, 10, "早                                        早");
	ScreenPrint(0, 11, "早                                        早");
	ScreenPrint(0, 12, "早                                        早");
	ScreenPrint(0, 13, "早                                        早");
	ScreenPrint(0, 14, "早                                        早");
	ScreenPrint(0, 15, "早                                        早");
	ScreenPrint(0, 16, "早                                        早");
	ScreenPrint(0, 17, "早                                        早");
	ScreenPrint(0, 18, "早                                        早");
	ScreenPrint(0, 19, "早                            ∞    ≒    早");
	ScreenPrint(0, 20, "早                          旨﹥旭旨﹤旭  早");
	ScreenPrint(0, 21, "早                            旭旬  旭旬  早");
	ScreenPrint(0, 22, "早                                        早");
	ScreenPrint(0, 23, "曲收收收收收收收收收收收收收收收收收收收收旭");
}

void Draw::FailureScreen()
{
	ScreenPrint(0, 0, "旨收收收收收收收收收收收收收收收收收收收收旬");
	ScreenPrint(0, 1, "早                                        早");
	ScreenPrint(0, 2, "早                                        早");
	ScreenPrint(0, 3, "早                                        早");
	ScreenPrint(0, 4, "早                                        早");
	ScreenPrint(0, 5, "早                                        早");
	ScreenPrint(0, 6, "早             灰-收收-汐                 早");
	ScreenPrint(0, 7, "早             d 玫,.玫 b                 早");
	ScreenPrint(0, 8, "早             早老式考早                 早");
	ScreenPrint(0, 9, "早             汍糸弛牝污                 早");
	ScreenPrint(0, 10, "早               汎死汛                   早");
	ScreenPrint(0, 11, "早                    蝶纔檜雖            早");
	ScreenPrint(0, 12, "早                                        早");
	ScreenPrint(0, 13, "早            嘐暮 褒ぬ !!!!              早");
	ScreenPrint(0, 14, "早                                        早");
	ScreenPrint(0, 15, "早                                        早");
	ScreenPrint(0, 16, "早                                        早");
	ScreenPrint(0, 17, "早      棻衛 ж衛啊蝗棲梱? ( y/n )        早");
	ScreenPrint(0, 18, "早                                        早");
	ScreenPrint(0, 19, "早                                        早");
	ScreenPrint(0, 20, "早                                        早");
	ScreenPrint(0, 21, "早                                        早");
	ScreenPrint(0, 22, "早                                        早");
	ScreenPrint(0, 23, "曲收收收收收收收收收收收收收收收收收收收收旭");
}

// Note: 褒ぬ ц擊 唳辦縑 轎溘腎賊憮 棻衛 й匙檣雖蒂 僖朝 �飛橉抴�.

void Draw::ResultScreen()
{
	ScreenPrint(0, 0, "旨收收收收收收收收收收收收收收收收收收收收旬");
	ScreenPrint(0, 1, "早                                        早");
	ScreenPrint(0, 2, "早                                        早");
	ScreenPrint(0, 3, "早                                        早");
	ScreenPrint(0, 4, "早                                        早");
	ScreenPrint(0, 5, "早                                        早");
	ScreenPrint(0, 6, "早                                        早");
	ScreenPrint(0, 7, "早  (((    舒渦雖 濩晦 啪歜 Score  ))))   早");
	ScreenPrint(0, 8, "早                                        早");
	ScreenPrint(0, 9, "早                                        早");
	ScreenPrint(0, 10, "早                                        早");
	ScreenPrint(0, 11, "早           識 薄熱  :                   早");
	ScreenPrint(0, 12, "早                                        早");
	ScreenPrint(0, 13, "早                                        早");
	ScreenPrint(0, 14, "早                                        早");
	ScreenPrint(0, 15, "早                                        早");
	ScreenPrint(0, 16, "早                                        早");
	ScreenPrint(0, 17, "早                                        早");
	ScreenPrint(0, 18, "早                                        早");
	ScreenPrint(0, 19, "早                                        早");
	ScreenPrint(0, 20, "早                                        早");
	ScreenPrint(0, 21, "早                                        早");
	ScreenPrint(0, 22, "早                                        早");
	ScreenPrint(0, 23, "曲收收收收收收收收收收收收收收收收收收收收旭");
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

	if (g_nStage == -1) // 1廓虜 蟾晦�降� 腎朝 睡碟縑 渠и 籀葬 餌о
	{
		SoundInit();
		g_nStage = 0;
		//FMOD_System_PlaySound( g_System, FMOD_CHANNEL_FREE, g_Sound[0], 0, &g_Channel[0] );
	}

	g_nDudagiCount = 0; // 濩擎 舒渦雖 偃熱	
	g_nGrade = 0;

	// Note: 蜂纂 撢機
	g_Mangchi.nIsAttack = 0;
	g_Mangchi.nIndex = 0;
	g_Mangchi.nStayX = 38;
	g_Mangchi.nStayY = 10;
	g_Mangchi.StartTime = g_GameStartTime;
	g_Mangchi.DelayTime = 300;

	for (i = 0; i < 9; i++)
	{
		g_Dudagi[i].StayTime = rand() % g_StageInfo[g_nStage].DownLimitTime + 10; // Note: 譆模 10擎 脹棻.
		g_Dudagi[i].OldTime = clock();
		g_Dudagi[i].nState = SETUP;
		g_Dudagi[i].OutPutTime = rand() % g_StageInfo[g_nStage].UpLimitTime + 10; //譆模 10擎 脹棻.
	}
}

void Supervise::Update()
{
	int i;
	clock_t CurTime = clock();

	switch (g_nGameState)
	{
	case READY:
		if (CurTime - g_UpdateOldTime > 2000)  // 2蟾
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
			// 舒渦雖 機等檜お	
			for (i = 0; i < 9; i++)
			{
				switch (g_Dudagi[i].nState)
				{
				case SETUP:
					g_Dudagi[i].OldTime = CurTime;
					g_Dudagi[i].OutPutTime = rand() % (int)g_StageInfo[g_nStage].UpLimitTime + 10;
					g_Dudagi[i].StayTime = rand() % (int)g_StageInfo[g_nStage].DownLimitTime + 10;
					g_Dudagi[i].nState = UP;
					//FMOD_System_PlaySound( g_System, FMOD_CHANNEL_FREE, g_Sound[3], 0, &g_Channel[3] ); // 釭螢陽虜 轎溘
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

			// 蜂纂 機等檜お 
			if (g_Mangchi.nIsAttack)
			{
				// 醱給 纔蝶お 蜂纂朝 螃霜 ж釭曖 舒渦雖虜 濩擊 熱 氈晦縑 ж釭虜 濩懊戲賊 醱給 羹觼蒂 緒螳 釭螞棻.
				for (i = 0; i < 9; i++)
				{
					if (g_Dudagi[i].nState == UP && i == g_Mangchi.nIndex)
					{
						g_nGrade += 10;
						g_nDudagiCount++;
						g_Dudagi[i].nState = DOWN; // 避歷戲賊 棻遴 鼻鷓煎 夥煎 瞪�素� ж紫煙 и棻.															
												   //FMOD_System_PlaySound( g_System, FMOD_CHANNEL_FREE, g_Sound[4], 0, &g_Channel[4] );								
						break;
					}
				}

				// Note: 蜂纂曖 鼻鷓蒂 滲唳п輿朝 睡碟 蜂纂煎 蟻擊 陽縑 橾薑и 衛除 翕寰 該僭紫煙 ж晦 嬪и 睡碟
				if (CurTime - g_Mangchi.StartTime > g_Mangchi.DelayTime)
				{
					g_Mangchi.nIsAttack = 0;
				}
			}

			g_RemainTime = (g_StageInfo[g_nStage].LimitTime - (CurTime - g_GameStartTime)) / 1000; // 啪歜 霞ч 陴擎 衛除
		}
		break;
	case STOP:
		// 撩奢檜傍 褒ぬ蒂 っ欽п輿橫憮 轎溘擊 п輿朝 睡碟檜 諦撿 и棻.
		if (g_nDudagiCount >= g_StageInfo[g_nStage].nCatchDudagi)
		{
			g_UpdateOldTime = CurTime;
			g_nGameState = SUCCESS;
			g_nTotalGrade += g_nGrade;
			//FMOD_System_PlaySound( g_System, FMOD_CHANNEL_FREE, g_Sound[6], 0, &g_Channel[6] ); // 嘐暮 撩奢 餌遴萄
		}
		else {
			g_nGameState = FAILED;
			//FMOD_System_PlaySound( g_System, FMOD_CHANNEL_FREE, g_Sound[1], 0, &g_Channel[1] ); // 嘐暮 褒ぬ 餌遴萄
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
			//FMOD_Channel_Stop( g_Channel[6] );  // 嘐暮 撩奢 餌遴萄 轎溘 醞雖					
			//FMOD_System_PlaySound( g_System, FMOD_CHANNEL_FREE, g_Sound[2], 0, &g_Channel[2]); // READY 餌遴萄 轎溘
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

		sprintf(string, "跡ル 舒渦雖 : %d  濩擎 舒渦雖 : %d", g_StageInfo[g_nStage].nCatchDudagi, g_nDudagiCount);
		ScreenPrint(2, 1, string);
		sprintf(string, "蝶纔檜雖 : %d 薄熱 : %d 陴擎 衛除 : %d ", g_nStage + 1, g_nGrade, g_RemainTime);
		ScreenPrint(2, 2, string);

		for (i = 0; i < 9; i++)
		{
			if (g_Dudagi[i].nState == UP)
				ScreenPrint(g_Point[i].nX, g_Point[i].nY, "≒");

			ScreenPrint(g_Point[i].nX, g_Point[i].nY + 1, "卄");
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

		sprintf( string, "跡ル 舒渦雖 : %d  濩擎 舒渦雖 : %d", g_StageInfo[g_nStage].nCatchDudagi, g_nDudagiCount );
		ScreenPrint( 2, 1, string );
		sprintf( string, "蝶纔檜雖 : %d 薄熱 : %d 陴擎 衛除 : %d ", g_nStage + 1, g_nGrade, g_RemainTime );
		ScreenPrint( 2, 2, string );

		for ( i = 0; i < 9; i++ )
		{
			if ( g_Dudagi[i].nState == UP )
				ScreenPrint( g_Point[i].nX, g_Point[i].nY, "≒" );

			ScreenPrint( g_Point[i].nX, g_Point[i].nY + 1, "卄" );
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


///////////////////////綰楣褒ч

typedef enum { INIT2, READY2, RUNNING2, SUCCESS2, FAILED2, STOP2, RESULT2 } GAME_STATE2;
typedef enum _DIRECT2 { TOP, LEFT_TOP, LEFT_DOWN, DOWN2, RIGHT_DOWN, RIGHT_TOP } DIRECT2;

typedef struct _STAGE_INFO2
{
	int      nBlockCount; // 漁給 偃熱
	clock_t  LimitTime;  // 薯и 衛除
} STAGE_INFO2;

typedef struct _BALL
{
	int		 nReady;     // 1 檜賊 遽綠 鼻鷓, 0檜賊 檜翕 鼻鷓
	int		 nHP;        // 儅貲
	int		 nX, nY;     // 謝ル
	int   nDirect;    // 檜翕 寞щ
	clock_t  MoveTime;   // 檜翕 衛除 除問
	clock_t  OldTime;	 // 檜瞪 檜翕 衛陝
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
int g_StateTable[4][6] = { // 漁婁 醱給ж啪 腎賊 寞щ 鼻鷓
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
int			g_nGrade2 = 0; // 薄熱 
int			g_nStageCount2 = 1;
clock_t		g_GameStartTime2, g_UpdateOldTime2, g_RemainTime2;
int			g_nTotalGrade2 = 0; // 識薄
STAGE_INFO2  g_StageInfo2[3] = { { 30, 60 * 1000 },{ 50, 2 * 60 * 1000 },{ 100, 3 * 60 * 1000 } };

int			g_nBlockCount = 0;   // 蜃轔 漁給


void B_Draw::InitScreen() // 啪歜 模偃 �飛�
{
	ScreenPrint(0, 0, "旨收收收收收收收收收收收收收收收收收收收收旬");
	ScreenPrint(0, 1, "早                                        早");
	ScreenPrint(0, 2, "早    ﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥    早");
	ScreenPrint(0, 3, "早      ﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥      早");
	ScreenPrint(0, 4, "早        ﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥        早");
	ScreenPrint(0, 5, "早          ﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥          早");
	ScreenPrint(0, 6, "早          旨收收收收收收收收旬          早");
	ScreenPrint(0, 7, "早          早≠ 漁給 梟晦  ≠早          早");
	ScreenPrint(0, 8, "早          曲收收收收收有收收旭          早");
	ScreenPrint(0, 9, "早              /)/)    早 ≧             早");
	ScreenPrint(0, 10, "早           ≠(*'')/                     早");
	ScreenPrint(0, 11, "早          ﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥          早");
	ScreenPrint(0, 12, "早        ﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥        早");
	ScreenPrint(0, 13, "早      ﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥      早");
	ScreenPrint(0, 14, "早    ﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥    早");
	ScreenPrint(0, 15, "早                                        早");
	ScreenPrint(0, 16, "早                                        早");
	ScreenPrint(0, 17, "早    ≠ 蝶む檜蝶酈蒂 揚楝輿撮蹂!! ≠     早");
	ScreenPrint(0, 18, "早                                        早");
	ScreenPrint(0, 19, "早     J:謝  L:辦 K: 奢嫦餌 I: 奢濩晦     早");
	ScreenPrint(0, 20, "早     ( 奢 嫦餌 寞щ )                   早");
	ScreenPrint(0, 21, "早       1: 豭褶 2: 嬪薹 3: 螃艇薹        早");
	ScreenPrint(0, 22, "早                                        早");
	ScreenPrint(0, 23, "曲收收收收收收收收收收收收收收收收收收收收旭");
}

void B_Draw::ReadyScreen()
{
	ScreenPrint(0, 0, "旨收收收收收收收收收收收收收收收收收收收收旬");
	ScreenPrint(0, 1, "早                                        早");
	ScreenPrint(0, 2, "早                                        早");
	ScreenPrint(0, 3, "早                                        早");
	ScreenPrint(0, 4, "早                                        早");
	ScreenPrint(0, 5, "早                                        早");
	ScreenPrint(0, 6, "早                                        早");
	ScreenPrint(0, 7, "早              S t a g e                 早");
	ScreenPrint(0, 8, "早                            ≒          早");
	ScreenPrint(0, 9, "早                      Ｂ㏑收早          早");
	ScreenPrint(0, 10, "早                        Ｂ㏑旭          早");
	ScreenPrint(0, 11, "早                          旨朴旬        早");
	ScreenPrint(0, 12, "早                                        早");
	ScreenPrint(0, 13, "早                                        早");
	ScreenPrint(0, 14, "早                                        早");
	ScreenPrint(0, 15, "早                                        早");
	ScreenPrint(0, 16, "早                                        早");
	ScreenPrint(0, 17, "早                                        早");
	ScreenPrint(0, 18, "早                                        早");
	ScreenPrint(0, 19, "早                                        早");
	ScreenPrint(0, 20, "早                                        早");
	ScreenPrint(0, 21, "早                                        早");
	ScreenPrint(0, 22, "早                                        早");
	ScreenPrint(0, 23, "曲收收收收收收收收收收收收收收收收收收收收旭");
}

void B_Draw::SuccessScreen()
{
	ScreenPrint(0, 0, "旨收收收收收收收收收收收收收收收收收收收收旬");
	ScreenPrint(0, 1, "早      *.                                早");
	ScreenPrint(0, 2, "早              .*            .*          早");
	ScreenPrint(0, 3, "早     *.                        .*       早");
	ScreenPrint(0, 4, "早       *.             .*                早");
	ScreenPrint(0, 5, "早           *.                           早");
	ScreenPrint(0, 6, "早            *.             .*           早");
	ScreenPrint(0, 7, "早     *.      *.旨旬旨旬.*渠    .*       早");
	ScreenPrint(0, 8, "早             旨朴朽曳朴旬欽             早");
	ScreenPrint(0, 9, "早     *.      早收朽曳收早п      .*     早");
	ScreenPrint(0, 10, "早             早收朽曳收早蹂~            早");
	ScreenPrint(0, 11, "早        *.   曲收旭曲收旭               早");
	ScreenPrint(0, 12, "早                                        早");
	ScreenPrint(0, 13, "早                          .*            早");
	ScreenPrint(0, 14, "早  *.           You Win!!          *.    早");
	ScreenPrint(0, 15, "早                                        早");
	ScreenPrint(0, 16, "早                                        早");
	ScreenPrint(0, 17, "早                       *.               早");
	ScreenPrint(0, 18, "早    *.         *.                       早");
	ScreenPrint(0, 19, "早                                 *.     早");
	ScreenPrint(0, 20, "早                      *.                早");
	ScreenPrint(0, 21, "早  *.                             *.     早");
	ScreenPrint(0, 22, "早                                        早");
	ScreenPrint(0, 23, "曲收收收收收收收收收收收收收收收收收收收收旭");
}

void B_Draw::FailureScreen()
{
	ScreenPrint(0, 0, "旨收收收收收收收收收收收收收收收收收收收收旬");
	ScreenPrint(0, 1, "早  ﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥  早");
	ScreenPrint(0, 2, "早  ﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥  早");
	ScreenPrint(0, 3, "早                                        早");
	ScreenPrint(0, 4, "早                                        早");
	ScreenPrint(0, 5, "早                                        早");
	ScreenPrint(0, 6, "早                                        早");
	ScreenPrint(0, 7, "早             *老考  老考*               早");
	ScreenPrint(0, 8, "早          *.  太太∩太太   .*           早");
	ScreenPrint(0, 9, "早   旨天天天天天天天天天天天天天天旬     早");
	ScreenPrint(0, 10, "早   早棻擠 廓 晦�虜� 檜辨п 輿撮蹂早     早");
	ScreenPrint(0, 11, "早   曲天天天天天天天天天天天天天天旭     早");
	ScreenPrint(0, 12, "早                                        早");
	ScreenPrint(0, 13, "早                                        早");
	ScreenPrint(0, 14, "早    (*÷÷*)                            早");
	ScreenPrint(0, 15, "早   旨O收收收O收收收收收收收收收收旬     早");
	ScreenPrint(0, 16, "早   早啗樓ж衛啊蝗棲梱? <y/n>     早     早");
	ScreenPrint(0, 17, "早   曲收收收收收收收收收收收收收收旭     早");
	ScreenPrint(0, 18, "早                                        早");
	ScreenPrint(0, 19, "早                                        早");
	ScreenPrint(0, 20, "早                                        早");
	ScreenPrint(0, 21, "早  ﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥  早");
	ScreenPrint(0, 22, "早  ﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥  早");
	ScreenPrint(0, 23, "曲收收收收收收收收收收收收收收收收收收收收旭");
}

void B_Draw::RunningScreen()
{
	ScreenPrint(0, 0, "旨收收收收收收收收收收收收收收收收收收收收旬");
	ScreenPrint(0, 1, "早                                        早");
	ScreenPrint(0, 2, "早                                        早");
	ScreenPrint(0, 3, "早                                        早");
	ScreenPrint(0, 4, "早                                        早");
	ScreenPrint(0, 5, "早                                        早");
	ScreenPrint(0, 6, "早                                        早");
	ScreenPrint(0, 7, "早                                        早");
	ScreenPrint(0, 8, "早                                        早");
	ScreenPrint(0, 9, "早                                        早");
	ScreenPrint(0, 10, "早                                        早");
	ScreenPrint(0, 11, "早                                        早");
	ScreenPrint(0, 12, "早                                        早");
	ScreenPrint(0, 13, "早                                        早");
	ScreenPrint(0, 14, "早                                        早");
	ScreenPrint(0, 15, "早                                        早");
	ScreenPrint(0, 16, "早                                        早");
	ScreenPrint(0, 17, "早                                        早");
	ScreenPrint(0, 18, "早                                        早");
	ScreenPrint(0, 19, "早                                        早");
	ScreenPrint(0, 20, "早                                        早");
	ScreenPrint(0, 21, "早                                        早");
	ScreenPrint(0, 22, "早                                        早");
	ScreenPrint(0, 23, "曲收收收收收收收收收收收收收收收收收收收收旭");
}

void B_Draw::ResultScreen()
{
	ScreenPrint(0, 0, "旨收收收收收收收收收收收收收收收收收收收收旬");
	ScreenPrint(0, 1, "早                                        早");
	ScreenPrint(0, 2, "早                                        早");
	ScreenPrint(0, 3, "早                                        早");
	ScreenPrint(0, 4, "早                                        早");
	ScreenPrint(0, 5, "早                                        早");
	ScreenPrint(0, 6, "早                                        早");
	ScreenPrint(0, 7, "早   (((    漁給 梟晦  啪歜 Score  ))))   早");
	ScreenPrint(0, 8, "早                                        早");
	ScreenPrint(0, 9, "早                                        早");
	ScreenPrint(0, 10, "早                                        早");
	ScreenPrint(0, 11, "早           識 薄熱  :                   早");
	ScreenPrint(0, 12, "早                                        早");
	ScreenPrint(0, 13, "早                                        早");
	ScreenPrint(0, 14, "早                                        早");
	ScreenPrint(0, 15, "早                                        早");
	ScreenPrint(0, 16, "早                                        早");
	ScreenPrint(0, 17, "早                                        早");
	ScreenPrint(0, 18, "早                                        早");
	ScreenPrint(0, 19, "早                                        早");
	ScreenPrint(0, 20, "早                                        早");
	ScreenPrint(0, 21, "早                                        早");
	ScreenPrint(0, 22, "早                                        早");
	ScreenPrint(0, 23, "曲收收收收收收收收收收收收收收收收收收收收旭");
}

void Block::SoundInit()
{
	//// 衛蝶蠱 螃粽薛お 儅撩婁 蟾晦��
	//FMOD_System_Create(&g_System);
	//FMOD_System_Init( g_System, 32, FMOD_INIT_NORMAL, NULL);

	//// 奩犒 餌遴萄
	//FMOD_System_CreateSound( g_System, "title.wav", FMOD_DEFAULT | FMOD_LOOP_NORMAL , 0, &g_Sound[0]);
	//FMOD_System_CreateSound( g_System, "run.wav",   FMOD_DEFAULT | FMOD_LOOP_NORMAL, 0, &g_Sound[1]);
	//FMOD_System_CreateSound( g_System, "fail.wav",  FMOD_DEFAULT | FMOD_LOOP_NORMAL, 0, &g_Sound[2]); // 瞳捱檜 檜啣擊 陽	

	//// �膩� 餌遴萄
	//FMOD_System_CreateSound( g_System, "stage.wav", FMOD_DEFAULT, 0, &g_Sound[3]); // 蝶纔檜雖 轎溘衛 
	//FMOD_System_CreateSound( g_System, "ball_bar_wall_collision.wav", FMOD_DEFAULT , 0, &g_Sound[4]); // 唳啗 艙羲婁 奢檜 睡詠�� 陽
	//FMOD_System_CreateSound( g_System, "block_collision.wav", FMOD_DEFAULT , 0, &g_Sound[5]); // 漁給婁 奢檜 睡�H�� 陽
	//FMOD_System_CreateSound( g_System, "fire.wav", FMOD_DEFAULT , 0, &g_Sound[6]); // 奢 嫦餌
	//FMOD_System_CreateSound( g_System, "success.wav", FMOD_DEFAULT , 0, &g_Sound[7]); // 奢 嫦餌
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
				return 1; // 偽擎 匙檜 氈戲賊
		}
	}
	return 0; // 偽擎 匙檜 橈戲賊 
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
			nX = rand() % 39 + 2; // 2 ~ 40 彰嬪 寰縑憮
			nY = rand() % 10 + 1; // 1 ~ 10 梱雖曖 彰嬪

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
	int i, nCount = 0; // 醱給 偃熱

					   // 奢婁 漁給曖 醱給
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

	// 醱給 羹觼 
	if (nCount != 0)
	{
		//FMOD_System_PlaySound( g_System, FMOD_CHANNEL_FREE, g_Sound[5], 0, &g_Channel[5]); // 奢婁 漁給 醱給
		return 1;
	}

	// 奢婁 虞渠晦 醱給
	for (i = 0; i < 3; i++)
	{
		if (nY == g_sBar.nY)
		{
			if ((nX >= g_sBar.nX[0] && nX <= (g_sBar.nX[2] + 1)) || ((nX + 1) >= g_sBar.nX[0] && (nX + 1) <= (g_sBar.nX[2] + 1)))
			{
				g_sBall.nDirect = g_BlockState[g_sBall.nDirect];
				//FMOD_System_PlaySound( g_System, FMOD_CHANNEL_FREE, g_Sound[4], 0, &g_Channel[4]); // READY 餌遴萄 轎溘
				return 1;
			}
		}
	}

	// Note: 嬪薹  
	if (nY < 1)
	{
		g_sBall.nDirect = g_StateTable[0][g_sBall.nDirect];
		return 1;
	}

	// Note: 螃艇薹
	if (nX > 39)
	{
		g_sBall.nDirect = g_StateTable[1][g_sBall.nDirect];
		return 1;
	}

	// Note: 奢曖 蟾晦�� 塽 儅貲 馬模
	if (nY > 22)
	{
		g_sBall.nHP--;

		if (g_sBall.nHP == 0)
		{	// 啪歜 っ薑戲煎 
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
	if (g_nStage2 == -1) // 1廓虜 蟾晦�降� 腎朝 睡碟縑 渠и 籀葬 餌о
	{
		SoundInit();
		g_nStage2 = 0;
		//FMOD_System_PlaySound( g_System, FMOD_CHANNEL_FREE, g_Sound[0], 0, &g_Channel[0] );
	}

	g_nGrade = 0;
	SetBlock(g_StageInfo2[g_nStage2].nBlockCount);

	// Note: 奢 蟾晦��
	g_sBall.nX = 19;
	g_sBall.nHP = 3;
	g_sBall.nY = 20;
	g_sBall.nDirect = TOP;
	g_sBall.OldTime = clock();
	g_sBall.nReady = 1;
	g_sBall.MoveTime = 50;

	// Note: 虞渠晦 蟾晦��
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
		if (CurTime - g_UpdateOldTime > 3000)  // 2蟾
		{
			g_nGameState2 = RUNNING2;
			g_GameStartTime2 = CurTime;

			//FMOD_System_PlaySound( g_System, FMOD_CHANNEL_FREE, g_Sound[1], 0, &g_Channel[1] ); // 啪歜 霞ч 餌遴萄
		}
		break;

	case RUNNING2:
		g_RemainTime2 = (g_StageInfo2[g_nStage2].LimitTime - (CurTime - g_GameStartTime)) / 1000; // 啪歜 霞ч 陴擎 衛除

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
		// 撩奢檜傍 褒ぬ蒂 っ欽п輿橫憮 轎溘擊 п輿朝 睡碟檜 諦撿 и棻.  
		if (g_nBlockCount == g_StageInfo2[g_nStage2].nBlockCount && g_sBall.nHP > 0 && g_RemainTime2 > 0)
		{
			g_UpdateOldTime2 = CurTime;
			g_nGameState2 = SUCCESS2;
			g_nTotalGrade2 += g_nBlockCount * 10;
			//FMOD_Channel_Stop( g_Channel[1] ); // 寡唳擠 醞雖
			//FMOD_System_PlaySound( g_System, FMOD_CHANNEL_FREE, g_Sound[7], 0, &g_Channel[7] ); // 嘐暮 撩奢 餌遴萄
		}
		else {
			g_nGameState2 = FAILED2;
			//FMOD_Channel_Stop( g_Channel[1] ); // 寡唳擠 醞雖
			//FMOD_System_PlaySound( g_System, FMOD_CHANNEL_FREE, g_Sound[2], 0, &g_Channel[2] ); // 嘐暮 褒ぬ 餌遴萄
		}
		break;
	case SUCCESS2:
		if (CurTime - g_UpdateOldTime2 > 3000)
		{
			g_UpdateOldTime2 = CurTime;
			++g_nStage;
			Init();
			g_nGameState2 = READY2;
			//FMOD_Channel_Stop( g_Channel[7] );  // 嘐暮 撩奢 餌遴萄 轎溘 醞雖					
			//FMOD_System_PlaySound( g_System, FMOD_CHANNEL_FREE, g_Sound[3], 0, &g_Channel[3]); // READY 餌遴萄 轎溘
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

		sprintf(string, "蝶纔檜雖 : %d", g_nStage2 + 1);
		ScreenPrint(45, 2, string);

		sprintf(string, "儅貲 : %d ", g_sBall.nHP);
		ScreenPrint(45, 4, string);

		sprintf(string, "薄熱 : %d ", g_nGrade2);
		ScreenPrint(45, 6, string);

		sprintf(string, "陴擎 衛除 : %d 碟 %d 蟾", g_RemainTime2 / 60, g_RemainTime2 % 60);
		ScreenPrint(45, 8, string);


		for (i = 0; i < g_StageInfo2[g_nStage2].nBlockCount; i++)
		{
			if (g_sBlock[i].nLife == 1)
				ScreenPrint(g_sBlock[i].nX, g_sBlock[i].nY, "﹥");
		}

		for (i = 0; i < 3; i++)
		{
			ScreenPrint(g_sBar.nX[i], g_sBar.nY, "〡");
		}

		ScreenPrint(g_sBall.nX, g_sBall.nY, "≒");
		break;
	case SUCCESS2:
		SuccessScreen();
		sprintf(string, "%d Stage", g_nStage2 + 1);
		ScreenPrint(19, 12, string);
		sprintf(string, "識薄: %d", g_nTotalGrade2);
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
	cout << "1廓)舒渦雖   2廓)綰楣梟晦" << endl;
	cin >> choice;

	if (choice == 1) {
		int nKey;

		ScreenInit();
		blank.Init();       // 蟾晦��

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
						//FMOD_Channel_Stop( g_Channel[0] ); // 寡唳擠 醞雖
						//FMOD_System_PlaySound( g_System, FMOD_CHANNEL_FREE, g_Sound[2], 0, &g_Channel[2]); // READY 餌遴萄 轎溘
						g_UpdateOldTime = clock();  // ready蒂 橾薑衛除 雖樓п 輿晦 嬪п 							
					}
					break;
				case '1':  // 蜂纂 酈 殮溘 1 ~ 9梱雖
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
						//FMOD_Channel_Stop( g_Channel[1] );  // 嘐暮 褒ぬ 餌遴萄 轎溘 醞雖 
						//FMOD_System_PlaySound( g_System, FMOD_CHANNEL_FREE, g_Sound[2], 0, &g_Channel[2]); // READY 餌遴萄 轎溘
						g_nGrade = 0;
						g_UpdateOldTime = clock();
					}
					break;
				case 'n':
				case 'N':
					if (g_nGameState == FAILED)
					{
						g_nGameState = RESULT;
						//FMOD_Channel_Stop( g_Channel[1] );  // 嘐暮 褒ぬ 餌遴萄 轎溘 醞雖							
					}
					break;
				}
			}

			blank.Update();    // 等檜攪 偵褐
			blank.Render();    // �飛� 轎溘
						 //FMOD_System_Update( g_System );
		}

		blank.Release();   // п薯
		ScreenRelease();
	}

	

//////////////////////////////////////////綰楣囀萄

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
						//FMOD_Channel_Stop( g_Channel[0] ); // 寡唳擠 醞雖
						//FMOD_System_PlaySound( g_System, FMOD_CHANNEL_FREE, g_Sound[3], 0, &g_Channel[3]); // 蝶纔檜雖 轎溘
						g_UpdateOldTime2 = clock();  // ready蒂 橾薑衛除 雖樓п 輿晦 嬪п 							
					}
					break;

				case 'k': //奢 嫦餌
					if (g_nGameState2 == RUNNING2 && g_sBall.nReady == 1)
					{
						g_sBall.nReady = 0;  // 檜翕 鼻鷓
						g_sBall.OldTime = clock();
						//FMOD_System_PlaySound( g_System, FMOD_CHANNEL_FREE, g_Sound[6], 0, &g_Channel[6]); // 奢 嫦餌
					}
					break;

				case 'j':
					if (g_nGameState2 == RUNNING2)
					{

						CurTime = clock();
						if (CurTime - g_sBar.OldTime > g_sBar.MoveTime)
						{
							g_sBar.OldTime = CurTime;
							if (g_sBar.nX[0] > 2) // 唳啗 艙羲 醱給 羹觼
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
							if (g_sBar.nX[2] < 40)  // 唳啗 艙羲 羹觼
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

				case 'i': // 奢 濩晦
						  //虞渠晦諦 奢 醱給
					if (g_nGameState2 == RUNNING2 && g_sBall.nReady == 0)
					{
						nX = g_sBall.nX;
						nY = g_sBall.nY;

						for (i = 0; i < 3; i++)
						{
							if (nY == (g_sBar.nY - 1)) // 奢婁 虞渠晦陛 蕾и 唳辦
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

				case '1': // 奢擊 濩懊擊 陽 1, 2, 3 寞щ 摹鷗陛棟	
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
						//FMOD_Channel_Stop( g_Channel[2] );  // 嘐暮 褒ぬ 餌遴萄 轎溘 醞雖 
						//FMOD_System_PlaySound( g_System, FMOD_CHANNEL_FREE, g_Sound[3], 0, &g_Channel[3]); // READY 餌遴萄 轎溘
						g_UpdateOldTime2 = clock();
					}
					break;
				case 'n':
				case 'N':
					if (g_nGameState2 == FAILED2)
					{
						g_nGameState2 = RESULT2;
						//FMOD_Channel_Stop( g_Channel[2] );  // 嘐暮 褒ぬ 餌遴萄 轎溘 醞雖							
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


