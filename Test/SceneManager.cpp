//======================================================================================
//		SceneManagerクラス
//======================================================================================

//------------------------------------
//		include
//------------------------------------
#include "SceneManager.h"
#include "Title.h"
#include "GameMain.h"
#include "Select.h"
#include "Result.h"

//シーンを空にしておく
Scene* SceneManager::mScene = NULL;
Fade* SceneManager::mFade[] = {NULL,NULL,NULL};

//------------------------------------
//		メンバー関数
//------------------------------------


//<><><><><><><><><><><><><><><><><><>
// 関数名：Init
// 役割：更新
//<><><><><><><><><><><><><><><><><><>
void SceneManager::Init(void)
{
	mScene = new Title();
	mFade[0] = new Fade();
	mFade[1] = new Fade_Bubble();
	mFade[2] = new Fade_Dogrun();
}

//<><><><><><><><><><><><><><><><><><>
// 関数名：UnInit
// 役割：更新
//<><><><><><><><><><><><><><><><><><>
void SceneManager::Uninit(void)
{
	for (int i = 0; i < 3; i++) {
		delete mFade[i];
	}
}


//<><><><><><><><><><><><><><><><><><>
// 関数名：シーンチェンジ関数
// 役割：シーンの変更
// 引数：シーンID
// 戻り値：なし
//<><><><><><><><><><><><><><><><><><>
void SceneManager::SceneChange(SceneStateID scene,Fade_Type Fade_Name)
{
	
	if (mScene != NULL) {
		delete mScene;
	}

	//フェードイン
	switch (Fade_Name)
	{
	case NOMAL_FADE:
		Fade::FadeIn();
		break;
	case BUBBLE_FADE:
		Fade_Bubble::FadeIn();
		break;
	case DOGRUN_FADE:
		Fade_Dogrun::FadeIn();
		break;
	default:
		break;
	}
	
	//ポリモーフィズムでシーンを生成する
	switch (scene)
	{
	case NONE_SCENE:		//どこのシーンでもなければDeleteする
		mScene = NULL;
		break;
	case TITLE:
		mScene = new Title;
		break;
	case SELECT:
		mScene = new Select;
		break;
	case GAME_MAIN:
		mScene = new GameMain;
		break;
	case POSE:
		break;
	case RESULT:
		mScene = new Result;
		break;
	default:
		break;
	}

}

//<><><><><><><><><><><><><><><><><><>
// 関数名：Update
// 役割：更新
//<><><><><><><><><><><><><><><><><><>
int SceneManager::Update(void)
{
	if (mScene != NULL) {
		mScene->Update();
		for (int i = 0; i < 3; i++) {
			mFade[i]->Update();
		}
	}
	else {
		return -1;
	}

	return 0;
}


//<><><><><><><><><><><><><><><><><><>
// 関数名：Draw
// 役割：描画
//<><><><><><><><><><><><><><><><><><>
void SceneManager::Draw(void)
{
	// DIRECT3D構造体にアクセスする
	DIRECT3D* d3d = Direct3D_Get();
	// 画面の塗りつぶし処理
	float color[4] = { 0.0f, 0.0f, 0.0f, 1.0f };  // rgba  0.0f-1.0f
	d3d->context->ClearRenderTargetView(d3d->renderTarget,
		color);
	
	if (mScene != NULL) {
		mScene->Draw();
		for (int i = 0; i < 3; i++) {
			mFade[i]->Draw();
		}
	}

	// ダブルバッファの切り替え
	d3d->swapChain->Present(0, 0);

}


//======================================================================================
// 担当者：		菅眞心
// チーム名：	黒棺
//======================================================================================