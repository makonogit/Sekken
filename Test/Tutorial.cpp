#include "Tutorial.h"

extern DWORD gDeltaTime;

//<><><><><><><><><><><><><><><><><><>
// 関数名：Tutorial
// 役割：コンストラクタ
// 引数：なし
//<><><><><><><><><><><><><><><><><><>
Tutorial::Tutorial()
{

	mInput = Select::GetInput();	//入力情報を取得

	//マップ情報の設定
	int MapInfo[STAGE_HIGHT][STAGE_WIDTH] =
	{
		//					   1				   2				   3				   4
		//	 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0

			/*{0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
			{0,0,0,0,0,1,1,0,0,1,1,1,1,1,0,0,1,0,0,1,1,1,0,0,0,0,0,0,0,0,1,0,0,0,1,1,1,1,0,0},
			{0,0,0,0,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,0,0,0,1,1,1,0,1,1,1,1,0,1,0,0,1,0,0},
			{0,0,0,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,0,0,0,0,0,1,1,1,0,0},
			{0,0,1,0,1,1,1,0,0,1,1,0,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,0,0,1,0,0,0,0,0,1,1,1,1,0},
			{0,0,1,0,1,1,1,1,1,1,0,0,0,0,1,1,0,1,0,1,1,0,0,1,1,1,0,0,0,0,0,0,0,0,1,1,1,1,0,0},
			{0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0},
			{0,0,1,1,0,1,0,0,0,0,0,0,0,0,0,1,1,1,1,1,0,0,0,1,1,1,0,1,1,0,1,0,0,0,0,0,0,1,1,1},
			{0,1,1,1,0,1,0,0,0,0,0,0,0,0,0,1,1,1,1,1,0,0,0,1,1,0,0,0,0,0,0,1,0,0,0,0,1,1,1,1},
			{0,1,0,1,1,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,1,1,1,1},
			{0,1,1,1,1,0,0,0,1,1,1,0,0,0,0,0,0,0,1,0,0,0,0,1,1,0,0,0,0,0,1,0,0,0,0,1,1,1,0,0},
			{0,0,1,1,1,1,0,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,1,1,1,0,0,0},
			{0,0,1,1,1,1,0,0,1,0,0,0,0,1,1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,1,1,1,1,0,0},
			{0,0,1,1,1,0,0,1,1,0,1,1,1,1,0,1,0,0,0,0,0,0,0,1,1,0,0,1,0,0,1,1,0,0,1,1,0,0,0,0},
			{0,1,0,0,1,1,0,0,1,1,0,0,1,0,1,1,0,0,0,0,0,0,0,1,0,0,1,0,1,1,1,0,0,0,1,1,0,1,0,0},
			{0,0,0,1,0,1,1,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1,1,1,0,1,0,0,0,0,0},
			{0,0,0,1,0,1,1,0,0,0,1,1,1,0,0,1,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0},
			{0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0},
			{0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1,1,1,0,0,1,1,1,1,1,1,1,1,1,1,0},
			{0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0},
			{0,0,0,0,0,0,1,0,1,1,0,0,0,0,0,0,1,0,0,0,1,1,0,1,1,0,0,1,0,0,0,0,1,1,1,1,0,0,0,0},
			{0,0,0,0,0,0,0,1,1,1,0,0,0,0,1,0,0,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,1,1,1,0,1,0,1},
			{0,0,0,0,0,0,1,1,1,1,1,0,1,1,1,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,0,0},
			{0,0,0,0,0,1,1,1,1,1,1,1,1,1,0,0,0,0,1,1,1,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0},
			{0,0,1,0,1,0,1,1,1,1,1,1,0,0,0,0,0,0,0,0,1,0,1,1,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,0},
			{0,0,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0},
			{0,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,1,1,1,1,1,0},
			{0,0,1,1,1,0,0,1,1,1,1,1,1,0,0,0,0,0,0,1,1,0,0,1,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1},
			{0,0,0,1,1,0,0,0,1,1,1,1,1,0,0,0,0,0,0,1,0,0,1,1,0,0,0,0,0,0,0,0,1,1,1,0,0,1,1,1},
			{0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0},*/

			//					   1				   2				   3				   4
			//	 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0

			{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
			{0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0},
			{0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0},
			{0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0},
			{0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0},
			{0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0},
			{0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0},
			{0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0},
			{0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0},
			{0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0},
			{0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,0},
			{0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,0,0,0,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,0},
			{0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,0,0,0,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,0},
			{0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,0,0,0,0,0,0,0,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,0},
			{0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,0,0,0,0,0,0,0,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,0},
			{0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,0,0,0,0,0,0,0,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,0},
			{0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,0,0,0,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,0},
			{0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,0,0,0,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,0},
			{0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,0},
			{0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,0},
			{0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0},
			{0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0},
			{0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0},
			{0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0},
			{0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0},
			{0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0},
			{0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0},
			{0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0},
			{0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0},
			{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},



	};

	for (int i = 0; i < STAGE_HIGHT; i++) {
		for (int j = 0; j < STAGE_WIDTH; j++) {
			mMapInfo[i][j] = MapInfo[i][j];
		}
	}

	//時間テクスチャ
	LoadTexture(L"assets/images/Time/Time0.png", &mNumTex[0]);
	LoadTexture(L"assets/images/Time/Time1.png", &mNumTex[1]);
	LoadTexture(L"assets/images/Time/Time2.png", &mNumTex[2]);
	LoadTexture(L"assets/images/Time/Time3.png", &mNumTex[3]);
	LoadTexture(L"assets/images/Time/Time4.png", &mNumTex[4]);
	LoadTexture(L"assets/images/Time/Time5.png", &mNumTex[5]);
	LoadTexture(L"assets/images/Time/Time6.png", &mNumTex[6]);
	LoadTexture(L"assets/images/Time/Time7.png", &mNumTex[7]);
	LoadTexture(L"assets/images/Time/Time8.png", &mNumTex[8]);
	LoadTexture(L"assets/images/Time/Time9.png", &mNumTex[9]);

	LoadTexture(L"assets/images/Time/TimeBack.png", &mTimeBackTex);

	mTimeBack = new StaticObject(mCamera);
	mTimeBack->mSprite->SetTexture(mTimeBackTex);
	mTimeBack->SetSize(0.6f, 0.3f);
	mTimeBack->SetPosition(0.0f, 0.8f);

	//時間
	for (int i = 0; i < 4; i++) {
		mTime[i] = new StaticObject(mCamera);
		mTime[i]->mSprite->SetTexture(mNumTex[0]);
		mTime[i]->SetSize(0.1f, 0.1f);
	}

	mCamera = { 0.0f,0.0f,1.0f };
	LoadTexture(L"assets/images/BackGround/Stage/Room_Stage.png", &mBgTex);	//背景テクスチャ
	LoadTexture(L"assets/images/Block/ChopSticks1.png", &mChopStick_BlueTex);			//お箸(青)
	LoadTexture(L"assets/images/Block/ChopSticks2.png", &mChopStick_PinkTex);			//お箸(ピンク)

	LoadTexture(L"assets/images/Item/CatMark.png", &mCatMarkTex);

	//汚れの初期化
	mFloor = new Floor(mCamera, MapInfo);

	ClearNum = 0;


	//泡の初期化
	for (int i = 0; i < BABBLMAX; i++) {
		mBabble[i] = new Babble(mCamera);
	}

	BabbleNum = 0;


	//----------------------
	//障害物の初期化
	//---------------------

	{
		XMFLOAT2 gap = { 0.05f,0.0f };			//あたり判定のずれ
		XMFLOAT2 ShoesHit_Size = { 0.0f,0.0f };	//靴のあたりサイズ

		for (int i = 0; i < BLOCKMAX; i++) {
			mBlock[i] = new StaticObject(mCamera);
			mBlock[i]->SetSize(1.3f, 1.65f);
		}

		mBlock4 = new StaticObject(mCamera);
		mBlock4->SetSize(1.0f, 2.0f);

		XMFLOAT2 ChopStickSize = { 0.06f,1.4f };
		mBlockHit[0] = new HitSquare(&mBlock[0]->mSprite->mCenter, ChopStickSize, gap, 0.0f);
		mBlockHit[1] = new HitSquare(&mBlock4->mSprite->mCenter, ChopStickSize, gap, 0.0f);
		mBlockHit[2] = new HitSquare(&mBlock[2]->mSprite->mCenter, ShoesHit_Size, gap, 0.0f);

		//テクスチャ,座標セット
		mBlock[0]->mSprite->SetTexture(mChopStick_BlueTex);	//箸青
		mBlock[0]->SetPosition(-0.6f, 0.1f);
		mBlock[0]->SetSize(1.3f, 1.65f);
		mBlock[0]->active = true;

		mBlock[1]->mSprite->SetTexture(mChopStick_BlueTex);	//箸青
		mBlock[1]->SetPosition(-0.5f, 0.1f);
		mBlock[1]->SetSize(1.3f, 1.65f);
		mBlock[1]->active = true;

		mBlock[2]->mSprite->SetTexture(mChopStick_PinkTex);	//箸ピンク
		mBlock[2]->SetPosition(0.7f, 0.0f);
		mBlock[2]->SetSize(1.3f, 1.65f);

		mBlock4->mSprite->SetTexture(mChopStick_PinkTex);	//箸ピンク
		mBlock4->SetPosition(0.6f, 0.0f);
		mBlock4->SetSize(1.3f, 1.65f);
	
	}

	//背景の初期化
	mBackGround = new StaticObject(mCamera);
	mBackGround->mSprite->SetTexture(mBgTex);
	mBackGround->SetSize(5.6f, 4.0f);


	//チュートリアル用の画像読み込み
	LoadTexture(L"assets/images/Tutorial/WalkTask.png", &mWalkTaskTex);
	LoadTexture(L"assets/images/Tutorial/SetTask.png", &mSetTaskTex);
	LoadTexture(L"assets/images/Tutorial/AngleTask.png", &mAngleTaskTex);
	LoadTexture(L"assets/images/Tutorial/ThrowTask.png", &mThrowTaskTex);
	LoadTexture(L"assets/images/Tutorial/CurveTask.png", &mCurveTaskTex);
	LoadTexture(L"assets/images/Tutorial/Pause.png", &mPauseTex);

	//ボタン画像の読み込み
	{
		LoadTexture(L"assets/images/Tutorial/Start.png", &mXY_ButtonTex[0]);		//XY
		LoadTexture(L"assets/images/Tutorial/XY_Push.png", &mXY_ButtonTex[1]);
		LoadTexture(L"assets/images/Tutorial/B.png", &mB_ButtonTex[0]);		//B
		LoadTexture(L"assets/images/Tutorial/B_Push.png", &mB_ButtonTex[1]);
		LoadTexture(L"assets/images/Tutorial/Trigger.png", &mTriggerTex[0]);		//トリガー
		LoadTexture(L"assets/images/Tutorial/RT.png", &mTriggerTex[1]);
		LoadTexture(L"assets/images/Tutorial/Stick.png", &mStickTex[0]);		//スティック
		LoadTexture(L"assets/images/Tutorial/Stick_Push.png", &mStickTex[1]);
	}
	
	//キー画像の読み込み
	{
		LoadTexture(L"assets/images/Tutorial/WASD.png", &mWASDKeyTex[0]);			//WASD
		LoadTexture(L"assets/images/Tutorial/WASD_Push.png", &mWASDKeyTex[1]);
		LoadTexture(L"assets/images/Tutorial/Esc.png", &mEscape_KeyTex[0]);			//Escape
		LoadTexture(L"assets/images/Tutorial/Esc_Push.png", &mEscape_KeyTex[1]);
		LoadTexture(L"assets/images/Tutorial/Speace.png", &mSpeace_KeyTex[0]);		//Speace
		LoadTexture(L"assets/images/Tutorial/Speace_Push.png", &mSpeace_KeyTex[1]);
		LoadTexture(L"assets/images/Tutorial/Mouse.png", &mMouseTex[0]);			//マウス
		LoadTexture(L"assets/images/Tutorial/Click.png", &mMouseTex[1]);
		LoadTexture(L"assets/images/Tutorial/Mouse_Right.png", &mMouseTex[2]);
		LoadTexture(L"assets/images/Tutorial/MousePoint.png", &mMousePointTex);		//マウスポインタ
	}

	LoadTexture(L"assets/images/Tutorial/DogIvent_Key.png", &mDogIvent_KeyTex);
	LoadTexture(L"assets/images/Tutorial/CatIvent_Key.png", &mCatIvent_KeyTex);
	LoadTexture(L"assets/images/Tutorial/DogIvent_Button.png", &mDogIvent_ButtonTex);
	LoadTexture(L"assets/images/Tutorial/CatIvent_Button.png", &mCatIvent_ButtonTex);

	mFrisbee = new Frisbee(mCamera);
	mPlayer = new Player(mCamera, mFrisbee);			//プレイヤー
	mMiniMap = new MiniMap(mFloor->mDirt, mBlock);		//ミニマップ
	mCat = new Cat(mCamera);							//猫
	mDog = new Dog(mCamera);

	if (mInput == 0) {
		ButtonLoad();
	}
	else {
		KeyLoad();
	}
	
	{
		mWalk_TaskUI = new StaticObject(mCamera);	//タスク
		mWalk_TaskUI->mSprite->SetTexture(mWalkTaskTex);
		mWalk_TaskUI->SetSize(0.7f, 0.1f);

		mSet_TaskUI = new StaticObject(mCamera);	//タスク
		mSet_TaskUI->mSprite->SetTexture(mSetTaskTex);
		mSet_TaskUI->SetSize(0.7f, 0.1f);

		mAngle_TaskUI = new StaticObject(mCamera);	//タスク
		mAngle_TaskUI->mSprite->SetTexture(mAngleTaskTex);
		mAngle_TaskUI->SetSize(0.7f, 0.1f);

		mThrow_TaskUI = new StaticObject(mCamera);	//タスク
		mThrow_TaskUI->mSprite->SetTexture(mThrowTaskTex);
		mThrow_TaskUI->SetSize(0.7f, 0.1f);

		mCurve_TaskUI = new StaticObject(mCamera);	//タスク
		mCurve_TaskUI->mSprite->SetTexture(mCurveTaskTex);
		mCurve_TaskUI->SetSize(0.7f, 0.1f);

		mPauseUI = new StaticObject(mCamera);	//タスク
		mPauseUI->mSprite->SetTexture(mPauseTex);
		mPauseUI->SetSize(0.7f, 0.1f);

	}


	//猫のマーカー
	mCatMark = new StaticObject(mCamera);
	mCatMark->mSprite->SetTexture(mCatMarkTex);
	mCatMark->SetSize(0.3f, 0.3f);
	//mCatMark->active = false;


	mDogIvent_State = NONE_IVENT;
	mCatIvent_State = NONE_IVENT;
	mBGMSound = SOUND_LABEL_BGM007;
	Sound_Init(mBGMSound);
	Play(mBGMSound);
	SetVolume(mBGMSound, 0.5f);
}


//<><><><><><><><><><><><><><><><><><>
// 関数名：~Tutorial
// 役割：デストラクタ
//<><><><><><><><><><><><><><><><><><>
Tutorial::~Tutorial()
{
	Sound_Uninit(mBGMSound);
	delete mWalk_KeyUI;
	delete mSet_KeyUI;
	delete mAngle_KeyUI;
	delete mThrow_KeyUI;
	delete mCurve_UI;
	delete mPause_KeyUI;

	delete mWalk_TaskUI;
	delete mSet_TaskUI;
	delete mAngle_TaskUI;
	delete mThrow_TaskUI;
	delete mCurve_TaskUI;
	delete mPauseUI;

	delete mIvent_UI;

	delete mFloor;
	delete mDog;
	delete mCat;
	delete mMiniMap;
	delete mPlayer;
	delete mFrisbee;
	delete mCatMark;

	for (int i = 0; i < 4; i++) {
		delete mTime[i];
	}

	for (int i = 0; i < BABBLMAX; i++) {
		delete mBabble[i];
	}

	for (int i = 0; i < BLOCKMAX; i++) {
		delete mBlock[i];
		delete mBlockHit[i];
	}
	delete mBlock4;


	for (int i = 0; i < 10; i++) {
		COM_SAFE_RELEASE(mNumTex[i]);
	}

	COM_SAFE_RELEASE(mTimeBackTex);
	COM_SAFE_RELEASE(mBgTex);
	COM_SAFE_RELEASE(mChopStick_BlueTex);
	COM_SAFE_RELEASE(mChopStick_PinkTex);
	//COM_SAFE_RELEASE(mStickTex);

	for (int i = 0; i < 2; i++) {

		COM_SAFE_RELEASE(mB_ButtonTex[i]);
		COM_SAFE_RELEASE(mXY_ButtonTex[i]);
		COM_SAFE_RELEASE(mTriggerTex[i]);
		COM_SAFE_RELEASE(mStickTex[i]);

		COM_SAFE_RELEASE(mWASDKeyTex[i]);
		COM_SAFE_RELEASE(mEscape_KeyTex[i]);
		COM_SAFE_RELEASE(mSpeace_KeyTex[i]);

		COM_SAFE_RELEASE(mMouseTex[i]);
	}
	COM_SAFE_RELEASE(mMouseTex[2]);
	COM_SAFE_RELEASE(mMousePointTex);

	COM_SAFE_RELEASE(mWalkTaskTex);
	COM_SAFE_RELEASE(mSetTaskTex);
	COM_SAFE_RELEASE(mAngleTaskTex);
	COM_SAFE_RELEASE(mThrowTaskTex);
	COM_SAFE_RELEASE(mCurveTaskTex);
	COM_SAFE_RELEASE(mPauseTex);

	COM_SAFE_RELEASE(mDogIvent_KeyTex);
	COM_SAFE_RELEASE(mCatIvent_KeyTex);
	COM_SAFE_RELEASE(mDogIvent_ButtonTex);
	COM_SAFE_RELEASE(mCatIvent_ButtonTex);

	COM_SAFE_RELEASE(mCatMarkTex);
}


//<><><><><><><><><><><><><><><><><><>
// 関数名：KeyLoad
// 役割：キーボード入力の初期化
//<><><><><><><><><><><><><><><><><><>
void Tutorial::KeyLoad()
{
	{
		mWalk_KeyUI = new StaticObject(mCamera);	//WASDボタン
		mWalk_KeyUI->mSprite->SetTexture(mWASDKeyTex[0]);
		mWalk_KeyUI->SetSize(0.3f, 0.1f);

		mSet_KeyUI = new StaticObject(mCamera);		//Speaceボタン
		mSet_KeyUI->mSprite->SetTexture(mSpeace_KeyTex[0]);
		mSet_KeyUI->SetSize(0.2f, 0.1f);

		mAngle_KeyUI = new StaticObject(mCamera);	//Mouse
		mAngle_KeyUI->mSprite->SetTexture(mMousePointTex);
		mAngle_KeyUI->SetSize(0.25f, 0.15f);

		mThrow_KeyUI = new StaticObject(mCamera);	//Speaceボタン
		mThrow_KeyUI->mSprite->SetTexture(mSpeace_KeyTex[1]);
		mThrow_KeyUI->SetSize(0.2f, 0.1f);

		mCurve_UI = new StaticObject(mCamera);		//Mouse
		mCurve_UI->mSprite->SetTexture(mMouseTex[1]);
		mCurve_UI->SetSize(0.25f, 0.15f);

		mPause_KeyUI = new StaticObject(mCamera);		//Escape
		mPause_KeyUI->mSprite->SetTexture(mEscape_KeyTex[0]);
		mPause_KeyUI->SetSize(0.2f, 0.1f);

		//イベントUI画像の読み込み
		mIvent_UI = new StaticObject(mCamera);
		mIvent_UI->mSprite->SetTexture(mDogIvent_KeyTex);	//最初は犬のイベントから
		mIvent_UI->SetSize(2.0f, 1.8f);
		mIvent_UI->mSprite->mColor.a = 0.0f;			//最初は透明にしておく

	}

}

//<><><><><><><><><><><><><><><><><><>
// 関数名：ButtonLoad
// 役割：ボタン入力の初期化
//<><><><><><><><><><><><><><><><><><>
void Tutorial::ButtonLoad()
{


	{
		//イベントUI画像の読み込み
		mIvent_UI = new StaticObject(mCamera);
		mIvent_UI->mSprite->SetTexture(mDogIvent_ButtonTex);	//最初は犬のイベントから
		mIvent_UI->SetSize(2.0f, 1.8f);
		mIvent_UI->mSprite->mColor.a = 0.0f;			//最初は透明にしておく

		mWalk_KeyUI = new StaticObject(mCamera);	//スティック
		mWalk_KeyUI->mSprite->SetTexture(mStickTex[0]);
		mWalk_KeyUI->SetSize(0.2f, 0.1f);

		mSet_KeyUI = new StaticObject(mCamera);		//Bボタン
		mSet_KeyUI->mSprite->SetTexture(mB_ButtonTex[0]);
		mSet_KeyUI->SetSize(0.2f, 0.1f);

		mAngle_KeyUI = new StaticObject(mCamera);	//スティック
		mAngle_KeyUI->mSprite->SetTexture(mStickTex[1]);
		mAngle_KeyUI->SetSize(0.2f, 0.1f);

		mThrow_KeyUI = new StaticObject(mCamera);	//Bボタン
		mThrow_KeyUI->mSprite->SetTexture(mB_ButtonTex[1]);
		mThrow_KeyUI->SetSize(0.2f, 0.1f);

		mCurve_UI = new StaticObject(mCamera);		//トリガー
		mCurve_UI->mSprite->SetTexture(mTriggerTex[0]);
		mCurve_UI->SetSize(0.25f, 0.15f);

		mPause_KeyUI = new StaticObject(mCamera);		//XY
		mPause_KeyUI->mSprite->SetTexture(mXY_ButtonTex[0]);
		mPause_KeyUI->SetSize(0.2f, 0.1f);


	}
}

//<><><><><><><><><><><><><><><><><><>
// 関数名：Task_Set
// 役割：タスクバーの位置設定
// 引数：なし
//<><><><><><><><><><><><><><><><><><>
void Tutorial::Task_Set()
{

	if (mInput == 1) {

		int OldMouseX = MouseX;		//前回のマウス座標を取得
		int OldMouseY = MouseY;

		MouseX = Input_GetMousePosX();	//現在のマウス座標
		MouseY = Input_GetMousePosY();

		//投げる準備中
		if (mPlayer->mState == PLAYER_THROW && mFrisbee->mHold == HOLD_PLAYER) {
			mSet_KeyUI->mSprite->mColor.a = 0.5f;
			mSet_TaskUI->mSprite->mColor.a = 0.5f;
			
			//角度調整
			if (MouseX != OldMouseX || MouseY != OldMouseY) {
				mAngle_KeyUI->mSprite->mColor.a = 0.5f;
				mAngle_TaskUI->mSprite->mColor.a = 0.5f;
			}
			else {
				mAngle_KeyUI->mSprite->mColor.a = 1.0f;
				mAngle_TaskUI->mSprite->mColor.a = 1.0f;
			}

		}
		else {
			mSet_KeyUI->mSprite->mColor.a = 1.0f;
			mSet_TaskUI->mSprite->mColor.a = 1.0f;
			//歩いている時
			if ((Input_GetKeyDown('W') || Input_GetKeyDown('A') || Input_GetKeyDown('S') || Input_GetKeyDown('D')) && mFrisbee->mState != FRISBEE_FRY) {
				mWalk_KeyUI->mSprite->mColor.a = 0.5f;
				mWalk_TaskUI->mSprite->mColor.a = 0.5f;
			}
			else {
				mWalk_KeyUI->mSprite->mColor.a = 1.0f;
				mWalk_TaskUI->mSprite->mColor.a = 1.0f;
			}
		}

		//投げた時
		if (mPlayer->mState == PLAYER_THROW && mFrisbee->mState == FRISBEE_FRY) {
			mThrow_KeyUI->mSprite->mColor.a = 0.5f;
			mThrow_TaskUI->mSprite->mColor.a = 0.5f;
		}
		else {
			mThrow_KeyUI->mSprite->mColor.a = 1.0f;
			mThrow_TaskUI->mSprite->mColor.a = 1.0f;
		}

		//カーブ中
		if ((Input_GetKeyDown(VK_RBUTTON) || Input_GetKeyDown(VK_LBUTTON)) && mFrisbee->mState == FRISBEE_FRY) {

			mCurve_UI->mSprite->mColor.a = 0.5f;
			mCurve_TaskUI->mSprite->mColor.a = 0.5f;
		}
		else {
			mCurve_UI->mSprite->mColor.a = 1.0f;
			mCurve_TaskUI->mSprite->mColor.a = 1.0f;
		}
	}
	else {


		//投げる準備中
		if (mPlayer->mState == PLAYER_THROW && mFrisbee->mHold == HOLD_PLAYER) {
			mSet_KeyUI->mSprite->mColor.a = 0.5f;
			mSet_TaskUI->mSprite->mColor.a = 0.5f;
		
			//角度調整
			if (Input_GetLeftStick_X() != 0 || Input_GetLeftStick_Y() != 0 && mFrisbee->mState != FRISBEE_FRY) {
				mAngle_KeyUI->mSprite->mColor.a = 0.5f;
				mAngle_TaskUI->mSprite->mColor.a = 0.5f;
			}
			else {
				mAngle_KeyUI->mSprite->mColor.a = 1.0f;
				mAngle_TaskUI->mSprite->mColor.a = 1.0f;
			}

			mWalk_KeyUI->mSprite->mColor.a = 1.0f;
			mWalk_TaskUI->mSprite->mColor.a = 1.0f;

		}
		else {
			mSet_KeyUI->mSprite->mColor.a = 1.0f;
			mSet_TaskUI->mSprite->mColor.a = 1.0f;
			mAngle_KeyUI->mSprite->mColor.a = 1.0f;
			mAngle_TaskUI->mSprite->mColor.a = 1.0f;

			//歩いている時
			if ((Input_GetLeftStick_X() != 0 && Input_GetLeftStick_Y() != 0) && mFrisbee->mState != FRISBEE_FRY) {
				mWalk_KeyUI->mSprite->mColor.a = 0.5f;
				mWalk_TaskUI->mSprite->mColor.a = 0.5f;
			}
			else {
				mWalk_KeyUI->mSprite->mColor.a = 1.0f;
				mWalk_TaskUI->mSprite->mColor.a = 1.0f;
			}

		}

		//投げた時
		if (mPlayer->mState == PLAYER_THROW && mFrisbee->mState == FRISBEE_FRY) {
			mThrow_KeyUI->mSprite->mColor.a = 0.5f;
			mThrow_TaskUI->mSprite->mColor.a = 0.5f;
		}
		else {
			mThrow_KeyUI->mSprite->mColor.a = 1.0f;
			mThrow_TaskUI->mSprite->mColor.a = 1.0f;
		}

		//カーブ中
		if ((Input_GetRTButton() > 0 || Input_GetLTButton() > 0) && mFrisbee->mState == FRISBEE_FRY) {

			mCurve_UI->mSprite->mColor.a = 0.5f;
			mCurve_TaskUI->mSprite->mColor.a = 0.5f;
		}
		else {
			mCurve_UI->mSprite->mColor.a = 1.0f;
			mCurve_TaskUI->mSprite->mColor.a = 1.0f;
		}

	}
	

	//UIの配置
	{
		mWalk_KeyUI->mSprite->mCenter.x = mBackGround->mSprite->mCamera.x - 1.24f;
		mWalk_KeyUI->mSprite->mCenter.y = mBackGround->mSprite->mCamera.y + 0.7f;

		mSet_KeyUI->mSprite->mCenter.x = mBackGround->mSprite->mCamera.x - 1.23f;
		mSet_KeyUI->mSprite->mCenter.y = mBackGround->mSprite->mCamera.y + 0.58f;

		mAngle_KeyUI->mSprite->mCenter.x = mBackGround->mSprite->mCamera.x - 1.23f;
		mAngle_KeyUI->mSprite->mCenter.y = mBackGround->mSprite->mCamera.y + 0.46f;

		mThrow_KeyUI->mSprite->mCenter.x = mBackGround->mSprite->mCamera.x - 1.23f;
		mThrow_KeyUI->mSprite->mCenter.y = mBackGround->mSprite->mCamera.y + 0.34f;

		mCurve_UI->mSprite->mCenter.x = mBackGround->mSprite->mCamera.x - 1.23f;
		mCurve_UI->mSprite->mCenter.y = mBackGround->mSprite->mCamera.y + 0.22f;

		mPause_KeyUI->mSprite->mCenter.x = mBackGround->mSprite->mCamera.x + 0.9f;
		mPause_KeyUI->mSprite->mCenter.y = mBackGround->mSprite->mCamera.y - 0.945f;

		mWalk_KeyUI->Update();
		mSet_KeyUI->Update();
		mAngle_KeyUI->Update();
		mThrow_KeyUI->Update();
		mCurve_UI->Update();
		mPause_KeyUI->Update();
	}
	{
		mWalk_TaskUI->mSprite->mCenter.x = mBackGround->mSprite->mCamera.x - 1.0f;
		mWalk_TaskUI->mSprite->mCenter.y = mBackGround->mSprite->mCamera.y + 0.7f;

		mSet_TaskUI->mSprite->mCenter.x = mBackGround->mSprite->mCamera.x - 1.0f;
		mSet_TaskUI->mSprite->mCenter.y = mBackGround->mSprite->mCamera.y + 0.58f;

		mAngle_TaskUI->mSprite->mCenter.x = mBackGround->mSprite->mCamera.x - 1.0f;
		mAngle_TaskUI->mSprite->mCenter.y = mBackGround->mSprite->mCamera.y + 0.46f;

		mThrow_TaskUI->mSprite->mCenter.x = mBackGround->mSprite->mCamera.x - 1.0f;
		mThrow_TaskUI->mSprite->mCenter.y = mBackGround->mSprite->mCamera.y + 0.34f;

		mCurve_TaskUI->mSprite->mCenter.x = mBackGround->mSprite->mCamera.x - 1.0f;
		mCurve_TaskUI->mSprite->mCenter.y = mBackGround->mSprite->mCamera.y + 0.22f;

		mPauseUI->mSprite->mCenter.x = mBackGround->mSprite->mCamera.x + 1.0f;
		mPauseUI->mSprite->mCenter.y = mBackGround->mSprite->mCamera.y - 0.945f;

		mWalk_TaskUI->Update();
		mSet_TaskUI->Update();
		mAngle_TaskUI->Update();
		mThrow_TaskUI->Update();
		mCurve_TaskUI->Update();
		mPauseUI->Update();
	}

}

//<><><><><><><><><><><><><><><><><><>
// 関数名：Ivent_Set
// 役割：イベントの開始処理
// 引数：イベント番号(1:Dog 2:Cat)
//<><><><><><><><><><><><><><><><><><>
Ivent Tutorial::Ivent_Set(Ivent IventNum)
{
	if (mInput == 1) {
		//犬のイベント
		if (IventNum == DOG_IVENT) {
			mIvent_UI->mSprite->SetTexture(mDogIvent_KeyTex);
			if (mIvent_UI->mSprite->mColor.a >= 1.0f) {
				if (Input_GetKeyTrigger(VK_RETURN)) {	//エンターキーで表示終了
					mIvent_UI->mSprite->mColor.a = 0.0f;
					return IVENT_END;
				}
				else {
					return DOG_IVENT;
				}
			}
			else {
				mIvent_UI->mSprite->mColor.a += 0.01f * gDeltaTime;		//α値をあげて段々表示する
				return DOG_IVENT;

			}
		}
		//猫のイベント
		if (IventNum == CAT_IVENT) {
			mIvent_UI->mSprite->SetTexture(mCatIvent_KeyTex);
			if (mIvent_UI->mSprite->mColor.a >= 1.0f) {
				if (Input_GetKeyTrigger(VK_RETURN)) {	//エンターキーで表示終了
					mIvent_UI->mSprite->mColor.a = 0.0f;
					return IVENT_END;
				}
				else {
					return CAT_IVENT;
				}
			}
			else {
				mIvent_UI->mSprite->mColor.a += 0.001f * gDeltaTime;		//α値をあげて段々表示する
				return CAT_IVENT;
			}
		}
	}
	else {
		//犬のイベント
		if (IventNum == DOG_IVENT) {
			mIvent_UI->mSprite->SetTexture(mDogIvent_ButtonTex);
			if (mIvent_UI->mSprite->mColor.a >= 1.0f) {
				if (Input_GetButtonTrigger(B)) {	//エンターキーで表示終了
					mIvent_UI->mSprite->mColor.a = 0.0f;
					return IVENT_END;
				}
				else {
					return DOG_IVENT;
				}
			}
			else {
				mIvent_UI->mSprite->mColor.a += 0.01f * gDeltaTime;		//α値をあげて段々表示する
				return DOG_IVENT;

			}
		}
		//猫のイベント
		if (IventNum == CAT_IVENT) {
			mIvent_UI->mSprite->SetTexture(mCatIvent_ButtonTex);
			if (mIvent_UI->mSprite->mColor.a >= 1.0f) {
				if (Input_GetButtonTrigger(B)) {	//エンターキーで表示終了
					mIvent_UI->mSprite->mColor.a = 0.0f;
					return IVENT_END;
				}
				else {
					return CAT_IVENT;
				}
			}
			else {
				mIvent_UI->mSprite->mColor.a += 0.001f * gDeltaTime;		//α値をあげて段々表示する
				return CAT_IVENT;
			}
		}
	}
}

//<><><><><><><><><><><><><><><><><><>
// 関数名：Hit
// 役割：あたり判定
//<><><><><><><><><><><><><><><><><><>
void Tutorial::Hit()
{

	//成功範囲で犬が(´；ω；`)ｳｩｩ
	if (mDog->mCatchArea->CheckHit(mFrisbee->mCircle) && mFrisbee->mState == FRISBEE_FRY) {
		fDogCryTime += gDeltaTime;
		//5秒に一回鳴く
		if (fDogCryTime > 0.4f * 1000) {
			Play(SOUND_LABEL_SE010);
			fDogCryTime = 0.0f;
		}
	}

	//--------------------------------------
		//汚れの当たり判定
		//--------------------------------------
	for (int i = 0; i < STAGE_HIGHT; i++) {
		for (int j = 0; j < STAGE_WIDTH; j++) {

			//----------------------------
			//フリスビーと汚れの当たり
			//----------------------------

			// 犬と汚れ
			if (mDog->mCircle->CheckHit(mFloor->mDirt[i][j]->mHitSpuare) && mDog->mState == DOG_RUN)
			{
				mFloor->mBubble[i][j]->BabbleSet(mFloor->mDirt[i][j]->mSprite->mCenter);
				mFloor->mDirt[i][j]->mHitDog = true;
			}

			//----------------------
			//猫と汚れの当たり
			//----------------------
			if (mCat->mHit->CheckHit(mFloor->mDirt[i][j]->mHitSpuare) == true) {
				if (mFloor->mDirt[i][j]->active)
				{	 //床が汚れていたら
					mCat->SetDirtState(CatDirtState::DIRT);
				}
				else if(mCat->Appearance) //床が汚れていなかったら
				{
					mFloor->mDirt[i][j]->SetActive(true);
				}
			}

			//寝転んだ時の汚れ
			if (mCat->mLieDownHit->CheckHit(mFloor->mDirt[i][j]->mHitSpuare) == true)
			{
				if (mFloor->mDirt[i][j]->active)
				{	//床が汚れていたら
					mCat->SetDirtState(CatDirtState::DIRT);
				}
				else if (mCat->Appearance)//床が汚れていなかったら
				{
					mFloor->mDirt[i][j]->SetActive(true);
				}
			}

			//カメラ変数を独自で持っているため毎回座標を更新している
			mFloor->mDirt[i][j]->mSprite->mCamera = mBackGround->mSprite->mCamera;

			mMapInfo[i][j] = mFloor->mDirt[i][j]->active;
			mFloor->SetDirtTex(mMapInfo, i, j);	//汚れテクスチャ

		}
	}

	//---------------------------
	//プレイヤーが猫に近づいた時
	//---------------------------
	//プレイヤーとの距離を求める
	float Distance = sqrt(sqr(mPlayer->mAnimObject->mCenter.x - mCat->mAnimObject->mCenter.x)
		+ sqr(mPlayer->mAnimObject->mCenter.y - mCat->mAnimObject->mCenter.y));

	if (Distance < 1.0f && mCat->GetState() == CatState::WALK && mCat->GetState() != CatState::LIEDOWN)
	{//一定距離近づいたら待機
		mCat->ChangeState(CatState::WAIT);
	}
	if (Distance < 0.5f && mCat->GetState() == CatState::WAIT)
	{//近づきすぎたら走り回る
		mCat->ChangeState(CatState::RUN);
	}
	if (Distance > 1.5f && mCat->GetState() == CatState::RUN)
	{//プレイヤーから離れたら歩く
		mCat->ChangeState(CatState::WALK);
	}


	//-----------------
	//障害物の当たり
	//-----------------

	for (int i = 0; i < BLOCKMAX; i++)

	{
		//猫との当たり
		if (mCat->mHit->CheckHit(mBlockHit[i]))
		{
			mCat->ChangeState(CatState::JUMP);
		}
		else if (mCat->GetState() == CatState::JUMP) {
			mCat->ChangeState(CatState::WALK);

		}

		//フリスビーとの当たり
		if ((mFrisbee->mCircle->CheckHit(mBlockHit[i])
			&& mFrisbee->mState == FRISBEE_FRY))
		{
			mFrisbee->ChangeState(FRISBEE_DROP);
		}

		//プレイヤーとの当たり
		if (mPlayer->mHit->CheckHit(mBlockHit[i]))
		{
			mPlayer->SetResistance(mBlock[i]->mSprite->mCenter);
		}
		if (mPlayer->mHit->CheckHit(mBlockHit[1]))
		{
			mPlayer->SetResistance(mBlock4->mSprite->mCenter);
		}
		if (mDog->mHit->CheckHit(mBlockHit[1]))
		{
			mDog->SetResistance(mBlock4->mSprite->mCenter);
		}

		//犬との当たり
		if (mDog->mHit->CheckHit(mBlockHit[i]))
		{
			mDog->SetResistance(mBlock[i]->mSprite->mCenter);
		}
		mBlock[i]->Update();
	}

	mBlock4->Update();
}

//<><><><><><><><><><><><><><><><><><>
// 関数名：Catch
// 役割：フリスビーのキャチ
//<><><><><><><><><><><><><><><><><><>
void Tutorial::Catch()
{
	if ((Input_GetButtonTrigger(B) || Input_GetKeyTrigger(VK_SPACE)) && mDogIvent_State == IVENT_END)
	{

		//泡を消す
		mFloor->OffBubble();
		VibrationTime = 0.5f * 1000;	//振動時間を設定

		// 成功	
		if (mDog->mCatchArea->CheckHit(mFrisbee->mCircle) && mDog->mState != DOG_BE_CARRYED) {

			if (mCat->Appearance == false) {
				mCat->SetAppearance(true);	//猫があらわれる
			}

			if (GetSoundState(SOUND_LABEL_SE035) == FALSE)
			{
				Play(SOUND_LABEL_SE035);
			}


			//猫がきれいになる
			if (mDog->mCatchBubbleArea->CheckHit(mCat->mHit)) {	//猫がいたら
				Input_SetVibration(40000, 40000);	//振動させる
				if (GetSoundState(SOUND_LABEL_SE005) == FALSE)
				{
					Play(SOUND_LABEL_SE005);
				}

				mCat->nDirtState = CatDirtState::CLEARN;
				mCat->SetAppearance(false);
				mDog->mCatchBubbleArea->mRadius = 0.5f;	//犬の泡あたり判定の半径
			}
			else
			{
				Stop(SOUND_LABEL_SE005);
			}

			if (!mDog->mCatchBubbleArea->CheckHit(mCat->mHit)) {	//猫がいなかったら
				Input_SetVibration(5000, 5000);	//振動させる
				mDog->mCatchBubbleArea->mRadius = 0.25f;	//犬の泡あたり判定の半径
			}

			for (int i = 0; i < STAGE_HIGHT; i++) {
				for (int j = 0; j < STAGE_WIDTH; j++) {

					if (mDog->mCatchBubbleArea->CheckHit(mFloor->mDirt[i][j]->mHitSpuare))
					{
						mFloor->mDirt[i][j]->mHitDog = true;

					}
				}
			}

			mFrisbee->ChangeState(FRISBEE_HOLD);
			mFrisbee->Catch(HOLD_DOG);
			mCat->SetTarget(NULL);

			mDog->SetTarget(&mPlayer->mAnimObject->mCenter);// プレイヤーに向かう
			mDog->ChangeState(DOG_RETURN);
			mFloor->Clean();
		}
		else
		{
			// ミス
			mFrisbee->ChangeState(FRISBEE_DROP);
			mCat->SetTarget(NULL);

		}
	}
}

//<><><><><><><><><><><><><><><><><><>
// 関数名：Update
// 役割：更新
//<><><><><><><><><><><><><><><><><><>
void Tutorial::Update()
{


	//ミニマップ表示されていたら他の更新は呼ばない
	if (mMiniMap->active) {
		mMiniMap->Update();
	}
	else {

		mBackGround->Update();
		mFloor->Update();		//床の更新

		//-------------------------------
		//フリスビーの処理
		//-------------------------------
		if (mPlayer->mState == PLAYER_THROW && mFrisbee->mHold != HOLD_DOG)
		{
			if (mFrisbee->mState == FRISBEE_FRY)
			{
				mCat->SetTarget(&mFrisbee->mSprite->mCenter);		//猫が追いかける

				if (mDog->mState != DOG_BE_CARRYED)// アヒルにつかまっていない時
				{
					mDog->SetTarget(&mFrisbee->mSprite->mCenter);		// フリスビーを追いかける
				}
			}
			else if (!(mDog->mCircle->CheckHit(mPlayer->mCircle)))	// 
			{
				mCat->SetTarget(NULL);
				if (mDog->mState != DOG_BE_CARRYED)// アヒルにつかまっていない時
				{
					mDog->SetTarget(&mPlayer->mAnimObject->mCenter);	// プレイヤーに向かう
				}
			}
			else
			{
				if (mDog->mState != DOG_BE_CARRYED)// アヒルにつかまっていない時
				{
					mDog->ChangeState(DOG_WAIT);
				}
			}

			
		}

		
		//猫がはたき落とす
		if (mCat->mBlockAreaHit->CheckHit(mFrisbee->mCircle) && mFrisbee->mState == FRISBEE_FRY) {
			mFrisbee->ChangeState(FRISBEE_DROP);
			mFrisbee->Catch(DONT_HOLD);
			mCat->SetTarget(NULL);
		}


		// キャッチできるかどうか
		if (mDog->mMissArea->CheckHit(mFrisbee->mCircle) && mFrisbee->mState == FRISBEE_FRY)
		{
			
			// 待つ
			if (mDog->mCircle->CheckHit(mFrisbee->mCircle)){
				mDog->ChangeState(DOG_NONE);	}
			else{
				mDog->ChangeState(DOG_RUN);		
			}

			Catch();

		}

		//成功する範囲に入ったらイベントを始める
		if (mDog->mCatchArea->CheckHit(mFrisbee->mCircle) && mDog->mState != DOG_BE_CARRYED 
			&& mFrisbee->mState == FRISBEE_FRY && mDogIvent_State != IVENT_END) {
			mDogIvent_State = Ivent_Set(DOG_IVENT);
		}

		VibrationTime -= gDeltaTime;
		if (VibrationTime < 0.0f) {
			Input_SetVibration(0, 0);
		}

		if (mFrisbee->mState == FRISBEE_DROP)
		{
			//泡を消す
			mFloor->OffBubble();
			mFloor->Miss();
		}

		// プレイヤーにフリスビーを返す
		if (mDog->mState == DOG_RETURN && mDog->mCircle->CheckHit(mPlayer->mCircle))
		{
			mDog->ChangeState(DOG_WALK);
			mFrisbee->Catch(HOLD_PLAYER);
			mPlayer->ChangeState(PLAYER_MOVE);
		}
		if (mFrisbee->mState == FRISBEE_DROP && mDog->mState != DOG_BE_CARRYED)
		{
			mDog->ChangeState(DOG_WALK);
		}

		// 犬が滑るか
		if (mFloor->OnSlipperyFloor(mDog->mCircle))
		{
			mDog->mSlip = true;
		}

		// プレイヤーが滑るか
		if (mFloor->OnSlipperyFloor(mPlayer->mCircle))
		{
			mPlayer->Slip(); if (mSound[0] == false)
			{
				Play(SOUND_LABEL_SE021);
				mSound[0] = true;
			}
		}
		else
		{
			Stop(SOUND_LABEL_SE021);
			mSound[0] = false;
		}

		//mCatMark->mSprite->mCenter.y = mBackGround->mSprite->mCamera.y + 0.9f;

		if (mCat->Appearance) 
		{	
			mCatMark->mSprite->mCenter.x = mCat->mAnimObject->mCenter.x;
			mCatMark->mSprite->mCenter.y = mCat->mAnimObject->mCenter.y;

			bool Active = false;// マーカーを表示するための変数

			if(mCat->mSprite->mCenter.x > mCamera.x + 1.25f)// 右
			{
				Active = true;
				mCatMark->mSprite->mCenter.x = mCamera.x + 1.15f;
			}
			else if(mCat->mSprite->mCenter.x < mCamera.x - 1.25)// 左
			{
				Active = true;
				mCatMark->mSprite->mCenter.x = mCamera.x - 1.15f;
			}
			
			if(mCat->mSprite->mCenter.y > mCamera.y + 1.1f)// 上
			{
				Active = true;
				mCatMark->mSprite->mCenter.y = mCamera.y + 0.9f;
			}
			else if(mCat->mSprite->mCenter.y < mCamera.y - 1.1f)// 下
			{
				Active = true;
				mCatMark->mSprite->mCenter.y = mCamera.y - 0.9;
			}
			mCatMark->SetActive(Active);	//マーカーを表示
			
		}
		else
		{
			mCatMark->SetActive(false);	//マーカーを非表示
		}

		Hit();	//あたり判定
		//イベント中はキャラの更新は呼ばない
		if (mDogIvent_State == DOG_IVENT || mCatIvent_State == CAT_IVENT) {
			mIvent_UI->mSprite->mCenter.x = mBackGround->mSprite->mCamera.x;
			mIvent_UI->mSprite->mCenter.y = mBackGround->mSprite->mCamera.y;
		}
		if ((mDogIvent_State == NONE_IVENT || mDogIvent_State == IVENT_END) &&
			(mCatIvent_State == NONE_IVENT || mCatIvent_State == IVENT_END))
		{
			if (mCat->Appearance) {
				mCat->Update();
			}
			mPlayer->Update();
			mFrisbee->Update();

			mDog->Update();			//犬の更新
		}

		// 落ちたフリスビーとプレイヤーのあたり判定
		if (mFrisbee->mCircle->CheckHit(mPlayer->mCircle)
			&& mFrisbee->mState == FRISBEE_DROP)
		{
			mFrisbee->ChangeState(FRISBEE_HOLD);
			mFrisbee->Catch(HOLD_PLAYER);
		}

		//猫が出現している時だけ更新
		if (mCat->Appearance && mCatIvent_State != IVENT_END) {
			mCatIvent_State = Ivent_Set(CAT_IVENT);
			if (GetSoundState(SOUND_LABEL_SE004) == FALSE && mSound[1] == false)
			{
				Play(SOUND_LABEL_SE004);
				mSound[1] = true;
			}
		}
		else
		{
			mSound[1] = false;
		}

		mIvent_UI->Update();
	
		for (int i = 0; i < BABBLMAX; i++) {
			mBabble[i]->Update();
		}
	}

	

	DrawMiniMap();	//ミニマップ表示
	CameraSet();	//カメラの制御

	//制限時間が0以下でスコア受け渡ししてシーン遷移(GameMain.cpp)
	if (fTime < 0) {
		TimeActive = false;
	}

	Task_Set();

	mCatMark->Update();	//猫のマーカー
	
}

//<><><><><><><><><><><><><><><><><><>
// 関数名：Draw
// 役割：描画
//<><><><><><><><><><><><><><><><><><>
void Tutorial::Draw()
{
	mBackGround->Draw();
	mFloor->Draw();				//床

	for (int i = 0; i < BLOCKMAX; i++)
	{
		mBlock[i]->Draw();
	}

	mBlock4->Draw();

	mFrisbee->mShadow->Draw();	//フリスビー
	mDog->Draw();				//犬
	if (mCat->Appearance == true) {
		mCat->Draw();				//猫
	}

	mFrisbee->Draw();
	

	mPlayer->Draw();			//プレイヤー
	mPlayer->mMark->Draw();

	for (int i = 0; i < BABBLMAX; i++)
	{	//泡
		mBabble[i]->Draw();
	}

	for (int i = 0; i < 4; i++)
	{	//時間
		mTime[i]->Draw();
	}

	mMiniMap->Draw();			//ミニマップ
	mCatMark->Draw();

	mWalk_TaskUI->Draw();
	mSet_TaskUI->Draw();
	mAngle_TaskUI->Draw();
	mThrow_TaskUI->Draw();
	mCurve_TaskUI->Draw();
	mPauseUI->Draw();

	mWalk_KeyUI->Draw();
	mSet_KeyUI->Draw();
	mAngle_KeyUI->Draw();
	mThrow_KeyUI->Draw();
	mCurve_UI->Draw();
	mPause_KeyUI->Draw();
	mIvent_UI->Draw();
}
