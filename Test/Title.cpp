//======================================================================================
// ���O�FGameObject.h
// �����F�Q�[���I�u�W�F�N�g�̕\��
//======================================================================================

//------------------------------------
//		include
//------------------------------------
#include "Title.h"

int TitleSelect = 0;
int FirstPlay = 0;

//<><><><><><><><><><><><><><><><><><>
// �֐����F�R���X�g���N�^
// �����F������
// �����F�Ȃ�
// �߂�l�F�Ȃ�
//<><><><><><><><><><><><><><><><><><>
Title::Title()
{

	backObject = new StaticObject(camera);						//�w�i
	LoadTexture(L"assets/images/BackGround/TitleBackGround.png", &backTexture);
	backObject->mSprite->SetTexture(backTexture);
	backObject->SetPosition(0.0f, 0.0f);
	backObject->SetSize(2.8f, 2.0f);

	titleObject = new StaticObject(camera);						//�^�C�g�����S
	LoadTexture(L"assets/images/UI/TitleLogo.png", &titleTexture);
	titleObject->mSprite->SetTexture(titleTexture);
	titleObject->SetPosition(0.0f, 0.4f);
	titleObject->SetSize(1.7f, 1.4f);

	charaObject = new StaticObject(camera);						//�L�����N�^�[
	LoadTexture(L"assets/images/UI/TitleChara.png", &charaTexture);
	charaObject->mSprite->SetTexture(charaTexture);
	charaObject->SetPosition(-0.95f, -0.3f);
	charaObject->SetSize(1.0f, 1.4f);

	dogObject = new StaticObject(camera);						//����
	LoadTexture(L"assets/images/UI/TitleDog.png", &dogTexture);
	dogObject->mSprite->SetTexture(dogTexture);
	dogObject->SetPosition(0.9f, -0.4f);
	dogObject->SetSize(1.0f, 1.3f);

	startObject = new StaticObject(camera);						//�Q�[���X�^�[�g
	LoadTexture(L"assets/images/UI/StageSelect.png", &startTexture);
	startObject->mSprite->SetTexture(startTexture);

	LoadTexture(L"assets/images/UI/StageSelect2.png", &startTexture2);


	endObject = new StaticObject(camera);						//�Q�[���G���h
	LoadTexture(L"assets/images/UI/ShutDown.png", &endTexture);
	endObject->mSprite->SetTexture(endTexture);

	LoadTexture(L"assets/images/UI/ShutDown2.png", &endTexture2);
	Sound_Init(SOUND_LABEL_BGM000);

	
}

//<><><><><><><><><><><><><><><><><><>
// �֐����F�f�X�g���N�^
// �����F�������̉��
// �����F�Ȃ�
// �߂�l�F�Ȃ�
//<><><><><><><><><><><><><><><><><><>
Title::~Title()
{
	
	Sound_Uninit(SOUND_LABEL_BGM000);
	delete backObject;
	COM_SAFE_RELEASE(backTexture);

	delete titleObject;
	COM_SAFE_RELEASE(titleTexture);

	delete charaObject;
	COM_SAFE_RELEASE(charaTexture);

	delete dogObject;
	COM_SAFE_RELEASE(dogTexture);

	delete startObject;
	COM_SAFE_RELEASE(startTexture);
	COM_SAFE_RELEASE(startTexture2);

	delete endObject;
	COM_SAFE_RELEASE(endTexture);
	COM_SAFE_RELEASE(endTexture2);
}

//<><><><><><><><><><><><><><><><><><>
// �֐����F Draw
// �����F�`��
//<><><><><><><><><><><><><><><><><><>
void Title::Draw(void)
{
	backObject->Draw();
	titleObject->Draw();
	charaObject->Draw();
	dogObject->Draw();
	startObject->Draw();
	endObject->Draw();
}

//<><><><><><><><><><><><><><><><><><>
// �֐����F Update
// �����F�X�V
//<><><><><><><><><><><><><><><><><><>
void Title::Update(void)
{

	if (FirstPlay == 0) {
		Fade::FadeIn();
		FirstPlay = 1;
	}

	// �^�C�g���ł̃��[�h�I��(�C���X�g�ω�)
	if (TitleSelect == 0)
	{
		startObject->SetPosition(0.0f, -0.3f);
		startObject->SetSize(0.8f, 0.3f);

		endObject->SetPosition(0.0f, -0.7f);
		endObject->SetSize(0.8f, 0.3f);
	}
	else if(TitleSelect == 1)
	{
		startObject->mSprite->SetTexture(startTexture2);
		startObject->SetPosition(0.0f, -0.25f);
		startObject->SetSize(0.9f, 0.4f);

		endObject->mSprite->SetTexture(endTexture);
		endObject->SetPosition(0.0f, -0.7f);
		endObject->SetSize(0.8f, 0.3f);
	}
	else if (TitleSelect == 2)
	{
		startObject->mSprite->SetTexture(startTexture);
		startObject->SetPosition(0.0f, -0.3f);
		startObject->SetSize(0.8f, 0.3f);
	
		endObject->mSprite->SetTexture(endTexture2);
		endObject->SetPosition(0.0f, -0.75f);
		endObject->SetSize(0.9f, 0.4f);
	}

	if (Fade::mState == FADE_IN_END) {

		if (!mBgmPlay) {
			Play(SOUND_LABEL_BGM000);	//1��Đ�
			SetVolume(SOUND_LABEL_BGM000,0.5f);
			mBgmPlay = true;
		}

		// �^�C�g���ł̃��[�h�I��(����)
		if (TitleSelect == 0)
		{
			//Input_SetKeyDown(VK_UP);

			if (Input_GetButtonTrigger(UP) || Input_GetKeyTrigger('W'))
			{	
				TitleSelect = 1;
			}
			else if (Input_GetButtonTrigger(DOWN) || Input_GetKeyTrigger('S'))
			{
				TitleSelect = 2;
			}
		}
		else if (TitleSelect == 1)
		{
			if (Input_GetButtonTrigger(UP) || Input_GetButtonTrigger(DOWN) || Input_GetKeyTrigger('W') || Input_GetKeyTrigger('S'))
			{
				TitleSelect = 2;
			}
		}
		else if (TitleSelect == 2)
		{
			if (Input_GetButtonTrigger(UP) || Input_GetButtonTrigger(DOWN) || Input_GetKeyTrigger('W') || Input_GetKeyTrigger('S'))
			{
				TitleSelect = 1;
			}
		}
	}
	backObject->Update();
	titleObject->Update();
	charaObject->Update();
	dogObject->Update();
	startObject->Update();
	endObject->Update();

	//A�{�^���ŃV�[���J��
	if (Input_GetButtonTrigger(B) || Input_GetKeyTrigger(VK_SPACE)) {

		if (TitleSelect == 1)
		{
			Fade_Bubble::FadeOut();
			Stop(SOUND_LABEL_BGM000);
		}
		else if (TitleSelect == 2)
		{
			SceneManager::SceneChange(NONE_SCENE,NONE_TYPE);
			
		}

	}

	if (Fade_Bubble::mState == FADE_OUT_END) {
		SceneManager::SceneChange(SELECT, BUBBLE_FADE);
	}


	
}

//======================================================================================
// �S���ҁF		�ɓ�
// ��������F�@ 2022-12-01
// �`�[�����F	����	
//======================================================================================