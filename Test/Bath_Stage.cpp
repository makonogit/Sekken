#include "Bath_Stage.h"

bool DuckInfo = true;
extern DWORD gDeltaTime;

Bath_Stage::Bath_Stage()
{
	//マップ情報の設定
	int MapInfo[STAGE_HIGHT][STAGE_WIDTH] =
	{
		{0,0,1,1,1,0,1,1,1,0,0,1,1,0,0,1,1,1,1,1,0,0,0,0,1,1,0,0,1,0,1,0,1,1,1,1,1,1,1,0},
		{1,1,1,1,1,1,1,1,0,0,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,1,1,1,1,0},
		{1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,0,0,1,1,1,1,0},
		{1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,0,1,1,1,0,0,0,1,1,1,1,1,1,0,0,0,1,0,1,1,0},
		{1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,0},
		{1,1,0,1,0,0,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,0,0,0,0,1,1,1,1,1,1,1,0,0,0,0,0,0,0},
		{1,1,0,1,1,0,1,1,1,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0},
		{1,1,1,0,0,1,0,0,0,1,1,1,1,1,1,1,0,1,0,0,1,1,1,0,1,1,1,0,0,1,1,0,0,0,0,0,0,0,0,0},
		{1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,0,1,0,0,1,1,1,1,0,0,1,1,0,1,1,0,0,0,0,0,0,0,0,0},
		{0,1,1,1,1,1,1,1,1,0,0,0,1,1,1,0,0,1,1,1,1,1,0,1,1,0,0,1,1,1,1,1,0,0,0,0,0,0,0,0},
		{0,1,1,1,1,1,1,0,0,0,0,0,0,1,1,1,1,0,0,0,1,1,0,0,1,1,0,1,1,1,1,1,1,1,0,0,0,0,0,0},
		{0,1,1,1,1,1,1,0,0,0,0,0,0,0,0,1,1,1,0,0,1,0,0,0,1,1,1,1,1,0,0,1,0,1,1,1,1,1,1,0},
		{1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,1,0,0,1,1,1,1,1,1,1,0,1,1,1,1,1,1,0},
		{0,1,1,1,1,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0},
		{1,1,1,0,0,0,0,0,0,0,0,0,0,1,1,1,1,0,1,0,0,0,1,0,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1},
		{1,1,1,0,0,0,0,0,0,0,0,0,0,1,1,0,1,1,1,0,0,0,0,0,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1},
		{1,1,1,0,0,0,0,0,0,0,0,1,1,1,0,0,1,1,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,0,0,1,1,1,1,1},
		{0,1,1,0,0,0,0,0,0,1,1,1,1,1,0,1,1,0,1,0,0,0,0,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,0},
		{1,1,1,1,0,0,0,0,1,1,1,0,0,0,1,1,1,1,1,1,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
		{1,0,1,1,1,1,1,1,1,1,0,0,1,0,1,0,1,1,0,1,1,0,0,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,0},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,0,0,1,1,1,1,0,0,1,0,1,0,1,1,1,1,1,1,1},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,0,1,1,1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1,1,1,1},
		{1,0,1,1,1,1,1,1,1,1,1,0,0,0,1,1,0,0,0,0,0,0,1,1,1,1,1,0,0,0,0,1,0,1,1,1,1,1,1,1},
		{1,0,1,1,1,1,1,1,1,1,1,0,0,0,1,1,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,1,1,1,1,1,1,1,1,0},
		{0,1,1,0,1,1,1,1,1,1,1,1,1,0,1,1,0,0,0,0,0,0,0,0,1,1,1,1,0,1,0,1,0,1,1,1,1,1,1,0},
		{0,0,1,0,1,1,1,1,1,1,1,0,0,0,1,1,0,0,0,0,0,0,0,0,1,1,1,1,1,0,0,1,0,1,1,1,1,1,1,0},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,0,0,0,0,0,0,0,0,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1},
		{0,1,1,0,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,0,0,0,0,0,0,1,0,1,1,1,0,1,1,1,1,1,1,1,1,0},
		{0,1,0,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,0,0,0,0,1,1,1,0,1,1,0,1,1,1,0,1,0,0,1,0},
		{0,0,1,0,1,1,1,1,1,1,1,0,0,0,0,1,1,0,0,0,0,0,0,0,1,1,1,0,0,1,0,1,1,0,0,1,0,0,0,1},
	};

	mCamera = { 0.0f,0.0f,1.0f };
	LoadTexture(L"assets/images/BackGround/Stage/Bath_Bg.png", &mBgTex);	//背景テクスチャ
	LoadTexture(L"assets/images/Block/Soap_dish.png", &mSoapTex);			//石鹼
	LoadTexture(L"assets/images/Block/Bottle.png", &mBottleTex);		//ボトル
	LoadTexture(L"assets/images/Block/Sponge.png", &mSpongeTex);	//スポンジ
	LoadTexture(L"assets/images/UI/Duck.png", &mDuckTex);			//アヒル説明
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

	LoadTexture(L"assets/images/Time/Time_Back2.png", &mTimeBackTex);

	mTimeBack = new StaticObject(mCamera);
	mTimeBack->mSprite->SetTexture(mTimeBackTex);
	mTimeBack->SetSize(0.6f, 0.3f);
	mTimeBack->SetPosition(0.0f, 0.8f);

	mDuckUI = new StaticObject(mCamera);
	mDuckUI->mSprite->SetTexture(mDuckTex);
	mDuckUI->SetSize(2.0f, 1.8f);
	mDuckUI->SetActive(true);

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

	XMFLOAT2 SoapHit_gap = { 0.0f,0.1f };			//石鹸のあたり判定のずれ
	XMFLOAT2 BottleHit_gap = { 0.0f,0.0f };			//あたり判定のずれ
	XMFLOAT2 SpongeHit_gap = { 0.0f,0.0f };			//スポンジのあたり判定のずれ
	XMFLOAT2 SoapHit_Size = { 1.0f,0.9f };	//石鹸のあたりサイズ
	XMFLOAT2 BottleHit_Size = { 0.35f,1.3f };	//ボトルのあたりサイズ
	XMFLOAT2 SpongeHit_Size = { 0.55f,1.2f };	//スポンジのあたりサイズ

	for (int i = 0; i < BLOCKMAX; i++) {
		mBlock[i] = new StaticObject(mCamera);
		mBlock[i]->SetSize(1.0f, 2.0f);
	}

	//テクスチャ,座標セット
	mBlock[0]->mSprite->SetTexture(mSoapTex);	//石鹼
	mBlock[0]->SetPosition(1.5f, 1.0f);
	mBlock[0]->SetSize(1.0f, 2.0f);

	mBlock[1]->mSprite->SetTexture(mBottleTex);	//ボトル
	mBlock[1]->SetPosition(-1.3f, 0.2f);
	mBlock[1]->SetSize(1.0f, 1.5f);

	mBlock[2]->mSprite->SetTexture(mSpongeTex);	//スポンジ
	mBlock[2]->SetPosition(0.0f, -1.0f);
	mBlock[2]->SetSize(1.0f, 1.5f);

	mBlockHit[0] = new HitSquare(&mBlock[0]->mSprite->mCenter, SoapHit_Size, SoapHit_gap, 70);	//石鹼
	mBlockHit[1] = new HitSquare(&mBlock[1]->mSprite->mCenter, BottleHit_Size, BottleHit_gap, -25);			//ボトル
	mBlockHit[2] = new HitSquare(&mBlock[2]->mSprite->mCenter, SpongeHit_Size, SpongeHit_gap, 40);			//スポンジ

	LoadTexture(L"assets/images/Item/CatMark.png", &mCatMarkTex);		//猫のマーカー

	//猫のマーカー
	mCatMark = new StaticObject(mCamera);
	mCatMark->mSprite->SetTexture(mCatMarkTex);
	mCatMark->SetSize(0.2f, 0.2f);

	//背景の初期化
	mBackGround = new StaticObject(mCamera);
	mBackGround->mSprite->SetTexture(mBgTex);
	mBackGround->SetSize(5.6f, 4.0f);
	//時間
	for (int i = 0; i < 4; i++) {
		mTime[i] = new StaticObject(mCamera);
		mTime[i]->mSprite->SetTexture(mNumTex[0]);
		mTime[i]->SetSize(0.1f, 0.1f);
	}


	mFrisbee = new Frisbee(mCamera);
	mPlayer = new Player(mCamera, mFrisbee);	//プレイヤー
	mMiniMap = new MiniMap(mFloor->mDirt, mBlock);		//ミニマップ
	mCat = new Cat(mCamera);		//猫
	mDog = new Dog(mCamera);
	mDuck = new Duck(mCamera);

	mBGMSound = SOUND_LABEL_BGM005;
	Sound_Init(mBGMSound);
	Play(mBGMSound);
	SetVolume(mBGMSound,0.25f);
}

