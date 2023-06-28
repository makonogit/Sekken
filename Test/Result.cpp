#include "Result.h"

extern DWORD gDeltaTime;
int Result::nScore = 0;

//<><><><><><><><><><><><><><><><><><>
// 関数名：コンストラクタ
// 役割：初期化
//<><><><><><><><><><><><><><><><><><>
Result::Result()
{
	//背景テクスチャのロード
	LoadTexture(L"assets/images/BackGround/ResultBackGround.png", &mBgTex);			//背景	
	LoadTexture(L"assets/images/UI/ReplayUI.png", &mReplayUITex);			//リプレイ
	LoadTexture(L"assets/images/UI/RastUI.png", &mReturnUITex);				//ステージ選択にもどる
	LoadTexture(L"assets/images/UI/RankC.png", &mScoreUITex[0]);			//スコア(C)
	LoadTexture(L"assets/images/UI/RankB.png", &mScoreUITex[1]);			//スコア(B)
	LoadTexture(L"assets/images/UI/RankA.png", &mScoreUITex[2]);			//スコア(A)
	LoadTexture(L"assets/images/UI/RankS.png", &mScoreUITex[3]);			//スコア(S)

	LoadTexture(L"assets/images/UI/CleanBarFlame.png", &mScoreGageFreamTex);	//スコアゲージ枠
	LoadTexture(L"assets/images/UI/CleanBarB.png", &mScoreGageBackTex);			//スコアゲージ背景
	LoadTexture(L"assets/images/UI/CleanBar.png", &mScoreGageTex);				//スコアゲージ
	LoadTexture(L"assets/images/UI/Cracker1.png", &mCrackerTex);				//クラッカー
	LoadTexture(L"assets/images/UI/Cracker2.png", &mCracker_PaperTex);			//クラッカーの紙

	//背景
	mBg = new StaticObject(camera);
	mBg->mSprite->SetTexture(mBgTex);
	mBg->SetSize(2.8f, 2.0f);

	//リプレイ
	mReplayUI = new StaticObject(camera);
	mReplayUI->mSprite->SetTexture(mReplayUITex);
	mReplayUI->SetSize(2.8f, 2.0f);
	
	//ステージ選択
	mReturnUI = new StaticObject(camera);
	mReturnUI->mSprite->SetTexture(mReturnUITex);
	mReturnUI->SetSize(2.8f, 2.0f);
	
	//UI選択中のサイズ
	SelectSize.x = 3.0f;
	SelectSize.y = 2.2f;

	mScoreUI = new StaticObject(camera);
	mScoreUI->mSprite->SetTexture(mScoreUITex[0]);
	mScoreUI->SetSize(2.8f, 2.0f);
	mScoreUI->SetActive(false);
	
	//スコアゲージの枠
	mScoreGageFream = new StaticObject(camera);
	mScoreGageFream->mSprite->SetTexture(mScoreGageFreamTex);
	mScoreGageFream->SetSize(GAGEMAX, 0.2f);
	mScoreGageFream->SetPosition(-0.4f, 0.5f);

	//スコアゲージの背景
	mScoreGageBack = new StaticObject(camera);
	mScoreGageBack->mSprite->SetTexture(mScoreGageBackTex);
	mScoreGageBack->SetSize(GAGEMAX, 0.2f);
	mScoreGageBack->SetPosition(-0.4f, 0.5f);

	//スコアゲージ
	mScoreGage = new StaticObject(camera);
	mScoreGage->mSprite->SetTexture(mScoreGageTex);
	mScoreGage->SetSize(0.0f, 0.2f);
	mScoreGage->SetPosition(-0.4f, 0.5f);

	//クラッカー
	mCracker_Left = new StaticObject(camera);
	mCracker_Left->mSprite->SetTexture(mCrackerTex);
	mCracker_Left->SetSize(0.6f, 0.6f);
	mCracker_Left->SetPosition(-1.15f, -1.5f);
	//mCracker->SetActive(false);

	mCracker_Right = new StaticObject(camera);
	mCracker_Right->mSprite->SetTexture(mCrackerTex);
	mCracker_Right->SetSize(0.6f, 0.6f);
	//左右反転させる
	fRevers = mCracker_Right->mSprite->mUV.w;
	mCracker_Right->mSprite->mUV.w = mCracker_Right->mSprite->mUV.x;
	mCracker_Right->mSprite->mUV.x = fRevers;

	mCracker_Right->SetPosition(1.15f, -1.5f);

	//クラッカーの紙
	mCracker_Paper_Left = new StaticObject(camera);
	mCracker_Paper_Left->mSprite->SetTexture(mCracker_PaperTex);
	mCracker_Paper_Left->SetSize(1.0f, 1.0f);
	mCracker_Paper_Left->SetPosition(-0.8f, -0.45f);
	
	mCracker_Paper_Left->SetActive(false);

	mCracker_Paper_Right = new StaticObject(camera);
	mCracker_Paper_Right->mSprite->SetTexture(mCracker_PaperTex);
	mCracker_Paper_Right->SetSize(1.0f, 1.0f);
	//左右反転させる
	fRevers = mCracker_Paper_Right->mSprite->mUV.w;
	mCracker_Paper_Right->mSprite->mUV.w = mCracker_Paper_Right->mSprite->mUV.x;
	mCracker_Paper_Right->mSprite->mUV.x = fRevers;
	mCracker_Paper_Right->SetPosition(0.8f, -0.45f);
	
	mCracker_Paper_Right->SetActive(false);

	//スコアが予想外の数字の場合
	if (nScore > 100 || nScore <= 0) {
		nScore = 10;
	}

	fWeight = 0.0f;	//重力加速

	Sound_Init(SOUND_LABEL_BGM001);
	Sound_Init(SOUND_LABEL_SE025);
	Sound_Init(SOUND_LABEL_SE026);
	Sound_Init(SOUND_LABEL_SE027);
	Sound_Init(SOUND_LABEL_SE028);
	Sound_Init(SOUND_LABEL_SE029);
	Sound_Init(SOUND_LABEL_SE030);
	Sound_Init(SOUND_LABEL_SE031);

	SetVolume(SOUND_LABEL_SE025,0.8);

	Play(SOUND_LABEL_BGM001);
	SetVolume(SOUND_LABEL_BGM001, 0.5);
	mSETime = 0.0f;
	Input_SetVibration(0, 0);
}


