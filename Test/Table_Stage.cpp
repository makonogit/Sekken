#include "Table_Stage.h"

Table_Stage::Table_Stage()
{
	//マップ情報の設定
	int MapInfo[STAGE_HIGHT][STAGE_WIDTH] =
	{
	//					   1				   2				   3				   4
	//	 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0

		{0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
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
		{0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0},

	//					   1				   2				   3				   4
	//	 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0
	};

	for (int i = 0; i < STAGE_HIGHT; i++) {
		for (int j = 0; j < STAGE_WIDTH; j++) {
			mMapInfo[i][j] = MapInfo[i][j];
		}
	}

	mCamera = { 0.0f,0.0f,1.0f };
	LoadTexture(L"assets/images/BackGround/Stage/Room_Stage_1.png", &mBgTex);	//背景テクスチャ
	LoadTexture(L"assets/images/Block/Plate.png", &mPlateTex);			//皿
	LoadTexture(L"assets/images/Block/ChopStick.png", &mStickTex);	//お箸
	LoadTexture(L"assets/images/Block/Cup.png", &mCupTex);				//カップ

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

	XMFLOAT2 gap = { 0.0f,0.0f };			//あたり判定のずれ
	XMFLOAT2 Hit_Size = { 0.0f,0.0f };
	XMFLOAT2 StickHit_Size = { 0.05f,1.6f };	//お箸のあたりサイズ

	for (int i = 0; i < BLOCKMAX; i++) {
		mBlock[i] = new StaticObject(mCamera);
		mBlock[i]->SetSize(1.0f, 2.0f);
	}

	mBlockHit[0] = new HitSquare(&mBlock[0]->mSprite->mCenter, Hit_Size, gap, 0.0f);
	mBlockHit[1] = new HitSquare(&mBlock[0]->mSprite->mCenter, Hit_Size, gap, 0.0f);

	//テクスチャ,座標セット
	mBlock[0]->mSprite->SetTexture(mPlateTex);	//皿
	mBlock[0]->SetPosition(1.1f, -1.3f);
	mBlock[0]->SetSize(1.3f, 1.4f);
	// 円のあたり判定
	mBlockHitCircle[0] = new HitCircle(&mBlock[0]->mSprite->mCenter,0.6f);

	mBlock[1]->mSprite->SetTexture(mCupTex);	//カップ
	mBlock[1]->SetPosition(1.3f, 1.3f);
	mBlock[1]->SetSize(0.7f, 0.7f);
	// 円のあたり判定
	mBlockHitCircle[1] = new HitCircle(&mBlock[1]->mSprite->mCenter, 0.25f);
	

	mBlock[2]->mSprite->SetTexture(mStickTex);	//箸
	mBlock[2]->SetPosition(-1.4f, -1.1f);
	mBlock[2]->SetSize(1.4f, 1.8f);
	mBlockHit[2] = new HitSquare(&mBlock[2]->mSprite->mCenter, StickHit_Size, gap, 0.0f);


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
	mBGMSound = SOUND_LABEL_BGM007;
	Sound_Init(mBGMSound);
	Play(mBGMSound);
	SetVolume(mBGMSound, 0.3f);

}

Table_Stage::~Table_Stage()
{
	Sound_Uninit(mBGMSound);
	delete mFloor;
	delete mDog;
	delete mCat;
	delete mMiniMap;
	delete mPlayer;
	delete mFrisbee;

	for (int i = 0; i < 2; i++)
	{
		delete mBlockHitCircle[i];
	}

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
	COM_SAFE_RELEASE(mCupTex);
	COM_SAFE_RELEASE(mPlateTex);
	COM_SAFE_RELEASE(mStickTex);
}

void Table_Stage::Update()
{

	//-----------------
	//障害物の当たり
	//-----------------

	for (int i = 0; i < 2; i++)
	{
		//猫との当たり
		if (mCat->mHit->CheckHit(mBlockHitCircle[i]))
		{
			mCat->ChangeState(CatState::JUMP);
		}
		else if (mCat->GetState() == CatState::JUMP) {
			mCat->ChangeState(CatState::WALK);

		}

		//フリスビーとの当たり
		if ((mFrisbee->mCircle->CheckHit(mBlockHitCircle[i])
			&& mFrisbee->mState == FRISBEE_FRY))
		{
			mFrisbee->ChangeState(FRISBEE_DROP);
		}
		//プレイヤーとの当たり
		if (mPlayer->mHit->CheckHit(mBlockHitCircle[i]))
		{
			mPlayer->SetResistance(mBlock[i]->mSprite->mCenter);
		}
		//犬との当たり
		if (mDog->mHit->CheckHit(mBlockHitCircle[i]))
		{
			mDog->SetResistance(mBlock[i]->mSprite->mCenter);
		}
		mBlock[i]->Update();
	}
	//40秒に1回猫が出現
	if (fCatTime >= 40.0f * 1000 && !mCat->Appearance) {
		mCat->SetAppearance(true);
		fCatTime = 0.0f;
	}
	Stage::Update();
}

void Table_Stage::Draw()
{
	Stage::Draw();
}
