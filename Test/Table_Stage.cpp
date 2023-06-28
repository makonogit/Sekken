#include "Table_Stage.h"

Table_Stage::Table_Stage()
{
	//�}�b�v���̐ݒ�
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
	LoadTexture(L"assets/images/BackGround/Stage/Room_Stage_1.png", &mBgTex);	//�w�i�e�N�X�`��
	LoadTexture(L"assets/images/Block/Plate.png", &mPlateTex);			//�M
	LoadTexture(L"assets/images/Block/ChopStick.png", &mStickTex);	//����
	LoadTexture(L"assets/images/Block/Cup.png", &mCupTex);				//�J�b�v

	//���ԃe�N�X�`��
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


	//����̏�����
	mFloor = new Floor(mCamera, MapInfo);

	ClearNum = 0;

	//�A�̏�����
	for (int i = 0; i < BABBLMAX; i++) {
		mBabble[i] = new Babble(mCamera);
	}

	BabbleNum = 0;


	//----------------------
	//��Q���̏�����
	//---------------------

	XMFLOAT2 gap = { 0.0f,0.0f };			//�����蔻��̂���
	XMFLOAT2 Hit_Size = { 0.0f,0.0f };
	XMFLOAT2 StickHit_Size = { 0.05f,1.6f };	//�����̂�����T�C�Y

	for (int i = 0; i < BLOCKMAX; i++) {
		mBlock[i] = new StaticObject(mCamera);
		mBlock[i]->SetSize(1.0f, 2.0f);
	}

	mBlockHit[0] = new HitSquare(&mBlock[0]->mSprite->mCenter, Hit_Size, gap, 0.0f);
	mBlockHit[1] = new HitSquare(&mBlock[0]->mSprite->mCenter, Hit_Size, gap, 0.0f);

	//�e�N�X�`��,���W�Z�b�g
	mBlock[0]->mSprite->SetTexture(mPlateTex);	//�M
	mBlock[0]->SetPosition(1.1f, -1.3f);
	mBlock[0]->SetSize(1.3f, 1.4f);
	// �~�̂����蔻��
	mBlockHitCircle[0] = new HitCircle(&mBlock[0]->mSprite->mCenter,0.6f);

	mBlock[1]->mSprite->SetTexture(mCupTex);	//�J�b�v
	mBlock[1]->SetPosition(1.3f, 1.3f);
	mBlock[1]->SetSize(0.7f, 0.7f);
	// �~�̂����蔻��
	mBlockHitCircle[1] = new HitCircle(&mBlock[1]->mSprite->mCenter, 0.25f);
	

	mBlock[2]->mSprite->SetTexture(mStickTex);	//��
	mBlock[2]->SetPosition(-1.4f, -1.1f);
	mBlock[2]->SetSize(1.4f, 1.8f);
	mBlockHit[2] = new HitSquare(&mBlock[2]->mSprite->mCenter, StickHit_Size, gap, 0.0f);


	LoadTexture(L"assets/images/Item/CatMark.png", &mCatMarkTex);		//�L�̃}�[�J�[

	//�L�̃}�[�J�[
	mCatMark = new StaticObject(mCamera);
	mCatMark->mSprite->SetTexture(mCatMarkTex);
	mCatMark->SetSize(0.2f, 0.2f);

	//�w�i�̏�����
	mBackGround = new StaticObject(mCamera);
	mBackGround->mSprite->SetTexture(mBgTex);
	mBackGround->SetSize(5.6f, 4.0f);
	
	//����
	for (int i = 0; i < 4; i++) {
		mTime[i] = new StaticObject(mCamera);
		mTime[i]->mSprite->SetTexture(mNumTex[0]);
		mTime[i]->SetSize(0.1f, 0.1f);
	}

	mFrisbee = new Frisbee(mCamera);
	mPlayer = new Player(mCamera, mFrisbee);	//�v���C���[
	mMiniMap = new MiniMap(mFloor->mDirt, mBlock);		//�~�j�}�b�v
	mCat = new Cat(mCamera);		//�L
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
	//��Q���̓�����
	//-----------------

	for (int i = 0; i < 2; i++)
	{
		//�L�Ƃ̓�����
		if (mCat->mHit->CheckHit(mBlockHitCircle[i]))
		{
			mCat->ChangeState(CatState::JUMP);
		}
		else if (mCat->GetState() == CatState::JUMP) {
			mCat->ChangeState(CatState::WALK);

		}

		//�t���X�r�[�Ƃ̓�����
		if ((mFrisbee->mCircle->CheckHit(mBlockHitCircle[i])
			&& mFrisbee->mState == FRISBEE_FRY))
		{
			mFrisbee->ChangeState(FRISBEE_DROP);
		}
		//�v���C���[�Ƃ̓�����
		if (mPlayer->mHit->CheckHit(mBlockHitCircle[i]))
		{
			mPlayer->SetResistance(mBlock[i]->mSprite->mCenter);
		}
		//���Ƃ̓�����
		if (mDog->mHit->CheckHit(mBlockHitCircle[i]))
		{
			mDog->SetResistance(mBlock[i]->mSprite->mCenter);
		}
		mBlock[i]->Update();
	}
	//40�b��1��L���o��
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
