//======================================================================================
// 名前：GsmeMain.h
// 説明：ゲームメイン画面
//======================================================================================

#pragma once
#include "Stage.h"
#include "Select.h"
#include "Result.h"
#include "Bath_Stage.h"
#include "Table_Stage.h"
#include "Pause.h"
#include "Room_Stage.h"
#include "Tutorial.h"

class GameMain :
	public Scene
{
private:

	XMFLOAT3 camera = { 0.0f,0.0f,1.0f };			//カメラ座標
	Stage* mStage;									//ステージ
	Pause* mPause;									//ポーズ

	bool PauseState;								//ポーズ中か
	int StageID;									//ステージID

public:
	
	GameMain();			//コンストラクタ
	~GameMain();		//デストラクタ

	//更新
	void Update(void);
	//更新
	void Draw(void);

};

//======================================================================================
// 担当者：		菅眞心
// 制作日時：　 2022-12-01
// チーム名：	黒棺	
//======================================================================================

