#include "Pause.h"


//<><><><><><><><><><><><><><><><><><>
// 関数名：Pause
// 役割：コンストラクタ
//<><><><><><><><><><><><><><><><><><>
Pause::Pause()
{
	LoadTexture(L"assets/Test.png", &mBackTex);
	LoadTexture(L"assets/images/UI/Continue.png",   &mUIContinueTex);
	LoadTexture(L"assets/images/UI/Restart.png",    &mUIRestartTex);
	LoadTexture(L"assets/images/UI/Back_Title.png", &mUITitleBackTex);
	camera = { 0.0f,0.0f,1.0f };		//カメラ
	
	//背景
	mBack = new StaticObject(camera);
	mBack->mSprite->SetTexture(mBackTex);
	mBack->SetSize(2.8f, 2.0f);
	color = { 0.0f,0.0f,0.0f,0.5f };	//半透明にする
	mBack->mSprite->SetColor(color);
	
	Normal = { 1.0f,1.0f,1.0f,1.0f };
	Black = { 0.5f,0.5f,0.5f,1.0f };
	Blue = { 0.0f,0.0f,1.0f,1.0f };

	//UI
	mReturnUI = new StaticObject(camera);
	mReturnUI->mSprite->SetTexture(mUIContinueTex);
	mReturnUI->SetSize(0.6f, 0.3f);
	mReturnUI->SetPosition(0.0f, 0.2f);

	mReplayUI = new StaticObject(camera);
	mReplayUI->mSprite->SetTexture(mUIRestartTex);
	mReplayUI->SetSize(0.6f, 0.3f);
	mReplayUI->SetPosition(0.0f, -0.3f);

	mTitleUI = new StaticObject(camera);
	mTitleUI->mSprite->SetTexture(mUITitleBackTex);
	mTitleUI->SetSize(0.8f, 0.3f);
	mTitleUI->SetPosition(0.0f, -0.8f);

	SelectID = RETURN;
}


//<><><><><><><><><><><><><><><><><><>
// 関数名：~Pause
// 役割：デストラクタ
//<><><><><><><><><><><><><><><><><><>
Pause::~Pause()
{

	delete mTitleUI;
	delete mReplayUI;
	delete mReturnUI;
	delete mBack;
	COM_SAFE_RELEASE(mBackTex);
	COM_SAFE_RELEASE(mUIContinueTex);
	COM_SAFE_RELEASE(mUIRestartTex);
	COM_SAFE_RELEASE(mUITitleBackTex);
}

//<><><><><><><><><><><><><><><><><><>
// 関数名：Update
// 役割：更新
//<><><><><><><><><><><><><><><><><><>
void Pause::Update()
{
	mBack->Update();
	mReturnUI->Update();
	mReplayUI->Update();
	mTitleUI->Update();

	if (Input_GetButtonTrigger(DOWN) || Input_GetKeyTrigger('S')) {
		SelectID++;	//選択IDを加算
	}
	if (Input_GetButtonTrigger(UP) || Input_GetKeyTrigger('W')) {
		SelectID--;	//選択IDを減算
	}


	if (SelectID > 2) {
		SelectID = 0;	//1番下までいったら上に戻す
	}
	if (SelectID < 0) {
		SelectID = 2;	//1番上までいったら下に戻す
	}


	//SelectIDによって描画を変更（ここはあとで書き換える）
	switch (SelectID)
	{
	case RETURN:
		mReturnUI->mSprite->SetColor(Normal);
		mReplayUI->mSprite->SetColor(Black);
		mTitleUI->mSprite->SetColor(Black);
		break;
	case REPLAY:
		mReplayUI->mSprite->SetColor(Normal);
		mReturnUI->mSprite->SetColor(Black);
		mTitleUI->mSprite->SetColor(Black);
		break;
	case TITLE_BACK:
		mTitleUI->mSprite->SetColor(Normal);
		mReturnUI->mSprite->SetColor(Black);
		mReplayUI->mSprite->SetColor(Black);
		break;
	default:
		break;
	}

}


//<><><><><><><><><><><><><><><><><><>
// 関数名：Draw
// 役割：描画
//<><><><><><><><><><><><><><><><><><>
void Pause::Draw()
{
	mBack->Draw();
	mReturnUI->Draw();
	mReplayUI->Draw();
	mTitleUI->Draw();

}

//<><><><><><><><><><><><><><><><><><>
// 関数名：SceneSelect
// 役割：シーン選択
//<><><><><><><><><><><><><><><><><><>
int Pause::SceneSelect()
{
	if (Input_GetButtonTrigger(B) || Input_GetKeyTrigger(VK_SPACE)) {
		return SelectID;
	}
	else {
		return - 1;
	}

}

