//------------------------------------
//		include
//------------------------------------
#include "Select.h"

extern DWORD gDeltaTime;
int Select::SelectStageID = ROOM_STAGE;	//最初は部屋に設定
int Select::mInput = 0;

bool Stage_Info_Flg = true;		//最初どこを選んでるか

//<><><><><><><><><><><><><><><><><><>
// 関数名：Select
// 役割：コンストラクタ
//<><><><><><><><><><><><><><><><><><>
Select::Select()
{
	//背景
	LoadTexture(L"assets/images/BackGround/SelectBG.png", &mBgTex);
	
	mBg = new StaticObject(camera);
	mBg->mSprite->SetTexture(mBgTex);
	mBg->SetSize(2.8f, 2.0f);

	//----------------------------------
	//ステージオブジェクト
	//----------------------------------
	LoadTexture(L"assets/images/UI/TableMiniature.png", &mTableObjTex);
	LoadTexture(L"assets/images/UI/BathRoomMiniature.png", &mBathObjTex);
	LoadTexture(L"assets/images/UI/EntranceMiniature.png", &mRoomObjTex);

	for (int i = 0; i < MAXSTAGE; i++) {
		mObject[i] = new StaticObject(camera);
	}

	//テクスチャ指定
	mObject[BATH_STAGE]->mSprite->SetTexture(mBathObjTex);
	mObject[TABLE_STAGE]->mSprite->SetTexture(mTableObjTex);
	mObject[ROOM_STAGE]->mSprite->SetTexture(mRoomObjTex);

	//--------座標指定------------
	//(前)
	mObject[ROOM_STAGE]->SetPosition(0.0f, 0.0f);
	mObject[ROOM_STAGE]->SetSize(0.9f, 1.0f);
	
	//(左)
	mObject[TABLE_STAGE]->SetPosition(-1.0f, 0.0f);
	mObject[TABLE_STAGE]->SetSize(0.4f, 0.5f);
	
	//(右)
	mObject[BATH_STAGE]->SetSize(0.4f, 0.5f);
	mObject[BATH_STAGE]->SetPosition(1.0f, 0.0f);
	
	Rota = NONE_ROTA;
	
	StageID[0] = 1;
	StageID[1] = 0;
	StageID[2] = 2;
	//-------------------------
	//UI
	//-------------------------
	LoadTexture(L"assets/images/UI/Start.png", &mStartUITex);
	LoadTexture(L"assets/images/UI/Cancel.png", &mCancelUITex);
	LoadTexture(L"assets/images/UI/SelectLogo.png", &mSelectTex);
	LoadTexture(L"assets/images/UI/StageNameBack.png", &mStageNameBackTex);
	LoadTexture(L"assets/images/UI/Table.png", &mTableNameUITex);
	LoadTexture(L"assets/images/UI/BathRoom.png", &mBathNameUITex);
	LoadTexture(L"assets/images/UI/Room.png", &mRoomNameUITex);
	LoadTexture(L"assets/images/UI/Difficulty.png", &mDifficultyUITex);
	LoadTexture(L"assets/images/UI/DifficultyBack.png", &mDifficultyBackUITex);
	LoadTexture(L"assets/images/UI/Tutorial.png", &mTutorialUITex);
	LoadTexture(L"assets/images/UI/RankC.png", &mRankUITex[0]);
	LoadTexture(L"assets/images/UI/RankB.png", &mRankUITex[1]);
	LoadTexture(L"assets/images/UI/RankA.png", &mRankUITex[2]);
	LoadTexture(L"assets/images/UI/RankS.png", &mRankUITex[3]);
	LoadTexture(L"assets/images/UI/LevelBack.png", &mRankBackUITex);

	LoadTexture(L"assets/images/UI/Test.png", &mSelectBackTex);

	// チュートリアル背景
	mSelectBackUI = new StaticObject(camera);
	mSelectBackUI->mSprite->SetTexture(mSelectBackTex);
	mSelectBackUI->SetSize(2.8f, 2.0f);
	mSelectBackUI->mSprite->mColor.r = 0.0f;
	mSelectBackUI->mSprite->mColor.g = 0.0f;
	mSelectBackUI->mSprite->mColor.b = 0.0f;
	mSelectBackUI->mSprite->mColor.a = 0.0f;

	// チュートリアルUI
	mTutorialUI = new StaticObject(camera);
	mTutorialUI->mSprite->SetTexture(mTutorialUITex);
	mTutorialUI->SetSize(2.5f, 2.5f);
	mTutorialUI->SetPosition(0.0f, 0.0f);
	mTutorialUI->SetActive(true);

	if (Stage_Info_Flg) {
		Stage_Info = -1;
		mTutorialUI->mSprite->mColor.r = 1.0f;
		mTutorialUI->mSprite->mColor.g = 1.0f;
		mTutorialUI->mSprite->mColor.b = 1.0f;

		mSelectBackUI->mSprite->mColor.a = 0.5f;
		Stage_Info_Flg = false;
	}
	else {
		Stage_Info = 2;
		mTutorialUI->mSprite->mColor.r = 0.5f;
		mTutorialUI->mSprite->mColor.g = 0.5f;
		mTutorialUI->mSprite->mColor.b = 0.5f;

		mSelectBackUI->mSprite->mColor.a = 0.0f;
	}


	// ステージ選択UI
	mSelectUI = new StaticObject(camera);
	mSelectUI->mSprite->SetTexture(mSelectTex);
	mSelectUI->SetSize(1.3f, 0.4f);
	mSelectUI->SetPosition(0.0f, 0.7f);

	// スタートUI
	mStartUI = new StaticObject(camera);
	mStartUI->mSprite->SetTexture(mStartUITex);
	mStartUI->SetSize(2.5f, 2.5f);
	mStartUI->SetPosition(0.0f, 0.0f);
	mStartUI->SetActive(false);

	// キャンセルUI
	mCancelUI = new StaticObject(camera);
	mCancelUI->mSprite->SetTexture(mCancelUITex);
	mCancelUI->SetSize(2.5f, 2.5f);
	mCancelUI->SetPosition(0.0f, 0.0f);
	mCancelUI->SetActive(false);

	// レベルUI
	mDifficultyBackUI = new StaticObject(camera);
	mDifficultyBackUI->mSprite->SetTexture(mDifficultyBackUITex);
	mDifficultyBackUI->SetSize(2.0f, 2.0f);
	mDifficultyBackUI->SetPosition(0.1f, 0.0f);
	mDifficultyBackUI->SetActive(false);
	mDifficultyUI = new StaticObject(camera);
	mDifficultyUI->mSprite->SetTexture(mDifficultyUITex);
	mDifficultyUI->SetSize(2.0f, 2.0f);
	mDifficultyUI->SetPosition(0.1f, 0.0f);
	mDifficultyUI->SetActive(false);

	// 時間UI
	mRankUI = new StaticObject(camera);
	mRankUI->mSprite->SetTexture(mRankUITex[1]);
	mRankUI->SetSize(2.0f, 1.7f);
	mRankUI->SetPosition(0.06f, 0.175f);
	mRankUI->SetActive(false);
	mRankBackUI = new StaticObject(camera);
	mRankBackUI->mSprite->SetTexture(mRankBackUITex);
	mRankBackUI->SetSize(2.5f, 2.5f);
	mRankBackUI->SetPosition(0.0f, 0.0f);
	mRankBackUI->SetActive(false);

	// ステージ名UI
	mStageNameBackUI = new StaticObject(camera);
	mStageNameBackUI->mSprite->SetTexture(mStageNameBackTex);
	mStageNameBackUI->SetSize(2.5f, 2.5f);
	mStageNameBackUI->SetPosition(0.0f, 0.0f);
	mStageNameBackUI->SetActive(false);
	mStageNameUI = new StaticObject(camera);
	mStageNameUI->mSprite->SetTexture(mRoomNameUITex);
	mStageNameUI->SetSize(2.5f, 2.5f);
	mStageNameUI->SetPosition(0.0f, 0.0f);
	mStageNameUI->SetActive(false);

	Sound_Init(SOUND_LABEL_SE000);
	Sound_Init(SOUND_LABEL_BGM001);
	Sound_Init(SOUND_LABEL_BGM002);
	Sound_Init(SOUND_LABEL_BGM003);
	Sound_Init(SOUND_LABEL_BGM004);

	mBGMTime = 0.0f;
	BGM = SOUND_LABEL_BGM003;
	OldBGM = BGM;
	Play(BGM);
	SetVolume(BGM, 0.25f);
	Stage_Dicision = true;	//ステージ決定していない
	SelectStageID = ROOM_STAGE;	//最初は部屋に設定
}

