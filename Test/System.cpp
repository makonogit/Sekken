//------------------------------------
//		include
//------------------------------------
#include "System.h"

DWORD gDeltaTime;		//デルタタイム

//<><><><><><><><><><><><><><><><><><>
// 関数名：SystemInit
// 役割：システムの初期化
//<><><><><><><><><><><><><><><><><><>
void System_Init(void)
{
	//乱数の初期化
	srand((unsigned int)time(NULL));

}

void System_Update(void)
{
	// デルタタイムの計測
	static DWORD lastTime = timeGetTime(); // 前回計測時の時間
	timeBeginPeriod(1); // 精度を１ミリ秒に上げる
	DWORD nowTime = timeGetTime(); // 現在の時間
	timeEndPeriod(1);						// 精度を元に戻す
	gDeltaTime = nowTime - lastTime;		// 差分がデルタタイム
	lastTime = nowTime;						// 前回計測時間として保存

	//デルタタイムが想定外の値になった場合の処理
	if (gDeltaTime >= 100)
	{
		gDeltaTime = 0;
	}
}

void GameSound_Init(void)
{
	Sound_Init(SOUND_LABEL_SE002);
	Sound_Init(SOUND_LABEL_SE003);
	Sound_Init(SOUND_LABEL_SE004);
	Sound_Init(SOUND_LABEL_SE005);
	Sound_Init(SOUND_LABEL_SE006);
	Sound_Init(SOUND_LABEL_SE007);
	Sound_Init(SOUND_LABEL_SE008);
	Sound_Init(SOUND_LABEL_SE009);
	Sound_Init(SOUND_LABEL_SE010);
	Sound_Init(SOUND_LABEL_SE011);
	Sound_Init(SOUND_LABEL_SE012);
	Sound_Init(SOUND_LABEL_SE013);
	Sound_Init(SOUND_LABEL_SE014);
	Sound_Init(SOUND_LABEL_SE015);
	Sound_Init(SOUND_LABEL_SE016);
	Sound_Init(SOUND_LABEL_SE017);
	Sound_Init(SOUND_LABEL_SE018);
	Sound_Init(SOUND_LABEL_SE019);
	Sound_Init(SOUND_LABEL_SE020);
	Sound_Init(SOUND_LABEL_SE021);
	Sound_Init(SOUND_LABEL_SE022);
	Sound_Init(SOUND_LABEL_SE023);
	Sound_Init(SOUND_LABEL_SE024);
	Sound_Init(SOUND_LABEL_SE034);
	Sound_Init(SOUND_LABEL_SE035);

}

void GameSound_Uninit(void)
{
	Sound_Uninit(SOUND_LABEL_SE002);
	Sound_Uninit(SOUND_LABEL_SE003);
	Sound_Uninit(SOUND_LABEL_SE004);
	Sound_Uninit(SOUND_LABEL_SE005);
	Sound_Uninit(SOUND_LABEL_SE006);
	Sound_Uninit(SOUND_LABEL_SE007);
	Sound_Uninit(SOUND_LABEL_SE008);
	Sound_Uninit(SOUND_LABEL_SE009);
	Sound_Uninit(SOUND_LABEL_SE010);
	Sound_Uninit(SOUND_LABEL_SE011);
	Sound_Uninit(SOUND_LABEL_SE012);
	Sound_Uninit(SOUND_LABEL_SE013);
	Sound_Uninit(SOUND_LABEL_SE014);
	Sound_Uninit(SOUND_LABEL_SE015);
	Sound_Uninit(SOUND_LABEL_SE016);
	Sound_Uninit(SOUND_LABEL_SE017);
	Sound_Uninit(SOUND_LABEL_SE018);
	Sound_Uninit(SOUND_LABEL_SE019);
	Sound_Uninit(SOUND_LABEL_SE020);
	Sound_Uninit(SOUND_LABEL_SE021);
	Sound_Uninit(SOUND_LABEL_SE022);
	Sound_Uninit(SOUND_LABEL_SE023);
	Sound_Uninit(SOUND_LABEL_SE024);
	Sound_Uninit(SOUND_LABEL_SE034);
	Sound_Uninit(SOUND_LABEL_SE035);
}
