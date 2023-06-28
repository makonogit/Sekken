//------------------------------------
//		include
//------------------------------------
#include "Select.h"

extern DWORD gDeltaTime;
int Select::SelectStageID = ROOM_STAGE;	//�ŏ��͕����ɐݒ�
int Select::mInput = 0;

bool Stage_Info_Flg = true;		//�ŏ��ǂ���I��ł邩

//<><><><><><><><><><><><><><><><><><>
// �֐����FSelect
// �����F�R���X�g���N�^
//<><><><><><><><><><><><><><><><><><>
Select::Select()
{
	//�w�i
	LoadTexture(L"assets/images/BackGround/SelectBG.png", &mBgTex);
	
	mBg = new StaticObject(camera);
	mBg->mSprite->SetTexture(mBgTex);
	mBg->SetSize(2.8f, 2.0f);

	//----------------------------------
	//�X�e�[�W�I�u�W�F�N�g
	//----------------------------------
	LoadTexture(L"assets/images/UI/TableMiniature.png", &mTableObjTex);
	LoadTexture(L"assets/images/UI/BathRoomMiniature.png", &mBathObjTex);
	LoadTexture(L"assets/images/UI/EntranceMiniature.png", &mRoomObjTex);

	for (int i = 0; i < MAXSTAGE; i++) {
		mObject[i] = new StaticObject(camera);
	}

	//�e�N�X�`���w��
	mObject[BATH_STAGE]->mSprite->SetTexture(mBathObjTex);
	mObject[TABLE_STAGE]->mSprite->SetTexture(mTableObjTex);
	mObject[ROOM_STAGE]->mSprite->SetTexture(mRoomObjTex);

	//--------���W�w��------------
	//(�O)
	mObject[ROOM_STAGE]->SetPosition(0.0f, 0.0f);
	mObject[ROOM_STAGE]->SetSize(0.9f, 1.0f);
	
	//(��)
	mObject[TABLE_STAGE]->SetPosition(-1.0f, 0.0f);
	mObject[TABLE_STAGE]->SetSize(0.4f, 0.5f);
	
	//(�E)
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

	// �`���[�g���A���w�i
	mSelectBackUI = new StaticObject(camera);
	mSelectBackUI->mSprite->SetTexture(mSelectBackTex);
	mSelectBackUI->SetSize(2.8f, 2.0f);
	mSelectBackUI->mSprite->mColor.r = 0.0f;
	mSelectBackUI->mSprite->mColor.g = 0.0f;
	mSelectBackUI->mSprite->mColor.b = 0.0f;
	mSelectBackUI->mSprite->mColor.a = 0.0f;

	// �`���[�g���A��UI
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


	// �X�e�[�W�I��UI
	mSelectUI = new StaticObject(camera);
	mSelectUI->mSprite->SetTexture(mSelectTex);
	mSelectUI->SetSize(1.3f, 0.4f);
	mSelectUI->SetPosition(0.0f, 0.7f);

	// �X�^�[�gUI
	mStartUI = new StaticObject(camera);
	mStartUI->mSprite->SetTexture(mStartUITex);
	mStartUI->SetSize(2.5f, 2.5f);
	mStartUI->SetPosition(0.0f, 0.0f);
	mStartUI->SetActive(false);

	// �L�����Z��UI
	mCancelUI = new StaticObject(camera);
	mCancelUI->mSprite->SetTexture(mCancelUITex);
	mCancelUI->SetSize(2.5f, 2.5f);
	mCancelUI->SetPosition(0.0f, 0.0f);
	mCancelUI->SetActive(false);

	// ���x��UI
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

	// ����UI
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

	// �X�e�[�W��UI
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
	Stage_Dicision = true;	//�X�e�[�W���肵�Ă��Ȃ�
	SelectStageID = ROOM_STAGE;	//�ŏ��͕����ɐݒ�
}

//<><><><><><><><><><><><><><><><><><>
// �֐����F~Select
// �����F�f�X�g���N�^
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
	// �����N�e�N�X�`���̉��
	for (int i = 0; i < 4; i++)
	{
		COM_SAFE_RELEASE(mRankUITex[i]);
	}
}