Bath_Stage::~Bath_Stage()
{
	Sound_Uninit(mBGMSound);
	delete mDuck;
	delete mFloor;
	delete mDog;
	delete mCat;
	delete mMiniMap;
	delete mPlayer;
	delete mFrisbee;

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

	for (int i = 0; i < 10; i++) {
		COM_SAFE_RELEASE(mNumTex[i]);
	}

	COM_SAFE_RELEASE(mTimeBackTex);
	COM_SAFE_RELEASE(mBgTex);
	COM_SAFE_RELEASE(mSoapTex);
	COM_SAFE_RELEASE(mBottleTex);
	COM_SAFE_RELEASE(mSpongeTex);
}

void Bath_Stage::Update()
{

	if (DuckInfo) {
		DuckInfoTime += gDeltaTime;
	}
	else {
		DuckInfoTime = 0.0f;
	}

	if (DuckInfoTime < 0.1f) {
		//20秒に1回猫が出現
		if (fCatTime >= 20.0f * 1000 && !mCat->Appearance) {
			mCat->SetAppearance(true);
			fCatTime = 0.0f;
		}
		mDuck->Update();
		Stage::Update();
	}
	else {
		mDuckUI->Update();
		if (Input_GetKeyTrigger(VK_RETURN) || Input_GetButtonTrigger(B)) {
			DuckInfo = false;
		}
	}
	// 障害物とアヒル
	for (int i = 0; i < BLOCKMAX; i++) {
		if (mDuck->mCircle->CheckHit(mBlockHit[i]))
		{
			mDuck->SetResistance(mBlock[i]->mSprite->mCenter);
		}
	}
	// 犬とアヒル
	if (mDuck->mCircle->CheckHit(mDog->mCircle) && mDuck->mState == DUCK_MOVE)
	{
		mDog->SetTarget(&mDuck->mAnimObject->mCenter);
		mDog->ChangeState(DOG_BE_CARRYED);// 運ばれる
		mDuck->ChangeState(DUCK_CARRY);// 運ぶ
		if (mFrisbee->mHold == HOLD_DOG)// 犬がフリスビーを持っていた時
		{
			mFrisbee->mSprite->mCenter = mDog->mAnimObject->mCenter;// 犬が捕まった位置に落とす
			mFrisbee->ChangeState(FRISBEE_DROP);
		}
	}
	// アヒルとフリスビー
	if (mDuck->mCircle->CheckHit(mFrisbee->mCircle) && mFrisbee->mState == FRISBEE_FRY)// 飛んでいるフリスビーにしか反応しない
	{
		mDog->ChangeState(DOG_WALK);
		mDuck->ChangeState(DUCK_CONFUSION);// 混乱する
		mFrisbee->ChangeState(FRISBEE_DROP);
	}
	// アヒルとプレイヤー
	if (mDuck->mCircle->CheckHit(mPlayer->mCircle))
	{
		mPlayer->SetResistance(mDuck->mAnimObject->mCenter);
	}
	
	
}

void Bath_Stage::Draw()
{
	Stage::Draw();
	mDuck->Draw();
	// アヒルよりプレイヤーが前の時
	if (mPlayer->mAnimObject->mCenter.y < mDuck->mAnimObject->mCenter.y)
	{
		mPlayer->Draw();
	}
	// 犬が捕まった時
	if (mDog->mState == DOG_BE_CARRYED)
	{
		mDog->Draw();
	}
	mFrisbee->Draw();
	if (DuckInfo) {
		mDuckUI->Draw();
	}
}