//<><><><><><><><><><><><><><><><><><>
// 関数名：~Select
// 役割：デストラクタ
//<><><><><><><><><><><><><><><><><><>
Select::~Select()
{
	for (int i = 0; i < MAXSTAGE; i++) {
		delete mObject[i];
	}
	delete mSelectBackUI;
	delete mSelectUI;
	delete mBgTex;
	delete mStartUI;
	delete mTutorialUI;
	delete mCancelUI;
	delete mDifficultyUI;
	delete mDifficultyBackUI;
	delete mRankUI;
	delete mRankBackUI;
	delete mStageNameBackUI;
	delete mStageNameUI;

	Sound_Uninit(SOUND_LABEL_BGM004);
	Sound_Uninit(SOUND_LABEL_BGM003);
	Sound_Uninit(SOUND_LABEL_BGM002);
	Sound_Uninit(SOUND_LABEL_BGM001);
	Sound_Uninit(SOUND_LABEL_SE000);

	COM_SAFE_RELEASE(mBgTex);
	COM_SAFE_RELEASE(mSelectTex);
	COM_SAFE_RELEASE(mCancelUITex);
	COM_SAFE_RELEASE(mStartUITex);
	COM_SAFE_RELEASE(mBathObjTex);
	COM_SAFE_RELEASE(mTableObjTex);
	COM_SAFE_RELEASE(mRoomObjTex);
	COM_SAFE_RELEASE(mDifficultyUITex);
	COM_SAFE_RELEASE(mDifficultyBackUITex);
	COM_SAFE_RELEASE(mTutorialUITex);
	COM_SAFE_RELEASE(mStageNameBackTex);
	COM_SAFE_RELEASE(mTableNameUITex);
	COM_SAFE_RELEASE(mBathNameUITex);
	COM_SAFE_RELEASE(mRoomNameUITex);
	COM_SAFE_RELEASE(mRankBackUITex);
	COM_SAFE_RELEASE(mSelectBackTex);
	// ランクテクスチャの解放
	for (int i = 0; i < 4; i++)
	{
		COM_SAFE_RELEASE(mRankUITex[i]);
	}
}

