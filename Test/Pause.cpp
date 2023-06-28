#include "Pause.h"


//<><><><><><><><><><><><><><><><><><>
// �֐����FPause
// �����F�R���X�g���N�^
//<><><><><><><><><><><><><><><><><><>
Pause::Pause()
{
	LoadTexture(L"assets/Test.png", &mBackTex);
	LoadTexture(L"assets/images/UI/Continue.png",   &mUIContinueTex);
	LoadTexture(L"assets/images/UI/Restart.png",    &mUIRestartTex);
	LoadTexture(L"assets/images/UI/Back_Title.png", &mUITitleBackTex);
	camera = { 0.0f,0.0f,1.0f };		//�J����
	
	//�w�i
	mBack = new StaticObject(camera);
	mBack->mSprite->SetTexture(mBackTex);
	mBack->SetSize(2.8f, 2.0f);
	color = { 0.0f,0.0f,0.0f,0.5f };	//�������ɂ���
	mBack->mSprite->SetColor(color);
	
	Normal = { 1.0f,1.0f,1.0f,1.0f };
	Black = { 0.5f,0.5f,0.5f,1.0f };
	Blue = { 0.0f,0.0f,1.0f,1.0f };

	//UI
	mReturnUI = new StaticObject(camera);
	mReturnUI->mSprite->SetTexture(mUIContinueTex);
	mReturnUI->SetSize(0.6f, 0.3f);
	mReturnUI->SetPosition(0.0f, 0.2f);

	mReplayUI = new StaticObject(camera);
	mReplayUI->mSprite->SetTexture(mUIRestartTex);
	mReplayUI->SetSize(0.6f, 0.3f);
	mReplayUI->SetPosition(0.0f, -0.3f);

	mTitleUI = new StaticObject(camera);
	mTitleUI->mSprite->SetTexture(mUITitleBackTex);
	mTitleUI->SetSize(0.8f, 0.3f);
	mTitleUI->SetPosition(0.0f, -0.8f);

	SelectID = RETURN;
}


//<><><><><><><><><><><><><><><><><><>
// �֐����F~Pause
// �����F�f�X�g���N�^
//<><><><><><><><><><><><><><><><><><>
Pause::~Pause()
{

	delete mTitleUI;
	delete mReplayUI;
	delete mReturnUI;
	delete mBack;
	COM_SAFE_RELEASE(mBackTex);
	COM_SAFE_RELEASE(mUIContinueTex);
	COM_SAFE_RELEASE(mUIRestartTex);
	COM_SAFE_RELEASE(mUITitleBackTex);
}

//<><><><><><><><><><><><><><><><><><>
// �֐����FUpdate
// �����F�X�V
//<><><><><><><><><><><><><><><><><><>
void Pause::Update()
{
	mBack->Update();
	mReturnUI->Update();
	mReplayUI->Update();
	mTitleUI->Update();

	if (Input_GetButtonTrigger(DOWN) || Input_GetKeyTrigger('S')) {
		SelectID++;	//�I��ID�����Z
	}
	if (Input_GetButtonTrigger(UP) || Input_GetKeyTrigger('W')) {
		SelectID--;	//�I��ID�����Z
	}


	if (SelectID > 2) {
		SelectID = 0;	//1�ԉ��܂ł��������ɖ߂�
	}
	if (SelectID < 0) {
		SelectID = 2;	//1�ԏ�܂ł������牺�ɖ߂�
	}


	//SelectID�ɂ���ĕ`���ύX�i�����͂��Ƃŏ���������j
	switch (SelectID)
	{
	case RETURN:
		mReturnUI->mSprite->SetColor(Normal);
		mReplayUI->mSprite->SetColor(Black);
		mTitleUI->mSprite->SetColor(Black);
		break;
	case REPLAY:
		mReplayUI->mSprite->SetColor(Normal);
		mReturnUI->mSprite->SetColor(Black);
		mTitleUI->mSprite->SetColor(Black);
		break;
	case TITLE_BACK:
		mTitleUI->mSprite->SetColor(Normal);
		mReturnUI->mSprite->SetColor(Black);
		mReplayUI->mSprite->SetColor(Black);
		break;
	default:
		break;
	}

}


//<><><><><><><><><><><><><><><><><><>
// �֐����FDraw
// �����F�`��
//<><><><><><><><><><><><><><><><><><>
void Pause::Draw()
{
	mBack->Draw();
	mReturnUI->Draw();
	mReplayUI->Draw();
	mTitleUI->Draw();

}

//<><><><><><><><><><><><><><><><><><>
// �֐����FSceneSelect
// �����F�V�[���I��
//<><><><><><><><><><><><><><><><><><>
int Pause::SceneSelect()
{
	if (Input_GetButtonTrigger(B) || Input_GetKeyTrigger(VK_SPACE)) {
		return SelectID;
	}
	else {
		return - 1;
	}

}