//<><><><><><><><><><><><><><><><><><>
// �֐����FGetStageID
// �����F�X�e�[�WID�̎擾
//<><><><><><><><><><><><><><><><><><>
int Select::GetStageID(void)
{
	return SelectStageID;
}

//<><><><><><><><><><><><><><><><><><>
// �֐����FGetInput
// �����F���͏��̎擾
//<><><><><><><><><><><><><><><><><><>
int Select::GetInput(void)
{
	return mInput;
}

//<><><><><><><><><><><><><><><><><><>
// �֐����FSelectStage
// �����F�X�e�[�W�I��
//<><><><><><><><><><><><><><><><><><>
void Select::StageSelect(void)
{

	//�I�𒆂̃X�e�[�W��ύX
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

	//�I�𒆂̃X�e�[�W�ʂ̔z�u
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
	//�����
	//---------------------------------------------
	if (Rota == LEFT_ROTA) {

		//�����I�u�W�F�N�g
		//if(mObject[StageID[0]]->mSprite->mCenter.x )

		if (mObject[StageID[0]]->mSprite->mCenter.x >= 0.0f) {	//���S�ɍs���܂ňړ�
			mObject[StageID[0]]->mSprite->mCenter.x -= 0.002f * gDeltaTime;
			if (mObject[StageID[0]]->mSprite->mSize.x < 0.9f) {	//���s��\�����邽�߂Ɋg��
				mObject[StageID[0]]->mSprite->mSize.x += 0.001f * gDeltaTime;
				mObject[StageID[0]]->mSprite->mSize.y += 0.001f * gDeltaTime;
			}

		}

		//���S�I�u�W�F�N�g
		if (mObject[StageID[1]]->mSprite->mCenter.x >= -1.0f) {	//���[�ɍs���܂ňړ�
			mObject[StageID[1]]->mSprite->mCenter.x -= 0.001f* gDeltaTime;
			if (mObject[StageID[1]]->mSprite->mSize.x > 0.4f) {	//���s��\�����邽�߂ɏk��
				mObject[StageID[1]]->mSprite->mSize.x -= 0.001f * gDeltaTime;
				mObject[StageID[1]]->mSprite->mSize.y -= 0.001f * gDeltaTime;
			}
		}

		//�E���I�u�W�F�N�g
		if (mObject[StageID[2]]->mSprite->mCenter.x <= 1.0f) {	//�E�[�܂ňړ�
			mObject[StageID[2]]->mSprite->mCenter.x += 0.002f* gDeltaTime;
		}

		if (mObject[StageID[0]]->mSprite->mCenter.x <= 0.0f &&
			mObject[StageID[1]]->mSprite->mCenter.x <= -1.0f &&
			mObject[StageID[2]]->mSprite->mCenter.x >= 1.0f) {	//�����I��
			SelectStageID++;
			Rota = NONE_ROTA;
		}

	}

	//---------------------------------------------
	//�E���
	//---------------------------------------------
	if (Rota == RIGHT_ROTA) {
		//�E���I�u�W�F�N�g
		if (mObject[StageID[0]]->mSprite->mCenter.x >= -1.0f) {	//���[�ɍs���܂ňړ�
			mObject[StageID[0]]->mSprite->mCenter.x -= 0.002f* gDeltaTime;
		}

		//���S�I�u�W�F�N�g
		if (mObject[StageID[1]]->mSprite->mCenter.x <= 1.0f) {	//�E�[�ɍs���܂ňړ�
			mObject[StageID[1]]->mSprite->mCenter.x += 0.001f * gDeltaTime;
			if (mObject[StageID[1]]->mSprite->mSize.x > 0.4f) {	//���s��\�����邽�߂ɏk��
				mObject[StageID[1]]->mSprite->mSize.x -= 0.001f * gDeltaTime;
				mObject[StageID[1]]->mSprite->mSize.y -= 0.001f * gDeltaTime;
			}
		}

		////�����I�u�W�F�N�g
		if (mObject[StageID[2]]->mSprite->mCenter.x <= 0.0f) {	//���S�܂ňړ�
			mObject[StageID[2]]->mSprite->mCenter.x += 0.001f * gDeltaTime;
			if (mObject[StageID[2]]->mSprite->mSize.x < 0.9f) {	//���s��\�����邽�߂Ɋg��
				mObject[StageID[2]]->mSprite->mSize.x += 0.001f * gDeltaTime;
				mObject[StageID[2]]->mSprite->mSize.y += 0.001f * gDeltaTime;
			}

			
		}

		if (mObject[StageID[0]]->mSprite->mCenter.x <= -1.0f &&
			mObject[StageID[1]]->mSprite->mCenter.x >= 1.0f &&
			mObject[StageID[2]]->mSprite->mCenter.x >= 0.0f) {	//�E���I��
			SelectStageID--;
			Rota = NONE_ROTA;
		}
		
	}

	//�X�e�[�W���̒���
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
		mStageNameUI->mSprite->SetTexture(mRoomNameUITex);// �e�N�X�`���̕ύX
		mRankUI->mSprite->SetTexture(mRankUITex[1]);// �e�N�X�`���̕ύX
		break;
	case BATH_STAGE:
		BGM = SOUND_LABEL_BGM002;
		mStageNameUI->mSprite->SetTexture(mBathNameUITex);// �e�N�X�`���̕ύX
		mRankUI->mSprite->SetTexture(mRankUITex[2]);// �e�N�X�`���̕ύX
		break;
	case TABLE_STAGE:
		BGM = SOUND_LABEL_BGM004;
		mStageNameUI->mSprite->SetTexture(mTableNameUITex);// �e�N�X�`���̕ύX
		mRankUI->mSprite->SetTexture(mRankUITex[0]);// �e�N�X�`���̕ύX
		break;
	}
	if (OldBGM != BGM)// BGM���ς������
	{
		Stop(OldBGM);
		Play(BGM);
		SetVolume(BGM, 0.25f);
		mBGMTime = 0.0f;
	}

}

