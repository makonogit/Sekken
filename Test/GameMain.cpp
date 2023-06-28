//------------------------------------
//		include
//------------------------------------
#include "GameMain.h"

//<><><><><><><><><><><><><><><><><><>
// 関数名：GameMain
// 役割：コンストラクタ
//<><><><><><><><><><><><><><><><><><>
GameMain::GameMain()
{

	PauseState = false;	//ポーズ中ではない
	
	StageID = Select::GetStageID();		//ステージIDの受け取り

	//ステージのインスタンス生成
	switch (StageID)
	{
	case BATH_STAGE:
		mStage = new Bath_Stage;
		break;
	case TABLE_STAGE:
		mStage = new Table_Stage;
		break;
	case ROOM_STAGE:
		mStage = new Room_Stage;
		break;
	case TUTORIAL_STAGE:
		mStage = new Tutorial;
		break;
	default:
		break;
	}

}

//<><><><><><><><><><><><><><><><><><>
// 関数名：~GameMain
// 役割：デストラクタ
//<><><><><><><><><><><><><><><><><><>
GameMain::~GameMain()
{
	delete mStage;
}

//<><><><><><><><><><><><><><><><><><>
// 関数名：Update
// 役割：更新
// 引数：なし
// 戻り値：なし
//<><><><><><><><><><><><><><><><><><>
void GameMain::Update(void)
{
	//スタートボタンでポーズ
	if (Input_GetButtonTrigger(START) || Input_GetKeyTrigger(VK_ESCAPE)) {
		if (PauseState) {
			PauseState = false;
			delete mPause;
			Resume(mStage->mBGMSound);
			Resume(SOUND_LABEL_SE013);
			Resume(SOUND_LABEL_SE019);
			Resume(SOUND_LABEL_SE023);
		}
		else {
			PauseState = true;
			mPause = new Pause();
			Stop(mStage->mBGMSound);
			Stop(SOUND_LABEL_SE013);
			Stop(SOUND_LABEL_SE019);
			Stop(SOUND_LABEL_SE021);
			Stop(SOUND_LABEL_SE023);
			Input_SetVibration(0, 0);	//振動を止める
		}
		
	}
	
	//ポーズ中ならポーズ以外の更新は呼ばない
	if (PauseState) {
		
		mPause->Update();

		switch (mPause->SceneSelect()) {
		case 0:
			PauseState = false;
			Resume(mStage->mBGMSound);
			break;
		case 1:
			PauseState = false;
			SceneManager::SceneChange(GAME_MAIN,NONE_TYPE);
			break;
		case 2:
			PauseState = false;
			SceneManager::SceneChange(TITLE,NONE_TYPE);	//タイトルへ移動、フェードしない
			break;
		default:
			break;
		}
	}
	else if(mStage->TimeActive){
		mStage->Update();
	}
	else {
		Result::GetScore(mStage->Score);
		Stop(mStage->mBGMSound);
		Fade_Dogrun::FadeOut();
		if (Fade_Dogrun::mState == FADE_OUT_END) {
			SceneManager::SceneChange(RESULT, DOGRUN_FADE);
		}
	}

}


//<><><><><><><><><><><><><><><><><><>
// 関数名：Draw
// 役割：描画
// 引数：なし
// 戻り値：なし
//<><><><><><><><><><><><><><><><><><>
void GameMain::Draw(void)
{
	
	mStage->Draw();
	
	if (PauseState) {
		mPause->Draw();
	}
}

//======================================================================================
// 担当者：		菅眞心
// 制作日時：　 2022-12-01
// チーム名：	黒棺	
//======================================================================================