//<><><><><><><><><><><><><><><><><><>
// 関数名：デストラクタ
// 役割：初期化
//<><><><><><><><><><><><><><><><><><>
Result::~Result()
{
	Sound_Uninit(SOUND_LABEL_BGM001);
	Sound_Uninit(SOUND_LABEL_SE025);
	Sound_Uninit(SOUND_LABEL_SE026);
	Sound_Uninit(SOUND_LABEL_SE027);
	Sound_Uninit(SOUND_LABEL_SE028);
	Sound_Uninit(SOUND_LABEL_SE029);
	Sound_Uninit(SOUND_LABEL_SE030);
	Sound_Uninit(SOUND_LABEL_SE031);

	delete mBg;
	delete mReplayUI;
	delete mReturnUI;
	delete mScoreUI;
	delete mScoreGage;
	delete mScoreGageBack;
	delete mScoreGageFream;
	delete mCracker_Left;
	delete mCracker_Right;
	delete mCracker_Paper_Left;
	delete mCracker_Paper_Right;

	COM_SAFE_RELEASE(mBgTex);
	COM_SAFE_RELEASE(mReplayUITex);
	COM_SAFE_RELEASE(mReturnUITex);
	COM_SAFE_RELEASE(mScoreGageFreamTex);
	COM_SAFE_RELEASE(mScoreGageBackTex);
	COM_SAFE_RELEASE(mScoreGageTex);
	COM_SAFE_RELEASE(mCrackerTex);
	COM_SAFE_RELEASE(mCracker_PaperTex);
	
	for (int i = 0; i < 4; i++) {
		COM_SAFE_RELEASE(mScoreUITex[i]);
	}
}