//<><><><><><><><><><><><><><><><><><>
// �֐����FStageInfo
// �����F�X�e�[�W�ڍו\��
//<><><><><><><><><><><><><><><><><><>
void Select::StageInfo(void)
{
	if (Rota == NONE_ROTA && Stage_Info != -1) {//��]������Ȃ�������
		//B�{�^���ŃX�e�[�W�ڍו\��
		if (Input_GetButtonTrigger(B) || Input_GetKeyTrigger(VK_SPACE)) {// �X�e�[�W����
			//�I�������X�e�[�W�I�u�W�F�N�g�ȊO���\��

			mSelectUI->SetActive(false);
			mObject[StageID[0]]->SetActive(false);
			mObject[StageID[2]]->SetActive(false);
			Stage_Info = true;

		}
	}

	if (Stage_Info == 1) {

		//�X�e�[�W�I�u�W�F�N�g�̈ړ�
		if (mObject[StageID[1]]->mSprite->mCenter.x >= -0.6f) {
			mObject[StageID[1]]->mSprite->mCenter.x -= 0.001f * gDeltaTime;
			if (mObject[StageID[1]]->mSprite->mSize.x <= 1.3f) {
				mObject[StageID[1]]->mSprite->mSize.x += 0.001f * gDeltaTime;
				mObject[StageID[1]]->mSprite->mSize.y += 0.001f * gDeltaTime;
			}

		}
		else {

			
		
			//�X�e�[�W����UI
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

			//UI�̕\��
			mStartUI->SetActive(true);
			mCancelUI->SetActive(true);
			mDifficultyBackUI->SetActive(true);
			mDifficultyUI->SetActive(true);
			mRankUI->SetActive(true);
			mRankBackUI->SetActive(true);
			mStageNameBackUI->SetActive(true);
			mStageNameUI->SetActive(true);
			mTutorialUI->SetActive(false);// ��\��
			//�X�e�[�W����UI�̃J�[�\���ړ�
			if (Input_GetButtonTrigger(LEFT) || Input_GetKeyTrigger('A')) {	//��
				if (Stage_Dicision) {
					Stage_Dicision = false;
				}
				else {
					Stage_Dicision = true;
				}
			}
			if (Input_GetButtonTrigger(RIGHT) || Input_GetKeyTrigger('D')) {//�E
				if (Stage_Dicision) {
					Stage_Dicision = false;
				}
				else {
					Stage_Dicision = true;
				}
			}

			if (Stage_Dicision) {	//�V�[���ړ�
				if (Input_GetButtonTrigger(B) || Input_GetKeyTrigger(VK_SPACE)) {
					Stop(BGM);
					Fade_Bubble::FadeOut();
				}
				if (Fade_Bubble::mState == FADE_OUT_END) {
					SceneManager::SceneChange(GAME_MAIN, BUBBLE_FADE);
				}
			}
			if (!Stage_Dicision) {
				if (Input_GetButtonTrigger(B) || Input_GetKeyTrigger(VK_SPACE)) {// �L�����Z��

					Stage_Info = false;
					//UI���\����
					mStartUI->SetActive(false);
					mCancelUI->SetActive(false);
					mDifficultyBackUI->SetActive(false);
					mDifficultyUI->SetActive(false);
					mRankUI->SetActive(false);
					mRankBackUI->SetActive(false);
					mStageNameBackUI->SetActive(false);
					mStageNameUI->SetActive(false);
					mTutorialUI->SetActive(true);// �\��
				}
			}

		}
		
	}
	else if (Stage_Info == 0)
	{
		//�X�e�[�W�I�u�W�F�N�g�����̈ʒu�Ɉړ�
		if (mObject[StageID[1]]->mSprite->mCenter.x <= 0.0f) {
			mObject[StageID[1]]->mSprite->mCenter.x += 0.001f * gDeltaTime;
			if (mObject[StageID[1]]->mSprite->mSize.x >= 1.0f) {
				mObject[StageID[1]]->mSprite->mSize.x -= 0.001f * gDeltaTime;
				mObject[StageID[1]]->mSprite->mSize.y -= 0.001f * gDeltaTime;
			}
		}
		else {
			//�I���O�̃I�u�W�F�N�g�̍ĕ\��
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
		if (Input_GetButtonTrigger(DOWN) || Input_GetKeyTrigger('S')) {//��
			/*mTutorialUI->mSprite->mSize.x = 2.6f;
			mTutorialUI->mSprite->mSize.y = 2.6f;*/
			mTutorialUI->mSprite->mColor.r = 1.0f;
			mTutorialUI->mSprite->mColor.g = 1.0f;
			mTutorialUI->mSprite->mColor.b = 1.0f;

			mSelectBackUI->mSprite->mColor.a = 0.5f;

			Stage_Info = -1;
		}
		if (Input_GetButtonTrigger(UP) || Input_GetKeyTrigger('W')) {//��
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
			mInput = 1;	//�R���g���[���[����
			Stop(BGM);
			Fade_Bubble::FadeOut();
		}
		if (Input_GetButtonTrigger(B) && !Input_GetKeyTrigger(VK_SPACE)) {
			SelectStageID = TUTORIAL_STAGE;
			mInput = 0;	//�L�[�{�[�h����
			Stop(BGM);
			Fade_Bubble::FadeOut();
		}
		if (Fade_Bubble::mState == FADE_OUT_END) {
			SceneManager::SceneChange(GAME_MAIN, BUBBLE_FADE);
		}
	}

}

//<><><><><><><><><><><><><><><><><><>
// �֐����FUpdate
// �����F�X�V
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
			StageSelect();	//�X�e�[�W�I��
		}
	}
	StageInfo();

}

//<><><><><><><><><><><><><><><><><><>
// �֐����FDraw
// �����F�`��
//<><><><><><><><><><><><><><><><><><>
void Select::Draw(void)
{
	mBg->Draw();

	//��]�����ɂ���ĕ`�揇��ύX
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
// �S���ҁF		�����S
// ��������F�@ 2022-12-01
// �`�[�����F	����	
//======================================================================================