//<><><><><><><><><><><><><><><><><><>
// 関数名：GetStageID
// 役割：ステージIDの取得
//<><><><><><><><><><><><><><><><><><>
int Select::GetStageID(void)
{
	return SelectStageID;
}

//<><><><><><><><><><><><><><><><><><>
// 関数名：GetInput
// 役割：入力情報の取得
//<><><><><><><><><><><><><><><><><><>
int Select::GetInput(void)
{
	return mInput;
}

//<><><><><><><><><><><><><><><><><><>
// 関数名：SelectStage
// 役割：ステージ選択
//<><><><><><><><><><><><><><><><><><>
void Select::StageSelect(void)
{

	//選択中のステージを変更
	if (Input_GetButtonTrigger(LEFT)||Input_GetKeyTrigger('A')) {
		if (Rota == NONE_ROTA) {
			Rota = RIGHT_ROTA;
			Play(SOUND_LABEL_SE000);
			//BGMChange = true;
		}
	}
	if (Input_GetButtonTrigger(RIGHT) || Input_GetKeyTrigger('D')) {
		if (Rota == NONE_ROTA) {
			Rota = LEFT_ROTA;
			Play(SOUND_LABEL_SE000);
			//BGMChange = true;
		}
	}

	//選択中のステージ別の配置
	switch (SelectStageID) {
	case ROOM_STAGE:
		StageID[0] = BATH_STAGE;
		StageID[1] = ROOM_STAGE;
		StageID[2] = TABLE_STAGE;
		break;
	case BATH_STAGE:
		StageID[0] = TABLE_STAGE;
		StageID[1] = BATH_STAGE;
		StageID[2] = ROOM_STAGE;
		break;
	case TABLE_STAGE:
		StageID[0] = ROOM_STAGE;
		StageID[1] = TABLE_STAGE;
		StageID[2] = BATH_STAGE;
		break;
	}

	


	//---------------------------------------------
	//左回り
	//---------------------------------------------
	if (Rota == LEFT_ROTA) {

		//左奥オブジェクト
		//if(mObject[StageID[0]]->mSprite->mCenter.x )

		if (mObject[StageID[0]]->mSprite->mCenter.x >= 0.0f) {	//中心に行くまで移動
			mObject[StageID[0]]->mSprite->mCenter.x -= 0.002f * gDeltaTime;
			if (mObject[StageID[0]]->mSprite->mSize.x < 0.9f) {	//奥行を表現するために拡大
				mObject[StageID[0]]->mSprite->mSize.x += 0.001f * gDeltaTime;
				mObject[StageID[0]]->mSprite->mSize.y += 0.001f * gDeltaTime;
			}

		}

		//中心オブジェクト
		if (mObject[StageID[1]]->mSprite->mCenter.x >= -1.0f) {	//左端に行くまで移動
			mObject[StageID[1]]->mSprite->mCenter.x -= 0.001f* gDeltaTime;
			if (mObject[StageID[1]]->mSprite->mSize.x > 0.4f) {	//奥行を表現するために縮小
				mObject[StageID[1]]->mSprite->mSize.x -= 0.001f * gDeltaTime;
				mObject[StageID[1]]->mSprite->mSize.y -= 0.001f * gDeltaTime;
			}
		}

		//右奥オブジェクト
		if (mObject[StageID[2]]->mSprite->mCenter.x <= 1.0f) {	//右端まで移動
			mObject[StageID[2]]->mSprite->mCenter.x += 0.002f* gDeltaTime;
		}

		if (mObject[StageID[0]]->mSprite->mCenter.x <= 0.0f &&
			mObject[StageID[1]]->mSprite->mCenter.x <= -1.0f &&
			mObject[StageID[2]]->mSprite->mCenter.x >= 1.0f) {	//左回り終了
			SelectStageID++;
			Rota = NONE_ROTA;
		}

	}

	//---------------------------------------------
	//右回り
	//---------------------------------------------
	if (Rota == RIGHT_ROTA) {
		//右奥オブジェクト
		if (mObject[StageID[0]]->mSprite->mCenter.x >= -1.0f) {	//左端に行くまで移動
			mObject[StageID[0]]->mSprite->mCenter.x -= 0.002f* gDeltaTime;
		}

		//中心オブジェクト
		if (mObject[StageID[1]]->mSprite->mCenter.x <= 1.0f) {	//右端に行くまで移動
			mObject[StageID[1]]->mSprite->mCenter.x += 0.001f * gDeltaTime;
			if (mObject[StageID[1]]->mSprite->mSize.x > 0.4f) {	//奥行を表現するために縮小
				mObject[StageID[1]]->mSprite->mSize.x -= 0.001f * gDeltaTime;
				mObject[StageID[1]]->mSprite->mSize.y -= 0.001f * gDeltaTime;
			}
		}

		////左奥オブジェクト
		if (mObject[StageID[2]]->mSprite->mCenter.x <= 0.0f) {	//中心まで移動
			mObject[StageID[2]]->mSprite->mCenter.x += 0.001f * gDeltaTime;
			if (mObject[StageID[2]]->mSprite->mSize.x < 0.9f) {	//奥行を表現するために拡大
				mObject[StageID[2]]->mSprite->mSize.x += 0.001f * gDeltaTime;
				mObject[StageID[2]]->mSprite->mSize.y += 0.001f * gDeltaTime;
			}

			
		}

		if (mObject[StageID[0]]->mSprite->mCenter.x <= -1.0f &&
			mObject[StageID[1]]->mSprite->mCenter.x >= 1.0f &&
			mObject[StageID[2]]->mSprite->mCenter.x >= 0.0f) {	//右回り終了
			SelectStageID--;
			Rota = NONE_ROTA;
		}
		
	}

	//ステージ数の調整
	if (SelectStageID < 0) {
		SelectStageID = 2;
	}
	if (SelectStageID > 2) {
		SelectStageID = 0;
	}

	OldBGM = BGM;
		switch (SelectStageID) {
	case ROOM_STAGE:
		BGM = SOUND_LABEL_BGM003;
		mStageNameUI->mSprite->SetTexture(mRoomNameUITex);// テクスチャの変更
		mRankUI->mSprite->SetTexture(mRankUITex[1]);// テクスチャの変更
		break;
	case BATH_STAGE:
		BGM = SOUND_LABEL_BGM002;
		mStageNameUI->mSprite->SetTexture(mBathNameUITex);// テクスチャの変更
		mRankUI->mSprite->SetTexture(mRankUITex[2]);// テクスチャの変更
		break;
	case TABLE_STAGE:
		BGM = SOUND_LABEL_BGM004;
		mStageNameUI->mSprite->SetTexture(mTableNameUITex);// テクスチャの変更
		mRankUI->mSprite->SetTexture(mRankUITex[0]);// テクスチャの変更
		break;
	}
	if (OldBGM != BGM)// BGMが変わった時
	{
		Stop(OldBGM);
		Play(BGM);
		SetVolume(BGM, 0.25f);
		mBGMTime = 0.0f;
	}

}