//<><><><><><><><><><><><><><><><><><>
// 関数名：Update
// 役割：更新
//<><><><><><><><><><><><><><><><><><>
void Result::Update()
{
	mBg->Update();			//背景

	mReplayUI->Update();	//リプレイ
	mReturnUI->Update();	//ステージ選択

	mScoreUI->Update();		//スコア
	
	mScoreGage->Update();			//スコアゲージ
	mScoreGageBack->Update();		//スコアゲージの背景
	mScoreGageFream->Update();		//スコアゲージ枠
	
	mCracker_Left->Update();		//クラッカー
	mCracker_Right->Update();
	
	mCracker_Paper_Left->Update();	//クラッカーの紙
	mCracker_Paper_Right->Update();

	if (Fade_Dogrun::mState == FADE_IN_END || Fade_Dogrun::mState == NONE_FADE) {
		if (GetSoundState(SOUND_LABEL_SE030) == false && GageState)
		{
			Play(SOUND_LABEL_SE030);
		}
		GageState = ScoreGageAnim();
	}
	
	//ゲージのアニメーションが終わったら
	if (!GageState) {
		mScoreUI->SetActive(true);
		mSETime += gDeltaTime;
		if (GetSoundState(SOUND_LABEL_SE031) == false && mSound == false)
		{
			Stop(SOUND_LABEL_SE030);
			Play(SOUND_LABEL_SE031);
		}
		bool CrackerSE = false;
		//スコアランクを決める
		if (nScore <= 25) {
			ScoreLank = 0;
			if (GetSoundState(SOUND_LABEL_SE027) == false && mSound == false && mSETime > 0.5f * 1000.0f)
			{
				Play(SOUND_LABEL_SE027);
				mSound = true;
			}
		}
		else if (nScore <= 50) {
			ScoreLank = 1;
			if (GetSoundState(SOUND_LABEL_SE026) == false && mSound == false && mSETime > 0.5f * 1000.0f)
			{
				Play(SOUND_LABEL_SE026);
				mSound = true;

			}
		}
		else if (nScore <= 75) {
			ScoreLank = 2;
			if (GetSoundState(SOUND_LABEL_SE025) == false && mSound == false && mSETime > 0.5f * 1000.0f)
			{
				Play(SOUND_LABEL_SE025);
				mSound = true;
			}
		}
		else {
			ScoreLank = 3;
			if (GetSoundState(SOUND_LABEL_SE028) == false && mSound == false && mSETime > 0.5f * 1000.0f)
			{
				Play(SOUND_LABEL_SE028);
				mSound = true;
				CrackerSE = true;
			}
		}

		if (ScoreLank == 3) {	//Sランクの時だけ
			Cracker_Anim();	//クラッカー
			if (GetSoundState(SOUND_LABEL_SE029) == false && CrackerSE == true && mSETime > 0.5f * 1000.0f)
			{
				Play(SOUND_LABEL_SE029);
				SetVolume(SOUND_LABEL_SE029, 2.5);
				mSound = true;
			}
		}
		mScoreUI->mSprite->SetTexture(mScoreUITex[ScoreLank]);
		SceneSelect();

	}
	
}


//<><><><><><><><><><><><><><><><><><>
// 関数名：Draw
// 役割：描画
//<><><><><><><><><><><><><><><><><><>
void Result::Draw()
{
	mBg->Draw();	//背景
	
	mReplayUI->Draw();	//リプレイ
	mReturnUI->Draw();	//ステージ選択

	mScoreUI->Draw();	//スコア

	mScoreGageBack->Draw();		//スコアゲージの背景
	mScoreGage->Draw();			//スコアゲージ
	mScoreGageFream->Draw();	//スコアゲージ枠

	mCracker_Left->Draw();		//クラッカー
	mCracker_Right->Draw();

	mCracker_Paper_Left->Draw();	//クラッカーの紙
	mCracker_Paper_Right->Draw();
}

//<><><><><><><><><><><><><><><><><><>
// 関数名：SceneSelect
// 役割：シーン選択
//<><><><><><><><><><><><><><><><><><>
void Result::SceneSelect()
{
	//シーン番号の変更
	if (Input_GetButtonTrigger(DOWN) || Input_GetKeyTrigger('S')) {
		nSceneNum--;
	}
	if (Input_GetButtonTrigger(UP) || Input_GetKeyTrigger('W')) {
		nSceneNum++;
	}

	if (nSceneNum < 0) {
		nSceneNum = 1;
	}
	if (nSceneNum > 1) {
		nSceneNum = 0;
	}
	
	if (nSceneNum == 0) 
	{
		mReplayUI->mSprite->mColor.r = 1.0f;
		mReplayUI->mSprite->mColor.g = 1.0f;
		mReplayUI->mSprite->mColor.b = 1.0f;
		mReturnUI->mSprite->mColor.r = 0.5f;
		mReturnUI->mSprite->mColor.g = 0.5f;
		mReturnUI->mSprite->mColor.b = 0.5f;

		if (Fade_Bubble::mState == FADE_OUT_END) {
			//Stop(SOUND_LABEL_BGM001);
			SceneManager::SceneChange(GAME_MAIN, BUBBLE_FADE);
		}
	}
	else 
	{
		mReplayUI->mSprite->mColor.r = 0.5f;
		mReplayUI->mSprite->mColor.g = 0.5f;
		mReplayUI->mSprite->mColor.b = 0.5f;
		mReturnUI->mSprite->mColor.r = 1.0f;
		mReturnUI->mSprite->mColor.g = 1.0f;
		mReturnUI->mSprite->mColor.b = 1.0f;

		if (Fade_Bubble::mState == FADE_OUT_END) {
			//Stop(SOUND_LABEL_BGM001);
			SceneManager::SceneChange(SELECT, BUBBLE_FADE);
		}
	}

	if (Input_GetButtonTrigger(B) || Input_GetKeyTrigger(VK_SPACE)) {
		Stop(SOUND_LABEL_BGM001);
		Fade_Bubble::FadeOut();
	}


}

