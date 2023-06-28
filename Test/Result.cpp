#include "Result.h"

extern DWORD gDeltaTime;
int Result::nScore = 0;

//<><><><><><><><><><><><><><><><><><>
// �֐����F�R���X�g���N�^
// �����F������
//<><><><><><><><><><><><><><><><><><>
Result::Result()
{
	//�w�i�e�N�X�`���̃��[�h
	LoadTexture(L"assets/images/BackGround/ResultBackGround.png", &mBgTex);			//�w�i	
	LoadTexture(L"assets/images/UI/ReplayUI.png", &mReplayUITex);			//���v���C
	LoadTexture(L"assets/images/UI/RastUI.png", &mReturnUITex);				//�X�e�[�W�I���ɂ��ǂ�
	LoadTexture(L"assets/images/UI/RankC.png", &mScoreUITex[0]);			//�X�R�A(C)
	LoadTexture(L"assets/images/UI/RankB.png", &mScoreUITex[1]);			//�X�R�A(B)
	LoadTexture(L"assets/images/UI/RankA.png", &mScoreUITex[2]);			//�X�R�A(A)
	LoadTexture(L"assets/images/UI/RankS.png", &mScoreUITex[3]);			//�X�R�A(S)

	LoadTexture(L"assets/images/UI/CleanBarFlame.png", &mScoreGageFreamTex);	//�X�R�A�Q�[�W�g
	LoadTexture(L"assets/images/UI/CleanBarB.png", &mScoreGageBackTex);			//�X�R�A�Q�[�W�w�i
	LoadTexture(L"assets/images/UI/CleanBar.png", &mScoreGageTex);				//�X�R�A�Q�[�W
	LoadTexture(L"assets/images/UI/Cracker1.png", &mCrackerTex);				//�N���b�J�[
	LoadTexture(L"assets/images/UI/Cracker2.png", &mCracker_PaperTex);			//�N���b�J�[�̎�

	//�w�i
	mBg = new StaticObject(camera);
	mBg->mSprite->SetTexture(mBgTex);
	mBg->SetSize(2.8f, 2.0f);

	//���v���C
	mReplayUI = new StaticObject(camera);
	mReplayUI->mSprite->SetTexture(mReplayUITex);
	mReplayUI->SetSize(2.8f, 2.0f);
	
	//�X�e�[�W�I��
	mReturnUI = new StaticObject(camera);
	mReturnUI->mSprite->SetTexture(mReturnUITex);
	mReturnUI->SetSize(2.8f, 2.0f);
	
	//UI�I�𒆂̃T�C�Y
	SelectSize.x = 3.0f;
	SelectSize.y = 2.2f;

	mScoreUI = new StaticObject(camera);
	mScoreUI->mSprite->SetTexture(mScoreUITex[0]);
	mScoreUI->SetSize(2.8f, 2.0f);
	mScoreUI->SetActive(false);
	
	//�X�R�A�Q�[�W�̘g
	mScoreGageFream = new StaticObject(camera);
	mScoreGageFream->mSprite->SetTexture(mScoreGageFreamTex);
	mScoreGageFream->SetSize(GAGEMAX, 0.2f);
	mScoreGageFream->SetPosition(-0.4f, 0.5f);

	//�X�R�A�Q�[�W�̔w�i
	mScoreGageBack = new StaticObject(camera);
	mScoreGageBack->mSprite->SetTexture(mScoreGageBackTex);
	mScoreGageBack->SetSize(GAGEMAX, 0.2f);
	mScoreGageBack->SetPosition(-0.4f, 0.5f);

	//�X�R�A�Q�[�W
	mScoreGage = new StaticObject(camera);
	mScoreGage->mSprite->SetTexture(mScoreGageTex);
	mScoreGage->SetSize(0.0f, 0.2f);
	mScoreGage->SetPosition(-0.4f, 0.5f);

	//�N���b�J�[
	mCracker_Left = new StaticObject(camera);
	mCracker_Left->mSprite->SetTexture(mCrackerTex);
	mCracker_Left->SetSize(0.6f, 0.6f);
	mCracker_Left->SetPosition(-1.15f, -1.5f);
	//mCracker->SetActive(false);

	mCracker_Right = new StaticObject(camera);
	mCracker_Right->mSprite->SetTexture(mCrackerTex);
	mCracker_Right->SetSize(0.6f, 0.6f);
	//���E���]������
	fRevers = mCracker_Right->mSprite->mUV.w;
	mCracker_Right->mSprite->mUV.w = mCracker_Right->mSprite->mUV.x;
	mCracker_Right->mSprite->mUV.x = fRevers;

	mCracker_Right->SetPosition(1.15f, -1.5f);

	//�N���b�J�[�̎�
	mCracker_Paper_Left = new StaticObject(camera);
	mCracker_Paper_Left->mSprite->SetTexture(mCracker_PaperTex);
	mCracker_Paper_Left->SetSize(1.0f, 1.0f);
	mCracker_Paper_Left->SetPosition(-0.8f, -0.45f);
	
	mCracker_Paper_Left->SetActive(false);

	mCracker_Paper_Right = new StaticObject(camera);
	mCracker_Paper_Right->mSprite->SetTexture(mCracker_PaperTex);
	mCracker_Paper_Right->SetSize(1.0f, 1.0f);
	//���E���]������
	fRevers = mCracker_Paper_Right->mSprite->mUV.w;
	mCracker_Paper_Right->mSprite->mUV.w = mCracker_Paper_Right->mSprite->mUV.x;
	mCracker_Paper_Right->mSprite->mUV.x = fRevers;
	mCracker_Paper_Right->SetPosition(0.8f, -0.45f);
	
	mCracker_Paper_Right->SetActive(false);

	//�X�R�A���\�z�O�̐����̏ꍇ
	if (nScore > 100 || nScore <= 0) {
		nScore = 10;
	}

	fWeight = 0.0f;	//�d�͉���

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
// �֐����F�f�X�g���N�^
// �����F������
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
// �֐����FUpdate
// �����F�X�V
//<><><><><><><><><><><><><><><><><><>
void Result::Update()
{
	mBg->Update();			//�w�i

	mReplayUI->Update();	//���v���C
	mReturnUI->Update();	//�X�e�[�W�I��

	mScoreUI->Update();		//�X�R�A
	
	mScoreGage->Update();			//�X�R�A�Q�[�W
	mScoreGageBack->Update();		//�X�R�A�Q�[�W�̔w�i
	mScoreGageFream->Update();		//�X�R�A�Q�[�W�g
	
	mCracker_Left->Update();		//�N���b�J�[
	mCracker_Right->Update();
	
	mCracker_Paper_Left->Update();	//�N���b�J�[�̎�
	mCracker_Paper_Right->Update();

	if (Fade_Dogrun::mState == FADE_IN_END || Fade_Dogrun::mState == NONE_FADE) {
		if (GetSoundState(SOUND_LABEL_SE030) == false && GageState)
		{
			Play(SOUND_LABEL_SE030);
		}
		GageState = ScoreGageAnim();
	}
	
	//�Q�[�W�̃A�j���[�V�������I�������
	if (!GageState) {
		mScoreUI->SetActive(true);
		mSETime += gDeltaTime;
		if (GetSoundState(SOUND_LABEL_SE031) == false && mSound == false)
		{
			Stop(SOUND_LABEL_SE030);
			Play(SOUND_LABEL_SE031);
		}
		bool CrackerSE = false;
		//�X�R�A�����N�����߂�
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

		if (ScoreLank == 3) {	//S�����N�̎�����
			Cracker_Anim();	//�N���b�J�[
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
// �֐����FDraw
// �����F�`��
//<><><><><><><><><><><><><><><><><><>
void Result::Draw()
{
	mBg->Draw();	//�w�i
	
	mReplayUI->Draw();	//���v���C
	mReturnUI->Draw();	//�X�e�[�W�I��

	mScoreUI->Draw();	//�X�R�A

	mScoreGageBack->Draw();		//�X�R�A�Q�[�W�̔w�i
	mScoreGage->Draw();			//�X�R�A�Q�[�W
	mScoreGageFream->Draw();	//�X�R�A�Q�[�W�g

	mCracker_Left->Draw();		//�N���b�J�[
	mCracker_Right->Draw();

	mCracker_Paper_Left->Draw();	//�N���b�J�[�̎�
	mCracker_Paper_Right->Draw();
}

//<><><><><><><><><><><><><><><><><><>
// �֐����FSceneSelect
// �����F�V�[���I��
//<><><><><><><><><><><><><><><><><><>
void Result::SceneSelect()
{
	//�V�[���ԍ��̕ύX
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
// �֐����FScoreGaageAnim
// �����F�X�R�A�Q�[�W�̃A�j���[�V����
// �����F�Ȃ�
// �߂�l�Ftrue:�A�j���[�V�������@false:�I��
//<><><><><><><><><><><><><><><><><><>
bool Result::ScoreGageAnim()
{
	//�Q�[�W�̍ő吔(�X�R�A�ɔ�Ⴓ����)
	float GageMaxSize = (GAGEMAX / 100.0f) * (float)nScore;
	
	float GageAddSpeed = 0.0003f;	//�Q�[�W�̉��Z�X�s�[�h

	//�ő�T�C�Y�܂ő傫������
	if (mScoreGage->mSprite->mSize.x <= GageMaxSize) {
		mScoreGage->mSprite->mSize.x += GageAddSpeed * gDeltaTime;
	}
	else {
		return false;
	}

	//�Q�[�W�̈ʒu���X�V����(�Ȃ񂩂�����Ƃ���Ă�...)
	mScoreGage->mSprite->mCenter.x = -0.401f - ((GAGEMAX - mScoreGage->mSprite->mSize.x) / 2.0f);

	return true;
}

//<><><><><><><><><><><><><><><><><><>
// �֐����FCracker_Anim
// �����F�N���b�J�[�̃A�j���[�V����
//<><><><><><><><><><><><><><><><><><>
void Result::Cracker_Anim()
{
	float MoveSpeed = 0.002f;	//�N���b�J�[�̈ړ����x

	//���̃N���b�J�[
	if (mCracker_Left->mSprite->mCenter.x <= -0.9f)
	{
		mCracker_Left->mSprite->mCenter.x += MoveSpeed * gDeltaTime;
	}
	if (mCracker_Left->mSprite->mCenter.y <= -0.65f)
	{
		mCracker_Left->mSprite->mCenter.y += MoveSpeed * gDeltaTime;
	}

	//�N���b�J�[�̈ړ����I������玆��\��
	if (mCracker_Left->mSprite->mCenter.x >= -0.9f && mCracker_Left->mSprite->mCenter.y >= -0.65f) 
	{
		mCracker_Paper_Left->SetActive(true);

		fWeight += 0.00001f * gDeltaTime;
		//�ʒu���X�V
		mCracker_Paper_Left->mSprite->mCenter.x += 0.002f * gDeltaTime;
		mCracker_Paper_Left->mSprite->mCenter.y += (0.005f - fWeight) * gDeltaTime;

	}

	//�E�̃N���b�J�[
	if (mCracker_Right->mSprite->mCenter.x >= 0.9f)
	{
		mCracker_Right->mSprite->mCenter.x -= MoveSpeed * gDeltaTime;
	}
	if (mCracker_Right->mSprite->mCenter.y <= -0.65f)
	{
		mCracker_Right->mSprite->mCenter.y += MoveSpeed * gDeltaTime;
	}

	//�N���b�J�[�̈ړ����I������玆��\��
	if (mCracker_Right->mSprite->mCenter.x >= -0.9f && mCracker_Right->mSprite->mCenter.y >= -0.65f)
	{
		mCracker_Paper_Right->SetActive(true);

		//�ʒu���X�V
		mCracker_Paper_Right->mSprite->mCenter.x -= 0.002f * gDeltaTime;
		mCracker_Paper_Right->mSprite->mCenter.y += (0.005f - fWeight) * gDeltaTime;

	}



}


//<><><><><><><><><><><><><><><><><><>
// �֐����FGetScore
// �����F�X�R�A�̎󂯎��
// �����F�X�R�A
// �߂�l�F�Ȃ�
//<><><><><><><><><><><><><><><><><><>
void Result::GetScore(int Score)
{
	nScore = Score;
}