//<><><><><><><><><><><><><><><><><><>
// 関数名：StageInfo
// 役割：ステージ詳細表示
//<><><><><><><><><><><><><><><><><><>
void Select::StageInfo(void)
{
	if (Rota == NONE_ROTA && Stage_Info != -1) {//回転中じゃなかったら
		//Bボタンでステージ詳細表示
		if (Input_GetButtonTrigger(B) || Input_GetKeyTrigger(VK_SPACE)) {// ステージ決定
			//選択したステージオブジェクト以外を非表示

			mSelectUI->SetActive(false);
			mObject[StageID[0]]->SetActive(false);
			mObject[StageID[2]]->SetActive(false);
			Stage_Info = true;

		}
	}

	if (Stage_Info == 1) {

		//ステージオブジェクトの移動
		if (mObject[StageID[1]]->mSprite->mCenter.x >= -0.6f) {
			mObject[StageID[1]]->mSprite->mCenter.x -= 0.001f * gDeltaTime;
			if (mObject[StageID[1]]->mSprite->mSize.x <= 1.3f) {
				mObject[StageID[1]]->mSprite->mSize.x += 0.001f * gDeltaTime;
				mObject[StageID[1]]->mSprite->mSize.y += 0.001f * gDeltaTime;
			}

		}
		else {

			
		
			//ステージ決定UI
			if (Stage_Dicision) {
				mStartUI->mSprite->mSize.x = 2.9f;
				mStartUI->mSprite->mSize.y = 2.1f;
				mCancelUI->mSprite->mSize.x = 2.8f;
				mCancelUI->mSprite->mSize.y = 2.0f;
				
				mStartUI->mSprite->mColor.r = 1.0f;
				mStartUI->mSprite->mColor.g = 1.0f;
				mStartUI->mSprite->mColor.b = 1.0f;
				mCancelUI->mSprite->mColor.b = 0.5f;
				mCancelUI->mSprite->mColor.r = 0.5f;
				mCancelUI->mSprite->mColor.g = 0.5f;
			}
			else {
				mStartUI->mSprite->mSize.x = 2.8f;
				mStartUI->mSprite->mSize.y = 2.0f;
				mCancelUI->mSprite->mSize.x = 2.9f;
				mCancelUI->mSprite->mSize.y = 2.1f;
				mCancelUI->mSprite->mColor.b = 1.0f;
				mCancelUI->mSprite->mColor.r = 1.0f;
				mCancelUI->mSprite->mColor.g = 1.0f;
				mStartUI->mSprite->mColor.r = 0.5f;
				mStartUI->mSprite->mColor.g = 0.5f;
				mStartUI->mSprite->mColor.b = 0.5f;
				
			}

			//UIの表示
			mStartUI->SetActive(true);
			mCancelUI->SetActive(true);
			mDifficultyBackUI->SetActive(true);
			mDifficultyUI->SetActive(true);
			mRankUI->SetActive(true);
			mRankBackUI->SetActive(true);
			mStageNameBackUI->SetActive(true);
			mStageNameUI->SetActive(true);
			mTutorialUI->SetActive(false);// 非表示
			//ステージ決定UIのカーソル移動
			if (Input_GetButtonTrigger(LEFT) || Input_GetKeyTrigger('A')) {	//左
				if (Stage_Dicision) {
					Stage_Dicision = false;
				}
				else {
					Stage_Dicision = true;
				}
			}
			if (Input_GetButtonTrigger(RIGHT) || Input_GetKeyTrigger('D')) {//右
				if (Stage_Dicision) {
					Stage_Dicision = false;
				}
				else {
					Stage_Dicision = true;
				}
			}

			if (Stage_Dicision) {	//シーン移動
				if (Input_GetButtonTrigger(B) || Input_GetKeyTrigger(VK_SPACE)) {
					Stop(BGM);
					Fade_Bubble::FadeOut();
				}
				if (Fade_Bubble::mState == FADE_OUT_END) {
					SceneManager::SceneChange(GAME_MAIN, BUBBLE_FADE);
				}
			}
			if (!Stage_Dicision) {
				if (Input_GetButtonTrigger(B) || Input_GetKeyTrigger(VK_SPACE)) {// キャンセル

					Stage_Info = false;
					//UIを非表示に
					mStartUI->SetActive(false);
					mCancelUI->SetActive(false);
					mDifficultyBackUI->SetActive(false);
					mDifficultyUI->SetActive(false);
					mRankUI->SetActive(false);
					mRankBackUI->SetActive(false);
					mStageNameBackUI->SetActive(false);
					mStageNameUI->SetActive(false);
					mTutorialUI->SetActive(true);// 表示
				}
			}

		}
		
	}
	else if (Stage_Info == 0)
	{
		//ステージオブジェクトを元の位置に移動
		if (mObject[StageID[1]]->mSprite->mCenter.x <= 0.0f) {
			mObject[StageID[1]]->mSprite->mCenter.x += 0.001f * gDeltaTime;
			if (mObject[StageID[1]]->mSprite->mSize.x >= 1.0f) {
				mObject[StageID[1]]->mSprite->mSize.x -= 0.001f * gDeltaTime;
				mObject[StageID[1]]->mSprite->mSize.y -= 0.001f * gDeltaTime;
			}
		}
		else {
			//選択外のオブジェクトの再表示
			mObject[StageID[0]]->SetActive(true);
			mObject[StageID[2]]->SetActive(true);
			mSelectUI->SetActive(true);
			Stage_Info = 2;
			if (Input_GetButtonTrigger(B) || Input_GetKeyTrigger(VK_SPACE)) {
				Stop(BGM);
				SceneManager::SceneChange(TITLE, NONE_TYPE);
			}
		}
		
	}
	if(Stage_Info != 1 && Rota == NONE_ROTA)
	{
		if (Input_GetButtonTrigger(DOWN) || Input_GetKeyTrigger('S')) {//下
			/*mTutorialUI->mSprite->mSize.x = 2.6f;
			mTutorialUI->mSprite->mSize.y = 2.6f;*/
			mTutorialUI->mSprite->mColor.r = 1.0f;
			mTutorialUI->mSprite->mColor.g = 1.0f;
			mTutorialUI->mSprite->mColor.b = 1.0f;

			mSelectBackUI->mSprite->mColor.a = 0.5f;

			Stage_Info = -1;
		}
		if (Input_GetButtonTrigger(UP) || Input_GetKeyTrigger('W')) {//下
			/*mTutorialUI->mSprite->mSize.x = 2.5f;
			mTutorialUI->mSprite->mSize.y = 2.5f;*/
			mTutorialUI->mSprite->mColor.r = 0.5f;
			mTutorialUI->mSprite->mColor.g = 0.5f;
			mTutorialUI->mSprite->mColor.b = 0.5f;

			mSelectBackUI->mSprite->mColor.a = 0.0f;
			Stage_Info = 0;
		}
	}
	

	if (Stage_Info == -1) {
		if (Input_GetKeyTrigger(VK_SPACE) && !Input_GetButtonTrigger(B)) {
			SelectStageID = TUTORIAL_STAGE;
			mInput = 1;	//コントローラー入力
			Stop(BGM);
			Fade_Bubble::FadeOut();
		}
		if (Input_GetButtonTrigger(B) && !Input_GetKeyTrigger(VK_SPACE)) {
			SelectStageID = TUTORIAL_STAGE;
			mInput = 0;	//キーボード入力
			Stop(BGM);
			Fade_Bubble::FadeOut();
		}
		if (Fade_Bubble::mState == FADE_OUT_END) {
			SceneManager::SceneChange(GAME_MAIN, BUBBLE_FADE);
		}
	}

}