//<><><><><><><><><><><><><><><><><><>
// 関数名：ScoreGaageAnim
// 役割：スコアゲージのアニメーション
// 引数：なし
// 戻り値：true:アニメーション中　false:終了
//<><><><><><><><><><><><><><><><><><>
bool Result::ScoreGageAnim()
{
	//ゲージの最大数(スコアに比例させる)
	float GageMaxSize = (GAGEMAX / 100.0f) * (float)nScore;
	
	float GageAddSpeed = 0.0003f;	//ゲージの加算スピード

	//最大サイズまで大きくする
	if (mScoreGage->mSprite->mSize.x <= GageMaxSize) {
		mScoreGage->mSprite->mSize.x += GageAddSpeed * gDeltaTime;
	}
	else {
		return false;
	}

	//ゲージの位置を更新する(なんかちょっとずれてる...)
	mScoreGage->mSprite->mCenter.x = -0.401f - ((GAGEMAX - mScoreGage->mSprite->mSize.x) / 2.0f);

	return true;
}

//<><><><><><><><><><><><><><><><><><>
// 関数名：Cracker_Anim
// 役割：クラッカーのアニメーション
//<><><><><><><><><><><><><><><><><><>
void Result::Cracker_Anim()
{
	float MoveSpeed = 0.002f;	//クラッカーの移動速度

	//左のクラッカー
	if (mCracker_Left->mSprite->mCenter.x <= -0.9f)
	{
		mCracker_Left->mSprite->mCenter.x += MoveSpeed * gDeltaTime;
	}
	if (mCracker_Left->mSprite->mCenter.y <= -0.65f)
	{
		mCracker_Left->mSprite->mCenter.y += MoveSpeed * gDeltaTime;
	}

	//クラッカーの移動が終わったら紙を表示
	if (mCracker_Left->mSprite->mCenter.x >= -0.9f && mCracker_Left->mSprite->mCenter.y >= -0.65f) 
	{
		mCracker_Paper_Left->SetActive(true);

		fWeight += 0.00001f * gDeltaTime;
		//位置を更新
		mCracker_Paper_Left->mSprite->mCenter.x += 0.002f * gDeltaTime;
		mCracker_Paper_Left->mSprite->mCenter.y += (0.005f - fWeight) * gDeltaTime;

	}

	//右のクラッカー
	if (mCracker_Right->mSprite->mCenter.x >= 0.9f)
	{
		mCracker_Right->mSprite->mCenter.x -= MoveSpeed * gDeltaTime;
	}
	if (mCracker_Right->mSprite->mCenter.y <= -0.65f)
	{
		mCracker_Right->mSprite->mCenter.y += MoveSpeed * gDeltaTime;
	}

	//クラッカーの移動が終わったら紙を表示
	if (mCracker_Right->mSprite->mCenter.x >= -0.9f && mCracker_Right->mSprite->mCenter.y >= -0.65f)
	{
		mCracker_Paper_Right->SetActive(true);

		//位置を更新
		mCracker_Paper_Right->mSprite->mCenter.x -= 0.002f * gDeltaTime;
		mCracker_Paper_Right->mSprite->mCenter.y += (0.005f - fWeight) * gDeltaTime;

	}



}


//<><><><><><><><><><><><><><><><><><>
// 関数名：GetScore
// 役割：スコアの受け取り
// 引数：スコア
// 戻り値：なし
//<><><><><><><><><><><><><><><><><><>
void Result::GetScore(int Score)
{
	nScore = Score;
}
