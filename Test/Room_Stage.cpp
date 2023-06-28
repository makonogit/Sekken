#include "Room_Stage.h"

bool RobotInfoFlg = true;	//���{�b�g�̐���

extern DWORD gDeltaTime;
//<><><><><><><><><><><><><><><><><><>
// �֐����FRoom_Stage
// �����F�R���X�g���N�^
//<><><><><><><><><><><><><><><><><><>
Room_Stage::Room_Stage()
{
	//�}�b�v���̐ݒ�
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
	LoadTexture(L"assets/images/BackGround/Stage/Room_Stage.png", &mBgTex);		//�w�i�e�N�X�`��
	LoadTexture(L"assets/images/Block/Shose.png", &mShoesTex);					//�C
	LoadTexture(L"assets/images/Block/Sneakers.png", &mSneakerShoesTex);		//�X�j�[�J�[
	LoadTexture(L"assets/images/Block/Leather_shoes.png", &mLeatherShoesTex);	//�v�C

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


	//���{�b�g�̐���
	LoadTexture(L"assets/images/UI/Robotton.png", &mRobotInfoTex);

	RobotInfoUI = new StaticObject(mCamera);
	RobotInfoUI->mSprite->SetTexture(mRobotInfoTex);
	RobotInfoUI->SetSize(2.0f, 1.8f);


	//����̏�����
	mFloor = new Floor(mCamera,MapInfo);
	
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
	XMFLOAT2 ShoesHit_Size = { 0.25f,1.2f };	//�C�̂�����T�C�Y

	for (int i = 0; i < BLOCKMAX; i++) {
		mBlock[i] = new StaticObject(mCamera);
		mBlock[i]->SetSize(1.0f, 1.5f);

		mBlockHit[i] = new HitSquare(&mBlock[i]->mSprite->mCenter, ShoesHit_Size, gap, 0.0f);
	}

	//�e�N�X�`��,���W�Z�b�g
	mBlock[0]->mSprite->SetTexture(mShoesTex);			//�q�[��
	mBlock[0]->SetPosition(-1.2f, 1.1f);
	mBlockHit[0]->mAngle = -43 * PI;
	
	mBlock[1]->mSprite->SetTexture(mSneakerShoesTex);	//�X�j�[�J�[
	mBlock[1]->SetPosition( 0.8f, -1.3f);
	mBlockHit[1]->mAngle = -155 * PI;

	mBlock[2]->mSprite->SetTexture(mLeatherShoesTex);	//�v�C
	mBlock[2]->SetPosition(-1.7f,-1.0f);

	//�����蔻��
	XMFLOAT2 RobotHit_gap = { 0.0f,0.0f };
	XMFLOAT2 RobotHit_Size = { 0.4f,0.6f };

	mRobot = new Robot(mCamera);
	mRobotHit = new HitSquare(&mRobot->mSprite->mCenter, RobotHit_Size, RobotHit_gap, 0.0f);

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
	mPlayer = new Player(mCamera,mFrisbee);	//�v���C���[
	mMiniMap = new MiniMap(mFloor->mDirt, mBlock);		//�~�j�}�b�v
	mCat = new Cat(mCamera);		//�L
	mDog = new Dog(mCamera);

	fCameraZoom = 0.0f;
	mBGMSound = SOUND_LABEL_BGM006;
	Sound_Init(mBGMSound);
	Play(mBGMSound);
	SetVolume(mBGMSound, 0.25f);
}

//<><><><><><><><><><><><><><><><><><>
// �֐����F~Room_Stage
// �����F�f�X�g���N�^
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
// �֐����FUpdate
// �����F�X�V
//<><><><><><><><><><><><><><><><><><>
void Room_Stage::Update()
{

	if (RobotInfoFlg) {
		RobotInfoTime += gDeltaTime;
	}
	else {
		RobotInfoTime = 0.0f;
	}

	//��u�A�b�v�f�[�g���Ȃ��ƕ`�悳��Ȃ�
	if (RobotInfoTime < 0.1f) {

		//30�b��1��L���o��
		if (fCatTime >= 30.0f * 1000 && !mCat->Appearance) {
			mCat->SetAppearance(true);
			fCatTime = 0.0f;
		}

		Stage::Update();

		//���{�b�g�ƃv���C���[�Ƃ̓�����
		if (mPlayer->mHit->CheckHit(mRobotHit))
		{
			mPlayer->SetResistance(mRobot->mSprite->mCenter);
		}

		//���{�b�g�ƃt���X�r�[�Ƃ̓�����
		if ((mFrisbee->mCircle->CheckHit(mRobotHit)
			&& mFrisbee->mState == FRISBEE_FRY))
		{
			mFrisbee->ChangeState(FRISBEE_DROP);
		}

		//���{�b�g�Ə�Q���̓�����
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
// �֐����FDraw
// �����F�`��
//<><><><><><><><><><><><><><><><><><>
void Room_Stage::Draw()
{
	Stage::Draw();
	mRobot->Draw();

	if (RobotInfoFlg) {
		RobotInfoUI->Draw();
	}
}