//<><><><><><><><><><><><><><><><><><>
// 関数名：Update
// 役割：更新
//<><><><><><><><><><><><><><><><><><>
void Select::Update(void)
{
	mBg->Update();
	mBGMTime += gDeltaTime;
	for (int i = 0; i < MAXSTAGE; i++) {
		mObject[i]->Update();
	}
	mTutorialUI->Update();
	mSelectUI->Update();
	mStartUI->Update();
	mCancelUI->Update();
	mDifficultyBackUI->Update();
	mDifficultyUI->Update();
	mRankBackUI->Update();
	mRankUI->Update();
	mStageNameBackUI->Update();
	mStageNameUI->Update();
	mSelectBackUI->Update();
	if (mBGMTime > 18.0f * 1000.0f)
	{
		Play(BGM);
		SetVolume(BGM, 0.25f);
		mBGMTime = 0.0f;
	}

	if (Fade_Bubble::mState == FADE_IN_END) {

		if (Stage_Info == 2) {
			StageSelect();	//ステージ選択
		}
	}
	StageInfo();

}

//<><><><><><><><><><><><><><><><><><>
// 関数名：Draw
// 役割：描画
//<><><><><><><><><><><><><><><><><><>
void Select::Draw(void)
{
	mBg->Draw();

	//回転向きによって描画順を変更
	if (Rota == LEFT_ROTA) {
		mObject[StageID[2]]->Draw();
		mObject[StageID[1]]->Draw();
		mObject[StageID[0]]->Draw();
	}
	else if (Rota == RIGHT_ROTA) {
		mObject[StageID[0]]->Draw();
		mObject[StageID[1]]->Draw();
		mObject[StageID[2]]->Draw();
	}
	else {
		mObject[StageID[0]]->Draw();
		mObject[StageID[1]]->Draw();
		mObject[StageID[2]]->Draw();
	}
	mSelectBackUI->Draw();
	mTutorialUI->Draw();
	mSelectUI->Draw();
	mStartUI->Draw();
	mCancelUI->Draw();
	mDifficultyBackUI->Draw();
	mDifficultyUI->Draw();
	mRankBackUI->Draw();
	mRankUI->Draw();
	mStageNameBackUI->Draw();
	mStageNameUI->Draw();
}


//======================================================================================
// 担当者：		菅眞心
// 制作日時：　 2022-12-01
// チーム名：	黒棺	
//======================================================================================