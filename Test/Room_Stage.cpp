#include "Room_Stage.h"

bool RobotInfoFlg = true;	//ロボットの説明

extern DWORD gDeltaTime;
//<><><><><><><><><><><><><><><><><><>
// 関数名：Room_Stage
// 役割：コンストラクタ
//<><><><><><><><><><><><><><><><><><>
Room_Stage::Room_Stage()
{
	//マップ情報の設定
	int MapInfo[STAGE_HIGHT][STAGE_WIDTH] =
	{

		{0,0,1,0,0,1,1,1,1,1,0,0,0,0,1,0,1,1,1,1,1,1,0,1,0,1,0,0,1,1,1,1,1,1,1,1,0,0,0,0},
		{0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
		{1,0,1,1,1,1,0,0,0,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,1},
		{0,0,1,1,1,0,0,0,0,1,1,1,1,1,1,0,1,1,1,1,1,1,0,1,1,0,1,0,1,1,1,1,1,1,1,1,0,0,0,0},
		{0,1,1,1,0,0,0,0,0,0,1,0,1,1,1,1,1,1,1,1,1,1,0,1,0,1,1,1,1,1,1,1,1,1,1,1,0,0,0,1},
		{1,0,1,1,0,0,1,0,0,0,1,1,1,1,1,1,0,0,1,1,0,1,0,1,0,0,0,0,0,1,1,1,0,0,1,1,0,0,0,1},
		{0,0,1,1,1,0,1,0,0,0,0,0,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,0,0},
		{1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,1,1,0,1,1,1},
		{1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,0,0},
		{1,1,1,1,1,1,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,1,1,0,1,1,1},
		{1,1,1,1,1,1,0,0,1,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,1,1,0,1,1,1},
		{1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,1,1,0,1,1,1},
		{0,0,1,1,0,0,1,1,1,1,1,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,1,1,0,0,0,1},
		{1,0,1,1,0,0,1,1,1,1,1,1,0,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1},
		{1,0,1,1,0,1,1,1,1,1,1,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,1,1,1,1,0,1},
		{0,1,1,1,1,1,0,1,1,1,1,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1},
		{0,0,1,1,1,1,0,1,1,1,1,1,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,0,1},
		{1,1,1,1,0,1,1,1,1,1,1,1,1,0,1,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,1,0,1,1},
		{1,1,1,0,0,0,1,1,0,0,1,1,0,0,1,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1},
		{1,1,0,0,0,0,0,1,1,0,0,1,1,0,0,1,1,0,1,0,0,0,0,0,0,0,0,1,0,1,1,1,1,1,1,1,1,0,1,0},
		{1,1,0,0,0,0,0,1,1,0,0,0,1,1,0,1,1,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,0},
		{0,1,1,0,0,0,0,1,1,1,1,1,1,1,1,0,1,0,0,1,1,1,1,1,1,1,1,1,1,1,0,1,1,0,1,1,1,1,1,1},
		{0,1,1,0,0,0,0,1,1,1,1,1,1,0,1,1,0,0,0,1,1,0,0,0,0,0,0,0,1,1,0,1,1,0,1,1,0,0,1,0},
		{0,1,1,0,0,0,0,1,1,0,0,1,0,0,0,1,1,0,1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,0,1,1,0,0,1,0},
		{0,1,1,0,0,0,0,1,0,0,0,0,0,1,0,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,1,1,1,1,1,1,0,0,1,0},
		{0,1,1,0,0,0,0,1,0,0,0,1,0,0,0,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,1,1,1,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,1,1,1,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,1,1,1,1,0,1,1,1,1,1,1,0,0,0,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},

		
	};

	for (int i = 0; i < STAGE_HIGHT; i++) {
		for (int j = 0; j < STAGE_WIDTH; j++) {
			mMapInfo[i][j] = MapInfo[i][j];
		}
	}

	mCamera = { 0.0f,0.0f,1.0f };
	LoadTexture(L"assets/images/BackGround/Stage/Room_Stage.png", &mBgTex);		//背景テクスチャ
	LoadTexture(L"assets/images/Block/Shose.png", &mShoesTex);					//靴
	LoadTexture(L"assets/images/Block/Sneakers.png", &mSneakerShoesTex);		//スニーカー
	LoadTexture(L"assets/images/Block/Leather_shoes.png", &mLeatherShoesTex);	//革靴

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


	//ロボットの説明
	LoadTexture(L"assets/images/UI/Robotton.png", &mRobotInfoTex);

	RobotInfoUI = new StaticObject(mCamera);
	RobotInfoUI->mSprite->SetTexture(mRobotInfoTex);
	RobotInfoUI->SetSize(2.0f, 1.8f);


	//汚れの初期化
	mFloor = new Floor(mCamera,MapInfo);
	
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
	XMFLOAT2 ShoesHit_Size = { 0.25f,1.2f };	//靴のあたりサイズ

	for (int i = 0; i < BLOCKMAX; i++) {
		mBlock[i] = new StaticObject(mCamera);
		mBlock[i]->SetSize(1.0f, 1.5f);

		mBlockHit[i] = new HitSquare(&mBlock[i]->mSprite->mCenter, ShoesHit_Size, gap, 0.0f);
	}

	//テクスチャ,座標セット
	mBlock[0]->mSprite->SetTexture(mShoesTex);			//ヒール
	mBlock[0]->SetPosition(-1.2f, 1.1f);
	mBlockHit[0]->mAngle = -43 * PI;
	
	mBlock[1]->mSprite->SetTexture(mSneakerShoesTex);	//スニーカー
	mBlock[1]->SetPosition( 0.8f, -1.3f);
	mBlockHit[1]->mAngle = -155 * PI;

	mBlock[2]->mSprite->SetTexture(mLeatherShoesTex);	//革靴
	mBlock[2]->SetPosition(-1.7f,-1.0f);

	//あたり判定
	XMFLOAT2 RobotHit_gap = { 0.0f,0.0f };
	XMFLOAT2 RobotHit_Size = { 0.4f,0.6f };

	mRobot = new Robot(mCamera);
	mRobotHit = new HitSquare(&mRobot->mSprite->mCenter, RobotHit_Size, RobotHit_gap, 0.0f);

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
	mPlayer = new Player(mCamera,mFrisbee);	//プレイヤー
	mMiniMap = new MiniMap(mFloor->mDirt, mBlock);		//ミニマップ
	mCat = new Cat(mCamera);		//猫
	mDog = new Dog(mCamera);

	fCameraZoom = 0.0f;
	mBGMSound = SOUND_LABEL_BGM006;
	Sound_Init(mBGMSound);
	Play(mBGMSound);
	SetVolume(mBGMSound, 0.25f);
}

//<><><><><><><><><><><><><><><><><><>
// 関数名：~Room_Stage
// 役割：デストラクタ
//<><><><><><><><><><><><><><><><><><>
Room_Stage::~Room_Stage()
{
	Sound_Uninit(mBGMSound);
	delete RobotInfoUI;
	delete mFloor;
	delete mDog;
	delete mCat;
	delete mMiniMap;
	delete mPlayer;
	delete mFrisbee;
	delete mRobot;

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

	COM_SAFE_RELEASE(mRobotInfoTex);
	COM_SAFE_RELEASE(mTimeBackTex);
	COM_SAFE_RELEASE(mBgTex);
	COM_SAFE_RELEASE(mShoesTex);
	COM_SAFE_RELEASE(mSneakerShoesTex);
	COM_SAFE_RELEASE(mLeatherShoesTex);
}

//<><><><><><><><><><><><><><><><><><>
// 関数名：Update
// 役割：更新
//<><><><><><><><><><><><><><><><><><>
void Room_Stage::Update()
{

	if (RobotInfoFlg) {
		RobotInfoTime += gDeltaTime;
	}
	else {
		RobotInfoTime = 0.0f;
	}

	//一瞬アップデートしないと描画されない
	if (RobotInfoTime < 0.1f) {

		//30秒に1回猫が出現
		if (fCatTime >= 30.0f * 1000 && !mCat->Appearance) {
			mCat->SetAppearance(true);
			fCatTime = 0.0f;
		}

		Stage::Update();

		//ロボットとプレイヤーとの当たり
		if (mPlayer->mHit->CheckHit(mRobotHit))
		{
			mPlayer->SetResistance(mRobot->mSprite->mCenter);
		}

		//ロボットとフリスビーとの当たり
		if ((mFrisbee->mCircle->CheckHit(mRobotHit)
			&& mFrisbee->mState == FRISBEE_FRY))
		{
			mFrisbee->ChangeState(FRISBEE_DROP);
		}

		//ロボットと障害物の当たり
		for (int i = 0; i < BLOCKMAX; i++)
		{
			if (mBlockHit[i]->CheckHit(mRobotHit))
			{
				mRobot->mHit->active = true;
			}
		}

		mRobot->Update();
	}
	else {
		RobotInfoUI->Update();
		if (Input_GetKeyTrigger(VK_RETURN) || Input_GetButtonTrigger(B)) {
			RobotInfoFlg = false;
		}
	}
}

//<><><><><><><><><><><><><><><><><><>
// 関数名：Draw
// 役割：描画
//<><><><><><><><><><><><><><><><><><>
void Room_Stage::Draw()
{
	Stage::Draw();
	mRobot->Draw();

	if (RobotInfoFlg) {
		RobotInfoUI->Draw();
	}
}
